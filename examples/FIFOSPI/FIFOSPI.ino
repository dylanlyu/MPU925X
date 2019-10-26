/**
 * FIFOSPI.ino - Set First In First Out on SPI bus.
**/

#include "MPU925X.h"

// an MPU925X object with the MPU-925X sensor on SPI bus 0 and chip select pin 10
MPU925XFIFO IMU(SPI, 10);
int status;

// variables to hold FIFO data, these need to be large enough to hold the data
float ax[100], ay[100], az[100];
size_t fifoSize;

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
    // enabling the FIFO to record just the accelerometers
    IMU.enableFifo(true, false, false, false);
    // gather 50 samples of data
    delay(980);
    // read the fifo buffer from the IMU
    IMU.readFifo();
    // get the X, Y, and Z accelerometer data and their size
    IMU.getFifoAccelX_mss(&fifoSize, ax);
    IMU.getFifoAccelY_mss(&fifoSize, ay);
    IMU.getFifoAccelZ_mss(&fifoSize, az);
    // print the data
    Serial.print("The FIFO buffer is ");
    Serial.print(fifoSize);
    Serial.println(" samples long.");
    for (size_t i = 0; i < fifoSize; i++)
    {
        Serial.print(ax[i], 6);
        Serial.print("\t");
        Serial.print(ay[i], 6);
        Serial.print("\t");
        Serial.println(az[i], 6);
    }
}

void loop() {}
