#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

struct gracz {
	string imie;
	string nazwisko;
	int pkt;
};

class ranking {
	ifstream plik1;
	ofstream plik2;
	vector<struct gracz> spis;
	vector <string> json;
	
	public:
		ranking();
		~ranking();
		
		void wprowadz();
		void sortowanie();
		void zapisJakoJson();
        void wypisz();
    	void zapiszDoPliku();  
};

ranking::ranking() {
	plik1.open("we.txt");
	plik2.open("wy.txt");
}

void ranking::wprowadz() {
	if(plik1.good())
		while(!plik1.eof()) {
			struct gracz wprowadzany;
			
			plik1>>wprowadzany.imie;
			plik1>>wprowadzany.nazwisko;
			plik1>>wprowadzany.pkt;
			spis.push_back(wprowadzany);
		}
}

void ranking::sortowanie() {
	sort(spis.begin(), spis.end(), [](const gracz &a, const gracz &b) {return (a.pkt > b.pkt);});
}

void ranking::zapisJakoJson() {
    for (vector<struct gracz>::iterator it = spis.begin(); it != spis.end(); ++it)
    {
		ostringstream ss;
		ss << it->pkt;
		string pkt = ss.str();
			
        json.push_back("{\"Punkty:\"" + pkt + ",\"Imie\":" + it->imie + ",\"Nazwisko\":" + it->nazwisko + "},\n");
    }
}

void ranking::wypisz() {
	cout<<"[\n";
	for (int i = 0; i < json.size(); i++) {
    	cout<<json[i];
	}
	cout<<"]";
}

void ranking::zapiszDoPliku() {
	plik2<<"[\n";
	for (int i = 0; i < json.size(); i++) {
    	plik2<<json[i];
	}
	plik2<<"]";
}

ranking::~ranking() {
	plik1.close();
	plik2.close();
}

int main(int argc, char** argv) {
	ranking R1;
	R1.wprowadz();
	R1.sortowanie();
	R1.zapisJakoJson();
	R1.wypisz();
    R1.zapiszDoPliku();  	
	return 0;
}

