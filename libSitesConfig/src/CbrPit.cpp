/*
 *
 *
 */

#include <QStringList>

#include "CbrPit.h"

//using std::string;
using namespace cbr;

static CbrPit *cbrPitPtr = nullptr;


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
    if (cbrPitPtr == nullptr)
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

void CbrPit::setJuvenileSymbol(Outcome oc, const QString symbol) {
    QString dsymbol(symbol);
    if (oc < NumOutcomes)
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
        juvenileSymbols[oc] = dsymbol;
    }
}

void CbrPit::setOutputFormat(Format format, const QString code, bool unknownLetter) {
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
    }
    if (unknownLetter)
        setJuvenileSymbol(Unknown, "U");
}

QString CbrPit::stringFromJuvenileOutcome(Outcome oc) {
//    QString result;
    if (oc < NumOutcomes) {
        result = juvenileSymbols.at(oc);
    }
    else {
        result = QString("U");
    }
    return result;
}
/*
string
CbrPit::stringFromJuvenileOutcome(Outcome oc) {
    if (oc < NumOutcomes)
        return juvenileSymbols.at(oc);//[oc];
    else
        return "U";
}*/

QString CbrPit::labelFromOutcome(Outcome oc) {
//    QString result;
    switch (oc) {
    case Hold:
        result = QString("H");
        break;
    case Returned:
        result = QString("R");
        break;
    case Sampled:
        result = QString("S");
        break;
    case Transported:
        result = QString("T");
        break;
    case Unknown:
        result = QString("U");
        break;
    case Bypass:
        result = QString("B");
        break;
    case Spillway:
        result = QString("P");
        break;
    case Weir:
        result = QString("W");
        break;
    case NoDetect:
        result = QString("N");
        break;
    case AdultDetect:
        result = QString("A");
        break;
    case PitBarge:
        result = QString("G");
        break;
    case PileDike:
        result = QString("D");
        break;
    case PitTrawl:
        result = QString("R");
        break;
    case AvianColony:
        result = QString("V");
        break;
    case BonnLadder:
        result = QString("W");
        break;
    case AMBridge:
        result = QString("M");
        break;
    default:  // Invalid, NoDetect,
        result = QString("I");
    }
    return result;
}

QString CbrPit::stringFromAdultOutcome(Outcome oc, int age, JacksPolicy jacksPolicy) {
//    QString result;
    if (outputFormat == Surph) {
        result = stringFromJuvenileOutcome(oc);
    }
    else {

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
                        result = QString("A");
                        break;
                    case 2:
                        result = QString("B");
                        break;
                    case 3:
                        result = QString("C");
                        break;
                    default:
                        result = QString("D");
                    break;
                }
                break;
            }
            case Sampled:
            {
                switch (index) {
                    case 1:
                        result = QString("a");
                        break;
                    case 2:
                        result = QString("b");
                        break;
                    case 3:
                        result = QString("c");
                        break;
                    default:
                        result = QString("d");
                        break;
                }
                break;
            }
            default:
                result = QString("0");
                break;
        }
    }
    return result;
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

QString &CbrPit::stringFromStage(Stage stage) {
    switch (stage) {
    case ST_Adult:
        result = QString("adult");
        break;
    case ST_Juvenile:
        result = QString("juvenile");
        break;
    default:
        result = QString("unknown");
        break;
    }
    return result;
}

CbrPit::Stage CbrPit::stageFromChar(char stage) {
    CbrPit::Stage cbrstage = ST_Unknown;
    switch (stage) {
    case 'J':
    case 'j':
        cbrstage = ST_Juvenile;
        break;
    case 'A':
    case 'a':
        cbrstage = ST_Adult;
        break;
    default:
        cbrstage = ST_Unknown;
    }
    return cbrstage;
}

CbrPit::Stage CbrPit::stageFromString(const QString stage) {
    CbrPit::Stage stg = ST_Unknown;
    if (!stage.compare("juvenile", Qt::CaseInsensitive))
        stg = ST_Juvenile;
    else if (!stage.compare("adult", Qt::CaseInsensitive))
        stg = ST_Adult;
    else
        stg = ST_Unknown;
    return stg;
}

bool
CbrPit::isRemoved(Outcome oc) const {
    bool removed = false;
    if (oc == Unknown || oc == Sampled || oc == Transported || oc == Hold)
        removed = true;
    return removed;
}
