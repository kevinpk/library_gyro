// Gyro.c
// Gyro I2C library
// hardware: MPU6050 IMU, nRF51 dev kit
// Kevin Kelly
// Run Beacon, LLC
// November 8, 2015

// This library is ported from an existing MPU6050 library for Arduino
// find the original library here: http://bit.ly/1OEkZ73

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "twi_master.h"
#include "Gyro.h"

#define devAddr                     0x68 << 1 // Gyro 2-wire address (MPU6050_ADDRESS_AD0_LOW)
#define MPU6050_RA_GYRO_XOUT_H      0x43
#define MPU6050_RA_GYRO_YOUT_H      0x45
#define MPU6050_RA_GYRO_ZOUT_H      0x47
#define MPU6050_RA_PWR_MGMT_1       0x6B
#define MPU6050_RA_GYRO_CONFIG      0x1B
#define MPU6050_RA_ACCEL_CONFIG     0x1C
#define MPU6050_CLOCK_PLL_XGYRO     0x01
#define MPU6050_GYRO_FS_250         0x00
#define MPU6050_ACCEL_FS_2          0x00
#define MPU6050_RA_WHO_AM_I         0x75
#define MPU6050_RA_ACCEL_XOUT_H     0x3B

void setClockSource(uint8_t source) {
//    I2Cdev::writeBits(devAddr, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, source);
	
		uint8_t cmd[2];
	
		// 0x2A enable interrupt setting register
		cmd[0] = MPU6050_RA_PWR_MGMT_1;
		cmd[1] = source; // 0100 0111 = 30 ms quiet, 75 ms shock, 700 ms tap_dur
		if (twi_master_transfer(devAddr, cmd, 2, TWI_ISSUE_STOP))
			printf("success setClockSource\n");
		else
			printf("error setClockSource\n");
}

void setFullScaleGyroRange(uint8_t range) {
//    I2Cdev::writeBits(devAddr, MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, range);

		uint8_t cmd[2];
	
		// 0x2A enable interrupt setting register
		cmd[0] = MPU6050_RA_GYRO_CONFIG;
		cmd[1] = range; // 0100 0111 = 30 ms quiet, 75 ms shock, 700 ms tap_dur
		if (twi_master_transfer(devAddr, cmd, 2, TWI_ISSUE_STOP))
			printf("success setFullScaleGyroRange\n");
		else
			printf("error setFullScaleGyroRange\n");
}

void setFullScaleAccelRange(uint8_t range) {
//    I2Cdev::writeBits(devAddr, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, range);

		uint8_t cmd[2];
	
		// 0x2A enable interrupt setting register
		cmd[0] = MPU6050_RA_ACCEL_CONFIG;
		cmd[1] = range; // 0100 0111 = 30 ms quiet, 75 ms shock, 700 ms tap_dur
		if (twi_master_transfer(devAddr, cmd, 2, TWI_ISSUE_STOP))
			printf("success setFullScaleAccelRange\n");
		else
			printf("error setFullScaleAccelRange\n");
}

void setSleepEnabled(bool enabled) {
//    I2Cdev::writeBit(devAddr, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, enabled);

		uint8_t cmd[2];
	
		// 0x2A enable interrupt setting register
		cmd[0] = MPU6050_RA_PWR_MGMT_1;
		cmd[1] = enabled; // 0100 0111 = 30 ms quiet, 75 ms shock, 700 ms tap_dur
		if (twi_master_transfer(devAddr, cmd, 2, TWI_ISSUE_STOP))
			printf("success setSleepEnabled\n");
		else
			printf("error setSleepEnabled\n");
}

uint8_t getDeviceID(void) {
//    I2Cdev::readBits(devAddr, MPU6050_RA_WHO_AM_I, MPU6050_WHO_AM_I_BIT, MPU6050_WHO_AM_I_LENGTH, buffer);
    uint8_t buffer[2];
	
    buffer[0] = MPU6050_RA_WHO_AM_I;
    twi_master_transfer(devAddr, buffer, 1, TWI_DONT_ISSUE_STOP);
    twi_master_transfer(devAddr | TWI_READ_BIT, buffer, 2, TWI_ISSUE_STOP);
	
		printf("deviceID = %X\n", buffer[0]);
	return buffer[0];
}

bool gyroTestConnection(void) {
    return getDeviceID() == devAddr;
}

void gyroInit(void) {
    setClockSource(MPU6050_CLOCK_PLL_XGYRO);
    setFullScaleGyroRange(MPU6050_GYRO_FS_250);
    setFullScaleAccelRange(MPU6050_ACCEL_FS_2);
    setSleepEnabled(false); // thanks to Jack Elston for pointing this one out!
}

//void getRotation(uint16_t* x, uint16_t* y, uint16_t* z){	
//    uint8_t buffer[7];

//		printf("getting rotation!\n");
//	
//    buffer[0] = MPU6050_RA_GYRO_XOUT_H;
//    twi_master_transfer(devAddr, buffer, 1, TWI_DONT_ISSUE_STOP);
//    twi_master_transfer(devAddr | TWI_READ_BIT, buffer, 6, TWI_ISSUE_STOP);
//    
//    *x = (((uint16_t)buffer[0]) << 8) | buffer[1];
//    *y = (((uint16_t)buffer[2]) << 8) | buffer[3];
//    *z = (((uint16_t)buffer[4]) << 8) | buffer[5];
//	
//		printf("x = %i\n", *x);
//		printf("y = %i\n", *y);	
//		printf("z = %i\n", *z);
//}

int16_t getRotationX() {
//    I2Cdev::readBytes(devAddr, MPU6050_RA_GYRO_XOUT_H, 2, buffer);
    uint8_t buffer[2];
	
    buffer[0] = MPU6050_RA_GYRO_XOUT_H;
    twi_master_transfer(devAddr, buffer, 1, TWI_DONT_ISSUE_STOP);
    twi_master_transfer(devAddr | TWI_READ_BIT, buffer, 2, TWI_ISSUE_STOP);
	
//		printf("X = %i\n",(((int16_t)buffer[0]) << 8) | buffer[1]);	
	
    return (((int16_t)buffer[0]) << 8) | buffer[1];
}
/** Get Y-axis gyroscope reading.
 * @return Y-axis rotation measurement in 16-bit 2's complement format
 * @see getMotion6()
 * @see MPU6050_RA_GYRO_YOUT_H
 */
int16_t getRotationY() {
//    I2Cdev::readBytes(devAddr, MPU6050_RA_GYRO_YOUT_H, 2, buffer);
    uint8_t buffer[2];
	
    buffer[0] = MPU6050_RA_GYRO_YOUT_H;
    twi_master_transfer(devAddr, buffer, 1, TWI_DONT_ISSUE_STOP);
    twi_master_transfer(devAddr | TWI_READ_BIT, buffer, 2, TWI_ISSUE_STOP);
	
		printf("Y = %i\n", (((int16_t)buffer[0]) << 8) | buffer[1]);	
    return (((int16_t)buffer[0]) << 8) | buffer[1];
}
/** Get Z-axis gyroscope reading.
 * @return Z-axis rotation measurement in 16-bit 2's complement format
 * @see getMotion6()
 * @see MPU6050_RA_GYRO_ZOUT_H
 */
int16_t getRotationZ() {
//    I2Cdev::readBytes(devAddr, MPU6050_RA_GYRO_ZOUT_H, 2, buffer);
    uint8_t buffer[2];
	
    buffer[0] = MPU6050_RA_GYRO_ZOUT_H;
    twi_master_transfer(devAddr, buffer, 1, TWI_DONT_ISSUE_STOP);
    twi_master_transfer(devAddr | TWI_READ_BIT, buffer, 2, TWI_ISSUE_STOP);
	
		printf("Z = %i\n", (((int16_t)buffer[0]) << 8) | buffer[1]);	
    return (((int16_t)buffer[0]) << 8) | buffer[1];
}

void setXGyroOffset(int16_t offset) {
//    I2Cdev::writeWord(devAddr, MPU6050_RA_XG_OFFS_USRH, offset);
}

void setYGyroOffset(int16_t offset) {
//    I2Cdev::writeWord(devAddr, MPU6050_RA_YG_OFFS_USRH, offset);
}

void setZGyroOffset(int16_t offset) {
//    I2Cdev::writeWord(devAddr, MPU6050_RA_ZG_OFFS_USRH, offset);
}

void setZAccelOffset(int16_t offset) {
//    I2Cdev::writeWord(devAddr, MPU6050_RA_ZA_OFFS_H, offset);
}

void setDMPEnabled(bool enabled) {
//    I2Cdev::writeBit(devAddr, MPU6050_RA_USER_CTRL, MPU6050_USERCTRL_DMP_EN_BIT, enabled);
}
void resetDMP() {
//    I2Cdev::writeBit(devAddr, MPU6050_RA_USER_CTRL, MPU6050_USERCTRL_DMP_RESET_BIT, true);
}

uint16_t getXTilt(void){
    uint8_t buffer[14];
	
    buffer[0] = MPU6050_RA_ACCEL_XOUT_H;
    twi_master_transfer(devAddr, buffer, 1, TWI_DONT_ISSUE_STOP);
    twi_master_transfer(devAddr | TWI_READ_BIT, buffer, 14, TWI_ISSUE_STOP);

//		printf("%X = 3.0i %5i° %5i°\n", ((((int16_t)buffer[0]) << 8) | buffer[1])/200, (((int16_t)buffer[2]) << 8) | buffer[3], (((int16_t)buffer[4]) << 8) | buffer[5]);
	
	return ((((int16_t)buffer[0]) << 8) | buffer[1])/200;
}