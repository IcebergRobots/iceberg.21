#include "HCompass.h"

void Compass::init() 
{
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    LogCmps("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
  } else
  {
    LogCmps("Current Temperature: " + bno.getTemp() + " °C");
    /* Display calibration status for each sensor. */
    uint8_t system, gyro, accel, mag = 0;
    bno.getCalibration(&system, &gyro, &accel, &mag);
    LogCmps("CALIBRATION: Sys=" + system + " Gyro=" + gyro + " Accel=" + accel + " Mag=" + mag);
  }
}

void Compass::update() 
{
  //Debug Calibration
  if(DEBUG_COMPASS)
  {
    if(_calsystem == false || _calgyro == false || _calaccel == false || _calmag == false)
    {
      uint8_t system, gyro, accel, mag = 0;
      bno.getCalibration(&system, &gyro, &accel, &mag);
      if(system == 3 && _calsystem == false)
      {
        LogCmps("Succesfully calibrated System");
        _calsystem = true;
      }
      if(gyro == 3 && _calgyro == false)
      {
        LogCmps("Succesfully calibrated Gyro");
        _calgyro = true;
      }
      if(accel == 3 && _calaccel == false)
      {
        LogCmps("Succesfully calibrated Accel");
        _calaccel = true;
      }
      if(mag == 3 && _calmag == false)
      {
        LogCmps("Succesfully calibrated Mag");
        _calmag = true;
      }

    }
    // LogCmps("CALIBRATION: Sys=" + system + " Gyro=" + gyro + " Accel=" + accel + " Mag=" + mag);
  }

  if(millis() - _lastTime > 100) //100 ms delay
  {
    //could add VECTOR_ACCELEROMETER, VECTOR_MAGNETOMETER,VECTOR_GRAVITY...
    sensors_event_t orientationData , angVelocityData , linearAccelData, magnetometerData, accelerometerData, gravityData;
    bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);
    bno.getEvent(&angVelocityData, Adafruit_BNO055::VECTOR_GYROSCOPE);
    bno.getEvent(&linearAccelData, Adafruit_BNO055::VECTOR_LINEARACCEL);
    bno.getEvent(&magnetometerData, Adafruit_BNO055::VECTOR_MAGNETOMETER);
    bno.getEvent(&accelerometerData, Adafruit_BNO055::VECTOR_ACCELEROMETER);
    bno.getEvent(&gravityData, Adafruit_BNO055::VECTOR_GRAVITY);
    int8_t boardTemp = bno.getTemp();

    LogCmps("Magnetometer: " + magnetometerData.magnetic.x + ", " + magnetometerData.magnetic.y + ", " + + magnetometerData.magnetic.z);

    _lastTime = millis();
  }

}

