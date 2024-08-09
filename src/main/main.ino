#include <AccelStepper.h>
#include "./init_IO.h"

#define Mode 1

AccelStepper stepperJoint1(Mode, PUL_Joint1, DIR_Joint1);
AccelStepper stepperJoint2(Mode, PUL_Joint2, DIR_Joint2);
AccelStepper stepperJoint3(Mode, PUL_Joint3, DIR_Joint3);
AccelStepper stepperJoint4(Mode, PUL_Joint4, DIR_Joint4);

int limitPositionJoint1 = 1000;
int limitPositionJoint2 = 1000;
int limitPositionJoint3 = 1000;
int limitPositionJoint4 = 1000;


double maxSpeed = 10000;
double defaultSpeed = 10000;
double acceleration = 3000;

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

void initStepperMotor(AccelStepper &StepperMotor, double MaxSpeed, double Acceleration)
{
	// setMaxSpeed => step per sec.
	StepperMotor.setMaxSpeed(MaxSpeed);

	// setAcceleration => step per sec^2.
	StepperMotor.setAcceleration(Acceleration);
}

void checkSpeedWithCurrentPosition(double speedJ1, double speedJ2, double speedJ3, double speedJ4){
    // Serial.print("PositionJoint1 :");Serial.print(stepperJoint1.currentPosition());
    // Serial.print("\t PositionJoint2 :");Serial.print(stepperJoint2.currentPosition());
    // Serial.print("\t PositionJoint3 :");Serial.print(stepperJoint3.currentPosition());
    Serial.print("\t PositionJoint4 :");Serial.println(stepperJoint4.currentPosition());

    if (stepperJoint1.currentPosition() >= limitPositionJoint1 && speedJ1 > 0) {
        stepperJoint1.setSpeed(0);
    }
    else if (stepperJoint1.currentPosition() <= -limitPositionJoint1 && speedJ1 < 0) {
        stepperJoint1.setSpeed(0);
    }

    if (stepperJoint2.currentPosition() >= limitPositionJoint2 && speedJ2 > 0) {
        stepperJoint2.setSpeed(0);
    }
    else if (stepperJoint2.currentPosition() <= -limitPositionJoint2 && speedJ2 < 0) {
        stepperJoint2.setSpeed(0);
    }

    if (stepperJoint3.currentPosition() >= limitPositionJoint3 && speedJ3 > 0) {
        stepperJoint3.setSpeed(0);
    }
    else if (stepperJoint3.currentPosition() <= -limitPositionJoint3 && speedJ3 < 0) {
        stepperJoint3.setSpeed(0);
    }

    if (stepperJoint4.currentPosition() >= limitPositionJoint4 && speedJ4 > 0) {
        stepperJoint4.setSpeed(0);
    }
    else if (stepperJoint4.currentPosition() <= -limitPositionJoint4 && speedJ4 < 0) {
        stepperJoint4.setSpeed(0);
    }

    // if (stepperJoint1.currentPosition() >= limitPositionJoint1 || stepperJoint1.currentPosition() <= -limitPositionJoint1) stepperJoint1.setSpeed(0);
    // if (stepperJoint2.currentPosition() >= limitPositionJoint2 || stepperJoint2.currentPosition() <= -limitPositionJoint2) stepperJoint2.setSpeed(0);
    // if (stepperJoint3.currentPosition() >= limitPositionJoint3 || stepperJoint3.currentPosition() <= -limitPositionJoint3) stepperJoint3.setSpeed(0);
    // if (stepperJoint4.currentPosition() >= limitPositionJoint4 || stepperJoint4.currentPosition() <= -limitPositionJoint4) stepperJoint4.setSpeed(0);
}

void setSpeedAllStepper(double speedJ1, double speedJ2, double speedJ3, double speedJ4){
        stepperJoint1.setSpeed(speedJ1);
		stepperJoint2.setSpeed(speedJ2);
		stepperJoint3.setSpeed(speedJ3);
		stepperJoint4.setSpeed(speedJ4);
        checkSpeedWithCurrentPosition(speedJ1, speedJ2, speedJ3, speedJ4);
        // Serial.print("speedJ1 :");Serial.print(speedJ1);
        // Serial.print("\tspeedJ2 :");Serial.print(speedJ2);
        // Serial.print("\tspeedJ3 :");Serial.print(speedJ3);
        // Serial.print("\tspeedJ4 :");Serial.println(speedJ4);
}

void setHome(AccelStepper &StepperMotor){
    if (StepperMotor.currentPosition() > 0) StepperMotor.setSpeed(-defaultSpeed);
    else if (StepperMotor.currentPosition() < 0) StepperMotor.setSpeed(defaultSpeed);

    while (StepperMotor.currentPosition() != 0){
        Serial.println(StepperMotor.speed());
        // Serial.println(StepperMotor.currentPosition());
        StepperMotor.runSpeed();
    }
    StepperMotor.setSpeed(0);
}

void setup()
{
	Serial.begin(115200);

    Serial.println("Robot !!!");
    for (int i = 0; i < sizeof(pinIN) / sizeof(pinIN[0]) ; i++) pinMode(pinIN[i], INPUT_PULLUP);
    // pinMode(SwitchJoint1UP, INPUT_PULLUP);pinMode(SwitchJoint1DOWN, INPUT_PULLUP);
    // pinMode(SwitchJoint2UP, INPUT_PULLUP);pinMode(SwitchJoint2DOWN, INPUT_PULLUP);
    // pinMode(SwitchJoint3UP, INPUT_PULLUP);pinMode(SwitchJoint3DOWN, INPUT_PULLUP);
    // pinMode(SwitchJoint4UP, INPUT_PULLUP);pinMode(SwitchJoint4DOWN, INPUT_PULLUP);

    initStepperMotor(stepperJoint1, maxSpeed, acceleration);
    initStepperMotor(stepperJoint2, maxSpeed, acceleration);
    initStepperMotor(stepperJoint3, maxSpeed, acceleration);
    initStepperMotor(stepperJoint4, maxSpeed, acceleration);


}

void loop()
{
    if (Serial.available() > 0){
        String data = Serial.readStringUntil('\n');
        Serial.println(data);
        if (data == "Home"){
            Serial.println("run condition");
            setHome(stepperJoint1);
            setHome(stepperJoint2);
            setHome(stepperJoint3);
            setHome(stepperJoint4);
        }
    }
    getInputValue();
	if (!digitalRead(SwitchJoint1UP)) setSpeedAllStepper(defaultSpeed, 0, 0, 0);
	else if (!digitalRead(SwitchJoint1DOWN)) setSpeedAllStepper(-defaultSpeed, 0, 0, 0);
	else if (!digitalRead(SwitchJoint2UP)) setSpeedAllStepper(0, defaultSpeed, 0, 0);
	else if (!digitalRead(SwitchJoint2DOWN)) setSpeedAllStepper(0, -defaultSpeed, 0, 0);
	else if (!digitalRead(SwitchJoint3UP)) setSpeedAllStepper(0, 0, defaultSpeed, 0);
	else if (!digitalRead(SwitchJoint3DOWN)) setSpeedAllStepper(0, 0, -defaultSpeed, 0);
	else if (!digitalRead(SwitchJoint4UP)) setSpeedAllStepper(0, 0, 0, defaultSpeed);
	else if (!digitalRead(SwitchJoint4DOWN)) setSpeedAllStepper(0, 0, 0, -defaultSpeed);
    else setSpeedAllStepper(0, 0, 0, 0);

    stepperJoint1.runSpeed();
    stepperJoint2.runSpeed();
    stepperJoint3.runSpeed();
    stepperJoint4.runSpeed();



}