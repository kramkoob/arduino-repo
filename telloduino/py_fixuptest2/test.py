#!/usr/bin/python3

# Create the packet for "takeoff"

from protocol import *
from utils import *
import crc

def main():
	pkt = Packet(SET_ALT_LIMIT_CMD)
	pkt.add_byte(0x1e)  # 30m
	pkt.add_byte(0x00)
	print(":".join("{:02x}".format(ord(chr(c))) for c in pkt.get_buffer()).upper())

	pkt = Packet(TAKEOFF_CMD)
	pkt.fixup()
	print(":".join("{:02x}".format(ord(chr(c))) for c in pkt.get_buffer()).upper())

	pkt = Packet(LAND_CMD)
	pkt.add_byte(0x00)
	pkt.fixup()
	print(":".join("{:02x}".format(ord(chr(c))) for c in pkt.get_buffer()).upper())

if __name__ == "__main__":
	main()
