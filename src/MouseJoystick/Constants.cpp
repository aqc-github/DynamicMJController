// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Constants.h"


namespace mouse_joystick
{
namespace constants
{
CONSTANT_STRING(device_name,"mouse_joystick");

CONSTANT_STRING(firmware_name,"MouseJoystick");
// Use semantic versioning http://semver.org/
const modular_server::FirmwareInfo firmware_info =
  {
   .name_ptr=&firmware_name,
   .version_major=1,
   .version_minor=0,
   .version_patch=1,
  };

CONSTANT_STRING(state_string,"state");
CONSTANT_STRING(state_assay_not_started_string,"ASSAY_NOT_STARTED");
CONSTANT_STRING(state_assay_started_string,"ASSAY_STARTED");
CONSTANT_STRING(state_homing_string,"HOMING");
CONSTANT_STRING(state_move_to_base_start_string,"MOVE_TO_BASE_START");
CONSTANT_STRING(state_moving_to_base_start_string,"MOVING_TO_BASE_START");
CONSTANT_STRING(state_move_to_reach_string,"MOVE_TO_REACH");
CONSTANT_STRING(state_moving_to_reach_string,"MOVING_TO_REACH");
CONSTANT_STRING(state_wait_for_pull_string,"WAIT_FOR_PULL");
CONSTANT_STRING(state_waiting_for_pull_string,"WAITING_FOR_PULL");
CONSTANT_STRING(state_retract_string,"RETRACT");
CONSTANT_STRING(state_retracting_string,"RETRACTING");
CONSTANT_STRING(state_move_to_base_stop_string,"MOVE_TO_BASE_STOP");
CONSTANT_STRING(state_moving_to_base_stop_string,"MOVING_TO_BASE_STOP");
CONSTANT_STRING(state_assay_finished_string,"ASSAY_FINISHED");

const long seconds_per_minute = 60;
const long milliseconds_per_second = 1000;
const long milliseconds_per_minute = milliseconds_per_second*seconds_per_minute;

// Clients
const size_t encoder_interface_simple_address[1] =
  {
   3,
  };

const size_t power_switch_controller_address[2] =
  {
   3,
   3,
  };

// Interrupts

// Units
CONSTANT_STRING(mm_units,"mm");
CONSTANT_STRING(ms_units,"ms");
CONSTANT_STRING(seconds_units,"s");
CONSTANT_STRING(minutes_units,"min");
CONSTANT_STRING(hz_units,"Hz");

// Properties
extern const long channel_count = CHANNEL_COUNT;

const long hold_delay_element_default = 50;

CONSTANT_STRING(base_position_property_name,"basePosition");

CONSTANT_STRING(reach_position_property_name,"reachPosition");

// Parameters

// Functions
CONSTANT_STRING(set_client_property_values_function_name,"setClientPropertyValues");
CONSTANT_STRING(get_assay_status_function_name,"getAssayStatus");
CONSTANT_STRING(move_joystick_to_base_position_function_name,"moveJoystickToBasePosition");
CONSTANT_STRING(move_joystick_to_reach_position_function_name,"moveJoystickToReachPosition");

// Callbacks
CONSTANT_STRING(start_trial_callback_name,"startTrial");
CONSTANT_STRING(abort_callback_name,"abort");

// Errors
}
}
