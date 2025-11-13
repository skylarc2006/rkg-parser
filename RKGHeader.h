#ifndef RKG_HEADER_H
#define RKG_HEADER_H

#include "BigEndianBitReader.h"
#include "FinishTime.h"
#include "MiiData.h"
#include <fstream>
#include <sstream>
#include <string>
#include <string_view>
#include <cstdint>
#include <array>

class RKGHeader {
    std::string m_rkgd; 				            // 0x04, offset 0x00
    FinishTime m_finishTime; 			            // 0x03, offset 0x04
    uint16_t m_trackID;				                // 6 bits, offset 0x07
    uint8_t m_unknown1;				                // 2 bits, offset 0x07.6, likely padding
    uint16_t m_vehicleID;				            // 6 bits, offset 0x08
    uint16_t m_characterID;			                // 6 bits, offset 0x08.6
    uint16_t m_yearSet;				                // 7 bits, offset 0x09.4
    uint16_t m_monthSet;				            // 4 bits, offset 0x0A.3
    uint16_t m_daySet;				                // 5 bits, offset 0x0A.7
    uint16_t m_controllerID;			            // 4 bits, offset 0x0B.4
    uint8_t m_unknown2;				                // 4 bits, offset 0x0C, always 0?
    bool m_isCompressed;				            // 1 bit, offset 0xC.4
    uint8_t m_unknown3;				                // 2 bits, offset 0x0C.5, always 0?
    uint16_t m_ghostType;				            // 7 bits, offset 0x0C.7
    bool m_isAutomaticDrift;			            // 1 bit, offset 0x0D.6
    bool m_unknown4;					            // 1 bit, offset 0x0D.7, likely padding
    uint16_t m_decompressedInputDataLength;		    // 0x02, offset 0x0E	
    uint16_t m_lapCount;				            // 0x01, offset 0x10
    std::vector<FinishTime> m_lapSplitTimes;	    // 0x0F, offset 0x11, first 5 laps. 0x14, offset 0x20, remaining laps. Game attempts to store laps greater than 5 here but fails
    uint16_t m_countryCode;				            // 0x01, offset 0x34
    uint16_t m_stateCode;				            // 0x01, offset 0x35
    uint16_t m_locationCode;				        // 0x02, offset 0x36
    uint32_t m_unknown6;				            // 0x04, offset 0x38, typically 0
    MiiData m_miiData;				                // 0x4A, offset 0x3C
    uint16_t m_miiCrc16;				            // 0x02, offset 0x86

    // Parses RKGD magic from ghost file
    void parseRkgd(BigEndianBitReader& ghostReader);

public:
    explicit RKGHeader(std::ifstream& file);

    std::string_view rkgd() { return m_rkgd; }
    FinishTime& finishTime() { return m_finishTime; }
};

#endif // RKG_HEADER_H
