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
  audio_controller_ptr_ = &(createClientAtAddress(constants::audio_controller_address));

  // Pin Setup

  // Assay Status Setup
  assay_status_.state_ptr = &constants::state_assay_not_started_string;
  for (size_t channel=0; channel < constants::CHANNEL_COUNT; ++channel)
  {
    assay_status_.reach_position.push_back(0);
  }
  assay_status_.pull_torque = 0;
  assay_status_.trial = 0;
  assay_status_.block = 0;
  assay_status_.set = 0;

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

  modular_server_.createProperty(constants::reach_position_0_property_name,constants::reach_position_0_default);

  modular_server_.createProperty(constants::reach_position_1_means_property_name,constants::reach_position_1_means_default);

  modular_server::Property & pull_threshold_property = modular_server_.createProperty(constants::pull_threshold_property_name,constants::pull_threshold_default);
  pull_threshold_property.setRange(constants::pull_threshold_min,constants::pull_threshold_max);

  modular_server::Property & push_threshold_property = modular_server_.createProperty(constants::push_threshold_property_name,constants::push_threshold_default);
  push_threshold_property.setRange(constants::push_threshold_min,constants::push_threshold_max);

  modular_server::Property & pull_torque_means_property = modular_server_.createProperty(constants::pull_torque_means_property_name,constants::pull_torque_means_default);
  pull_torque_means_property.setRange(constants::pull_torque_min,constants::pull_torque_max);
  pull_torque_means_property.setUnits(constants::percent_units);
  pull_torque_means_property.setArrayLengthRange(constants::pull_torque_array_length_min,
                                                 constants::pull_torque_array_length_max);

  modular_server::Property & ready_tone_frequency_property = modular_server_.createProperty(constants::ready_tone_frequency_property_name,constants::ready_tone_frequency_default);
  ready_tone_frequency_property.setRange(audio_controller::constants::frequency_min,audio_controller::constants::frequency_max);
  ready_tone_frequency_property.setUnits(audio_controller::constants::hz_units);

  modular_server::Property & ready_tone_duration_property = modular_server_.createProperty(constants::ready_tone_duration_property_name,constants::ready_tone_duration_default);
  ready_tone_duration_property.setRange(constants::ready_tone_duration_min,constants::ready_tone_duration_max);
  ready_tone_duration_property.setUnits(audio_controller::constants::ms_units);

  modular_server::Property & reward_tone_frequency_property = modular_server_.createProperty(constants::reward_tone_frequency_property_name,constants::reward_tone_frequency_default);
  reward_tone_frequency_property.setRange(audio_controller::constants::frequency_min,audio_controller::constants::frequency_max);
  reward_tone_frequency_property.setUnits(audio_controller::constants::hz_units);

  modular_server::Property & reward_tone_duration_property = modular_server_.createProperty(constants::reward_tone_duration_property_name,constants::reward_tone_duration_default);
  reward_tone_duration_property.setRange(constants::reward_tone_duration_min,constants::reward_tone_duration_max);
  reward_tone_duration_property.setUnits(audio_controller::constants::ms_units);

  modular_server::Property & reward_solenoid_delay_property = modular_server_.createProperty(constants::reward_solenoid_delay_property_name,constants::reward_solenoid_delay_default);
  reward_solenoid_delay_property.setRange(constants::reward_solenoid_delay_min,constants::reward_solenoid_delay_max);
  reward_solenoid_delay_property.setUnits(power_switch_controller::constants::ms_units);

  modular_server::Property & reward_solenoid_duration_property = modular_server_.createProperty(constants::reward_solenoid_duration_property_name,constants::reward_solenoid_duration_default);
  reward_solenoid_duration_property.setRange(constants::reward_solenoid_duration_min,constants::reward_solenoid_duration_max);
  reward_solenoid_duration_property.setUnits(power_switch_controller::constants::ms_units);

  modular_server::Property & trial_timeout_duration_property = modular_server_.createProperty(constants::trial_timeout_duration_property_name,constants::trial_timeout_duration_default);
  trial_timeout_duration_property.setRange(constants::trial_timeout_duration_min,constants::trial_timeout_duration_max);
  trial_timeout_duration_property.setUnits(constants::seconds_units);

  modular_server_.createProperty(constants::repeat_aborted_trial_property_name,constants::repeat_aborted_trial_default);

  modular_server::Property & trial_count_property = modular_server_.createProperty(constants::trial_count_property_name,constants::trial_count_default);
  trial_count_property.setRange(constants::trial_count_min,constants::trial_count_max);

  modular_server::Property & set_count_property = modular_server_.createProperty(constants::set_count_property_name,constants::set_count_default);
  set_count_property.setRange(constants::set_count_min,constants::set_count_max);

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

  modular_server::Callback & start_assay_callback = modular_server_.createCallback(constants::start_assay_callback_name);
  start_assay_callback.attachFunctor(makeFunctor((Functor1<modular_server::Interrupt *> *)0,*this,&MouseJoystickController::startAssayHandler));

  modular_server::Callback & abort_trial_callback = modular_server_.createCallback(constants::abort_trial_callback_name);
  abort_trial_callback.attachFunctor(makeFunctor((Functor1<modular_server::Interrupt *> *)0,*this,&MouseJoystickController::abortTrialHandler));
  abort_trial_callback.attachTo(modular_device_base::constants::bnc_a_interrupt_name,modular_server::interrupt::mode_falling);
#if !defined(__AVR_ATmega2560__)
  abort_trial_callback.attachTo(modular_device_base::constants::btn_a_interrupt_name,modular_server::interrupt::mode_falling);
#endif

  modular_server::Callback & abort_assay_callback = modular_server_.createCallback(constants::abort_assay_callback_name);
  abort_assay_callback.attachFunctor(makeFunctor((Functor1<modular_server::Interrupt *> *)0,*this,&MouseJoystickController::abortAssayHandler));

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
      assay_status_.state_ptr = &constants::state_wait_to_start_trial_string;
    }
  }
  else if (state_ptr == &constants::state_wait_to_start_trial_string)
  {
    setupTrial();
  }
  else if (state_ptr == &constants::state_waiting_to_start_trial_string)
  {
    checkForStartTrial();
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
  }
  else if (state_ptr == &constants::state_waiting_for_pull_string)
  {
    checkForPullOrPush();
  }
  else if (state_ptr == &constants::state_reward_string)
  {
    reward();
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
      assay_status_.state_ptr = &constants::state_finish_trial_string;
    }
  }
  else if (state_ptr == &constants::state_finish_trial_string)
  {
    finishTrial();
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
  return assay_status_.reach_position;
}

long MouseJoystickController::getPullTorque()
{
  return assay_status_.pull_torque;
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
  if (assay_status_.state_ptr == &constants::state_waiting_to_start_trial_string)
  {
    assay_status_.state_ptr = &constants::state_move_to_reach_string;
  }
  else
  {
    startAssay();
  }
}

void MouseJoystickController::startAssay()
{
  if ((assay_status_.state_ptr == &constants::state_assay_not_started_string) ||
      (assay_status_.state_ptr == &constants::state_assay_finished_string))
  {
    trial_aborted_ = false;
    assay_aborted_ = false;
    reach_position_1_index_ = 0;
    updateReachPosition();
    pull_torque_index_ = 0;
    updatePullTorque();

    assay_status_.state_ptr = &constants::state_assay_started_string;
  }
}

void MouseJoystickController::abortTrial()
{
  stopAll();
  event_controller_.removeAllEvents();

  trial_aborted_ = true;
  assay_status_.state_ptr = &constants::state_retract_string;
}

void MouseJoystickController::abortAssay()
{
  assay_aborted_ = true;
  abortTrial();
}

void MouseJoystickController::setupTrial()
{
  trial_aborted_ = false;
  assay_status_.state_ptr = &constants::state_waiting_to_start_trial_string;
}

void MouseJoystickController::checkForStartTrial()
{
  // todo: sense paws
  if (false)
  {
    assay_status_.state_ptr = &constants::state_move_to_reach_string;
  }
}

void MouseJoystickController::setupPull()
{
  encoder_interface_simple_ptr_->call(encoder_interface_simple::constants::set_position_function_name,
                                      constants::pull_encoder_index,
                                      constants::pull_encoder_initial_value);

  long pull_torque = getPullTorque();

  long pwm_offset = map(pull_torque,
                        constants::pull_torque_min,
                        constants::pull_torque_max,
                        constants::pull_pwm_offset_min,
                        constants::pull_pwm_offset_max);

  disableAutomaticCurrentScaling(constants::pull_channel);
  setPwmOffset(constants::pull_channel,pwm_offset);

  long ready_tone_frequency;
  modular_server_.property(constants::ready_tone_frequency_property_name).getValue(ready_tone_frequency);

  long ready_tone_duration;
  modular_server_.property(constants::ready_tone_duration_property_name).getValue(ready_tone_duration);

  long trial_timeout_duration;
  modular_server_.property(constants::trial_timeout_duration_property_name).getValue(trial_timeout_duration);

  trial_timeout_event_id_ = event_controller_.addEventUsingDelay(makeFunctor((Functor1<int> *)0,*this,&MouseJoystickController::trialTimeoutHandler),
                                                                 trial_timeout_duration*constants::milliseconds_per_second);
  event_controller_.enable(trial_timeout_event_id_);

  audio_controller_ptr_->call(audio_controller::constants::add_tone_pwm_function_name,
                              ready_tone_frequency,
                              audio_controller::constants::speaker_all,
                              constants::ready_tone_delay,
                              ready_tone_duration,
                              ready_tone_duration,
                              constants::ready_tone_count);

  assay_status_.state_ptr = &constants::state_waiting_for_pull_string;
}

void MouseJoystickController::checkForPullOrPush()
{
  StaticJsonBuffer<constants::ENCODER_POSITIONS_JSON_BUFFER_SIZE> json_buffer;
  JsonArray & position_array = encoder_interface_simple_ptr_->callGetResult(json_buffer,encoder_interface_simple::constants::get_positions_function_name);
  long position = position_array[constants::pull_encoder_index];

  long pull_threshold;
  modular_server_.property(constants::pull_threshold_property_name).getValue(pull_threshold);

  long push_threshold;
  modular_server_.property(constants::push_threshold_property_name).getValue(push_threshold);

  if (position <= pull_threshold)
  {
    event_controller_.remove(trial_timeout_event_id_);
    assay_status_.state_ptr = &constants::state_reward_string;
  }
  else if (position >= push_threshold)
  {
    event_controller_.remove(trial_timeout_event_id_);
    abortTrial();
  }
}

void MouseJoystickController::reward()
{
  long reward_tone_frequency;
  modular_server_.property(constants::reward_tone_frequency_property_name).getValue(reward_tone_frequency);

  long reward_tone_duration;
  modular_server_.property(constants::reward_tone_duration_property_name).getValue(reward_tone_duration);

  audio_controller_ptr_->call(audio_controller::constants::add_tone_pwm_function_name,
                              reward_tone_frequency,
                              audio_controller::constants::speaker_all,
                              constants::reward_tone_delay,
                              reward_tone_duration,
                              reward_tone_duration,
                              constants::reward_tone_count);

  long reward_solenoid_delay;
  modular_server_.property(constants::reward_solenoid_delay_property_name).getValue(reward_solenoid_delay);

  long reward_solenoid_duration;
  modular_server_.property(constants::reward_solenoid_duration_property_name).getValue(reward_solenoid_duration);

  Array<long,constants::REWARD_SOLENOID_CHANNEL_COUNT> solenoid_channels(constants::reward_solenoid_channels);
  power_switch_controller_ptr_->call(power_switch_controller::constants::add_pwm_function_name,
                                     solenoid_channels,
                                     reward_solenoid_delay,
                                     reward_solenoid_duration*2,
                                     reward_solenoid_duration,
                                     constants::reward_solenoid_count);

  assay_status_.state_ptr = &constants::state_retract_string;
}

void MouseJoystickController::finishTrial()
{
  assay_status_.state_ptr = &constants::state_move_to_base_start_string;

  if (assay_aborted_)
  {
    assay_status_.state_ptr = &constants::state_move_to_base_stop_string;
    return;
  }

  if (trial_aborted_)
  {
    bool repeat_aborted_trial;
    modular_server_.property(constants::repeat_aborted_trial_property_name).getValue(repeat_aborted_trial);
    if (repeat_aborted_trial)
    {
      return;
    }
  }

  long trial_count;
  modular_server_.property(constants::trial_count_property_name).getValue(trial_count);
  if (++assay_status_.trial >= (size_t)trial_count)
  {
    assay_status_.trial = 0;

    ++assay_status_.block;
    const size_t pull_torque_array_length = modular_server_.property(constants::pull_torque_means_property_name).getArrayLength();
    if (++pull_torque_index_ >= pull_torque_array_length)
    {
      pull_torque_index_ = 0;
      assay_status_.block = 0;

      const size_t reach_position_1_array_length = modular_server_.property(constants::reach_position_1_means_property_name).getArrayLength();
      if (++reach_position_1_index_ >= reach_position_1_array_length)
      {
        reach_position_1_index_ = 0;

        long set_count;
        modular_server_.property(constants::set_count_property_name).getValue(set_count);
        if (++assay_status_.set >= (size_t)set_count)
        {
          assay_status_.set = 0;

          assay_status_.state_ptr = &constants::state_move_to_base_stop_string;
        }
      }
    }
  }
  updateReachPosition();
  updatePullTorque();
}

void MouseJoystickController::updateReachPosition()
{
  long reach_position_0;
  modular_server_.property(constants::reach_position_0_property_name).getValue(reach_position_0);

  long reach_position_1;
  modular_server_.property(constants::reach_position_1_means_property_name).getElementValue(reach_position_1_index_,
                                                                                            reach_position_1);

  assay_status_.reach_position[0] = reach_position_0;
  assay_status_.reach_position[1] = reach_position_1;
}

void MouseJoystickController::updatePullTorque()
{
  long pull_torque_mean;
  modular_server_.property(constants::pull_torque_means_property_name).getElementValue(pull_torque_index_,
                                                                                       pull_torque_mean);
  assay_status_.pull_torque = pull_torque_mean;
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

  modular_server_.response().writeKey(audio_controller::constants::device_name);
  modular_server_.response().beginArray();
  audio_controller_ptr_->call(modular_server::constants::set_properties_to_defaults_function_name,
                              modular_server::constants::all_array);
  call_was_successful = audio_controller_ptr_->callWasSuccessful();
  modular_server_.response().write(call_was_successful);
  modular_server_.response().endArray();

  modular_server_.response().endObject();
}

void MouseJoystickController::getAssayStatusHandler()
{
  modular_server_.response().writeResultKey();

  modular_server_.response().beginObject();

  modular_server_.response().write(constants::state_string,assay_status_.state_ptr);
  modular_server_.response().write(constants::reach_position_string,assay_status_.reach_position);
  modular_server_.response().write(constants::pull_torque_string,assay_status_.pull_torque);
  modular_server_.response().write(constants::trial_string,assay_status_.trial);
  modular_server_.response().write(constants::block_string,assay_status_.block);
  modular_server_.response().write(constants::set_string,assay_status_.set);

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

void MouseJoystickController::startAssayHandler(modular_server::Interrupt * interrupt_ptr)
{
  startAssay();
}

void MouseJoystickController::abortTrialHandler(modular_server::Interrupt * interrupt_ptr)
{
  abortTrial();
}

void MouseJoystickController::abortAssayHandler(modular_server::Interrupt * interrupt_ptr)
{
  abortAssay();
}

void MouseJoystickController::trialTimeoutHandler(int arg)
{
  abortTrial();
}
