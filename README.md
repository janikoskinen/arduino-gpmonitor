# arduino-gpmonitor

This project provides (or will provide in near future) possibility to monitor and keep track several external variables. These include:
- Temperature (implemented)
- Humidity
- Wire statuses, closed / open circuits

In order to use this data communication protocol for host computer is required. (TBD)

## Hardware

Three components is required:
- Arduino (Nano used here)
- DS18B20 thermometer sensor
- 4.7 kOhm pull-up resistor for data line

## Software

One external library is used: OneWire. This provides 1-wire communication with devices that are connected to some IO pin. Note: 1-wire supports multiple devices in single bus.

My software includes class for temperature sensor. Separate class was created to allow any additional functionality to be easily added. Use of separate class also simplifies the main program so that only two functions are used.
