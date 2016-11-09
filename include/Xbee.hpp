#pragma once

#ifndef XBEE_HP
#define XBEE_HP

#include <cstdint>
#include <string>
#include <sstream>
#include <typeinfo>
#include <type_traits>

#include <iostream>

namespace XBEE {
    const uint8_t kMaxChecksum = 0xFF;

    enum class BroadcastType_64 : uint64_t {
        RESERVE_COORDINATOR = 0x0000000000000000,
        ALL_ROUTERS = 0x000000000000FFFF,
        UNKNOWN = 0xFFFFFFFFFFFFFFFF
    };

    enum class BroadcastType_16 : uint16_t {
        ALL_ROUTERS = 0xFFFC,
        NON_SLEEPY = 0xFFFD,
        DEFAULT = 0xFFFE,
        ALL_SLEEPY = 0xFFFF
    };

    enum class FrameType : uint16_t {
        TX_TRANSMIT_REQUEST_64 = 0x00,
        TX_TRANSMIT_REQUEST_16 = 0x01,
        REMOTE_AT_COMMAND_WIFI = 0x07,
        AT_COMMAND = 0x08,
        AT_COMMAND_QUEUE = 0x09,
        TRANSMIT_REQUEST = 0x10,
        EXPLICIT_ADDR_COMMAND_FRAME = 0x11,
        TX_METAFRAME = 0x16,
        REMOTE_AT_COMMAND = 0x17,
        TX_IPV4 = 0x20,
        CREATE_SRC_ROUTE = 0x21,
        REGISTER_JOINING_DEVICE = 0x24,
        PUT_REQUEST = 0x28,
        DEVICE_RESPONSE = 0x2A,
        RX_PACKET_64 = 0x80,
        RX_PACKET_16 = 0x81,
        RX_PACKET_64_IO = 0x82,
        RX_PACKET_16_IO = 0x83,
        REMOTE_AT_COMMAND_RESPONSE_WIFI = 0x87,
        AT_COMMAND_RESPONSE = 0x88,
        TX_TRANSMIT_STATUS = 0x89,
        MODEM_STATUS = 0x8A,
        TRANSMIT_STATUS = 0x8B,
        ROUTE_INFORMATION_PACKET = 0x8D,
        AGGREGATE_ADDR_UPDATE = 0x8F,
        RECIEVE_PACKET = 0x90,
        RX_EXPLICIT = 0x91,
        RX_DATA_SAMPLE_IO = 0x92,
        XBEE_SENSOR_READ = 0x94,
        NODE_IDENTIFICATION = 0x95,
        REMOTE_AT_COMMAND_RESPONSE = 0x97,
        EXTENDED_MODEM_STATUS = 0x98,
        OTA_FIRMWARE_UPDATE_STATUS = 0xA0,
        ROUTE_RECORD = 0xA1,
        DEVICE_AUTHENTICATED = 0xA2,
        MANY_TO_ONE_ROUTE_REQUEST = 0xA3,
        REGISTER_JOINING_DEVICE_STATUS = 0xA4,
        JOIN_NOTIFICATION_STATUS = 0xA5,
        RX_METAFRAME = 0xA6,
        RX_IPV4 = 0xB0,
        PUT_RESPONSE = 0xB8,
        DEVICE_REQUEST = 0xB9,
        DEVICE_RESPONSE_REQUEST = 0xBA,
        FRAME_ERROR = 0xFE,
        GENERIC = 0xFF
    };

    // overload HexString function to handle char*, std::string, or generic type

    static std::string HexString(char value[], bool is_spaced = true) {
        /* Function to convert a char array (c string) into a std::string of containing hex value octets
         * A hex octet is defined as a hex representation of 8 bits. Example FF, 00, 01, 9F, etc.
         * 
         * Inputs
         *      value           - char array to be converted
         *      is_spaced    - bool specifying if white space character should be placed between octets
         * 
         * Return
         *      a std::string type with hex octets representing the binary data within value. A whitespace character is added between each octet if the
         *      is_spaced bool is set true
         */

        // declare and initialize a std::string from the char array
        std::string std_str(value);
        uint16_t ndx;
        uint16_t len = std_str.length();
        char str_buf[len];
        std::stringstream stream; // declare a stringstream to store the hex octets

        // loop through length of char array/std::string
        for (ndx = 0; ndx < len; ndx++) {
            snprintf(str_buf, 3, "%02X", value[ndx]); //snprintf prevents buffer overflow
            stream << str_buf;
            if (ndx != (len - 1) && is_spaced) stream << " "; // add white space if is_spaced set true
        }
        return stream.str();
    }

    static std::string HexString(const char value[], bool is_spaced = true) {
        /* Function to convert a const char array (c string) into a std::string of containing hex value octets
         * A hex octet is defined as a hex representation of 8 bits. Example FF, 00, 01, 9F, etc.
         * 
         * Inputs
         *      value           - char array to be converted
         *      is_spaced    - bool specifying if white space character should be placed between octets
         * 
         * Return
         *      a std::string type with hex octets representing the binary data within value. A whitespace character is added between each octet if the
         *      is_spaced bool is set true
         * 
         * NOTE: This function is a function overload of HexString for a const char array. Const char arrays are returned by std::string.c_str() calls
         */

        // declare and initialize a std::string from the char array
        std::string std_str(value);
        uint16_t ndx;
        uint16_t len = std_str.length();
        char str_buf[len];
        std::stringstream stream; // declare a stringstream to store the hex octets

        // loop through length of char array/std::string
        for (ndx = 0; ndx < len; ndx++) {
            snprintf(str_buf, 3, "%02X", value[ndx]); //snprintf prevents buffer overflow
            stream << str_buf;
            if (ndx != (len - 1) && is_spaced) stream << " "; // add white space if is_spaced set true
        }
        return stream.str();
    }

    static std::string HexString(const std::string &value, bool is_spaced = true) {
        /* Function to convert each character of a std::string (C++ string) into a std::string of containing hex value octets. This function will only
         * convert the string data within the std::string and ignore any associated metadata or methods
         * A hex octet is defined as a hex representation of 8 bits. Example FF, 00, 01, 9F, etc.
         * 
         * Inputs
         *      value           - std::string to be converted
         *      is_spaced    - bool specifying if white space character should be placed between octets
         * 
         * Return
         *      a std::string type with hex octets representing the binary data within value. A whitespace character is added between each octet if the
         *      is_spaced bool is set true
         */
        uint16_t ndx;
        uint16_t len = value.length();
        char str_buf[len];
        std::stringstream stream; // declare a stringstream to store the hex octets

        // loop through length of std::string
        for (ndx = 0; ndx < len; ndx++) {
            snprintf(str_buf, 3, "%02X", value[ndx]); // snprintf prevents buffer overflow
            stream << str_buf;
            if (ndx != (len - 1) && is_spaced) stream << " "; // add white space if is_spaced set true
        }
        return stream.str();
    }

    // template function must be in header

    template <typename T> static std::string HexString(const T &value, bool is_spaced = true, bool little_endian = true) {
        /* Function to convert a generic data type to a std::string of containing hex value octets
         * A hex octet is defined as a hex representation of 8 bits. Example FF, 00, 01, 9F, etc.
         * 
         * Inputs
         *      value           - generic data type to be converted
         *      is_spaced    - bool specifying if white space character should be placed between octets
         *      little_endian - bool specifying value is represented in little_endian and a conversion to big_endian is necessary
         *                          NOTE: Human readable is big_endian, leave little_endian = true for human readable output
         * 
         * Return
         *      a std::string type with hex octets representing the binary data within value. A whitespace character is added between each octet if the
         *      is_spaced bool is set true. The order of the return will be reversed if little_endian is set false
         * 
         * NOTE: Current implementation WILL NOT WORK ON STRUCTS OR CLASSES
         */
        uint16_t ndx;
        uint16_t dataNdx;
        uint16_t len = sizeof (value);
        char str_buf[len];
        uint8_t *dat = (uint8_t*) & value; // declare a stringstream to store the hex octets
        std::stringstream stream; // declare a stringstream to store the hex octets

        // TODO: Handle classes and struct types
        // Using this function to handle classes and structs WILL NOT COMPILE
        static_assert(!std::is_class<T>::value, "Cannot convert class or struct to string of Hex octets");
        for (ndx = 0; ndx < len; ndx++) {
            dataNdx = little_endian ? (len - 1) - ndx : ndx; // set data access based on requested endianess
            snprintf(str_buf, 3, "%02X", (dat[dataNdx])); // snprintf to prevent buffer overflow
            stream << str_buf;
            if (ndx != (len - 1) && is_spaced) stream << " ";
        }
        return stream.str();
    };

    // overload ByteSum function to handle char*, const char*, std::string, or generic type

    static uint8_t ByteSum(char *item) {
        /* Function to calculate the sum of bytes in a char*. The sum is stored into a uint8_t and sums greater than 256 are allowed to overflow
         * 
         * Inputs
         *      item    - char array to be summed
         * 
         * Return
         *      a uint8_t value representing the sum of the bytes in item. Sums greater than 256 are allowed to overflow
         * 
         */
        std::string std_str(item);
        uint16_t ndx;
        uint16_t len = std_str.length();
        uint8_t sum(0);

        for (ndx = 0; ndx < len; ndx++) sum += std_str[ndx];

        return sum;
    }

    static uint8_t ByteSum(const char *item) {
        /* Function to calculate the sum of bytes in a const char*. The sum is stored into a uint8_t and sums greater than 256 are allowed to overflow
         * 
         * Inputs
         *      item    - const char array to be summed
         * 
         * Return
         *      a uint8_t value representing the sum of the bytes in item. Sums greater than 256 are allowed to overflow
         * 
         * NOTE: This function is a function overload of ByteSum to handle const char* types. It is not the same function as ByteSum(char *item)
         */

        std::string std_str(item);
        uint16_t ndx;
        uint16_t len = std_str.length();
        uint8_t sum(0);

        for (ndx = 0; ndx < len; ndx++) sum += std_str[ndx];

        return sum;
    }

    static uint8_t ByteSum(std::string &item) {
        /* Function to calculate the sum of bytes in a std::string. The sum is stored into a uint8_t and sums greater than 256 are allowed to overflow
         * This function will only sum the bytes in the string data and will disregard any metadata or methods associated with the std::string
         * 
         * Inputs
         *      item    - std::string array to be summed
         * 
         * Return
         *      a uint8_t value representing the sum of the bytes in item. Sums greater than 256 are allowed to overflow
         * 
         */

        uint16_t ndx;
        uint16_t len = item.length();
        uint8_t sum(0);

        for (ndx = 0; ndx < len; ndx++) sum += item[ndx];
        return sum;
    }

    template <typename T> static uint8_t ByteSum(T &item) {
        /* Function to calculate the sum of bytes in a generic type. The sum is stored into a uint8_t and sums > 256 are allowed to overflow
         * This function is intended for integral types (bool, char, short, int, long, etc.) 
         * 
         * Inputs
         *      item    - generic type to be summed
         * 
         * Return
         *      a uint8_t value representing the sum of the bytes in item. Sums greater than 256 are allowed to overflow
         * 
         * NOTE: This function will not work with classes or structs. A static_assert will prevent the code from compiling if this function is used on a 
         * class or struct
         */
        
        // TODO: Handle classes and struct types
        // Using this function to handle classes and structs WILL NOT COMPILE
        static_assert(!std::is_class<T>::value, "ByteSum cannot evaluate classes or structs");
        uint16_t ndx;
        uint16_t len = sizeof (item);
        uint8_t sum(0);
        uint8_t *dat = (uint8_t*) & item;

        for (ndx = 0; ndx < len; ndx++) sum += dat[ndx];

        return sum;
    }

}
#endif