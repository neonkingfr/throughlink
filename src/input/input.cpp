#include "input/input.h"

#include <zephyr.h>

#include <device.h>
#include <devicetree/gpio.h>
#include <drivers/gpio.h>
#include <logging/log.h>

#define LOG_LEVEL LOG_LEVEL_INF
LOG_MODULE_REGISTER(input);

#include "arch.h"
#include "display/display.h"
#include "input/queue.h"
#include "input/touchpad.h"
#include "panic.h"
#include "profiling.h"

TouchpadData touchpad_data;

static void input_gpio_init();

void input_init() {
  input_gpio_init();
  input_touchpad_init();
}

#if defined(CONFIG_PASSINGLINK_INPUT_NONE)

static void input_gpio_init() {}

bool input_get_raw_state(RawInputState* out) {
#if defined(CONFIG_PASSINGLINK_INPUT_QUEUE)
  if (auto input = input_queue_get_state()) {
    *out = *input;
    return true;
  }
#endif

  memset(out, 0, sizeof(*out));
  return true;
}

#elif defined(CONFIG_PASSINGLINK_INPUT_EXTERNAL)

static RawInputState input_state;

static void input_gpio_init() {}

bool input_get_raw_state(RawInputState* out) {
#if defined(CONFIG_PASSINGLINK_INPUT_QUEUE)
  if (auto input = input_queue_get_state()) {
    *out = *input;
    return true;
  }
#endif

  *out = input_state;
  return true;
}

void input_set_raw_state(RawInputState* in) {
  input_state = *in;
}

#else

#define GPIO_PORT_COUNT 4

static const struct device* gpio_devices[GPIO_PORT_COUNT];
static uint8_t gpio_device_count;

static uint8_t gpio_indices[PL_GPIO_COUNT];

static uint8_t gpio_device_add(const struct device* device) {
  uint8_t i;
  for (i = 0; i < GPIO_PORT_COUNT; ++i) {
    if (device == gpio_devices[i]) {
      // Skipping already-cached device.
      return i;
    }
  }
  if (gpio_device_count == GPIO_PORT_COUNT) {
    PANIC("ran out of cached GPIO device slots");
  }

  i = gpio_device_count++;
  gpio_devices[i] = device;
  return i;
}

static void input_gpio_init() {
#define PL_GPIO(index, name)                                                                    \
  {                                                                                             \
    const struct device* device = device_get_binding(PL_GPIO_LABEL(name));                      \
    if (!device) {                                                                              \
      PANIC("failed to find gpio device %s", PL_GPIO_LABEL(name));                              \
    }                                                                                           \
    if (gpio_pin_configure(device, PL_GPIO_PIN(name), PL_GPIO_FLAGS(name) | GPIO_INPUT) != 0) { \
      PANIC("failed to configure gpio pin (device = %s, pin = %d)", PL_GPIO_LABEL(name),        \
            PL_GPIO_PIN(name));                                                                 \
    };                                                                                          \
    uint8_t device_offset = gpio_device_add(device);                                            \
    gpio_indices[index] = device_offset;                                                        \
  }
  PL_GPIOS()
#undef PL_GPIO
}

bool input_get_raw_state(RawInputState* out) {
  PROFILE("input_get_raw_state", 128);

#if defined(CONFIG_PASSINGLINK_INPUT_QUEUE)
  if (auto input = input_queue_get_state()) {
    *out = *input;
    return true;
  }
#endif

  gpio_port_value_t port_values[GPIO_PORT_COUNT];
  for (size_t i = 0; i < gpio_device_count; ++i) {
    if (gpio_port_get_raw(gpio_devices[i], &port_values[i]) != 0) {
      PANIC("failed to get gpio values");
    }
  }

#define PL_GPIO(index, name)                                            \
  {                                                                     \
    uint8_t device_index = gpio_indices[index];                         \
    bool value = port_values[device_index] & (1U << PL_GPIO_PIN(name)); \
    if constexpr (PL_GPIO_FLAGS(name) & GPIO_ACTIVE_LOW) {              \
      out->name = !value;                                               \
    } else {                                                            \
      out->name = value;                                                \
    }                                                                   \
  }
  PL_GPIOS()
#undef PL_GPIO

  return true;
}
#endif

// Convert ({-1, 0, 1}, {-1, 0, 1}) to a StickState.
static StickState stick_state_from_x_y(int horizontal, int vertical) {
  if (vertical == -1 && horizontal == 0) {
    return StickState::North;
  } else if (vertical == -1 && horizontal == 1) {
    return StickState::NorthEast;
  } else if (vertical == 0 && horizontal == 1) {
    return StickState::East;
  } else if (vertical == 1 && horizontal == 1) {
    return StickState::SouthEast;
  } else if (vertical == 1 && horizontal == 0) {
    return StickState::South;
  } else if (vertical == 1 && horizontal == -1) {
    return StickState::SouthWest;
  } else if (vertical == 0 && horizontal == -1) {
    return StickState::West;
  } else if (vertical == -1 && horizontal == -1) {
    return StickState::NorthWest;
  } else {
    return StickState::Neutral;
  }

  __builtin_unreachable();
}

// Scale {-1, 0, 1} to {-128, 0, 127}.
static uint8_t stick_scale(int sign) {
  if (sign < 0) {
    return 0x00;
  } else if (sign == 0) {
    return 0x80;
  } else {
    return 0xFF;
  }
}

static bool input_locked = false;
bool input_get_locked() {
  return input_locked;
}

void input_set_locked(bool locked) {
#if defined(CONFIG_PASSINGLINK_DISPLAY)
  if (locked != input_locked) {
    display_set_locked(locked);
  }
#endif

  input_locked = locked;
}

struct ButtonHistory {
  bool state;

  // The cycle on which it entered the state.
  uint64_t tick;
};

struct {
#define PL_GPIO(index, name) ButtonHistory name;
  PL_GPIOS()
#undef PL_GPIO
} button_history;

// Debounce a button input, given its history.
// Updates ButtonHistory and returns the value that should be used.
static bool input_debounce(bool current_state, ButtonHistory* button_history,
                           uint64_t current_tick) {
  if (current_state == button_history->state) {
    return current_state;
  }

  // Only allow transitions every 5 milliseconds.
  // TODO: Make configurable?
  uint64_t duration_ticks = current_tick - button_history->tick;
  constexpr uint64_t transition_time = k_ms_to_cyc_ceil64(5);
  if (duration_ticks < transition_time) {
    return !current_state;
  }

  button_history->state = current_state;
  button_history->tick = current_tick;
  return current_state;
}

static bool input_parse(InputState* out, RawInputState* in) {
  PROFILE("input_parse", 128);

  // Copy TouchpadData.
  out->touchpad_data = touchpad_data;

  uint64_t current_tick = k_uptime_ticks();
  // Debounce inputs.
#define PL_GPIO(index, name) \
  in->name = input_debounce(in->name, &button_history.name, current_tick);
  PL_GPIOS()
#undef PL_GPIO

#if defined(PL_GPIO_MODE_LOCK_AVAILABLE)
  input_set_locked(in->mode_lock);
#endif

  // Assign buttons.
  out->button_north = in->button_north;
  out->button_east = in->button_east;
  out->button_south = in->button_south;
  out->button_west = in->button_west;
  out->button_l1 = in->button_l1;
  out->button_l2 = in->button_l2;
  out->button_l3 = in->button_l3;
  out->button_r1 = in->button_r1;
  out->button_r2 = in->button_r2;
  out->button_r3 = in->button_r3;
  out->button_touchpad = in->button_touchpad;

  out->button_select = input_locked ? 0 : in->button_select;
  out->button_start = input_locked ? 0 : in->button_start;
  out->button_home = input_locked ? 0 : in->button_home;

  // Assign stick.
  int stick_vertical = 0;
  int stick_horizontal = 0;

  // Note: positive Y means down.
  // TODO: Make SOCD cleaning customizable.
  if (in->stick_up) {
    --stick_vertical;
  }
  if (in->stick_down) {
    ++stick_vertical;
  }
  if (in->stick_right) {
    ++stick_horizontal;
  }
  if (in->stick_left) {
    --stick_horizontal;
  }

  enum class OutputMode {
    mode_dpad,
    mode_ls,
    mode_rs,
  };

  OutputMode output_mode = OutputMode::mode_dpad;
#define PL_GPIO(index, mode)        \
  else if (in->mode) {              \
    output_mode = OutputMode::mode; \
  }
  if (false) {
  }
  PL_GPIO_OUTPUT_MODES();
#undef PL_GPIO

  out->dpad = StickState::Neutral;
  out->left_stick_x = 128;
  out->left_stick_y = 128;
  out->right_stick_x = 128;
  out->right_stick_y = 128;

  switch (output_mode) {
    case OutputMode::mode_dpad:
      out->dpad = stick_state_from_x_y(stick_horizontal, stick_vertical);
      break;

    case OutputMode::mode_ls:
      out->left_stick_x = stick_scale(stick_horizontal);
      out->left_stick_y = stick_scale(stick_vertical);
      break;

    case OutputMode::mode_rs:
      out->right_stick_x = stick_scale(stick_horizontal);
      out->right_stick_y = stick_scale(stick_vertical);
      break;
  }

  return true;
}

bool input_get_state(InputState* out) {
  RawInputState input;
  return input_get_raw_state(&input) && input_parse(out, &input);
}
