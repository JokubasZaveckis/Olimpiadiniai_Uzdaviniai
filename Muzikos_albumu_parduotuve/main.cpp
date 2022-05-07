#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>

using namespace std;

struct Albumas
{
    char pavadinimas[17];
    char autorius[25];
    int kaina=5, kiekis;
};

struct Operacija:Albumas
{
    string simbolis;
};

void Nuskaitymas(int& n, int& k, Albumas albumai[], Operacija*& operacijos);

int main()
{
    int n, k;
    Albumas albumai[100];
    Operacija* operacijos = nullptr;

    Nuskaitymas(n, k, albumai, operacijos);
    cout << n  << " " << k << endl;
    for(int i=0; i<k; i++)
    {
        if(operacijos[i].simbolis =="+")
        {
            //cout << operacijos[i].pavadinimas << " " << operacijos[i].kiekis << endl;
        }
    }

    return 0;
}

void Nuskaitymas(int& n, int& k, Albumas albumai[], Operacija*& operacijos)
{
    ifstream duomenys("duomenys.txt");
    duomenys >> n;
    for(int i=0; i<n; i++)
    {
        duomenys.ignore(256, '\n');
        duomenys.get(albumai[i].pavadinimas, 17);
        duomenys.get(albumai[i].autorius, 25);
        duomenys >> albumai[i].kaina >> albumai[i].kiekis;
    }
    duomenys.close();

    ifstream df("operacijos.txt");
    df >> k;
    operacijos = new Operacija[k];
    for(int i=0; i<k; i++)
    {
        //duomenys.ignore(256, '\n');
        df >> operacijos[i].simbolis;
        cout << operacijos[i].simbolis << endl;
        if(operacijos[i].simbolis == "+")
        {
            df.get(operacijos[i].pavadinimas, 17);
            cout << operacijos[i].pavadinimas << endl;
            df.get(operacijos[i].autorius, 25);
            df >> operacijos[i].kaina >> operacijos[i].kiekis;
        }
        else
        {
            df.get(operacijos[i].pavadinimas, 17);
            df >> operacijos[i].kiekis;
        }
    }
    df.close();
}

void OperacijuVykdymas(int& n, int k, Albumas albumai[], Operacija*& operacijos)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<k; j++)
        {
            bool rasta=false;
            if(operacijos[j].simbolis=="+" && operacijos[j].pavadinimas == albumai[i].pavadinimas)
            {
                albumai[i].kiekis+=operacijos[j].kiekis;
                rasta=true;
            }

            if(rasta==false && operacijos[j].simbolis=="+")
            {
                albumai[++n]=operacijos[j];
            }

            if(operacijos[j].simbolis=="-" && albumai[i].kiekis-operacijos[i].kiekis>=0 && operacijos[j].pavadinimas == albumai[i].pavadinimas)
            {
                albumai[i].kiekis-=operacijos[j].kiekis;
            }
            else if(operacijos[j].simbolis=="-" && albumai[i].kiekis-operacijos[i].kiekis<0 && operacijos[j].pavadinimas == albumai[i].pavadinimas)
            {
                while(albumai[i].kiekis>0)
                {
                    albumai[i].kiekis--;
                }
            }
        }
    }
}
