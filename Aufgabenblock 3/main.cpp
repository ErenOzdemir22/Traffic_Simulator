#include <iostream>
#include <memory>
#include "Fahrzeug.h"
#include <vector>
#include "PKW.h"
#include "Fahrrad.h"
#include "Weg.h"
#include "Tempolimit.h"
#include "SimuClientSocket.h"
#include "SimuClient.h"
#include "random"
#include "Kreuzung.h"
#include <stdexcept>
#include <fstream>
#include "Simulation.h"

double TAKT = 0.5;

void vAufgabe_1(){

Fahrzeug FahrzeugObj0("BMW");

Fahrzeug FahrzeugObj1("Mercedes");

Fahrzeug FahrzeugObj2("Audi");//stackde tutulur

Fahrzeug FahrzeugObj3("Volkswagen"); // static obje blok kapanınca yok olur//heapde tutulur

Fahrzeug* Fahrzeugptr = new Fahrzeug("Tofaş"); //dinamik obje program kapanana kadaer devam eder

auto ptr = std::make_unique<Fahrzeug>("Ford");

auto ptr2 = std::move(ptr);

auto ptr3 = std::make_shared<Fahrzeug>("Tesla");
std::cout<<ptr3.use_count()<<std::endl;

auto ptr4 = ptr3;

std::cout<<ptr3.use_count()<<std::endl;

std::vector<std::unique_ptr<Fahrzeug>> vector1;
std::vector<std::shared_ptr<Fahrzeug>> vector2;


vector1.push_back(std::move(ptr));
vector1.push_back(std::move(ptr2));
vector2.push_back(ptr3);
vector2.push_back(ptr4);


}


void vAufgabe_1a(){
	auto ptr1 = std::make_unique<PKW>("McLaren", 120, 5);
	auto ptr2 = std::make_unique<PKW>("Mini", 90, 7);
	auto ptr3 = std::make_unique<PKW>("Mazda",210, 6);
	auto ptr4 = std::make_unique<Fahrrad>("BMX",15);

	std::vector<std::unique_ptr<Fahrzeug>> vector;

	vector.push_back(std::move(ptr1));
	vector.push_back(std::move(ptr2));
	vector.push_back(std::move(ptr3));
	vector.push_back(std::move(ptr4));

	PKW::vKopf();
	while(dGlobaleZeit<6){

		if(dGlobaleZeit==3){
			for(int i=0; i<4; i++){

				vector[i]-> dTanken();

			}
			std::cout<<"Tanken werden ausgefüllt"<<std::endl;
		}
		for(int i=0; i<4; i++){

			std::cout<<*vector[i];
			std::cout<<std::endl;
		}

		dGlobaleZeit+=0.5;


		for(int i=0; i<4; i++){

			vector[i]->vSimulieren();
		}

		std::cout<<std::endl;

	}
}
void vAufgabe_3(){

	 auto ptr1 = std::make_unique<PKW>("Mtsbh",40,30);
	 auto ptr2 = std::make_unique<PKW>("Mercedes",30,20);

	 bool temp = ptr1<ptr2;
	 std::cout<<temp<<*ptr1<<*ptr2;

}

void  vAufgabe_4(){


	auto ptr1 = std::make_unique<PKW>("VW",40,30);
	auto ptr2 = std::make_unique<PKW>("BMW",40,30);

    Weg::vKopf();
	Weg Weg1 ("dd", 30, Tempolimit::Innerorts);
	Weg1.vSimulieren();
	Weg1.vAusgeben(std::cout);

}

void vAufgabe_5(){


	Weg weg1("Erenstrss", 600, Tempolimit::Landstraße);

	auto ptr1 = std::make_unique<PKW>("Toyota", 200,20,150);
	auto ptr2 = std::make_unique<PKW>("Audi", 300,40,300);
	auto ptr3 = std::make_unique<PKW>("Renault", 100,30,110);

	weg1.vAnnahme(std::move(ptr1),0.5);
	weg1.vAnnahme(std::move(ptr2));
	weg1.vAnnahme(std::move(ptr3));

	Weg::vKopf();

	dGlobaleZeit+=0.5;
	weg1.vSimulieren();
    weg1.vAusgeben(std::cout);

    std::cout<<std::endl;

    dGlobaleZeit+=0.5;
   	weg1.vSimulieren();
    weg1.vAusgeben(std::cout);
}
void vAufgabe_6(){

   auto	ptr1=std::make_unique<PKW>("BMW",100,1,100);
   auto	ptr2=std::make_unique<PKW>("GMC",50,1,100);
   auto	ptr5=std::make_unique<PKW>("GC",50,1,100);
   auto	ptr3=std::make_unique<Weg>("hin",500,Tempolimit::Landstraße);
   auto	ptr4=std::make_unique<Weg>("rueck",500,Tempolimit::Landstraße);
   int Koordinaten[4]= {10,10,510,510};




   ptr3->vAnnahme(std::move(ptr1));//yola araba koyuyoruz, weg in ppfahrzeug listesine koyduk
   ptr4->vAnnahme(std::move(ptr2));
   ptr4->vAnnahme(std::move(ptr5), 3);//Annahme yola araçları kabul ediyor ; 3, başlangıç zamanı
   //bZeichneStrasse("bey","hin",50,2,Koordinaten);
   bInitialisiereGrafik(600,600);
   bZeichneStrasse("rueck","hin",500,2,Koordinaten);//2, koordinat sayısıdır
   while(dGlobaleZeit<15){
	   ptr3->vSimulieren();
	   ptr4->vSimulieren();
	   vSleep(400);//her schritt arasında mesafe var
	   dGlobaleZeit+=0.5;
   }


}

void vAufgabe6a()
{
    vertagt::VListe<int> liste;//Vliste template klass ının liste objesi


    // 1. Setup Random Number Generator
    static std::mt19937 device(9);//device bir mersenne twister engine, buna seed giriliyor ve random oluşturuluyor
    // 0=seed
    std::uniform_int_distribution<int> dist(1, 10);//oluşuturlan  sayıları eşit aralıklarla verilen aralıkta dağıtıyor

    // 2. Add elements
    for (int i = 0; i < 10; ++i) {         //oluşturulan listeye rastgele 10 taen eleman ekledik
        liste.push_back(dist(device));
    }

    std::cout << "Initial list:\n";        // boş listeyi print ler çünkü aktualisieren yaptırmadı henüz
        for (auto it = liste.begin(); it != liste.end(); ++it) {
            std::cout << *it << " ";
        }


    liste.vAktualisieren();   //aktion lar listesindeki her elemana Ausführen yapıyo



    // 7. Print (Final result)
    std::cout << "After vAktualisieren():\n";    // şu anda elemanlar pobjekte listesine yüklendi
    for (auto it = liste.begin(); it != liste.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
}
void vTest_Aufgabe_6_2_Teil3()
{
	//std::cout<<"1235678";
		int koordinaten[4] = {30,30,530,530};

		Weg w1("L_hin", 500, Tempolimit::Landstraße);
		Weg w2("L_rueck", 500, Tempolimit::Landstraße);

		bInitialisiereGrafik(1000,1000);
		bZeichneStrasse("L_hin","L_rueck",500,2,koordinaten);

		//std::cout<<"hello1235567890";

		auto p1 = std::make_unique<PKW>("BMW", 20, 8, 50);
		auto p2 = std::make_unique<PKW>("Audi", 75, 10, 200);
		auto p3 = std::make_unique<PKW>("Ford", 75, 10, 200);

		w1.vAnnahme(std::move(p1),3.0);//parked vehicle
		w2.vAnnahme(std::move(p2));//running vehicle
		w1.vAnnahme(std::move(p3),50);//perma parked vehicle

		bool flag = true;

		for(int i = 1; i<=100; i++){
			dGlobaleZeit = TAKT*i;
			if(i>=15 && flag){
				auto p3 = std::make_unique<PKW>("Mercedes", 75, 10, 200);
				w1.vAnnahme(std::move(p3));
				flag = false;
			}
			vSetzeZeit(dGlobaleZeit);
					w1.vSimulieren();
					w2.vSimulieren();
					vSleep(550);

    }
}

void vAufgabe7(){

	Weg w1("W12", 40, Tempolimit::Landstraße,true);
	Weg w2("W21", 40, Tempolimit::Landstraße,true);
	int koordinaten1[99] = {680,40,680,300};

	Weg w3("W23a", 115, Tempolimit::Autobahn,false);
	Weg w4("W32a", 115, Tempolimit::Autobahn,false);
	int koordinaten2[99] = {680,300,850,300,970,390,970,500,850,570,680,570};

	Weg w5("W23b", 40, Tempolimit::Landstraße,true);
	Weg w6("W32b", 40, Tempolimit::Landstraße,true);
	int koordinaten3[99] = {680,300,680,570};

	Weg w7("W24", 55, Tempolimit::Landstraße,true);
	Weg w8("W42", 55, Tempolimit::Landstraße,true);
	int koordinaten4[99] = {320,300,680,300};

	Weg w9("W34", 115, Tempolimit::Autobahn,false);
	Weg w10("W43", 115, Tempolimit::Autobahn,false);
	int koordinaten5[99] = {320,300,320,420,350,510,500,570,680,570};

	Weg w11("W23a", 130, Tempolimit::Autobahn,false);
	Weg w12("W23a", 130, Tempolimit::Autobahn,false);
	int koordinaten6[99] = {320,300,320,150,200,60,80,90,70,250,170,300,320,300};

	auto k1 = std::make_shared<Kreuzung>(1000);
	auto k2 = std::make_shared<Kreuzung>(1000);
	auto k3 = std::make_shared<Kreuzung>(1000);
	auto k4 = std::make_shared<Kreuzung>(1000);

	std::weak_ptr<Kreuzung> p1 = k1;
	std::weak_ptr<Kreuzung> p2 = k2;
	std::weak_ptr<Kreuzung> p3 = k3;
	std::weak_ptr<Kreuzung> p4 = k4;


	bInitialisiereGrafik(1000,1000);

	bZeichneStrasse("W12","W21",40,2,koordinaten1);
	bZeichneStrasse("W23a","W32a",115,6,koordinaten2);
	bZeichneStrasse("W23b","W32b",40,2,koordinaten3);
	bZeichneStrasse("W24","W42",55,2,koordinaten4);
	bZeichneStrasse("W34","W43",85,5,koordinaten5);
	bZeichneStrasse("W44a","W44b",130,7,koordinaten6);

	bZeichneKreuzung(680,40);
	bZeichneKreuzung(680,300);
	bZeichneKreuzung(680,570);
	bZeichneKreuzung(320,300);

	Kreuzung::vVerbinde("W12","W21",40,p1,p2,Tempolimit::Landstraße,true);//true
	Kreuzung::vVerbinde("W23a","W32a",115,p2,p3,Tempolimit::Autobahn,true);
	Kreuzung::vVerbinde("W23b","W32b",40,p2,p3,Tempolimit::Landstraße,true);//true
	Kreuzung::vVerbinde("W24","W42",55,p4,p2,Tempolimit::Landstraße,true);//true
	Kreuzung::vVerbinde("W34","W43",85,p4,p3,Tempolimit::Autobahn,true);
	Kreuzung::vVerbinde("W44a","W44b",130,p4,p4,Tempolimit::Autobahn,true );

	auto pf1 = std::make_unique<PKW>("Audi", 35, 10, 200);
	auto pf2 = std::make_unique<PKW>("Toyota", 30,20,150);
	auto pf3 = std::make_unique<PKW>("Renault", 15,40,300);
	auto pf4 = std::make_unique<PKW>("BMW", 50,30,110);


	k1->vAnnahme(std::move(pf1));
	k2->vAnnahme(std::move(pf2));
	k4->vAnnahme(std::move(pf3));
	k1->vAnnahme(std::move(pf4));


	dGlobaleZeit = 0;
	while(dGlobaleZeit<150){
		vSetzeZeit(dGlobaleZeit);
		k1->vSimulieren();
		k2->vSimulieren();
		k3->vSimulieren();
		k4->vSimulieren();
		vSleep(250);//her schritt arasında mesafe var
		dGlobaleZeit+=0.5;
	   }

	vSleep(2000);
}
void vAufgabe8() {
    std::cout << "--- Starting Aufgabe 8: File Input ---" << std::endl;

    std::ifstream infile("VO.dat");

    if (!infile.is_open()) {
        std::cerr << "Error: Could not open VO.dat. Make sure it is in the build folder." << std::endl;
        return;
    }

    try {

        infile.exceptions(std::ios_base::failbit | std::ios_base::badbit);

        //empty objects
        PKW pkw;
        Fahrrad fahrrad;
        Kreuzung Kreuzung;

        infile >> pkw
               >> fahrrad
               >> Kreuzung;


        std::cout << "\n--- Data Read From File ---" << std::endl;
        std::cout << "PKW:      " << pkw << std::endl;
        std::cout << "Fahrrad:  " << fahrrad << std::endl;
        std::cout << "Kreuzung: " << Kreuzung << std::endl;

    }
    catch (std::runtime_error& e) {

        std::cerr << "Runtime Error caught: " << e.what() << std::endl;
    }
    catch (std::ios_base::failure& e) {

        std::cerr << "File Error caught: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unknown error occurred." << std::endl;
    }

}

void vAufgabe9()
{
    std::ifstream file("Simu.dat");

    // Activate exception handling for the stream
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        if (!file.is_open()) {
            throw std::runtime_error("Could not open Simu.dat");
        }

        Simulation sim;
        sim.vEinlesen(file);
    }
    catch (const std::exception& e) {
        std::cerr << "Error while reading simulation file: "
                  << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void vAufgabe9a(){
	 std::ifstream file("SimuDisplay.dat");

	    // Activate exception handling for the stream
	    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);//hatalar sessiz olmasın expection fırlatılsın

	    try {
	        if (!file.is_open()) {
	            throw std::runtime_error("Could not open Simu.dat");
	        }

	        Simulation sim;
	        sim.vEinlesen(file,1);
	        sim.vSimulieren(100,0.1);
	    }
	    catch (const std::exception& e) {
	        std::cerr << "Error while reading simulation file: "
	                  << e.what() << std::endl;
	        std::exit(EXIT_FAILURE);
	    }


}




int main()
{
	std::cout.setf(std::ios::unitbuf);
	//vAufgabe_1();
	//vAufgabe_1a();
	//vAufgabe_3();
	//vAufgabe_4();
	//vAufgabe_5();
	//vAufgabe_6();
	//vAufgabe6a();
	//vTest_Aufgabe_6_2_Teil3();
	//vAufgabe7();
	//vAufgabe8();
	//vAufgabe9();
	vAufgabe9a();
 	return 0 ;

}













