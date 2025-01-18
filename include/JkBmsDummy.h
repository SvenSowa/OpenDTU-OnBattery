// #pragma once

// #include <Arduino.h>
// #include <vector>
// #include "MessageOutput.h"

// namespace JkBms {

// class DummySerial {
//     public:
//         DummySerial() = default;
//         void begin(uint32_t, uint32_t, int8_t, int8_t) {
//             MessageOutput.println("JK BMS Dummy Serial: begin()");
//         }
//         void end() { MessageOutput.println("JK BMS Dummy Serial: end()"); }
//         void flush() { }
//         bool availableForWrite() const { return true; }
//         size_t write(const uint8_t *buffer, size_t size) {
//             MessageOutput.printf("JK BMS Dummy Serial: write(%d Bytes)\r\n", size);
//             _byte_idx = 0;
//             _msg_idx = (_msg_idx + 1) % _data.size();
//             return size;
//         }
//         bool available() const {
//             return _byte_idx < _data[_msg_idx].size();
//         }
//         int read() {
//             if (_byte_idx >= _data[_msg_idx].size()) { return 0; }
//             return _data[_msg_idx][_byte_idx++];
//         }

//     private:
//         std::vector<std::vector<uint8_t>> const _data =
//         {
//             {
//                 0x4e, 0x57, 0x01, 0x21, 0x00, 0x00, 0x00, 0x00,
//                 0x06, 0x00, 0x01, 0x79, 0x30, 0x01, 0x0c, 0xfb,
//                 0x02, 0x0c, 0xfb, 0x03, 0x0c, 0xfb, 0x04, 0x0c,
//                 0xfb, 0x05, 0x0c, 0xfb, 0x06, 0x0c, 0xfb, 0x07,
//                 0x0c, 0xfb, 0x08, 0x0c, 0xf7, 0x09, 0x0d, 0x01,
//                 0x0a, 0x0c, 0xf9, 0x0b, 0x0c, 0xfb, 0x0c, 0x0c,
//                 0xfb, 0x0d, 0x0c, 0xfb, 0x0e, 0x0c, 0xf8, 0x0f,
//                 0x0c, 0xf9, 0x10, 0x0c, 0xfb, 0x80, 0x00, 0x1a,
//                 0x81, 0x00, 0x12, 0x82, 0x00, 0x12, 0x83, 0x14,
//                 0xc3, 0x84, 0x83, 0xf4, 0x85, 0x2e, 0x86, 0x02,
//                 0x87, 0x00, 0x15, 0x89, 0x00, 0x00, 0x13, 0x52,
//                 0x8a, 0x00, 0x10, 0x8b, 0x00, 0x00, 0x8c, 0x00,
//                 0x03, 0x8e, 0x16, 0x80, 0x8f, 0x12, 0xc0, 0x90,
//                 0x0e, 0x10, 0x91, 0x0c, 0xda, 0x92, 0x00, 0x05,
//                 0x93, 0x0b, 0xb8, 0x94, 0x0c, 0x80, 0x95, 0x00,
//                 0x05, 0x96, 0x01, 0x2c, 0x97, 0x00, 0x28, 0x98,
//                 0x01, 0x2c, 0x99, 0x00, 0x28, 0x9a, 0x00, 0x1e,
//                 0x9b, 0x0b, 0xb8, 0x9c, 0x00, 0x0a, 0x9d, 0x01,
//                 0x9e, 0x00, 0x64, 0x9f, 0x00, 0x50, 0xa0, 0x00,
//                 0x64, 0xa1, 0x00, 0x64, 0xa2, 0x00, 0x14, 0xa3,
//                 0x00, 0x46, 0xa4, 0x00, 0x46, 0xa5, 0x00, 0x00,
//                 0xa6, 0x00, 0x02, 0xa7, 0xff, 0xec, 0xa8, 0xff,
//                 0xf6, 0xa9, 0x10, 0xaa, 0x00, 0x00, 0x00, 0xe6,
//                 0xab, 0x01, 0xac, 0x01, 0xad, 0x04, 0x4d, 0xae,
//                 0x01, 0xaf, 0x00, 0xb0, 0x00, 0x0a, 0xb1, 0x14,
//                 0xb2, 0x32, 0x32, 0x31, 0x31, 0x38, 0x37, 0x00,
//                 0x00, 0x00, 0x00, 0xb3, 0x00, 0xb4, 0x62, 0x65,
//                 0x6b, 0x69, 0x00, 0x00, 0x00, 0x00, 0xb5, 0x32,
//                 0x33, 0x30, 0x36, 0xb6, 0x00, 0x01, 0x4a, 0xc3,
//                 0xb7, 0x31, 0x31, 0x2e, 0x58, 0x57, 0x5f, 0x53,
//                 0x31, 0x31, 0x2e, 0x32, 0x36, 0x32, 0x48, 0x5f,
//                 0xb8, 0x00, 0xb9, 0x00, 0x00, 0x00, 0xe6, 0xba,
//                 0x62, 0x65, 0x6b, 0x69, 0x00, 0x00, 0x00, 0x00,
//                 0x00, 0x00, 0x00, 0x00, 0x4a, 0x4b, 0x5f, 0x42,
//                 0x31, 0x41, 0x32, 0x34, 0x53, 0x31, 0x35, 0x50,
//                 0xc0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x68, 0x00,
//                 0x00, 0x53, 0xbb
//             },
//             {
//                 0x4e, 0x57, 0x01, 0x21, 0x00, 0x00, 0x00, 0x00,
//                 0x06, 0x00, 0x01, 0x79, 0x30, 0x01, 0x0c, 0xc0,
//                 0x02, 0x0c, 0xc1, 0x03, 0x0c, 0xc0, 0x04, 0x0c,
//                 0xc4, 0x05, 0x0c, 0xc4, 0x06, 0x0c, 0xc2, 0x07,
//                 0x0c, 0xc2, 0x08, 0x0c, 0xc1, 0x09, 0x0c, 0xba,
//                 0x0a, 0x0c, 0xc1, 0x0b, 0x0c, 0xc2, 0x0c, 0x0c,
//                 0xc2, 0x0d, 0x0c, 0xc2, 0x0e, 0x0c, 0xc4, 0x0f,
//                 0x0c, 0xc2, 0x10, 0x0c, 0xc1, 0x80, 0x00, 0x1b,
//                 0x81, 0x00, 0x1b, 0x82, 0x00, 0x1a, 0x83, 0x14,
//                 0x68, 0x84, 0x03, 0x70, 0x85, 0x3c, 0x86, 0x02,
//                 0x87, 0x00, 0x19, 0x89, 0x00, 0x00, 0x16, 0x86,
//                 0x8a, 0x00, 0x10, 0x8b, 0x00, 0x00, 0x8c, 0x00,
//                 0x07, 0x8e, 0x16, 0x80, 0x8f, 0x12, 0xc0, 0x90,
//                 0x0e, 0x10, 0x91, 0x0c, 0xda, 0x92, 0x00, 0x05,
//                 0x93, 0x0b, 0xb8, 0x94, 0x0c, 0x80, 0x95, 0x00,
//                 0x05, 0x96, 0x01, 0x2c, 0x97, 0x00, 0x28, 0x98,
//                 0x01, 0x2c, 0x99, 0x00, 0x28, 0x9a, 0x00, 0x1e,
//                 0x9b, 0x0b, 0xb8, 0x9c, 0x00, 0x0a, 0x9d, 0x01,
//                 0x9e, 0x00, 0x64, 0x9f, 0x00, 0x50, 0xa0, 0x00,
//                 0x64, 0xa1, 0x00, 0x64, 0xa2, 0x00, 0x14, 0xa3,
//                 0x00, 0x46, 0xa4, 0x00, 0x46, 0xa5, 0x00, 0x00,
//                 0xa6, 0x00, 0x02, 0xa7, 0xff, 0xec, 0xa8, 0xff,
//                 0xf6, 0xa9, 0x10, 0xaa, 0x00, 0x00, 0x00, 0xe6,
//                 0xab, 0x01, 0xac, 0x01, 0xad, 0x04, 0x4d, 0xae,
//                 0x01, 0xaf, 0x00, 0xb0, 0x00, 0x0a, 0xb1, 0x14,
//                 0xb2, 0x32, 0x32, 0x31, 0x31, 0x38, 0x37, 0x00,
//                 0x00, 0x00, 0x00, 0xb3, 0x00, 0xb4, 0x62, 0x65,
//                 0x6b, 0x69, 0x00, 0x00, 0x00, 0x00, 0xb5, 0x32,
//                 0x33, 0x30, 0x36, 0xb6, 0x00, 0x01, 0x7f, 0x2a,
//                 0xb7, 0x31, 0x31, 0x2e, 0x58, 0x57, 0x5f, 0x53,
//                 0x31, 0x31, 0x2e, 0x32, 0x36, 0x32, 0x48, 0x5f,
//                 0xb8, 0x00, 0xb9, 0x00, 0x00, 0x00, 0xe6, 0xba,
//                 0x62, 0x65, 0x6b, 0x69, 0x00, 0x00, 0x00, 0x00,
//                 0x00, 0x00, 0x00, 0x00, 0x4a, 0x4b, 0x5f, 0x42,
//                 0x31, 0x41, 0x32, 0x34, 0x53, 0x31, 0x35, 0x50,
//                 0xc0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x68, 0x00,
//                 0x00, 0x4f, 0xc1
//             },
//             {
//                 0x4e, 0x57, 0x01, 0x21, 0x00, 0x00, 0x00, 0x00,
//                 0x06, 0x00, 0x01, 0x79, 0x30, 0x01, 0x0c, 0x13,
//                 0x02, 0x0c, 0x12, 0x03, 0x0c, 0x0f, 0x04, 0x0c,
//                 0x15, 0x05, 0x0c, 0x0d, 0x06, 0x0c, 0x13, 0x07,
//                 0x0c, 0x16, 0x08, 0x0c, 0x13, 0x09, 0x0b, 0xdb,
//                 0x0a, 0x0b, 0xf6, 0x0b, 0x0c, 0x17, 0x0c, 0x0b,
//                 0xf5, 0x0d, 0x0c, 0x16, 0x0e, 0x0c, 0x1a, 0x0f,
//                 0x0c, 0x1b, 0x10, 0x0c, 0x1c, 0x80, 0x00, 0x18,
//                 0x81, 0x00, 0x18, 0x82, 0x00, 0x18, 0x83, 0x13,
//                 0x49, 0x84, 0x00, 0x00, 0x85, 0x00, 0x86, 0x02,
//                 0x87, 0x00, 0x23, 0x89, 0x00, 0x00, 0x20, 0x14,
//                 0x8a, 0x00, 0x10, 0x8b, 0x00, 0x08, 0x8c, 0x00,
//                 0x05, 0x8e, 0x16, 0x80, 0x8f, 0x12, 0xc0, 0x90,
//                 0x0e, 0x10, 0x91, 0x0c, 0xda, 0x92, 0x00, 0x05,
//                 0x93, 0x0b, 0xb8, 0x94, 0x0c, 0x80, 0x95, 0x00,
//                 0x05, 0x96, 0x01, 0x2c, 0x97, 0x00, 0x28, 0x98,
//                 0x01, 0x2c, 0x99, 0x00, 0x28, 0x9a, 0x00, 0x1e,
//                 0x9b, 0x0b, 0xb8, 0x9c, 0x00, 0x0a, 0x9d, 0x01,
//                 0x9e, 0x00, 0x64, 0x9f, 0x00, 0x50, 0xa0, 0x00,
//                 0x64, 0xa1, 0x00, 0x64, 0xa2, 0x00, 0x14, 0xa3,
//                 0x00, 0x46, 0xa4, 0x00, 0x46, 0xa5, 0x00, 0x00,
//                 0xa6, 0x00, 0x02, 0xa7, 0xff, 0xec, 0xa8, 0xff,
//                 0xf6, 0xa9, 0x10, 0xaa, 0x00, 0x00, 0x00, 0xe6,
//                 0xab, 0x01, 0xac, 0x01, 0xad, 0x04, 0x4d, 0xae,
//                 0x01, 0xaf, 0x00, 0xb0, 0x00, 0x0a, 0xb1, 0x14,
//                 0xb2, 0x32, 0x32, 0x31, 0x31, 0x38, 0x37, 0x00,
//                 0x00, 0x00, 0x00, 0xb3, 0x00, 0xb4, 0x62, 0x65,
//                 0x6b, 0x69, 0x00, 0x00, 0x00, 0x00, 0xb5, 0x32,
//                 0x33, 0x30, 0x36, 0xb6, 0x00, 0x02, 0x17, 0x10,
//                 0xb7, 0x31, 0x31, 0x2e, 0x58, 0x57, 0x5f, 0x53,
//                 0x31, 0x31, 0x2e, 0x32, 0x36, 0x32, 0x48, 0x5f,
//                 0xb8, 0x00, 0xb9, 0x00, 0x00, 0x00, 0xe6, 0xba,
//                 0x62, 0x65, 0x6b, 0x69, 0x00, 0x00, 0x00, 0x00,
//                 0x00, 0x00, 0x00, 0x00, 0x4a, 0x4b, 0x5f, 0x42,
//                 0x31, 0x41, 0x32, 0x34, 0x53, 0x31, 0x35, 0x50,
//                 0xc0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x68, 0x00,
//                 0x00, 0x45, 0xce
//             },
//             {
//                 0x4e, 0x57, 0x01, 0x21, 0x00, 0x00, 0x00, 0x00,
//                 0x06, 0x00, 0x01, 0x79, 0x30, 0x01, 0x0c, 0x07,
//                 0x02, 0x0c, 0x0a, 0x03, 0x0c, 0x0b, 0x04, 0x0c,
//                 0x08, 0x05, 0x0c, 0x05, 0x06, 0x0c, 0x0b, 0x07,
//                 0x0c, 0x07, 0x08, 0x0c, 0x0a, 0x09, 0x0c, 0x08,
//                 0x0a, 0x0c, 0x06, 0x0b, 0x0c, 0x0a, 0x0c, 0x0c,
//                 0x05, 0x0d, 0x0c, 0x0a, 0x0e, 0x0c, 0x0a, 0x0f,
//                 0x0c, 0x0a, 0x10, 0x0c, 0x0a, 0x80, 0x00, 0x06,
//                 0x81, 0x00, 0x03, 0x82, 0x00, 0x03, 0x83, 0x13,
//                 0x40, 0x84, 0x00, 0x00, 0x85, 0x29, 0x86, 0x02,
//                 0x87, 0x00, 0x01, 0x89, 0x00, 0x00, 0x01, 0x0a,
//                 0x8a, 0x00, 0x10, 0x8b, 0x02, 0x00, 0x8c, 0x00,
//                 0x02, 0x8e, 0x16, 0x80, 0x8f, 0x10, 0x40, 0x90,
//                 0x0e, 0x10, 0x91, 0x0d, 0xde, 0x92, 0x00, 0x05,
//                 0x93, 0x0a, 0x28, 0x94, 0x0a, 0x5a, 0x95, 0x00,
//                 0x05, 0x96, 0x01, 0x2c, 0x97, 0x00, 0x28, 0x98,
//                 0x01, 0x2c, 0x99, 0x00, 0x28, 0x9a, 0x00, 0x1e,
//                 0x9b, 0x0b, 0xb8, 0x9c, 0x00, 0x0a, 0x9d, 0x01,
//                 0x9e, 0x00, 0x5a, 0x9f, 0x00, 0x50, 0xa0, 0x00,
//                 0x64, 0xa1, 0x00, 0x64, 0xa2, 0x00, 0x14, 0xa3,
//                 0x00, 0x37, 0xa4, 0x00, 0x37, 0xa5, 0x00, 0x03,
//                 0xa6, 0x00, 0x05, 0xa7, 0xff, 0xec, 0xa8, 0xff,
//                 0xf6, 0xa9, 0x10, 0xaa, 0x00, 0x00, 0x00, 0xe6,
//                 0xab, 0x01, 0xac, 0x01, 0xad, 0x04, 0x4d, 0xae,
//                 0x01, 0xaf, 0x00, 0xb0, 0x00, 0x0a, 0xb1, 0x14,
//                 0xb2, 0x32, 0x32, 0x31, 0x31, 0x38, 0x37, 0x00,
//                 0x00, 0x00, 0x00, 0xb3, 0x00, 0xb4, 0x62, 0x65,
//                 0x6b, 0x69, 0x00, 0x00, 0x00, 0x00, 0xb5, 0x32,
//                 0x33, 0x30, 0x36, 0xb6, 0x00, 0x03, 0xb7, 0x2d,
//                 0xb7, 0x31, 0x31, 0x2e, 0x58, 0x57, 0x5f, 0x53,
//                 0x31, 0x31, 0x2e, 0x32, 0x36, 0x32, 0x48, 0x5f,
//                 0xb8, 0x00, 0xb9, 0x00, 0x00, 0x00, 0xe6, 0xba,
//                 0x62, 0x65, 0x6b, 0x69, 0x00, 0x00, 0x00, 0x00,
//                 0x00, 0x00, 0x00, 0x00, 0x4a, 0x4b, 0x5f, 0x42,
//                 0x31, 0x41, 0x32, 0x34, 0x53, 0x31, 0x35, 0x50,
//                 0xc0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x68, 0x00,
//                 0x00, 0x41, 0x7b
//             }
//         };
//         size_t _msg_idx = 0;
//         size_t _byte_idx = 0;
// };

// } /* namespace JkBms */
