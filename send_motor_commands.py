import serial
import time

with open("LumiAPI/motor1_angle.txt", 'r') as file:
    # Read the contents of the file
    file_contents = file.read()

port = '/dev/ttyACM0'

ser = serial.Serial(port, 9600)  # Change 'COM3' to the name of your serial port
file = open('data.txt', 'w')

top_degree_lim = 180

m1_pos = int(file_contents)

def move_to(m1):
        # Move the robot arm, first motor rotates the stem of the lamp to m1 degrees (0-180)
        if (m1 < 0 or m1 > top_degree_lim):
            return
        
        while True:
            data2 = "m{},{}\n".format(m1_pos,m1)
            serial.write(data2.encode()) 
            time.sleep(2) # ADJUST THIS (if this delay is too short, then actions might happen multiple times)
            if (serial.in_waiting > 0):
                datam = serial.readline().decode().strip()
                file.write(datam + '\n')
                break
        m1_pos = m1
        with open('LumiAPI/motor1_angle.txt', 'w') as f:
            # Write the number to the file
            f.write(str(m1_pos))


move_to(0)
move_to(180)
