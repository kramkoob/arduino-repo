#!/usr/bin/python3

# Create the packet for "takeoff"

from protocol import *
from utils import *
import crc

def main():
        pkt = Packet(SET_ALT_LIMIT_CMD)
        pkt.add_byte(0x1e)  # 30m
        pkt.add_byte(0x00)
        self.send_packet(pkt)
	print(":".join("{:02x}".format(ord(chr(c))) for c in pkt.get_buffer()))

if __name__ == "__main__":
	main()
