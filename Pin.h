#pragma once
/*
PIN_A0   (54)
PIN_A1   (55)
PIN_A2   (56)
PIN_A3   (57)
PIN_A4   (58)
PIN_A5   (59)
PIN_A6   (60)
PIN_A7   (61)
PIN_A8   (62)
PIN_A9   (63)
PIN_A10  (64)
PIN_A11  (65)
PIN_A12  (66)
PIN_A13  (67)
PIN_A14  (68)
PIN_A15  (69)
*/
// Motorpins:
#define FWD0            23
#define BWD0            25
#define PWM0            8

#define FWD1            27
#define BWD1            29
#define PWM1            9 

#define FWD2            37
#define BWD2            35
#define PWM2            10

#define FWD3            33
#define BWD3            31
#define PWM3            11

#define M0_CURR         55 //  Pin zum messen des Motorstroms von M1
#define M1_CURR         56 //  Pin zum messen des Motorstroms von M2
#define M2_CURR         57 //  Pin zum messen des Motorstroms von M3
#define M3_CURR         58 //  Pin zum messen des Motorstroms von M4


// BallTouchpins:
#define BT_LED        47
#define BT_SENSOR       69  //A15

// KickerPins
#define KICKER          12
#define POTKICK         54  //  hier ist das Potentiometer unten auf der Platine angeschlossen

//Tones
#define BUZZER          13

//HEARTBEAT_LED
#define HEARTBEAT_LED   7

//HARDWARE difference robots
#define HARDWARE_DIFFERENCE 68 //A14

//Ultraadresses
//addresses of the Ultrasonicsensors named by their position
#define NUM_OF_US       5

#define FRONT_LEFT      112
#define LEFT            113
#define FRONT_RIGHT     116
#define BACK            114
#define RIGHT           115

#define S_KICKER        0
#define S_MOTOR         1
#define S_HEADSTART     2

#define B_KICK          8
#define B_CAL           9
#define B_SHIFT         10
#define J_LEFT          3
#define J_CENTER        4
#define J_DOWN          5
#define J_UP            7
#define J_RIGHT         6

#define LED_BACK_LEFT   6
#define LED_BACK_RIGHT  38
#define LED_FRONT       49

#define LED_DEFENDER    11
#define LED_STRIKER     12    //not working 

#define BOTTOM_LED       46   //  Hier können die RGB-LEDs des Bodensensors gesteuert werden

#define INT_BODENSENSOR 3   //  hier sendet der Nano des Bodensensors sein Interruptsignal

#define TX2             16  //  Serielles Senden zum Bodensensor Arduino Nano
#define RX2             17  //  Serielles Empfangen vom Bodensensor Arduino Nano