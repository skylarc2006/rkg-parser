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
    std::cout << "Finish time: " << ghostHeader.finishTime().asString() << '\n';
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
