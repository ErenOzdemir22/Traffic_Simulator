         /*
 * PKW.cpp
 *
 *  Created on: 29 Nov 2025
 *      Author: 90530
 */

#include "PKW.h"

PKW::PKW():Fahrzeug(),p_dTankvolumen(60),p_dVerbrauch(10),p_dTankinhalt(30) {



}

PKW::PKW(std::string sName, double dMaxGeschwindigkeit,double dVerbrauch ,double dTankvolumen ):Fahrzeug(sName,dMaxGeschwindigkeit), p_dTankvolumen(dTankvolumen),p_dTankinhalt(dTankvolumen/2) ,p_dVerbrauch(dVerbrauch)
{

}

PKW::~PKW() {


}

double PKW::dTanken(double dMenge){

	if(dMenge<p_dTankvolumen-p_dTankinhalt){
	p_dTankinhalt+= dMenge;
	return dMenge;
  }
	else{
		p_dTankinhalt=p_dTankvolumen;
    return p_dTankvolumen-p_dTankinhalt;
	}
}

void  PKW::vSimulieren(){
	if(dGeschwindigkeit()* (0.5) *p_dVerbrauch/100<p_dTankinhalt ){

		Fahrzeug::vSimulieren();
        p_dTankinhalt-=p_dMaxGeschwindigkeit* (0.5) *p_dVerbrauch/100;
	}
	else{
		p_dTankinhalt = 0;
	}

}
void  PKW::vSimulieren(double dTakt){
	if(dGeschwindigkeit()* (dTakt) *p_dVerbrauch/100<p_dTankinhalt ){

		Fahrzeug::vSimulieren(dTakt);
        p_dTankinhalt-=p_dMaxGeschwindigkeit* (dTakt) *p_dVerbrauch/100;
	}
	else{
		p_dTankinhalt = 0;
	}

}


void PKW::vAusgeben(std::ostream& os){

	    Fahrzeug::vAusgeben(os);
	    os << std::resetiosflags(std::ios::right)
	       << std::setiosflags(std::ios::left)
	       << std::setw(20) << p_dGesamtStrecke/100*p_dVerbrauch
	       << std::setw(20) << p_dTankinhalt;
}

void PKW::vKopf(){

	std::cout<< std::left
		         <<std::setw(10)  << "ID"
		         << std::setw(10) << "Name"
		         << std::setw(24) << "MaxGeschwindigkeit"
		         << std::setw(10) << "Gesamtstrecke";
	std::cout<<std::left << std::setw(10)<<"GesamtVerbrauch: "
							 << std::setw(10)<<"p_dTankinhalt"
							 <<std::endl;
	std::cout << std::string(57, '-') << std::endl;



}

void PKW::vZeichnen(){

	bZeichnePKW(p_sName,p_pVerhalten->getWeg().getName(),p_dAbschnittStrecke/p_pVerhalten->getWeg().getLaenge(),dGeschwindigkeit(),p_dTankinhalt);


}

void PKW::vEinlesen(std::istream& is) {
    Fahrzeug::vEinlesen(is);
    is >> p_dVerbrauch >> p_dTankvolumen;
}

std::istream& operator>>(std::istream& is, PKW& sobj) {
    sobj.vEinlesen(is);
    return is;
}









