# AVR, 8-bit Cheat Sheet (working on Arduino UNO)

---

## GPIO

1.  `DDRx` (Data Direction Register):

- `1` = Output,
- `0` = Input,

2. `PORTx` (Port Register):

- If set to `1` (Output):
  - `1` = VCC (High),
  - `0` = GND (Low),
- If coresponding `DDRx` bit is set to `0` (Input) then `1` activates the internal Pull-up resistor (~50k Ohm),

3. `PINx` reads out a physical current pin status.

## Binary operations

1. Set: can be done using `| (OR)` and `<< (bitwise left shift)`,
2. Clear: can be done using `& (AND)` and `~ (negation)`,
3. Toggle: can be done using `^ (XOR)`,
4. Single bit read: can be done `& (and)` combined with proper mask.

## ISR Configuration

#### For Arduino interruptions can be triggered from `D2` and `D3`.

1. `EICRA` Register where you can configure what exacly will trigger an interruption:

| `ISCx1` | `ISCx0` | Meaning          |
| ------- | ------- | ---------------- |
| `0`     | `0`     | Low Level        |
| `0`     | `1`     | Any Logic Change |
| `1`     | `0`     | Falling Edge     |
| `1`     | `1`     | Rising Edge      |

2. `EIMSK` register where you turn on interruption triggering (INT0, INT1...),
3. `SREG` bits in this registry turns on the ISR. Usage: `sei()` to turn on and `cli()` to turn off (Important: this functions only set proper bit to `1` or `0` ),

## Creating Virtual Registry

#### Can be used to sotre flags

1. It is important to use `volatile` type when creating a registry if flags are used inside ISR and used later in `main()`,
2. The 8 bit registry structure is defined as `uint8_t` and then by using `typedef struct` an internal structure of a registry can be defined,
3. To inform the compilator that flags are the size of a single bit `: 1` should be used when defining flag names (e.g `FlagName : 1;`),
4. Flags can be accesed by `RegistyName.FlagName`

## UART Configuration

1. Setting the communication parameters:

- `Baudrate` configuration is done by configuring two registers `UBRRxH` and `UBRRxL`:

  | Register | Binary operation          | Role                     |
  | -------- | ------------------------- | ------------------------ |
  | `UBRRxH` | `[(`Value` >> 8) & 0x0F]` | 4 most significant bits  |
  | `UBRRxL` | `[`Value` & 0xFF]`        | 8 least significant bits |

`Value` is calculates by equation: `[`Value` = f / (X \* Baud) - 1]` where: f - system clock frequency, X is variable dependant of perating mode for normal mode X = 16, Baud - Baud rate

- Number of data bits in a frame is configured with two bits (`UCSZx1:0`) in register `UCSRxC`:

  | `UCSZx1` | `UCSZx0` | Bits in frame |
  | -------- | -------- | ------------- |
  | `0`      | `0`      | 5-bit         |
  | `0`      | `1`      | 6-bit         |
  | `1`      | `0`      | 7-bit         |
  | `1`      | `1`      | 8-bit         |

**Note**: For standard modes (5-8 bits), UCSZx2 in UCSRxB must be `0`.

- Stop bit should be configured with `USBSx` bit in `UCSRxC` register:

  | `USBSx` | Number of stop bits |
  | ------- | ------------------- |
  | `0`     | 1-bit               |
  | `1`     | 2-bit               |

- Parity mode needs to be configured with two bits (`UPMx1:0`) in register `UCSR0C`:

  | `UPMx1` | `UPMx0` | Parity mode |
  | ------- | ------- | ----------- |
  | `0`     | `0`     | Disabled    |
  | `0`     | `1`     | Reserved    |
  | `1`     | `0`     | Even parity |
  | `1`     | `1`     | Odd parity  |

2. After communication parameters setup Transmission and Reciving pins should be configured with two bits (`TXENx` and `RXENx`) in register `UCSRxB`:

| `TXENx` | `RXENx` | Status            |
| ------- | ------- | ----------------- |
| `0`     | `0`     | UART turned off   |
| `0`     | `1`     | Only recieving    |
| `1`     | `0`     | Only transmission |
| `1`     | `1`     | Both turned on    |

3. To maintain system responsivenes and low latency it's highly recommend to use two following things to handle the UART communication:

- ISR to send and recieve data asynchronoulsy. There are three ISR vectors which can be used:
  | Vector | Register | Meaning |
  | `UDRIEx` | `UCSRxB` |USART Data Register Empty |
  | `RXCIEx` | `UCSRxB` |RX Complete |
  | `TXCIEx` | `UCSRxB` |TX Complete |

- To avoid processor freeze while operating on data and registers I used circular buffer logic:

## ADC Configuration:

1. Configuration od ADC is bone by configuring `ADCSRA` registry:

- ADC is enabled by proper configuration of `ADEN` bit:

  | `ADTS2` | Status       |
  | ------- | ------------ |
  | `0`     | ADC disabled |
  | `1`     | ADC enabled  |

- In single conversion mode conversion is triggered by writting `1` to the `ADCS` bit

- Auto trigger is configured by `ADTS` bit:

  | `ADTS` | Status                  |
  | ------ | ----------------------- |
  | `0`    | Auto trigger enabled    |
  | `1`    | External trigger enable |

- ADC Interrupt can be enabled by configuring `ADIE` bit:

- Prescaler is configured by `ADPSx` bits:

2. Configuring the way ADC works can be done by configuring bits in `ADCSRB` registry:

- Trigger souce of the ADC can be chosen by configuring following bits:

  | `ADTS2` | `ADTS1` | `ADTS0` | Trigger                        |
  | ------- | ------- | ------- | ------------------------------ |
  | `0`     | `0`     | `0`     | Free run mode                  |
  | `0`     | `0`     | `1`     | Analog comparator              |
  | `0`     | `1`     | `0`     | External interrupt             |
  | `0`     | `1`     | `1`     | Timer/Compare match A          |
  | `1`     | `0`     | `0`     | Timer/Counter0 overflow        |
  | `1`     | `0`     | `1`     | Timer/Counter1 compare match B |
  | `1`     | `1`     | `0`     | Timer/Counter1 overflow        |
  | `1`     | `1`     | `1`     | Capture event                  |

- Analog comparator multiplexer enable can be configured with `ACME` bit if the `ADEN` bit in `ADCSRA` is set to `0`:

  | `ACME` | `ADEN` (`ADCSRA` registry) | Status                                                            |
  | ------ | -------------------------- | ----------------------------------------------------------------- |
  | `0`    | `0`                        | `AIN1` is provided to negative input of Analog Comparator         |
  | `1`    | `0`                        | Allows to choose `ADCx` to be negative input of Analog comparator |

3. The digital input on ADC pin can be dsiable by configuring `DIDR0` register:

- When `ADCxD` bit is set to `1` the corresponding pin does no longer works as digital input which helps reduce power usage. The corresponding `PIN` register will be read as 0 as long as the corresponding `ADCxD` bit is set as `1`.

- Bits from 7:6 are reserved however they should be always written to `0` when configuring `DIDR0` register in order to ensure compatibility with future devices.

4. Multiplexer is configured by `ADMUX` registry:

- The `REFS1` and `REFS0` bits configure the reference voltage:

  | `REFS1` | `REFS0` | Status   |
  | ------- | ------- | -------- |
  | `0`     | `0`     |          |
  | `0`     | `1`     |          |
  | `1`     | `0`     | Reserved |
  | `1`     | `1`     |          |

- The `ADLAR` bit is responsible for the way the ADC conversion is represented:

  | `ADLAR` | Adjust mode |
  | ------- | ----------- |
  | `0`     |             |
  | `1`     |             |

- The `MUXx` bits are responsible for channel selection:

  | `MUX3` | `MUX2` | `MUX1` | `MUX0` | Selected channel |
  | ------ | ------ | ------ | ------ | ---------------- |
  | `0`    | `0`    | `0`    | `0`    |                  |
  | `0`    | `0`    | `0`    | `1`    |                  |
  | `0`    | `0`    | `1`    | `0`    |                  |
  | `0`    | `0`    | `1`    | `1`    |                  |
  | `0`    | `1`    | `0`    | `0`    |                  |
  | `0`    | `1`    | `0`    | `1`    |                  |
  | `0`    | `1`    | `1`    | `0`    |                  |
  | `0`    | `1`    | `1`    | `1`    |                  |
  | `1`    | `0`    | `0`    | `0`    |                  |
  | `1`    | `0`    | `0`    | `1`    |                  |
  | `1`    | `0`    | `1`    | `0`    |                  |
  | `1`    | `0`    | `1`    | `1`    |                  |
  | `1`    | `1`    | `0`    | `0`    |                  |
  | `1`    | `1`    | `0`    | `1`    |                  |
  | `1`    | `1`    | `1`    | `0`    |                  |
  | `1`    | `1`    | `1`    | `1`    |                  |

5. Reading data from ADC is done by reading `ADCL` and `ADCH`(to which side is it adjusted is determined by the `ADLAR` bit).
