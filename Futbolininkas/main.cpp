#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>

using namespace std;

struct Futbolininkas
{
    string vardas, pavarde;
    int kiekIvarciu=0;
    int* ivarciai = nullptr;
};

void Nuskaitymas(int& n, Futbolininkas futbolininkai[]);
void Isvedimas(int n, Futbolininkas futbolininkai[]);
void IvarciuSumosSkaiciavimas(int n, Futbolininkas& futbolininkas);
void IvarciuRikiavimas(int n, int ivarciai[]);
void Isvedimas(int n, Futbolininkas futbolininkas);

int main()
{
    int n;
    Futbolininkas futbolininkai[2];

    Nuskaitymas(n, futbolininkai);
    IvarciuSumosSkaiciavimas(n, futbolininkai[0]);
    IvarciuSumosSkaiciavimas(n, futbolininkai[1]);
    int laimetojas;
    if(futbolininkai[0].kiekIvarciu>futbolininkai[1].kiekIvarciu)
        laimetojas=0;
    else laimetojas=1;
    IvarciuRikiavimas(n, futbolininkai[laimetojas].ivarciai);
    Isvedimas(n, futbolininkai[laimetojas]);

    return 0;
}

void Nuskaitymas(int& n, Futbolininkas futbolininkai[])
{
    ifstream duomenys("duomenys.txt");
    duomenys >> futbolininkai[0].vardas >> futbolininkai[0].pavarde;
    duomenys >> futbolininkai[1].vardas >> futbolininkai[1].pavarde;
    duomenys >> n;
    futbolininkai[0].ivarciai = new int[n];
    futbolininkai[1].ivarciai = new int[n];
    for(int i=0; i<n; i++)
    {
        duomenys >> futbolininkai[0].ivarciai[i];
        duomenys >> futbolininkai[1].ivarciai[i];
    }
    duomenys.close();
}

void IvarciuSumosSkaiciavimas(int n, Futbolininkas& futbolininkas)
{
    for(int i=0; i<n; i++)
    {
        futbolininkas.kiekIvarciu+=futbolininkas.ivarciai[i];
    }
}

void IvarciuRikiavimas(int n, int ivarciai[])
{
    for(int i=0; i<n-1; i++)
    {
        int max=i;
        for(int j=i+1; j<n; j++)
        {
            if(ivarciai[j]>ivarciai[max])
            {
                max=j;
            }
        }
        if(max!=i)
        {
            swap (ivarciai[i], ivarciai[max]);
        }
    }

}

void Isvedimas(int n, Futbolininkas futbolininkas)
{
    ofstream rezultatai("rezultatai.txt");
    rezultatai << futbolininkas.vardas << " " << futbolininkas.pavarde << endl;
    for(int i=0; i<n; i++)
    {
        rezultatai << futbolininkas.ivarciai[i] << " ";
    }
    rezultatai.close();
}
