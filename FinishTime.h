#ifndef FINISH_TIME_H
#define FINISH_TIME_H

#include "BigEndianBitReader.h"
#include <cstdint>
#include <string>
#include <sstream>

class FinishTime {
    uint16_t m_minutes; 				// 7 bits, offset 0x00
    uint16_t m_seconds; 				// 7 bits, offset 0x00.7
    uint16_t m_milliseconds; 			// 10 bits, offset 0x01.6

public:
    FinishTime() = default;
    explicit FinishTime(BigEndianBitReader& ghostReader, size_t byteOffset, size_t bitPos);

    uint16_t minutes() { return m_minutes; }
    uint16_t seconds() { return m_seconds; }
    uint16_t milliseconds() { return m_milliseconds; }

    std::string asString();
};

#endif // FINISH_TIME_H
