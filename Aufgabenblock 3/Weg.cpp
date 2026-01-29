
#include "Weg.h"
#include "Fahrzeug.h"
#include "Fahrausnahme.h"
#include "Kreuzung.h"

Weg::Weg():Simulationsobjekt() {

}
Weg::Weg(std::string sName, double dLaenge, Tempolimit Tempolimit, bool bUeberholverbot, std::shared_ptr<Kreuzung> ziel):Simulationsobjekt(sName), p_dLaenge(dLaenge), p_dTempolimit(Tempolimit), p_bUeberholverbot(bUeberholverbot),p_pZielkreuzung(ziel){

}

Weg::~Weg() {

}

void Weg::vSimulieren(){

	p_pFahrzeuge.vAktualisieren();

	for(auto& ptr : p_pFahrzeuge){//for each iteration

		try{
				ptr->vSimulieren();
			}
		catch(Fahrausnahme& ausnahme){
			ausnahme.vBearbeiten();  //duruma göre listeden çıkarılır ya da hareket halinde eklenir

		}


	}
	p_pFahrzeuge.vAktualisieren();

}
void Weg::vSimulieren(double dTakt){

	p_pFahrzeuge.vAktualisieren();

	for(auto& ptr : p_pFahrzeuge){//for each iteration

		try{
				ptr->vSimulieren(dTakt);
			}
		catch(Fahrausnahme& ausnahme){
			ausnahme.vBearbeiten();  //duruma göre listeden çıkarılır ya da hareket halinde eklenir

		}


	}
	p_pFahrzeuge.vAktualisieren();

}

void Weg::vAusgeben(std::ostream& os){ //bunu önceki aufgabelerde kullandık

	Simulationsobjekt::vAusgeben(os);
	for(auto& ptr : p_pFahrzeuge){

	    os<<std::endl<<*ptr<<"  ";
	}
}


double Weg::getTempolimit(){

	return double(p_dTempolimit);

}

void Weg::vKopf(){
	std::cout<< std::left
			         <<std::setw(10)  << "ID"
			         << std::setw(10) << "Name"
					 <<std::setw(10)  << "Laenge"
					 << std::setw(10) << "Fahrzeuge";
}


double Weg::getLaenge(){

	return p_dLaenge;


}

bool Weg::getUeberholverbot() const {
	return p_bUeberholverbot;
}


void Weg::vAnnahme(std::unique_ptr<Fahrzeug> ptr){  //fahren  //fonksiyon overload
	ptr->vNeueStrecke(*this);
	p_pFahrzeuge.push_back(std::move(ptr));
}


void Weg::vAnnahme(std::unique_ptr<Fahrzeug> ptr,double dStartZeit){  //parken //fonksiyonlar da constructor lar gibi aynı isimde ayrı parametreli olabilirler
	ptr->vNeueStrecke(*this,dStartZeit);
	p_pFahrzeuge.push_front(std::move(ptr));

}



std::string Weg::getName(){
	return p_sName;
}

vertagt::VListe<std::unique_ptr<Fahrzeug>>* Weg::getpFahrzeuge()
{
    return &p_pFahrzeuge;
}


std::unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& fobj){

	std::unique_ptr<Fahrzeug> temp;
	for(std::list<std::unique_ptr<Fahrzeug>>::iterator i= p_pFahrzeuge.begin(); i!= p_pFahrzeuge.end()  ;i++){
	     if(**i == fobj){

	    temp = std::move(*i);
	    *i = std::make_unique<Fahrzeug>();

	    p_pFahrzeuge.erase(i); //pointer ın işaret ettiği liste elemanını siler
	   }
	}

	      return temp;
}
















