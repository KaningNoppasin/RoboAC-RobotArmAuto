#include <AccelStepper.h>
#include <MultiStepper.h>
#include "./init_IO.h"
#include "StepperController.h"

#define Mode 1

StepperController stepperJoint1(Mode, PUL_Joint1, DIR_Joint1);
StepperController stepperJoint2(Mode, PUL_Joint2, DIR_Joint2);
StepperController stepperJoint3(Mode, PUL_Joint3, DIR_Joint3);
StepperController stepperJoint4(Mode, PUL_Joint4, DIR_Joint4);
StepperController stepperJoint5(Mode, PUL_Joint5, DIR_Joint5);

double maxSpeed = 5000;
// double defaultSpeed = 500;
double defaultSpeed = 5000;
double acceleration = 1000;

double limitPosition = 5000;

void getCurrentPosition()
{
    Serial.print(" J1 :");
    Serial.print(stepperJoint1.currentPosition());
    Serial.print(" J2 :");
    Serial.print(stepperJoint2.currentPosition());
    Serial.print(" J3 :");
    Serial.print(stepperJoint3.currentPosition());
    Serial.print(" J4 :");
    Serial.print(stepperJoint4.currentPosition());
    Serial.print(" J5 :");
    Serial.println(stepperJoint5.currentPosition());
}

void moveToTagetPosition(int targetJ1, int targetJ2, int targetJ3, int targetJ4, int targetJ5)
{
    while (
        stepperJoint1.currentPosition() != targetJ1 ||
        stepperJoint2.currentPosition() != targetJ2 ||
        stepperJoint3.currentPosition() != targetJ3 ||
        stepperJoint4.currentPosition() != targetJ4 ||
        stepperJoint5.currentPosition() != targetJ5)
    {
        delay(1);
        stepperJoint1.setSpeedWithPositionCondition(targetJ1);
        stepperJoint2.setSpeedWithPositionCondition(targetJ2);
        stepperJoint3.setSpeedWithPositionCondition(targetJ3);
        stepperJoint4.setSpeedWithPositionCondition(targetJ4);
        stepperJoint5.setSpeedWithPositionCondition(targetJ5);

        stepperJoint1.runSpeed();
        stepperJoint2.runSpeed();
        stepperJoint3.runSpeed();
        stepperJoint4.runSpeed();
        stepperJoint5.runSpeed();
    }
}

void setup()
{
    Serial.begin(115200);

    Serial.println("Robot !!!");
    stepperJoint1.setMaxSpeed(maxSpeed);
    stepperJoint2.setMaxSpeed(maxSpeed);
    stepperJoint3.setMaxSpeed(maxSpeed);
    stepperJoint4.setMaxSpeed(maxSpeed);

    stepperJoint1.setAcceleration(acceleration);
    stepperJoint2.setAcceleration(acceleration);
    stepperJoint3.setAcceleration(acceleration);
    stepperJoint4.setAcceleration(acceleration);
}

void loop()
{
    // 0_0_0_6200_
    // 0_3000_5000_6200_
    // 0_3500_14000_6200_
    // 0_3000_5000_6200_
    /*
0_0_0_0_0_
0_0_-1500_3100_3100_
0_0_-3500_14000_5600_
0_0_-1500_7000_5600_
0_0_-3500_7500_0_
    */
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
                    int targetJ5 = Serial.readStringUntil('_').toInt();
                    // Serial.println(" >> targetJ5: " + String(targetJ5));
                    moveToTagetPosition(targetJ1, targetJ2, targetJ3, targetJ4, targetJ5);
                    // * for test
                    // moveToTagetPosition(targetJ2, targetJ3, targetJ1, targetJ4, targetJ5);
                    break;
                }
            }
        }
        else if (type == "test")
        {
            // moveToTagetPosition(0, 0, 0, 0);
            moveToTagetPosition(0, 0, -1500, 3100, 3100);
            moveToTagetPosition(0, 0, -3500, 14000, 5600);
            delay(1000);
            moveToTagetPosition(0, 0, -1500, 7000, 5600);
            moveToTagetPosition(0, 0, -3500, 7500, 0);
            // moveToTagetPosition(0, 7100, 11100, -3600);
            moveToTagetPosition(0, 0, -5500, 9500, -2000);
            delay(1000);
            moveToTagetPosition(0, 0, -6300, 11100, 500);
            // delay(500);
            delay(2000);
            moveToTagetPosition(0, 0, 0, 0, 0);
        }
        else if (type == "home")
        {
            moveToTagetPosition(0, 0, 0, 0, 0);
        }
        else
        {
            Serial.read();
        }
    }

    // stepperJoint1.runSpeed();
    // stepperJoint2.runSpeed();
    // stepperJoint3.runSpeed();
    // stepperJoint4.runSpeed();
    // stepperJoint5.runSpeed();
}