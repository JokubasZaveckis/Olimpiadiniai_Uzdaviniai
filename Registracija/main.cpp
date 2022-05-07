#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

struct Asmuo
{
    char vardas[26];
    long long numeris;
    bool arTinka=false;
};

void Nuskaitymas(int& n, Asmuo*& asmenys);
int SumosSkaiciavimas(int numeris);
void TinkamumoIeskojimas(int n, Asmuo*& asmenys, int& kiekTiko);
void Ismetimas(int& n, Asmuo*& asmenys, Asmuo*& pasalinti, int kiekTiko);
void Isvedimas(int n, Asmuo*& asmenys, Asmuo*& pasalinti, int kiekPasalino);

int main()
{
    int n, kiekTiko=0;

    Asmuo* asmenys = nullptr;
    Asmuo* pasalinti = nullptr;

    Nuskaitymas(n, asmenys);
    TinkamumoIeskojimas(n, asmenys, kiekTiko);
    int kiekPasalino=n-kiekTiko;
    Ismetimas(n, asmenys, pasalinti, kiekTiko);
    Isvedimas(n, asmenys, pasalinti, kiekPasalino);

    delete[] asmenys;
    delete[] pasalinti;
    return 0;
}

void Nuskaitymas(int& n, Asmuo*& asmenys)
{
    ifstream duomenys("duomenys.txt");
    duomenys >> n;
    asmenys = new Asmuo[n];
    for(int i=0; i<n; i++)
    {
        duomenys.ignore(256, '\n');
        duomenys.get(asmenys[i].vardas, 26);
        duomenys >> asmenys[i].numeris;
    }
    duomenys.close();
}

int SumosSkaiciavimas(long long numeris)
{
    int suma=0;
    long long liekana = 10000000000;
    int skaitmuo=0;

    skaitmuo=numeris/liekana;
    suma+=skaitmuo;

    for(int i=0; i<10; i++)
    {
        liekana/=10;
        skaitmuo=numeris/liekana%10;

        if(i%2==0)
        {
            skaitmuo*=2;
        }

        if(skaitmuo>=10)
        {
            suma+=skaitmuo/10;
            suma+=skaitmuo%10;
        }
        else
        {
            suma+=skaitmuo;
        }
    }
    return suma;
}

void TinkamumoIeskojimas(int n, Asmuo*& asmenys, int& kiekTiko)
{
    for(int i=0; i<n; i++)
    {
        int suma = SumosSkaiciavimas(asmenys[i].numeris);
        if(suma%10==0)
        {
            asmenys[i].arTinka=true;
            kiekTiko++;
        }
    }
}

void Ismetimas(int& n, Asmuo*& asmenys, Asmuo*& pasalinti, int kiekTiko)
{
    pasalinti = new Asmuo[n-kiekTiko];
    int a=0;
    for(int i=0; i<n; i++)
    {
        if(asmenys[i].arTinka==false)
        {
            pasalinti[a++]=asmenys[i];
            for(int j=i+1; j<n; j++)
            {
                asmenys[i]=asmenys[j];
            }
            n--;
        }
    }
}

void Isvedimas(int n, Asmuo*& asmenys, Asmuo*& pasalinti, int kiekPasalino)
{
    ofstream rezultatai("rezultatai.txt");

    for(int i=0; i<n; i++)
    {
        rezultatai << asmenys[i].vardas << " " << asmenys[i].numeris << endl;
    }
    rezultatai << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    for(int i=0; i<kiekPasalino; i++)
    {
        rezultatai << pasalinti[i].vardas << " " << pasalinti[i].numeris << endl;
    }
    rezultatai.close();
}
