// ----------------------------------------------------------------------------
// MouseJoystickController.cpp
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
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
  encoder_interface_simple_ptr_ = &(createClientAtAddress(encoder_interface_simple::constants::device_name,constants::encoder_interface_simple_address));
  power_switch_controller_ptr_ = &(createClientAtAddress(power_switch_controller::constants::device_name,constants::power_switch_controller_address));
  audio_controller_ptr_ = &(createClientAtAddress(audio_controller::constants::device_name,constants::audio_controller_address));

  // Pin Setup

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

  setChannelCountHandler();

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

  modular_server::Property & right_switches_enabled_property = modular_server_.property(step_dir_controller::constants::right_switches_enabled_property_name);
  right_switches_enabled_property.setDefaultValue(constants::right_switches_enabled_default);

  modular_server::Property & right_switch_stop_enabled_property = modular_server_.property(step_dir_controller::constants::right_switch_stop_enabled_property_name);
  right_switch_stop_enabled_property.setDefaultValue(constants::right_switch_stop_enabled_default);

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

  modular_server::Property & idle_current_property = modular_server_.createProperty(constants::idle_current_property_name,constants::idle_current_default);
  idle_current_property.setUnits(stepper_controller::constants::percent_units);
  idle_current_property.setRange(stepper_controller::constants::percent_min,stepper_controller::constants::percent_max);

  modular_server_.createProperty(constants::base_position_property_name,constants::base_position_default);

  modular_server::Property & pull_threshold_property = modular_server_.createProperty(constants::pull_threshold_property_name,constants::pull_threshold_default);
  pull_threshold_property.setRange(constants::pull_threshold_min,constants::pull_threshold_max);
  pull_threshold_property.attachPostSetValueFunctor(makeFunctor((Functor0 *)0,*this,&MouseJoystickController::updatePullThreshold));
 
  modular_server::Property & push_threshold_property = modular_server_.createProperty(constants::push_threshold_property_name,constants::push_threshold_default);
  push_threshold_property.setRange(constants::push_threshold_min,constants::push_threshold_max);

  modular_server::Property & joystick_ready_tone_frequency_property = modular_server_.createProperty(constants::joystick_ready_tone_frequency_property_name,constants::joystick_ready_tone_frequency_default);
  joystick_ready_tone_frequency_property.setRange(audio_controller::constants::frequency_min,audio_controller::constants::frequency_max);
  joystick_ready_tone_frequency_property.setUnits(audio_controller::constants::hz_units);

  modular_server::Property & joystick_ready_tone_duration_property = modular_server_.createProperty(constants::joystick_ready_tone_duration_property_name,constants::joystick_ready_tone_duration_default);
  joystick_ready_tone_duration_property.setRange(constants::joystick_ready_tone_duration_min,constants::joystick_ready_tone_duration_max);
  joystick_ready_tone_duration_property.setUnits(audio_controller::constants::ms_units);

  modular_server::Property & reward_tone_frequency_property = modular_server_.createProperty(constants::reward_tone_frequency_property_name,constants::reward_tone_frequency_default);
  reward_tone_frequency_property.setRange(audio_controller::constants::frequency_min,audio_controller::constants::frequency_max);
  reward_tone_frequency_property.setUnits(audio_controller::constants::hz_units);

  modular_server::Property & reward_tone_duration_property = modular_server_.createProperty(constants::reward_tone_duration_property_name,constants::reward_tone_duration_default);
  reward_tone_duration_property.setRange(constants::reward_tone_duration_min,constants::reward_tone_duration_max);
  reward_tone_duration_property.setUnits(audio_controller::constants::ms_units);

  modular_server::Property & tone_volume_property = modular_server_.createProperty(constants::tone_volume_property_name,constants::tone_volume_default);
  tone_volume_property.setRange(constants::tone_volume_min,constants::tone_volume_max);
  tone_volume_property.setUnits(audio_controller::constants::percent_units);

  modular_server::Property & lickport_reward_delay_property = modular_server_.createProperty(constants::lickport_reward_delay_property_name,constants::lickport_reward_delay_default);
  lickport_reward_delay_property.setRange(constants::lickport_reward_delay_min,constants::lickport_reward_delay_max);
  lickport_reward_delay_property.setUnits(power_switch_controller::constants::ms_units);

  modular_server::Property & trial_timeout_duration_property = modular_server_.createProperty(constants::trial_timeout_duration_property_name,constants::trial_timeout_duration_default);
  trial_timeout_duration_property.setRange(constants::trial_timeout_duration_min,constants::trial_timeout_duration_max);
  trial_timeout_duration_property.setUnits(constants::seconds_units);

  modular_server_.createProperty(constants::repeat_aborted_trial_property_name,constants::repeat_aborted_trial_default);

  modular_server::Property & repeat_set_count_property = modular_server_.createProperty(constants::repeat_set_count_property_name,constants::repeat_set_count_default);
  repeat_set_count_property.setRange(constants::repeat_set_count_min,constants::repeat_set_count_max);
  repeat_set_count_property.attachPostSetValueFunctor(makeFunctor((Functor0 *)0,*this,&MouseJoystickController::updateSetCount));

  modular_server::Property & start_trial_duration_property = modular_server_.createProperty(constants::start_trial_duration_property_name,constants::start_trial_duration_default);
  start_trial_duration_property.setRange(constants::start_trial_duration_min,constants::start_trial_duration_max);
  start_trial_duration_property.setUnits(constants::seconds_units);

  modular_server_.createProperty(constants::wait_until_trial_timing_data_read_property_name,constants::wait_until_trial_timing_data_read_default);

  // Parameters
  modular_server::Parameter & repeat_trial_count_parameter = modular_server_.createParameter(constants::repeat_trial_count_parameter_name);
  repeat_trial_count_parameter.setRange(constants::repeat_trial_count_min,constants::repeat_trial_count_max);

  modular_server::Parameter & pull_torque_parameter = modular_server_.createParameter(constants::pull_torque_parameter_name);
  pull_torque_parameter.setRange(constants::pull_torque_min,constants::pull_torque_max);
  pull_torque_parameter.setUnits(constants::percent_units);

  modular_server::Parameter & lickport_reward_duration_parameter = modular_server_.createParameter(constants::lickport_reward_duration_parameter_name);
  lickport_reward_duration_parameter.setRange(constants::lickport_reward_duration_min,constants::lickport_reward_duration_max);
  lickport_reward_duration_parameter.setUnits(constants::ms_units);

  modular_server::Parameter & reach_position_parameter = modular_server_.createParameter(constants::reach_position_parameter_name);
  reach_position_parameter.setRange(constants::reach_position_element_min,constants::reach_position_element_max);
  reach_position_parameter.setArrayLengthRange(constants::reach_position_length_min,constants::reach_position_length_max);

	modular_server::Parameter & lickport_activation_duration_parameter = modular_server_.createParameter(constants::lickport_activation_duration_parameter_name);
  lickport_activation_duration_parameter.setRange(constants::lickport_activation_duration_min,constants::lickport_activation_duration_max);

	modular_server::Parameter & lickport_activation_count_parameter = modular_server_.createParameter(constants::lickport_activation_count_parameter_name);
  lickport_activation_count_parameter.setRange(constants::lickport_activation_count_min,constants::lickport_activation_count_max);

  // Functions
  modular_server::Function & get_set_function = modular_server_.createFunction(constants::get_set_function_name);
  get_set_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&MouseJoystickController::getSetHandler));
  get_set_function.setResultTypeArray();

  modular_server::Function & clear_set_function = modular_server_.createFunction(constants::clear_set_function_name);
  clear_set_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&MouseJoystickController::clearSetHandler));

  modular_server::Function & get_block_count_function = modular_server_.createFunction(constants::get_block_count_function_name);
  get_block_count_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&MouseJoystickController::getBlockCountHandler));
  get_block_count_function.setResultTypeLong();

  modular_server::Function & add_block_to_set_function = modular_server_.createFunction(constants::add_block_to_set_function_name);
  add_block_to_set_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&MouseJoystickController::addBlockToSetHandler));
  add_block_to_set_function.addParameter(repeat_trial_count_parameter);
  add_block_to_set_function.addParameter(pull_torque_parameter);
  add_block_to_set_function.addParameter(lickport_reward_duration_parameter);
  add_block_to_set_function.addParameter(reach_position_parameter);
  add_block_to_set_function.setResultTypeObject();

  modular_server::Function & start_assay_function = modular_server_.createFunction(constants::start_assay_function_name);
  start_assay_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&MouseJoystickController::startAssayHandler));
  start_assay_function.setResultTypeBool();

  modular_server::Function & get_assay_status_function = modular_server_.createFunction(constants::get_assay_status_function_name);
  get_assay_status_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&MouseJoystickController::getAssayStatusHandler));
  get_assay_status_function.setResultTypeObject();

  modular_server::Function & move_joystick_to_base_position_function = modular_server_.createFunction(constants::move_joystick_to_base_position_function_name);
  move_joystick_to_base_position_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&MouseJoystickController::moveJoystickToBasePositionHandler));

  modular_server::Function & move_joystick_to_reach_position_function = modular_server_.createFunction(constants::move_joystick_to_reach_position_function_name);
  move_joystick_to_reach_position_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&MouseJoystickController::moveJoystickToReachPositionHandler));

  modular_server::Function & activate_lickport_function = modular_server_.createFunction(constants::activate_lickport_function_name);
  activate_lickport_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&MouseJoystickController::activateLickportHandler));
  activate_lickport_function.addParameter(lickport_activation_duration_parameter);
  activate_lickport_function.addParameter(lickport_activation_count_parameter);

  modular_server::Function & get_trial_timing_data_function = modular_server_.createFunction(constants::get_trial_timing_data_function_name);
  get_trial_timing_data_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&MouseJoystickController::getTrialTimingDataHandler));
  get_trial_timing_data_function.setResultTypeObject();

  // Callbacks
  modular_server::Callback & start_trial_callback = modular_server_.createCallback(constants::start_trial_callback_name);
  start_trial_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&MouseJoystickController::startTrialHandler));

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

  // Assay Status Setup
  resetAssayStatus();
  assay_status_.state_ptr = &constants::state_assay_not_started_string;
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
    assay_status_.unread_trial_timing_data = true;
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
  else if (state_ptr == &constants::state_wait_until_trial_timing_data_read_string)
  {
    assay_status_.state_ptr = &constants::state_waiting_until_trial_timing_data_read_string;
  }
  else if (state_ptr == &constants::state_waiting_until_trial_timing_data_read_string)
  {
    if (!assay_status_.unread_trial_timing_data)
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
    moveToBasePosition();
  }
  else if (state_ptr == &constants::state_moving_to_base_stop_string)
  {
    if (stageAtTargetPosition())
    {
      setIdleCurrent();
      assay_status_.state_ptr = &constants::state_assay_finished_string;
    }
  }
}

MouseJoystickController::set_t MouseJoystickController::getSet()
{
	return set_;
}

void MouseJoystickController::clearSet()
{
  if ((assay_status_.state_ptr == &constants::state_assay_not_started_string) ||
    (assay_status_.state_ptr == &constants::state_assay_finished_string))
  {
    set_.clear();
    assay_status_.block_count = getBlockCount();
    updateBlock();
  }
}

size_t MouseJoystickController::getBlockCount()
{
	return set_.size();
}

MouseJoystickController::block_t MouseJoystickController::addBlockToSet(block_t block)
{
  if (set_.full())
  {
    return dummy_block_;
  }
  if ((assay_status_.state_ptr == &constants::state_assay_not_started_string) ||
    (assay_status_.state_ptr == &constants::state_assay_finished_string))
  {
    set_.push_back(block);
    assay_status_.block_count = getBlockCount();
    updateBlock();
    return set_.back();
  }
  else
  {
    return dummy_block_;
  }
}

MouseJoystickController::assay_status_t MouseJoystickController::getAssayStatus()
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
    if (getBlockCount() > 0)
    {
      moveToReachPosition();
    }
  }
}

void MouseJoystickController::activateLickport(long duration,
  long count)
{
  if ((assay_status_.state_ptr == &constants::state_assay_not_started_string) ||
    (assay_status_.state_ptr == &constants::state_assay_finished_string))
  {
    triggerLickport(constants::activate_lickport_delay,duration,count);
  }
}

MouseJoystickController::trial_timing_data_t MouseJoystickController::getTrialTimingData()
{
  assay_status_.unread_trial_timing_data = false;

  return trial_timing_data_;
}

void MouseJoystickController::startTrial()
{
  if (assay_status_.state_ptr == &constants::state_waiting_to_start_trial_string)
  {
    if (timeIsSet())
    {
      trial_timing_data_.trial_start = getTime();
    }
    assay_status_.state_ptr = &constants::state_wait_for_mouse_ready_string;
  }
  else
  {
    startAssay();
  }
}

bool MouseJoystickController::startAssay()
{
  if ((assay_status_.state_ptr == &constants::state_assay_not_started_string) ||
    (assay_status_.state_ptr == &constants::state_assay_finished_string))
  {
    if (getBlockCount() > 0)
    {
      resetAssayStatus();
      assay_status_.state_ptr = &constants::state_assay_started_string;
      return true;
    }
  }
  return false;
}

void MouseJoystickController::abortTrial()
{
  stopAll();
  event_controller_.removeAllEvents();

  encoder_interface_simple_ptr_->callUntilSuccessful(encoder_interface_simple::constants::disable_outputs_callback_name);

  assay_status_.trial_aborted = true;
  if (timeIsSet())
  {
    trial_timing_data_.trial_abort = getTime();
  }

  triggerTrialTerminationPulse();

  assay_status_.state_ptr = &constants::state_retract_string;
}

void MouseJoystickController::abortAssay()
{
  assay_status_.assay_aborted = true;
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
  bool call_was_successful;

  encoder_interface_simple_ptr_->callUntilSuccessful(modular_server::constants::set_properties_to_defaults_function_name,
    modular_server::constants::all_array);
  setup_was_successful = setup_was_successful && encoder_interface_simple_ptr_->callWasSuccessful();

  power_switch_controller_ptr_->callUntilSuccessful(modular_server::constants::set_properties_to_defaults_function_name,
    modular_server::constants::all_array);
  setup_was_successful = setup_was_successful && power_switch_controller_ptr_->callWasSuccessful();
  call_was_successful = setupRewardPulse();
  setup_was_successful = setup_was_successful && call_was_successful;
  call_was_successful = setupTrialTerminationPulse();
  setup_was_successful = setup_was_successful && call_was_successful;

  audio_controller_ptr_->callUntilSuccessful(modular_server::constants::set_properties_to_defaults_function_name,
    modular_server::constants::all_array);
  setup_was_successful = setup_was_successful && audio_controller_ptr_->callWasSuccessful();
  call_was_successful = setupReadyPulse();
  setup_was_successful = setup_was_successful && call_was_successful;


  return setup_was_successful;
}

StageController::PositionArray MouseJoystickController::getBasePosition()
{
  StageController::PositionArray base_position_array;
  modular_server_.property(constants::base_position_property_name).getValue(base_position_array);

  return base_position_array;
}

void MouseJoystickController::resetAssayStatus()
{
	assay_status_t assay_status;
	assay_status_ = assay_status;
  updatePullThreshold();
  updateSetCount();
  assay_status_.block_count = getBlockCount();
  updateBlock();
}

void MouseJoystickController::setupAssay()
{
  if (assay_status_.state_ptr == &constants::state_assay_started_string)
  {
    encoder_interface_simple_ptr_->callUntilSuccessful(encoder_interface_simple::constants::disable_outputs_callback_name);
  }
}

void MouseJoystickController::setupTrial()
{
  resetTrialTimingData();
  assay_status_.trial_aborted = false;
  assay_status_.unread_trial_timing_data = false;
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
    if (timeIsSet())
    {
      trial_timing_data_.mouse_ready = getTime();
    }
    assay_status_.state_ptr = &constants::state_move_to_reach_string;
  }
}

void MouseJoystickController::setupPull()
{
  encoder_interface_simple_ptr_->callUntilSuccessful(encoder_interface_simple::constants::enable_outputs_callback_name);
  encoder_interface_simple_ptr_->callUntilSuccessful(encoder_interface_simple::constants::set_position_function_name,
    constants::pull_encoder_index,
    constants::pull_encoder_initial_value);

  long pull_torque = assay_status_.block.pull_torque;

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

  if (timeIsSet())
  {
    trial_timing_data_.joystick_ready = getTime();
  }

  playJoystickReadyTone();
  triggerReadyPulse();

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

  StaticJsonDocument<constants::ENCODER_POSITIONS_JSON_DOCUMENT_SIZE> json_document;
  JsonArray position_array = encoder_interface_simple_ptr_->callGetResult(json_document,encoder_interface_simple::constants::get_positions_function_name);
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
    ++assay_status_.successful_trial_count;
    if (timeIsSet())
    {
      trial_timing_data_.pull = getTime();
    }
    assay_status_.state_ptr = &constants::state_reward_string;
  }
  else if (position >= push_threshold)
  {
    event_controller_.remove(trial_timeout_event_id_);
    if (timeIsSet())
    {
      trial_timing_data_.push = getTime();
    }
    abortTrial();
  }
}

void MouseJoystickController::reward()
{
  playRewardTone();

  encoder_interface_simple_ptr_->callUntilSuccessful(encoder_interface_simple::constants::disable_outputs_callback_name);

  triggerLickportReward();
  triggerRewardPulse();
  triggerTrialTerminationPulse();

  assay_status_.state_ptr = &constants::state_retract_string;
}

void MouseJoystickController::checkTrialTermination()
{
  if (assay_status_.assay_aborted)
  {
    assay_status_.state_ptr = &constants::state_move_to_base_stop_string;
  }
  else
  {
    bool wait_until_trial_timing_data_read;
    modular_server_.property(constants::wait_until_trial_timing_data_read_property_name).getValue(wait_until_trial_timing_data_read);
    if (wait_until_trial_timing_data_read)
    {
      assay_status_.state_ptr = &constants::state_wait_until_trial_timing_data_read_string;
    }
    else
    {
      assay_status_.state_ptr = &constants::state_finish_trial_string;
    }
  }
}

void MouseJoystickController::finishTrial()
{
  assay_status_.state_ptr = &constants::state_move_to_base_start_string;
  ++assay_status_.finished_trial_count;

  bool repeat_aborted_trial;
  modular_server_.property(constants::repeat_aborted_trial_property_name).getValue(repeat_aborted_trial);

  if (!assay_status_.trial_aborted || !repeat_aborted_trial)
  {
    prepareNextTrial();
  }
}

void MouseJoystickController::prepareNextTrial()
{
  bool block_needs_updating = updateTrialBlockSet();
  if (block_needs_updating)
  {
    updateBlock();
  }
}

void MouseJoystickController::resetTrialTimingData()
{
  trial_timing_data_t ttd;
  trial_timing_data_ = ttd;
}

bool MouseJoystickController::updateTrialBlockSet()
{
  bool block_needs_updating = false;
  if (++assay_status_.trial_in_block >= assay_status_.block.repeat_trial_count)
  {
    assay_status_.trial_in_block = 0;
    block_needs_updating = true;

    if (++assay_status_.block_in_set >= assay_status_.block_count)
    {
      assay_status_.block_in_set = 0;

			if (++assay_status_.set_in_assay >= assay_status_.repeat_set_count)
      {
        assay_status_.set_in_assay = 0;
        block_needs_updating = false;

        assay_status_.state_ptr = &constants::state_move_to_base_stop_string;
      }
    }
  }
  return block_needs_updating;
}

void MouseJoystickController::updateBlock()
{
  if (assay_status_.block_in_set < assay_status_.block_count)
  {
    if (assay_status_.set_in_assay < assay_status_.repeat_set_count)
    {
      assay_status_.block = set_[assay_status_.block_in_set];
    }
  }
}

void MouseJoystickController::updatePullThreshold()
{
  long pull_threshold;
  modular_server_.property(constants::pull_threshold_property_name).getValue(pull_threshold);

  assay_status_.pull_threshold = pull_threshold;
}

void MouseJoystickController::updateSetCount()
{
  long repeat_set_count;
  modular_server_.property(constants::repeat_set_count_property_name).getValue(repeat_set_count);

  assay_status_.repeat_set_count = repeat_set_count;
}

void MouseJoystickController::moveToBasePosition()
{
  StageController::PositionArray base_position = getBasePosition();
  moveStageTo(base_position);
}

void MouseJoystickController::moveToReachPosition()
{
  StageController::PositionArray reach_position = assay_status_.block.reach_position;
  moveStageTo(reach_position);
}

void MouseJoystickController::playJoystickReadyTone()
{
  long joystick_ready_tone_frequency;
  modular_server_.property(constants::joystick_ready_tone_frequency_property_name).getValue(joystick_ready_tone_frequency);

  long joystick_ready_tone_duration;
  modular_server_.property(constants::joystick_ready_tone_duration_property_name).getValue(joystick_ready_tone_duration);

  long tone_volume;
  modular_server_.property(constants::tone_volume_property_name).getValue(tone_volume);

  audio_controller_ptr_->callUntilSuccessful(audio_controller::constants::add_tone_pwm_at_function_name,
    joystick_ready_tone_frequency,
    audio_controller::constants::speaker_all,
    tone_volume,
    constants::joystick_ready_tone_delay,
    joystick_ready_tone_duration,
    joystick_ready_tone_duration,
    constants::joystick_ready_tone_count);
}

void MouseJoystickController::playRewardTone()
{
  long reward_tone_frequency;
  modular_server_.property(constants::reward_tone_frequency_property_name).getValue(reward_tone_frequency);

  long reward_tone_duration;
  modular_server_.property(constants::reward_tone_duration_property_name).getValue(reward_tone_duration);

  long tone_volume;
  modular_server_.property(constants::tone_volume_property_name).getValue(tone_volume);

  audio_controller_ptr_->callUntilSuccessful(audio_controller::constants::add_tone_pwm_at_function_name,
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
  long lickport_reward_delay;
  modular_server_.property(constants::lickport_reward_delay_property_name).getValue(lickport_reward_delay);

  long duration = assay_status_.block.lickport_reward_duration;

  triggerLickport(lickport_reward_delay,duration,constants::lickport_reward_count);
}

void MouseJoystickController::triggerLickport(long delay,
  long duration,
  long count)
{
  Array<long,constants::LICKPORT_REWARD_CHANNEL_COUNT> lickport_channels(constants::lickport_reward_channels);
  power_switch_controller_ptr_->callUntilSuccessful(power_switch_controller::constants::add_pwm_function_name,
    lickport_channels,
    delay,
    duration*2,
    duration,
    count);
}

void MouseJoystickController::setHomeCurrent(size_t channel)
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

void MouseJoystickController::setIdleCurrent()
{
  long idle_current;
  for (size_t channel=0; channel < constants::CHANNEL_COUNT; ++channel)
  {
    modular_server_.property(constants::idle_current_property_name).getElementValue(channel,idle_current);

    modifyRunCurrent(channel,idle_current);
    modifyHoldCurrent(channel,idle_current);
  }
}

void MouseJoystickController::restoreCurrentSettings(size_t channel)
{
  restoreHoldCurrent(channel);
  restoreRunCurrent(channel);
}

bool MouseJoystickController::setupReadyPulse()
{
  audio_controller_ptr_->callUntilSuccessful(modular_server::constants::set_pin_mode_function_name,
    modular_device_base::constants::bnc_b_pin_name,
    modular_server::constants::pin_mode_pulse_rising);
  return audio_controller_ptr_->callWasSuccessful();
}

bool MouseJoystickController::triggerReadyPulse()
{
  audio_controller_ptr_->callUntilSuccessful(modular_server::constants::set_pin_value_function_name,
    modular_device_base::constants::bnc_b_pin_name,
    constants::pulse_duration);
  return audio_controller_ptr_->callWasSuccessful();
}

bool MouseJoystickController::setupRewardPulse()
{
  power_switch_controller_ptr_->callUntilSuccessful(modular_server::constants::set_pin_mode_function_name,
    modular_device_base::constants::bnc_b_pin_name,
    modular_server::constants::pin_mode_pulse_rising);
  return power_switch_controller_ptr_->callWasSuccessful();
}

bool MouseJoystickController::triggerRewardPulse()
{
  power_switch_controller_ptr_->callUntilSuccessful(modular_server::constants::set_pin_value_function_name,
    modular_device_base::constants::bnc_b_pin_name,
    constants::pulse_duration);
  return power_switch_controller_ptr_->callWasSuccessful();
}

bool MouseJoystickController::setupTrialTerminationPulse()
{
  power_switch_controller_ptr_->callUntilSuccessful(modular_server::constants::set_pin_mode_function_name,
    modular_device_base::constants::bnc_a_pin_name,
    modular_server::constants::pin_mode_pulse_rising);
  return power_switch_controller_ptr_->callWasSuccessful();
}

bool MouseJoystickController::triggerTrialTerminationPulse()
{
  power_switch_controller_ptr_->callUntilSuccessful(modular_server::constants::set_pin_value_function_name,
    modular_device_base::constants::bnc_a_pin_name,
    constants::pulse_duration);
  return power_switch_controller_ptr_->callWasSuccessful();
}

void MouseJoystickController::writeBlockToResponse(block_t block)
{
  modular_server_.response().beginObject();

  modular_server_.response().write(constants::repeat_trial_count_string,block.repeat_trial_count);
  modular_server_.response().write(constants::pull_torque_string,block.pull_torque);
  modular_server_.response().write(constants::lickport_reward_duration_string,block.lickport_reward_duration);
  modular_server_.response().write(constants::reach_position_string,block.reach_position);
  
  modular_server_.response().endObject();
}

void MouseJoystickController::getSetHandler()
{
	set_t set = getSet();

  modular_server_.response().writeResultKey();

	modular_server_.response().beginArray();

	for (auto& block : set)
  {
    writeBlockToResponse(block);
  }

  modular_server_.response().endArray();
}

void MouseJoystickController::clearSetHandler()
{
	clearSet();
}

void MouseJoystickController::getBlockCountHandler()
{
	long block_count = getBlockCount();
  modular_server_.response().returnResult(block_count);
}

void MouseJoystickController::addBlockToSetHandler()
{
	block_t block;
  modular_server_.parameter(constants::repeat_trial_count_parameter_name).getValue(block.repeat_trial_count);

  modular_server_.parameter(constants::pull_torque_parameter_name).getValue(block.pull_torque);

  modular_server_.parameter(constants::lickport_reward_duration_parameter_name).getValue(block.lickport_reward_duration);

  ArduinoJson::JsonArray reach_position;
  modular_server_.parameter(constants::reach_position_parameter_name).getValue(reach_position);

	for (JsonVariant value : reach_position)
  {
    block.reach_position.push_back(value);
  }

	block_t block_added = addBlockToSet(block);

  modular_server_.response().writeResultKey();
  writeBlockToResponse(block_added);
}

void MouseJoystickController::startAssayHandler()
{
  bool started = startAssay();
  modular_server_.response().returnResult(started);
}

void MouseJoystickController::getAssayStatusHandler()
{
	assay_status_t assay_status = getAssayStatus();

  modular_server_.response().writeResultKey();

  modular_server_.response().beginObject();

  modular_server_.response().write(constants::state_string,assay_status.state_ptr);
  modular_server_.response().write(constants::unread_trial_timing_data_string,assay_status.unread_trial_timing_data);
  modular_server_.response().write(constants::finished_trial_count_string,assay_status.finished_trial_count);
  modular_server_.response().write(constants::successful_trial_count_string,assay_status.successful_trial_count);
  modular_server_.response().write(constants::trial_aborted_string,assay_status.trial_aborted);
  modular_server_.response().write(constants::assay_aborted_string,assay_status.assay_aborted);
  modular_server_.response().write(constants::pull_threshold_string,assay_status.pull_threshold);
  modular_server_.response().write(constants::set_in_assay_string,assay_status.set_in_assay);
  modular_server_.response().write(constants::repeat_set_count_string,assay_status.repeat_set_count);
  modular_server_.response().write(constants::block_in_set_string,assay_status.block_in_set);
  modular_server_.response().write(constants::block_count_string,assay_status.block_count);
  modular_server_.response().write(constants::trial_in_block_string,assay_status.trial_in_block);
  modular_server_.response().writeKey(constants::block_string);
  writeBlockToResponse(assay_status.block);

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
  long lickport_activation_duration;
  modular_server_.parameter(constants::lickport_activation_duration_parameter_name).getValue(lickport_activation_duration);

  long lickport_activation_count;
  modular_server_.parameter(constants::lickport_activation_count_parameter_name).getValue(lickport_activation_count);

  activateLickport(lickport_activation_duration,lickport_activation_count);
}

void MouseJoystickController::getTrialTimingDataHandler()
{
	trial_timing_data_t trial_timing_data = getTrialTimingData();

  modular_server_.response().writeResultKey();

  modular_server_.response().beginObject();

  modular_server_.response().write(constants::trial_start_string,trial_timing_data.trial_start);
  modular_server_.response().write(constants::mouse_ready_string,trial_timing_data.mouse_ready);
  modular_server_.response().write(constants::joystick_ready_string,trial_timing_data.joystick_ready);
  modular_server_.response().write(constants::pull_string,trial_timing_data.pull);
  modular_server_.response().write(constants::push_string,trial_timing_data.push);
  modular_server_.response().write(constants::timeout_string,trial_timing_data.timeout);
  modular_server_.response().write(constants::trial_abort_string,trial_timing_data.trial_abort);

  modular_server_.response().endObject();
}

void MouseJoystickController::startTrialHandler(modular_server::Pin * pin_ptr)
{
  startTrial();
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
  startTrial();
}

void MouseJoystickController::trialTimeoutEventHandler(int arg)
{
  if (timeIsSet())
  {
    trial_timing_data_.timeout = getTime();
  }
  abortTrial();
}
