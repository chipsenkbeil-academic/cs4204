#include "serialfile.h"

SerialFile::SerialFile(const char* name, const char* mode) {
    pFile = NULL;
    open(name, mode);
}

SerialFile::~SerialFile(void) {
    close();
}

void SerialFile::open(const char* name, const char* mode) {
    close();
    pFile = fopen(name, mode);
}

void SerialFile::close(void) {
    if (pFile) fclose(pFile);
    pFile = NULL;
}

int SerialFile::eof(void) {
    return feof(pFile);
}

void SerialFile::write(const void* data, size_t size) {
    if (pFile) fwrite(data, size, 1, pFile);
}

void SerialFile::read(void* data, size_t size) {
    if (pFile) fread(data, size, 1, pFile);
}

FILE* SerialFile::getPointer(void) {
    return pFile;
}

