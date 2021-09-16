// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
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
  .version_major=4,
  .version_minor=1,
  .version_patch=0,
};

CONSTANT_STRING(repeat_trial_count_string,"repeat_trial_count");
CONSTANT_STRING(pull_torque_string,"pull_torque");
CONSTANT_STRING(lickport_reward_duration_string,"lickport_reward_duration");
CONSTANT_STRING(reach_position_string,"reach_position");

CONSTANT_STRING(unread_trial_timing_data_string,"unread_trial_timing_data");
CONSTANT_STRING(finished_trial_count_string,"finished_trial_count");
CONSTANT_STRING(successful_trial_count_string,"successful_trial_count");
CONSTANT_STRING(trial_aborted_string,"trial_aborted");
CONSTANT_STRING(assay_aborted_string,"assay_aborted");
CONSTANT_STRING(pull_threshold_string,"pull_threshold");
CONSTANT_STRING(set_in_assay_string,"set_in_assay");
CONSTANT_STRING(repeat_set_count_string,"repeat_set_count");
CONSTANT_STRING(block_in_set_string,"block_in_set");
CONSTANT_STRING(block_count_string,"block_count");
CONSTANT_STRING(trial_in_block_string,"trial_in_block");
CONSTANT_STRING(block_string,"block");

CONSTANT_STRING(trial_start_string,"trial_start");
CONSTANT_STRING(mouse_ready_string,"mouse_ready");
CONSTANT_STRING(joystick_ready_string,"joystick_ready");
CONSTANT_STRING(pull_string,"pull");
CONSTANT_STRING(push_string,"push");
CONSTANT_STRING(timeout_string,"timeout");
CONSTANT_STRING(trial_abort_string,"trial_abort");

CONSTANT_STRING(state_string,"state");
CONSTANT_STRING(state_assay_not_started_string,"ASSAY_NOT_STARTED");
CONSTANT_STRING(state_assay_started_string,"ASSAY_STARTED");
CONSTANT_STRING(state_homing_0_string,"HOMING_0");
CONSTANT_STRING(state_homing_1_string,"HOMING_1");
CONSTANT_STRING(state_move_to_homed_0_string,"MOVE_TO_HOMED_0");
CONSTANT_STRING(state_moving_to_homed_0_string,"MOVING_TO_HOMED_0");
CONSTANT_STRING(state_move_to_homed_1_string,"MOVE_TO_HOMED_1");
CONSTANT_STRING(state_moving_to_homed_1_string,"MOVING_TO_HOMED_1");
CONSTANT_STRING(state_move_to_base_start_string,"MOVE_TO_BASE_START");
CONSTANT_STRING(state_moving_to_base_start_string,"MOVING_TO_BASE_START");
CONSTANT_STRING(state_wait_to_start_trial_string,"WAIT_TO_START_TRIAL");
CONSTANT_STRING(state_waiting_to_start_trial_string,"WAITING_TO_START_TRIAL");
CONSTANT_STRING(state_wait_for_mouse_ready_string,"WAIT_FOR_MOUSE_READY");
CONSTANT_STRING(state_waiting_for_mouse_ready_string,"WAITING_FOR_MOUSE_READY");
CONSTANT_STRING(state_move_to_reach_string,"MOVE_TO_REACH");
CONSTANT_STRING(state_moving_to_reach_string,"MOVING_TO_REACH");
CONSTANT_STRING(state_wait_for_pull_string,"WAIT_FOR_PULL");
CONSTANT_STRING(state_waiting_for_pull_string,"WAITING_FOR_PULL");
CONSTANT_STRING(state_reward_string,"REWARD");
CONSTANT_STRING(state_retract_string,"RETRACT");
CONSTANT_STRING(state_retracting_0_string,"RETRACTING_0");
CONSTANT_STRING(state_retracting_1_string,"RETRACTING_1");
CONSTANT_STRING(state_move_to_retracted_0_string,"MOVE_TO_RETRACTED_0");
CONSTANT_STRING(state_moving_to_retracted_0_string,"MOVING_TO_RETRACTED_0");
CONSTANT_STRING(state_move_to_retracted_1_string,"MOVE_TO_RETRACTED_1");
CONSTANT_STRING(state_moving_to_retracted_1_string,"MOVING_TO_RETRACTED_1");
CONSTANT_STRING(state_check_trial_termination_string,"CHECK_TRIAL_TERMINATION");
CONSTANT_STRING(state_finish_trial_string,"FINISH_TRIAL");
CONSTANT_STRING(state_wait_until_trial_timing_data_read_string,"WAIT_UNTIL_TRIAL_TIMING_DATA_READ");
CONSTANT_STRING(state_waiting_until_trial_timing_data_read_string,"WAITING_UNTIL_TRIAL_TIMING_DATA_READ");
CONSTANT_STRING(state_move_to_base_stop_string,"MOVE_TO_BASE_STOP");
CONSTANT_STRING(state_moving_to_base_stop_string,"MOVING_TO_BASE_STOP");
CONSTANT_STRING(state_assay_finished_string,"ASSAY_FINISHED");

const long seconds_per_minute = 60;
const long milliseconds_per_second = 1000;
const long milliseconds_per_minute = milliseconds_per_second*seconds_per_minute;

const long activate_lickport_delay = 40;

const long pulse_duration = 25;

const long not_touching_switch_position = 20;

// Ready
const long joystick_ready_tone_delay = 40;
const long joystick_ready_tone_count = 1;

// Pull
const size_t pull_encoder_index = 0;
const size_t pull_encoder_initial_value = 0;
const size_t pull_channel = 0;
const long pull_pwm_offset_min = 0;
const long pull_pwm_offset_max = 80;
const unsigned long pull_push_poll_period = 50;

// Reward
const long reward_tone_delay = 40;
const long reward_tone_count = 1;
const long lickport_reward_channels[LICKPORT_REWARD_CHANNEL_COUNT] =
{
  0,
};
const long lickport_reward_count = 1;

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

const size_t audio_controller_address[3] =
{
  3,
  3,
  3,
};

// Pins

// Units
CONSTANT_STRING(mm_units,"mm");
CONSTANT_STRING(ms_units,"ms");
CONSTANT_STRING(seconds_units,"s");
CONSTANT_STRING(minutes_units,"min");
CONSTANT_STRING(hz_units,"Hz");
CONSTANT_STRING(percent_units,"%");

// Properties
const long steps_per_position_units_element_default = 32;

const long velocity_max_element_default = 800;

const long velocity_min_element_default = 10;

const long acceleration_max_element_default = 800;

const long home_velocity_element_default = -85;

const bool right_switches_enabled_element_default = false;

const bool right_switch_stop_enabled_element_default = false;

const long invert_driver_direction_element_0_default = false;
const long invert_driver_direction_element_1_default = true;

const long run_current_element_0_default = 20;
const long run_current_element_1_default = 35;

const long hold_current_element_0_default = 10;
const long hold_current_element_1_default = 20;

const long hold_delay_element_default = 50;

const long stage_position_min_element_0_default = 0;
const long stage_position_min_element_1_default = 0;

const long stage_position_max_element_0_default = 175;
const long stage_position_max_element_1_default = 300;

CONSTANT_STRING(home_current_property_name,"homeCurrent");
const long home_current_element_0_default = 25;
const long home_current_element_1_default = 35;

CONSTANT_STRING(idle_current_property_name,"idleCurrent");
const long idle_current_element_0_default = 6;
const long idle_current_element_1_default = 12;

CONSTANT_STRING(base_position_property_name,"basePosition");
const long base_position_element_0_default = not_touching_switch_position;
const long base_position_element_1_default = 300;

CONSTANT_STRING(pull_threshold_property_name,"pullThreshold");
const long pull_threshold_min = -1000;
const long pull_threshold_max = 0;
const long pull_threshold_default = -50;

CONSTANT_STRING(push_threshold_property_name,"pushThreshold");
const long push_threshold_min = 0;
const long push_threshold_max = 1000;
const long push_threshold_default = 50;

CONSTANT_STRING(joystick_ready_tone_frequency_property_name,"joystickReadyToneFrequency");
const long joystick_ready_tone_frequency_default = 8000;

CONSTANT_STRING(joystick_ready_tone_duration_property_name,"joystickReadyToneDuration");
const long joystick_ready_tone_duration_min = 100;
const long joystick_ready_tone_duration_max = 2000;
const long joystick_ready_tone_duration_default = 200;

CONSTANT_STRING(reward_tone_frequency_property_name,"rewardToneFrequency");
const long reward_tone_frequency_default = 4000;

CONSTANT_STRING(reward_tone_duration_property_name,"rewardToneDuration");
const long reward_tone_duration_min = 100;
const long reward_tone_duration_max = 2000;
const long reward_tone_duration_default = 500;

CONSTANT_STRING(tone_volume_property_name,"toneVolume");
const long tone_volume_min = 0;
const long tone_volume_max = 100;
const long tone_volume_default = 25;

CONSTANT_STRING(lickport_reward_delay_property_name,"rewardLickportDelay");
const long lickport_reward_delay_min = 100;
const long lickport_reward_delay_max = 5000;
const long lickport_reward_delay_default = 1000;

CONSTANT_STRING(trial_timeout_duration_property_name,"trialTimeoutDuration");
const long trial_timeout_duration_min = 1;
const long trial_timeout_duration_max = 20;
const long trial_timeout_duration_default = 20;

CONSTANT_STRING(repeat_aborted_trial_property_name,"repeatAbortedTrial");
const bool repeat_aborted_trial_default = true;

CONSTANT_STRING(repeat_set_count_property_name,"repeatSetCount");
const long repeat_set_count_min = 1;
const long repeat_set_count_max = 100;
const long repeat_set_count_default = 2;

CONSTANT_STRING(start_trial_duration_property_name,"startTrialDuration");
const long start_trial_duration_min = 0;
const long start_trial_duration_max = 60;
const long start_trial_duration_default = 0;

CONSTANT_STRING(wait_until_trial_timing_data_read_property_name,"waitUntilTrialTimingDataRead");
const bool wait_until_trial_timing_data_read_default = true;

// Parameters
CONSTANT_STRING(repeat_trial_count_parameter_name,"repeat_trial_count");
const long repeat_trial_count_min = 1;
const long repeat_trial_count_max = 100;

CONSTANT_STRING(pull_torque_parameter_name,"pull_torque");
const long pull_torque_min = 0;
const long pull_torque_max = 100;

CONSTANT_STRING(lickport_reward_duration_parameter_name,"lickport_reward_duration");
const long lickport_reward_duration_min = 5;
const long lickport_reward_duration_max = 1000;

CONSTANT_STRING(reach_position_parameter_name,"reach_position");
const long reach_position_element_min = 0;
const long reach_position_element_max = 1000;
const long reach_position_length_min = channel_count;
const long reach_position_length_max = channel_count;

CONSTANT_STRING(lickport_activation_duration_parameter_name,"lickport_activation_duration");
const long lickport_activation_duration_min = 1;
const long lickport_activation_duration_max = 20;

CONSTANT_STRING(lickport_activation_count_parameter_name,"lickport_activation_count");
const long lickport_activation_count_min = 1;
const long lickport_activation_count_max = 20;

// Functions
CONSTANT_STRING(get_set_function_name,"getSet");
CONSTANT_STRING(clear_set_function_name,"clearSet");
CONSTANT_STRING(get_block_count_function_name,"getBlockCount");
CONSTANT_STRING(add_block_to_set_function_name,"addBlockToSet");
CONSTANT_STRING(start_assay_function_name,"startAssay");
CONSTANT_STRING(get_assay_status_function_name,"getAssayStatus");
CONSTANT_STRING(move_joystick_to_base_position_function_name,"moveJoystickToBasePosition");
CONSTANT_STRING(move_joystick_to_reach_position_function_name,"moveJoystickToReachPosition");
CONSTANT_STRING(activate_lickport_function_name,"activateLickport");
CONSTANT_STRING(get_trial_timing_data_function_name,"getTrialTimingData");

// Callbacks
CONSTANT_STRING(start_trial_callback_name,"startTrial");
CONSTANT_STRING(abort_trial_callback_name,"abortTrial");
CONSTANT_STRING(abort_assay_callback_name,"abortAssay");
CONSTANT_STRING(restart_assay_callback_name,"restartAssay");

// Errors
}
}
