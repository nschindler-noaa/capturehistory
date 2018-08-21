/*
*/

#ifndef RiverKm_h
#define RiverKm_h

#include <string>
#include <iostream>

namespace cbr {
	class RiverKm 
	{
	public:
		RiverKm() : data("") {}
		RiverKm( const std::string& riverk ) : data(riverk) {}
		RiverKm( const char* riverk );
		void setRiverKm( const std::string& riverk ) { data = riverk; }
		void setRiverKm( const char* riverk);
		int total() const;
		bool isValid() const;
		bool isColocated(const RiverKm& target) const;
		bool isUpstream(const RiverKm& target) const;
		bool isDownstream(const RiverKm& target) const;
		std::string toString() const { return data; }

		friend std::ostream& operator<<(std::ostream& os, const RiverKm& rkm) {
			os << rkm.data;
			return os;
		}
	private:
		std::string data;
	};
}

#endif
