#ifndef FAHRAUSNAHME_H_
#define FAHRAUSNAHME_H_
class Fahrzeug;
class Weg;
class Kreuzung;
#include <iostream>
#include <exception>

class Fahrausnahme: public std::exception {
public:

	Fahrausnahme(Weg& w, Fahrzeug& f);
	virtual ~Fahrausnahme();
	virtual void vBearbeiten()=0;
protected:
	Fahrzeug& p_rF;
	Weg& p_rW;
};


#endif /* FAHRAUSNAHME_H_ */
