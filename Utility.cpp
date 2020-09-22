#include "Utility.h"

void startSound()
{
  //Fiepen, welches Programstart signalisiert

  for (int i = 10; i < 2000; i += 10)
  {
    if (robotID == Robot::A)
      tone(BUZZER, i);
    else
      tone(BUZZER, 2010 - i);

    delay(1);
  }
  noTone(BUZZER);
}

extern unsigned int __bss_end;
extern unsigned int __heap_start;
extern void *__brkval;

uint16_t getFreeSRAM()
{
  uint8_t newVariable;
  // heap is empty, use bss as start memory address
  if ((uint16_t)__brkval == 0)
    return (((uint16_t)&newVariable) - ((uint16_t)&__bss_end));
  // use heap end as the start of the memory address
  else
    return (((uint16_t)&newVariable) - ((uint16_t)__brkval));
}

void reset()
{
  asm("jmp 0"); // starte den Arduino neu
}

#define HEARTBEAT_LOOPTIME 500
void heartbeat()
{
  byte i = map(millis() % HEARTBEAT_LOOPTIME * 2, 0, HEARTBEAT_LOOPTIME, 0, 255);
  analogWrite(HEARTBEAT_LED, i > 255 ? i : 255 - i);
}


static bool initChooseRobot = true;
static Robot robotID;

Robot getRobot()
{
  if (initChooseRobot)
  {
    pinMode(HARDWARE_DIFFERENCE, INPUT_PULLUP);
    if (digitalRead(HARDWARE_DIFFERENCE) == HIGH)
    {
      LogUtility("Robot A started");
      robotID = Robot::A;
    }
    else
    {
      LogUtility("Robot B started");
      robotID = Robot::B;
    }

    initChooseRobot = false;
  }
  return robotID;
}