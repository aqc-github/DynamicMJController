// ----------------------------------------------------------------------------
// MouseJoystickController.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "../MouseJoystickController.h"


using namespace mouse_joystick_controller;

MouseJoystickController::MouseJoystickController()
{
}

void MouseJoystickController::setup()
{
  // Parent Setup
  StageController::setup();

  // Event Controller Setup
  event_controller_.setup();

  // Clients Setup
  encoder_interface_simple_ptr_ = &(createClientAtAddress(constants::encoder_interface_simple_address));
  power_switch_controller_ptr_ = &(createClientAtAddress(constants::power_switch_controller_address));

  // Pin Setup

  // Assay Status Setup
  assay_status_.state_ptr = &constants::state_assay_not_started_string;

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
  modular_server::Property & channel_count_property = modular_server_.property(step_dir_controller::constants::channel_count_property_name);
  channel_count_property.setDefaultValue(constants::channel_count);
  channel_count_property.setRange(constants::channel_count,constants::channel_count);

  modular_server::Property & steps_per_position_units_property = modular_server_.property(step_dir_controller::constants::steps_per_position_units_property_name);
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

  modular_server::Property & stage_position_min_property = modular_server_.property(stage_controller::constants::stage_position_min_property_name);
  stage_position_min_property.setDefaultValue(constants::stage_position_min_default);

  modular_server::Property & stage_position_max_property = modular_server_.property(stage_controller::constants::stage_position_max_property_name);
  stage_position_max_property.setDefaultValue(constants::stage_position_max_default);

  modular_server_.createProperty(constants::base_position_property_name,constants::base_position_default);

  modular_server_.createProperty(constants::reach_position_property_name,constants::reach_position_default);

  modular_server::Property & pull_threshold_property = modular_server_.createProperty(constants::pull_threshold_property_name,constants::pull_threshold_default);
  pull_threshold_property.setRange(constants::pull_threshold_min,constants::pull_threshold_max);

  // Parameters

  // Functions
  modular_server::Function & set_client_property_values_function = modular_server_.createFunction(constants::set_client_property_values_function_name);
  set_client_property_values_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&MouseJoystickController::setClientPropertyValuesHandler));
  set_client_property_values_function.setResultTypeObject();

  modular_server::Function & get_assay_status_function = modular_server_.createFunction(constants::get_assay_status_function_name);
  get_assay_status_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&MouseJoystickController::getAssayStatusHandler));
  get_assay_status_function.setResultTypeObject();

  modular_server::Function & move_joystick_to_base_position_function = modular_server_.createFunction(constants::move_joystick_to_base_position_function_name);
  move_joystick_to_base_position_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&MouseJoystickController::moveJoystickToBasePositionHandler));

  modular_server::Function & move_joystick_to_reach_position_function = modular_server_.createFunction(constants::move_joystick_to_reach_position_function_name);
  move_joystick_to_reach_position_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&MouseJoystickController::moveJoystickToReachPositionHandler));

  // Callbacks
  modular_server::Callback & start_trial_callback = modular_server_.createCallback(constants::start_trial_callback_name);
  start_trial_callback.attachFunctor(makeFunctor((Functor1<modular_server::Interrupt *> *)0,*this,&MouseJoystickController::startTrialHandler));
  start_trial_callback.attachTo(modular_device_base::constants::bnc_b_interrupt_name,modular_server::interrupt::mode_falling);
#if defined(__MK64FX512__)
  start_trial_callback.attachTo(modular_device_base::constants::btn_b_interrupt_name,modular_server::interrupt::mode_falling);
#endif

  modular_server::Callback & abort_callback = modular_server_.createCallback(constants::abort_callback_name);
  abort_callback.attachFunctor(makeFunctor((Functor1<modular_server::Interrupt *> *)0,*this,&MouseJoystickController::abortHandler));
  abort_callback.attachTo(modular_device_base::constants::bnc_a_interrupt_name,modular_server::interrupt::mode_falling);
#if !defined(__AVR_ATmega2560__)
  abort_callback.attachTo(modular_device_base::constants::btn_a_interrupt_name,modular_server::interrupt::mode_falling);
#endif

}

void MouseJoystickController::update()
{
  // Parent Update
  StageController::update();

  const ConstantString * state_ptr = assay_status_.state_ptr;

  if (state_ptr == &constants::state_assay_started_string)
  {
    if (stageHomed())
    {
      assay_status_.state_ptr = &constants::state_move_to_base_start_string;
    }
    else
    {
      assay_status_.state_ptr = &constants::state_homing_string;
      homeStage();
    }
  }
  else if (state_ptr == &constants::state_homing_string)
  {
    if (stageHomed())
    {
      assay_status_.state_ptr = &constants::state_move_to_base_start_string;
    }
  }
  else if (state_ptr == &constants::state_move_to_base_start_string)
  {
    assay_status_.state_ptr = &constants::state_moving_to_base_start_string;
    moveJoystickToBasePosition();
  }
  else if (state_ptr == &constants::state_moving_to_base_start_string)
  {
    if (stageAtTargetPosition())
    {
      assay_status_.state_ptr = &constants::state_move_to_reach_string;
    }
  }
  else if (state_ptr == &constants::state_move_to_reach_string)
  {
    assay_status_.state_ptr = &constants::state_moving_to_reach_string;
    moveJoystickToReachPosition();
  }
  else if (state_ptr == &constants::state_moving_to_reach_string)
  {
    if (stageAtTargetPosition())
    {
      assay_status_.state_ptr = &constants::state_wait_for_pull_string;
    }
  }
  else if (state_ptr == &constants::state_wait_for_pull_string)
  {
    setupPull();
    assay_status_.state_ptr = &constants::state_waiting_for_pull_string;
  }
  else if (state_ptr == &constants::state_waiting_for_pull_string)
  {
    if (pulled())
    {
      assay_status_.state_ptr = &constants::state_retract_string;
    }
  }
  else if (state_ptr == &constants::state_retract_string)
  {
    assay_status_.state_ptr = &constants::state_retracting_string;
    homeStage();
  }
  else if (state_ptr == &constants::state_retracting_string)
  {
    if (stageHomed())
    {
      assay_status_.state_ptr = &constants::state_move_to_base_stop_string;
    }
  }
  else if (state_ptr == &constants::state_move_to_base_stop_string)
  {
    assay_status_.state_ptr = &constants::state_moving_to_base_stop_string;
    moveJoystickToBasePosition();
  }
  else if (state_ptr == &constants::state_moving_to_base_stop_string)
  {
    if (stageAtTargetPosition())
    {
      assay_status_.state_ptr = &constants::state_assay_finished_string;
    }
  }
}

constants::AssayStatus MouseJoystickController::getAssayStatus()
{
  return assay_status_;
}

StageController::PositionArray MouseJoystickController::getBasePosition()
{
  long base_position[constants::CHANNEL_COUNT];
  modular_server_.property(constants::base_position_property_name).getValue(base_position);

  StageController::PositionArray base_position_array(base_position);
  return base_position_array;
}

StageController::PositionArray MouseJoystickController::getReachPosition()
{
  long reach_position[constants::CHANNEL_COUNT];
  modular_server_.property(constants::reach_position_property_name).getValue(reach_position);

  StageController::PositionArray reach_position_array(reach_position);
  return reach_position_array;
}

void MouseJoystickController::moveJoystickToBasePosition()
{
  StageController::PositionArray base_position = getBasePosition();
  moveStageTo(base_position);
}

void MouseJoystickController::moveJoystickToReachPosition()
{
  StageController::PositionArray reach_position = getReachPosition();
  moveStageTo(reach_position);
}

void MouseJoystickController::startTrial()
{
  if ((assay_status_.state_ptr == &constants::state_assay_not_started_string) ||
      (assay_status_.state_ptr == &constants::state_assay_finished_string))
  {
    assay_status_.state_ptr = &constants::state_assay_started_string;
  }
}

void MouseJoystickController::abort()
{
  stopAll();
  event_controller_.removeAllEvents();

  assay_status_.state_ptr = &constants::state_retract_string;
}

void MouseJoystickController::setupPull()
{
  encoder_interface_simple_ptr_->call(encoder_interface_simple::constants::set_position_function_name,
                                      constants::encoder_index,
                                      constants::encoder_initial_value);
}

bool MouseJoystickController::pulled()
{
  bool was_pulled = false;
  StaticJsonBuffer<constants::ENCODER_POSITIONS_JSON_BUFFER_SIZE> json_buffer;
  JsonArray & position_array = encoder_interface_simple_ptr_->callGetResult(json_buffer,encoder_interface_simple::constants::get_positions_function_name);
  long position = position_array[constants::encoder_index];

  long pull_threshold;
  modular_server_.property(constants::pull_threshold_property_name).getValue(pull_threshold);

  if (position <= pull_threshold)
  {
    was_pulled = true;
  }
  return was_pulled;
}

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

void MouseJoystickController::setClientPropertyValuesHandler()
{
  modular_server_.response().writeResultKey();

  modular_server_.response().beginObject();

  bool call_was_successful;

  modular_server_.response().writeKey(encoder_interface_simple::constants::device_name);
  modular_server_.response().beginArray();
  encoder_interface_simple_ptr_->call(modular_server::constants::set_properties_to_defaults_function_name,
                                      modular_server::constants::all_array);
  call_was_successful = encoder_interface_simple_ptr_->callWasSuccessful();
  modular_server_.response().write(call_was_successful);
  modular_server_.response().endArray();

  modular_server_.response().writeKey(power_switch_controller::constants::device_name);
  modular_server_.response().beginArray();
  power_switch_controller_ptr_->call(modular_server::constants::set_properties_to_defaults_function_name,
                                     modular_server::constants::all_array);
  call_was_successful = power_switch_controller_ptr_->callWasSuccessful();
  modular_server_.response().write(call_was_successful);
  modular_server_.response().endArray();

  modular_server_.response().endObject();
}

void MouseJoystickController::getAssayStatusHandler()
{
  constants::AssayStatus assay_status = getAssayStatus();

  modular_server_.response().writeResultKey();

  modular_server_.response().beginObject();

  modular_server_.response().write(constants::state_string,assay_status.state_ptr);

  modular_server_.response().endObject();

}

void MouseJoystickController::moveJoystickToBasePositionHandler()
{
  if ((assay_status_.state_ptr == &constants::state_assay_not_started_string) ||
      (assay_status_.state_ptr == &constants::state_assay_finished_string))
  {
    moveJoystickToBasePosition();
  }
}

void MouseJoystickController::moveJoystickToReachPositionHandler()
{
  if ((assay_status_.state_ptr == &constants::state_assay_not_started_string) ||
      (assay_status_.state_ptr == &constants::state_assay_finished_string))
  {
    moveJoystickToReachPosition();
  }
}

void MouseJoystickController::startTrialHandler(modular_server::Interrupt * interrupt_ptr)
{
  startTrial();
}

void MouseJoystickController::abortHandler(modular_server::Interrupt * interrupt_ptr)
{
  abort();
}
