// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef MOUSE_JOYSTICK_CONSTANTS_H
#define MOUSE_JOYSTICK_CONSTANTS_H
#include <ConstantVariable.h>
#include <StepDirController.h>
#include <StepperController.h>
#include <StageController.h>

#include <EncoderInterfaceSimple.h>
#include <PowerSwitchController.h>


namespace mouse_joystick
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PROPERTY_COUNT_MAX=2};
enum{PARAMETER_COUNT_MAX=1};
enum{FUNCTION_COUNT_MAX=4};
enum{CALLBACK_COUNT_MAX=2};

enum{EVENT_COUNT_MAX=32};

enum{CHANNEL_COUNT=2};

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
extern ConstantString state_move_to_reach_string;
extern ConstantString state_moving_to_reach_string;
extern ConstantString state_wait_for_pull_string;
extern ConstantString state_waiting_for_pull_string;
extern ConstantString state_retract_string;
extern ConstantString state_retracting_string;
extern ConstantString state_move_to_base_stop_string;
extern ConstantString state_moving_to_base_stop_string;
extern ConstantString state_assay_finished_string;

extern const long seconds_per_minute;
extern const long milliseconds_per_second;
extern const long milliseconds_per_minute;

// Clients
extern const size_t encoder_interface_simple_address[1];

extern const size_t power_switch_controller_address[2];

// Interrupts

// Units
extern ConstantString mm_units;
extern ConstantString ms_units;
extern ConstantString seconds_units;
extern ConstantString minutes_units;

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

extern ConstantString reach_position_property_name;
extern const long reach_position_default[CHANNEL_COUNT];

extern ConstantString retract_position_property_name;
extern const long retract_position_default[CHANNEL_COUNT];

// Parameters

// Functions
extern ConstantString set_client_property_values_function_name;
extern ConstantString get_assay_status_function_name;
extern ConstantString move_joystick_to_base_position_function_name;
extern ConstantString move_joystick_to_reach_position_function_name;

// Callbacks
extern ConstantString start_trial_callback_name;
extern ConstantString abort_callback_name;

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
