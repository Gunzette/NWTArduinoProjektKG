#include <Arduino.h>
#include "Grove_Motor_Driver_TB6612FNG.h"
#include <Wire.h>

MotorDriver motor;

void setup()
{
    // join I2C bus (I2Cdev library doesn't do this automatically)
    Wire.begin();
    motor.init();
    delay(2000);
}

void loop()
{
    // Nach vorne Fahren
    motor.dcMotorRun(MOTOR_CHA, -150);
    motor.dcMotorRun(MOTOR_CHB, -200);
    delay(750);
    
    // stop 2 motors;
    motor.dcMotorStop(MOTOR_CHA);
    motor.dcMotorStop(MOTOR_CHB);
    delay(750);

    // Nach hinten Fahren
    motor.dcMotorRun(MOTOR_CHA, 150);
    motor.dcMotorRun(MOTOR_CHB, 200);
    delay(750);
    
    // stop 2 motors
    motor.dcMotorStop(MOTOR_CHA);
    motor.dcMotorStop(MOTOR_CHB);
    delay(750);
}