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

  // Reset Watchdog
  resetWatchdog();

  // Event Controller Setup
  event_controller_.setup();

  // Clients Setup
  encoder_interface_simple_ptr_ = &(createClientAtAddress(constants::encoder_interface_simple_address));
  encoder_interface_simple_ptr_->setName(encoder_interface_simple::constants::device_name);
  power_switch_controller_ptr_ = &(createClientAtAddress(constants::power_switch_controller_address));
  power_switch_controller_ptr_->setName(power_switch_controller::constants::device_name);
  audio_controller_ptr_ = &(createClientAtAddress(constants::audio_controller_address));
  audio_controller_ptr_->setName(audio_controller::constants::device_name);

  // Pin Setup

  // Assay Status Setup
  assay_status_.state_ptr = &constants::state_assay_not_started_string;
  assay_status_.trial = 0;
  assay_status_.block = 0;
  assay_status_.set = 0;
  for (size_t channel=0; channel < constants::CHANNEL_COUNT; ++channel)
  {
    assay_status_.reach_position.push_back(0);
  }
  assay_status_.pull_torque = 0;
  assay_status_.pull_threshold = 0;
  assay_status_.successful_trial_count = 0;

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);

  // Add Hardware

  // Pins

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

  modular_server::Property & home_current_property = modular_server_.createProperty(constants::home_current_property_name,constants::home_current_default);
  home_current_property.setUnits(stepper_controller::constants::percent_units);
  home_current_property.setRange(stepper_controller::constants::percent_min,stepper_controller::constants::percent_max);

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

  modular_server::Property & tone_volume_property = modular_server_.createProperty(constants::tone_volume_property_name,constants::tone_volume_default);
  tone_volume_property.setRange(constants::tone_volume_min,constants::tone_volume_max);
  tone_volume_property.setUnits(audio_controller::constants::percent_units);

  modular_server::Property & reward_lickport_delay_property = modular_server_.createProperty(constants::reward_lickport_delay_property_name,constants::reward_lickport_delay_default);
  reward_lickport_delay_property.setRange(constants::reward_lickport_delay_min,constants::reward_lickport_delay_max);
  reward_lickport_delay_property.setUnits(power_switch_controller::constants::ms_units);

  modular_server::Property & lickport_duration_property = modular_server_.createProperty(constants::lickport_duration_property_name,constants::lickport_duration_default);
  lickport_duration_property.setRange(constants::lickport_duration_min,constants::lickport_duration_max);
  lickport_duration_property.setUnits(power_switch_controller::constants::ms_units);

  modular_server::Property & trial_timeout_duration_property = modular_server_.createProperty(constants::trial_timeout_duration_property_name,constants::trial_timeout_duration_default);
  trial_timeout_duration_property.setRange(constants::trial_timeout_duration_min,constants::trial_timeout_duration_max);
  trial_timeout_duration_property.setUnits(constants::seconds_units);

  modular_server_.createProperty(constants::repeat_aborted_trial_property_name,constants::repeat_aborted_trial_default);

  modular_server::Property & trial_count_property = modular_server_.createProperty(constants::trial_count_property_name,constants::trial_count_default);
  trial_count_property.setRange(constants::trial_count_min,constants::trial_count_max);

  modular_server::Property & set_count_property = modular_server_.createProperty(constants::set_count_property_name,constants::set_count_default);
  set_count_property.setRange(constants::set_count_min,constants::set_count_max);

  modular_server::Property & start_trial_duration_property = modular_server_.createProperty(constants::start_trial_duration_property_name,constants::start_trial_duration_default);
  start_trial_duration_property.setRange(constants::start_trial_duration_min,constants::start_trial_duration_max);
  start_trial_duration_property.setUnits(constants::seconds_units);

  // Parameters
  modular_server::Parameter & count_parameter = modular_server_.createParameter(constants::count_parameter_name);
  count_parameter.setRange(constants::count_min,constants::count_max);

  // Functions
  modular_server::Function & get_assay_status_function = modular_server_.createFunction(constants::get_assay_status_function_name);
  get_assay_status_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&MouseJoystickController::getAssayStatusHandler));
  get_assay_status_function.setResultTypeObject();

  modular_server::Function & move_joystick_to_base_position_function = modular_server_.createFunction(constants::move_joystick_to_base_position_function_name);
  move_joystick_to_base_position_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&MouseJoystickController::moveJoystickToBasePositionHandler));

  modular_server::Function & move_joystick_to_reach_position_function = modular_server_.createFunction(constants::move_joystick_to_reach_position_function_name);
  move_joystick_to_reach_position_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&MouseJoystickController::moveJoystickToReachPositionHandler));

  modular_server::Function & activate_lickport_function = modular_server_.createFunction(constants::activate_lickport_function_name);
  activate_lickport_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&MouseJoystickController::activateLickportHandler));
  activate_lickport_function.addParameter(count_parameter);

  // Callbacks
  modular_server::Callback & start_trial_callback = modular_server_.createCallback(constants::start_trial_callback_name);
  start_trial_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&MouseJoystickController::startTrialHandler));

  modular_server::Callback & start_assay_callback = modular_server_.createCallback(constants::start_assay_callback_name);
  start_assay_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&MouseJoystickController::startAssayHandler));

  modular_server::Callback & abort_trial_callback = modular_server_.createCallback(constants::abort_trial_callback_name);
  abort_trial_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&MouseJoystickController::abortTrialHandler));
  abort_trial_callback.attachTo(modular_device_base::constants::bnc_a_pin_name,modular_server::constants::pin_mode_interrupt_falling);

  modular_server::Callback & abort_assay_callback = modular_server_.createCallback(constants::abort_assay_callback_name);
  abort_assay_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&MouseJoystickController::abortAssayHandler));

  modular_server::Callback & restart_assay_callback = modular_server_.createCallback(constants::restart_assay_callback_name);
  restart_assay_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&MouseJoystickController::restartAssayHandler));
  restart_assay_callback.attachTo(modular_device_base::constants::bnc_b_pin_name,modular_server::constants::pin_mode_interrupt_falling);
#if defined(__MK64FX512__)
  restart_assay_callback.attachTo(modular_device_base::constants::btn_b_pin_name,modular_server::constants::pin_mode_interrupt_falling);
#endif

}

void MouseJoystickController::update()
{
  // Parent Update
  StageController::update();

  const ConstantString * state_ptr = assay_status_.state_ptr;

  if (state_ptr == &constants::state_assay_started_string)
  {
    setupClients();
    setupAssay();
    assay_status_.state_ptr = &constants::state_homing_0_string;
    reinitialize();
    setHomeCurrent(0);
    home(0);
  }
  else if (state_ptr == &constants::state_homing_0_string)
  {
    if (homed(0))
    {
      assay_status_.state_ptr = &constants::state_move_to_homed_0_string;
    }
  }
  else if (state_ptr == &constants::state_move_to_homed_0_string)
  {
    assay_status_.state_ptr = &constants::state_moving_to_homed_0_string;
    moveTo(0,constants::not_touching_switch_position);
  }
  else if (state_ptr == &constants::state_moving_to_homed_0_string)
  {
    if (atTargetPosition(0))
    {
      restoreCurrentSettings(0);
      assay_status_.state_ptr = &constants::state_homing_1_string;
      setHomeCurrent(1);
      home(1);
    }
  }
  else if (state_ptr == &constants::state_homing_1_string)
  {
    if (homed(1))
    {
      assay_status_.state_ptr = &constants::state_move_to_homed_1_string;
    }
  }
  else if (state_ptr == &constants::state_move_to_homed_1_string)
  {
    assay_status_.state_ptr = &constants::state_moving_to_homed_1_string;
    moveTo(1,constants::not_touching_switch_position);
  }
  else if (state_ptr == &constants::state_moving_to_homed_1_string)
  {
    if (atTargetPosition(1))
    {
      restoreCurrentSettings(1);
      assay_status_.state_ptr = &constants::state_move_to_base_start_string;
    }
  }
  else if (state_ptr == &constants::state_move_to_base_start_string)
  {
    assay_status_.state_ptr = &constants::state_moving_to_base_start_string;
    moveToBasePosition();
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
    assay_status_.state_ptr = &constants::state_waiting_to_start_trial_string;
    setupTrial();
    addStartTrialEvent();
  }
  else if (state_ptr == &constants::state_waiting_to_start_trial_string)
  {
  }
  else if (state_ptr == &constants::state_wait_for_mouse_ready_string)
  {
    assay_status_.state_ptr = &constants::state_waiting_for_mouse_ready_string;
  }
  else if (state_ptr == &constants::state_waiting_for_mouse_ready_string)
  {
    checkForMouseReady();
  }
  else if (state_ptr == &constants::state_move_to_reach_string)
  {
    assay_status_.state_ptr = &constants::state_moving_to_reach_string;
    moveToReachPosition();
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
    assay_status_.state_ptr = &constants::state_retracting_0_string;
    reinitialize();
    setHomeCurrent(0);
    home(0);
  }
  else if (state_ptr == &constants::state_retracting_0_string)
  {
    if (homed(0))
    {
      assay_status_.state_ptr = &constants::state_move_to_retracted_0_string;
    }
  }
  else if (state_ptr == &constants::state_move_to_retracted_0_string)
  {
    assay_status_.state_ptr = &constants::state_moving_to_retracted_0_string;
    moveTo(0,constants::not_touching_switch_position);
  }
  else if (state_ptr == &constants::state_moving_to_retracted_0_string)
  {
    if (atTargetPosition(0))
    {
      restoreCurrentSettings(0);
      assay_status_.state_ptr = &constants::state_retracting_1_string;
      setHomeCurrent(1);
      home(1);
    }
  }
  else if (state_ptr == &constants::state_retracting_1_string)
  {
    if (homed(1))
    {
      assay_status_.state_ptr = &constants::state_move_to_retracted_1_string;
    }
  }
  else if (state_ptr == &constants::state_move_to_retracted_1_string)
  {
    assay_status_.state_ptr = &constants::state_moving_to_retracted_1_string;
    moveTo(1,constants::not_touching_switch_position);
  }
  else if (state_ptr == &constants::state_moving_to_retracted_1_string)
  {
    if (atTargetPosition(1))
    {
      restoreCurrentSettings(1);
      assay_status_.state_ptr = &constants::state_check_trial_termination_string;
    }
  }
  else if (state_ptr == &constants::state_check_trial_termination_string)
  {
    checkTrialTermination();
  }
  else if (state_ptr == &constants::state_finish_trial_string)
  {
    finishTrial();
  }
  else if (state_ptr == &constants::state_move_to_base_stop_string)
  {
    assay_status_.state_ptr = &constants::state_moving_to_base_stop_string;
    moveToBasePosition();
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

void MouseJoystickController::moveJoystickToBasePosition()
{
  if ((assay_status_.state_ptr == &constants::state_assay_not_started_string) ||
      (assay_status_.state_ptr == &constants::state_assay_finished_string))
  {
    moveToBasePosition();
  }
}

void MouseJoystickController::moveJoystickToReachPosition()
{
  if ((assay_status_.state_ptr == &constants::state_assay_not_started_string) ||
      (assay_status_.state_ptr == &constants::state_assay_finished_string))
  {
    moveToReachPosition();
  }
}

void MouseJoystickController::activateLickport(const long count)
{
  if ((assay_status_.state_ptr == &constants::state_assay_not_started_string) ||
      (assay_status_.state_ptr == &constants::state_assay_finished_string))
  {
    triggerLickport(constants::activate_lickport_delay,count);
  }
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
    assay_status_.trial = 0;
    assay_status_.block = 0;
    assay_status_.set = 0;
    assay_status_.successful_trial_count = 0;
    trial_aborted_ = false;
    assay_aborted_ = false;
    reach_position_1_index_ = 0;
    updateReachPosition();
    pull_torque_index_ = 0;
    updatePullTorque();
    updatePullThreshold();

    assay_status_.state_ptr = &constants::state_assay_started_string;
  }
}

void MouseJoystickController::abortTrial()
{
  stopAll();
  event_controller_.removeAllEvents();

  encoder_interface_simple_ptr_->call(encoder_interface_simple::constants::disable_all_outputs_function_name);

  trial_aborted_ = true;
  assay_status_.state_ptr = &constants::state_retract_string;
}

void MouseJoystickController::abortAssay()
{
  assay_aborted_ = true;
  abortTrial();
}

void MouseJoystickController::restartAssay()
{
  abortAssay();
  assay_status_.state_ptr = &constants::state_assay_not_started_string;
  startAssay();
}

// private

bool MouseJoystickController::setupClients()
{
  bool setup_was_successful = true;

  encoder_interface_simple_ptr_->call(modular_server::constants::set_properties_to_defaults_function_name,
                                      modular_server::constants::all_array);
  setup_was_successful = setup_was_successful && encoder_interface_simple_ptr_->callWasSuccessful();

  power_switch_controller_ptr_->call(modular_server::constants::set_properties_to_defaults_function_name,
                                     modular_server::constants::all_array);
  setup_was_successful = setup_was_successful && power_switch_controller_ptr_->callWasSuccessful();
  power_switch_controller_ptr_->call(modular_server::constants::set_pin_mode_function_name,
                                     modular_device_base::constants::bnc_b_pin_name,
                                     modular_server::constants::pin_mode_pulse_rising);
  setup_was_successful = setup_was_successful && power_switch_controller_ptr_->callWasSuccessful();

  audio_controller_ptr_->call(modular_server::constants::set_properties_to_defaults_function_name,
                              modular_server::constants::all_array);
  setup_was_successful = setup_was_successful && audio_controller_ptr_->callWasSuccessful();
  audio_controller_ptr_->call(modular_server::constants::set_pin_mode_function_name,
                              modular_device_base::constants::bnc_b_pin_name,
                              modular_server::constants::pin_mode_pulse_rising);
  setup_was_successful = setup_was_successful && audio_controller_ptr_->callWasSuccessful();

  return setup_was_successful;
}

StageController::PositionArray MouseJoystickController::getBasePosition()
{
  StageController::PositionArray base_position_array;
  modular_server_.property(constants::base_position_property_name).getValue(base_position_array);

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

void MouseJoystickController::setupAssay()
{
  if (assay_status_.state_ptr == &constants::state_assay_started_string)
  {
    encoder_interface_simple_ptr_->call(encoder_interface_simple::constants::disable_all_outputs_function_name);
  }
}

void MouseJoystickController::setupTrial()
{
  trial_aborted_ = false;
}

void MouseJoystickController::addStartTrialEvent()
{
  long start_trial_duration;
  modular_server_.property(constants::start_trial_duration_property_name).getValue(start_trial_duration);

  if (start_trial_duration > 0)
  {
    EventId start_trial_event_id = event_controller_.addEventUsingDelay(makeFunctor((Functor1<int> *)0,*this,&MouseJoystickController::startTrialEventHandler),
                                                                        start_trial_duration*constants::milliseconds_per_second);
    event_controller_.enable(start_trial_event_id);
  }
  else
  {
    startTrialEventHandler(0);
  }
}

void MouseJoystickController::checkForMouseReady()
{
  // todo: sense paws
  if (true)
  {
    assay_status_.state_ptr = &constants::state_move_to_reach_string;
  }
}

void MouseJoystickController::setupPull()
{
  encoder_interface_simple_ptr_->call(encoder_interface_simple::constants::enable_all_outputs_function_name);
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

  long trial_timeout_duration;
  modular_server_.property(constants::trial_timeout_duration_property_name).getValue(trial_timeout_duration);

  trial_timeout_event_id_ = event_controller_.addEventUsingDelay(makeFunctor((Functor1<int> *)0,*this,&MouseJoystickController::trialTimeoutEventHandler),
                                                                 trial_timeout_duration*constants::milliseconds_per_second);
  event_controller_.enable(trial_timeout_event_id_);

  playReadyTone();

  pull_push_poll_time_previous_ = millis();

  assay_status_.state_ptr = &constants::state_waiting_for_pull_string;
}

void MouseJoystickController::checkForPullOrPush()
{
  time_ = millis();
  if ((time_ - pull_push_poll_time_previous_) < constants::pull_push_poll_period)
  {
    return;
  }
  pull_push_poll_time_previous_ = time_;

  if (!encoder_interface_simple_ptr_->enabled())
  {
    event_controller_.remove(trial_timeout_event_id_);
    assay_status_.state_ptr = &constants::state_reward_string;
  }

  StaticJsonBuffer<constants::ENCODER_POSITIONS_JSON_BUFFER_SIZE> json_buffer;
  JsonArray & position_array = encoder_interface_simple_ptr_->callGetResult(json_buffer,encoder_interface_simple::constants::get_positions_function_name);
  long position;
  if (encoder_interface_simple_ptr_->callWasSuccessful())
  {
    position = position_array[constants::pull_encoder_index];
  }
  else
  {
    return;
  }

  long push_threshold;
  modular_server_.property(constants::push_threshold_property_name).getValue(push_threshold);

  if (position <= assay_status_.pull_threshold)
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
  playRewardTone();

  encoder_interface_simple_ptr_->call(encoder_interface_simple::constants::disable_all_outputs_function_name);

  triggerLickportReward();

  assay_status_.state_ptr = &constants::state_retract_string;
}

void MouseJoystickController::checkTrialTermination()
{
  if (assay_aborted_)
  {
    assay_status_.state_ptr = &constants::state_move_to_base_stop_string;
  }
  else
  {
    assay_status_.state_ptr = &constants::state_finish_trial_string;
  }
}

void MouseJoystickController::finishTrial()
{
  assay_status_.state_ptr = &constants::state_move_to_base_start_string;

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
  ++assay_status_.successful_trial_count;
  updateReachPosition();
  updatePullTorque();
  updatePullThreshold();
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

void MouseJoystickController::updatePullThreshold()
{
  long pull_threshold;
  modular_server_.property(constants::pull_threshold_property_name).getValue(pull_threshold);

  assay_status_.pull_threshold = pull_threshold;
}

void MouseJoystickController::moveToBasePosition()
{
  StageController::PositionArray base_position = getBasePosition();
  moveStageTo(base_position);
}

void MouseJoystickController::moveToReachPosition()
{
  StageController::PositionArray reach_position = getReachPosition();
  moveStageTo(reach_position);
}

void MouseJoystickController::playReadyTone()
{
  long ready_tone_frequency;
  modular_server_.property(constants::ready_tone_frequency_property_name).getValue(ready_tone_frequency);

  long ready_tone_duration;
  modular_server_.property(constants::ready_tone_duration_property_name).getValue(ready_tone_duration);

  long tone_volume;
  modular_server_.property(constants::tone_volume_property_name).getValue(tone_volume);

  audio_controller_ptr_->call(audio_controller::constants::add_tone_pwm_at_function_name,
                              ready_tone_frequency,
                              audio_controller::constants::speaker_all,
                              tone_volume,
                              constants::ready_tone_delay,
                              ready_tone_duration,
                              ready_tone_duration,
                              constants::ready_tone_count);
  audio_controller_ptr_->call(modular_server::constants::set_pin_value_function_name,
                              modular_device_base::constants::bnc_b_pin_name,
                              constants::pulse_duration);
}

void MouseJoystickController::playRewardTone()
{
  long reward_tone_frequency;
  modular_server_.property(constants::reward_tone_frequency_property_name).getValue(reward_tone_frequency);

  long reward_tone_duration;
  modular_server_.property(constants::reward_tone_duration_property_name).getValue(reward_tone_duration);

  long tone_volume;
  modular_server_.property(constants::tone_volume_property_name).getValue(tone_volume);

  audio_controller_ptr_->call(audio_controller::constants::add_tone_pwm_at_function_name,
                              reward_tone_frequency,
                              audio_controller::constants::speaker_all,
                              tone_volume,
                              constants::reward_tone_delay,
                              reward_tone_duration,
                              reward_tone_duration,
                              constants::reward_tone_count);
}

void MouseJoystickController::triggerLickportReward()
{
  long reward_lickport_delay;
  modular_server_.property(constants::reward_lickport_delay_property_name).getValue(reward_lickport_delay);

  triggerLickport(reward_lickport_delay,constants::reward_lickport_count);
}

void MouseJoystickController::triggerLickport(const long delay,
                                              const long count)
{
  long lickport_duration;
  modular_server_.property(constants::lickport_duration_property_name).getValue(lickport_duration);

  Array<long,constants::REWARD_LICKPORT_CHANNEL_COUNT> lickport_channels(constants::reward_lickport_channels);
  power_switch_controller_ptr_->call(power_switch_controller::constants::add_pwm_function_name,
                                     lickport_channels,
                                     delay,
                                     lickport_duration*2,
                                     lickport_duration,
                                     count);
  power_switch_controller_ptr_->call(modular_server::constants::set_pin_value_function_name,
                                     modular_device_base::constants::bnc_b_pin_name,
                                     constants::pulse_duration);
}

void MouseJoystickController::setHomeCurrent(const size_t channel)
{
  if (channel >= constants::CHANNEL_COUNT)
  {
    return;
  }
  long home_current;
  modular_server_.property(constants::home_current_property_name).getElementValue(channel,home_current);

  modifyRunCurrent(channel,home_current);
  modifyHoldCurrent(channel,home_current);
}

void MouseJoystickController::restoreCurrentSettings(const size_t channel)
{
  restoreHoldCurrent(channel);
  restoreRunCurrent(channel);
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
// const ConstantString *
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_server_.property(property_name).getValue(value) value type must match the property default type
// modular_server_.property(property_name).setValue(value) value type must match the property default type
// modular_server_.property(property_name).getElementValue(element_index,value) value type must match the property array element default type
// modular_server_.property(property_name).setElementValue(element_index,value) value type must match the property array element default type

void MouseJoystickController::getAssayStatusHandler()
{
  modular_server_.response().writeResultKey();

  modular_server_.response().beginObject();

  modular_server_.response().write(constants::state_string,assay_status_.state_ptr);
  modular_server_.response().write(constants::trial_string,assay_status_.trial);
  modular_server_.response().write(constants::block_string,assay_status_.block);
  modular_server_.response().write(constants::set_string,assay_status_.set);
  modular_server_.response().write(constants::reach_position_string,assay_status_.reach_position);
  modular_server_.response().write(constants::pull_torque_string,assay_status_.pull_torque);
  modular_server_.response().write(constants::pull_threshold_string,assay_status_.pull_threshold);
  modular_server_.response().write(constants::successful_trial_count_string,assay_status_.successful_trial_count);

  modular_server_.response().endObject();

}

void MouseJoystickController::moveJoystickToBasePositionHandler()
{
  moveJoystickToBasePosition();
}

void MouseJoystickController::moveJoystickToReachPositionHandler()
{
  moveJoystickToReachPosition();
}

void MouseJoystickController::activateLickportHandler()
{
  long count;
  modular_server_.parameter(constants::count_parameter_name).getValue(count);

  activateLickport(count);
}

void MouseJoystickController::startTrialHandler(modular_server::Pin * pin_ptr)
{
  startTrial();
}

void MouseJoystickController::startAssayHandler(modular_server::Pin * pin_ptr)
{
  startAssay();
}

void MouseJoystickController::abortTrialHandler(modular_server::Pin * pin_ptr)
{
  abortTrial();
}

void MouseJoystickController::abortAssayHandler(modular_server::Pin * pin_ptr)
{
  abortAssay();
}

void MouseJoystickController::restartAssayHandler(modular_server::Pin * pin_ptr)
{
  restartAssay();
}

void MouseJoystickController::startTrialEventHandler(int arg)
{
  assay_status_.state_ptr = &constants::state_wait_for_mouse_ready_string;
}

void MouseJoystickController::trialTimeoutEventHandler(int arg)
{
  abortTrial();
}
