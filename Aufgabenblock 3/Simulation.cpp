/*
 * Simulation.cpp
 *
 *  Created on: Jan 25, 2026
 *      Author: kutay
 */
#include <memory>
#include "Simulation.h"
#include "Kreuzung.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "Weg.h"
#include "Simulationsobjekt.h"

Simulation::Simulation() {
	// TODO Auto-generated constructor stub

}

Simulation::~Simulation() {
	// TODO Auto-generated destructor stub
}

void Simulation::vEinlesen(std::istream& is,bool bMitGrafik) {
    std::string sKeyword;
    int iZeile = 0; // Line counter
    if(bMitGrafik){bInitialisiereGrafik(1000,1000);}
    dGlobaleZeit = 0.0;


    try {
        while (is >> sKeyword) {
            iZeile++;

            if (sKeyword == "KREUZUNG") {
            	std::shared_ptr<Kreuzung> spKr = std::make_shared<Kreuzung>();
            	std::weak_ptr<Kreuzung> wpKr = spKr;
                is >> *wpKr.lock();
                if(bMitGrafik){
                	double posx;
                	double posy;
                	is>>posx>>posy;
                	bZeichneKreuzung(posx,posy);
                }

                // Store in map: Key = Name, Value = Pointer
                std::string name = spKr->getName();

                if (p_mKreuzungen.find(name) != p_mKreuzungen.end()) {
                    throw std::runtime_error("Kreuzung already exists: " + name);
                }

                p_mKreuzungen[name] = spKr;

            }
            else if (sKeyword == "PKW") {

            	std::string sName;
            	double Geschwindigkeit;
            	double Verbrauch;
            	double Tankvolumen;
            	std::string sNameS;
            	double dStartZeit;


            	is >>sName>>Geschwindigkeit>>Verbrauch>>Tankvolumen>>sNameS>> dStartZeit;

                std::unique_ptr<Fahrzeug> pPkw = std::make_unique<PKW>(sName,Geschwindigkeit,Verbrauch,Tankvolumen);





                // Find the start intersection
                if (p_mKreuzungen.find(sNameS) == p_mKreuzungen.end()) {
                    throw std::runtime_error("PKW Start intersection not found: " + sNameS);
                }






                //std::unique_ptr<Fahrzeug> pF = std::move(pPkw);


                p_mKreuzungen[sNameS]->vAnnahme(std::move(pPkw), dStartZeit);
            }
            else if (sKeyword == "FAHRRAD") {
                // Same logic as PKW
            	std::unique_ptr<Fahrrad> pRad = std::make_unique<Fahrrad>();
                is >> *pRad;

                std::string sNameS;
                double dStartZeit;
                is >> sNameS >> dStartZeit;

                if (p_mKreuzungen.find(sNameS) == p_mKreuzungen.end()) {
                    throw std::runtime_error("Fahrrad Start intersection not found: " + sNameS);
                }
                //std::unique_ptr<Fahrzeug> pF = std::move(pRad);
                p_mKreuzungen[sNameS]->vAnnahme(std::move(pRad), dStartZeit);
            }
            else if (sKeyword == "STRASSE") {
                // STRASSE <NameQ> <NameZ> <NameW1> <NameW2> <Länge> <Tempolimit> <Überholverbot>
                std::string sNameQ, sNameZ, sNameW1, sNameW2;
                double dLaenge;
                int iTempolimitInt;
                bool bUeberholverbot;

                is >> sNameQ >> sNameZ >> sNameW1 >> sNameW2 >> dLaenge >> iTempolimitInt >> bUeberholverbot;

                if(bMitGrafik){
                	int anzahlk;
                	is >> anzahlk;
                	int koordinaten[99];
                	for(int i = 0; i<anzahlk*2; i++){
                		is >> koordinaten[i];
                	}
                	bZeichneStrasse(sNameW1,sNameW2,dLaenge,anzahlk,koordinaten);
                }

                // Validate Intersections exist
                if (p_mKreuzungen.find(sNameQ) == p_mKreuzungen.end() ||
                    p_mKreuzungen.find(sNameZ) == p_mKreuzungen.end()) {
                    throw std::runtime_error("Road connects unknown intersections: " + sNameQ + " -> " + sNameZ);
                }

                auto pKrQ = p_mKreuzungen[sNameQ];
                auto pKrZ = p_mKreuzungen[sNameZ];

                Tempolimit limit;
                if(iTempolimitInt == 3){
                	limit = Tempolimit::Innerorts;
                }
                else if(iTempolimitInt == 2){
                	limit = Tempolimit::Landstraße;
                }
                else{
                	limit = Tempolimit::Autobahn;
                }



                Kreuzung::vVerbinde(sNameW1,sNameW2,dLaenge,pKrQ,pKrZ,limit,bUeberholverbot);
            }
            else if(sKeyword == "END"){
            	std::cout<<"success reading the file!!";
            	return;
            }
            else {
                // Unknown keyword -> Throw error
                throw std::runtime_error("Unknown keyword: " + sKeyword);
            }
        }
    }
    catch (std::runtime_error& e) {
        std::cerr << "Error in line " << iZeile << ": " << e.what() << std::endl;
        throw; // "reichen Sie den Fehler weiter"
    }
}
void Simulation::vSimulieren(double dDauer, double dZeitschritt)
{


    while (dGlobaleZeit < dDauer) {
    	vSetzeZeit(dGlobaleZeit);
        // Simulate each intersection
        for (auto it : p_mKreuzungen) {

            it.second->vSimulieren(dZeitschritt);
        }
        vSleep(250*dZeitschritt);

        dGlobaleZeit += dZeitschritt;
    }
}
