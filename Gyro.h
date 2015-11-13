// Gyro.h
// Gyro I2C library
// hardware: MPU6050 IMU, nRF51 dev kit
// Kevin Kelly
// Run Beacon, LLC
// November 8, 2015

// This library is ported from an existing MPU6050 library for Arduino
// find the original library here: http://bit.ly/1OEkZ73

#include <stdint.h>
#include <stdbool.h>

//void getRotation(uint16_t* x, uint16_t* y, uint16_t* z);
void gyroInit(void);
bool gyroTestConnection(void);
int16_t getRotationX(void);
int16_t getRotationY(void);
int16_t getRotationZ(void);
void setXGyroOffset(int16_t offset);
void setYGyroOffset(int16_t offset);
void setZGyroOffset(int16_t offset);
void setZAccelOffset(int16_t offset);
void setDMPEnabled(bool enabled);
void resetDMP();
uint16_t getXTilt(void);
