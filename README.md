I was looking for a way to see if the Grove hub can do multiple I2C devices via the Grove Hub and instead of implementing all devices in a sketch I decided to port the I2C Arduino example to the M5Cardputer.

The initial goal was just to get the addresses of the attached devices, but my next idea is to identify M5Stack modules by name based on their HEX address. Eventually I'd love for this to evolve into an I2C diagnostics thing where some basic readout of devices is possible. But not sure if that'll happen any time soon. 

Note: addresses _are_ in HEX format, but the `0x` prefix is omitted to save screen space. 

- [x] Print HEX addresses of attached I2C devices
- [x] Allow >10 addresses to be listed
- [ ] Allow color cycling for the UI
- [ ] Allow pausing scans (for future functionality)
- [ ] Allow selecting a device to see the (possible) matches for that address
- [ ] Implement simple readout for certain devices (particularly ones that can be done in a couple of lines of code)