#include<iostream>
#include<fstream>
#include<cmath>
#include<vector>

int Ntot=234;

using namespace std;
vector<int> daten(Ntot);

/*
Definiere Poisson-Funktion.
Argumente sind Mittelwert mu und Häufigkeit k.
Ausgabe ist Wahrscheinlichkeit, die Häufigkeit k zu beobachten
*/
double poisson(double mu, int k) {
  double prob = pow(mu,k)*exp(-mu)/(tgamma(k+1));
  return prob;
}

/*
Definiere Likelihood-Funktion.
Argumente sind der Mittelwert mu und der Vektor, der das beobachtete Sample enthält.
Ausgabe ist Wahrscheinlichkeit, genau das gegebene Sample bei gegebenem Mittelwert zu beobachten.
Hierzu multipliziert die Funktion die Poisson-Wahrscheinlichkeit für alle Events miteinander.
*/

long double prob(std::vector<int> daten, double mu) {
  long double sprob = 1;
  for(int k : daten) {
    long double kprob = poisson(mu,k);
    sprob *= kprob;
    //std::cout << m << " " << daten[m] <<  " " << k << " " << kprob << " " << sprob << std::endl;
  }
  return sprob;
}

int main() {

ifstream fin("datensumme.txt");

//Fülle Vektor "daten" mit den Werten aus datensumme.txt
//Die push_back-Funktion hängt den ihr gegebenen Wert an den Vektor an.
int zahl = 0;
for(int i = 0; i < Ntot; i++) {
  fin >> zahl;
  daten[i] = zahl;
  //daten.push_back(zahl);
  //std::cout << zahl << std::endl;
}

fin.close();

std::cout << prob(daten, 3.11538) << std::endl;

/*
Schreibe die Werte von mu und L(mu) für Werte von mu zwischen 0 und 6 in Intervallen von 0,1 in die Datei likelihood.txt.
L(mu) basiert auf dem beobachteten Sample.
*/
ofstream fout("likelihood.txt");

for (int j = 0; j < 601; j++) {
  long double mu1 = 0.01 * j;
  long double muprob = prob(daten, mu1);
  fout << mu1 << " " << muprob << std::endl;
}

fout.close();



ofstream fout2("nll.txt");

/*
Schreibe die Werte von mu und - 2 ln (L(mu)) für Werte von mu zwischen 0 und 6 in Intervallen von 0,1 in die Datei nll.txt.
L(mu) basiert auf dem beobachteten Sample.
*/

for (int j = 0; j < 601; j++) {
  long double mu1 = 0.01 * j;
  long double muprob = prob(daten, mu1);
  long double nll = - 2 * log(muprob);
  fout2 << mu1 << " " << nll << std::endl;
}

fout2.close();

ofstream fout3("deltanll.txt");

/*
Schreibe die Werte von mu und - 2 ln (L(mu)) - (-2 ln (L(3.11538))) für Werte von mu zwischen 0 und 6 in Intervallen von 0,1 in die Datei deltanll.txt.
L(mu) basiert auf dem beobachteten Sample.
*/

for (int j = 0; j < 601; j++) {
  long double mu1 = 0.01 * j;
  long double muprob = prob(daten, mu1);
  long double nll = - 2 * log(muprob);
  long double deltanll = nll - (-2 * log (prob(daten, 3.11538)));
  fout3 << mu1 << " " << deltanll << std::endl;
}

fout3.close();

/*
Berechne Lambda aus Teilaufgabe e)
Lambda ist definiert als L(mu)/(Produkt der P(ki,ki) für alle Messungen in "Daten").
Wir verwenden das bereits bekannte mu=3,11538.
Zunächst wird das Produkt berechnet, dann Lambda.
*/

long double sprob2 = 1;

for (int k : daten) {
  long double kprob = poisson(k,k);
  sprob2 *= kprob;
}

long double lambda = prob(daten, 3.11538)/sprob2;

std::cout << "Product over all P(ki,ki): " << sprob2 << std::endl;

std::cout << "Resulting Lambda: " << lambda << std::endl;

std::cout << "-2 ln (Lambda): " << - 2 * log(lambda) << std::endl;

}