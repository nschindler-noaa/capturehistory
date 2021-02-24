/*
 * Statistics.cpp
 */

#include <math.h>

#include "Statistics.h"

using namespace std;


/*
 * Arithmetic mean
 */
double Statistics::amean( const QList<double>& data ) {
    double amn = 0;
    double sum = 0;
    if (!data.isEmpty()) {
        for (int i = 0; i < data.size(); i++)
            sum += data[i];
        amn = sum / data.size();
    }
    return amn;
//    if ( data.size() == 0 )
//        return 0;

//    double sum = 0;
//    for ( unsigned int i = 0; i < data.size(); i++ )
//        sum += data[ i ];
//    return sum / data.size();
}

/*
 * Harmonic mean
 */
double Statistics::hmean(const QList<double> &data) {
    double hmn = 0;
    double sum = 0;
    if (!data.isEmpty()) {
        for (int i = 0; i < data.size(); i++)
            sum += (1 / data[i]);
        hmn = data.size() / sum;
    }
    return hmn;
}

double Statistics::var(const QList<double>& data) {
    if (data.size() < 2)
        return 0;

    double m = amean(data);

    double sum = 0;
    for (int i = 0; i < data.size(); i++)
        sum += pow(data[i] - m, 2);
    return sum / (data.size() - 1);
}

static QList<double> inv;

QList<double> &Statistics::invert(const QList<double>& data) {
//    QList<double> inv;
    double x = 1;
    for (int i = 0; i < data.count(); i++) {
        x = data.at(i);
        inv.append(1.0 / x);
    }
//    for (QList<double>::const_iterator it = data.begin(); it != data.end(); it++ ) {
//        double x = static_cast<double>( *it );
//        inv.push_back( 1.0 / x );
//    }
    return inv;
}

double Statistics::sum(const QList<double> &data ) {
    double s = 0;
    for (int i = 0; i < data.count(); i++) {//vector<double>::const_iterator it = data.begin(); it != data.end(); it++ ) {
        s += data.at(i);
//        s += static_cast<double>( *it );
    }
    return s;
}

double Statistics::hvar( const QList<double>& data ) {
    if ( data.size() < 2 )
        return 0;

    QList<double> inv = invert( data );
    double v1 = Statistics::var( inv );
    int n = data.size();
    v1 /= n;

    double s = sum( inv );
    s /= n;

    double var = v1 / pow( s, 4 );
    return var;
}


double Statistics::se(const QList<double> &data ) {
    return sqrt( var( data ) );
}

