# remote-sensing-intro
Accessing sensor readings remotely using an NXP LPC-1768 microcontroller

## Description:
One useful application of IoT is remote sensing. In remote sensing, a collection of sensors is installed in a dangerous or inaccessible location and then the readings of these sensors are transmitted to the head office via the Internet.

This project is an introduction to remote sensing. In this project, a voltage meter, a light sensor, a temperature sensor and a humidity sensor are attached to an NXP LPC-1768 microcontroller which is connected directly to a server via UART. The readings of the sensors are forwarded to the server every 10 seconds for 10 times. These readings are then accessible remotely over the Internet. The transmitted values are also shown on an LCD attached to the microcontroller.

*NOTE: This code has a bug responsible for the unsuccessful transmission of every other reading. Therefore, only the readings of every 20 seconds are correctly transmitted to and accessible by the server.*

## Copy Right:
* This project was a lab assignment for the Microcontrollers Lab by Professor O. Fatemi in the summer of 2020 at the University of Tehran.
* The author of the libraries used in this project is [ExploreEmbedded](http://www.exploreembedded.com/wiki/). More information about them is written inside their files.
* The rest of the files in this repository are created by me and my teammates R. Ghoroghchian and M. Haghifam.
