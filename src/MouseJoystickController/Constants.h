// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef MOUSE_JOYSTICK_CONTROLLER_CONSTANTS_H
#define MOUSE_JOYSTICK_CONTROLLER_CONSTANTS_H
#include <ConstantVariable.h>
#include <Time.h>

#include <StepDirController.h>
#include <StepperController.h>
#include <StageController.h>

#include <EncoderInterfaceSimple.h>
#include <PowerSwitchController.h>
#include <AudioController.h>


namespace mouse_joystick_controller
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PROPERTY_COUNT_MAX=20};
enum{PARAMETER_COUNT_MAX=1};
enum{FUNCTION_COUNT_MAX=5};
enum{CALLBACK_COUNT_MAX=5};

enum{EVENT_COUNT_MAX=32};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

struct AssayStatus
{
  const ConstantString * state_ptr;
  size_t trial_index;
  size_t trial;
  size_t block;
  size_t set;
  StageController::PositionArray reach_position;
  long pull_torque;
  long pull_threshold;
  bool unread_trial_timing_data;
};

extern ConstantString trial_index_string;
extern ConstantString trial_string;
extern ConstantString block_string;
extern ConstantString set_string;
extern ConstantString reach_position_0_string;
extern ConstantString reach_position_1_string;
extern ConstantString pull_torque_string;
extern ConstantString pull_threshold_string;
extern ConstantString unread_trial_timing_data_string;

struct TrialTimingData
{
  time_t trial_start;
  time_t mouse_ready;
  time_t joystick_ready;
  time_t reward;
};

extern ConstantString trial_start_string;
extern ConstantString mouse_ready_string;
extern ConstantString joystick_ready_string;
extern ConstantString reward_string;

extern ConstantString state_string;
extern ConstantString state_assay_not_started_string;
extern ConstantString state_assay_started_string;
extern ConstantString state_homing_0_string;
extern ConstantString state_homing_1_string;
extern ConstantString state_move_to_homed_0_string;
extern ConstantString state_moving_to_homed_0_string;
extern ConstantString state_move_to_homed_1_string;
extern ConstantString state_moving_to_homed_1_string;
extern ConstantString state_move_to_base_start_string;
extern ConstantString state_moving_to_base_start_string;
extern ConstantString state_wait_to_start_trial_string;
extern ConstantString state_waiting_to_start_trial_string;
extern ConstantString state_wait_for_mouse_ready_string;
extern ConstantString state_waiting_for_mouse_ready_string;
extern ConstantString state_move_to_reach_string;
extern ConstantString state_moving_to_reach_string;
extern ConstantString state_wait_for_pull_string;
extern ConstantString state_waiting_for_pull_string;
extern ConstantString state_reward_string;
extern ConstantString state_retract_string;
extern ConstantString state_retracting_0_string;
extern ConstantString state_retracting_1_string;
extern ConstantString state_move_to_retracted_0_string;
extern ConstantString state_moving_to_retracted_0_string;
extern ConstantString state_move_to_retracted_1_string;
extern ConstantString state_moving_to_retracted_1_string;
extern ConstantString state_check_trial_termination_string;
extern ConstantString state_finish_trial_string;
extern ConstantString state_wait_until_trial_timing_data_read_string;
extern ConstantString state_waiting_until_trial_timing_data_read_string;
extern ConstantString state_move_to_base_stop_string;
extern ConstantString state_moving_to_base_stop_string;
extern ConstantString state_assay_finished_string;

extern const long seconds_per_minute;
extern const long milliseconds_per_second;
extern const long milliseconds_per_minute;

extern const long activate_lickport_delay;

extern const long pulse_duration;

extern const long not_touching_switch_position;

// Ready
extern const long joystick_ready_tone_delay;
extern const long joystick_ready_tone_count;

// Pull
extern const size_t pull_encoder_index;
extern const size_t pull_encoder_initial_value;
enum{ENCODER_POSITIONS_JSON_BUFFER_SIZE=256};
extern const size_t pull_channel;
extern const long pull_pwm_offset_min;
extern const long pull_pwm_offset_max;
enum{PULL_TORQUE_COUNT_MAX=4};
extern const long pull_torque_min;
extern const long pull_torque_max;
extern const long pull_torque_array_length_min;
extern const long pull_torque_array_length_max;
extern const unsigned long pull_push_poll_period;

// Reward
extern const long reward_tone_delay;
extern const long reward_tone_count;
enum{REWARD_LICKPORT_CHANNEL_COUNT=1};
extern const long reward_lickport_channels[REWARD_LICKPORT_CHANNEL_COUNT];
extern const long reward_lickport_count;

// Clients
extern const size_t encoder_interface_simple_address[1];

extern const size_t power_switch_controller_address[2];

extern const size_t audio_controller_address[4];

// Pins

// Units
extern ConstantString mm_units;
extern ConstantString ms_units;
extern ConstantString seconds_units;
extern ConstantString minutes_units;
extern ConstantString percent_units;

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern const long channel_count;

extern const long steps_per_position_units_element_default;

extern const long velocity_max_element_default;

extern const long velocity_min_element_default;

extern const long acceleration_max_element_default;

extern const long home_velocity_element_default;

extern const long invert_driver_direction_element_0_default;
extern const long invert_driver_direction_element_1_default;

extern const long run_current_element_0_default;
extern const long run_current_element_1_default;

extern const long hold_current_element_0_default;
extern const long hold_current_element_1_default;

extern const long hold_delay_element_default;

extern const long stage_channel_count_min;
extern const long stage_channel_count_max;
extern const long stage_channel_count_default;

extern const long stage_position_min_element_0_default;
extern const long stage_position_min_element_1_default;

extern const long stage_position_max_element_0_default;
extern const long stage_position_max_element_1_default;

extern ConstantString home_current_property_name;
extern const long home_current_element_0_default;
extern const long home_current_element_1_default;

extern ConstantString base_position_property_name;
extern const long base_position_element_0_default;
extern const long base_position_element_1_default;

extern ConstantString reach_position_0_property_name;
extern const long reach_position_0_default;

extern ConstantString reach_position_1_means_property_name;
enum{REACH_POSITION_1_COUNT_MAX=3};
extern const long reach_position_1_means_default[REACH_POSITION_1_COUNT_MAX];

extern ConstantString pull_threshold_property_name;
extern const long pull_threshold_min;
extern const long pull_threshold_max;
extern const long pull_threshold_default;

extern ConstantString push_threshold_property_name;
extern const long push_threshold_min;
extern const long push_threshold_max;
extern const long push_threshold_default;

extern ConstantString pull_torque_means_property_name;
extern const long pull_torque_means_default[PULL_TORQUE_COUNT_MAX];

extern ConstantString joystick_ready_tone_frequency_property_name;
extern const long joystick_ready_tone_frequency_default;

extern ConstantString joystick_ready_tone_duration_property_name;
extern const long joystick_ready_tone_duration_min;
extern const long joystick_ready_tone_duration_max;
extern const long joystick_ready_tone_duration_default;

extern ConstantString reward_tone_frequency_property_name;
extern const long reward_tone_frequency_default;

extern ConstantString reward_tone_duration_property_name;
extern const long reward_tone_duration_min;
extern const long reward_tone_duration_max;
extern const long reward_tone_duration_default;

extern ConstantString tone_volume_property_name;
extern const long tone_volume_min;
extern const long tone_volume_max;
extern const long tone_volume_default;

extern ConstantString reward_lickport_delay_property_name;
extern const long reward_lickport_delay_min;
extern const long reward_lickport_delay_max;
extern const long reward_lickport_delay_default;

extern ConstantString lickport_duration_property_name;
extern const long lickport_duration_min;
extern const long lickport_duration_max;
extern const long lickport_duration_default;

extern ConstantString trial_timeout_duration_property_name;
extern const long trial_timeout_duration_min;
extern const long trial_timeout_duration_max;
extern const long trial_timeout_duration_default;

extern ConstantString repeat_aborted_trial_property_name;
extern const bool repeat_aborted_trial_default;

extern ConstantString trial_count_property_name;
extern const long trial_count_min;
extern const long trial_count_max;
extern const long trial_count_default;

extern ConstantString set_count_property_name;
extern const long set_count_min;
extern const long set_count_max;
extern const long set_count_default;

extern ConstantString start_trial_duration_property_name;
extern const long start_trial_duration_min;
extern const long start_trial_duration_max;
extern const long start_trial_duration_default;

extern ConstantString wait_until_trial_timing_data_read_property_name;
extern const bool wait_until_trial_timing_data_read_default;

// Parameters
extern ConstantString count_parameter_name;
extern const long count_min;
extern const long count_max;

// Functions
extern ConstantString get_assay_status_function_name;
extern ConstantString move_joystick_to_base_position_function_name;
extern ConstantString move_joystick_to_reach_position_function_name;
extern ConstantString activate_lickport_function_name;
extern ConstantString get_trial_timing_data_function_name;

// Callbacks
extern ConstantString start_trial_callback_name;
extern ConstantString start_assay_callback_name;
extern ConstantString abort_trial_callback_name;
extern ConstantString abort_assay_callback_name;
extern ConstantString restart_assay_callback_name;

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
