// ----------------------------------------------------------------------------
// MouseJoystick.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef MOUSE_JOYSTICK_H
#define MOUSE_JOYSTICK_H
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

#include <SPI.h>
#include <TMC429.h>
#include <TMC2130.h>
#include <EventController.h>

#include <ModularClient.h>
#include <EncoderInterfaceSimple.h>
#include <PowerSwitchController.h>

#include <ModularServer.h>
#include <ModularDeviceBase.h>
#include <StepDirController.h>
#include <StepperController.h>
#include <StageController.h>

#include "MouseJoystick/Constants.h"


class MouseJoystick : public StageController
{
public:
  MouseJoystick();
  virtual void setup();
  virtual void update();

  mouse_joystick::constants::AssayStatus getAssayStatus();
  StageController::PositionArray getBasePosition();
  StageController::PositionArray getReachPosition();

  void moveJoystickToBasePosition();
  void moveJoystickToReachPosition();

  void startTrial();
  void abort();

private:
  modular_server::Property properties_[mouse_joystick::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[mouse_joystick::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[mouse_joystick::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[mouse_joystick::constants::CALLBACK_COUNT_MAX];

  mouse_joystick::constants::AssayStatus assay_status_;
  EventController<mouse_joystick::constants::EVENT_COUNT_MAX> event_controller_;

  ModularClient * encoder_interface_simple_ptr_;
  ModularClient * power_switch_controller_ptr_;

  // Handlers
  void setClientPropertyValuesHandler();
  void getAssayStatusHandler();
  void moveJoystickToBasePositionHandler();
  void moveJoystickToReachPositionHandler();
  void startTrialHandler(modular_server::Interrupt * interrupt_ptr);
  void abortHandler(modular_server::Interrupt * interrupt_ptr);

};

#endif
