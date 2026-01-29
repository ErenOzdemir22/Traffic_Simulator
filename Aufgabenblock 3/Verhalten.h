
#ifndef VERHALTEN_H_
#define VERHALTEN_H_
#include "Weg.h"
class Fahrzeug;
class PKW;
class Verhalten {
public:

	Verhalten(Weg& w1);
	virtual ~Verhalten()=0;
	virtual double dStrecke(Fahrzeug& fhrzg,double Zeitinterval);
	Weg& getWeg();
protected:
	Weg& p_Weg;

};

#endif
