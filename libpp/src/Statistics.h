#ifndef Statistics_h
#define Statistics_h

#include <vector>

class Statistics {
    public:
        static double amean( const std::vector<double>& data );
        static double hmean( const std::vector<double>& data );
        static double var( const std::vector<double>& data );
        static double se( const std::vector<double>& data );
        static double hvar( const std::vector<double>& data );
        static double sum( const std::vector<double>& data );
		static std::vector<double> invert( const std::vector<double>& data );
};

#endif // Statistics_h






