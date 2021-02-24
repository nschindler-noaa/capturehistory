/*
*
*/

#include <string>
#include <iostream>
#include <sstream>

#include <StringManip.h>
#include <Sites.h>
#include <DateConverter.h>

#include "PPFlags.h"
#include "PitProSettings.h"
#include "PPOutputMaker.h"
#include "PPVersion.h"
#include "PPErrors.h"

using std::string;
using std::stringstream;
using std::endl;
using std::cout;
using cbr::DateConverter;
using cbr::toString;


void PPFlags::readArgs( int argc, char *argv[], PPOutputMaker& out)
{
    PitProSettings& settings = PitProSettings::getInstance();

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            char key = argv[i][1];
            char* value = 0;
            if (strlen(argv[i]) > 2)
                value = argv[i]+2;
            else
                value = (char*)0;

            if ( !value &&
                ( key == 'r' || key == 'p' || key == 'i' ||
                key == 'G' || key == 'M' || key == 'R' ||
                key == 'F' || key == 'S' || key == 'd' ) )
            {
                out.write ("Warning. -" + toString<char> (key) +
                    " found with no value.", PPOutputMaker::Error);
                continue;
            }

            if (key == 'A')
                settings.setChecked( PitProSettings::AdultModeSwitch, true );
            else if (key == 'E')
                settings.setChecked( PitProSettings::ErrorsCheck, true );
            else if (key == 'n')
                settings.setChecked( PitProSettings::NewRcFile, true );
            else if (key == 'c')
                settings.setChecked( PitProSettings::SingleCoilSwitch, true );
            else if (key == 'v' || key=='V')
                settings.setChecked( PitProSettings::Version, true );
            else if (key == 'j')
                settings.setChecked( PitProSettings::JulianDates, true );
            else if (key == 'l')
            {
                settings.setChecked( PitProSettings::LengthCovSwitch, true );
                settings.setChecked( PitProSettings::ZeroLengthSwitch, true );
            }
            else if (key == 'h')
                settings.setChecked( PitProSettings::Usage, true );
            else if (key == 'U')
                settings.setChecked( PitProSettings::UnknownSwitch, true );
            else if (key == 't')
                settings.setChecked( PitProSettings::TagCheck, false );
            else if (key == 'T') {
                if ( !value  )
                    settings.setValue( PitProSettings::OutputFormat, "SURPH1" );
                else if ( !strcmp( value, "SURPH2" ) || !strcmp( value, "ROSTER" ) )
                    settings.setValue( PitProSettings::OutputFormat, value );
                else {
                    out.write (QString("Error. argument to -T should be SURPH1, SURPH2, or ROSTER."));
                    settings.setValue( PitProSettings::OutputFormat, "SURPH1" );
                }
            }
            else if (key == 'd')
            {
                if ( strlen( value ) != 8 )
                    out.write (QString("Error. argument to -d should be in date format yyyymmdd."));
                else {
                    DateConverter dc( value );
                    settings.setValue( PitProSettings::RelDate, dc.getTime() );
                    settings.setChecked( PitProSettings::AltRelDate, true );
                }
            }
            else if (key == 'J')
            {
                if ( strlen( value ) != 8 )
                    out.write (QString("Error. argument to -J should be in date format yyyymmdd."));
                else {
                    DateConverter dc( value );
                    settings.setValue( PitProSettings::JuvenileCutoffDate, dc.getTime() );
                }
            }
            else if (key == 'r')
            {
                settings.setValue( PitProSettings::RelFile, value );
            }
            else if (key == 'p')
            {
                settings.setValue( PitProSettings::OutPrefix, value );
            }
            else if (key == 'i')
            {
                settings.setValue( PitProSettings::RcFileName, value );
            }
            else if (key == 'C')
            {
                if (!value)
                    settings.setChecked( PitProSettings::ShowConfig, true );
                else
                {
//					settings.setChecked (PitProSettings::SitesConfigSwitch, false ); // use alt
                    settings.setValue (PitProSettings::AltSitesConfig, value );
                }
            }
            else if (key == 'G') /* group */
                settings.addParamDef( PitProSettings::GroupPrefix, value );
            else if (key == 'M') /* mortality file */
            {
                settings.setValue( PitProSettings::MortFile, value );
            }
            else if (key == 'R') /* release site */
            {
                char *c = value;
                if (strlen(c) == 3)
                    c++;
                else
                    settings.setChecked( PitProSettings::SiteRel, true );

                Sites* sites = Sites::getInstance();
                int relsite = sites->getSiteNumber(c);

//				settings.setValue( PitProSettings::RelSiteString, value );
                settings.setValue( PitProSettings::RelSite, relsite );
            }
            else if (key == 'F')
            {
                if (strcmp (value, "A") && strcmp (value, "U") &&
                    strcmp (value, "W") && strcmp (value, "H"))
                {
                    fprintf(stderr, "!! Warning. Unknown rearing type: %s\n", value);
                }
                settings.setValue( PitProSettings::RearType, cbr::toString<char>( value[ 0 ] ) );
            }
            else if (key == 's')
            {
                int split = 1;

                if (value)
                {
                    int nsplit = atoi(value);
                    if (nsplit > 0 && nsplit < 4)
                        split = nsplit;
                }

                settings.setValue( PitProSettings::Split, split );
            }
            else if (key == 'S')
            {
                int is = atoi(value);
                if (strcmp(value, "A") && is != 9 && is < 1 && is > 5)
                    fprintf(stderr, "!! Warning. Unknown species: %s\n", value);
                settings.setValue( PitProSettings::Species,  value);
            }
            else if (key == 'y') // migration year
            {
                if (strlen(value) != 4)
                    fprintf(stderr, "!! Warning. Migration year should be 4 digits.");
                else
                {
                    settings.setValue (PitProSettings::MigrationYear, value);
                }
            }

            else
                fprintf(stderr, "!! Warning. Unknown flag: %c\n", key);
        }
    }

    if ( settings.getValue( PitProSettings::RcFileName ).empty() )
        settings.setValue( PitProSettings::RcFileName, "chrc" );

}

string PPFlags::usage()
{
    stringstream ss;

    ss << "capthist: " << PPVersion::versionString() << endl;
    ss << "Usage:" << endl;
    ss << "   -A: Generate full life cycle capture histories compatible with ROSTER." << endl;
    ss << "       Transported juvenile flag will be 3 instead of 2 and the adult flags" << endl;
    ss << "       A, B, C, etc will be used. In this mode it is usually necessary to" << endl;
    ss << "       supply a migration year (-y) or juvenile cutoff date (-J) to enable" << endl;
    ss << "       the program to distinguish between juvenile and adult detections. " << endl;
    ss << "   -d<yyyymmdd>: Use this release date for all fish in place of any"  << endl;
    ss << "       release dates found in the release file (if given)." << endl;
    ss << "   -c: Allow single coil hits." << endl;
    ss << "   -C<config>: When the -C flag is given alone this will cause ." << endl;
    ss << "       the program to display configuration information" << endl;
    ss << "       and exit. To change the configuration save this" << endl;
    ss << "       file by sending the -C output to a file, make your" << endl;
    ss << "       changes and then call the capthist with the -C flag" << endl;
    ss << "       again but this time give the new site configuration" << endl;
    ss << "       file name: -Cfilename.txt" << endl;
    ss << "   -E: Check for and remove errors." << endl;
    ss << "       The columns in the error output file have the following meaning:" << endl;
    ss << "          1: Tag ID" << endl;
    for ( int i = 0; i < PPErrors::NumErrorTypes; ++i ) {
        ss << "         ";
        ss.width(2);
        ss << i + 2 << ": " << PPErrors::getText( i ) << endl;
    }
    ss << "   -F<rearing type>: A=any, U=unknown, W=wild, H=hatchery (default)." << endl;
    ss << "   -G<group>: Gives group prefix, multiple -G flags allowed." << endl;
    ss << "   -i<rc file name>: Use alternate rc file name." << endl;
    ss << "   -j: Output dates in the dd file as julian dates."  << endl;
    ss << "   -J<yyyymmdd>: Juvenile life stage cutoff date. Any observations" << endl;
    ss << "                 after this date are marked as adult observations." << endl;
    ss << "   -l: Include length covariate in surph file, remove zero length fish" << endl;
    ss << "   -M<mortality file>: Use alternate mortality file." << endl;
    ss << "   -n: Create a default rc file and exit." << endl;
    ss << "   -p<output prefix>: Gives output name prefix, helpful when using " << endl;
    ss << "       multiple groups." << endl;
    ss << "   -r<release file>: Use alternate release file" << endl;
    ss << "   -R<release site>: gives release site, the following are defined:" << endl;
    ss << "                     Adding an 'a' signifies above (agr = above gr)" << endl;
    Sites* sites = Sites::getInstance();
    for ( int i = 0; i < sites->nsites(); i++ ) {
        Site* site = sites->getSite( i );
        ss << "                       " << site->getSiteCode() << "  " << site->getLongName() << endl;
    }
    ss << "   -S<species>: The following species codes are allowed:" << endl;
    ss << "       A Any species" << endl;
    ss << "       1 Chinook (default)" << endl;
    ss << "       2 Coho" << endl;
    ss << "       3 Steelhead" << endl;
    ss << "       4 Sockeye" << endl;
    ss << "       5 Chum" << endl;
    ss << "       9 Non-Salmonid or Other Species" << endl;
    ss << "   -t: Keep fish found in the obs file but not in the tag file." << endl;
    ss << "   -T<format>: The format of the capture histories file: surph1, surph2, or" << endl;
    ss << "               roster. If no argument is given, the format is set to surph1." << endl;
    ss << "   -U: Give 3 for unknown capture status." << endl;
    ss << "   -v: Print the version number." << endl;
    ss << "   -y<year>: Migration year (yyyy)." << endl;


    return ss.str();
}
