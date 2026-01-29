#ifndef STRECKENENDE_H_
#define STRECKENENDE_H_

#include "Fahrausnahme.h"
class Weg;
class Fahrzeug;
class Kreuzung;

class Streckenende: public Fahrausnahme {
public:

	Streckenende(Weg& w,Fahrzeug& f);
	virtual ~Streckenende();
	void vBearbeiten() override;
};

#endif /* STRECKENENDE_H_ */
