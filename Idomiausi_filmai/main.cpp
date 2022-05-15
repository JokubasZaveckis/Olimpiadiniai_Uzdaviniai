#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>

using namespace std;

struct Filmas
{
    int metai;
    string pavadinimas;
    int laikas, ziurovai;
};

void Nuskaitymas(int& n, Filmas*& filmai);
void Rikiavimas(int n, Filmas*& filmai);
void Isvedimas(int n, Filmas* filmai);

int main()
{
    int n;
    Filmas* filmai = nullptr;

    Nuskaitymas(n, filmai);
    Rikiavimas(n, filmai);
    Isvedimas(n, filmai);

    delete[] filmai;
    return 0;
}

void Nuskaitymas(int& n, Filmas*& filmai)
{
    ifstream duomenys("duomenys.txt");
    duomenys >> n;

    filmai = new Filmas[n];
    char name[26];
    int h, m;
    for(int i=0; i<n; i++)
    {
         duomenys.ignore(256, '\n');
         duomenys >> filmai[i].metai;
         duomenys.get(name, 26);
         filmai[i].pavadinimas=name;
         duomenys >> h >> m;
         filmai[i].laikas=h*60+m;
         duomenys >> filmai[i].ziurovai;
    }
    duomenys.close();
}

void Rikiavimas(int n, Filmas*& filmai)
{
    for(int i=0; i<n-1; i++)
    {
        int max=i;
        for(int j=i+1; j<n; j++)
        {
            if(filmai[j].laikas<filmai[max].laikas || (filmai[j].laikas==filmai[max].laikas && filmai[j].ziurovai>filmai[max].ziurovai))
            {
                max=j;
            }
        }
        if(max!=i)
        {
            swap(filmai[i], filmai[max]);
        }
    }
}

void Isvedimas(int n, Filmas* filmai)
{
    ofstream rezultatai("rezultatai.txt");

    for(int i=0; i<n; i++)
    {
        rezultatai << filmai[i].metai << " " << filmai[i].pavadinimas << " " << filmai[i].laikas/60 << " " << filmai[i].laikas%60 << " " << filmai[i].ziurovai << endl;
    }
    rezultatai.close();
}
