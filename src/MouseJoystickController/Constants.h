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
enum{PROPERTY_COUNT_MAX=16};
enum{PARAMETER_COUNT_MAX=1};
enum{FUNCTION_COUNT_MAX=4};
enum{CALLBACK_COUNT_MAX=4};

enum{EVENT_COUNT_MAX=32};

enum{CHANNEL_COUNT=2};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

struct AssayStatus
{
  const ConstantString * state_ptr;
  StageController::PositionArray reach_position;
  long pull_torque;
  size_t trial;
  size_t block;
  size_t set;
};

extern ConstantString state_string;
extern ConstantString state_assay_not_started_string;
extern ConstantString state_assay_started_string;
extern ConstantString state_homing_string;
extern ConstantString state_move_to_base_start_string;
extern ConstantString state_moving_to_base_start_string;
extern ConstantString state_wait_to_start_trial_string;
extern ConstantString state_waiting_to_start_trial_string;
extern ConstantString state_move_to_reach_string;
extern ConstantString state_moving_to_reach_string;
extern ConstantString state_wait_for_pull_string;
extern ConstantString state_waiting_for_pull_string;
extern ConstantString state_reward_string;
extern ConstantString state_retract_string;
extern ConstantString state_retracting_string;
extern ConstantString state_finish_trial_string;
extern ConstantString state_move_to_base_stop_string;
extern ConstantString state_moving_to_base_stop_string;
extern ConstantString state_assay_finished_string;

extern ConstantString reach_position_string;
extern ConstantString pull_torque_string;
extern ConstantString trial_string;
extern ConstantString block_string;
extern ConstantString set_string;

extern const long seconds_per_minute;
extern const long milliseconds_per_second;
extern const long milliseconds_per_minute;

// Ready
extern const long ready_tone_delay;
extern const long ready_tone_count;

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

// Reward
extern const long reward_tone_delay;
extern const long reward_tone_count;
enum{REWARD_SOLENOID_CHANNEL_COUNT=1};
extern const long reward_solenoid_channels[REWARD_SOLENOID_CHANNEL_COUNT];
extern const long reward_solenoid_count;

// Clients
extern const size_t encoder_interface_simple_address[1];

extern const size_t power_switch_controller_address[2];

extern const size_t audio_controller_address[4];

// Interrupts

// Units
extern ConstantString mm_units;
extern ConstantString ms_units;
extern ConstantString seconds_units;
extern ConstantString minutes_units;
extern ConstantString percent_units;

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern const long channel_count;

extern const long steps_per_position_units_default[CHANNEL_COUNT];

extern const long velocity_max_default[CHANNEL_COUNT];

extern const long velocity_min_default[CHANNEL_COUNT];

extern const long acceleration_max_default[CHANNEL_COUNT];

extern const long home_velocity_default[CHANNEL_COUNT];

extern const bool invert_driver_direction_default[CHANNEL_COUNT];

extern const long run_current_default[CHANNEL_COUNT];

extern const long hold_current_default[CHANNEL_COUNT];

extern const long hold_delay_default[CHANNEL_COUNT];
extern const long hold_delay_element_default;

extern const long stage_channel_count_min;
extern const long stage_channel_count_max;
extern const long stage_channel_count_default;

extern const long stage_position_min_default[CHANNEL_COUNT];

extern const long stage_position_max_default[CHANNEL_COUNT];

extern ConstantString base_position_property_name;
extern const long base_position_default[CHANNEL_COUNT];

extern ConstantString reach_position_0_property_name;
extern const long reach_position_0_default;

extern ConstantString reach_position_1_means_property_name;
enum{REACH_POSITION_1_COUNT_MAX=2};
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

extern ConstantString ready_tone_frequency_property_name;
extern const long ready_tone_frequency_default;

extern ConstantString ready_tone_duration_property_name;
extern const long ready_tone_duration_min;
extern const long ready_tone_duration_max;
extern const long ready_tone_duration_default;

extern ConstantString reward_tone_frequency_property_name;
extern const long reward_tone_frequency_default;

extern ConstantString reward_tone_duration_property_name;
extern const long reward_tone_duration_min;
extern const long reward_tone_duration_max;
extern const long reward_tone_duration_default;

extern ConstantString reward_solenoid_delay_property_name;
extern const long reward_solenoid_delay_min;
extern const long reward_solenoid_delay_max;
extern const long reward_solenoid_delay_default;

extern ConstantString reward_solenoid_duration_property_name;
extern const long reward_solenoid_duration_min;
extern const long reward_solenoid_duration_max;
extern const long reward_solenoid_duration_default;

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

// Parameters

// Functions
extern ConstantString set_client_property_values_function_name;
extern ConstantString get_assay_status_function_name;
extern ConstantString move_joystick_to_base_position_function_name;
extern ConstantString move_joystick_to_reach_position_function_name;

// Callbacks
extern ConstantString start_trial_callback_name;
extern ConstantString start_assay_callback_name;
extern ConstantString abort_trial_callback_name;
extern ConstantString abort_assay_callback_name;

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
