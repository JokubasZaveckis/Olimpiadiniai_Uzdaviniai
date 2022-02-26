#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>

using namespace std;

const char PUSE_1[13] = {'A','B','C','D','E','F','G','H','I','J','K','L','M'};
const char PUSE_2[13] = {'Z','Y','X','W','V','U','T','S','R','Q','P','O','N'};
const char PUSE_1_MAZOSIOS[13] = {'a','b','c','d','e','f','g','h','i','j','k','l','m'};
const char PUSE_2_MAZOSIOS[13] = {'z','y','x','w','v','u','t','s','r','q','p','o','n'};

struct Eilute
{
    string zodziai;
};

void Nuskaitymas(int& n, Eilute*& eilutes);
string Atbash(string zodis);
void Isvedimas(int n, Eilute vertimai[]);

int main()
{
    int n;
    Eilute* eilutes = nullptr;

    Nuskaitymas(n, eilutes);
    Eilute vertimai[n];

    for(int i=0; i<n; i++)
    {
        vertimai[i].zodziai=Atbash(eilutes[i].zodziai);
    }

    //vertimai[0].zodziai=Atbash(eilutes[0].zodziai);
    //vertimai[1].zodziai=Atbash(eilutes[1].zodziai);
    //cout << endl;
    //vertimai[2].zodziai=Atbash(eilutes[2].zodziai);

    Isvedimas(n, vertimai);

    delete[] eilutes;
    return 0;
}

void Nuskaitymas(int& n, Eilute*& eilutes)
{
    ifstream duomenys("duomenys.txt");
    duomenys >> n;
    eilutes = new Eilute[n];

    for(int i=0; i<n; i++)
    {
        duomenys >> eilutes[i].zodziai;
    }
    duomenys.close();
}

string Atbash(string zodis)
{
    //cout << zodis << endl;
    int b=0;
    while(!isdigit(zodis[b]) && !isspace(zodis[b]) && zodis[b]!=0)
    {
        b++;
    }
    //cout << b << endl;
    char vertimas[b];
    string Vertimas;
    for(int j=0; j<b; j++)
    {
        bool rasta=false;
        for(int i=0; i<13; i++)
        {
            if(zodis[j]==PUSE_1[i])
            {
                //cout << zodis[j] << " ";
                vertimas[j]=PUSE_2[i];
                rasta=true;
                //cout << vertimas[j] << " ";
            }
            if(zodis[j]==PUSE_1_MAZOSIOS[i])
            {
                //cout << zodis[j] << " ";
                rasta=true;
                vertimas[j]=PUSE_2_MAZOSIOS[i];
                //cout << vertimas[j] << " ";
            }
        }
        bool arRasta=false;
        if(rasta==false)
        {
            for(int i=0; i<13; i++)
            {
                if(zodis[j]==PUSE_2[i])
                {
                    //cout << zodis[j] << " ";
                    arRasta=true;
                    vertimas[j]=PUSE_1[i];
                    //cout << vertimas[j] << " ";
                }
                if(zodis[j]==PUSE_2_MAZOSIOS[i])
                {
                    //cout << zodis[j] << " ";
                    arRasta=true;
                    vertimas[j]=PUSE_1_MAZOSIOS[i];
                    //cout << vertimas[j] << " ";
                }
            }
        }
        if(arRasta==false && rasta==false)
        {
            //cout << zodis[j] << " ";
            vertimas[j]=zodis[j];
            //cout << vertimas[j] << " ";
        }
        //cout << vertimas[j] << " ";
    }
    vertimas[b]='\0';
    //cout << vertimas << endl;
    Vertimas = vertimas;
    return vertimas;
}

void Isvedimas(int n, Eilute vertimai[])
{
    ofstream rezultatai("rezultatai.txt");

    for(int i=0; i<n; i++)
    {
        cout << vertimai[i].zodziai << endl;
    }
    rezultatai.close();
}
