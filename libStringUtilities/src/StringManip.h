#ifndef StringManip_H
#define StringManip_H

// define some methods for string manipulation

#include <string>
#include <sstream>
#include <iomanip>

namespace cbr
{

	enum StripType { leading, trailing, both };
	std::string strip(const std::string& str, StripType type = both);

	template <class T>
	std::string toString (const T& value, int w = -1, char fill = ' ')  
	{
		std::ostringstream os;
		os << std::fixed; 
		os.precision(15);

		if (w > 0) {
			os.width (w);
			os.fill (fill);
		}

		os << value;
		std::string result (os.str());

		return (result);
	}


	template <class T> 
	T fromString (const std::string &str)
	{
		std::istringstream is (str);
		T result;
		is >> result;
		return (result);
	}

}



#endif
