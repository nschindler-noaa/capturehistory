/****************************************************************************
  file: OFile.h
****************************************************************************/

#ifndef OFile_H
#define OFile_H

#include <iostream>
#include <fstream>
#include <string>
#include <QString>

class OFile {
public:
    OFile(const QString& s);
    OFile(const OFile& ofile);
    ~OFile();

    OFile &operator=(const OFile& ofile)
    {return *(new OFile(ofile));}

    void open(char mode);
    void close();

    const QString& getName() { return name; }
    std::ofstream& getStream() { return ofs; }

    friend int operator<(const OFile& ofile_a, const OFile& ofile_b)
    { return ofile_a.name.compare(ofile_b.name) < 0; }
    friend int operator<=(const OFile& ofile_a, const OFile& ofile_b)
    { return ofile_a.name.compare(ofile_b.name) <= 0; }
    friend int operator==(const OFile& ofile_a, const OFile& ofile_b)
    { return ofile_a.name.compare(ofile_b.name) == 0; }
    friend int operator==(const OFile& ofile, const QString& s)
    { return ofile.name.compare(s) == 0; }

private:
    QString name;
    std::ofstream ofs;


};


#endif
