// ----------------------------------------------------------------------------
// 5x3.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "5x3.h"


#if defined(__MK64FX512__)

namespace mouse_joystick_controller
{
namespace constants
{
// Interrupts

// Units

// Properties
const long steps_per_position_units_default[CHANNEL_COUNT] =
  {
   32,
   32,
  };

const long velocity_max_default[CHANNEL_COUNT] =
  {
   150,
   150,
  };

 const long velocity_min_default[CHANNEL_COUNT] =
  {
   10,
   10,
  };

const long acceleration_max_default[CHANNEL_COUNT] =
  {
   150,
   150,
  };

const long home_velocity_default[CHANNEL_COUNT] =
  {
   -50,
   -50,
  };

const bool invert_driver_direction_default[CHANNEL_COUNT] =
  {
   false,
   true,
  };

const long run_current_default[CHANNEL_COUNT] =
  {
   20,
   50,
  };

const long hold_current_default[CHANNEL_COUNT] =
  {
   10,
   25,
  };

const long hold_delay_default[CHANNEL_COUNT] =
  {
   hold_delay_element_default,
   hold_delay_element_default,
  };

const long stage_position_min_default[CHANNEL_COUNT] =
  {
   0,
   0,
  };

const long stage_position_max_default[CHANNEL_COUNT] =
  {
   100,
   150,
  };

const long base_position_default[CHANNEL_COUNT] =
  {
   5,
   150,
  };

const long reach_position_default[CHANNEL_COUNT] =
  {
   50,
   5,
  };

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
