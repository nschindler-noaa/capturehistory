/*
 *
 */

#include <string>
#include <iostream>
#include <fstream>

#include <ArrayDefs.h>
#include <StringTok.h>
#include <StringManip.h>

#include "PPRunConfig.h"
#include "PitProSettings.h"
#include "PPBatchOutputMaker.h"

using std::string;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;

using cbr::StringVector;
using cbr::strip;
using cbr::toString;

void PPRunConfig::read(const string& fileName) 
{
    PPBatchOutputMaker& out = PPBatchOutputMaker::getInstance();

    if (fileName.empty()) 
    {
        out.write("Null run configuration!", PPBatchOutputMaker::Error);
        return;
    }

    ifstream in(fileName.c_str());
    if (!in.is_open())
        out.write("Can't open run configuration file \"" + fileName + "\".", PPBatchOutputMaker::Error);
    else 
    {
        string line;
        while (getline(in, line)) {
            // remove comments
            size_t pos = line.find('#');
            if (pos != string::npos)
                line.erase(pos);
            pos = line.find(':');
            if (pos != string::npos) {
                string groupkey = strip(line.substr(0, pos));
                if (pos < line.size() - 1) {
                    string value = cbr::strip(line.substr(pos + 1));
                    QStringList toks; //StringVector toks;
                    stringTok(toks, QString(groupkey.data()), "_");
                    if (toks.size() == 2) {
                        string group = toks[0].toStdString();
                        string key = toks[1].toStdString();
                        processParamDef(group, key, value);
                    }
                }
            }
        }
    }
}

/*
 * toks should contains (with examples): 
 *   groupkey: dir_dat
 *   value:    data
 *   group:    dir
 *   key:      dat
 */
void PPRunConfig::processParamDef(const string group, const string key, const string val) 
{
    PitProSettings& settings = PitProSettings::getInstance();


    if (!group.compare("fields")) 
    {
        QStringList sites;//StringVector sites;
        stringTok(sites, QString(val.data()), ", \t");
//        StringVector::const_iterator it;
        for (int i = 0; i < sites.count(); i++)
//        for (it = sites.begin(); it != sites.end(); it++)
        {
            settings.addParamDef(PitProSettings::HistField, sites.at(i).toStdString());
//            settings.addParamDef(PitProSettings::HistField, *it);
        }
        if (!key.compare("main"))
            settings.setValue(PitProSettings::NumMainSites, toString<int> (sites.size()));
    } else if (!group.compare("sites"))
    {
        if (!key.compare("main"))
            settings.setValue(PitProSettings::NumMainSites, val);
        else {
            QStringList sites; //StringVector sites;
            stringTok(sites, QString(val.data()), ", \t");
//            StringVector::const_iterator it;
            for (int i = 0; i < sites.count(); i++)
//            for (it = sites.begin(); it != sites.end(); it++)
            {
                if (!key.compare("juvenile"))
                    settings.addParamDef(PitProSettings::HistField, sites.at(i).toStdString());
//                    settings.addParamDef(PitProSettings::HistField, *it);
                else if (!key.compare("adult"))
                    settings.addParamDef(PitProSettings::AdultField, sites.at(i).toStdString());
//                    settings.addParamDef(PitProSettings::AdultField, *it);
            }
        }
    } 
    else if (!group.compare("out")) 
    {
        bool isOn = val.compare("1") == 0;

        if (!key.compare("surph"))
            settings.setChecked(PitProSettings::SurphFileSwitch, isOn);
        else if (!key.compare("error"))
            settings.setChecked(PitProSettings::ErrorsFileSwitch, isOn);
        else if (!key.compare("seq"))
            settings.setChecked(PitProSettings::SequenceFileSwitch, isOn);
        else if (!key.compare("dd"))
            settings.setChecked(PitProSettings::DdFileSwitch, isOn);
        else if (!key.compare("tt"))
            settings.setChecked(PitProSettings::TtFileSwitch, isOn);
    } 
    else if (!group.compare("dir"))
    {
        if (!key.compare("dat"))
            settings.setValue(PitProSettings::DataDir, val);
        else if (!key.compare("out"))
            settings.setValue(PitProSettings::OutputDir, val);
    } 
    else if (!group.compare("ext"))
    {
        if (!key.compare("obs"))
            settings.setValue(PitProSettings::ObsSuffix, val);
        else if (!key.compare("tag"))
            settings.setValue(PitProSettings::TagSuffix, val);
        else if (!key.compare("surph"))
            settings.setValue(PitProSettings::SurphSuffix, val);
        else if (!key.compare("error"))
            settings.setValue(PitProSettings::ErrorSuffix, val);
        else if (!key.compare("seq"))
            settings.setValue(PitProSettings::SeqSuffix, val);
        else if (!key.compare("dd"))
            settings.setValue(PitProSettings::DdSuffix, val);
        else if (!key.compare("tt"))
            settings.setValue(PitProSettings::TtSuffix, val);
    }
}

void
PPRunConfig::write(const string& fileName)
{
    PPBatchOutputMaker& out = PPBatchOutputMaker::getInstance();

    ofstream ofs(fileName.c_str());
    if (!ofs.is_open())
        out.write("Unable to open run configuration file.", PPBatchOutputMaker::Error);
    else
    {
        PitProSettings& settings = PitProSettings::getInstance();

        ofs << "#" << endl;
        ofs << "# CaptHist Run time Coniguration file" << endl;
        ofs << "#" << endl << endl;
        ofs << "# sites: capture history fields configurations" << endl;

        // sites
        StringVector::const_iterator it;

        ofs << "sites_juvenile:";
        StringVector juvenileSites = settings.getValues(PitProSettings::HistField);
        for (size_t i = 0; i < juvenileSites.size(); ++i)
            ofs << (i == 0 ? " " : ", ") << juvenileSites[ i ];
        ofs << endl;

        ofs << "sites_adult:";
        StringVector adultSites = settings.getValues(PitProSettings::AdultField);
        for (size_t i = 0; i < adultSites.size(); ++i)
            ofs << (i == 0 ? " " : ", ") << adultSites[ i ];
        ofs << endl;

        int numMainSites = settings.getIntValue(PitProSettings::NumMainSites);
        int numSites = juvenileSites.size() + adultSites.size();
        if (numMainSites < 0 || numMainSites >= numSites)
            numMainSites = numSites;
        ofs << "sites_main: " << numMainSites << endl;
        ofs << endl;

        ofs << "# out: output file switches" << endl;

        ofs << "out_surph:  " << (settings.isChecked(PitProSettings::SurphFileSwitch) ? 1 : 0) << endl;
        ofs << "out_error:  " << (settings.isChecked(PitProSettings::ErrorsFileSwitch) ? 1 : 0) << endl;
        ofs << "out_tt:     " << (settings.isChecked(PitProSettings::TtFileSwitch) ? 1 : 0) << endl;
        ofs << "out_dd:     " << (settings.isChecked(PitProSettings::DdFileSwitch) ? 1 : 0) << endl;
        ofs << "out_seq:    " << (settings.isChecked(PitProSettings::SequenceFileSwitch) ? 1 : 0) << endl;
        ofs << endl;

        ofs << "# dir: directories for input output" << endl;

        ofs << "dir_dat: " << settings.getValue(PitProSettings::DataDir) << endl;
        ofs << "dir_out: " << settings.getValue(PitProSettings::OutputDir) << endl;
        ofs << endl;

        ofs << "# ext: input filename extensions" << endl;

        ofs << "ext_obs: " << settings.getValue(PitProSettings::ObsSuffix) << endl;
        ofs << "ext_tag: " << settings.getValue(PitProSettings::TagSuffix) << endl;
        ofs << endl;

        ofs << "# ext: output filename extensions" << endl;

        ofs << "ext_surph: " << settings.getValue(PitProSettings::SurphSuffix) << endl;
        ofs << "ext_error: " << settings.getValue(PitProSettings::ErrorSuffix) << endl;
        ofs << "ext_tt:	   " << settings.getValue(PitProSettings::TtSuffix) << endl;
        ofs << "ext_dd:	   " << settings.getValue(PitProSettings::DdSuffix) << endl;
        ofs << "ext_seq:   " << settings.getValue(PitProSettings::SeqSuffix) << endl;
    }
}
