#include "FinishTime.h"
#include "BigEndianBitReader.h"
#include <cstdint>
#include <string>
#include <sstream>
#include <iomanip>

FinishTime::FinishTime(BigEndianBitReader& ghostReader, size_t byteOffset, size_t bitPos) {
        size_t bitOffset{ byteOffset * 8 + bitPos };
        m_minutes = ghostReader.readBits(bitOffset, 7);
        m_seconds = ghostReader.readBits(bitOffset + 7, 7);
        m_milliseconds = ghostReader.readBits(bitOffset + 14, 10);
}

std::string FinishTime::asString() {
    std::stringstream ss;

    ss << std::setfill('0')               // pad with zeros
       << std::setw(2) << m_minutes       // 2 digits for minutes
       << ":" 
       << std::setw(2) << m_seconds       // 2 digits for seconds
       << "."
       << std::setw(3) << m_milliseconds; // 3 digits for milliseconds

    return ss.str();
}
