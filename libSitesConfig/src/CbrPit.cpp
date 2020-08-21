/*
 *
 *
 */

#include "CbrPit.h"

using std::string;
using namespace cbr;

static CbrPit *cbrPitPtr = NULL;


CbrPit::CbrPit() {
    setNumJuvenileSymbols (NumOutcomes);
/*    setJuvenileSymbol(Hold);
    setJuvenileSymbol(Returned);
    setJuvenileSymbol(Sampled);
    setJuvenileSymbol(Transported);
    setJuvenileSymbol(Unknown);
    setJuvenileSymbol(Bypass);
    setJuvenileSymbol(NoDetect);
    setJuvenileSymbol(Invalid);*/
    setOutputFormat(Surph);
    cbrPitPtr = this;
}

CbrPit& CbrPit::getInstance() {
    if (cbrPitPtr == NULL)
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
            setJuvenileSymbol(Returned, "1");
            setJuvenileSymbol(Transported, "2");
            setJuvenileSymbol(Sampled,  "3");
            setJuvenileSymbol(Hold,     "4");
            setJuvenileSymbol(Bypass,   "5");
            setJuvenileSymbol(Spillway, "6");
            setJuvenileSymbol(Unknown,  "9");
            setJuvenileSymbol(Invalid,  "I");
            setJuvenileSymbol(PitTrawl, "1");
            setJuvenileSymbol(Weir,     "2");
            setJuvenileSymbol(BonnLadder, "2");
            setJuvenileSymbol(AvianColony, "3");
            setJuvenileSymbol(PileDike,  "4");
            setJuvenileSymbol(PitBarge,  "5");
            setJuvenileSymbol(AMBridge,  "6");
            setJuvenileSymbol(AdultDetect, "7");
        }
        else  // default numbers compatible with historical data
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
        }

    } else {  // Roster
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
    }
    if (unknownLetter)
        setJuvenileSymbol(Unknown, "U");
}

string
CbrPit::stringFromJuvenileOutcome(Outcome oc) {
    if (oc < NumOutcomes) {
        string *strp = new string(juvenileSymbols.at(oc).toStdString().data());
        return *strp;
    }
    else {
        return "U";
    }
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
    switch (oc) {
    case Hold:
        return "H";
    case Returned:
        return "R";
    case Sampled:
        return "S";
    case Transported:
        return "T";
    case Unknown:
        return "U";
    case Bypass:
        return "B";
    case Spillway:
        return "P";
    case Weir:
        return "W";
    case NoDetect:
        return "N";
    default:
        return "I";
    }
}

string
CbrPit::stringFromAdultOutcome(Outcome oc, int age, JacksPolicy jacksPolicy) {
    if (outputFormat == Surph) {
        return stringFromJuvenileOutcome(oc);
    }

    int index = age;
    if (jacksPolicy == JP_Combined && age == 0)
        index = 1;
    else if (jacksPolicy == JP_Seperate)
        index = age + 1;


    switch (oc) {
        case Returned: case Bypass:
        {
            switch (index) {
                case 1:
                    return "A";
                case 2:
                    return "B";
                case 3:
                    return "C";
                default:
                    return "D";
            }
        }
        case Sampled:
        {
            switch (index) {
                case 1:
                    return "a";
                case 2:
                    return "b";
                case 3:
                    return "c";
                default:
                    return "d";
            }
        }
        default:
            return "0";
    }
}

char
CbrPit::charFromStage(Stage stage) {
    switch (stage) {
        case ST_Adult:
            return 'A';
        case ST_Juvenile:
            return 'J';
        default:
            return 'U';
    }
}

string
CbrPit::stringFromStage(Stage stage) {
    switch (stage) {
        case ST_Adult:
            return "adult";
        case ST_Juvenile:
            return "juvenile";
        default:
            return "unknown";
    }
}

CbrPit::Stage
CbrPit::stageFromChar(char stage) {
    switch (stage) {
        case 'J': case 'j':
            return ST_Juvenile;
        case 'A': case 'a':
            return ST_Adult;
        default:
            return ST_Unknown;
    }
}

CbrPit::Stage
CbrPit::stageFromString(const std::string& stage) {
    if (!stage.compare("juvenile"))
        return ST_Juvenile;
    else if (!stage.compare("adult"))
        return ST_Adult;
    else
        return ST_Unknown;
}

bool
CbrPit::isRemoved(Outcome oc) const {
    if (oc == Unknown || oc == Sampled || oc == Transported || oc == Hold)
        return true;
    return false;
}
