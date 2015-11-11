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
uint16_t getRotationX(void);
uint16_t getRotationY(void);
uint16_t getRotationZ(void);
