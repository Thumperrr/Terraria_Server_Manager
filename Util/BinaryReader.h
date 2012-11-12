#ifndef BINARYREADER_H
#define BINARYREADER_H

#include <stdio.h>
#include <string>
using namespace std;

namespace Utility
{
    class BinaryReader
    {
        public:
            BinaryReader(string s);
            bool IsOpen();
            void Close();

            int Read7BitEncodedInt(unsigned char b);
            unsigned char ReadByte();
            bool ReadBoolean();
            char ReadChar();
            int ReadShort();
            int ReadInt32();
            float ReadFloat();
            double ReadDouble();

            string ReadChars(int chars);
            string ReadString();

            string fname;
            fpos_t pos;
            FILE *file;
            long fSize;
    };
}

#endif // BINARYREADER_H
