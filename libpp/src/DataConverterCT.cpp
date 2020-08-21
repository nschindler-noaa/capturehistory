/*
*/

#include <string>
#include <fstream>
#include <sstream>

#include <qfile.h>
#include <qfileinfo.h>

#include "DataConverterCT.h"
#include "PPObs.h"
#include "PPTag.h"
#include "PPRel.h"

using std::string;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::endl;

DataConverterCT::DataConverterCT (QObject* object, const QString& name) :
    ComputationThread (object, name), convertType(Invalid) {}


void DataConverterCT::compute() {
    if (convertType != Obs && convertType != Tag && convertType != Both) {
		cancel();
		return;
	}

	int totalBytes = 0;

    if (convertType == Obs || convertType == Both) {
        totalBytes = getTotalBytes ();
        sendNumSteps (totalBytes);

		PPObs ppObs;
        ppObs.setColumnOrder (PPObs::PitCode, 1);
        ppObs.setColumnOrder (PPObs::ObsSite, 2);
        ppObs.setColumnOrder (PPObs::ObsTime, 3);
        ppObs.setColumnOrder (PPObs::Coil1, 5);

        ifstream ifs (obs.toStdString ().data());
        if (!ifs.is_open ())  {
            sendStatusMessage ("Error. Unable to open file \"" + obs + "\"...");
			sendCanceledSignal();
			return;
		}

        ofstream ofs( tobs.toStdString().data() );
		if ( !ofs.is_open() ) {
			sendErrorMessage( "Error. Unable to open file \"" + tobs + "\"..." );
			sendCanceledSignal();
			return;
		}

		sendStatusMessage( "Converting observation data..." );
		string line;
		int bytesProcessed = 0;
		int row = 0;
		while (getline( ifs, line ) ) {
			if ( isCanceled() ) {
				cancel();
				return;
			}

			// report progress
			bytesProcessed += line.size() + 1;
			sendCurrentStep( bytesProcessed );

			stringstream instream( line );
			instream >> ppObs;

			if ( ppObs.isOk() && !ppObs.isHeader() ) {
				++row;
				ofs << ppObs << endl;
			}
		}
		ifs.close();
		ofs.close();

		if ( !row ) {
			sendErrorMessage( "Observation file: no valid version 3rows found." );
			cancel();
			return;
		}
	} 

	if ( convertType == Tag || convertType == Both ) {
		totalBytes = getTotalBytes();
		sendNumSteps( totalBytes );
		int bytesProcessed = 0;

		// read release file, if given
		std::map<string, double> releaseData;
		if ( !rel.isNull() ) {
            ifstream ifs( rel.toStdString().data() );
			if ( !ifs.is_open() )  {
				sendErrorMessage( "Error. Unable to open release file \"" + rel + "\"..." );
				sendCanceledSignal();
				return;
			}

			sendStatusMessage( "Converting tagging data..." );
			string line;
			int row = 0;
			while (getline( ifs, line ) ) {
				if ( isCanceled() ) {
					cancel();
					return;
				}

				// report progress
				bytesProcessed += line.size() + 1;
				sendCurrentStep( bytesProcessed );

				stringstream instream( line );
				PPRel ppRel;
				instream >> ppRel;

				if ( ppRel.isOk() && !ppRel.isHeader() ) {
					++row;
					releaseData[ ppRel.getKey() ] = ppRel.getReleaseTime();
				}
			}
			ifs.close();


			if ( !row )
				sendErrorMessage( "Release file: no valid version 3 rows found." );
		}

        ifstream ifs( tag.toStdString().data() );
		if ( !ifs.is_open() )  {
			sendErrorMessage( "Error. Unable to open file \"" + tag + "\"..." );
			sendCanceledSignal();
			return;
		}

		PPTag ppTag;
		ppTag.setColumnOrder( PPTag::TagGroup, 0 );
		ppTag.setColumnOrder( PPTag::PitCode, 1 );
		ppTag.setColumnOrder( PPTag::RelTime, -1 );
		ppTag.setColumnOrder( PPTag::RelSite, -1 );
		ppTag.setColumnOrder( PPTag::Species, 2 );
		ppTag.setColumnOrder( PPTag::Run, -1 );
		ppTag.setColumnOrder( PPTag::RearType, 3 );
		ppTag.setColumnOrder( PPTag::ICov1, 4 );

        ofstream ofs( ttag.toStdString().data() );
		if ( !ofs.is_open() ) {
			sendErrorMessage( "Error. Unable to open file \"" + ttag + "\"..." );
			sendCanceledSignal();
			return;
		}

		sendStatusMessage( "Processing tag file \"" + tag + "\"..." );
		int row = 0;
		string line;
		while (getline( ifs, line ) ) {
			if ( isCanceled() ) {
				cancel();
				return;
			}

			// report progress
			bytesProcessed += line.size() + 1;
			sendCurrentStep( bytesProcessed );

			stringstream instream( line );
			instream >> ppTag;
			if ( ppTag.isOk() && !ppTag.isHeader() ) {
				++row;
				if ( releaseData.find( ppTag.getTagGroup() ) != releaseData.end() )
					ppTag.setRelTime( releaseData[ ppTag.getTagGroup() ] );
				else if ( releaseData.find( ppTag.getPitCode() ) != releaseData.end() )
					ppTag.setRelTime( releaseData[ ppTag.getPitCode() ] );

				ofs << ppTag << endl;
			}

		}
		ifs.close();
		ofs.close();

		if ( !row ) {
			sendErrorMessage( "Tag file: no valid rows found." );
			cancel();
			return;
		}
	}

	sendCurrentStep( totalBytes );
	sendCompletedSignal();


}

void DataConverterCT::cancel() {
	sendCanceledSignal();
}

int DataConverterCT::getTotalBytes() {
	if ( convertType != Obs && convertType != Tag && convertType != Both )
		return 0;

	QStringList files;
	if ( convertType == Obs || convertType == Both  ) {
		files += obs;
	}
	if ( convertType == Tag || convertType == Both  ) {
		files += tag;
		files += rel;
	}

	int numBytes = 0;
	for ( QStringList::iterator it = files.begin(); it != files.end(); ++it ) {
		QString file = *it;
		if ( !file.isNull() ) {
			QFileInfo fi( *it );
			if (fi.exists())
				numBytes += fi.size();
		}
	}

	return numBytes;
}

void DataConverterCT::setFiles( const QString& o, const QString& t, const QString& r, 
							   const QString& to, const QString& tt )
{
	obs = o;
	tag = t;
	rel = r;
	tobs = to;
	ttag = tt;
}
