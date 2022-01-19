#include <iostream>
#include <iomanip>
#include <fstream>
#include <iomanip>

using namespace std;

struct Dalyviai
{
    string* Pavadinimas = nullptr;
    int* Vertinimas = nullptr;
    int* regionas = nullptr;


    ~Dalyviai()
    {
        delete[] Vertinimas;
        delete[] Pavadinimas;
        delete[] regionas;
    }
};

void Nuskaitymas(int& n, int& k, Dalyviai& dalyviai);
void VisuRegionuPridejimas(int n, int& k, Dalyviai& dalyviai);
void Rikiavimas(int k, Dalyviai& dalyviai);
void Isvedimas(int k, Dalyviai dalyviai);

int main()
{
   int n, k;
   Dalyviai dalyviai;

   Nuskaitymas(n, k, dalyviai);
   VisuRegionuPridejimas(n, k, dalyviai);
   Rikiavimas(k, dalyviai);
   Isvedimas(k, dalyviai);
   return 0;
}

void Nuskaitymas(int&n, int& k, Dalyviai& dalyviai)
{
    ifstream duomenys("duomenys.txt");
    duomenys >> n >> k;
    for(int i=0; i<n; i++)
    {
        dalyviai.Pavadinimas = new string[k];
        dalyviai.Vertinimas = new int[k];
        dalyviai.regionas = new int[k];
    }

    for(int i=0; i<k; i++)
    {
        duomenys >> dalyviai.Pavadinimas[i] >> dalyviai.Vertinimas[i];
        dalyviai.regionas[i] = 1;
    }
    duomenys.close();
}

void VisuRegionuPridejimas(int n, int& k, Dalyviai& dalyviai)
{
    ifstream duomenys("duomenys.txt");
    int a;
    duomenys >> n >> k;
    for(int i=0; i<k; i++)
    {
        duomenys >> dalyviai.Pavadinimas[i] >> dalyviai.Vertinimas[i];
    }
    for(int i=1; i<n; i++)
    {
        duomenys >> a;
        for(int j=k; j<k+a; j++)
        {
            cout << k+a << endl;
            duomenys >> dalyviai.Pavadinimas[j] >> dalyviai.Vertinimas[j];
            cout << "a " << dalyviai.Pavadinimas[j] << " " << dalyviai.Vertinimas[j] << endl;
        }
        dalyviai.regionas[i]=i+1;
        k+=a;
    }
    duomenys.close();
}

void Rikiavimas(int k, Dalyviai& dalyviai)
{
    for(int i=0; i<k-1; i++)
    {
        int max=i;
        for(int j=i+1; j<k; j++)
        {
            if(dalyviai.Vertinimas[j]>dalyviai.Vertinimas[max])
            {
                swap(dalyviai.Vertinimas[j], dalyviai.Vertinimas[max]);
                swap(dalyviai.regionas[j], dalyviai.regionas[max]);
                swap(dalyviai.Pavadinimas[j], dalyviai.Pavadinimas[max]);
            }
        }
    }
}

void Isvedimas(int k, Dalyviai dalyviai)
{
    for(int i=0; i<k; i++)
    {
        cout << dalyviai.Pavadinimas[i] << " " << dalyviai.regionas[i] << endl;
    }
}
