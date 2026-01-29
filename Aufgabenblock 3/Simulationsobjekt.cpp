/*
 * Simulationsobjekt.cpp
 *
 *  Created on: 30 Nov 2025
 *      Author: 90530
 */

#include "Simulationsobjekt.h"
double dGlobaleZeit = 0.0;
int Simulationsobjekt::g_iID = 1;
Simulationsobjekt::Simulationsobjekt(): p_sName(""), p_iID(g_iID), p_dZeit(dGlobaleZeit) {
  g_iID++;

}
Simulationsobjekt::Simulationsobjekt(std::string sName): p_sName(sName), p_iID(g_iID), p_dZeit(dGlobaleZeit) {// : sonrarsı initialitionslist
  g_iID++;

  std::cout<<"ID:  "<<p_iID<<std::endl;

}

Simulationsobjekt::~Simulationsobjekt() {

}


void Simulationsobjekt::vAusgeben(std::ostream& os){
	os << std::setiosflags(std::ios::left)
		   << std::setw(4) << p_iID
		   << std::setw(18) << p_sName;


}
std::ostream& operator<<(std::ostream& os, Simulationsobjekt& sobj){

	sobj.vAusgeben(os);

}


void Simulationsobjekt::vEinlesen(std::istream& is) {
    if (p_sName != "") {
        throw std::runtime_error("error p_sName != 0");
    }
    is >> p_sName;
}

std::istream& operator>>(std::istream& is, Simulationsobjekt& sobj) {
    sobj.vEinlesen(is);
    return is;
}
















