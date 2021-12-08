# Window_Door-Sensor
Door/Window sensor based on a design by MakerMeik but using different code to use the ESP-NOW protocol.

Using ESP-NOW means that the connection and sending of the data packet takes around 500mS to complete and
is device to device without the need of a WiFi router.

There are two Arduino ino files, one for the transmitter and one for the receiver, the receiver will need to
be powered up to receive data and the recieved data will be sent to the host computer via serial/USB to be read
in a terminal program.

There is an additiona png file showing the Scope trace of the power consumption profiile, although this shows the length to be 626mS it is usually around 526mS.

Using an online calculator to work out how long a battery would last with a couple of triggers an hour you can get well over a year on a 600mAH battery.

On the rear half of the 3D printed case I used M3 Brass threaded inserts for the M3 cap screws to thread into.

More information can also be found on www.gadjet.co.uk
