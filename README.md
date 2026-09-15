# LDR-LED Closed-Loop Control

I built this project to control the brightness of an LED using feedback from an LDR. An Arduino Uno continuously compares the measured light level with a user-defined setpoint and adjusts the LED brightness through PWM.

## Overview

The idea is simple: instead of setting the LED to a fixed brightness, I wanted the system to automatically maintain a desired light level using feedback from an LDR.

A potentiometer is used to set the desired light level. The Arduino compares this setpoint with the LDR feedback and uses a PID controller to adjust the LED's PWM output and reduce the error between them.

To make the feedback more stable, the LDR and potentiometer signals are filtered using capacitors as well as software filtering.

## System Architecture

The overall control loop is shown below.

![Control Flow diagram](Control/Control_Flow_diagram.png)

The potentiometer provides the reference setpoint. The Arduino compares it with the filtered LDR feedback, calculates the PID control action, and adjusts the LED brightness through PWM. The LDR then measures the resulting light level and feeds it back to the controller.
