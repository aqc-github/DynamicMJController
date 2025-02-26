# Mouse Joystick Controller - Torque Field Implementation

## Overview
This document describes the implementation of a viscous torque field in the Mouse Joystick Controller firmware. The torque field provides haptic feedback by applying resistance proportional to velocity on the encoded pull axis.

## Key Components

### Constants and Structures

```cpp
struct PullAxisConstants {
    static const int PULL_AXIS = 0; // Encoded pull axis
    static const long ENCODER_COUNTS_PER_REV = 4096;
    static const float MAX_TORQUE_CURRENT = 20; // mA
};

struct TorqueField {
    bool enabled = false;  
    float damping_coefficient = 1.0; // Ns/m
    long last_encoder_position = 0;
    long last_time = 0;
    const long MAX_FIELD_CURRENT = 20; // mA
    const long MIN_FIELD_CURRENT = 0;
    const long UPDATE_INTERVAL_US = 1000; // 1kHz update rate
    long next_update_time = 0;
};
```


### API Properties
- `torqueFieldEnabled`: Enable/disable the torque field
- `dampingCoefficient`: Set the viscous damping coefficient

## Implementation Details

### Torque Field Update
The `updateTorqueField()` function runs at 1kHz and:
1. Reads encoder position
2. Calculates velocity
3. Computes opposing force
4. Applies current to motor

```cpp
void MouseJoystickController::updateTorqueField() {
    if (!torque_field_.enabled) return;
    // Rate limiting to 1kHz
    long current_time = micros();
    if (current_time < torque_field_.next_update_time) return;
    // Get velocity from encoder
    long current_encoder_position;
    encoder_interface_simple_ptr_->callUntilSuccessful(
    encoder_interface_simple::constants::get_position_function_name,
    constants::pull_encoder_index,
    current_encoder_position);
    float dt = (current_time - torque_field_.last_time) / 1000000.0f;
    float velocity = (current_encoder_position - torque_field_.last_encoder_position) / dt;
    // Calculate and apply force
    float opposing_force = -torque_field_.damping_coefficient velocity;
    float current_scaling = 1.0f; // mA/(unit force)
    long desired_current = (long)(opposing_force current_scaling);
    // Apply with limits
    desired_current = constrain(desired_current,
                                torque_field_.MIN_FIELD_CURRENT,
                                torque_field_.MAX_FIELD_CURRENT);
    setMotorTorque(PullAxisConstants::PULL_AXIS, desired_current);
    // Update state
    torque_field_.last_encoder_position = current_encoder_position;
    torque_field_.last_time = current_time;
    torque_field_.next_update_time = current_time + torque_field_.UPDATE_INTERVAL_US;
}
```


### Motor Current Control

```cpp
void MouseJoystickController::setMotorTorque(int axis, long current) {
    if (axis != PullAxisConstants::PULL_AXIS) return;  // Safety check
    
    // Get base current setting
    long base_current;
    modular_server_.property(constants::run_current_property_name)
        .getElementValue(axis, base_current);
    
    // Add field current (with limits)
    long new_current = constrain(base_current + current,
                               constants::run_current_min,
                               constants::run_current_max);
                               
    // Update TMC2130 current
    setMotorCurrent(axis, new_current);
}
```

### Debugging

```cpp
void MouseJoystickController::debugTorqueField() {
    if (!torque_field_.enabled) {
        Serial.println("Torque field disabled");
        return;
    }
    
    // Get current encoder position
    long current_encoder_position;
    encoder_interface_simple_ptr_->callUntilSuccessful(
        encoder_interface_simple::constants::get_position_function_name,
        constants::pull_encoder_index,
        current_encoder_position);
    
    Serial.print("Encoder Position: ");
    Serial.print(current_encoder_position);
    
    // Get current motor current
    long current;
    modular_server_.property(constants::run_current_property_name)
        .getElementValue(PullAxisConstants::PULL_AXIS, current);
    
    Serial.print(" Current: ");
    Serial.print(current);
    Serial.println(" mA");
}
```

### Safety features:

```cpp
bool MouseJoystickController::checkEncoderHealth() {
    // Verify encoder is responding
    long position;
    bool success = encoder_interface_simple_ptr_->callUntilSuccessful(
        encoder_interface_simple::constants::get_position_function_name,
        constants::pull_encoder_index,
        position);
        
    if (!success) {
        torque_field_.enabled = false;  // Disable field if encoder fails
        return false;
    }
    return true;
}
```
- If the encoder fails, the torque field is disabled to prevent damage.




## Usage

1. Enable the torque field:

```cpp
torque_field_.enabled = true;
```

2. Set the damping coefficient:

```cpp
torque_field_.damping_coefficient = 1.0; // Ns/m
```


3. The torque field will automatically update during the main loop.

## Debugging
Use `debugTorqueField()` to monitor:
- Current encoder position
- Applied motor current

## Notes
- Only applies to the encoded pull axis (axis 0)
- Update rate: 1kHz
- Current limits: 0-20mA
- Requires calibration of current_scaling factor

## Future Improvements
1. Add different force field patterns
2. Implement calibration routines
3. Add position-dependent forces
4. Improve safety checks