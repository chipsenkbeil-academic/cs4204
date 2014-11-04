#include <stdio.h>

#ifndef SERIALFILE_H
#define SERIALFILE_H

/**
 * Class representing a file that can be written to and read from.
 */
class SerialFile {
    private:
        FILE* pFile;

    public:
        SerialFile(const char*, const char*);
        ~SerialFile(void);

        void open(const char*, const char*);
        void close(void);
        void read(void*, size_t);
        void write(const void*, size_t);
        int eof(void);
        FILE* getPointer(void);
};

#endif

