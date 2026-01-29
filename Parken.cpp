#include "Losfahren.h"
#include "Parken.h"


Parken::Parken(Weg& w1,double StartZeit): Verhalten(w1), p_dStartZeit(StartZeit){

}

Parken::~Parken() {
	// TODO Auto-generated destructor stub
}

double Parken::dStrecke(Fahrzeug& fhrzg,double Zeitinterval){
         if(p_dStartZeit<dGlobaleZeit){
     //   	 std::cout<<"Los Fahren!";
        	 throw Losfahren(p_Weg,fhrzg);

         }
         else{
        	 return 0;

         }
}

