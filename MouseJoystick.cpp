// ----------------------------------------------------------------------------
// MouseJoystick.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "MouseJoystick.h"


using namespace mouse_joystick;

MouseJoystick::MouseJoystick()
{
}

void MouseJoystick::setup()
{
  // Parent Setup
  StageController::setup();

  // Event Controller Setup
  // event_controller_.setup();

  // Clients Setup
  // encoder_interface_simple_ptr_ = &(createClientAtAddress(constants::encoder_interface_simple_address));

  // Pin Setup

  // Assay Status Setup
  // assay_status_.state_ptr = &constants::state_assay_not_started_string;

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);

  // Add Hardware

  // Interrupts

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
                              properties_,
                              parameters_,
                              functions_,
                              callbacks_);

  // Properties
  modular_server::Property & steps_per_position_units_property = modular_server_.property(step_dir_controller::constants::steps_per_position_units_property_name);
  steps_per_position_units_property.setRange(constants::steps_per_position_units_element_min,constants::steps_per_position_units_element_max);
  steps_per_position_units_property.setDefaultValue(constants::steps_per_position_units_default);

  modular_server::Property & velocity_max_property = modular_server_.property(step_dir_controller::constants::velocity_max_property_name);
  velocity_max_property.setDefaultValue(constants::velocity_max_default);

  modular_server::Property & velocity_min_property = modular_server_.property(step_dir_controller::constants::velocity_min_property_name);
  velocity_min_property.setDefaultValue(constants::velocity_min_default);

  modular_server::Property & acceleration_max_property = modular_server_.property(step_dir_controller::constants::acceleration_max_property_name);
  acceleration_max_property.setDefaultValue(constants::acceleration_max_default);

  modular_server::Property & home_velocity_property = modular_server_.property(step_dir_controller::constants::home_velocity_property_name);
  home_velocity_property.setDefaultValue(constants::home_velocity_default);

  modular_server::Property & invert_driver_direction_property = modular_server_.property(stepper_controller::constants::invert_driver_direction_property_name);
  invert_driver_direction_property.setDefaultValue(constants::invert_driver_direction_default);

  modular_server::Property & run_current_property = modular_server_.property(stepper_controller::constants::run_current_property_name);
  run_current_property.setDefaultValue(constants::run_current_default);

  modular_server::Property & hold_current_property = modular_server_.property(stepper_controller::constants::hold_current_property_name);
  hold_current_property.setDefaultValue(constants::hold_current_default);

  modular_server::Property & hold_delay_property = modular_server_.property(stepper_controller::constants::hold_delay_property_name);
  hold_delay_property.setDefaultValue(constants::hold_delay_default);

  modular_server::Property & stage_channel_count_property = modular_server_.property(stage_controller::constants::stage_channel_count_property_name);
  stage_channel_count_property.setDefaultValue(constants::stage_channel_count_default);
  stage_channel_count_property.setRange(constants::stage_channel_count_min,constants::stage_channel_count_max);
  stage_channel_count_property.setArrayLengthRange(constants::stage_channel_count_min,constants::stage_channel_count_max);

  modular_server::Property & stage_positions_min_property = modular_server_.property(stage_controller::constants::stage_positions_min_property_name);
  stage_positions_min_property.setDefaultValue(constants::stage_positions_min_default);

  modular_server::Property & stage_positions_max_property = modular_server_.property(stage_controller::constants::stage_positions_max_property_name);
  stage_positions_max_property.setDefaultValue(constants::stage_positions_max_default);

  // modular_server_.createProperty(constants::base_positions_property_name,constants::base_positions_default);

  // modular_server_.createProperty(constants::deliver_positions_property_name,constants::deliver_positions_default);

  // modular_server_.createProperty(constants::dispense_position_property_name,constants::dispense_position_default);

  // modular_server::Property & buzz_period_property = modular_server_.createProperty(constants::buzz_period_property_name,constants::buzz_period_default);
  // buzz_period_property.setUnits(audio_controller::constants::ms_units);
  // buzz_period_property.setRange(constants::buzz_period_min,constants::buzz_period_max);

  // modular_server::Property & buzz_on_duration_property = modular_server_.createProperty(constants::buzz_on_duration_property_name,constants::buzz_on_duration_default);
  // buzz_on_duration_property.setUnits(audio_controller::constants::ms_units);
  // buzz_on_duration_property.setRange(constants::buzz_on_duration_min,constants::buzz_on_duration_max);

  // modular_server::Property & buzz_count_property = modular_server_.createProperty(constants::buzz_count_property_name,constants::buzz_count_default);
  // buzz_count_property.setRange(constants::buzz_count_min,constants::buzz_count_max);

  // modular_server::Property & tone_frequency_property = modular_server_.createProperty(constants::tone_frequency_property_name,constants::tone_frequency_default);
  // tone_frequency_property.setUnits(audio_controller::constants::hz_units);
  // tone_frequency_property.setRange(constants::tone_frequency_min,constants::tone_frequency_max);

  // modular_server::Property & tone_duration_property = modular_server_.createProperty(constants::tone_duration_property_name,constants::tone_duration_default);
  // tone_duration_property.setUnits(constants::seconds_units);
  // tone_duration_property.setRange(constants::tone_duration_min,constants::tone_duration_max);

  // modular_server::Property & tone_volume_property = modular_server_.createProperty(constants::tone_volume_property_name,constants::tone_volume_default);
  // tone_volume_property.setRange(audio_controller::constants::volume_min,audio_controller::constants::volume_max);

  // modular_server::Property & tone_delay_min_property = modular_server_.createProperty(constants::tone_delay_min_property_name,constants::tone_delay_min_default);
  // tone_delay_min_property.setUnits(constants::seconds_units);
  // tone_delay_min_property.setRange(constants::tone_delay_min,constants::tone_delay_max);

  // modular_server::Property & tone_delay_max_property = modular_server_.createProperty(constants::tone_delay_max_property_name,constants::tone_delay_max_default);
  // tone_delay_max_property.setUnits(constants::seconds_units);
  // tone_delay_max_property.setRange(constants::tone_delay_min,constants::tone_delay_max);

  // modular_server::Property & return_delay_property = modular_server_.createProperty(constants::return_delay_property_name,constants::return_delay_default);
  // return_delay_property.setUnits(constants::minutes_units);
  // return_delay_property.setRange(constants::return_delay_min,constants::return_delay_max);

  // Parameters
  // modular_server::Parameter & stage_positions_parameter = modular_server_.parameter(stage_controller::constants::stage_positions_parameter_name);
  // stage_positions_parameter.setUnits(constants::mm_units);

  // Functions
  // modular_server::Function & set_client_property_values_function = modular_server_.createFunction(constants::set_client_property_values_function_name);
  // set_client_property_values_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&MouseJoystick::setClientPropertyValuesHandler));

  // modular_server::Function & get_assay_status_function = modular_server_.createFunction(constants::get_assay_status_function_name);
  // get_assay_status_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&MouseJoystick::getAssayStatusHandler));
  // get_assay_status_function.setResultTypeObject();

  // Callbacks
//   modular_server::Callback & deliver_callback = modular_server_.createCallback(constants::deliver_callback_name);
//   deliver_callback.attachFunctor(makeFunctor((Functor1<modular_server::Interrupt *> *)0,*this,&MouseJoystick::deliverHandler));
//   deliver_callback.attachTo(modular_device_base::constants::bnc_b_interrupt_name,modular_server::interrupt::mode_falling);
// #if defined(__MK64FX512__)
//   deliver_callback.attachTo(modular_device_base::constants::btn_b_interrupt_name,modular_server::interrupt::mode_falling);
// #endif

//   modular_server::Callback & abort_callback = modular_server_.createCallback(constants::abort_callback_name);
//   abort_callback.attachFunctor(makeFunctor((Functor1<modular_server::Interrupt *> *)0,*this,&MouseJoystick::abortHandler));
//   abort_callback.attachTo(modular_device_base::constants::bnc_a_interrupt_name,modular_server::interrupt::mode_falling);
// #if !defined(__AVR_ATmega2560__)
//   abort_callback.attachTo(modular_device_base::constants::btn_a_interrupt_name,modular_server::interrupt::mode_falling);
// #endif

}

void MouseJoystick::update()
{
  // Parent Update
  StageController::update();

  // const ConstantString * state_ptr = assay_status_.state_ptr;

  // if (state_ptr == &constants::state_assay_started_string)
  // {
  //   if (stageHomed())
  //   {
  //     assay_status_.state_ptr = &constants::state_move_to_base_start_string;
  //   }
  //   else
  //   {
  //     assay_status_.state_ptr = &constants::state_homing_string;
  //     homeStage();
  //   }
  // }
  // else if (state_ptr == &constants::state_homing_string)
  // {
  //   if (stageHomed())
  //   {
  //     assay_status_.state_ptr = &constants::state_move_to_base_start_string;
  //   }
  // }
  // else if (state_ptr == &constants::state_move_to_base_start_string)
  // {
  //   assay_status_.state_ptr = &constants::state_moving_to_base_start_string;
  //   moveStageSoftlyToBase();
  // }
  // else if (state_ptr == &constants::state_moving_to_base_start_string)
  // {
  //   if (stageAtTargetPositions())
  //   {
  //     assay_status_.state_ptr = &constants::state_move_to_deliver_string;
  //   }
  // }
  // else if (state_ptr == &constants::state_move_to_deliver_string)
  // {
  //   assay_status_.state_ptr = &constants::state_moving_to_deliver_string;
  //   moveStageSoftlyToDeliver();
  // }
  // else if (state_ptr == &constants::state_moving_to_deliver_string)
  // {
  //   if (stageAtTargetPositions())
  //   {
  //     assay_status_.state_ptr = &constants::state_buzz_string;
  //   }
  // }
  // else if (state_ptr == &constants::state_buzz_string)
  // {
  //   assay_status_.state_ptr = &constants::state_buzzing_string;
  //   buzz();
  // }
  // else if (state_ptr == &constants::state_buzzing_string)
  // {
  // }
  // else if (state_ptr == &constants::state_wait_to_play_tone_string)
  // {
  //   assay_status_.state_ptr = &constants::state_waiting_to_play_tone_string;
  //   waitToPlayTone();
  // }
  // else if (state_ptr == &constants::state_waiting_to_play_tone_string)
  // {
  // }
  // else if (state_ptr == &constants::state_play_tone_string)
  // {
  //   assay_status_.state_ptr = &constants::state_playing_tone_string;
  //   playTone();
  // }
  // else if (state_ptr == &constants::state_playing_tone_string)
  // {
  // }
  // else if (state_ptr == &constants::state_move_to_dispense_string)
  // {
  //   assay_status_.state_ptr = &constants::state_moving_to_dispense_string;
  //   moveStageSoftlyToDispense();
  // }
  // else if (state_ptr == &constants::state_moving_to_dispense_string)
  // {
  //   if (stageAtTargetPositions())
  //   {
  //     assay_status_.state_ptr = &constants::state_wait_to_return_string;
  //   }
  // }
  // else if (state_ptr == &constants::state_wait_to_return_string)
  // {
  //   assay_status_.state_ptr = &constants::state_waiting_to_return_string;
  //   waitToReturn();
  // }
  // else if (state_ptr == &constants::state_waiting_to_return_string)
  // {
  // }
  // else if (state_ptr == &constants::state_move_to_base_stop_string)
  // {
  //   assay_status_.state_ptr = &constants::state_moving_to_base_stop_string;
  //   moveStageSoftlyToBase();
  // }
  // else if (state_ptr == &constants::state_moving_to_base_stop_string)
  // {
  //   if (stageAtTargetPositions())
  //   {
  //     assay_status_.state_ptr = &constants::state_assay_finished_string;
  //   }
  // }
}

// constants::AssayStatus MouseJoystick::getAssayStatus()
// {
//   return assay_status_;
// }

// StageController::PositionsArray MouseJoystick::getBasePositions()
// {
//   double base_positions[step_dir_controller::constants::CHANNEL_COUNT];
//   modular_server_.property(constants::base_positions_property_name).getValue(base_positions);

//   StageController::PositionsArray base_positions_array(base_positions);
//   return base_positions_array;
// }

// StageController::PositionsArray MouseJoystick::getDeliverPositions()
// {
//   double deliver_positions[step_dir_controller::constants::CHANNEL_COUNT];
//   modular_server_.property(constants::deliver_positions_property_name).getValue(deliver_positions);

//   StageController::PositionsArray deliver_positions_array(deliver_positions);
//   return deliver_positions_array;
// }

// StageController::PositionsArray MouseJoystick::getDispensePositions()
// {
//   double deliver_positions[step_dir_controller::constants::CHANNEL_COUNT];
//   modular_server_.property(constants::deliver_positions_property_name).getValue(deliver_positions);

//   StageController::PositionsArray dispense_positions_array(deliver_positions);

//   double dispense_position;
//   modular_server_.property(constants::dispense_position_property_name).getValue(dispense_position);
//   dispense_positions_array[constants::DISPENSE_CHANNEL] = dispense_position;

//   return dispense_positions_array;
// }

// long MouseJoystick::getBuzzPeriod()
// {
//   long buzz_period;
//   modular_server_.property(constants::buzz_period_property_name).getValue(buzz_period);

//   return buzz_period;
// }

// long MouseJoystick::getBuzzOnDuration()
// {
//   long buzz_on_duration;
//   modular_server_.property(constants::buzz_on_duration_property_name).getValue(buzz_on_duration);

//   return buzz_on_duration;
// }

// long MouseJoystick::getBuzzCount()
// {
//   long buzz_count;
//   modular_server_.property(constants::buzz_count_property_name).getValue(buzz_count);

//   return buzz_count;
// }

// long MouseJoystick::getToneDelay()
// {
//   long tone_delay_min;
//   modular_server_.property(constants::tone_delay_min_property_name).getValue(tone_delay_min);

//   long tone_delay_max;
//   modular_server_.property(constants::tone_delay_max_property_name).getValue(tone_delay_max);

//   long tone_delay = random(tone_delay_min,tone_delay_max);
//   tone_delay = tone_delay*constants::milliseconds_per_second;
//   return tone_delay;
// }

// long MouseJoystick::getToneFrequency()
// {
//   long tone_frequency;
//   modular_server_.property(constants::tone_frequency_property_name).getValue(tone_frequency);

//   return tone_frequency;
// }

// long MouseJoystick::getToneDuration()
// {
//   long tone_duration;
//   modular_server_.property(constants::tone_duration_property_name).getValue(tone_duration);

//   return tone_duration*constants::milliseconds_per_second;
// }

// long MouseJoystick::getToneVolume()
// {
//   long tone_volume;
//   modular_server_.property(constants::tone_volume_property_name).getValue(tone_volume);

//   return tone_volume;
// }

// double MouseJoystick::getReturnDelay()
// {
//   double return_delay;
//   modular_server_.property(constants::return_delay_property_name).getValue(return_delay);

//   return return_delay*constants::milliseconds_per_minute;
// }

// void MouseJoystick::moveStageSoftlyToBase()
// {
//   StageController::PositionsArray base_positions = getBasePositions();
//   moveStageSoftlyTo(base_positions);
// }

// void MouseJoystick::moveStageSoftlyToDeliver()
// {
//   StageController::PositionsArray deliver_positions = getDeliverPositions();
//   moveStageSoftlyTo(deliver_positions);
// }

// void MouseJoystick::moveStageSoftlyToDispense()
// {
//   StageController::PositionsArray dispense_positions = getDispensePositions();
//   moveStageSoftlyTo(dispense_positions);
// }

// void MouseJoystick::buzz()
// {
//   long buzz_period = getBuzzPeriod();
//   long buzz_on_duration = getBuzzOnDuration();
//   long buzz_count = getBuzzCount();

//   Array<size_t,constants::BUZZ_CHANNEL_COUNT> buzz_channels_array(constants::buzz_channels);

//   h_bridge_controller_ptr_->call(h_bridge_controller::constants::add_pwm_function_name,
//                                  buzz_channels_array,
//                                  h_bridge_controller::constants::polarity_positive,
//                                  0,
//                                  buzz_period,
//                                  buzz_on_duration,
//                                  buzz_count);
//   EventId event_id = event_controller_.addEventUsingDelay(makeFunctor((Functor1<int> *)0,*this,&MouseJoystick::waitToPlayToneHandler),
//                                                           buzz_period*buzz_count);
//   event_controller_.enable(event_id);
// }

// void MouseJoystick::setWaitToPlayToneState()
// {
//   assay_status_.state_ptr = &constants::state_wait_to_play_tone_string;
// }

// void MouseJoystick::waitToPlayTone()
// {
//   long tone_delay = getToneDelay();
//   EventId event_id = event_controller_.addEventUsingDelay(makeFunctor((Functor1<int> *)0,*this,&MouseJoystick::playToneHandler),
//                                                           tone_delay);
//   event_controller_.enable(event_id);
// }

// void MouseJoystick::setPlayToneState()
// {
//   assay_status_.state_ptr = &constants::state_play_tone_string;
// }

// void MouseJoystick::playTone()
// {
//   long tone_frequency = getToneFrequency();
//   long tone_duration = getToneDuration();
//   long tone_volume = getToneVolume();

//   audio_controller_ptr_->call(audio_controller::constants::add_tone_pwm_at_function_name,
//                               tone_frequency,
//                               audio_controller::constants::speaker_all,
//                               tone_volume,
//                               0,
//                               tone_duration,
//                               tone_duration,
//                               1);
//   EventId event_id = event_controller_.addEventUsingDelay(makeFunctor((Functor1<int> *)0,*this,&MouseJoystick::moveToDispenseHandler),
//                                                           tone_duration);
//   event_controller_.enable(event_id);
// }

// void MouseJoystick::setMoveToDispenseState()
// {
//   assay_status_.state_ptr = &constants::state_move_to_dispense_string;
// }

// void MouseJoystick::waitToReturn()
// {
//   double return_delay = getReturnDelay();
//   EventId event_id = event_controller_.addEventUsingDelay(makeFunctor((Functor1<int> *)0,*this,&MouseJoystick::moveToBaseHandler),
//                                                           return_delay);
//   event_controller_.enable(event_id);
// }

// void MouseJoystick::setMoveToBaseStopState()
// {
//   assay_status_.state_ptr = &constants::state_move_to_base_stop_string;
// }

// void MouseJoystick::deliver()
// {
//   if ((assay_status_.state_ptr == &constants::state_assay_not_started_string) ||
//       (assay_status_.state_ptr == &constants::state_assay_finished_string))
//   {
//     assay_status_.state_ptr = &constants::state_assay_started_string;
//   }
// }

// void MouseJoystick::abort()
// {
//   stopAll();
//   event_controller_.removeAllEvents();
//   h_bridge_controller_ptr_->call(h_bridge_controller::constants::stop_all_pwm_function_name);
//   audio_controller_ptr_->call(audio_controller::constants::stop_all_pwm_function_name);

//   if (stageHomed())
//   {
//     setMoveToBaseStopState();
//   }
//   else
//   {
//     assay_status_.state_ptr = &constants::state_assay_not_started_string;
//   }
// }

// Handlers must be non-blocking (avoid 'delay')
//
// modular_server_.parameter(parameter_name).getValue(value) value type must be either:
// fixed-point number (int, long, etc.)
// floating-point number (float, double)
// bool
// const char *
// ArduinoJson::JsonArray *
// ArduinoJson::JsonObject *
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_server_.property(property_name).getValue(value) value type must match the property default type
// modular_server_.property(property_name).setValue(value) value type must match the property default type
// modular_server_.property(property_name).getElementValue(element_index,value) value type must match the property array element default type
// modular_server_.property(property_name).setElementValue(element_index,value) value type must match the property array element default type

void MouseJoystick::setClientPropertyValuesHandler()
{
  // h_bridge_controller_ptr_->call(modular_server::constants::set_properties_to_defaults_function_name);

  // optical_switch_interface_ptr_->call(modular_server::constants::set_properties_to_defaults_function_name);
  // Array<bool,optical_switch_interface::constants::OUTPUT_COUNT> inverted(constants::inverted);
  // optical_switch_interface_ptr_->call(optical_switch_interface::constants::inverted_property_name,
  //                                     modular_server::property::set_value_function_name,
  //                                     inverted);

  // audio_controller_ptr_->call(modular_server::constants::set_properties_to_defaults_function_name);
}

// void MouseJoystick::getAssayStatusHandler()
// {
//   constants::AssayStatus assay_status = getAssayStatus();

//   modular_server_.response().writeResultKey();

//   modular_server_.response().beginObject();

//   modular_server_.response().write(constants::state_string,assay_status.state_ptr);

//   modular_server_.response().endObject();

// }

// void MouseJoystick::playToneHandler(int arg)
// {
//   setPlayToneState();
// }

// void MouseJoystick::moveToDispenseHandler(int arg)
// {
//   setMoveToDispenseState();
// }

// void MouseJoystick::waitToPlayToneHandler(int arg)
// {
//   setWaitToPlayToneState();
// }

// void MouseJoystick::moveToBaseHandler(int arg)
// {
//   setMoveToBaseStopState();
// }

// void MouseJoystick::deliverHandler(modular_server::Interrupt * interrupt_ptr)
// {
//   deliver();
// }

// void MouseJoystick::abortHandler(modular_server::Interrupt * interrupt_ptr)
// {
//   abort();
// }
