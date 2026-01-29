#include "Losfahren.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include "Kreuzung.h"

Losfahren::Losfahren(Weg& w ,Fahrzeug& f): Fahrausnahme(w,f){

}

Losfahren::~Losfahren() {
	// TODO Auto-generated destructor stub
}

void Losfahren::vBearbeiten(){
	auto ptr1 = p_rW.getRueckweg().lock()->getZielkreuzung().lock();
	std::unique_ptr<Fahrzeug> temp = p_rW.pAbgabe(p_rF); // park eden araçlar listenin sonunda olduğu için önce listeden çıkartıyoruz
	ptr1->vAnnahme(p_rW,std::move(temp)); // Annahme içinde unique pointer olduğu için temp pointerını siliyoruz ve listenin başına ekliyoruz

	std::cout<<"Los fahren!";
}
