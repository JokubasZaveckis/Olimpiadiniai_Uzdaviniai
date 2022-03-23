#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <cmath>

using namespace std;

void Nuskaitymas(int& n, int dienos[]);
float VidutineTemperatura(int n, int dienos[]);
int KarsciausiaDiena(int n, int dienos[]);
int kiekDienuNeigiama(int n, int dienos[]);
void Rikiavimas(int n, int dienos[]);
void Isvedimas(int n, int dienos[], float vidutineTemperatura, int karsciausiaDiena, int neigiamosDienos);

int main()
{
    int n, dienos[31];

    Nuskaitymas(n, dienos);
    float vidutineTemperatura = VidutineTemperatura(n, dienos);
    int karsciausiaDiena = KarsciausiaDiena(n, dienos);
    int neigiamosDienos = kiekDienuNeigiama(n, dienos);
    Isvedimas(n, dienos, vidutineTemperatura, karsciausiaDiena, neigiamosDienos);

    return 0;
}

void Nuskaitymas(int& n, int dienos[])
{
    ifstream duomenys("duomenys.txt");
    duomenys >> n;
    for(int i=0; i<n; i++)
    {
        duomenys >> dienos[i];
    }
    duomenys.close();
}

float VidutineTemperatura(int n, int dienos[])
{
    int suma=0;
    for(int i=0; i<n; i++)
    {
        suma+=dienos[i];
    }
    return suma*1.0/n;
}

int KarsciausiaDiena(int n, int dienos[])
{
    int max=0;
    for(int i=0; i<n; i++)
    {
        if(dienos[i]>dienos[max]) max=i;
    }
    return max;
}

int kiekDienuNeigiama(int n, int dienos[])
{
    int kiek=0;
    for(int i=0; i<n; i++)
    {
        if(dienos[i]<0) kiek++;
    }
    return kiek;
}

void Rikiavimas(int n, int dienos[])
{
    for(int i=0; i<n-1; i++)
    {
        int max=i;
        for(int j=i+1; j<n; j++)
        {
            if(dienos[j]>dienos[max]) max=j;
        }
        if(max!=i)
        {
            swap(dienos[i], dienos[max]);
        }
    }
}

void Isvedimas(int n, int dienos[], float vidutineTemperatura, int karsciausiaDiena, int neigiamosDienos)
{
    cout << "Vidutine temperatura: " << " " << vidutineTemperatura << endl;
    cout << "Maksimali temperatura buvo " << karsciausiaDiena << " diena. Ji tokia: " << dienos[karsciausiaDiena] << endl; // ar reikia ziureti ar daugiau dienu turejo maksimalia temperatura
    if(neigiamosDienos==0)
    {
        cout << "Neigiamu dienu nebuvo" << endl;
    }
    else cout << "Neigiama temperatura buvo " << neigiamosDienos << " dienu" << endl;
    Rikiavimas(n, dienos);
    cout << "Trys maksimalios temperaturos: ";
    for(int i=0; i<3; i++)
    {
        cout << dienos[i] << " ";
    }
    cout << endl;
    cout << "Trys maziausios temperaturos: ";
    for(int i=n-3; i<n; i++)
    {
        cout << dienos[i] << " ";
    }
    cout << endl;
}










