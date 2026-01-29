/*
 * Weg.h
 *
 *  Created on: 30 Nov 2025
 *      Author: 90530
 */

#ifndef WEG_H_
#define WEG_H_
#include <list>
#include "Simulationsobjekt.h"
#include<memory>
#include "Tempolimit.h"
#include "vertagt_liste.h"
class Fahrzeug;//forward deklaration
class Kreuzung;
class Weg: public Simulationsobjekt {
public:
	Weg();
	Weg(std::string sName, double dLaenge, Tempolimit Tempolimit, bool bUeberholverbot = true,std::shared_ptr<Kreuzung> ziel = nullptr);
	virtual ~Weg();
	void vAusgeben(std::ostream& os) override;
	//void vEinlesen(std::istream& is) override{return;}
    void vSimulieren() override;
    void vSimulieren(double dTakt);

    double getTempolimit();
    double getLaenge();
    std::string getName();
    bool getUeberholverbot() const;
    vertagt::VListe<std::unique_ptr<Fahrzeug>>* getpFahrzeuge();
    std::weak_ptr<Kreuzung> getZielkreuzung() const{return p_pZielkreuzung;}
    std::weak_ptr<Weg> getRueckweg() const{return p_pRueckweg;}
    void setRueckweg(std::weak_ptr<Weg> pRueckweg){p_pRueckweg = pRueckweg;}


    void static vKopf();
    void vAnnahme(std::unique_ptr<Fahrzeug>);//fahren
    void vAnnahme(std::unique_ptr<Fahrzeug>, double dStartZeit);//parken
    std::unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug&);


protected:
    double p_dLaenge;
    bool p_bUeberholverbot;
    Tempolimit p_dTempolimit;
    vertagt::VListe<std::unique_ptr<Fahrzeug>> p_pFahrzeuge; //Vliste yerine eskiden std::list yazıyordu
    std::weak_ptr<Kreuzung> p_pZielkreuzung;
    std::weak_ptr<Weg> p_pRueckweg;




};

#endif


