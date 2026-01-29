#include "Fahrzeug.h"
#include "PKW.h"
#include "Verhalten.h"
#include "Streckende.h"

Verhalten::Verhalten(Weg& w1): p_Weg(w1){

}

Verhalten::~Verhalten() {

}

double Verhalten::dStrecke(Fahrzeug& fhrzg, double Zeitintervall)
{

	bool flag = true;
	if(p_Weg.getUeberholverbot()!=1){flag = false;}
	vertagt::VListe<std::unique_ptr<Fahrzeug>>* liste = p_Weg.getpFahrzeuge();
    auto it = liste->begin();

    //std::cout << (*it)->getName() << std::endl;

    // Find vehicle by ID
    while (it != liste->end())
    {
    	if ((*it)->getID() == fhrzg.getID())
            break;
        ++it;
    }


    if (it != liste->begin())
    {
    	auto itVorne = std::prev(it);//önde benzin olmayan araba var mı diye bak
    	while((*itVorne)->getTankeninhalt() == 0 && itVorne != liste->begin()){
    		itVorne = std::prev(itVorne);
    	}
    	if((*itVorne)->getTankeninhalt() == 0 || (*itVorne)->getAbschnittStrecke() == 0){
    		flag = false;
    	}


        if (flag && fhrzg.dGeschwindigkeit() * Zeitintervall >= itVorne->get()->getAbschnittStrecke()-fhrzg.getAbschnittStrecke())
        {
            return itVorne->get()->getAbschnittStrecke()-fhrzg.getAbschnittStrecke();
        }
    }

    if (fhrzg.dGeschwindigkeit() * Zeitintervall
        < p_Weg.getLaenge() - fhrzg.getAbschnittStrecke())
    {
        return fhrzg.dGeschwindigkeit() * Zeitintervall;
    }
    else
    {
        throw Streckenende(p_Weg, fhrzg);
    }
}


Weg& Verhalten::getWeg(){

	return p_Weg;


}
