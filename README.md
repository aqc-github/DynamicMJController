# MouseJoystickController

Authors:

    Peter Polidoro <polidorop@janelia.hhmi.org>

License:

    BSD

[Examples](./examples)

## Ancestors

[ModularServer](https://github.com/janelia-arduino/ModularServer)

[ModularDeviceBase](https://github.com/janelia-arduino/ModularDeviceBase)

[StepDirController](https://github.com/janelia-arduino/StepDirController)

[StepperController](https://github.com/janelia-arduino/StepperController)

[StageController](https://github.com/janelia-arduino/StageController)

## Clients

[EncoderInterfaceSimple](https://github.com/janelia-arduino/EncoderInterfaceSimple)

[PowerSwitchController](https://github.com/janelia-arduino/PowerSwitchController)

[AudioController](https://github.com/janelia-arduino/AudioController)

## Devices

[modular_device_base](https://github.com/janelia-modular-devices/modular_device_base.git)

[stepper_controller](https://github.com/janelia-modular-devices/stepper_controller.git)

[encoder_interface_simple](https://github.com/janelia-modular-devices/encoder_interface_simple.git)

[power_switch_controller](https://github.com/janelia-modular-devices/power_switch_controller.git)

[audio_controller](https://github.com/janelia-modular-devices/audio_controller.git)

## API NAMES

```json
{
  "id": "getApi",
  "result": {
    "firmware": [
      "MouseJoystickController"
    ],
    "verbosity": "NAMES",
    "functions": [
      "setClientPropertyValues",
      "getAssayStatus",
      "moveJoystickToBasePosition",
      "moveJoystickToReachPosition"
    ],
    "properties": [
      "basePosition",
      "reachPosition0",
      "reachPosition1Means",
      "pullThreshold",
      "pushThreshold",
      "pullTorqueMeans",
      "readyToneFrequency",
      "readyToneDuration",
      "rewardToneFrequency",
      "rewardToneDuration",
      "rewardSolenoidDelay",
      "rewardSolenoidDuration",
      "trialTimeoutDuration",
      "repeatAbortedTrial",
      "trialCount",
      "setCount"
    ],
    "callbacks": [
      "startTrial",
      "startAssay",
      "abortTrial",
      "abortAssay",
      "restartAssay"
    ]
  }
}
```

## API GENERAL

[API GENERAL](./api.json)

## More Detailed Modular Device Information

[modular-devices](https://github.com/janelia-modular-devices/modular-devices)

## Install Library Dependencies

[arduino-libraries](https://github.com/janelia-arduino/arduino-libraries)
