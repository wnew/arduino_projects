#All Project Ideas

This is a repo for all my random arduino projects


##Wireless Home Automation

Arduino controlled home automation, maybe with a RaspPi or Due and Ethernet
shield as the main control board. With wireless control from your android
phone. Remote arduino nodes with wireless transievers would control the 
peripherals.


##Electriciy Management System
Measuring and plotting household power usage. Using the arduino and current
sensors. Use this data to optimise the usage.


##Wireless Speaker Setup

Centralised music system which can play music in any room wirelessly, contolled
via mobile phone. 
Cell Phone -> Wireless to network -> Music Server -> Stream music to different rooms
This would be best achieved with a raspberry pi


##Media PC attached to TV

Device running XBMC to manage media. (This is more of a RaspberryPi project)
Will also need to set up a remote control and a media server. 


##Arduino Controlled Headlamp
 
This would need to use a pro micro
Control brighness using some brightness sensor (LDR etc)
Monitor battery charge


##Arduino Controlled Fencing Box

This is a basic fencing scoring box controlled by an Arduino. It is used to 
sense when a touch is made in a fencing bout.


##Arduino Controlled Wireless Fencing Box

This is a more complex project then the basic fencing scoring box. As it will require syncronisation between the 2 wireless devices. The plan is to use the 4 HC-05 bluetooth modules (1 for each fencer and 2 on the control box). They will need to be synced every minute or so. The control box will need 2 hardware serial interfaces so the processor wont have to manage any software serial buffers. either the Mega or the Due would be able to do this. The fencers modules will use a Pro Micro or Pro Mini and the HC-05. Need to test if we can handle 2 bluetooth modules on a arduino, that the bluetooth link is still good over 10m and that the syncronisation is good enough for millisecond accuracy. 


##Arduino Controlled Switch Mode Power Supply

I am sure this project has been done before but it would be a great project to
get your hands dirty with. The idea is to create a dual channle switch mode
power supply with much of the control done with an Adruino. It would be easy to
implement a display for the voltage and current settings and actual voltage
and current values. A basic relay board could be used and a couple of those
large heat sinks I have lying around. 

 
##Vehicle Tracker 

This would use a GPS and a 3G/GSM module to track and report the location of a
vehicle. It would be useful to have a serperate battery to the vehicle battery
which also gets charged like the vehicle battery. You couls also include a 
magnetometer, gyro and accellerometer and capture these for analysis.


##Gyro Mouse

The idea here is to create give a standard mouse a few more axis of movement
using a gyro, accel and a magnetometer. This could be used for gaming or in 3D
design environments. Check out "Air Mouse"


##Full RC chain

This project is meant to create a full chain, from remote control to the RF
link to the motor controller on a RC vehicle. It will use a Wii Nunchuk as the
controller, a pair of NRF24L01s as the RF link and an arduino with a motor
controller shield on the vehicle. There will also be an option to swap out the 
NRF modules for a standard 433MHz RF link. Or even swap out the nunchuk for a 
bluetooth link to your smart phone.


##Arduino Phone

The idea here is to replace a fixed-line telephone with an arduino based device
which is connected to the home network and alowes phone calls to be make using
an android device over the fixed-line network. Thie would require a device that
can do ADC and DAC and can decode/encode DTMF. The Due could work for this but
more investigation is requried. 


##Arduino Oscilliscope

Best to use a Due as is has a 12 bit ADC and runs at 84MHz as apposed to 10 bit
and 16MHz. We need some software for this as well, best do this in Python. 
This should be a fun project.


##Arduino Waveform/Signal/funtion Generator

Best to use a Due as is has built in DACs, will have to determine the bitrate.  


##Storm cloud lamp

Cotton wool with leds inside controlled by an arduino to randomly light up. 
Use a remote control to set the mode.


##Cricket Bowling Machine

This machine consistis of a couple of 'wheels' which grip a ball and throw it.
The speed of the wheels contoll the spin/swing of the ball and can be adjusted
via the arduino.


##Bluetooth Arduino Programmer Module

The idea here is to have a bluetooth board which can be plugged into an arduino and used to program it. This can be done with the standard HC-05 and a few components.


##Arduino Controlled RGB Strobe Light

Pretty obvious


##Wireless light switches

The ESP8266 is an amazing little module, it even has a small micro on board so no need for an Arduino. If we connect a relay to this device and a small 220v power supply we can very easily create a wireless light switch or anything else for that matter.


##Some other idea which I forget right now

Blah blah blah


