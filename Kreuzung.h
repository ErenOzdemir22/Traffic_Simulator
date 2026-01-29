/*
 * Kreuzung.h
 *
 *  Created on: Jan 21, 2026
 *      Author: kutay
 */

#ifndef KREUZUNG_H_
#define KREUZUNG_H_
#include <list>
#include "Simulationsobjekt.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include <vector>
#include <iostream>
#include "random"

class Kreuzung: public Simulationsobjekt {
public:
	Kreuzung();
	Kreuzung(double dTankstelle);
	virtual ~Kreuzung();

	void vEinlesen(std::istream& is) override;

	void vTanken(Fahrzeug&);
	void vAnnahme(std::unique_ptr<Fahrzeug> f1);
	void vAnnahme(std::unique_ptr<Fahrzeug> f1,double dStartZeit);
	void vAnnahme(Weg& w,std::unique_ptr<Fahrzeug>);
	void vAnnahme(Weg& w,std::unique_ptr<Fahrzeug>,double dStartZeit);
	static void vVerbinde(std::string sNameweg1,std::string sNameweg2,double dWeglaenge,std::weak_ptr<Kreuzung> k1, std::weak_ptr<Kreuzung> k2, Tempolimit Tempolimit, bool bUeberholverbot);
	void vSimulieren();
	void vSimulieren(double dTakt);
	std::shared_ptr<Weg> pZufaelligerWeg(Weg&);


protected:
	double p_dTankstelle;
	std::list<std::shared_ptr<Weg>> p_pWege;

};

#endif /* KREUZUNG_H_ */
