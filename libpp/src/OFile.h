/****************************************************************************
  file: OFile.h
****************************************************************************/

#ifndef OFile_H
#define OFile_H

#include <iostream>
#include <fstream>
#include <string>

class OFile {
public:
    OFile(const std::string& s);
    OFile(const OFile& ofile);
    ~OFile();

    void open(char mode);
    void close();
    
    const std::string& getName() { return name; }
    std::ofstream& getStream() { return ofs; }

    friend int operator<(const OFile& ofile_a, const OFile& ofile_b)
    { return ofile_a.name.compare(ofile_b.name) < 0; }
    friend int operator<=(const OFile& ofile_a, const OFile& ofile_b)
    { return ofile_a.name.compare(ofile_b.name) <= 0; }
    friend int operator==(const OFile& ofile_a, const OFile& ofile_b)
    { return ofile_a.name.compare(ofile_b.name) == 0; }
    friend int operator==(const OFile& ofile, const std::string& s)
    { return ofile.name.compare(s) == 0; }

private:
    std::string name;
    std::ofstream ofs;
};


#endif
