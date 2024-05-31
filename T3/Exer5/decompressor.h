#pragma once

#include <fstream>
#include <iostream>
#include <string>
//#include <vector>

/* void ClearBuffer(char buffer[], const int buffer_size){
    for(int i = 0; i < buffer_size; ++i){
        buffer[i] = '\0';
    }
} */
// напишите эту функцию
inline bool DecodeRLE(const std::string& src_name, const std::string& dst_name){

    std::ifstream in(src_name, std::ios::in | std::ios::binary);
    if (!in) {
        return false;
    }

    std::ofstream out(dst_name, std::ios::out | std::ios::binary);
    if (!out) {
        return false;
    }

    do {
        auto header = in.get();
        if (header != std::istream::traits_type::eof()) {
            int block_type = (header & 1);
            int data_size = (header >> 1) + 1; 
            static const int max_block_size = 128;
            char block[max_block_size];

            if (block_type != 0) {
                auto data_block1 = in.get();
                if(data_block1 == std::istream::traits_type::eof()){
                    break;
                }
            
                std::string block1_str(data_size, data_block1);
                out.write(block1_str.data(), data_size);
               
            }
            else {
                in.read(block, data_size);
                if(in.eof()){
                    break;
                }
                
                out.write(block, in.gcount());
            }
        }
        else {
            break;
        }
    }
    while(!in.eof());

    return true;
}

