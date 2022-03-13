#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>

using namespace std;


void Nuskaitymas(int& n, double kainos[], int zaidimuKiekis[]);
double VienoZaidimoDalis(double kaina);
double PriedasPrieAtlyginimo(int& n, double kainos[], int zaidimuKiekis[]);
double DidziausiasPriedas(int n, double kainos[], int zaidimuKiekis[], int& zaidimas);
void Isvedimas(double priedas, double kainos[], int zaidimas);

int main()
{
    int n;
    ifstream duomenys("duomenys.txt");
    duomenys >> n;
    duomenys.close();
    int zaidimuKiekis[n], zaidimas;
    double kainos[n], priedas;

    Nuskaitymas(n, kainos, zaidimuKiekis);
    priedas = PriedasPrieAtlyginimo(n, kainos, zaidimuKiekis);
    double max = DidziausiasPriedas(n, kainos, zaidimuKiekis, zaidimas);

    Isvedimas(priedas, kainos, zaidimas);

    return 0;
}

void Nuskaitymas(int& n, double kainos[], int zaidimuKiekis[])
{
    ifstream duomenys("duomenys.txt");
    duomenys >> n;
    for(int i=0; i<n; i++)
    {
        duomenys >> kainos[i] >> zaidimuKiekis[i];
    }
    duomenys.close();
}

double VienoZaidimoDalis(double kaina)
{
    return (kaina*=10)/100;
}

double PriedasPrieAtlyginimo(int& n, double kainos[], int zaidimuKiekis[])
{
    double priedas=0;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<zaidimuKiekis[i]; j++)
        {
            priedas+=VienoZaidimoDalis(kainos[i]);
        }
    }
    return priedas;
}

double DidziausiasPriedas(int n, double kainos[], int zaidimuKiekis[], int& zaidimas)
{
    double suma, max=0;
    for(int i=0; i<n; i++)
    {
        suma=0;
        for(int j=0; j<zaidimuKiekis[i]; j++)
        {
            suma+=kainos[i]*10/100;
        }
        if(suma>max)
        {
            max=suma;
            zaidimas=i;
        };
    }
    return max;
}

void Isvedimas(double priedas, double kainos[], int zaidimas)
{
    ofstream rezultatai("rezultatai.txt");
    cout << fixed << setprecision(2) << priedas << endl;
    cout << kainos[zaidimas] << endl;
    rezultatai.close();
}
