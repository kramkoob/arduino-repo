#!/usr/bin/python3

import crc

def main():
	str = "Hello, world!"
	buf = bytearray(str, 'utf-8')

	print(str)
	print(crc.crc8(buf))
	print(crc.crc16(buf))

if __name__ == "__main__":
	main()
