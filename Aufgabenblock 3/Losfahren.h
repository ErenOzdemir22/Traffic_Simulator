#ifndef LOSFAHREN_H_
#define LOSFAHREN_H_
#include "Fahrausnahme.h"
class Kreuzung;

class Losfahren: public Fahrausnahme {
public:

	Losfahren(Weg& w,Fahrzeug& f);
	virtual ~Losfahren();
	void vBearbeiten() override;
};

#endif /* LOSFAHREN_H_ */
