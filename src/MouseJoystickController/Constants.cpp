// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Constants.h"


namespace mouse_joystick_controller
{
namespace constants
{
CONSTANT_STRING(device_name,"mouse_joystick_controller");

CONSTANT_STRING(firmware_name,"MouseJoystickController");
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
CONSTANT_STRING(state_reward_string,"REWARD");
CONSTANT_STRING(state_retract_string,"RETRACT");
CONSTANT_STRING(state_retracting_string,"RETRACTING");
CONSTANT_STRING(state_move_to_base_stop_string,"MOVE_TO_BASE_STOP");
CONSTANT_STRING(state_moving_to_base_stop_string,"MOVING_TO_BASE_STOP");
CONSTANT_STRING(state_assay_finished_string,"ASSAY_FINISHED");

const long seconds_per_minute = 60;
const long milliseconds_per_second = 1000;
const long milliseconds_per_minute = milliseconds_per_second*seconds_per_minute;

// Pull
const size_t pull_encoder_index = 0;
const size_t pull_encoder_initial_value = 0;
const size_t pull_channel = 0;
const long pull_pwm_offset_min = 0;
const long pull_pwm_offset_max = 80;

// Ready
const long ready_tone_delay = 0;
const long ready_tone_count = 1;

// Reward
const long reward_tone_delay = 0;
const long reward_tone_count = 1;
const long reward_solenoid_channels[REWARD_SOLENOID_CHANNEL_COUNT] =
  {
   0,
  };
const long reward_solenoid_count = 1;

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

const size_t audio_controller_address[4] =
  {
   3,
   3,
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
CONSTANT_STRING(percent_units,"%");

// Properties
extern const long channel_count = CHANNEL_COUNT;

const long hold_delay_element_default = 50;

CONSTANT_STRING(base_position_property_name,"basePosition");

CONSTANT_STRING(reach_position_property_name,"reachPosition");

CONSTANT_STRING(pull_threshold_property_name,"pullThreshold");
const long pull_threshold_min = -1000;
const long pull_threshold_max = 0;
const long pull_threshold_default = -75;

CONSTANT_STRING(pull_torque_property_name,"pullTorque");
const long pull_torque_min = 0;
const long pull_torque_max = 100;
const long pull_torque_default = 25;

CONSTANT_STRING(ready_tone_frequency_property_name,"readyToneFrequency");
const long ready_tone_frequency_default = 8000;

CONSTANT_STRING(ready_tone_duration_property_name,"readyToneDuration");
const long ready_tone_duration_min = 100;
const long ready_tone_duration_max = 2000;
const long ready_tone_duration_default = 200;

CONSTANT_STRING(reward_tone_frequency_property_name,"rewardToneFrequency");
const long reward_tone_frequency_default = 4000;

CONSTANT_STRING(reward_tone_duration_property_name,"rewardToneDuration");
const long reward_tone_duration_min = 100;
const long reward_tone_duration_max = 2000;
const long reward_tone_duration_default = 500;

CONSTANT_STRING(reward_solenoid_delay_property_name,"rewardSolenoidDelay");
const long reward_solenoid_delay_min = 100;
const long reward_solenoid_delay_max = 5000;
const long reward_solenoid_delay_default = 1000;

CONSTANT_STRING(reward_solenoid_duration_property_name,"rewardSolenoidDuration");
const long reward_solenoid_duration_min = 5;
const long reward_solenoid_duration_max = 1000;
const long reward_solenoid_duration_default = 80;

CONSTANT_STRING(trial_timeout_duration_property_name,"trialTimeoutDuration");
const long trial_timeout_duration_min = 1;
const long trial_timeout_duration_max = 3600;
const long trial_timeout_duration_default = 30;

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
