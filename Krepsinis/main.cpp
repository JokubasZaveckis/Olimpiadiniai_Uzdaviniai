#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>

using namespace std;

struct Krepsininkas
{
    int numeris;
    string vardas, pavarde;
    int baudos=0, dvitaskiai=0, tritaskiai=0;
    int metimai=0, pramestiMetimai=0;
    int taiklumas, taskai=0;
};

struct Taskai
{
    int numeris, metimas;
};

void Nuskaitymas(int& n, int& a, Krepsininkas*& krepsininkai, Taskai taskai[]);
void TaskuSkaiciavimas(int n, int a, Krepsininkas*& krepsininkai, Taskai taskai[]);
void MetimuTikslumas(int n, Krepsininkas*& krepsininkai);
void Rikiavimas(int n, Krepsininkas*& krepsininkai);
int DaugiausiaiTasku(int n, Krepsininkas*& krepsininkai);
int DaugiausiaiTritaskiu(int n, Krepsininkas*& krepsininkai);
int Taikliausias(int n, Krepsininkas*& krepsininkai);
void Isvedimas(int n, Krepsininkas* krepsininkai, int daugiausiaTasku, int tritaskiai, int tiksliausias);

int main()
{
    int n, a=0;
    Krepsininkas* krepsininkai = nullptr;
    Taskai taskai[100];
    Nuskaitymas(n, a, krepsininkai, taskai);
    TaskuSkaiciavimas(n, a, krepsininkai, taskai);
    //MetimuTikslumas(n, krepsininkai);
    //Rikiavimas(n, krepsininkai);
    int daugiausiaTasku = DaugiausiaiTasku(n, krepsininkai);
    /*int tritaskiai = DaugiausiaiTritaskiu(n, krepsininkai);
    int tiksliausias = Taikliausias(n, krepsininkai);
    Isvedimas(n, krepsininkai, daugiausiaTasku, tritaskiai, tiksliausias);*/

    delete[] krepsininkai;
    return 0;
}

void Nuskaitymas(int& n, int& a, Krepsininkas*& krepsininkai, Taskai taskai[])
{
    ifstream duomenys("duomenys.txt");
    krepsininkai = new Krepsininkas[12];
    /*char vard[26];
    for(int i=0; i<12; i++)
    {
        duomenys >> krepsininkai[i].numeris;
        duomenys.ignore(256, '\n');
        duomenys.get(vard, 26);
        krepsininkai[i].vardas=vard;
        cout << krepsininkai[i].numeris << endl;
    }
    duomenys.close();*/

    for(int i=0; i<12; i++)
    {
        duomenys >> krepsininkai[i].numeris >> krepsininkai[i].vardas >> krepsininkai[i].pavarde;
    }
    duomenys.close();

    ifstream df("taskai.txt");
    while(!df.eof())
    {
        df >> taskai[a].numeris >> taskai[a++].metimas;
    }
    df.close();
}

void TaskuSkaiciavimas(int n, int a, Krepsininkas*& krepsininkai, Taskai taskai[])
{
    for(int i=0; i<12; i++)
    {
        for(int j=0; j<a; j++)
        {
            //cout << krepsininkai[i].numeris << " " << taskai[j].numeris << endl;
            if(krepsininkai[i].numeris==taskai[j].numeris)
            {
                if(taskai[j].metimas==0)
                {
                    krepsininkai[i].metimai++;
                    krepsininkai[i].pramestiMetimai++;
                }
                else if(taskai[j].metimas==1)
                {
                    krepsininkai[i].metimai++;
                    krepsininkai[i].baudos++;
                    krepsininkai[i].taskai++;
                }
                else if(taskai[j].metimas==2)
                {
                    krepsininkai[i].metimai++;
                    krepsininkai[i].dvitaskiai++;
                    krepsininkai[i].taskai+=2;
                }
                else
                {
                    krepsininkai[i].metimai++;
                    krepsininkai[i].tritaskiai++;
                    krepsininkai[i].taskai+=3;
                }
            }
        }
    }
}

void MetimuTikslumas(int n, Krepsininkas*& krepsininkai)
{
    for(int i=0; i<n; i++)
    {
        krepsininkai[i].taiklumas=100-krepsininkai[i].pramestiMetimai*100/krepsininkai[i].metimai;
    }
}

void Rikiavimas(int n, Krepsininkas*& krepsininkai)
{
    for(int i=0; i<11; i++)
    {
        int max=i;
        for(int j=i+1; j<12; j++)
        {
            if(krepsininkai[j].numeris>krepsininkai[max].numeris)
            {
                max=j;
            }
        }
        if(max!=i)
        {
            swap (krepsininkai[i], krepsininkai[max]);
        }
    }
}

int DaugiausiaiTasku(int n, Krepsininkas*& krepsininkai)
{
    cout << "a" << endl;
    int max=0;
    for(int i=0; i<12; i++)
    {
        //cout << krepsininkai[i].taskai << " " << krepsininkai[max].taskai << endl;
        if(krepsininkai[i].taskai>krepsininkai[max].taskai)
            max=i;
    }
    return max;
}

int DaugiausiaiTritaskiu(int n, Krepsininkas*& krepsininkai)
{
    int max=0;
    for(int i=0; i<12; i++)
    {
        if(krepsininkai[i].tritaskiai>krepsininkai[max].tritaskiai)
            max=i;
    }
    return max;
}

int Taikliausias(int n, Krepsininkas*& krepsininkai)
{
    int max=0;
    for(int i=0; i<12; i++)
    {
        if(krepsininkai[i].taiklumas>krepsininkai[max].taiklumas)
            max=i;
    }
    return max;
}

void Isvedimas(int n, Krepsininkas* krepsininkai, int daugiausiaTasku, int tritaskiai, int tiksliausias)
{
    ofstream rezultatai("rezultatai.txt");

    for(int i=0; i<12; i++)
    {
        cout << krepsininkai[i].numeris << " " << krepsininkai[i].vardas << " " << krepsininkai[i].baudos << " " << krepsininkai[i].dvitaskiai << " " << krepsininkai[i].tritaskiai << " " << krepsininkai[i].pramestiMetimai << " " <<  krepsininkai[i].taiklumas << endl;
    }
    cout << "Daugiausia tasku: " << krepsininkai[daugiausiaTasku].numeris << " " << krepsininkai[daugiausiaTasku].vardas << " " << krepsininkai[daugiausiaTasku].taskai << endl;
    cout << "Daugiausia tritaskiu: " << krepsininkai[tritaskiai].numeris << " " << krepsininkai[tritaskiai].vardas << " " << krepsininkai[tritaskiai].tritaskiai << endl;
    cout << "Taikliausias: " << krepsininkai[tiksliausias].numeris << " " << krepsininkai[tiksliausias].vardas << " " << krepsininkai[tiksliausias].taiklumas << endl;
    rezultatai.close();
}
