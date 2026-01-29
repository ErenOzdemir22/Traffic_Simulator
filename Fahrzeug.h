#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_
#include <string>
#include <iostream>
#include <iomanip>
#include <limits>
#include <iostream>
#include "Simulationsobjekt.h"//kendimiz yazdığımız için ".." kullanırız
#include "Verhalten.h"
#include "Fahren.h"
#include "Parken.h"
#include "SimuClientSocket.h"
#include "SimuClient.h"

class Fahrzeug: public Simulationsobjekt {

public:
	Fahrzeug(std::string sName);//konst. farklı parametreler giriliyosa buna overload denir
	Fahrzeug();
	Fahrzeug(const Fahrzeug& other) = delete;//copy constructer yasaklandı
    Fahrzeug(std::string sName, double dMaxGeschwindigkeit);
	virtual ~Fahrzeug();
	//virtual static void vKopf();
	virtual void vAusgeben(std::ostream& os) override;
	virtual void vEinlesen(std::istream& is) override;
	virtual void vSimulieren() override;
	virtual void vSimulieren(double dTakt);
    virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity());
    virtual double dGeschwindigkeit();
    bool operator<(Fahrzeug& fhrzg1);
    void operator=(Fahrzeug& fhrzg1);
    bool operator==(const Fahrzeug& other);
    double getAbschnittStrecke();
    virtual double getTankeninhalt(){return std::numeric_limits<double>::infinity();}
    virtual double getTankverbrauch()  {return 1;}
    std::string getName() {return p_sName;}
    void vNeueStrecke(Weg&);
    void vNeueStrecke(Weg&, double StartZeit);
    virtual void vZeichnen();
protected:
double p_dMaxGeschwindigkeit;
double p_dGesamtStrecke;
double p_dGesamtZeit;
double p_dAbschnittStrecke = 0;
std::unique_ptr<Verhalten> p_pVerhalten;//template class

};

std::ostream& operator<<(std::ostream& os, Fahrzeug& fhrzg);






#endif

















