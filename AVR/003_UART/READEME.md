# UART Communication with PC

---

This project was made to order to learn UART communication Protocol. Whole Logic Analyzer Dump is saved as `Logic_Analyzer_Dump.sr` and png version is avaliable
as `Logic_Analyzer_Dump_PNG.png` to provide guick view(`Logic_Analyzer_Dump_PNG_Zoom_in.png` shows data transmission).

### What have I done?

- I've taken previously implemented functionalities and added UART alerts sended to a PC.
- Configured whole UART communications using registers.
- Implemented circular buffer - in case of buffer overflow, the oldest data is overwritten to maintain real-time flow.
- Implemented ISR as a UART data sender.

### What have I learned?

- How to configure UART.
- How to maintain system responsivenes during time consuming operations as UART communication.
- How to implement buffers in order to store data that is ready to be sent.

### Important:

As I mentioned before data transmission was implemented in ISR to minimalize latency and maintain system responsiveness. Circular buffer was a way of storing data to be send without blocking processor to process and then send the data.

### Hardware Connection and Parameters:

- UART was configured with `9600` Baudrate and Frame `8N1`.
- **Button:** Connected between `Pin 2 (PD2)` and`GND`.
- **Logic Analyzer:** `CH0` on `D2`, `CH1` on `D13`, `CH2` on `TX (Pin 1)`, `Common GND`.
