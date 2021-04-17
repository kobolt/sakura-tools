#!/usr/bin/python

import serial
import time

class Sakura(object):
	def __init__(self, port):
		self.s = serial.Serial()
		self.s.port = port
		self.s.baudrate = 115200
		self.s.bytesize = serial.EIGHTBITS
		self.s.parity = serial.PARITY_NONE
		self.s.stopbits = serial.STOPBITS_ONE
		self.s.xonxoff = False
		self.s.rtscts = False
		self.s.dsrdtr = False

		self.s.setDTR(False)
		self.s.open()
		self.s.flushInput()
		self.s.flushOutput()
	
	def __del__(self):
		self.s.close()

	def _command(self, cmd):
		print ">", cmd
		for char in cmd:
			self.s.write(char) # Write one character at a time...
			time.sleep(0.01)
			self.s.read(1)     # ...and read the echo.
		self.s.write("\r") # Finish command...
		time.sleep(0.01)
		self.s.read(10)    # ...and read the prompt.

	def script(self, filename):
		self._command("stop")
		self._command("d1 off")
		self._command("d2 off")
		self._command("d3 off")
		self._command("d4 off")
		self._command("clear")
		with open(filename) as fh:
			for line_no, line in enumerate(fh):
				self._command("%s %s" % (line_no, line.strip()))
		self._command("run")

if __name__ == "__main__":
	import sys
	s = Sakura("/dev/ttyACM0")

	if len(sys.argv) > 1:
		s.script(sys.argv[1])
	else:
		print "Usage: %s <script file>" % (sys.argv[0])

