// Gyro.h
// Gyro I2C library
// hardware:
// Kevin Kelly
// Run Beacon, LLC
// November 8, 2015

void getRotation(uint16_t* x, uint16_t* y, uint16_t* z);
void gyroInit(void);
bool gyroTestConnection(void);
uint16_t getRotationX(void);
uint16_t getRotationY(void);
uint16_t getRotationZ(void);
