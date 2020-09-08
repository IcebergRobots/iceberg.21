#pragma once

#include "Hardware.h"
#include "HMotor.h"

#define ANGLE_M 70 //Angle between motors

class Chassis : public Hardware
{
public:
  Chassis(Motor* motors, const int motorCount = 4, const bool& enabled = false);

  void init() override;
  void update() override; //TODO Encoder

  void setEn(const bool& enabled) override;

  inline Motor& getMotor(int motorNumber) { return _motors[motorNumber]; }

  void calculate(int angle, int power, int rotation = 0);
  void drive();
  void drive(int angle, int power, int rotation = 0);
  void brake(const bool& activ);

private:
  int _motorCount = 0;
  Motor *_motors;
};
