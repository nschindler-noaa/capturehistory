/*
 * Statistics.cpp
 */

#include <math.h>

#include "Statistics.h"

using namespace std;


/*
 * Arithmetic mean
 */
double Statistics::amean( const vector<double>& data ) {
    if ( data.size() == 0 )
        return 0;

    double sum = 0;
    for ( unsigned int i = 0; i < data.size(); i++ ) 
        sum += data[ i ];
    return sum / data.size();
}

/*
 * Harmonic mean
 */
double Statistics::hmean( const vector<double>& data ) {
    if ( data.size() == 0 )
        return 0;

   double sum = 0;
    for ( unsigned int i = 0; i < data.size(); i++ ) 
        sum += ( 1 / data[ i ] );
    return data.size() / sum;

}

double Statistics::var( const vector<double>& data ) {
    if ( data.size() < 2 )
        return 0;

    double m = amean( data );

    double sum = 0;
    for ( unsigned int i = 0; i < data.size(); i++ ) 
        sum += pow( data[ i ] - m, 2 );
    return sum / ( data.size() - 1);
}



vector<double> Statistics::invert( const vector<double>& data ) {
	vector<double> inv;
	for (vector<double>::const_iterator it = data.begin(); it != data.end(); it++ ) {
		double x = static_cast<double>( *it );
		inv.push_back( 1.0 / x );
	}
	return inv;
}

double Statistics::sum( const vector<double>& data ) {
	double s = 0;
	for (vector<double>::const_iterator it = data.begin(); it != data.end(); it++ ) {
		s += static_cast<double>( *it );
	}
	return s;
}

double Statistics::hvar( const vector<double>& data ) {
    if ( data.size() < 2 )
        return 0;

	vector<double> inv = invert( data );
	double v1 = Statistics::var( inv );
	int n = data.size();
	v1 /= n;

	double s = sum( inv );
	s /= n;
	
	double var = v1 / pow( s, 4 );
	return var;
}


double Statistics::se( const vector<double>& data ) {
    return sqrt( var( data ) );
}

