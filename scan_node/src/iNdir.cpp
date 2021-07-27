#include <Arduino.h>
#include <iNdir.h>

iNdir::iNdir() {}
iNdir::~iNdir() {}
float iNdir::get_co2_value() { return _concentration; }

void iNdir::read_value(int sensor_value)
{
    float voltage, voltage_dif = 0;
    voltage = sensor_value * (3.3 / 4095.0);

    /* Check preheating */
    /*if (_voltage == MIN_VOLTAGE)
    {
        Serial.println("Fault");
    }
    else if (_voltage < 0.4)
    {
        Serial.println("Preheating");
    }
    else
    {*/
    if (voltage >= 0.4){
        voltage_dif = voltage - 0.4;
        _concentration = (voltage_dif * 5000) / 1.6;
    }
}  