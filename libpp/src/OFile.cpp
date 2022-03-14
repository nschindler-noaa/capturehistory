/****************************************************************************
  file: OFile.cc
  ****************************************************************************/

#include <stdio.h>
#include "OFile.h"

using std::string;
using std::ofstream;
using std::ios;

OFile::OFile(const QString &filen) : name(filen)
{}

OFile::OFile(const OFile& ofile) : name(ofile.name)
{}

OFile::~OFile()
{
    close();
}

void OFile::open(char mode) {
    close();

    if (mode == 'a')
        ofs.open(name.toStdString().data(), ios::out | ios::app);
    else if (mode == 'w')
        ofs.open(name.toStdString().data(), ios::out);
}

void OFile::close() {
    if (ofs.is_open())
        ofs.close();
}

