
#ifndef TEMPOLIMIT_H_
#define TEMPOLIMIT_H_
#include <limits>
enum class Tempolimit{
	Innerorts=50,
	Landstraße=100,
	Autobahn= std::numeric_limits<int>::max() //2^31-1
};




#endif
