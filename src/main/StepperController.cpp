#include <Arduino.h>
#include "StepperController.h"

// int StepperController::_limitPosition = 1000;

StepperController::StepperController(uint8_t interface, uint8_t pin1, uint8_t pin2) : AccelStepper(interface, pin1, pin2) {
    this->_limitPositivePosition = 1000;
    this->_limitNegativePosition = 1000;
    this->_defaultSpeed = 10000;
    setMaxSpeed(10000);
    setAcceleration(3000);
}

/**
 * The function `setSpeedAndLimitPositionOutOfRange` sets the speed of a stepper motor to 0 if it
 * reaches the positive or negative position limits.
 * 
 * @param speedx The `speedx` parameter in the `setSpeedAndLimitPositionOutOfRange` function represents
 * the desired speed that you want to set for the stepper motor. The function checks if the current
 * position of the stepper motor is beyond the positive or negative limit positions and adjusts the
 * speed accordingly. If the current position
 */
void StepperController::setSpeedAndLimitPositionOutOfRange(float speedx){
    // if (this->currentPosition() >= this->_limitPosition && this->speed() > 0) this->setSpeed(0);
    // else if (this->currentPosition() <= -this->_limitPosition && this->speed() < 0) this->setSpeed(0);
    if (this->currentPosition() >= this->_limitPositivePosition && speedx > 0) this->setSpeed(0);
    else if (this->currentPosition() <= -this->_limitNegativePosition && speedx < 0) this->setSpeed(0);
    else this->setSpeed(speedx);
}

void StepperController::setLimitPositivePosition(unsigned long limitPositivePosition) {
    this->_limitPositivePosition = limitPositivePosition;
}

unsigned int StepperController::getLimitPositivePosition(){
    return this->_limitPositivePosition;
}

void StepperController::setLimitNegativePosition(unsigned long limitNegativePosition) {
    this->_limitNegativePosition = limitNegativePosition;
}

unsigned int StepperController::getLimitNegativePosition(){
    return this->_limitNegativePosition;
}

void StepperController::setDefaultSpeed(float defaultSpeed) {
    this->_defaultSpeed = defaultSpeed;
}

unsigned int StepperController::getDefaultSpeed(){
    return this->_defaultSpeed;
}

/**
 * The `setHome` function in the `StepperController` class sets the stepper motor to its home position
 * by adjusting the speed until the current position is zero.
 */
void StepperController::setHome(){
    if (this->currentPosition() > 0) this->setSpeed(-this->_defaultSpeed);
    else if (this->currentPosition() < 0) this->setSpeed(this->_defaultSpeed);

    while (this->currentPosition() != 0){
        // The delay statements introduced within the loop provide pauses to ensure that the motor has time to reach the desired position.
        delay(1);
        this->runSpeed();
    }

    this->setSpeed(0);
}

void StepperController::setSpeedWithPositionCondition(int targetPosition){
    // this->_defaultSpeed = map(abs(this->currentPosition() - targetPosition), 0, 50000, 500, 5000);
    if (this->currentPosition() > targetPosition){
        this->setSpeed(-this->_defaultSpeed);
    }
    else if(this->currentPosition() < targetPosition){
        this->setSpeed(this->_defaultSpeed);
    }
    else{
        this->setSpeed(0);
    }
}