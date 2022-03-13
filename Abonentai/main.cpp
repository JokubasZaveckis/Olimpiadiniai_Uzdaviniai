#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>

using namespace std;

struct Gyventojas
{
    string Vardas;
    int numeris;
    string miestas;
    int kiekLaikoPrasnekejo;
    float kiekSumokes=0;
};

struct Kaina
{
    string miestas;
    float kainaMinutei;
};

void Nuskaitymas(int& n, int& k, Gyventojas*& gyventojai, Kaina*& kainos);
void MokescioSkaiciavimas(int n, int k, Gyventojas*& gyventojai, Kaina*& kainos);
void Rikiavimas(int n, Gyventojas*& gyventojai);
void Sutraukimas(int& n, Gyventojas*& gyventojai);
float Pajamos(int n, Gyventojas*& gyventojai);
void Isvedimas(int n, Gyventojas*& gyventojai, float pajamos);

int main()
{
    int n, k;
    Gyventojas* gyventojai = nullptr;
    Kaina* kainos = nullptr;

    Nuskaitymas(n, k, gyventojai, kainos);
    MokescioSkaiciavimas(n, k, gyventojai, kainos);
    Rikiavimas(n, gyventojai);
    Sutraukimas(n, gyventojai);
    float pajamos = Pajamos(n, gyventojai);
    Isvedimas(n, gyventojai, pajamos);

    delete[] gyventojai;
    delete[] kainos;
    return 0;
}

void Nuskaitymas(int& n, int& k, Gyventojas*& gyventojai, Kaina*& kainos)
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
        duomenys >> gyventojai[i].numeris >> gyventojai[i].miestas >> gyventojai[i].kiekLaikoPrasnekejo;
    }
    duomenys.close();

    ifstream df("kainos.txt");
    df>>k;
    kainos = new Kaina[k];
    for(int i=0; i<k; i++)
    {
        df >> kainos[i].miestas >> kainos[i].kainaMinutei;
    }
    df.close();
}

void MokescioSkaiciavimas(int n, int k, Gyventojas*& gyventojai, Kaina*& kainos)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<k; j++)
        {
            if(gyventojai[i].miestas==kainos[j].miestas)
            {
                gyventojai[i].kiekSumokes+=gyventojai[i].kiekLaikoPrasnekejo*kainos[j].kainaMinutei;
            }
        }
    }
}

void Rikiavimas(int n, Gyventojas*& gyventojai)
{
    for(int i=0; i<n-1; i++)
    {
        int max=i;
        for(int j=i+1; j<n; j++)
        {
            if(gyventojai[j].Vardas < gyventojai[max].Vardas)
            {
                max=j;
            }
        }
        if(max!=i)
        {
            swap(gyventojai[i], gyventojai[max]);
        }
    }
}

void Sutraukimas(int& n, Gyventojas*& gyventojai)
{
    for(int i=0; i<n-1; i++)
    {
        if(gyventojai[i].Vardas==gyventojai[i+1].Vardas)
        {
            gyventojai[i].kiekSumokes+=gyventojai[i+1].kiekSumokes;
            for(int j=i+1; j<n-1; j++)
            {
                gyventojai[j]=gyventojai[j+1];
            }
            i--;
            n--;
        }
    }
}

float Pajamos(int n, Gyventojas*& gyventojai)
{
    float suma=0;
    for(int i=0; i<n; i++)
    {
        suma+=gyventojai[i].kiekSumokes;
    }
    return suma;
}

void Isvedimas(int n, Gyventojas*& gyventojai, float pajamos)
{
    ofstream rezultatai("rezultatai.txt");

    for(int i=0; i<n; i++)
    {
        cout << fixed << setprecision(2) << gyventojai[i].Vardas << " " << gyventojai[i].kiekSumokes << endl;
    }
    cout << fixed << setprecision(2) << pajamos << endl;
    rezultatai.close();
}
