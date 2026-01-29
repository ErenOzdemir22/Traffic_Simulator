/*
 * Fahrzeug.cpp
 *
 *  Created on: 25 Nov 2025
 *      Author: 90530
 */

#include "Fahrzeug.h"


Fahrzeug::Fahrzeug(std::string sName): Simulationsobjekt(sName), p_dGesamtStrecke(0), p_dGesamtZeit(0),p_dAbschnittStrecke(0)//initialisation list
{

     // std::cout<<"Object mit dem ID "<< p_iID <<"konstruktiert."<<std::endl;


}

Fahrzeug::Fahrzeug() : Simulationsobjekt(), p_dGesamtStrecke(0), p_dGesamtZeit(0), p_dAbschnittStrecke(0){



}

Fahrzeug::Fahrzeug(std::string sName,double dMaxGeschwindigkeit): Simulationsobjekt(sName), p_dMaxGeschwindigkeit(dMaxGeschwindigkeit>0 ? dMaxGeschwindigkeit : 0),p_dGesamtStrecke(0), p_dGesamtZeit(0),p_dAbschnittStrecke(0)
{

      //std::cout<<"Object mit dem ID "<< p_iID <<"konstruktiert."<<std::endl;
}

Fahrzeug::~Fahrzeug() {
	 //std::cout<<"Object mit dem ID "<< p_iID <<" gelöscht."<<std::endl;
}


/*void Fahrzeug::vKopf(){
	 std::cout<< std::left
	         <<std::setw(10)  << "ID"
	         << std::setw(10) << "Name"
	         << std::setw(24) << "MaxGeschwindigkeit"
	         << std::setw(10) << "Gesamtstrecke";


};*/


void Fahrzeug::vAusgeben(std::ostream& os){

	Simulationsobjekt::vAusgeben(os);
		os << std::fixed << std::setprecision(2)
		   << std::setw(20) << p_dMaxGeschwindigkeit
		   << std::setw(20) << p_dGesamtStrecke;
}

void Fahrzeug::vSimulieren(){

	if(p_dZeit<dGlobaleZeit){


		p_dGesamtZeit+= 0.5;
		p_dGesamtStrecke+= p_pVerhalten->dStrecke(*this,0.5);
		p_dAbschnittStrecke+= p_pVerhalten->dStrecke(*this,0.5);
		p_dZeit+=0.5;
		vZeichnen();
}
}
void Fahrzeug::vSimulieren(double dTakt){

		if(p_dZeit<dGlobaleZeit){


			p_dGesamtZeit+= dTakt;
			p_dGesamtStrecke+= p_pVerhalten->dStrecke(*this,dTakt);
			p_dAbschnittStrecke+= p_pVerhalten->dStrecke(*this,dTakt);
			p_dZeit+=dTakt;
			vZeichnen();
	}

}

double Fahrzeug::dTanken(double dMenge){

	return -1;

}



double Fahrzeug::dGeschwindigkeit(){
	if(p_dMaxGeschwindigkeit<p_pVerhalten->getWeg().getTempolimit()){
	return p_dMaxGeschwindigkeit;
	}
	else{
		return p_pVerhalten->getWeg().getTempolimit();
	}

}


std::ostream& operator<<(std::ostream& os, Fahrzeug& fhrzg){

	fhrzg.vAusgeben(os);
	return os;
}


bool Fahrzeug::operator<(Fahrzeug& fhrzg1){

	return p_iID < fhrzg1.p_iID;            ////f1<f2    f1(f2)   sağdaki operatörün sağına yazılır
}

void Fahrzeug::operator=(Fahrzeug& fhrzg1){

	p_sName=fhrzg1.p_sName;

	//p_iID=fhrzg1.p_iID;
	p_dMaxGeschwindigkeit=fhrzg1.p_dMaxGeschwindigkeit;
	p_dGesamtStrecke=fhrzg1.p_dGesamtStrecke;
	p_dGesamtZeit=fhrzg1.p_dGesamtZeit;
	p_dZeit=fhrzg1.p_dZeit;

}

bool Fahrzeug::operator==(const Fahrzeug& fhrzg){

	if(p_iID == fhrzg.p_iID){

		return true;

	}

	else{

		return false;
	}

}

double Fahrzeug::getAbschnittStrecke(){

	return p_dAbschnittStrecke;

}

void Fahrzeug::vNeueStrecke(Weg& w1){


	p_pVerhalten = std::make_unique<Fahren>(w1);   //yeni yola girerken
	p_dAbschnittStrecke=0;

}


void Fahrzeug::vNeueStrecke(Weg& w1, double StartZeit){


	p_pVerhalten = std::make_unique<Parken>(w1,StartZeit);
	p_dAbschnittStrecke=0;
}


void Fahrzeug::vZeichnen(){
	return;
}

void Fahrzeug::vEinlesen(std::istream& is) {

    Simulationsobjekt::vEinlesen(is);

    is >> p_dMaxGeschwindigkeit;
}


















