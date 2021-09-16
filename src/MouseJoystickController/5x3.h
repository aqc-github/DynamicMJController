// ----------------------------------------------------------------------------
// 5x3.h
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#ifndef MOUSE_JOYSTICK_CONTROLLER_5X3_CONSTANTS_H
#define MOUSE_JOYSTICK_CONTROLLER_5X3_CONSTANTS_H
#include "Constants.h"


#if defined(__MK64FX512__)

namespace mouse_joystick_controller
{
namespace constants
{
enum{CHANNEL_COUNT=2};

// Pins

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern const long steps_per_position_units_default[CHANNEL_COUNT];

extern const long velocity_max_default[CHANNEL_COUNT];

extern const long velocity_min_default[CHANNEL_COUNT];

extern const long acceleration_max_default[CHANNEL_COUNT];

extern const long home_velocity_default[CHANNEL_COUNT];

extern const bool invert_driver_direction_default[CHANNEL_COUNT];

extern const long run_current_default[CHANNEL_COUNT];

extern const long hold_current_default[CHANNEL_COUNT];

extern const long hold_delay_default[CHANNEL_COUNT];

extern const long stage_position_min_default[CHANNEL_COUNT];

extern const long stage_position_max_default[CHANNEL_COUNT];

extern const long home_current_default[CHANNEL_COUNT];

extern const long idle_current_default[CHANNEL_COUNT];

extern const long base_position_default[CHANNEL_COUNT];

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
#endif
