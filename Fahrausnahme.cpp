#include "Fahrausnahme.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include "Kreuzung.h"

Fahrausnahme::Fahrausnahme(Weg& w, Fahrzeug& f): p_rF(f), p_rW(w){


}

Fahrausnahme::~Fahrausnahme() {
	// TODO Auto-generated destructor stub
}

