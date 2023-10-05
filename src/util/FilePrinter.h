#pragma once

#include <string>
#include <fstream>
#include <iostream>

#include <impl/CarRecord.h>
#include <util/Constants.h>
#include <util/Config.h>

namespace sbd::util::fileprinter {

    void print(const std::string& filename){
        if(!Config::instance().isDebugModeEnabled()) return;

        std::cout << "[TAPE] " << filename << std::endl;
        std::ifstream file(filename);
        std::vector<uint8_t> recordSerialized(constants::RECORD_SIZE);

        while(true){
            file.read(reinterpret_cast<char*>(recordSerialized.data()), constants::RECORD_SIZE);
            if(file.eof()) break;
            std::cout << impl::CarRecord::deserialize(recordSerialized, 0) << std::endl;
        }
        std::cout << std::endl;

        file.close();
    }

}