/*
*/

#include <boost/regex.hpp>

#include <QStringList>

#include "RiverKm.h"
#include "ArrayDefs.h"
#include "StringManip.h"
#include "StringTok.h"

using namespace cbr;
using std::string;

RiverKm::RiverKm( const char* riverk ) {
	setRiverKm(riverk);
}

void RiverKm::setRiverKm( const char* riverk) {
	if (!riverk) 
		data.clear();
	else 
		data = riverk;
}

int RiverKm::total() const {
	int total = 0;
	if (isValid()) {
        QStringList toks;
//		StringVector toks;
        stringTok(toks, QString(data.c_str()), ".");
        for (int i = 0; i < toks.count(); i++) {
//		for ( StringVector::iterator it = toks.begin(); it != toks.end(); ++it ) {
            total += toks.at(i).toInt();
//			total += fromString<int>( *it );
		}
	}
	return total;
}

bool RiverKm::isValid() const {
	if (data.empty())
		return false;
   static const boost::regex e( "[\\.0-9]+" );
   return regex_match( data, e);
}


bool RiverKm::isColocated(const RiverKm& target) const {
	if (!isValid() || !target.isValid())
		return false;
	return data.compare(target.data) == 0;
}

/*
 * Return true if target is upstream of this site. Assume the target site is 
 * upstream of this site, see if it holds up.
 */
bool RiverKm::isDownstream(const RiverKm& target) const {
    bool down = false;
    if (isValid() && target.isValid()) {
        if (target.total() > total())
            down = true;
    }
    return down;
    /*
	if (!isValid() || !target.isValid())
		return false;

    if (target.total() > total())
        return true;
    else
        return false;

    QStringList upToks;
//	StringVector upToks;
    stringTok(upToks, target.data.c_str(), ".");
    QStringList dnToks;
//	StringVector dnToks;
    stringTok(dnToks, data.c_str(), ".");

	if (dnToks.size() > upToks.size())
		return false;

	StringVector::iterator it_up = upToks.begin();
	StringVector::iterator it_dn = dnToks.begin();
	while (it_dn != dnToks.end() && it_up != upToks.end()) {
		int up = fromString<int>( *it_up );
		int dn = fromString<int>( *it_dn );
		++it_dn;
		++it_up;
		if (up < dn)
			return false;
		else if (up > dn) {
			if (it_dn != dnToks.end())
				return false;
			else
				return true;
		}
	}

	if (it_up != upToks.end())
		return true;
	else
		return false;

    return true;*/
}


bool RiverKm::isUpstream(const RiverKm& target) const {
    bool up = false;
    if (!isDownstream(target) && !isColocated(target))
        up = true;
    return up;
//	return !isColocated(target) && target.isDownstream(*this);
}
