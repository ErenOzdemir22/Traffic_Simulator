/*
 * Fahrrad.h
 *
 *  Created on: 29 Nov 2025
 *      Author: 90530
 */

#ifndef FAHRRAD_H_
#define FAHRRAD_H_

#include "Fahrzeug.h"

class Fahrrad: public Fahrzeug {
public:
	Fahrrad();
	Fahrrad(std::string sName,double dGeschwindigkeit);
    void vEinlesen(std::istream& is) override;
	virtual ~Fahrrad();
	double dGeschwindigkeit()override ;
	void vZeichnen() override;
};

#endif /* FAHRRAD_H_ */
