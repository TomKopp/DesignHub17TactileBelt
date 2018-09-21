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

## Hardware specifications

ID to Pin assignment
Motor ID:Pin

```
				front
				0:15
		1:16			7:6
2:17							6:10
		3:18			5:11
				4:12
				back
```

## Instalation

This is a Platform.io project.
It is preconfigured for an adafruit_feather_m0 microcontroller.

If you use VS Code or Atome IDE with the Platform.io plugin you only need to `build` and `upload` the project to your Feather M0.
