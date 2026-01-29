#include "Streckende.h"
#include "Fahrzeug.h"
#include "Kreuzung.h"


Streckenende::Streckenende(Weg& w,Fahrzeug& f):Fahrausnahme(w,f){

}

Streckenende::~Streckenende() {
	// TODO Auto-generated destructor stub
}


void Streckenende::vBearbeiten(){



	std::unique_ptr<Fahrzeug> temp = p_rW.pAbgabe(p_rF);  //yolun sonuna gelen araç listeden silinir, template klass larla
	auto kruzungPtr = p_rW.getZielkreuzung().lock();
	if (kruzungPtr) {
	    kruzungPtr->vAnnahme(p_rW, std::move(temp));
	} else {
	    // Hedef kavşak artık mevcut değil, hata yönetimi yapılmalı
	}




}
