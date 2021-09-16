// ----------------------------------------------------------------------------
// MouseJoystickController.h
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#ifndef MOUSE_JOYSTICK_CONTROLLER_H
#define MOUSE_JOYSTICK_CONTROLLER_H
#include <ArduinoJson.h>
#include <JsonStream.h>
#include <Array.h>
#include <Vector.h>
#include <ConstantVariable.h>
#include <Functor.h>

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

  typedef mouse_joystick_controller::constants::Block block_t;
  typedef Array<block_t,
    mouse_joystick_controller::constants::BLOCK_COUNT_MAX> set_t;

	set_t getSet();
	void clearSet();
	size_t getBlockCount();
	block_t addBlockToSet(block_t block);

  typedef mouse_joystick_controller::constants::AssayStatus assay_status_t;
  assay_status_t getAssayStatus();

  void moveJoystickToBasePosition();
  void moveJoystickToReachPosition();
  void activateLickport(long duration,
    long count);

  typedef mouse_joystick_controller::constants::TrialTimingData trial_timing_data_t;
  trial_timing_data_t getTrialTimingData();

  void startTrial();
  bool startAssay();
  void abortTrial();
  void abortAssay();
  void restartAssay();

private:
  modular_server::Property properties_[mouse_joystick_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[mouse_joystick_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[mouse_joystick_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[mouse_joystick_controller::constants::CALLBACK_COUNT_MAX];

	set_t set_;
  block_t dummy_block_;

  assay_status_t assay_status_;
  EventController<mouse_joystick_controller::constants::EVENT_COUNT_MAX> event_controller_;
  EventId trial_timeout_event_id_;

  trial_timing_data_t trial_timing_data_;

  ModularClient * encoder_interface_simple_ptr_;
  ModularClient * power_switch_controller_ptr_;
  ModularClient * audio_controller_ptr_;

  unsigned long time_;
  unsigned long pull_push_poll_time_previous_;

  bool setupClients();

  StageController::PositionArray getBasePosition();

  void resetAssayStatus();

  void setupAssay();
  void setupTrial();
  void addStartTrialEvent();
  void checkForMouseReady();

  void setupPull();
  void checkForPullOrPush();

  void reward();
  void checkTrialTermination();
  void finishTrial();

  void prepareNextTrial();
  void resetTrialTimingData();
  bool updateTrialBlockSet();
  void updateBlock();
  void updatePullThreshold();
  void updateSetCount();
  void moveToBasePosition();
  void moveToReachPosition();
  void playJoystickReadyTone();
  void playRewardTone();
  void triggerLickportReward();
  void triggerLickport(long delay,
    long duration,
    long count);
  void setHomeCurrent(size_t channel);
  void setIdleCurrent();
  void restoreCurrentSettings(size_t channel);

  bool setupReadyPulse();
  bool triggerReadyPulse();
  bool setupRewardPulse();
  bool triggerRewardPulse();
  bool setupTrialTerminationPulse();
  bool triggerTrialTerminationPulse();

  void writeBlockToResponse(block_t block);

  // Handlers
  void getSetHandler();
  void clearSetHandler();
  void getBlockCountHandler();
  void addBlockToSetHandler();
  void startAssayHandler();
  void getAssayStatusHandler();
  void moveJoystickToBasePositionHandler();
  void moveJoystickToReachPositionHandler();
  void activateLickportHandler();
  void getTrialTimingDataHandler();
  void startTrialHandler(modular_server::Pin * pin_ptr);
  void abortTrialHandler(modular_server::Pin * pin_ptr);
  void abortAssayHandler(modular_server::Pin * pin_ptr);
  void restartAssayHandler(modular_server::Pin * pin_ptr);
  void startTrialEventHandler(int arg);
  void trialTimeoutEventHandler(int arg);

};

#endif
