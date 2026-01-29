/*
 * Kreuzung.cpp
 *
 *  Created on: Jan 21, 2026
 *      Author: kutay
 */

#include "Kreuzung.h"


Kreuzung::Kreuzung(): Simulationsobjekt(){}

Kreuzung::Kreuzung(double dTankstelle):Simulationsobjekt(), p_dTankstelle(dTankstelle) {
	// TODO Auto-generated constructor stub

}

Kreuzung::~Kreuzung() {
	// TODO Auto-generated destructor stub
}

void Kreuzung::vVerbinde(std::string sNameweg1,std::string sNameweg2,double dWeglaenge,std::weak_ptr<Kreuzung> k1, std::weak_ptr<Kreuzung> k2, Tempolimit Tempolimit, bool bUeberholverbot){

	std::shared_ptr<Kreuzung> k1s = k1.lock();
	std::shared_ptr<Kreuzung> k2s = k2.lock();

	auto p1 = std::make_shared<Weg>(sNameweg1,dWeglaenge,Tempolimit,bUeberholverbot,k2s);
	auto p2 = std::make_shared<Weg>(sNameweg2,dWeglaenge,Tempolimit,bUeberholverbot,k1s);
	p1->setRueckweg(p2);
	p2->setRueckweg(p1);
	k2s->p_pWege.push_front(p2);
	k1s->p_pWege.push_front(p1);
}
void Kreuzung::vTanken(Fahrzeug& f1){
	if(p_dTankstelle > 0){
		p_dTankstelle -= f1.dTanken();
	}
}
void Kreuzung::vAnnahme(Weg& w,std::unique_ptr<Fahrzeug> f1){
	if (p_pWege.empty()) {
	        throw std::runtime_error("Kreuzung has no roads");
	    }
	vTanken(*f1);
	auto temp = pZufaelligerWeg(w);
	std::cout<<"Zeit    :   "<<dGlobaleZeit<<std::endl
		     <<"Wechsel :   "<<w.getName()<< " --> "<<temp->getName()<<std::endl
			 <<"Fahrzeug:   "<<f1->getName()<<std::endl;
	temp->vAnnahme(std::move(f1));

}
void Kreuzung::vAnnahme(Weg& w,std::unique_ptr<Fahrzeug> f1, double dStartZeit){
	if (p_pWege.empty()) {
	        throw std::runtime_error("Kreuzung has no roads");
	    }
	vTanken(*f1);
	auto temp = pZufaelligerWeg(w);
	std::cout<<"Zeit    :   "<<dGlobaleZeit<<std::endl
			     <<"Wechsel :   "<<w.getName()<< " --> "<<w.getRueckweg().lock()->getName()<<std::endl
				 <<"Fahrzeug:   "<<f1->getName()<<std::endl;
	temp->vAnnahme(std::move(f1));
}
void Kreuzung::vAnnahme(std::unique_ptr<Fahrzeug> f1){
	vTanken(*f1);
	if (p_pWege.empty()) {
	        throw std::runtime_error("Kreuzung has no roads");
	    }
	p_pWege.front()->vAnnahme(std::move(f1));

}
void Kreuzung::vAnnahme(std::unique_ptr<Fahrzeug> f1,double dStartZeit){
	vTanken(*f1);
	if (p_pWege.empty()) {
	        throw std::runtime_error("Kreuzung has no roads");
	    }
	p_pWege.front()->vAnnahme(std::move(f1),dStartZeit);

}


void Kreuzung::vSimulieren(){
	for(auto it : p_pWege){
		it->vSimulieren();
	}
}
void Kreuzung::vSimulieren(double dTakt){
	for(auto it : p_pWege){
		it->vSimulieren(dTakt);
	}
}
std::shared_ptr<Weg> Kreuzung::pZufaelligerWeg(Weg& w){
	if(p_pWege.size() == 1){
		return p_pWege.front();
	}
	std::vector<std::shared_ptr<Weg>> Wegvector;

	for(auto it : p_pWege){
		if(it != w.getRueckweg().lock()){
			Wegvector.push_back(it);
		}
	}

	static std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<size_t> dist(0, Wegvector.size() - 1);

	return Wegvector[dist(rng)];


}

void Kreuzung::vEinlesen(std::istream& is) {
    Simulationsobjekt::vEinlesen(is);

    is >> p_dTankstelle;
}
