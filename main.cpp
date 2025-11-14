#include "MiiData.h"
#include "FinishTime.h"
#include "RKGHeader.h"
#include "BigEndianBitReader.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>

#include <vector>
#include <string_view>

int main(int argc, char *argv[])
{
    std::ifstream ghostFile{ "140915.rkg", std::ios::binary };
    RKGHeader ghostHeader{ ghostFile };

    if (ghostHeader.rkgd() != "RKGD") {
        std::cerr << "It appears this is not a Mario Kart Wii ghost file!\n";
        return 1;
    }

    std::cout << "Track name: " << ghostHeader.trackName() << '\n';
    std::cout << "Date set: " << ghostHeader.dateSet() << '\n';
    std::cout << "Controller: " << ghostHeader.controllerString() << '\n';
    std::cout << "Combo: " << ghostHeader.character() << " on " << ghostHeader.vehicle() << "\n\n";

    for (size_t i{ 0 }; i < ghostHeader.lapCount(); i++) {
        std::cout << "Lap " << i + 1 << ": \t\t"
                  << ghostHeader.lapSplitTimes()[i].asString() << '\n';
    }
    std::cout << "\nTime: \t\t" << ghostHeader.finishTime().asString() << '\n';
}

/*
"-pedantic-errors",
"-Wall",
"-Weffc++",
"-Wextra",
"-Wconversion",
"-Wsign-conversion",
"-Werror",
*/
