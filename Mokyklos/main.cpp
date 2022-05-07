#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>

using namespace std;

struct Mokykla
{
    string Pavadinimas;
    int mokiniuSkaicius, kompiuteriuSkaicius;
    bool arGauna=false;
    int tenka, tenkaKompiuteriu;
};

void Nuskaitymas(int& n, int& kompiuteriai, Mokykla*& mokyklos);
void MokyklosAtitikimas(int n, int kompiuteriai, Mokykla*& mokyklos);
void KompiuteriuDalinimas(int n, int& kompiuteriai, Mokykla*& mokyklos);
bool ArDarDalinti(int n, Mokykla*& mokyklos);
int KompiuteriuTrukumas(int n, int& kompiuteriai, Mokykla*& mokyklos);
void Rikiavimas(int n, Mokykla*& mokyklos);
void Isvedimas(int n, int kompiuteriai, int truksta, Mokykla*& mokyklos);

int main()
{
    int n, kompiuteriai;
    Mokykla* mokyklos = nullptr;
    Nuskaitymas(n, kompiuteriai, mokyklos);
    MokyklosAtitikimas(n, kompiuteriai, mokyklos);
    int truksta = KompiuteriuTrukumas(n, kompiuteriai, mokyklos);
    Isvedimas(n, kompiuteriai, truksta, mokyklos);

    delete[] mokyklos;
    return 0;
}

void Nuskaitymas(int& n, int& kompiuteriai, Mokykla*& mokyklos)
{
    ifstream duomenys("duomenys.txt");
    duomenys >> kompiuteriai >> n;
    mokyklos = new Mokykla[n];

    char vardas[16];
    for(int i=0; i<n; i++)
    {
        duomenys.ignore(256, '\n');
        duomenys.get(vardas, 16);
        mokyklos[i].Pavadinimas = vardas;
        duomenys >> mokyklos[i].mokiniuSkaicius >> mokyklos[i].kompiuteriuSkaicius;
    }
    duomenys.close();
}

void MokyklosAtitikimas(int n, int kompiuteriai, Mokykla*& mokyklos)
{
    for(int i=0; i<n; i++)
    {
        mokyklos[i].tenka = mokyklos[i].kompiuteriuSkaicius/(mokyklos[i].mokiniuSkaicius/10);
    }
}

bool ArDarDalinti(int n, Mokykla*& mokyklos)
{
    for(int i=0; i<n; i++)
    {
        if(mokyklos[i].tenka<5)
        {
            return true;
        }
    }
    return false;
}

void KompiuteriuDalinimas(int n, int& kompiuteriai, Mokykla*& mokyklos)
{

    for(int i=0; kompiuteriai>0 && ArDarDalinti(n, mokyklos); i++)
    {
        if(mokyklos[i].tenka<5)
        {
            if(mokyklos[i].mokiniuSkaicius/10<=kompiuteriai)
            {
                mokyklos[i].kompiuteriuSkaicius+=mokyklos[i].mokiniuSkaicius/10;
                mokyklos[i].tenka++;
                kompiuteriai-=mokyklos[i].mokiniuSkaicius/10;
            }
            else
            {
                mokyklos[i].kompiuteriuSkaicius+=kompiuteriai;
                kompiuteriai = 0;
                mokyklos[i].tenka = mokyklos[i].kompiuteriuSkaicius/(mokyklos[i].mokiniuSkaicius/10);
            }
        }
        if(i==n-1)
        {
            i=-1;
        }
    }

    for(int i=0; i<n && kompiuteriai>0; i++)
    {
        if(mokyklos[i].tenka==6)
        {
            if(mokyklos[i].mokiniuSkaicius/10<=kompiuteriai)
            {
                mokyklos[i].kompiuteriuSkaicius+=mokyklos[i].mokiniuSkaicius/10;
                mokyklos[i].tenka++;
                kompiuteriai-=mokyklos[i].mokiniuSkaicius/10;
            }
            else
            {
                mokyklos[i].kompiuteriuSkaicius+=kompiuteriai;
                kompiuteriai = 0;
                mokyklos[i].tenka = mokyklos[i].kompiuteriuSkaicius/(mokyklos[i].mokiniuSkaicius/10);
            }
        }
    }
}

int KompiuteriuTrukumas(int n, int& kompiuteriai, Mokykla*& mokyklos)
{
    int truksta = 0;
    for(int i=0; i<n; i++)
    {
        if(mokyklos[i].tenka<5)
        {
            truksta += mokyklos[i].mokiniuSkaicius/10;
        }
    }
    return truksta;
}

void Rikiavimas(int n, Mokykla*& mokyklos)
{
    for(int i=0; i<n-1; i++)
    {
        int max=i;
        for(int j=0; j<n; j++)
        {
            if(mokyklos[j].kompiuteriuSkaicius>mokyklos[max].kompiuteriuSkaicius || mokyklos[j].kompiuteriuSkaicius==mokyklos[max].kompiuteriuSkaicius && mokyklos[i].Pavadinimas > mokyklos[max].Pavadinimas)
            {
                max=j;
            }
        }
        if(max!=i)
        {
            swap(mokyklos[i], mokyklos[max]);
        }
    }
}

void Isvedimas(int n, int kompiuteriai, int truksta, Mokykla*& mokyklos)
{
    ofstream rezultatai("rezultatai.txt");

    for(int i=0; i<n; i++)
    {
        cout << mokyklos[i].Pavadinimas << " " << mokyklos[i].mokiniuSkaicius << " " << mokyklos[i].kompiuteriuSkaicius << " " << mokyklos[i].tenka << endl;
    }
    cout << endl;
    KompiuteriuDalinimas(n, kompiuteriai, mokyklos);
    //Rikiavimas(n, mokyklos);
    for(int i=0; i<n; i++)
    {
        cout << mokyklos[i].Pavadinimas << " " << mokyklos[i].mokiniuSkaicius << " " <<  mokyklos[i].kompiuteriuSkaicius << " " << mokyklos[i].tenka << endl;
    }
    cout << kompiuteriai << endl;
    cout << truksta << endl;
    rezultatai.close();
}
