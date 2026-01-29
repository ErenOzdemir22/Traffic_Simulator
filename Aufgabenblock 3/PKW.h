/*
 * PKW.h
 *
 *  Created on: 29 Nov 2025
 *      Author: 90530
 */

#ifndef PKW_H_
#define PKW_H_

#include "Fahrzeug.h"

class PKW: public Fahrzeug {
public:
	PKW();
	PKW(std::string sName, double dMaxGeschwindigkeit,double dVerbrauch ,double dTankvolumen = 55);//benzin deposu default parameter, çağırılırken değer girilmezse oto olark 55 olur
	double dTanken(double dMenge = std::numeric_limits<double>::infinity()) override;
	void vSimulieren() override;
	void vSimulieren(double dTakt) override;
	void vAusgeben(std::ostream& os) override;
    void vEinlesen(std::istream& is) override;
	static void vKopf();
	virtual ~PKW();
	void vZeichnen() override;
	double getTankeninhalt() override {return p_dTankinhalt;}
	double getTankverbrauch() override {return p_dVerbrauch;}


protected:
	double p_dVerbrauch;
	double p_dTankvolumen;
	double p_dTankinhalt;

};
std::istream& operator>>(std::istream& is, PKW& sobj);

#endif /* PKW_H_ */
