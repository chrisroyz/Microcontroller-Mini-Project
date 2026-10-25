# Microcontroller-Mini-Project
# Solar Smart Irrigation System

## Overview
A solar-powered irrigation prototype designed to monitor soil moisture and control a water pump automatically.

## Hardware
- Arduino Uno
- Soil moisture sensor
- Relay module
- Mini DC water pump
- 18650 lithium-ion battery
- Solar panel
- TP4056-style charging module

## Working Principle
1. Read soil moisture through analog pin A0.
2. Activate the relay-controlled pump when the soil is dry.
3. Turn the pump off after a short watering burst.
4. Wait for 15 seconds to allow water to spread through the soil.
5. Measure moisture again and repeat if necessary.
6. Keep the pump off when the soil reaches the target moisture level.

## Pin Connections
- Moisture sensor signal: A0
- Relay control signal: D7

## Project Status
Prototype design and control logic documented. Hardware integration, charging safety, and complete automatic operation require verification.

## Future Improvements
- Calibrate moisture thresholds for different soil conditions.
- Add low-battery protection and reliable solar charging.
- Implement low-power sleep mode.
- Add water-level monitoring and dry-run protection.
