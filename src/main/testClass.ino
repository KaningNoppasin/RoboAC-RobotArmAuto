#include <AccelStepper.h>
#include "./init_IO.h"
#include "StepperController.h"

#define Mode 1

StepperController stepperJoint1(Mode, PUL_Joint1, DIR_Joint1);
StepperController stepperJoint2(Mode, PUL_Joint2, DIR_Joint2);
StepperController stepperJoint3(Mode, PUL_Joint3, DIR_Joint3);
StepperController stepperJoint4(Mode, PUL_Joint4, DIR_Joint4);

double maxSpeed = 10000;
double defaultSpeed = 10000;
double acceleration = 3000;

void setSpeedAllStepper(double speedJ1, double speedJ2, double speedJ3, double speedJ4){
        stepperJoint1.setSpeedAndLimitPositionOutOfRange(speedJ1);
        stepperJoint2.setSpeedAndLimitPositionOutOfRange(speedJ2);
        stepperJoint3.setSpeedAndLimitPositionOutOfRange(speedJ3);
        stepperJoint4.setSpeedAndLimitPositionOutOfRange(speedJ4);
}

void getCurrentSpeed(){
    Serial.print("speedJ1 :");Serial.print(stepperJoint1.speed());
    Serial.print("\tspeedJ2 :");Serial.print(stepperJoint2.speed());
    Serial.print("\tspeedJ3 :");Serial.print(stepperJoint3.speed());
    Serial.print("\tspeedJ4 :");Serial.println(stepperJoint4.speed());
}

void getInputValue(){
    Serial.print("SWJ1UP :");Serial.print(digitalRead(SwitchJoint1UP));
    Serial.print("\tSWJ1DOWN :");Serial.print(digitalRead(SwitchJoint1DOWN));
    Serial.print("\tSWJ2UP :");Serial.print(digitalRead(SwitchJoint2UP));
    Serial.print("\tSWJ2DOWN :");Serial.print(digitalRead(SwitchJoint2DOWN));
    Serial.print("\tSWJ3UP :");Serial.print(digitalRead(SwitchJoint3UP));
    Serial.print("\tSWJ3DOWN :");Serial.print(digitalRead(SwitchJoint3DOWN));
    Serial.print("\tSWJ4UP :");Serial.print(digitalRead(SwitchJoint4UP));
    Serial.print("\tSWJ4DOWN :");Serial.println(digitalRead(SwitchJoint4DOWN));
}


void setup()
{
	Serial.begin(115200);

    Serial.println("Robot !!!");
    for (int i = 0; i < sizeof(pinIN) / sizeof(pinIN[0]) ; i++) pinMode(pinIN[i], INPUT_PULLUP);
    stepperJoint4.setLimitPositivePosition(1500);
    stepperJoint4.setLimitNegativePosition(500);

}

void loop()
{
    delay(1);
    if (Serial.available() > 0){
        String data = Serial.readStringUntil('\n');
        Serial.println(data);
        if (data == "Home"){
            Serial.println("run condition");
            stepperJoint1.setHome();
            stepperJoint2.setHome();
            stepperJoint3.setHome();
            stepperJoint4.setHome();
        }
    }
    // getInputValue();
	// if (!digitalRead(SwitchJoint1UP)) setSpeedAllStepper(defaultSpeed, 0, 0, 0);
	// else if (!digitalRead(SwitchJoint1DOWN)) setSpeedAllStepper(-defaultSpeed, 0, 0, 0);
	// else if (!digitalRead(SwitchJoint2UP)) setSpeedAllStepper(0, defaultSpeed, 0, 0);
	// else if (!digitalRead(SwitchJoint2DOWN)) setSpeedAllStepper(0, -defaultSpeed, 0, 0);
	// else if (!digitalRead(SwitchJoint3UP)) setSpeedAllStepper(0, 0, defaultSpeed, 0);
	// else if (!digitalRead(SwitchJoint3DOWN)) setSpeedAllStepper(0, 0, -defaultSpeed, 0);
	// else if (!digitalRead(SwitchJoint4UP)) setSpeedAllStepper(0, 0, 0, defaultSpeed);
	// else if (!digitalRead(SwitchJoint4DOWN)) setSpeedAllStepper(0, 0, 0, -defaultSpeed);
    // else setSpeedAllStepper(0, 0, 0, 0);

    if (!digitalRead(SwitchJoint1UP)) stepperJoint1.setSpeedAndLimitPositionOutOfRange(defaultSpeed);
	else if (!digitalRead(SwitchJoint1DOWN)) stepperJoint1.setSpeedAndLimitPositionOutOfRange(-defaultSpeed);
	else if (!digitalRead(SwitchJoint2UP)) stepperJoint2.setSpeedAndLimitPositionOutOfRange(defaultSpeed);
	else if (!digitalRead(SwitchJoint2DOWN)) stepperJoint2.setSpeedAndLimitPositionOutOfRange(-defaultSpeed);
	else if (!digitalRead(SwitchJoint3UP)) stepperJoint3.setSpeedAndLimitPositionOutOfRange(defaultSpeed);
	else if (!digitalRead(SwitchJoint3DOWN)) stepperJoint3.setSpeedAndLimitPositionOutOfRange(-defaultSpeed);
	else if (!digitalRead(SwitchJoint4UP)) stepperJoint4.setSpeedAndLimitPositionOutOfRange(defaultSpeed);
	else if (!digitalRead(SwitchJoint4DOWN)) stepperJoint4.setSpeedAndLimitPositionOutOfRange(-defaultSpeed);
    else setSpeedAllStepper(0, 0, 0, 0);

    stepperJoint1.runSpeed();
    stepperJoint2.runSpeed();
    stepperJoint3.runSpeed();
    stepperJoint4.runSpeed();

}