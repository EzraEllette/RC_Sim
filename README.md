# RC SIM

## Description
This repository contains ESP32 firmware and a node client for a remote control car interface with a driving simulator. The simulator is a simple NodeJS application that allows you to control a remote control car using your steering wheel and pedal. The ESP32 firmware is responsible for reading the remote control signals and sending them to the simulator. The simulator is responsible for sending the remote control signals to the ESP32 firmware.

## Future
This project is still in development. The following features are planned:
- [ ] Add support for multiple steering wheels
- [ ] SDR support to reduce cost of hardware
- [ ] Add support for multiple rc controllers
- [ ] Use steering data to rotate camera for improved driving experience and visibility
- [ ] Add support for multiple cameras
- [ ] Add support for clutch simulation
- [ ] Simulate gearing and calculate accurate speed
