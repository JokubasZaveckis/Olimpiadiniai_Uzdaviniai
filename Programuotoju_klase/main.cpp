#include <iostream>
#include <iomanip>
#include <fstream>
#include <bits/stdc++.h>
#include <string>

using namespace std;

struct Grupe
{
    string vardas;
    int prioritetoNumeris;
};

void Nuskaitymas(int& n, int& p, Grupe*& norintys);
void Rikiavimas(int n, Grupe*& norintys);
void Atrinkimas(int p, Grupe*& norintys, Grupe*& priimti);
void MokiniuAtrinkimas(int n, int p, Grupe*& norintys, Grupe*& priimti);
void Atranka(int& n, int p, Grupe*& norintys);
void M_Atrinkimas(int n, int p, Grupe*& norintys);
void Isvedimas(int p, Grupe*& priimti);

int main()
{
    int n, p;
    Grupe* norintys = nullptr;
    Grupe* priimti = nullptr;

    Nuskaitymas(n, p, norintys);
    priimti = new Grupe[p];
    Rikiavimas(n, norintys);
    //Atrinkimas(p, norintys, priimti);
    //MokiniuAtrinkimas(n, p, norintys, priimti);
    //Atranka(n, p, norintys);
    M_Atrinkimas(n, p, norintys);

    //priimti[0].prioritetoNumeris=0;
    //erase.priimti[0].vardas;
    Isvedimas(p, norintys);

    delete[] norintys;
    delete[] priimti;
    return 0;
}

void Nuskaitymas(int& n, int& p, Grupe*& norintys)
{
    ifstream duomenys("duomenys.txt");
    duomenys >> p >> n;
    norintys = new Grupe[n];
    for(int i=0; i<n; i++)
    {
        duomenys >> norintys[i].vardas >> norintys[i].prioritetoNumeris;
    }
    duomenys.close();
}

void Rikiavimas(int n, Grupe*& norintys)
{
    for(int i=0; i<n-1; i++)
    {
        int max=i;
        for(int j=i+1; j<n; j++)
        {
            if(norintys[j].prioritetoNumeris<norintys[max].prioritetoNumeris)
            {
                max=j;
            }
        }
        if(max!=i)
        {
            swap(norintys[i], norintys[max]);
        }
    }
}

void Atranka(int& n, int p, Grupe*& norintys)
{
    while(n!=p)
    {
        int max=0;
        for(int i=0; i<n; i++)
        {
            if(norintys[i].prioritetoNumeris>norintys[max].prioritetoNumeris)
            {
                max=i;
            }
        }
        for(int i=max; i<n-1; i++)
        {
            norintys[max]=norintys[i+1];
        }
        n--;
    }
}

void M_Atrinkimas(int n, int p, Grupe*& norintys)
{

    while(n!=p)
    {
        int max=0;
        for(int i=0; i<n; i++)
        {
            if(norintys[i].prioritetoNumeris>norintys[max].prioritetoNumeris)
            {
                max=i;
            }
        }
        Grupe* kopijos = new Grupe[n-1];
        int kiek=0;
        for(int i=0; i<n; i++)
        {

            if(i!=max)
            {
                kopijos[kiek++]=norintys[i];
            }
        }
        n--;
        delete[] norintys;
        norintys=kopijos;
    }
}

void Atrinkimas(int p, Grupe*& norintys, Grupe*& priimti)
{
    //cout << p << endl;
    for(int i=0; i<p; i++)
    {
        priimti[i]=norintys[i];
    }
}

void MokiniuAtrinkimas(int n, int p, Grupe*& norintys, Grupe*& priimti)
{
    int kiek=0;
    for(int i=0; i<n && kiek<=p; i++)
    {
        if(norintys[i].prioritetoNumeris==1)
        {
            priimti[kiek]=norintys[i];
            kiek++;
        }
    }

    for(int i=0; i<n && kiek<p; i++)
    {
        if(norintys[i].prioritetoNumeris==2)
        {
            priimti[kiek]=norintys[i];
            kiek++;
        }
    }

    for(int i=0; i<n && kiek<p; i++)
    {
        if(norintys[i].prioritetoNumeris==3)
        {
            priimti[kiek]=norintys[i];
            kiek++;
        }
    }
}

void Isvedimas(int p, Grupe*& priimti)
{
    ofstream rezultatai("rezultatai.txt");
    rezultatai << "Sudarytos klases mokiniu sarasas: " << endl;
    for(int i=0; i<p; i++)
    {
        rezultatai << priimti[i].vardas << " " << priimti[i].prioritetoNumeris << endl;
    }
    rezultatai.close();
}
