
#ifndef SIMULATIONSOBJEKT_H_
#define SIMULATIONSOBJEKT_H_
#include <string>
#include <iostream>
#include <iomanip>
#include <limits>
#include <iostream>
extern double dGlobaleZeit;

class Simulationsobjekt{
public:
	Simulationsobjekt();
	Simulationsobjekt(std::string sName);
	virtual void vAusgeben(std::ostream& os);//bu fonksiyonu 0 a eşitleyerek pure virtual bir fonksiyon yaptık ve class ın kendi objesi olmayacağı için abstrakt class.
	virtual void vEinlesen(std::istream& is);
	virtual void vSimulieren()=0;
	virtual ~Simulationsobjekt();
  	Simulationsobjekt(const Simulationsobjekt& other)=delete;//copy constructor
  	int getID(){return p_iID;}
  	virtual std::string getName(){return p_sName;}
protected:
	std::string p_sName;
	int const p_iID;
	double p_dZeit;
	static int g_iID;
};




std::ostream& operator<<(std::ostream& os, Simulationsobjekt& sobj);
std::istream& operator>>(std::istream& is, Simulationsobjekt& sobj);






#endif



















