#ifndef protocol_h
#define protocol_h
#include "Arduino.h"

#define MAX_BUFFER_LENGTH 63

#define START_OF_PACKET                     0xcc
#define SSID_MSG                            0x0011
#define SSID_CMD                            0x0012
#define SSID_PASSWORD_MSG                   0x0013
#define SSID_PASSWORD_CMD                   0x0014
#define WIFI_REGION_MSG                     0x0015
#define WIFI_REGION_CMD                     0x0016
#define WIFI_MSG                            0x001a
#define VIDEO_ENCODER_RATE_CMD              0x0020
#define VIDEO_DYN_ADJ_RATE_CMD              0x0021
#define EIS_CMD                             0x0024
#define VIDEO_START_CMD                     0x0025
#define VIDEO_RATE_QUERY                    0x0028
#define TAKE_PICTURE_COMMAND                0x0030
#define VIDEO_MODE_CMD                      0x0031
#define VIDEO_RECORD_CMD                    0x0032
#define EXPOSURE_CMD                        0x0034
#define LIGHT_MSG                           0x0035
#define JPEG_QUALITY_MSG                    0x0037
#define ERROR_1_MSG                         0x0043
#define ERROR_2_MSG                         0x0044
#define VERSION_MSG                         0x0045
#define TIME_CMD                            0x0046
#define ACTIVATION_TIME_MSG                 0x0047
#define LOADER_VERSION_MSG                  0x0049
#define STICK_CMD                           0x0050
#define TAKEOFF_CMD                         0x0054
#define LAND_CMD                            0x0055
#define FLIGHT_MSG                          0x0056
#define SET_ALT_LIMIT_CMD                   0x0058
#define FLIP_CMD                            0x005c
#define THROW_AND_GO_CMD                    0x005d
#define PALM_LAND_CMD                       0x005e
#define TELLO_CMD_FILE_SIZE                 0x0062  # pt50
#define TELLO_CMD_FILE_DATA                 0x0063  # pt50
#define TELLO_CMD_FILE_COMPLETE             0x0064  # pt48
#define SMART_VIDEO_CMD                     0x0080
#define SMART_VIDEO_STATUS_MSG              0x0081
#define LOG_HEADER_MSG                      0x1050
#define LOG_DATA_MSG                        0x1051
#define LOG_CONFIG_MSG                      0x1052
#define BOUNCE_CMD                          0x1053
#define CALIBRATE_CMD                       0x1054
#define LOW_BAT_THRESHOLD_CMD               0x1055
#define ALT_LIMIT_MSG                       0x1056
#define LOW_BAT_THRESHOLD_MSG               0x1057
#define ATT_LIMIT_CMD                       0x1058 # Stated incorrectly by Wiki (checked from raw packets)
#define ATT_LIMIT_MSG                       0x1059

class Packet {
  public:
    Packet(String cmd);
    Packet(uint8_t cmd[]);
    Packet(uint16_t cmd, uint8_t pkt_type, uint8_t payload[]);
    Packet(uint16_t cmd);
    void fixup();
    void fixup(uint16_t seq_num);
    // void add_byte(uint8_t val);
    // void add_int16(uint16_t val);
    uint8_t length();
    uint8_t get_buffer(uint8_t position);
    void print_buffer(Stream &interface);
    void add_byte(uint8_t data);
  private:
    uint8_t _buf[MAX_BUFFER_LENGTH];
    uint8_t _buf_fixup[MAX_BUFFER_LENGTH];
    uint8_t _size;
};

#endif
