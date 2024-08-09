#ifndef StepperController_h
#define StepperController_h

#include <Arduino.h>
#include <AccelStepper.h>


class StepperController: public AccelStepper{
    public:
        StepperController(uint8_t interface = AccelStepper::FULL4WIRE, uint8_t pin1 = 2, uint8_t pin2 = 3);
        void setSpeedAndLimitPositionOutOfRange(float speedx);
        void setLimitPositivePosition(unsigned long limitPosition);
        unsigned int getLimitPositivePosition();
        void setLimitNegativePosition(unsigned long limitPosition);
        unsigned int getLimitNegativePosition();
        void setDefaultSpeed(float defaultSpeed);
        unsigned int getDefaultSpeed();
        void setHome();
        void setSpeedWithPositionCondition(int targetPosition);
    private:
        unsigned long _limitPositivePosition;
        unsigned long _limitNegativePosition;
        float _defaultSpeed;
};

#endif