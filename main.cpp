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

    std::cout << "RKGD: " << ghostHeader.rkgd() << '\n';
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
