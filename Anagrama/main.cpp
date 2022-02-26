#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>

using namespace std;

struct Zodis
{
    string zodis;
    int kiekRaidziu=0;
};

void Nuskaitymas(Zodis zodziai[]);
void Isvedimas(Zodis zodziai[]);
void KiekRaidziuZodyje(Zodis zodziai[]);
void Rikiavimas(Zodis& zodis);
bool ArAnagrama(Zodis zodziai[]);

int main()
{
    Zodis zodziai[2];

    Nuskaitymas(zodziai);
    KiekRaidziuZodyje(zodziai);
    Rikiavimas(zodziai[0]);
    Rikiavimas(zodziai[1]);
    //cout << zodziai[0].zodis << " " << zodziai[1].zodis << endl;
    Isvedimas(zodziai);

    return 0;
}

void Nuskaitymas(Zodis zodziai[])
{
    ifstream duomenys("duomenys.txt");
    for(int i=0; i<2; i++)
    {
         duomenys >> zodziai[i].zodis;
    }
    duomenys.close();
}

void KiekRaidziuZodyje(Zodis zodziai[])
{
    for(int i=0; i<2; i++)
    {
        while(isalpha(zodziai[i].zodis[zodziai[i].kiekRaidziu++]));
        //{

        //}
        //zodziai[i].kiekRaidziu=zodziai[i].zodis.length();
    }
}

void Rikiavimas(Zodis& zodis)
{
    for(int i=0; i<zodis.kiekRaidziu-1; i++)
    {
        int max=i;
        for(int j=i+1; j<zodis.kiekRaidziu; j++)
        {
            //cout << zodis.zodis[j] << " " << zodis.zodis[max] << endl;
            if(zodis.zodis[j]<zodis.zodis[max]) // kur dingsta t pasukus zenkla
            {
                //cout << "a" << endl;
                max=j;
            }
        }
        if(max!=i)
        {
            swap(zodis.zodis[i], zodis.zodis[max]);
        }
    }
}

bool ArAnagrama(Zodis zodziai[])
{
    if(zodziai[0].zodis==zodziai[1].zodis && zodziai[0].kiekRaidziu==zodziai[1].kiekRaidziu)
        return true;
    return false;
}

void Isvedimas(Zodis zodziai[])
{
    ofstream rezultatai("rezultatai.txt");
    if(ArAnagrama(zodziai))
    {
        cout << "taip" << endl;
    }
    else rezultatai << "ne" << endl;
    rezultatai.close();
}
