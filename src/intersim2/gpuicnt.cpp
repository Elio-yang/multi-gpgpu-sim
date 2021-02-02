//
// Created by Ben on 1/30/21.
//

#include "gpuicnt.h"
#include <ctime>
#include <cstring>

std::fstream file;

InterGPU::InterGPU() {
    file.open("remote.txt", std::ios::app);
    file << "\tinput\t" << "output\t" << "size\t" << "Packet_Type\t" <<"chip_ID\t\t" << "sub_part_ID\t" << "read/write\t" << "cycle(s)\t" << "time\n";
    file.close();
}

void InterGPU::apply(const char *func, unsigned input_deviceID, unsigned output_deviceID, unsigned int size, int ptype, int chip_id, unsigned int sub_partition_id, const char* is_write) {
    char type[15];
    switch (ptype) {
        case 0:
            strcpy(type, "READ_REQUEST");
            break;
        case 1:
            strcpy(type, "WRITE_REQUEST");
            break;
        case 2:
            strcpy(type, "READ_REPLY");
            break;
        case 3:
            strcpy(type, "WRITE_ACK");
            break;
    }
    file.open("remote.txt", std::ios::app);
    time_t ttime = time(0);
    tm *current = localtime(&ttime);
    if(file.is_open()){
        file << func << "\t" << input_deviceID << "\t" << output_deviceID << "\t" << size << "\t" << type << "\t" << chip_id << "\t\t" << sub_partition_id << "\t\t" << is_write << "\t\t" << this->end - this->start << "\t\t" << current->tm_min << ":" << current->tm_sec << std::endl;
    }
    file.close();
}

void InterGPU::setStart(int start) {
    std::cout << "Start: " << start << std::endl;
    this->start = start;
}

void InterGPU::setEnd(int end) {
    std::cout << "End: " << start << std::endl;
    this->end = end;
}