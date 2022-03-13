#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>

using namespace std;

struct Albumas
{
    char Pavadinimas[21];
    int metai, valandos, minutes;
    int kiekKartuPraklausyta;
};

void Nuskaitymas(int& n, Albumas*& albumai);
int AlbumuTrukme(int n, Albumas* albumai);
float PerklausuVidurkis(int n, Albumas* albumai);
void Rikiavimas(int n, Albumas* albumai);
void Isvedimas(int n, Albumas* albumai, int laikas, float vidurkis);

int main()
{
    int n;
    Albumas* albumai = nullptr;

    Nuskaitymas(n, albumai);
    int laikas = AlbumuTrukme(n, albumai);
    float vidurkis = PerklausuVidurkis(n, albumai);
    Rikiavimas(n, albumai);
    Isvedimas(n, albumai, laikas, vidurkis);

    delete[] albumai;
    return 0;
}

void Nuskaitymas(int& n, Albumas*& albumai)
{
    ifstream duomenys("duomenys.txt");
    duomenys >> n;

    albumai = new Albumas[n];

    for(int i=0; i<n; i++)
    {
        duomenys.ignore(256, '\n');
        duomenys.get(albumai[i].Pavadinimas, 21);
        duomenys >> albumai[i].metai >> albumai[i].valandos >> albumai[i].minutes >> albumai[i].kiekKartuPraklausyta;
    }
    duomenys.close();
}

int AlbumuTrukme(int n, Albumas* albumai)
{
    int laikas=0;
    for(int i=0; i<n; i++)
    {
        laikas += albumai[i].valandos*60+albumai[i].minutes;
    }
    return laikas;
}

float PerklausuVidurkis(int n, Albumas* albumai)
{
    int suma=0;
    for(int i=0; i<n; i++)
    {
        suma+=albumai[i].kiekKartuPraklausyta;
    }
    return suma*1.0/n;
}

void Rikiavimas(int n, Albumas* albumai)
{
    for(int i=0; i<n-1; i++)
    {
        int max=i;
        for(int j=i+1; j<n; j++)
        {
            if(albumai[j].kiekKartuPraklausyta>albumai[max].kiekKartuPraklausyta)
            {
                max=j;
            }
        }
        if(max!=i)
        {
            swap(albumai[i], albumai[max]);
        }
    }
}

void Isvedimas(int n, Albumas* albumai, int laikas, float vidurkis)
{
    ofstream rezultatai("rezultatai.txt");
    cout << laikas/60 << " " << laikas%60 << endl;
    cout << fixed << setprecision(2) << vidurkis << endl;
    for(int i=0; i<n; i++)
    {
        cout << albumai[i].Pavadinimas << " " << albumai[i].metai << endl;
    }
    rezultatai.close();
}
