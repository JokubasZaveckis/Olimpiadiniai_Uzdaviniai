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
};

void Nuskaitymas(int& n, int& kompiuteriai, Mokykla*& mokyklos);
void MokyklosAtitikimas(int n, int kompiuteriai, Mokykla*& mokyklos);
void Isvedimas(int n, int kompiuteriai, Mokykla* mokyklos);

int main()
{
    int n, kompiuteriai;
    Mokykla* mokyklos = nullptr;
    cout << false << " " << true << endl;
    Nuskaitymas(n, kompiuteriai, mokyklos);
    MokyklosAtitikimas(n, kompiuteriai, mokyklos);
    Isvedimas(n, kompiuteriai, mokyklos);

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
        int mokiniai = mokyklos[i].mokiniuSkaicius;
        int mokyklosKompiuteriai = mokyklos[i].kompiuteriuSkaicius;
        while(mokiniai-10>=0 || mokyklosKompiuteriai-5>=0)
        {
            mokiniai-=10;
            mokyklosKompiuteriai-=5;
        }
    }
}

void Isvedimas(int n, int kompiuteriai, Mokykla* mokyklos)
{
    ofstream rezultatai("rezultatai.txt");

    for(int i=0; i<n; i++)
    {

    }
    rezultatai.close();
}
