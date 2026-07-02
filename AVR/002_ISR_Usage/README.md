# ISR Usage and Configuration

---

This project was made to order to learn Interrupt Service Routine (ISR). Functionality of a program is shown in `Logic_analyzer_Dump.png`.

### What have I done?

- Defined an additional `virtual-registry` to store flags.
- Made `setup()` function to handle pin and registers configuration.
- Implemented ISR which changes flag stored in defined earlier `virtual-registry`. no delays and no complex logic in order to keep interruption as short as possible to maintain system responsiveness.

### What have I learned?

- How to configure and use ISR.
- How to identify pins which can handle interruptions.
- How to define `virtual-registry` and use it in order to handle system logic.

### Important:

I noticed that whole system was susceptible to electromagnetic interference (EMI). This can be caused by Logic Analyzer or for example external magnetic fields. Since the Pull-up resistor has high impedance adding additional pull-up resistor would increase noise immunity.

### Hardware Connection:

- **Button:** Connected between `Pin 2 (PD2)` and `GND`.
- **Logic Analyzer:** `CH0` on `D2`, `CH1` on `D13`, `Common GND`.
