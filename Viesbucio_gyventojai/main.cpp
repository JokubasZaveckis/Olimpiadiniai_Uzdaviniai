#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <ctime>

using namespace std;

struct Gyventojas
{
    string Vardas;
    int metai, menuo, diena, kiekGyveno;
    int Imetai, Imenuo, Idiena; // isvykimo datos
    float kiekKainavo, kiekSumokejo=0;
    time_t atvykimoData;
    time_t laikas = time(0);
    char* t = ctime(&laikas);

    void laikoKonvertavimas();
    void isvykimoDienosSkaiciavimas();

};

void Nuskaitymas(int& n, Gyventojas*& gyventojai);
void IslaiduSkaiciavimas(int n, Gyventojas*& gyventojai);
float Suma(int n, Gyventojas*& gyventojai);
void Isvedimas(int n, float suma, Gyventojas*& gyventojai);

int main()
{
    int n;
    Gyventojas* gyventojai = nullptr;

    Nuskaitymas(n, gyventojai);
    IslaiduSkaiciavimas(n, gyventojai);
    float suma = Suma(n, gyventojai);


//    tm laikai={0};
//    laikai.tm_year = 2020-1900;
//    laikai.tm_mon = 1-1;
//    laikai.tm_mday = 15;
//
//    tm metai={0};
//    metai.tm_year = 2021-1900;
//    metai.tm_mon = 10-1;
//    metai.tm_mday = 25;
//
//    time_t laikas1 = mktime(&laikai);
//    time_t laikas2 = mktime(&metai);
//
//    cout << difftime(laikas2, laikas1)/(60*60*24) << endl;

//    time_t laikas3 = (laikas2-laikas1)/(3600*24);
//    char* a = ctime(&laikas1);

    //cout << a << endl;

    Isvedimas(n, suma, gyventojai);

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

void Gyventojas::laikoKonvertavimas()
{
    tm laikai= {0};
    laikai.tm_year = metai-1900;
    laikai.tm_mon = menuo-1;
    laikai.tm_mday = diena;
    atvykimoData = mktime(&laikai);
}

void Gyventojas::isvykimoDienosSkaiciavimas()
{
    atvykimoData += kiekGyveno*60*60*24;
}

void Isvedimas(int n, float suma, Gyventojas*& gyventojai)
{
    ofstream rezultatai("rezultatai.txt");

    for(int i=0; i<n; i++)
    {
        gyventojai[i].laikoKonvertavimas();
        gyventojai[i].isvykimoDienosSkaiciavimas();
        cout << gyventojai[i].Vardas << " " << gyventojai[i].metai << " " << gyventojai[i].menuo << " " << gyventojai[i].diena << " " << ctime(&gyventojai[i].atvykimoData) << " " << gyventojai[i].kiekSumokejo << " " << gyventojai[i].kiekGyveno << endl;
    }
    cout << suma << endl;
    rezultatai.close();
}
