/*
 * Simulation.h
 *
 *  Created on: Jan 25, 2026
 *      Author: kutay
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stdexcept>
#include <memory>


class Kreuzung;
class Simulationsobjekt;

class Simulation {
public:
	Simulation();
	virtual ~Simulation();
	void vEinlesen(std::istream& is,bool bMitGrafik = false);
	void vSimulieren(double dDauer, double dZeitschritt);

private:
	std::map<std::string, std::shared_ptr<Kreuzung>> p_mKreuzungen;//red black tree
};

#endif /* SIMULATION_H_ */
