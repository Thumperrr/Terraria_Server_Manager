#include "BinaryReader.h"

namespace Utility
{
    BinaryReader::BinaryReader(string s)
    {
        this->fname = s;
        this->pos = 0;
        this->file = fopen(s.c_str(), "rb");
        //fseek(file, 0, SEEK_END);
        //this->fSize = ftell(file);
        //rewind(file);
    }

    bool BinaryReader::IsOpen()
    {
        return file != NULL;
    }

    void BinaryReader::Close()
    {
        fclose(this->file);
    }

    int BinaryReader::Read7BitEncodedInt(unsigned char b)
    {
        int ret = 0;
        int shift = 0;

        do {
            ret = ret | ((b & 0x7f) << shift);
            shift += 7;
        } while ((b & 0x80) == 0x80);
        return ret;
    }

    unsigned char BinaryReader::ReadByte()
    {
        fsetpos(this->file, &pos);
        unsigned char value;
        int size = sizeof(value);
        pos += size;
        char *buf = new char[size];

        fread(buf, 1, size, this->file);
        if(ferror(this->file))
            perror("Error reading file");
        value = buf[0];
        delete [] buf;
        return static_cast<unsigned char>(value);
    }

    bool BinaryReader::ReadBoolean()
    {
        return (ReadByte() != 0);
    }

    char BinaryReader::ReadChar()
    {
        fsetpos(this->file, &pos);
        char value;
        int size = sizeof(char);
        pos += size;
        char *buf = new char[size];

        fread(buf, 1, size, this->file);
        if(ferror(this->file))
            perror("Error reading file");

        value = buf[0];
        delete [] buf;
        return value;
    }

    int BinaryReader::ReadShort()
    {
        fsetpos(this->file, &pos);
        short value;
        int size = sizeof(value);
        pos += size;
        char *buf = new char[size];

        fread(buf, 1, size, this->file);
        if(ferror(this->file))
            perror("Error reading file");

        value = *(reinterpret_cast<short*>(buf));
        delete [] buf;
        return value;
    }

    int BinaryReader::ReadInt32()
    {
        fsetpos(this->file, &pos);
        int value, size = sizeof(value);
        pos += size;
        char *buf = new char[size];

        fread(buf, 1, size, this->file);
        if(ferror(this->file))
            perror("Error reading file");

        value = *(reinterpret_cast<int*>(buf));
        delete [] buf;
        return value;
    }

    float BinaryReader::ReadFloat()
    {
        fsetpos(this->file, &pos);
        float value;
        int size = sizeof(value);
        pos += size;
        char *buf = new char[size];

        fread(buf, 1, size, this->file);
        if(ferror(this->file))
            perror("Error reading file");

        value = *(reinterpret_cast<float*>(buf));
        delete [] buf;
        return value;
    }

    double BinaryReader::ReadDouble()
    {
        fsetpos(this->file, &pos);
        double value;
        int size = sizeof(value);
        pos += size;
        char *buf = new char[size];
        fread(buf, 1, size, file);
        if(ferror(this->file))
            perror("Error reading file");

        value = *(reinterpret_cast<double*>(buf));
        delete [] buf;
        return value;
    }

    string BinaryReader::ReadChars(int chars)
    {
        if(chars < 1) return "";

        fsetpos(this->file, &pos);
        pos += chars;
        char *buf = new char[chars];

        fread(buf, 1, chars, this->file);
        if(ferror(this->file))
            perror("Error reading file");

        string s = buf;
        delete [] buf;
        return s.substr(0, chars);
    }

    string BinaryReader::ReadString()
    {
        fsetpos(this->file, &pos);
        pos += 1;
        char buf[1];
        fread(buf, 1, 1, this->file);
        int len = this->Read7BitEncodedInt(buf[0]);
        return this->ReadChars(len);
    }
}
