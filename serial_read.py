#Written by Kevin O'Brien

import serial
from datetime import datetime

#Grab current time in string format to create collision-proof filenames.
now = datetime.now().strftime("%Y-%m-%d--%H-%M-%S")

#Establish a serial connection. You may need to change the port based on your system.
ser = serial.Serial(
	"COM5", 
	baudrate = 115200,
	bytesize = serial.EIGHTBITS,
	parity = serial.PARITY_NONE,
	stopbits = serial.STOPBITS_ONE, 
	timeout = 0.0001,
	xonxoff = 0,
	rtscts = 0);

#In the directory where this file is run, create a CSV based on start datetime and write a header into it.
out_file = open("{}.csv".format(now),"w")
out_file.write("Counter,ADC\n")

#Infinite loop but breaks cleanly with CTRL+C. (Only tested on Windows systems.)
print("Press CTRL+C to end.")
try:
	while True:
		while ser.in_waiting >= 1:
			read_val = ser.readline().decode("utf-8")
			read_val = read_val.strip("\r").strip("\n")
			#Handles double reads
			if read_val.count(",") == 2:
				x = len(read_val)//2
				a = read_val[0:x]
				b = read_val[x+1:]
				out_file.write(a)
				out_file.write(b)
			else:
				out_file.write(read_val)
			ser.reset_input_buffer()

except KeyboardInterrupt:
	pass
