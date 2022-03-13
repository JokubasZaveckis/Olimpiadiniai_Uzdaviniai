#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>

using namespace std;

struct Vaikas
{
    char vardas[16];
    int litai, centai;
    int dienos, porcijos;
    int sutaupyta;
    float kiekIsleidoLedams=0;
    float kiekTuriCentais=0;
};

void Nuskaitymas(int& n, Vaikas*& vaikai);
void KiekVaikasTuriCentais(int n, Vaikas*& vaikai);
void KiekSutaupe(int n, Vaikas*& vaikai);
int KiekLikoPienui(int n, Vaikas*& vaikai);
int KurisPaaukojoDaugiausia(int n, Vaikas*& vaikai);
void Isvedimas(int n, Vaikas* vaikai, int suma, int max);

int main()
{
    int n;
    Vaikas* vaikai = nullptr;

    Nuskaitymas(n, vaikai);
    KiekVaikasTuriCentais(n, vaikai);
    KiekSutaupe(n, vaikai);
    int suma = KiekLikoPienui(n, vaikai);
    int max =  KurisPaaukojoDaugiausia(n, vaikai);
    Isvedimas(n, vaikai, suma, max);

    delete[] vaikai;
    return 0;
}

void Nuskaitymas(int& n, Vaikas*& vaikai)
{
    ifstream duomenys("duomenys.txt");
    duomenys >> n;
    vaikai = new Vaikas[n];
    float a;

    for(int i=0; i<n; i++)
    {
         duomenys.ignore(256, '\n');
         duomenys.get(vaikai[i].vardas, 16);
         duomenys >> vaikai[i].litai >> vaikai[i].centai >> vaikai[i].dienos;
         for(int j=0; j<vaikai[i].dienos; j++)
         {
             duomenys >> vaikai[i].porcijos >> a;
             vaikai[i].kiekIsleidoLedams+=vaikai[i].porcijos*a*100;
         }
    }
    duomenys.close();
}

void KiekVaikasTuriCentais(int n, Vaikas*& vaikai)
{
    for(int i=0; i<n; i++)
    {
        vaikai[i].kiekTuriCentais=vaikai[i].litai*100+vaikai[i].centai;
    }
}

void KiekSutaupe(int n, Vaikas*& vaikai)
{
    for(int i=0; i<n; i++)
    {
        vaikai[i].sutaupyta=vaikai[i].kiekTuriCentais-vaikai[i].kiekIsleidoLedams;
    }
}

int KiekLikoPienui(int n, Vaikas*& vaikai)
{
    int suma=0;
    for(int i=0; i<n; i++)
    {
        suma+=vaikai[i].sutaupyta;
    }
    return suma;
}

int KurisPaaukojoDaugiausia(int n, Vaikas*& vaikai)
{
    int max=0;
    for(int i=0; i<n; i++)
    {
        if(vaikai[i].sutaupyta>vaikai[max].sutaupyta)
        {
            max=i;
        }
    }
    return max;
}


void Isvedimas(int n, Vaikas* vaikai, int suma, int max)
{
    ofstream rezultatai("rezultatai.txt");

    for(int i=0; i<n; i++)
    {
        cout << vaikai[i].vardas << " " << vaikai[i].sutaupyta/100 << " " << vaikai[i].sutaupyta%100 << endl;
    }
    cout << suma/100 << " " << suma%100 << endl;
    cout << vaikai[max].vardas << " " << vaikai[max].sutaupyta/100 << " " << vaikai[max].sutaupyta%100;
    rezultatai.close();
}
