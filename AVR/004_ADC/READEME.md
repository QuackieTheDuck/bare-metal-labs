# The ADC configuration and usage

---

This project purpose was to familiarize myself with the way analog inputs can be used and configured.

### What have I done?

-

### What have I learned?

-

### Important:

Because I've transmitted raw data from the ADC the Arduino IDE was not able to display data correctly. It would be recomended to write a simple script in Python to properly display current value transmitted via UART interface.

### Hardware Connection and Parameters:

- ### Update:

A simple line in Python is enough to calculate the value based on the observed transmission: `print((second_byte << 8) | first_byte)`.
Additionally, I managed to add oscilloscope measurements to the documentation.
Oscilloscope captures confirm accurate readings across the 0–1023 range.
During testing, a calibration issue was identified where an incorrect reference voltage(3.3V instead of 5V) limited the maximum output to ~670, which has since been resolved.
