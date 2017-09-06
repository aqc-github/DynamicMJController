// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef MOUSE_JOYSTICK_CONSTANTS_H
#define MOUSE_JOYSTICK_CONSTANTS_H
#include "ConstantVariable.h"
#include "StepDirController.h"
#include "StepperController.h"
#include "StageController.h"

#include "HBridgeController.h"
#include "OpticalSwitchInterface.h"
#include "AudioController.h"


namespace mouse_joystick
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PROPERTY_COUNT_MAX=15};
enum{PARAMETER_COUNT_MAX=1};
enum{FUNCTION_COUNT_MAX=6};
enum{CALLBACK_COUNT_MAX=2};

enum{EVENT_COUNT_MAX=32};

enum{DISPENSE_CHANNEL=0};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

struct AssayStatus
{
  const ConstantString * state_ptr;
};

extern ConstantString state_string;
extern ConstantString state_assay_not_started_string;
extern ConstantString state_assay_started_string;
extern ConstantString state_homing_string;
extern ConstantString state_move_to_base_start_string;
extern ConstantString state_moving_to_base_start_string;
extern ConstantString state_move_to_deliver_string;
extern ConstantString state_moving_to_deliver_string;
extern ConstantString state_move_to_clean_string;
extern ConstantString state_moving_to_clean_string;
extern ConstantString state_wait_at_clean_string;
extern ConstantString state_waiting_at_clean_string;
extern ConstantString state_buzz_string;
extern ConstantString state_buzzing_string;
extern ConstantString state_wait_to_play_tone_string;
extern ConstantString state_waiting_to_play_tone_string;
extern ConstantString state_play_tone_string;
extern ConstantString state_playing_tone_string;
extern ConstantString state_move_to_dispense_string;
extern ConstantString state_moving_to_dispense_string;
extern ConstantString state_wait_to_return_string;
extern ConstantString state_waiting_to_return_string;
extern ConstantString state_move_to_base_stop_string;
extern ConstantString state_moving_to_base_stop_string;
extern ConstantString state_assay_finished_string;

extern const long seconds_per_minute;
extern const long milliseconds_per_second;
extern const long milliseconds_per_minute;

// Clients
extern const size_t optical_switch_interface_address[1];

extern const size_t h_bridge_controller_address[2];

extern const size_t audio_controller_address[3];

enum{BUZZ_CHANNEL_COUNT=1};
extern const size_t buzz_channels[BUZZ_CHANNEL_COUNT];

// Interrupts

// Units
extern ConstantString mm_units;
extern ConstantString ms_units;
extern ConstantString seconds_units;
extern ConstantString minutes_units;

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern const long steps_per_position_units_default[step_dir_controller::constants::CHANNEL_COUNT];

extern const long velocity_max_default[step_dir_controller::constants::CHANNEL_COUNT];

extern const long velocity_min_default[step_dir_controller::constants::CHANNEL_COUNT];

extern const long acceleration_max_default[step_dir_controller::constants::CHANNEL_COUNT];

extern const long home_velocity_default[step_dir_controller::constants::CHANNEL_COUNT];

extern const long run_current_default[stepper_controller::constants::DRIVER_COUNT];
extern const long run_current_element_default;

extern const long hold_current_default[stepper_controller::constants::DRIVER_COUNT];
extern const long hold_current_element_default;

extern const long hold_delay_default[stepper_controller::constants::DRIVER_COUNT];
extern const long hold_delay_element_default;

extern const long stage_channel_count_min;
extern const long stage_channel_count_max;
extern const long stage_channel_count_default;

extern const long stage_position_min_default[step_dir_controller::constants::CHANNEL_COUNT];

extern const long stage_position_max_default[step_dir_controller::constants::CHANNEL_COUNT];

extern const bool inverted[optical_switch_interface::constants::OUTPUT_COUNT];

extern ConstantString base_position_property_name;
extern const long base_position_default[step_dir_controller::constants::CHANNEL_COUNT];

extern ConstantString deliver_position_property_name;
extern const long deliver_position_default[step_dir_controller::constants::CHANNEL_COUNT];

extern ConstantString dispense_channel_position_property_name;
extern const long dispense_channel_position_default;

extern ConstantString clean_position_property_name;
extern const long clean_position_default[step_dir_controller::constants::CHANNEL_COUNT];

extern ConstantString clean_duration_property_name;
extern const long clean_duration_min;
extern const long clean_duration_max;
extern const long clean_duration_default;

extern ConstantString buzz_period_property_name;
extern const long buzz_period_min;
extern const long buzz_period_max;
extern const long buzz_period_default;

extern ConstantString buzz_on_duration_property_name;
extern const long buzz_on_duration_min;
extern const long buzz_on_duration_max;
extern const long buzz_on_duration_default;

extern ConstantString buzz_count_property_name;
extern const long buzz_count_min;
extern const long buzz_count_max;
extern const long buzz_count_default;

extern ConstantString tone_delay_min_property_name;
extern const long tone_delay_min;
extern const long tone_delay_max;
extern const long tone_delay_min_default;

extern ConstantString tone_delay_max_property_name;
extern const long tone_delay_max_default;

extern ConstantString tone_frequency_property_name;
extern const long tone_frequency_min;
extern const long tone_frequency_max;
extern const long tone_frequency_default;

extern ConstantString tone_duration_property_name;
extern const long tone_duration_min;
extern const long tone_duration_max;
extern const long tone_duration_default;

extern ConstantString tone_volume_property_name;
extern const long tone_volume_default;

extern ConstantString return_delay_min_property_name;
extern const double return_delay_min;
extern const double return_delay_max;
extern const double return_delay_min_default;

extern ConstantString return_delay_max_property_name;
extern const double return_delay_max_default;

// Parameters

// Functions
extern ConstantString set_client_property_values_function_name;
extern ConstantString get_assay_status_function_name;
extern ConstantString move_stage_to_base_position_function_name;
extern ConstantString move_stage_to_deliver_position_function_name;
extern ConstantString move_stage_to_dispense_position_function_name;
extern ConstantString move_stage_to_clean_position_function_name;

// Callbacks
extern ConstantString deliver_callback_name;
extern ConstantString abort_callback_name;

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
