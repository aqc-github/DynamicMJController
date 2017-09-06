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
   .version_major=2,
   .version_minor=0,
   .version_patch=0,
  };

CONSTANT_STRING(state_string,"state");
CONSTANT_STRING(state_assay_not_started_string,"ASSAY_NOT_STARTED");
CONSTANT_STRING(state_assay_started_string,"ASSAY_STARTED");
CONSTANT_STRING(state_homing_string,"HOMING");
CONSTANT_STRING(state_move_to_base_start_string,"MOVE_TO_BASE_START");
CONSTANT_STRING(state_moving_to_base_start_string,"MOVING_TO_BASE_START");
CONSTANT_STRING(state_move_to_deliver_string,"MOVE_TO_DELIVER");
CONSTANT_STRING(state_moving_to_deliver_string,"MOVING_TO_DELIVER");
CONSTANT_STRING(state_move_to_clean_string,"MOVE_TO_CLEAN");
CONSTANT_STRING(state_moving_to_clean_string,"MOVING_TO_CLEAN");
CONSTANT_STRING(state_wait_at_clean_string,"WAIT_AT_CLEAN");
CONSTANT_STRING(state_waiting_at_clean_string,"WAITING_AT_CLEAN");
CONSTANT_STRING(state_buzz_string,"BUZZ");
CONSTANT_STRING(state_buzzing_string,"BUZZING");
CONSTANT_STRING(state_wait_to_play_tone_string,"WAIT_TO_PLAY_TONE");
CONSTANT_STRING(state_waiting_to_play_tone_string,"WAITING_TO_PLAY_TONE");
CONSTANT_STRING(state_play_tone_string,"PLAY_TONE");
CONSTANT_STRING(state_playing_tone_string,"PLAYING_TONE");
CONSTANT_STRING(state_move_to_dispense_string,"MOVE_TO_DISPENSE");
CONSTANT_STRING(state_moving_to_dispense_string,"MOVING_TO_DISPENSE");
CONSTANT_STRING(state_wait_to_return_string,"WAIT_TO_RETURN");
CONSTANT_STRING(state_waiting_to_return_string,"WAITING_TO_RETURN");
CONSTANT_STRING(state_move_to_base_stop_string,"MOVE_TO_BASE_STOP");
CONSTANT_STRING(state_moving_to_base_stop_string,"MOVING_TO_BASE_STOP");
CONSTANT_STRING(state_assay_finished_string,"ASSAY_FINISHED");

const long seconds_per_minute = 60;
const long milliseconds_per_second = 1000;
const long milliseconds_per_minute = milliseconds_per_second*seconds_per_minute;

// Clients
const size_t optical_switch_interface_address[1] =
  {
   3,
  };

const size_t h_bridge_controller_address[2] =
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

const size_t buzz_channels[BUZZ_CHANNEL_COUNT] =
  {
   0,
  };

// Interrupts

// Units
CONSTANT_STRING(mm_units,"mm");
CONSTANT_STRING(ms_units,"ms");
CONSTANT_STRING(seconds_units,"s");
CONSTANT_STRING(minutes_units,"min");
CONSTANT_STRING(hz_units,"Hz");

// Properties
const long run_current_element_default = 20;

const long hold_current_element_default = 10;

const long hold_delay_element_default = 50;

CONSTANT_STRING(base_position_property_name,"basePosition");

CONSTANT_STRING(deliver_position_property_name,"deliverPosition");

CONSTANT_STRING(dispense_channel_position_property_name,"dispenseChannelPosition");
const long dispense_channel_position_default = -5;

CONSTANT_STRING(clean_position_property_name,"cleanPosition");

CONSTANT_STRING(clean_duration_property_name,"cleanDuration");
const long clean_duration_min = 1;
const long clean_duration_max = 10;
const long clean_duration_default = 3;

CONSTANT_STRING(buzz_period_property_name,"buzzPeriod");
const long buzz_period_min = 100;
const long buzz_period_max = 1000;
const long buzz_period_default = 500;

CONSTANT_STRING(buzz_on_duration_property_name,"buzzOnDuration");
const long buzz_on_duration_min = 5;
const long buzz_on_duration_max = 20;
const long buzz_on_duration_default = 10;

CONSTANT_STRING(buzz_count_property_name,"buzzCount");
const long buzz_count_min = 1;
const long buzz_count_max = 5;
const long buzz_count_default = 3;

CONSTANT_STRING(tone_delay_min_property_name,"toneDelayMin");
const long tone_delay_min = 0;
const long tone_delay_max = 60;
const long tone_delay_min_default = 2;

CONSTANT_STRING(tone_delay_max_property_name,"toneDelayMax");
const long tone_delay_max_default = 10;

CONSTANT_STRING(tone_frequency_property_name,"toneFrequency");
const long tone_frequency_min = 1000;
const long tone_frequency_max = 15000;
const long tone_frequency_default = 5000;

CONSTANT_STRING(tone_duration_property_name,"toneDuration");
const long tone_duration_min = 1;
const long tone_duration_max = 5;
const long tone_duration_default = 1;

CONSTANT_STRING(tone_volume_property_name,"toneVolume");
const long tone_volume_default = 25;

CONSTANT_STRING(return_delay_min_property_name,"returnDelayMin");
const double return_delay_min = 0.1;
const double return_delay_max = 15.0;
const double return_delay_min_default = 0.1;

CONSTANT_STRING(return_delay_max_property_name,"returnDelayMax");
const double return_delay_max_default = 0.3;

// Parameters

// Functions
CONSTANT_STRING(set_client_property_values_function_name,"setClientPropertyValues");
CONSTANT_STRING(get_assay_status_function_name,"getAssayStatus");
CONSTANT_STRING(move_stage_to_base_position_function_name,"moveStageToBasePosition");
CONSTANT_STRING(move_stage_to_deliver_position_function_name,"moveStageToDeliverPosition");
CONSTANT_STRING(move_stage_to_dispense_position_function_name,"moveStageToDispensePosition");
CONSTANT_STRING(move_stage_to_clean_position_function_name,"moveStageToCleanPosition");

// Callbacks
CONSTANT_STRING(deliver_callback_name,"deliver");
CONSTANT_STRING(abort_callback_name,"abort");

// Errors
}
}
