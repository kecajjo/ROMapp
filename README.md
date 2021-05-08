# ROMapp
Project was designed to visualize position and sensor values of the floor cleaning robot developed in project called "ROMAN". Hopefully it can be used with other mobile robots too.

It's not finished yet though.

## Author:
Jacek Multan

## About:
Window application which calculates robot position basing on sensor values. It has three main widgets:
* "Map" which allows user to see how robot position is changing over time
* table containing current sensor values
* graphs showing how sensor values are changing over time

Program uses bluetooth to receive information from the robot. User can scan for nearby devices then choose one and connect to it.

Project was written using [open source version of QT framework](https://www.qt.io/download-open-source) and [QCustomPlot](https://www.qcustomplot.com).

## Frame
* 2bytes <uint16_t> PWM of right motor
* 2bytes <uint16_t> PWM of left motor
* 2bytes <int16_t> speed and direction of right motor
* 2bytes <int16_t> speed and direction of left motor
* 2bytes <int16_t> gyroscope data
* 4bytes <float> compass data
* CRC (not implemented yet)

## License
[GNU General Public License v3](https://www.gnu.org/licenses/gpl-3.0.en.html)