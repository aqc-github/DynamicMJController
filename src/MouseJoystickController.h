// ----------------------------------------------------------------------------
// MouseJoystickController.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef MOUSE_JOYSTICK_CONTROLLER_H
#define MOUSE_JOYSTICK_CONTROLLER_H
#include <Flash.h>
#include <EEPROM.h>
#include <Streaming.h>
#include <ArduinoJson.h>
#include <JsonSanitizer.h>
#include <JsonStream.h>
#include <Array.h>
#include <Vector.h>
#include <MemoryFree.h>
#include <ConstantVariable.h>
#include <SavedVariable.h>
#include <Functor.h>
#include <IndexedContainer.h>
#include <FunctorCallbacks.h>
#include <Watchdog.h>

#include <SPI.h>
#include <TMC429.h>
#include <TMC2130.h>
#include <EventController.h>

#include <ModularClient.h>
#include <EncoderInterfaceSimple.h>
#include <PowerSwitchController.h>
#include <AudioController.h>

#include <ModularServer.h>
#include <ModularDeviceBase.h>
#include <StepDirController.h>
#include <StepperController.h>
#include <StageController.h>

#include "MouseJoystickController/Constants.h"


class MouseJoystickController : public StageController
{
public:
  MouseJoystickController();
  virtual void setup();
  virtual void update();

  mouse_joystick_controller::constants::AssayStatus getAssayStatus();
  StageController::PositionArray getBasePosition();
  StageController::PositionArray getReachPosition();
  long getPullTorque();

  void moveJoystickToBasePosition();
  void moveJoystickToReachPosition();
  void activateLickport(const long count);

  void setupAssay();
  void startTrial();
  void startAssay();
  void abortTrial();
  void abortAssay();
  void restartAssay();

  void setupTrial();
  void checkForStartTrial();

  void setupPull();
  void checkForPullOrPush();

  void reward();
  void finishTrial();

private:
  modular_server::Property properties_[mouse_joystick_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[mouse_joystick_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[mouse_joystick_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[mouse_joystick_controller::constants::CALLBACK_COUNT_MAX];

  mouse_joystick_controller::constants::AssayStatus assay_status_;
  EventController<mouse_joystick_controller::constants::EVENT_COUNT_MAX> event_controller_;
  EventId trial_timeout_event_id_;

  ModularClient * encoder_interface_simple_ptr_;
  ModularClient * power_switch_controller_ptr_;
  ModularClient * audio_controller_ptr_;

  bool trial_aborted_;
  bool assay_aborted_;
  size_t reach_position_1_index_;
  size_t pull_torque_index_;

  void updateReachPosition();
  void updatePullTorque();
  void moveToBasePosition();
  void moveToReachPosition();
  void playReadyTone();
  void playRewardTone();
  void triggerLickportReward();
  void triggerLickport(const long delay, const long count);

  // Handlers
  void setClientPropertyValuesHandler();
  void getAssayStatusHandler();
  void moveJoystickToBasePositionHandler();
  void moveJoystickToReachPositionHandler();
  void activateLickportHandler();
  void startTrialHandler(modular_server::Interrupt * interrupt_ptr);
  void startAssayHandler(modular_server::Interrupt * interrupt_ptr);
  void abortTrialHandler(modular_server::Interrupt * interrupt_ptr);
  void abortAssayHandler(modular_server::Interrupt * interrupt_ptr);
  void restartAssayHandler(modular_server::Interrupt * interrupt_ptr);
  void trialTimeoutHandler(int arg);

};

#endif
