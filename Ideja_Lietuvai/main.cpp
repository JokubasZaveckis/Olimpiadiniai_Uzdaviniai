#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>

using namespace std;

struct Ideja
{
    string aprasymas;
    int kiekPrabalsuota;
};

struct Grupe
{
    string pavadinimas;
    int k, max;
    Ideja idejos[30];
};

void Nuskaitymas(int& n, Grupe*& grupes);
int DidziausiosReiksmesPaieska(int n, Grupe*& grupes, int skaicius=0, int skaicius2=0);
void Isvedimas(int n, Grupe* grupes, int didziausiosReiksmes[]);

int main()
{
    int n, didziausiosReiksmes[3];
    Grupe* grupes = nullptr;
    Nuskaitymas(n, grupes);

    didziausiosReiksmes[0] = DidziausiosReiksmesPaieska(n, grupes);
    didziausiosReiksmes[1] = DidziausiosReiksmesPaieska(n, grupes, didziausiosReiksmes[0]);
    didziausiosReiksmes[2] = DidziausiosReiksmesPaieska(n, grupes, didziausiosReiksmes[1], didziausiosReiksmes[0]);


    Isvedimas(n, grupes, didziausiosReiksmes);

    delete[] grupes;
    return 0;
}

void Nuskaitymas(int& n, Grupe*& grupes)
{
    ifstream duomenys("duomenys.txt");
    duomenys >> n;
    grupes = new Grupe[n];

    for(int i=0; i<n; i++)
    {
        duomenys.ignore(256, '\n');
        duomenys >> grupes[i].pavadinimas >> grupes[i].k;
        for(int j=0; j<grupes[i].k; j++)
        {
            duomenys >> grupes[i].idejos[j].aprasymas >> grupes[i].idejos[j].kiekPrabalsuota;
        }
    }
    duomenys.close();
}

int DidziausiosReiksmesPaieska(int n, Grupe*& grupes, int skaicius, int skaicius2)
{
    int a=0, b=0;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<grupes[i].k; j++)
        {
            if(grupes[i].idejos[j].kiekPrabalsuota>grupes[b].idejos[a].kiekPrabalsuota && grupes[i].idejos[j].kiekPrabalsuota!=skaicius && grupes[i].idejos[j].kiekPrabalsuota!=skaicius2)
            {
                 a = j;
                 b = i;
            }
        }
    }
    return grupes[b].idejos[a].kiekPrabalsuota;
}

void Isvedimas(int n, Grupe* grupes, int didziausiosReiksmes[]) // savotiskas rikiavimas, jei kurti atskira funkcija kiekvienam tikrinimui, ar atitiks paskutini reikalavima
{
    ofstream rezultatai("rezultatai.txt");

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<grupes[i].k; j++)
        {
            if(grupes[i].idejos[j].kiekPrabalsuota==didziausiosReiksmes[0])
            {
                cout << grupes[i].pavadinimas << " " << grupes[i].idejos[j].aprasymas << " " << grupes[i].idejos[j].kiekPrabalsuota << endl;
            }
        }
    }
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<grupes[i].k; j++)
        {
            if(grupes[i].idejos[j].kiekPrabalsuota==didziausiosReiksmes[1])
            {
                cout << grupes[i].pavadinimas << " " << grupes[i].idejos[j].aprasymas << " " << grupes[i].idejos[j].kiekPrabalsuota << endl;
            }
        }
    }
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<grupes[i].k; j++)
        {
            if(grupes[i].idejos[j].kiekPrabalsuota==didziausiosReiksmes[2])
            {
                cout << grupes[i].pavadinimas << " " << grupes[i].idejos[j].aprasymas << " " << grupes[i].idejos[j].kiekPrabalsuota << endl;
            }
        }
    }
    rezultatai.close();
}
