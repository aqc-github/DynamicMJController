// ----------------------------------------------------------------------------
// 5x3.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "5x3.h"


#if defined(__MK64FX512__)

namespace mouse_joystick
{
namespace constants
{
// Interrupts

// Units

// Properties
const long steps_per_position_units_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
   824, // microsteps/pellet/4 = (12.88steps/pellet)*(256microsteps/step)/4
   8063, // microsteps/mm = (200steps/rev)*(256microsteps/step)/((0.250in/rev)*(25.4mm/in))
   8063, // microsteps/mm = (200steps/rev)*(256microsteps/step)/((0.250in/rev)*(25.4mm/in))
  };

const long velocity_max_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
   80,
   40,
   40,
  };

const long velocity_min_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
   4,
   2,
   2,
  };

const long acceleration_max_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
   200,
   100,
   100,
  };

const long home_velocity_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
   20,
   -20,
   -20,
  };

const long run_current_default[stepper_controller::constants::DRIVER_COUNT] =
  {
   run_current_element_default,
   run_current_element_default,
   run_current_element_default,
  };

const long hold_current_default[stepper_controller::constants::DRIVER_COUNT] =
  {
   hold_current_element_default,
   hold_current_element_default,
   hold_current_element_default,
  };

const long hold_delay_default[stepper_controller::constants::DRIVER_COUNT] =
  {
   hold_delay_element_default,
   hold_delay_element_default,
   hold_delay_element_default,
  };

const long stage_channel_count_min = step_dir_controller::constants::CHANNEL_COUNT;
const long stage_channel_count_max = step_dir_controller::constants::CHANNEL_COUNT;
const long stage_channel_count_default = step_dir_controller::constants::CHANNEL_COUNT;

const long stage_position_min_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
   -76,
   0,
   0,
  };

const long stage_position_max_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
   0,
   80,
   80,
  };

const long base_position_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
   -74,
   70,
   20,
  };

const long deliver_position_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
   -74,
   75,
   20,
  };

const long clean_position_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
   -48,
   60,
   10,
  };

const bool inverted[optical_switch_interface::constants::OUTPUT_COUNT] =
  {
   true,
   false,
   false,
   false,
  };

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
