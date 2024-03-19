# ARR-V2
Automatic Router Rebooter V2
## Introduction
When home internet WIFI doesn't work, sometimes the solution is to reboot the router. 
Here is an Automatic Router Rebooter that uses an ESP32 to automatically check the WIFI internet connectivity: when there is no internet for a specified amout of time, the power to the router is interrupted and then reactivated.
All the parameters are customizable through a web interface 
## The HW
The HW part is rather simple. There is 
- an ESP32 module
- a voltage regulator (a 7805 would work but i prefer to use a step down voltage controller that is more efficient, generates less heat and consumes less)
- a 5V relay module. These type of modules incorporate some electronic to adapt the ESP32 output to contro the relay coil. The type that I have used is a high trigger element (relay is ON when the input is HIGH). You can also use a low trigger relay module but you need to change the program logic (invert HIGH and LOW relays control)
- a power on switsh
- a button
- 4 LEDs, each one with its current limiting resistor
The schema is shown in the following picture
![alt text](https://github.com/dariomella/ARR-V1/blob/main/ARR%20V1%20HW.png)
## Instructions
When you connect the power supply all the LED flash once.

The first time when the ARR is started or whenever you want to reset to the factory settings, keep the button pressed for more than 15 seconds during power on:
you will enter into the  setup portal mode: the led #2 will turn on. After a few seconds the led #3 will turn on indicating
that the setup portal is ready. 
Using a computer, a tablet or a mobile phone, connect to the temporary WIFI network ARR_NET using the password "password123"
(when using a mobile phone or a tablet, you might need to switch off the mobile connectivity (3G/4G/5G).
Then point your browser to the address 192.168.4.1. You will be presented with a web page. Here you need to specify the network ID (SSID) and the 
password of the WIFI network to be monitored for internet connectivity.

The setup portal mode can also be invoked without resetting the parameters to the default factory values: to do this keep the button pressed for less than 15 seconds during power on:

You can also enter other optional parameters:
- remoteHost1,2,3,4: name of a remote host that is always up and running reliably. The host name can be written as IP address (x.x.x.x) form or as a website 
(for example www.google.com). Up to 4 host can be specified and internet connectivity is successful if at least one of them can be responds to a PING command.
If you want to leave blank one of the remoteHosts, just insert an empty space.

- posrtalSSID and portalPassword: you can change the default values of the setup portal WIFI SSID and password. 
This can be usefule because the setup portal shows the SIID and password of the WIFI network to be monitored:
if you fear that someone unauthorized can invoke the setup portal mode and look at the WIFI SSID and password, you can change the default portal SSID and password to a value that only you know.

- wifiRstTimeout: if there is no wifi connection after the specified timeout, The ARR is restarted and a new connection attempted. This procedure is repeated 2 times. 
If still there is no WIFI connection the ARR interrupts the power to the router for 15 seconds and waits "rebootDelay" seconds before restarting again the ARR

- hostPingTimeout: if there is no internet connection to any of the remoteHosts after the specified timeout, the ARR interrupts the power to the router for 15 seconds and waits "rebootDelay" seconds before restarting the ARR

- rebootDelay: when ther ARR interrupts the power to the router, this parameters is the amount of time to wait before restarting the ARR to allow the router to finish its reboot.

The Web portal page example is shown at 
[this link](https://github.com/dariomella/ARR-V1/blob/main/Screenshot%20%20ARR%20(Automatic%20Router%20Rebooter)%20input%20parms.png)

If you connect the USB port to a computer and have the proper driver installed, you can use a teminal program (like PuTTY) to see various status messages produced by ARR
while checking the network.  putty has to be configured with the following parameters:
Speed = 115200
data bits = 8
stop bits = 1
parity = none
flow control = none

When ARR is running the three leds show the status of the conection
LED 1 on =  wifi connected
LED 2 on = gateway reachable
LED 3 on = internet reachable

The possible combinations are:

| 1    | 2    | 3     | meaning                                                                               |
|------|------|-------|---------------------------------------------------------------------------------------|
| OFF  | OFF  | ON    |  parameters setup portal mode. waiting for web server to become active                |
| OFF  | ON   | ON    |  parameters setup portal mode. web server is started to show the parameters page      |
| blink| blink| blink | Fast blinking of all the three leds for about 3 seconds means that a factory reset was requested by pressing the button for more than 15 seconds at power on             |
| OFF  | blink| OFF   | waiting for router to complete (duration is rebootDelay)                              | 
| OFF  | OFF  | OFF   | no wifi no gateway connection - wait for wifiRstTimeout seconds then reboot ARR to retry the connection; if unsuccessful after 3 attempts, reboot router and ARR         |
| ON   | ON   | ON    | wifi ok, gateway (LAN) ok, internet ok - everithing is fine. Monitoring continues normally                                                                              |
| ON   | ON   | OFF   | wifi ok, gateway (LAN) ok, no internet. if the status remains for more than hostPingTimeout seconds, the router and ARR will be rebooted                          |
| ON   | OFF  | OFF   | wifi OK, gateway (LAN) not reachable, no internet. if the status remains for more than hostPingTimeout seconds, the router and ARR will be rebooted                          |

## The Arduino code
To make the code more manageable I have splitted it into several files. Simply put all the .ino and .h modules in the same directory and compile the ARR_V2.ino code

If you don't already have them, you might need to install the following libraries:
- ESPAsyncWebServer https://github.com/mathieucarbou/ESPAsyncWebServer
- ESPping https://github.com/dvarrel/ESPping
