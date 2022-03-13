#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <limits.h>
#include <climits>

using namespace std;

struct Gyventojas
{
    char vardas[16];
    float suma=0;
    int* leidiniai=nullptr;
    int kiekLeidiniu=0;

    ~Gyventojas()
    {
        delete[] leidiniai;
    }
};

void Nuskaitymas(int& n, int& k, float*& kainos, Gyventojas*& gyventojai);
void KiekZmogusIsleidoPinigu(int n, int k, float*& kainos, Gyventojas*& gyventojai);
float KiekMiestelisIsledoPinigu(int n, Gyventojas*& gyventojai);
void KiekLeidiniuNusipirkoGyventojas(int n, int k, Gyventojas*& gyventojai);
int KasNusipirkoDaugiausiaLeidiniu(int n, Gyventojas*& gyventojai);
int KasIsleidoMaziausia(int n, Gyventojas*& gyventojai);
void Isvedimas(int n, Gyventojas* gyventojai, float suma, int daugiausia, int maziausia);

int main()
{
    int n, k;
    float* kainos = nullptr;
    Gyventojas* gyventojai = nullptr;

    Nuskaitymas(n, k, kainos, gyventojai);
    KiekZmogusIsleidoPinigu(n, k, kainos, gyventojai);
    float suma =  KiekMiestelisIsledoPinigu(n, gyventojai);
    KiekLeidiniuNusipirkoGyventojas(n, k, gyventojai);
    int daugiausia = KasNusipirkoDaugiausiaLeidiniu(n, gyventojai);
    int maziausia = KasIsleidoMaziausia(n, gyventojai);
    Isvedimas(n, gyventojai, suma, daugiausia, maziausia);

    delete[] gyventojai;
    return 0;
}

void Nuskaitymas(int& n, int& k, float*& kainos, Gyventojas*& gyventojai)
{
    ifstream duomenys("duomenys.txt");
    duomenys >> n >> k;
    gyventojai = new Gyventojas[n];
    for(int i=0; i<n; i++)
    {
        gyventojai[i].leidiniai = new int[k];
    }

    kainos = new float[k];
    for(int i=0; i<k; i++)
    {
        duomenys >> kainos[i];
    }

    for(int i=0; i<n; i++)
    {
        duomenys.ignore(256, '\n');
        duomenys.get(gyventojai[i].vardas, 16);
        for(int j=0; j<k; j++)
        {
            duomenys >> gyventojai[i].leidiniai[j];
        }
    }
    duomenys.close();
}

void KiekZmogusIsleidoPinigu(int n, int k, float*& kainos, Gyventojas*& gyventojai)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<k; j++)
        {
            gyventojai[i].suma+=kainos[j]*gyventojai[i].leidiniai[j];
        }
    }
}

float KiekMiestelisIsledoPinigu(int n, Gyventojas*& gyventojai)
{
    float suma=0;
    for(int i=0; i<n; i++)
    {
        suma+=gyventojai[i].suma;
    }
    return suma;
}

void KiekLeidiniuNusipirkoGyventojas(int n, int k, Gyventojas*& gyventojai)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<k; j++)
        {
            gyventojai[i].kiekLeidiniu+=gyventojai[i].leidiniai[j];
        }
    }
}

int KasNusipirkoDaugiausiaLeidiniu(int n, Gyventojas*& gyventojai)
{
    int max=0;
    for(int i=0; i<n; i++)
    {
        if(gyventojai[i].kiekLeidiniu>gyventojai[max].kiekLeidiniu) max=i;
    }
    return max;
}

int KasIsleidoMaziausia(int n, Gyventojas*& gyventojai)
{
    int min=0;
    for(int i=0; i<n; i++)
    {
        if(gyventojai[i].suma<gyventojai[min].suma) min=i;
    }
    return min;
}

void Isvedimas(int n, Gyventojas* gyventojai, float suma, int daugiausia, int maziausia)
{
    ofstream rezultatai("rezultatai.txt");

    for(int i=0; i<n; i++)
    {
        cout << fixed << setprecision(2) << gyventojai[i].vardas << " " << gyventojai[i].suma << endl;
    }
    cout << fixed << setprecision(2) << suma << endl;
    cout << gyventojai[daugiausia].vardas << " " << gyventojai[daugiausia].kiekLeidiniu << endl;
    cout << fixed << setprecision(2) << gyventojai[maziausia].vardas << " " << gyventojai[maziausia].suma << endl;
    rezultatai.close();
}
