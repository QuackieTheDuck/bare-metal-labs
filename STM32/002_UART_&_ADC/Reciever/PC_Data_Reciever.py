import serial

serial_port = serial.Serial(port='/dev/ttyACM0 ',baudrate=115200 )  # Hardcoded port since this project is not about Pyserial

while True:
    data = serial_port.readline()
    data = str(data, 'UTF-8')
    print(data)