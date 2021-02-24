#ifndef Statistics_h
#define Statistics_h

//#include <vector>
#include <QList>

class Statistics {
    public:
        static double amean(const QList<double> &data );
        static double hmean( const QList<double>& data );
        static double var(const QList<double> &data );
        static double se( const QList<double>& data );
        static double hvar(const QList<double> &data );
        static double sum( const QList<double>& data );
        static QList<double> &invert(const QList<double> &data );
};

#endif // Statistics_h






