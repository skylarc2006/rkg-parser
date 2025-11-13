#ifndef MII_DATA_H
#define MII_DATA_H

#include <string>
#include <cstdint>

class MiiData {
    // https://wiibrew.org/wiki/Mii_data#Mii_format
    // Strings are stored in Unicode format (UTF-16)
    
    bool m_unknown1{}; 					// 1 bit, offset 0x00
    bool m_isGirl{};					// 1 bit, offset 0x00.1
    uint16_t m_month{};					// 4 bits, offset 0x00.2
    uint16_t m_day{};					// 5 bits, offset 0x00.6
    uint16_t m_favColor{};				// 4 bits, offset 0x01.3
    bool m_isFavorite{};				// 1 bit, offset 0x01.7
    std::string m_name{}; 				// 0x14 (10 chars), offset 0x02
    uint16_t m_height{};				// 0x01, offset 0x16
    uint16_t m_weight{};				// 0x01, offset 0x17
    uint16_t m_miiID1{};				// 0x01, offset 0x18
    uint16_t m_miiID2{};				// 0x01, offset 0x19
    uint16_t m_miiID3{};				// 0x01, offset 0x1A
    uint16_t m_miiID4{};				// 0x01, offset 0x1B
    uint16_t m_systemID0{};				// 0x01, offset 0x1C
    uint16_t m_systemID1{};				// 0x01, offset 0x1D
    uint16_t m_systemID2{};				// 0x01, offset 0x1E
    uint16_t m_systemID3{};				// 0x01, offset 0x1F
    uint16_t m_faceShape{};				// 3 bits, offset 0x20
    uint16_t m_skinColor{};				// 3 bits, offset 0x20.3
    uint16_t m_facialFeature{};				// 4 bits, offset 0x20.6
    uint16_t m_unknown2{};				// 3 bits, offset 0x21.2
    bool m_mingleOff{};					// 1 bit, offset 0x21.5
    bool m_unknown3{};					// 1 bit, offset 0x21.6
    bool m_downloaded{};				// 1 bit, offset 0x21.7
    uint16_t m_hairType{};				// 7 bits, offset 0x22
    uint16_t m_hairColor{};				// 3 bits, offset 0x22.7
    bool m_hairPartReversed{};				// 1 bit, offset 0x23.2
    uint16_t m_unknown4{};				// 5 bits, offset 0x23.3
    uint16_t m_eyebrowType{};				// 5 bits, offset 0x24
    bool m_unknown5{};					// 1 bit, offset 0x24.5
    uint16_t eyebrowRotation{};				// 4 bits, offset 0x24.6
    uint8_t m_unknown6{};				// 6 bits, offset 0x25.2
    uint16_t m_eyebrowColor{};				// 3 bits, offset 0x26
    uint16_t m_eyebrowSize{};				// 4 bits, offset 0x26.3
    uint16_t m_eyebrowVerticalPos{};			// 5 bits, offset 0x26.7
    uint16_t m_eyebrowHorizontalSpacing{};		// 4 bits, offset 0x27.4
    uint16_t m_eyeType{};				// 6 bits, offset 0x28
    uint8_t m_unknown7{};				// 2 bits, offset 0x28.6
    uint16_t m_eyeRotation{};				// 3 bits, offset 0x29
    uint16_t m_eyeVerticalPos{};			// 5 bits, offset 0x29.3
    uint16_t m_eyeColor{};				// 3 bits, offset 0x2A
    bool m_unknown8{};					// 1 bit, offset 0x2A.3
    uint16_t m_eyeSize{};				// 3 bits, offset 0x2A.4
    uint16_t m_eyeHorizontalSpacing{};			// 4 bits, offset 0x2A.7
    uint8_t m_unknown9{};				// 5 bits, offset 0x2B.3
    uint16_t m_noseType{};				// 4 bits, offset 0x2C
    uint16_t m_noseSize{};				// 4 bits, offset 0x2C.4
    uint16_t m_noseVerticalPos{};			// 5 bits, offset 0x2D
    uint16_t m_unknown10{};				// 3 bits, offset 0x2D.5
    uint16_t m_lipType{};				// 5 bits, offset 0x2E
    uint16_t m_lipColor{};				// 2 bits, offset 0x2E.5
    uint16_t m_lipSize{};				// 4 bits, offset 0x2E.7
    uint16_t m_lipVerticalPos{};			// 5 bits, offset 0x2F.3
    uint16_t m_glassesType{};				// 4 bits, offset 0x30
    uint16_t m_glassesColor{};				// 3 bits, offset 0x30.4
    bool m_unknown11{};					// 1 bit, offset 0x30.7
    uint16_t m_glassesSize{};				// 3 bits, offset 0x31
    uint16_t m_glassesVerticalPos{};			// 5 bits, offset 0x31.3
    uint16_t m_mustacheType{};				// 2 bits, offset 0x32
    uint16_t m_beardType{};				// 2 bits, offset 0x32.2
    uint16_t m_facialHairColor{};			// 3 bits, offset 0x32.4
    uint16_t m_mustacheSize{};				// 4 bits, offset 0x32.7
    uint16_t m_mustacheVerticalPos{};			// 5 bits, offset 0x33.3
    bool m_hasMole{};					// 1 bit, offset 0x34
    uint16_t m_moleSize{};				// 4 bits, offset 0x34.1
    uint16_t m_moleVerticalPos{};			// 5 bits, offset 0x34.5
    uint16_t m_moleHorizontalPos{};			// 5 bits, offset 0x35.2
    bool m_unknown12{};					// 1 bit, offset 0x35.7
    std::string m_creatorName{};			// 0x14 (10 chars), offset 0x36
};

#endif // MII_DATA_H
