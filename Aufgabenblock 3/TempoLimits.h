/*
 * TempoLimits.h
 *
 *  Created on: Nov 15, 2025
 *      Author: kutay
 */

#ifndef TEMPOLIMITS_H_
#define TEMPOLIMITS_H_
#include<limits>

enum Tempolimit{
		Innerorts = 50,
		Landstrasse = 100,
		Autobahn = std::numeric_limits<int>::max()
	};



#endif /* TEMPOLIMITS_H_ */
