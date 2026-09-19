import serial


serial_port = serial.Serial(port='/ttyACM0', baudrate=115200, timeout=1)

while True:
    data = serial_port.readline()
    # Decode and strip whitespace to avoid errors and double newlines
    try:
        decoded_data = data.decode('utf-8').strip()
        if decoded_data:
            print(decoded_data)
    except UnicodeDecodeError:
        pass # Ignore corrupted transmission bytes