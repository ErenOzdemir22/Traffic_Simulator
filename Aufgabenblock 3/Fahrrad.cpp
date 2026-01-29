
#include "Fahrrad.h"
#include "cmath"
Fahrrad::Fahrrad():Fahrzeug() {


}
Fahrrad::Fahrrad(std::string sName,double dGeschwindigkeit):Fahrzeug(sName,dGeschwindigkeit){

	}
Fahrrad::~Fahrrad() {

}


double Fahrrad::dGeschwindigkeit(){

double temp = p_dMaxGeschwindigkeit*pow(0.9,(p_dGesamtStrecke/20));

	return temp<12 ? 12 : temp; //en son azalmış hızları 12 olabiliyor

}

void Fahrrad::vZeichnen() {

	bZeichneFahrrad(p_sName, p_pVerhalten->getWeg().getName(), p_dAbschnittStrecke/p_pVerhalten->getWeg().getLaenge(), dGeschwindigkeit());

}

void Fahrrad::vEinlesen(std::istream& is) {
     Fahrzeug::vEinlesen(is);

 }






























