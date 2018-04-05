# DesignHub17TactileBelt
Code for microcontroller to control the tactile belt for DesignHub 2017 app


The tactile belt reads from its USB serial port, parses the incomming string and builds intensity lists for the atached motors.
The serial port is read as fast as possible to act fast upon incomming commands.
These commands will be read with the configured frequency (4Hz atm) and update the motors and thereby the vibration intensity.
The motors will react as fast as possible to the update.

The accepted serial string should look like this:

```
7=255,100,255,100,255&6=255,100,255,100,255&5=255,100,255,100,255\r\n
```

Explanation:\
`7=` represents the motor id\
`255,100,255,100,255&` these are the pwm intensities for this motor for each tick followed by the motor seperator\
`\r\n` the line ending signals the end of this command. This is typically a CRLF, but the algorithm is fine with just the LF.
