#!/usr/bin/python3

# Create the packet for "takeoff"

from protocol import *
from utils import *
import crc

def main():
	pkt = Packet(TAKEOFF_CMD) #TAKEOFF_CMD defined in protocol.py
	pkt.fixup()
	print(":".join("{:02x}".format(ord(chr(c))) for c in pkt.get_buffer()))

if __name__ == "__main__":
	main()
