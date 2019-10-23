/**
 *
* */

#include "MPU925X.h"

MPU925X mpu9255(Wire, 0x68);
int status;

void setup()
{
  // serial to display data
  Serial.begin(115200);
  while (!Serial)
  {
  }

  // start communication with mpu9255
  status = mpu9255.begin();
  if (status < 0)
  {
    Serial.println("mpu9255 initialization unsuccessful");
    Serial.println("Check mpu9255 wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while (1)
    {
    }
  }
}

void loop()
{
  // read the sensor
  mpu9255.readSensor();
  // display the data
  Serial.print(mpu9255.getAccelX_mss(), 6);
  Serial.print("\t");
  Serial.print(mpu9255.getAccelY_mss(), 6);
  Serial.print("\t");
  Serial.print(mpu9255.getAccelZ_mss(), 6);
  Serial.print("\t");
  Serial.print(mpu9255.getGyroX_rads(), 6);
  Serial.print("\t");
  Serial.print(mpu9255.getGyroY_rads(), 6);
  Serial.print("\t");
  Serial.print(mpu9255.getGyroZ_rads(), 6);
  Serial.print("\t");
  Serial.print(mpu9255.getMagX_uT(), 6);
  Serial.print("\t");
  Serial.print(mpu9255.getMagY_uT(), 6);
  Serial.print("\t");
  Serial.print(mpu9255.getMagZ_uT(), 6);
  Serial.print("\t");
  Serial.println(mpu9255.getTemperature_C(), 6);
  delay(100);
}
