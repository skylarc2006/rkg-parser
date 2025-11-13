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

RKGHeader::RKGHeader(std::ifstream& file) {
    BigEndianBitReader ghostReader{ file };
    
    parseRkgd(ghostReader);
    m_finishTime = FinishTime(ghostReader, 0x04, 0);
}

void RKGHeader::parseRkgd(BigEndianBitReader& ghostReader) {
    auto rkgdBytes = ghostReader.readBytes(0x00, 0x04);

    for (auto rkgdByte : rkgdBytes) {
        m_rkgd += static_cast<char>(rkgdByte);
    }
}
