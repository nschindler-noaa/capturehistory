/*
 *
 *
 */

#include <QStringList>

#include "CbrPit.h"

using std::string;
using namespace cbr;

static CbrPit *cbrPitPtr = 0;


CbrPit::CbrPit() {
    setNumJuvenileSymbols (NumOutcomes);
    setOutputFormat(Surph);
    cbrPitPtr = this;
}

CbrPit& CbrPit::getInstance() {
    if (cbrPitPtr == 0)
    {
        cbrPitPtr = new CbrPit();
    }

    return *cbrPitPtr;
}

void CbrPit::setNumJuvenileSymbols(int num)
{
    for (int i = 0; i < num; i++)
        juvenileSymbols.append(QString("0"));
}

// 
// This function is mainly to allow for Transportation to be either 2 or 3
// depending on output type, or for Unknown to be a 'U' instead of 2 based
// on program option.
//

void CbrPit::setJuvenileSymbol(Outcome oc, const string& symbol) {
    int index = (int)oc;
    QString dsymbol(symbol.data());
    if (index < NumOutcomes)
    {
        if (dsymbol.isEmpty())
        {
            switch (oc)
            {
            case Hold:
                dsymbol = QString("2");
                break;
            case Returned:
                dsymbol = QString("1");
                break;
            case Sampled:
                dsymbol = QString("2");
                break;
            case Transported:
                dsymbol = QString("2");
                break;
            case Unknown:
                dsymbol = QString("2");
                break;
            case Bypass:
                dsymbol = QString("1");
                break;
            case Spillway:
                dsymbol = QString("1");
                break;
            case Weir:
            case BonnLadder:
                dsymbol = QString("1");
                break;
            case AvianColony:
                dsymbol = QString("1");
                break;
            case AdultDetect:
            case PitTrawl:
            case PileDike:
            case PitBarge:
            case AMBridge:
            case TrTowers:
                dsymbol = QString("1");
                break;
            case NoDetect:
                dsymbol = QString("0");
                break;
            case Invalid:
                dsymbol = QString("I");
                break;
            default:
                dsymbol = QString("N");
            }
        }
        juvenileSymbols[index] = dsymbol;
    }
}

void
CbrPit::setOutputFormat(Format format, const std::string &code, bool unknownLetter) {
    outputFormat = format;

    if (format == Surph) {
        if (code.compare("All") == 0) // new usage to distinguish passage routes
        {
            setJuvenileSymbol(NoDetect, "0");
            setJuvenileSymbol(Returned, "R");
            setJuvenileSymbol(Transported, "T");
            setJuvenileSymbol(Sampled,  "S");
            setJuvenileSymbol(Hold,     "H");
            setJuvenileSymbol(Bypass,   "B");
            setJuvenileSymbol(Spillway, "P");
            setJuvenileSymbol(Unknown,  "U");
            setJuvenileSymbol(Invalid,  "I");
            setJuvenileSymbol(PitTrawl, "R");
            setJuvenileSymbol(Weir,     "W");
            setJuvenileSymbol(BonnLadder, "W");
            setJuvenileSymbol(AvianColony, "V");
            setJuvenileSymbol(PileDike,  "D");
            setJuvenileSymbol(PitBarge,  "G");
            setJuvenileSymbol(AMBridge,  "M");
            setJuvenileSymbol(AdultDetect, "A");
            setJuvenileSymbol(TrTowers, "X");
        }
        else  // code = "Std": default numbers compatible with historical data
        {
            setJuvenileSymbol(Hold);
            setJuvenileSymbol(Returned);
            setJuvenileSymbol(Sampled);
            setJuvenileSymbol(Transported);
            setJuvenileSymbol(Unknown);
            setJuvenileSymbol(Bypass);
            setJuvenileSymbol(NoDetect);
            setJuvenileSymbol(Spillway);
            setJuvenileSymbol(Weir);
            setJuvenileSymbol(AvianColony);
            setJuvenileSymbol(Invalid);
            setJuvenileSymbol(BonnLadder);
            setJuvenileSymbol(PileDike);
            setJuvenileSymbol(PitBarge);
            setJuvenileSymbol(AMBridge);
            setJuvenileSymbol(AdultDetect);
            setJuvenileSymbol(TrTowers);
        }

    } else {  // Roster - same as Std except for Transported
        setJuvenileSymbol(Hold);
        setJuvenileSymbol(Returned);
        setJuvenileSymbol(Sampled);
        setJuvenileSymbol(Transported, "3");
        setJuvenileSymbol(Unknown);
        setJuvenileSymbol(Bypass);
        setJuvenileSymbol(NoDetect);
        setJuvenileSymbol(Spillway);
        setJuvenileSymbol(Weir);
        setJuvenileSymbol(AvianColony);
        setJuvenileSymbol(Invalid);
        setJuvenileSymbol(BonnLadder);
        setJuvenileSymbol(PileDike);
        setJuvenileSymbol(PitBarge);
        setJuvenileSymbol(AMBridge);
        setJuvenileSymbol(AdultDetect);
        setJuvenileSymbol(TrTowers);
    }
    if (unknownLetter)
        setJuvenileSymbol(Unknown, "U");
}

string
CbrPit::stringFromJuvenileOutcome(Outcome oc) {
    string str("U");
    if (oc < NumOutcomes) {
        str = juvenileSymbols.at(oc).toStdString();
//        string *strp = new string(juvenileSymbols.at(oc).toStdString().data());
//        return *strp;
    }
    return str;
}
/*
string
CbrPit::stringFromJuvenileOutcome(Outcome oc) {
    if (oc < NumOutcomes)
        return juvenileSymbols.at(oc);//[oc];
    else
        return "U";
}*/

string
CbrPit::labelFromOutcome(Outcome oc) {
    string label("I");
    switch (oc) {
    case Hold:
        label = "H";
        break;
    case Returned:
        label = "R";
        break;
    case Sampled:
        label = "S";
        break;
    case Transported:
        label = "T";
        break;
    case Unknown:
        label = "U";
        break;
    case Bypass:
        label = "B";
        break;
    case Spillway:
        label = "P";
        break;
    case Weir:
        label = "W";
        break;
    case NoDetect:
        label = "N";
        break;
    case AdultDetect:
        label = "A";
        break;
    case PitBarge:
        label = "G";
        break;
    case PileDike:
        label = "D";
        break;
    case PitTrawl:
        label = "R";
        break;
    case AvianColony:
        label = "V";
        break;
    case BonnLadder:
        label = "W";
        break;
    case AMBridge:
        label = "M";
        break;
    case TrTowers:
        label = "X";
        break;
    default:  // Invalid, NoDetect,
        label = "I";
    }
    return label;
}

string
CbrPit::stringFromAdultOutcome(Outcome oc, int age, JacksPolicy jacksPolicy) {
    string code("A");
    int index = age;
    if (outputFormat == Surph) {
        code = stringFromJuvenileOutcome(oc);
    }
    else {
        if (jacksPolicy == JP_Combined && age == 0)
            index = 1;
        else if (jacksPolicy == JP_Seperate)
            index = age + 1;


        switch (oc) {
            case Returned: case Bypass:
            {
                switch (index) {
                    case 1:
                        code = "A";
                    break;
                    case 2:
                        code = "B";
                    break;
                    case 3:
                        code = "C";
                    break;
                    default:
                        code = "D";
                }
                break;
            }
            case Sampled:
            {
                switch (index) {
                    case 1:
                        code = "a";
                    break;
                    case 2:
                        code = "b";
                    break;
                    case 3:
                        code = "c";
                    break;
                    default:
                        code = "d";
                }
                break;
            }
            default:
                code = "0";
        }
    }
    return code;
}

char
CbrPit::charFromStage(Stage stage) {
    char c = 'U';
    switch (stage) {
        case ST_Adult:
            c = 'A';
        break;
        case ST_Juvenile:
            c = 'J';
        break;
        default:
            c = 'U';
    }
    return c;
}

string
CbrPit::stringFromStage(Stage stage) {
    string s("unknown");
    switch (stage) {
        case ST_Adult:
            s = "adult";
        break;
        case ST_Juvenile:
            s = "juvenile";
        break;
        default:
            s = "unknown";
    }
    return s;
}

CbrPit::Stage
CbrPit::stageFromChar(char stage) {
    CbrPit::Stage st = ST_Unknown;
    switch (stage) {
        case 'J': case 'j':
            st = ST_Juvenile;
        break;
        case 'A': case 'a':
            st = ST_Adult;
        break;
        default:
            st = ST_Unknown;
    }
    return st;
}

CbrPit::Stage
CbrPit::stageFromString(const std::string& stage) {
    CbrPit::Stage st = ST_Unknown;
    if (!stage.compare("juvenile"))
        st = ST_Juvenile;
    else if (!stage.compare("adult"))
        st = ST_Adult;
    else
        st = ST_Unknown;
    return st;
}

bool
CbrPit::isRemoved(Outcome oc) const {
    bool removed = false;
    if (oc == Unknown || oc == Sampled || oc == Transported || oc == Hold)
        removed = true;
    return removed;
}
