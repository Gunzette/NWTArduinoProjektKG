#include "Grove_Motor_Driver_TB6612FNG.h"

MotorDriver::MotorDriver()
{
}

void MotorDriver::init(uint8_t addr)
{
    _addr = addr;
    standby();
}

void MotorDriver::standby()
{
    I2Cdev::writeByte(_addr, GROVE_MOTOR_DRIVER_I2C_CMD_STANDBY, 0);
    delay(1);
}

void MotorDriver::notStandby()
{
    I2Cdev::writeByte(_addr, GROVE_MOTOR_DRIVER_I2C_CMD_NOT_STANDBY, 0);
    delay(1);
}

void MotorDriver::setI2cAddr(uint8_t addr)
{
    if (addr == 0x00) return;
    else if (addr >= 0x80) return;
    I2Cdev::writeByte(_addr, GROVE_MOTOR_DRIVER_I2C_CMD_SET_ADDR, addr);
    _addr = addr;
    delay(100);
}

void MotorDriver::dcMotorRun(motor_channel_type_t chl, int16_t speed)
{
    if (speed > 255) speed = 255;
    else if (speed < -255) speed = -255;

    if (speed >= 0) _buffer[0] = GROVE_MOTOR_DRIVER_I2C_CMD_CW;
    else _buffer[0] = GROVE_MOTOR_DRIVER_I2C_CMD_CCW;

    _buffer[1] = chl;
    if (speed >= 0) _buffer[2] = speed;
    else _buffer[2] = (uint8_t)(-speed);

    I2Cdev::writeBytes(_addr, _buffer[0], 2, _buffer+1);
    delay(1);
}

void MotorDriver::dcMotorBrake(motor_channel_type_t chl)
{
    I2Cdev::writeByte(_addr, GROVE_MOTOR_DRIVER_I2C_CMD_BRAKE, chl);
    delay(1);
}

void MotorDriver::dcMotorStop(motor_channel_type_t chl)
{
    I2Cdev::writeByte(_addr, GROVE_MOTOR_DRIVER_I2C_CMD_STOP, chl);
    delay(1);
}

