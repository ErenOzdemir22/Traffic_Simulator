/*
 * Parken.h
 *
 *  Created on: 2 Dec 2025
 *      Author: 90530
 */

#ifndef PARKEN_H_
#define PARKEN_H_

#include "Verhalten.h"

class Parken: public Verhalten {
public:

	Parken(Weg& w1, double StartZeit);
	double dStrecke(Fahrzeug& fhrzg,double Zeitinterval) override;
	virtual ~Parken();

protected:
	double p_dStartZeit;
};

#endif /* PARKEN_H_ */
