#include <iostream>
#include <iomanip>
#include <fstream>
#include <iomanip>

using namespace std;

struct Dalyvis
{
    string Pavadinimas;
    int Taskai;
    int Regionas;
};

void Nuskaitymas(int&n, int& k, Dalyvis dalyviai[], ifstream& duomenys);
void VisuRegionuPridejimas(int n, int& k, Dalyvis dalyviai[], ifstream& duomenys);
int Iterpimas(int n, Dalyvis dalyviai[], Dalyvis naujasDalyvis);
void VienoElementoIterpimas(int& n, Dalyvis dalyviai[], int vieta, Dalyvis naujasDalyvis);
void Isvedimas(int n, Dalyvis dalyviai[]);

int main()
{
    int n, k;
    Dalyvis dalyviai[400];

    ifstream duomenys("duomenys.txt");

    Nuskaitymas(n, k, dalyviai, duomenys);
    VisuRegionuPridejimas(n, k, dalyviai, duomenys);

    duomenys.close();

    Isvedimas(k, dalyviai);

    return 0;
}

void Nuskaitymas(int&n, int& k, Dalyvis dalyviai[], ifstream& duomenys)
{
    duomenys >> n >> k;

    for(int i=0; i<k; i++)
    {
        duomenys >> dalyviai[i].Pavadinimas >> dalyviai[i].Taskai;
        //cout << dalyviai[i].Pavadinimas << " " << dalyviai[i].Taskai << endl;
        dalyviai[i].Regionas=1;
    }
}

void VisuRegionuPridejimas(int n, int& k, Dalyvis dalyviai[], ifstream& duomenys)
{
    int a, b, c=n;
    for(int i=1; i<c; i++)
    {
        Dalyvis naujasDalyvis;
        duomenys >> a;
        for(int j=0; j<a; j++)
        {
            duomenys >> naujasDalyvis.Pavadinimas >> naujasDalyvis.Taskai;
            //cout << naujasDalyvis.Pavadinimas << endl;
            naujasDalyvis.Regionas = i+1;
            b = Iterpimas(k, dalyviai, naujasDalyvis);
            //cout << b << endl;
            VienoElementoIterpimas(k, dalyviai, b, naujasDalyvis);
            //cout << a << endl;
        }
    }
}

int Iterpimas(int n, Dalyvis dalyviai[], Dalyvis naujasDalyvis)
{
    for(int i=0; i<n; i++)
    {
        if(naujasDalyvis.Taskai>dalyviai[i].Taskai)
        {
            return i;
        }
    }
    return n;
}

void VienoElementoIterpimas(int& n, Dalyvis dalyviai[], int vieta, Dalyvis naujasDalyvis)
{
    for(int i=n; i>vieta; i--)
    {
        dalyviai[i]=dalyviai[i-1];
    }
    dalyviai[vieta]=naujasDalyvis;
    //cout << dalyviai[vieta].Pavadinimas << " " <<naujasDalyvis.Pavadinimas << endl;
    n++;
}

void Isvedimas(int n, Dalyvis dalyviai[])
{
    for(int i=0; i<n; i++)
    {
        cout << dalyviai[i].Pavadinimas << " " << dalyviai[i].Taskai << " " << dalyviai[i].Regionas << endl;
    }
}
