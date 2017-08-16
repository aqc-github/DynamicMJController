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
const double steps_per_position_units_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
    0.05,
    0.05,
    0.05,
  };

const double velocity_max_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
    200,
    200,
    200,
  };

const double velocity_min_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
    20,
    20,
    20,
  };

const double acceleration_max_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
    200,
    200,
    200,
  };

const double home_velocity_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
    -50,
    -50,
    -50,
  };

const bool invert_driver_direction_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
    false,
    true,
    false,
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

const double stage_positions_min_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
    0,
    0,
    0,
  };

const double stage_positions_max_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
    200,
    200,
    200,
  };

// const double base_positions_default[step_dir_controller::constants::CHANNEL_COUNT] =
//   {
//     -17.5,
//     70,
//     20,
//   };

// const double deliver_positions_default[step_dir_controller::constants::CHANNEL_COUNT] =
//   {
//     -17.5,
//     75,
//     20,
//   };

// const bool inverted[optical_switch_interface::constants::OUTPUT_COUNT] =
//   {
//     true,
//     false,
//     false,
//     false,
//   };

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
