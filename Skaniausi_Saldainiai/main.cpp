#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

struct Gamintojas
{
    string Pavadinimas;
    int kiekRusiu;
    string* rusis = nullptr;
    int* skonis = nullptr;
};

void Nuskaitymas(int& n, Gamintojas*& gamintojai);
void Rikiavimas(int n, Gamintojas*& gamintojai);
void Rikiavimas2(int kriterijai[], string pavadinimai[], int a);
void Isvedimas(int n, Gamintojas*& gamintojai);

int main()
{
    int n;
    Gamintojas* gamintojai = nullptr;
    Nuskaitymas(n, gamintojai);
    Rikiavimas(n, gamintojai);

    /*for(int i=0; i<n; i++)
    {
        Rikiavimas2(gamintojai[i].skonis, gamintojai[i].rusis, gamintojai[i].kiekRusiu);
    }*/

    Isvedimas(n, gamintojai);

    delete[] gamintojai;
    return 0;

}

void Nuskaitymas(int& n, Gamintojas*& gamintojai)
{
    ifstream duomenys("duomenys.txt");
    duomenys >> n;
    gamintojai = new Gamintojas[n];

    char pavadinimas[26], rusiesPavadinimas[21];
    for(int i=0; i<n; i++)
    {
        duomenys.ignore(256, '\n');
        duomenys.get(pavadinimas, 26);
        gamintojai[i].Pavadinimas = pavadinimas;
        duomenys >> gamintojai[i].kiekRusiu;
        gamintojai[i].rusis = new string[gamintojai[i].kiekRusiu];
        gamintojai[i].skonis = new int[gamintojai[i].kiekRusiu];
        for(int j=0; j<gamintojai[i].kiekRusiu; j++)
        {
            duomenys.ignore(256, '\n');
            duomenys.get(rusiesPavadinimas, 21);
            gamintojai[i].rusis[j]=rusiesPavadinimas;
            duomenys >> gamintojai[i].skonis[j];
        }
    }
    duomenys.close();
}

void Rikiavimas(int n, Gamintojas*& gamintojai)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<gamintojai[i].kiekRusiu-1; j++)
        {
            int max=j;
            for(int k=j+1; k<gamintojai[i].kiekRusiu; k++)
            {
                if(gamintojai[i].skonis[k]<gamintojai[i].skonis[max])
                {
                    max=k;
                }
            }
            if(max!=j)
            {
                swap(gamintojai[i].rusis[j], gamintojai[i].rusis[j]);
                swap(gamintojai[i].skonis[j], gamintojai[i].skonis[j]);
            }
        }
    }
}

void Rikiavimas2(int kriterijai[], string pavadinimai[], int a)
{
    for(int i=0; i<a; i++)
    {
        int max=i;
        for(int j=i+1; j<a; j++)
        {
            if(kriterijai[j]<kriterijai[max])
            {
                max=j;
            }
        }
        if(max!=i)
        {
            swap(kriterijai[i], kriterijai[max]);
            swap(pavadinimai[i], pavadinimai[max]);
        }
    }
}

void Isvedimas(int n, Gamintojas*& gamintojai)
{
    ofstream rezultatai("rezultatai.txt");
    for(int i=0; i<n; i++)
    {
        rezultatai << gamintojai[i].Pavadinimas << endl;
        for(int j=0; j<gamintojai[i].kiekRusiu; j++)
        {
            rezultatai << setw(10) << gamintojai[i].rusis[j] << " " << gamintojai[i].skonis[j] << endl;
            cout << setw(10) << gamintojai[i].rusis[j] << " " << gamintojai[i].skonis[j] << endl;
        }
    }
    rezultatai.close();
}
