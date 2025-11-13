#include "RKGHeader.h"
#include "BigEndianBitReader.h"
#include "FinishTime.h"
#include "MiiData.h"
#include <fstream>
#include <sstream>
#include <string>
#include <string_view>
#include <cstdint>
#include <array>
#include <unordered_map>

RKGHeader::RKGHeader(std::ifstream& file) {
    BigEndianBitReader ghostReader{ file };
    
    parseRkgd(ghostReader);
    m_finishTime = FinishTime(ghostReader, 0x04, 0);
    m_trackID = ghostReader.readBits(0x07 * 8, 6);
}

void RKGHeader::parseRkgd(BigEndianBitReader& ghostReader) {
    auto rkgdBytes = ghostReader.readBytes(0x00, 0x04);

    for (auto rkgdByte : rkgdBytes) {
        m_rkgd += static_cast<char>(rkgdByte);
    }
}

std::string_view RKGHeader::trackName() {
    static constexpr std::array<std::string_view, 0x20> names = {
        /* 0x00 */ "Mario Circuit",
        /* 0x01 */ "Moo Moo Meadows",
        /* 0x02 */ "Mushroom Gorge",
        /* 0x03 */ "Grumble Volcano",
        /* 0x04 */ "Toad's Factory",
        /* 0x05 */ "Coconut Mall",
        /* 0x06 */ "DK Summit",
        /* 0x07 */ "Wario's Gold Mine",
        /* 0x08 */ "Luigi Circuit",
        /* 0x09 */ "Daisy Circuit",
        /* 0x0A */ "Moonview Highway",
        /* 0x0B */ "Maple Treeway",
        /* 0x0C */ "Bowser's Castle",
        /* 0x0D */ "Rainbow Road",
        /* 0x0E */ "Dry Dry Ruins",
        /* 0x0F */ "Koopa Cape",
        /* 0x10 */ "GCN Peach Beach",
        /* 0x11 */ "GCN Mario Circuit",
        /* 0x12 */ "GCN Waluigi Stadium",
        /* 0x13 */ "GCN DK Mountain",
        /* 0x14 */ "DS Yoshi Falls",
        /* 0x15 */ "DS Desert Hills",
        /* 0x16 */ "DS Peach Gardens",
        /* 0x17 */ "DS Delfino Square",
        /* 0x18 */ "SNES Mario Circuit 3",
        /* 0x19 */ "SNES Ghost Valley 2",
        /* 0x1A */ "N64 Mario Raceway",
        /* 0x1B */ "N64 Sherbet Land",
        /* 0x1C */ "N64 Bowser's Castle",
        /* 0x1D */ "N64 DK's Jungle Parkway",
        /* 0x1E */ "GBA Bowser Castle 3",
        /* 0x1F */ "GBA Shy Guy Beach"
    };

    if (m_trackID < names.size())
        return names[m_trackID];
    return "Unknown Track";
}
