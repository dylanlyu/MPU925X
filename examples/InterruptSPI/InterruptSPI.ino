/**
 * InterruptSPI.ino - Set Interrupt on SPI bus.
**/

#include "MPU925X.h"

// an MPU925X object with the MPU-925X sensor on SPI bus 0 and chip select pin 10
MPU925X IMU(SPI, 10);
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
    // setting DLPF bandwidth to 20 Hz
    IMU.setDlpfBandwidth(MPU925X::DLPF_BANDWIDTH_20HZ);
    // setting SRD to 19 for a 50 Hz update rate
    IMU.setSrd(19);
    // enabling the data ready interrupt
    IMU.enableDataReadyInterrupt();
    // attaching the interrupt to microcontroller pin 1
    pinMode(1, INPUT);
    attachInterrupt(1, getIMU, RISING);
}

void loop() {}

void getIMU()
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
}
