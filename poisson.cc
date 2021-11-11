#include<iostream>
#include<fstream>
#include<cmath>
#include<vector>

/*
Definiere Poisson-Funktion.
Argumente sind Mittelwert mu und Häufigkeit k.
Ausgabe ist Wahrscheinlichkeit, die Häufigkeit k zu beobachten
*/
double poisson(double mu, int k) {
  double prob = pow(mu,k)*exp(-mu)/(tgamma(k+1));
  return prob;
}

int main() {

using namespace std;
vector<int> zaehler(11);

int Ntot=234;

ifstream fin("datensumme.txt");

//Fülle Zähler-Vektor
int zahl=0;
for(int i = 0 ; i < Ntot; i++) {
  fin >> zahl;
  zaehler[zahl] += 1;
}

fin.close();

//Ausgabe des Wertes von k und des zugehörigen Eintrags des Vektors
for(unsigned int k = 0; k < zaehler.size(); ++k) {
  std::cout << k << ": " << zaehler[k] << std::endl;
}

ofstream fout("hist.txt");

//Schreibe Inhalt des Vektors in die Datei hist.txt
for(unsigned int k = 0; k < zaehler.size(); ++k) {
  fout << k << " " << zaehler[k] << std::endl;
}

fout.close();

ofstream fout2("histpoi.txt");

/*
Ausgabe des Wertes von k, des zugehörigen Eintrags des Zähler-Vektors und der erwarteten Häufigkeit bei der Ereignisanzahl.
Die Werte werden in die Datei histpoi.txt geschrieben
Die erwartete Häufigkeit resultiert aus der Wahrscheinlichkeit aus der Poisson-Verteilung.
*/
for(unsigned int m = 0; m < zaehler.size(); ++m) {
  double pevents = poisson(3.11538, m) * Ntot;
  fout2 << m << " " << zaehler[m] << " " << pevents << std::endl;
}

fout2.close();

}