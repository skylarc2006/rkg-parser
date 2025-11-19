#include "RKGHeader.h"
#include "BigEndianFileIO.h"
#include "FinishTime.h"
#include "MiiData.h"
#include <fstream>
#include <sstream>
#include <string>
#include <string_view>
#include <cstdint>
#include <array>
#include <unordered_map>
#include <iostream>

using namespace std::literals::string_view_literals;

RKGHeader::RKGHeader(std::ifstream& file) {
    BigEndianFileIO ghostReader{ file };
    
    parseRkgd(ghostReader);
    m_finishTime = FinishTime(ghostReader, 0x04, 0);
    m_trackID = ghostReader.readBits(0x07 * 8, 6);
    m_vehicleID = ghostReader.readBits(0x08 * 8, 6);
    m_characterID = ghostReader.readBits(0x08 * 8 + 6, 6);
    m_yearSet = ghostReader.readBits(0x09 * 8 + 4, 7);
    m_monthSet = ghostReader.readBits(0x0A * 8 + 3, 4);
    m_daySet = ghostReader.readBits(0x0A * 8 + 7, 5);
    m_controllerID = ghostReader.readBits(0x0B * 8 + 4, 4);
    m_compressed = ghostReader.readBits(0x0C * 8 + 4, 1);
    m_ghostType = ghostReader.readBits(0x0C * 8 + 7, 7);
    m_automaticDrift = ghostReader.readBits(0x0D * 8 + 6, 1);
    m_decompressedInputDataLength = ghostReader.readUInt16(0x0E * 8);
    m_lapCount = ghostReader.readUInt8(0x10 * 8);
    
    constexpr size_t lapSplitBaseByteOffset = 0x11;
    for (size_t i{ 0 }; i < m_lapCount; i++) {
        m_lapSplitTimes.emplace_back(FinishTime(ghostReader, lapSplitBaseByteOffset + (i * 0x03), 0));
    }

    m_countryCode = ghostReader.readUInt8(0x34 * 8);
    m_stateCode = ghostReader.readUInt8(0x35 * 8);
    m_locationCode = ghostReader.readUInt16(0x36 * 8);

    m_miiCrc16 = ghostReader.readUInt16(0x86 * 8);

    // TESTING
    std::cout << "CURRENT TESTING INFO\n";
    std::cout << "====================\n";
    std::cout << "Country code: " << m_countryCode << '\n';
    std::cout << "State code: " << m_stateCode << '\n';
    std::cout << "Location code: " << m_locationCode << "\n\n";
}

void RKGHeader::parseRkgd(BigEndianFileIO& ghostReader) {
    auto rkgdBytes = ghostReader.readBytes(0x00, 0x04);

    for (auto rkgdByte : rkgdBytes) {
        m_rkgd += static_cast<char>(rkgdByte);
    }
}

std::string_view RKGHeader::trackName() {
    static constexpr std::array<std::pair<size_t, std::string_view>, 49> tracks = {{
        {0x00, "Mario Circuit"sv},
        {0x01, "Moo Moo Meadows"sv},
        {0x02, "Mushroom Gorge"sv},
        {0x03, "Grumble Volcano"sv},
        {0x04, "Toad's Factory"sv},
        {0x05, "Coconut Mall"sv},
        {0x06, "DK Summit"sv},
        {0x07, "Wario's Gold Mine"sv},
        {0x08, "Luigi Circuit"sv},
        {0x09, "Daisy Circuit"sv},
        {0x0A, "Moonview Highway"sv},
        {0x0B, "Maple Treeway"sv},
        {0x0C, "Bowser's Castle"sv},
        {0x0D, "Rainbow Road"sv},
        {0x0E, "Dry Dry Ruins"sv},
        {0x0F, "Koopa Cape"sv},
        {0x10, "GCN Peach Beach"sv},
        {0x11, "GCN Mario Circuit"sv},
        {0x12, "GCN Waluigi Stadium"sv},
        {0x13, "GCN DK Mountain"sv},
        {0x14, "DS Yoshi Falls"sv},
        {0x15, "DS Desert Hills"sv},
        {0x16, "DS Peach Gardens"sv},
        {0x17, "DS Delfino Square"sv},
        {0x18, "SNES Mario Circuit 3"sv},
        {0x19, "SNES Ghost Valley 2"sv},
        {0x1A, "N64 Mario Raceway"sv},
        {0x1B, "N64 Sherbet Land"sv},
        {0x1C, "N64 Bowser's Castle"sv},
        {0x1D, "N64 DK's Jungle Parkway"sv},
        {0x1E, "GBA Bowser Castle 3"sv},
        {0x1F, "GBA Shy Guy Beach"sv},
        {0x20, "Delfino Pier"sv},
        {0x21, "Block Plaza"sv},
        {0x22, "Chain Chomp Wheel"sv},
        {0x23, "Funky Stadium"sv},
        {0x24, "Thwomp Desert"sv},
        {0x25, "GCN Cookie Land"sv},
        {0x26, "DS Twilight House"sv},
        {0x27, "SNES Battle Course 4"sv},
        {0x28, "GBA Battle Course 3"sv},
        {0x29, "N64 Skyscraper"sv},
        {0x36, "Galaxy Colosseum"sv},
        {0x37, "Winning Scene"sv},
        {0x38, "Loser Scene"sv},
        {0x39, "Draw Demo"sv},
        {0x3A, "Luigi Circuit (credits)"sv},
        {0x43, "Unselected Track"sv},
        {0xFF, "Random"}
    }};



    for (auto& track : tracks) {
        if (m_trackID == track.first) {
            return track.second;
        }
    }
        
    return "Unknown Track";
}

std::string_view RKGHeader::character() {
    
    static constexpr std::array<std::pair<size_t, std::string_view>, 48> characters = {{
    {0x00, "Mario"sv},
    {0x01, "Baby Peach"sv},
    {0x02, "Waluigi"sv},
    {0x03, "Bowser"sv},
    {0x04, "Baby Daisy"sv},
    {0x05, "Dry Bones"sv},
    {0x06, "Baby Mario"sv},
    {0x07, "Luigi"sv},
    {0x08, "Toad"sv},
    {0x09, "Donkey Kong"sv},
    {0x0A, "Yoshi"sv},
    {0x0B, "Wario"sv},
    {0x0C, "Baby Luigi"sv},
    {0x0D, "Toadette"sv},
    {0x0E, "Koopa Troopa"sv},
    {0x0F, "Daisy"sv},
    {0x10, "Peach"sv},
    {0x11, "Birdo"sv},
    {0x12, "Diddy Kong"sv},
    {0x13, "King Boo"sv},
    {0x14, "Bowser Jr."sv},
    {0x15, "Dry Bowser"sv},
    {0x16, "Funky Kong"sv},
    {0x17, "Rosalina"sv},

    {0x18, "Small Mii Outfit A (Male)"sv},
    {0x19, "Small Mii Outfit A (Female)"sv},
    {0x1A, "Small Mii Outfit B (Male)"sv},
    {0x1B, "Small Mii Outfit B (Female)"sv},
    {0x1C, "Small Mii Outfit C (Male)"sv},
    {0x1D, "Small Mii Outfit C (Female)"sv},

    {0x1E, "Medium Mii Outfit A (Male)"sv},
    {0x1F, "Medium Mii Outfit A (Female)"sv},
    {0x20, "Medium Mii Outfit B (Male)"sv},
    {0x21, "Medium Mii Outfit B (Female)"sv},
    {0x22, "Medium Mii Outfit C (Male)"sv},
    {0x23, "Medium Mii Outfit C (Female)"sv},

    {0x24, "Large Mii Outfit A (Male)"sv},
    {0x25, "Large Mii Outfit A (Female)"sv},
    {0x26, "Large Mii Outfit B (Male)"sv},
    {0x27, "Large Mii Outfit B (Female)"sv},
    {0x28, "Large Mii Outfit C (Male)"sv},
    {0x29, "Large Mii Outfit C (Female)"sv},

    {0x2A, "Medium Mii"sv},
    {0x2B, "Small Mii"sv},
    {0x2C, "Large Mii"sv},

    {0x2D, "Peach (Character/Vehicle Selection)"sv},
    {0x2E, "Daisy (Character/Vehicle Selection)"sv},
    {0x2F, "Rosalina (Character/Vehicle Selection)"sv}
}};

    for (auto& character : characters) {
        if (m_characterID == character.first) {
            return character.second;
        }
    }
        
    return "Unknown Character";
}

std::string_view RKGHeader::vehicle() {
    static constexpr std::array<std::pair<size_t, std::string_view>, 36> vehicles = {{
    {0x00, "Standard Kart S"sv},
    {0x01, "Standard Kart M"sv},
    {0x02, "Standard Kart L"sv},
    {0x03, "Booster Seat"sv},
    {0x04, "Classic Dragster"sv},
    {0x05, "Offroader"sv},
    {0x06, "Mini Beast"sv},
    {0x07, "Wild Wing"sv},
    {0x08, "Flame Flyer"sv},
    {0x09, "Cheep Charger"sv},
    {0x0A, "Super Blooper"sv},
    {0x0B, "Piranha Prowler"sv},
    {0x0C, "Tiny Titan"sv},
    {0x0D, "Daytripper"sv},
    {0x0E, "Jetsetter"sv},
    {0x0F, "Blue Falcon"sv},
    {0x10, "Sprinter"sv},
    {0x11, "Honeycoupe"sv},
    {0x12, "Standard Bike S"sv},
    {0x13, "Standard Bike M"sv},
    {0x14, "Standard Bike L"sv},
    {0x15, "Bullet Bike"sv},
    {0x16, "Mach Bike"sv},
    {0x17, "Flame Runner"sv},
    {0x18, "Bit Bike"sv},
    {0x19, "Sugarscoot"sv},
    {0x1A, "Wario Bike"sv},
    {0x1B, "Quacker"sv},
    {0x1C, "Zip Zip"sv},
    {0x1D, "Shooting Star"sv},
    {0x1E, "Magikruiser"sv},
    {0x1F, "Sneakster"sv},
    {0x20, "Spear"sv},
    {0x21, "Jet Bubble"sv},
    {0x22, "Dolphin Dasher"sv},
    {0x23, "Phantom"sv}
}};

    for (auto& vehicle : vehicles) {
        if (m_vehicleID == vehicle.first) {
            return vehicle.second;
        }
    }
        
    return "Unknown Vehicle";
}

std::string_view RKGHeader::monthAsString() {
    static constexpr std::array<std::string_view, 12> months {
        "January"sv,
        "February"sv,
        "March"sv,
        "April"sv,
        "May"sv,
        "June"sv,
        "July"sv,
        "September"sv,
        "October"sv,
        "November"sv,
        "December"sv
    };

    return months[m_monthSet - 1];
}

std::string RKGHeader::dateSet() {
    std::stringstream ss;

    ss << monthAsString() << ' ' << m_daySet << ", 20" << m_yearSet;

    return ss.str();
}

std::string_view RKGHeader::controllerString() {
    static constexpr std::array<std::string_view, 4> controllers {
        "Wii Wheel",
        "Nunchuk",
        "Classic",
        "Gamecube"
    };
    return controllers[m_controllerID];
}

std::string_view RKGHeader::ghostTypeString() {
    if (m_ghostType == 0x01) return "Player's Best Time";
    else if (m_ghostType == 0x02) return "World Record Ghost";
    else if (m_ghostType == 0x03) return "Continental Record Ghost";
    else if (m_ghostType == 0x04) return "Rival Ghost";
    else if (m_ghostType == 0x05) return "Special Ghost";
    else if (m_ghostType == 0x06) return "Ghost Race";
    else if (m_ghostType <= 0x24) return "Friend Ghost";
    else if (m_ghostType == 0x25) return "Normal Staff Ghost";
    else if (m_ghostType == 0x26) return "Expert Staff Ghost";
   else return "Unknown";
}

std::string_view RKGHeader::countryString() {
    static constexpr std::array<std::pair<size_t, std::string_view>, 124> countries = {{
        {0x01, "Japan"sv},
        {0x08, "Anguilla"sv},
        {0x09, "Antigua and Barbuda"sv},
        {0x0A, "Argentina"sv},
        {0x0B, "Aruba"sv},
        {0x0C, "Bahamas"sv},
        {0x0D, "Barbados"sv},
        {0x0E, "Belize"sv},
        {0x0F, "Bolivia"sv},
        {0x10, "Brazil"sv},
        {0x11, "British Virgin Islands"sv},
        {0x12, "Canada"sv},
        {0x13, "Cayman Islands"sv},
        {0x14, "Chile"sv},
        {0x15, "Colombia"sv},
        {0x16, "Costa Rica"sv},
        {0x17, "Dominica"sv},
        {0x18, "Dominican Republic"sv},
        {0x19, "Ecuador"sv},
        {0x1A, "El Salvador"sv},
        {0x1B, "French Guiana"sv},
        {0x1C, "Grenada"sv},
        {0x1D, "Guadeloupe"sv},
        {0x1E, "Guatemala"sv},
        {0x1F, "Guyana"sv},
        {0x20, "Haiti"sv},
        {0x21, "Honduras"sv},
        {0x22, "Jamaica"sv},
        {0x23, "Martinique"sv},
        {0x24, "Mexico"sv},
        {0x25, "Montserrat"sv},
        {0x26, "Netherlands Antilles"sv},
        {0x27, "Nicaragua"sv},
        {0x28, "Panama"sv},
        {0x29, "Paraguay"sv},
        {0x2A, "Peru"sv},
        {0x2B, "St. Kitts and Nevis"sv},
        {0x2C, "St. Lucia"sv},
        {0x2D, "St. Vincent and the Grenadines"sv},
        {0x2E, "Suriname"sv},
        {0x2F, "Trinidad and Tobago"sv},
        {0x30, "Turks and Caicos Islands"sv},
        {0x31, "United States"sv},
        {0x32, "Uruguay"sv},
        {0x33, "US Virgin Islands"sv},
        {0x34, "Venezuela"sv},

        {0x40, "Albania"sv},
        {0x41, "Australia"sv},
        {0x42, "Austria"sv},
        {0x43, "Belgium"sv},
        {0x44, "Bosnia and Herzegovina"sv},
        {0x45, "Botswana"sv},
        {0x46, "Bulgaria"sv},
        {0x47, "Croatia"sv},
        {0x48, "Cyprus"sv},
        {0x49, "Czech Republic"sv},
        {0x4A, "Denmark"sv},
        {0x4B, "Estonia"sv},
        {0x4C, "Finland"sv},
        {0x4D, "France"sv},
        {0x4E, "Germany"sv},
        {0x4F, "Greece"sv},
        {0x50, "Hungary"sv},
        {0x51, "Iceland"sv},
        {0x52, "Ireland"sv},
        {0x53, "Italy"sv},
        {0x54, "Latvia"sv},
        {0x55, "Lesotho"sv},
        {0x56, "Liechtenstein"sv},
        {0x57, "Lithuania"sv},
        {0x58, "Luxembourg"sv},
        {0x59, "F.Y.R. of Macedonia"sv},
        {0x5A, "Malta"sv},
        {0x5B, "Montenegro"sv},
        {0x5C, "Mozambique"sv},
        {0x5D, "Namibia"sv},
        {0x5E, "Netherlands"sv},
        {0x5F, "New Zealand"sv},
        {0x60, "Norway"sv},
        {0x61, "Poland"sv},
        {0x62, "Portugal"sv},
        {0x63, "Romania"sv},
        {0x64, "Russia"sv},
        {0x65, "Serbia"sv},
        {0x66, "Slovakia"sv},
        {0x67, "Slovenia"sv},
        {0x68, "South Africa"sv},
        {0x69, "Spain"sv},
        {0x6A, "Swaziland"sv},
        {0x6B, "Sweden"sv},
        {0x6C, "Switzerland"sv},
        {0x6D, "Turkey"sv},
        {0x6E, "United Kingdom"sv},
        {0x6F, "Zambia"sv},
        {0x70, "Zimbabwe"sv},
        {0x71, "Azerbaijan"sv},
        {0x72, "Mauritania"sv},
        {0x73, "Mali"sv},
        {0x74, "Niger"sv},
        {0x75, "Chad"sv},
        {0x76, "Sudan"sv},
        {0x77, "Eritrea"sv},
        {0x78, "Djibouti"sv},
        {0x79, "Somalia"sv},

        {0x80, "Taiwan"sv},

        {0x88, "South Korea"sv},

        {0x90, "Hong Kong"sv},
        {0x91, "Macao"sv},

        {0x98, "Indonesia"sv},
        {0x99, "Singapore"sv},
        {0x9A, "Thailand"sv},
        {0x9B, "Philippines"sv},
        {0x9C, "Malaysia"sv},

        {0xA0, "China"sv},

        {0xA8, "U.A.E."sv},
        {0xA9, "India"sv},
        {0xAA, "Egypt"sv},
        {0xAB, "Oman"sv},
        {0xAC, "Qatar"sv},
        {0xAD, "Kuwait"sv},
        {0xAE, "Saudi Arabia"sv},
        {0xAF, "Syria"sv},
        {0xB0, "Bahrain"sv},
        {0xB1, "Jordan"sv},
    }};


    for (auto& country : countries) {
        if (m_countryCode == country.first) {
            return country.second;
        }
    }
        
    return "Unknown";
}

std::string_view RKGHeader::stateString() {
    return " ";
}

std::string_view RKGHeader::locationString() {
    return " ";
}

std::string RKGHeader::combo() {
    std::stringstream ss{};
    ss << character() << " on " << vehicle() << " (" << driftString() << ")";
    return ss.str();
}
