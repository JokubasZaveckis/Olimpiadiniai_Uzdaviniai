#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>

using namespace std;

const int DIENOS[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

struct Gyventojas
{
    string Vardas;
    int metai, menuo, diena, kiekGyveno;
    int Imetai, Imenuo, Idiena; // isvykimo datos
    float kiekKainavo, kiekSumokejo=0;
};

void Nuskaitymas(int& n, Gyventojas*& gyventojai);
void IslaiduSkaiciavimas(int n, Gyventojas*& gyventojai);
float Suma(int n, Gyventojas*& gyventojai);
void Isvedimas(int n, Gyventojas* gyventojai);

int main()
{
    int n;
    Gyventojas* gyventojai = nullptr;

    Nuskaitymas(n, gyventojai);
    IslaiduSkaiciavimas(n, gyventojai);
    float suma = Suma(n, gyventojai);
    Isvedimas(n, gyventojai);

    delete[] gyventojai;
    return 0;
}

void Nuskaitymas(int& n, Gyventojas*& gyventojai)
{
    ifstream duomenys("duomenys.txt");
    duomenys >> n;
    gyventojai = new Gyventojas[n];
    char vardas[21];
    for(int i=0; i<n; i++)
    {
         duomenys.ignore(256, '\n');
         duomenys.get(vardas, 21);
         gyventojai[i].Vardas = vardas;
         duomenys >> gyventojai[i].metai >> gyventojai[i].menuo >> gyventojai[i].diena >> gyventojai[i].kiekGyveno >> gyventojai[i].kiekKainavo;
    }
    duomenys.close();
}

void IslaiduSkaiciavimas(int n, Gyventojas*& gyventojai)
{
    for(int i=0; i<n; i++)
    {
        gyventojai[i].kiekSumokejo=gyventojai[i].kiekKainavo*gyventojai[i].kiekGyveno;
    }
}

float Suma(int n, Gyventojas*& gyventojai)
{
    float suma=0;
    for(int i=0; i<n; i++)
    {
        suma+=gyventojai[i].kiekSumokejo;
    }
    return suma;
}

void Rikiavimas(int n, Gyventojas*& gyventojai)
{
    for(int i=0; i<n-1; i++)
    {
        int max=i;
        for(int j=i+1; j<n; j++)
        {
            if(gyventojai[j].kiekSumokejo>gyventojai[max].kiekSumokejo) max=j;
        }
        if(max!=i)
        {
            swap(gyventojai[i], gyventojai[max]);
        }
    }
}

void IsvykimoDatosSkaiciavimas(int n, Gyventojas*& gyventojai)
{
    for(int i=0; i<n; i++)
    {
        while(gyventojai[i].kiekGyveno>356)
        {
            gyventojai[i].kiekGyveno-=356;
            gyventojai[i].Imetai++;
        }
        while(gyventojai[i].kiekGyveno>31)
    }
}

void Isvedimas(int n, Gyventojas* gyventojai)
{
    ofstream rezultatai("rezultatai.txt");

    for(int i=0; i<n; i++)
    {

    }
    rezultatai.close();
}
