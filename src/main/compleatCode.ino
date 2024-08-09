#include <AccelStepper.h>
#include <MultiStepper.h>
#include "./init_IO.h"
#include "StepperController.h"

#define Mode 1

StepperController stepperJoint1(Mode, PUL_Joint1, DIR_Joint1);
StepperController stepperJoint2(Mode, PUL_Joint2, DIR_Joint2);
StepperController stepperJoint3(Mode, PUL_Joint3, DIR_Joint3);
StepperController stepperJoint4(Mode, PUL_Joint4, DIR_Joint4);

double maxSpeed = 500;
// double defaultSpeed = 500;
double defaultSpeed = 5000;
double acceleration = 3000;

double limitPosition = 5000;

// Variables for PID control
double previousError1 = 0, integral1 = 0;
double previousError2 = 0, integral2 = 0;
double previousError3 = 0, integral3 = 0;
double previousError4 = 0, integral4 = 0;

void getInputValue()
{
    for (int i = 0; i < sizeof(pinIN) / sizeof(pinIN[0]); i++)
    {
        Serial.print(" Index");
        Serial.print(i);
        Serial.print(" :");
        Serial.print(digitalRead(pinIN[i]));
    }
    Serial.println();
}
void getCurrentPosition()
{
    Serial.print(" J1 :");
    Serial.print(stepperJoint1.currentPosition());
    Serial.print(" J2 :");
    Serial.print(stepperJoint2.currentPosition());
    Serial.print(" J3 :");
    Serial.print(stepperJoint3.currentPosition());
    Serial.print(" J4 :");
    Serial.println(stepperJoint4.currentPosition());
}

void moveToTagetPosition(int targetJ1, int targetJ2, int targetJ3, int targetJ4)
{
    while (
        stepperJoint1.currentPosition() != targetJ1 ||
        stepperJoint2.currentPosition() != targetJ2 ||
        stepperJoint3.currentPosition() != targetJ3 ||
        stepperJoint4.currentPosition() != targetJ4)
    {
        delay(1);
        stepperJoint1.setSpeedWithPositionCondition(targetJ1);
        stepperJoint2.setSpeedWithPositionCondition(targetJ2);
        stepperJoint3.setSpeedWithPositionCondition(targetJ3);
        stepperJoint4.setSpeedWithPositionCondition(targetJ4);

        stepperJoint1.runSpeed();
        stepperJoint2.runSpeed();
        stepperJoint3.runSpeed();
        stepperJoint4.runSpeed();
    }
}

void setup()
{
    Serial.begin(115200);

    Serial.println("Robot !!!");
    for (int i = 0; i < sizeof(pinIN) / sizeof(pinIN[0]); i++)
        pinMode(pinIN[i], INPUT_PULLUP);
    stepperJoint1.setMaxSpeed(5000);
    stepperJoint2.setMaxSpeed(5000);
    stepperJoint3.setMaxSpeed(5000);
    stepperJoint4.setMaxSpeed(5000);

    stepperJoint1.setAcceleration(1000);
    stepperJoint2.setAcceleration(1000);
    stepperJoint3.setAcceleration(1000);
    stepperJoint4.setAcceleration(1000);
}

void loop()
{
    // 0_0_0_6200_
    // 0_3000_5000_6200_
    // 0_3500_14000_6200_
    // 0_3000_5000_6200_
    // getInputValue();
    getCurrentPosition();
    delay(1);
    if (Serial.available() > 0)
    {

        String type = Serial.readStringUntil('\n');
        if (type == "moveToTagetPosition")
        {
            Serial.println(" >> moveToTagetPosition");
            Serial.read();
            while (true)
            {
                if (Serial.available() > 0)
                {
                    int targetJ1 = Serial.readStringUntil('_').toInt();
                    int targetJ2 = Serial.readStringUntil('_').toInt();
                    int targetJ3 = Serial.readStringUntil('_').toInt();
                    int targetJ4 = Serial.readStringUntil('_').toInt();
                    moveToTagetPosition(targetJ1, targetJ2, targetJ3, targetJ4);
                    // moveToPosition(targetJ1, targetJ2, targetJ3, targetJ4);
                    break;
                }
            }
        }
        else if (type == "test")
        {
            // moveToTagetPosition(0, 0, 0, 0);
            moveToTagetPosition(0, 1500, 3100, 3100);
            moveToTagetPosition(0, 3500, 14000, 5600);
            delay(1000);
            moveToTagetPosition(0, 1500, 7000, 5600);
            moveToTagetPosition(0, 3500, 7500, 0);
            // moveToTagetPosition(0, 7100, 11100, -3600);
            moveToTagetPosition(0, 5500, 9500, -2000);
            delay(1000);
            moveToTagetPosition(0, 6300, 11100, 500);
            // delay(500);
            delay(2000);
            moveToTagetPosition(0, 0, 0, 0);
        }
        else if (type == "home")
        {
            moveToTagetPosition(0, 0, 0, 0);
        }
        else
        {
            Serial.read();
        }
    }

    // TODO : This is for test with out limmit

    // if (!digitalRead(SwitchJoint1UP))
    //     stepperJoint1.setSpeed(-defaultSpeed);
    // else if (!digitalRead(SwitchJoint1DOWN))
    //     stepperJoint1.setSpeed(defaultSpeed);
    // else
    //     stepperJoint1.setSpeed(0);

    // if (!digitalRead(SwitchJoint2UP))
    //     stepperJoint2.setSpeed(defaultSpeed);
    // else if (!digitalRead(SwitchJoint2DOWN))
    //     stepperJoint2.setSpeed(-defaultSpeed);
    // else
    //     stepperJoint2.setSpeed(0);

    // if (!digitalRead(SwitchJoint3UP))
    //     stepperJoint3.setSpeed(-defaultSpeed);
    // else if (!digitalRead(SwitchJoint3DOWN))
    //     stepperJoint3.setSpeed(defaultSpeed);
    // else
    //     stepperJoint3.setSpeed(0);

    // if (!digitalRead(SwitchJoint4UP))
    //     stepperJoint4.setSpeed(-defaultSpeed);
    // else if (!digitalRead(SwitchJoint4DOWN))
    //     stepperJoint4.setSpeed(defaultSpeed);
    // else
    //     stepperJoint4.setSpeed(0);

    stepperJoint1.runSpeed();
    stepperJoint2.runSpeed();
    stepperJoint3.runSpeed();
    stepperJoint4.runSpeed();
}