#include "Ultrasonic.h"

void Ultrasonic::init()
{
    if (getEn())
    {
        Wire.beginTransmission((byte)0x00);   //broadcast
        LogUs("enabled");
        Wire.write((byte)0x02); //Register zuim Einstellen der Reichweite
        Wire.write((byte)70);   //Reichweite wird auf ~3m gesetzt, dadurch sind die Messwerte nach 21ms verfügbar
        Wire.endTransmission();
        LogUs("Initlized");
    }else
        LogUs("disabled");
}

void Ultrasonic::update()
{
    if (getEn())
    {
        if (millis() - _lastMeasurement > 25 && !_fetched)
        {
            fetch();
            filter();
            _fetched = true;
        }
        if (millis() - _lastMeasurement > 65)
        {
            Wire.beginTransmission(0);
            Wire.write(byte(0x00));      // Command-Register wird angesprochen
            Wire.write(byte(0x51));      // Messung in cm wird gestartet
            Wire.endTransmission();   
            _lastMeasurement = millis();
            _fetched = false;
        }
    }
}

void Ultrasonic::fetch()
{
    for (int i = 0; i < NUM_OF_US; i++)
    {

        Wire.beginTransmission(_addresses[i]);
        Wire.write((byte)0x02);
        Wire.endTransmission();
        Wire.requestFrom(_addresses[i], (byte)2);

        if (2 <= Wire.available())
        {
            for(int j = 0; j < FILTER_VALUES - 1; j++ )
            {
                _distance[i][j] = _distance[i][j+1];
            }
            int reading = Wire.read() << 8;
            reading |= Wire.read();
            _distance[i][FILTER_VALUES-1] = reading;
        }
    }
}

void Ultrasonic::filter()
{
    int distanceSum = 0;
    for(int i = 0; i < NUM_OF_US;i ++)
    {
        for(int j = 0; j < FILTER_VALUES; j++)
        {
            distanceSum += _distance[i][j];
        }
        _filteredDistance[i] = distanceSum / FILTER_VALUES;
        distanceSum = 0;
    }
}

int Ultrasonic::getFrontLeft() { return _filteredDistance[0]; }
int Ultrasonic::getLeft() { return _filteredDistance[1]; }
int Ultrasonic::getBack() { return _filteredDistance[2]; }
int Ultrasonic::getRight() { return _filteredDistance[3]; }
int Ultrasonic::getFrontRight() { return _filteredDistance[4]; }
int Ultrasonic::getFront() { return min(getFrontLeft(), getFrontRight()); }
