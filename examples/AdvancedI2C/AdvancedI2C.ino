/**
 * AdvancedI2C.ino - Advanced settings on I2C bus.
**/

#include "MPU925X.h"

// an MPU925X object with the MPU-925X sensor on I2C bus 0 with address 0x68
MPU925X IMU(Wire, 0x68);
int status;

void setup()
{
    // serial to display data
    Serial.begin(115200);
    while (!Serial)
    {
    }

    // start communication with IMU
    status = IMU.begin();
    if (status < 0)
    {
        Serial.println("IMU initialization unsuccessful");
        Serial.println("Check IMU wiring or try cycling power");
        Serial.print("Status: ");
        Serial.println(status);
        while (1)
        {
        }
    }
    // setting the accelerometer full scale range to +/-8G
    IMU.setAccelRange(MPU925X::ACCEL_RANGE_8G);
    // setting the gyroscope full scale range to +/-500 deg/s
    IMU.setGyroRange(MPU925X::GYRO_RANGE_500DPS);
    // setting DLPF bandwidth to 20 Hz
    IMU.setDlpfBandwidth(MPU925X::DLPF_BANDWIDTH_20HZ);
    // setting SRD to 19 for a 50 Hz update rate
    IMU.setSrd(19);
}

void loop()
{
    // read the sensor
    IMU.readSensor();

    // display the data
    Serial.print(IMU.getAccelX_mss(), 6);
    Serial.print("\t");
    Serial.print(IMU.getAccelY_mss(), 6);
    Serial.print("\t");
    Serial.print(IMU.getAccelZ_mss(), 6);
    Serial.print("\t");
    Serial.print(IMU.getGyroX_rads(), 6);
    Serial.print("\t");
    Serial.print(IMU.getGyroY_rads(), 6);
    Serial.print("\t");
    Serial.print(IMU.getGyroZ_rads(), 6);
    Serial.print("\t");
    Serial.print(IMU.getMagX_uT(), 6);
    Serial.print("\t");
    Serial.print(IMU.getMagY_uT(), 6);
    Serial.print("\t");
    Serial.print(IMU.getMagZ_uT(), 6);
    Serial.print("\t");
    Serial.println(IMU.getTemperature_C(), 6);
    delay(20);
}
