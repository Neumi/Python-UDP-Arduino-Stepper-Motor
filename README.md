# Python-UDP-Arduino-Stepper-Motor
Snippet of code to control stepper motors via UDP in python.


Upload Arduino Code on Microcontroller. Ethernet shield is connected. A4988 Stepper motor driver is connected as shown.
Test connection from python device with <code>ping 192.168.2.10</code> 

Check Netzwork setup before. The IP may differ from my depending on your network. Change if required.

Assemble the Arduino Ethernet Shield and the Motor + driver as shown in the schcematic.

![Schematic](https://raw.githubusercontent.com/Neumi/Python-UDP-Arduino-Stepper-Motor/master/schematic.png)

If Arduino is pingable run the python script.

Now the Motor should move a few steps. 

Have fun. Best regards.
