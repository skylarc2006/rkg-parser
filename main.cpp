#include "MiiData.h"
#include "FinishTime.h"
#include "RKGHeader.h"
#include "BigEndianFileIO.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>

#include <vector>
#include <string_view>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <rkg file>\n";
        return 1;
    }

    std::ifstream ghostFile{ argv[1], std::ios::binary };
    RKGHeader ghostHeader{ ghostFile };

    if (ghostHeader.rkgd() != "RKGD") {
        std::cerr << "It appears this is not a Mario Kart Wii ghost file!\n";
        return 1;
    }

    auto printField = [](const char* label, const std::string_view value) {
    std::cout << label << value << '\n';
    };

    std::cout << "HEADER INFO:\n";
    std::cout << "============\n";
    printField("Track:\t\t", ghostHeader.trackName());
    printField("Name:\t\t", "(not implemented)");
    printField("Country:\t", ghostHeader.countryString());
    printField("Date set:\t", ghostHeader.dateSet());
    printField("Combo:\t\t", ghostHeader.combo());
    printField("Controller:\t", ghostHeader.controllerString());
    std::cout << '\n';

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
