#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <cmath>

using namespace std;

struct Mokinys
{
    char vardas[16];
    int* pazymiai = nullptr;
    int balas;

    ~Mokinys()
    {
        delete[] pazymiai;
    }
};

void Nuskaitymas(int& n, int& k, float*& koficientai, Mokinys*& mokiniai);
void BaluSkaiciavimas(int n, int k, float* koficientai, Mokinys*& mokiniai);
int BaluVidurkis(int n, Mokinys* mokiniai);
int GeriausiasBalas(int n, Mokinys* mokiniai);
int BlogiausiasBalas(int n, Mokinys* mokiniai);
int kiekTeigiamu(int n, Mokinys* mokiniai);
void GeriausiuArBlogiausiuIsvedimas(int n, int kriterijus, Mokinys* mokiniai);
void Isvedimas(int n, Mokinys* mokiniai, int vidurkis, int geriausias, int blogiausias, int kiek);

int main()
{
    int n, k;
    float* koficientai = nullptr;
    Mokinys* mokiniai = nullptr;

    Nuskaitymas(n, k,  koficientai, mokiniai);
    BaluSkaiciavimas(n, k, koficientai, mokiniai);
    int vidurkis = BaluVidurkis(n, mokiniai);
    int geriausias = GeriausiasBalas(n, mokiniai);
    int blogiausias = BlogiausiasBalas(n, mokiniai);
    int kiek = kiekTeigiamu(n, mokiniai);
    Isvedimas(n, mokiniai, vidurkis, geriausias, blogiausias, kiek);

    delete[] mokiniai;
    return 0;
}

void Nuskaitymas(int& n, int& k, float*& koficientai, Mokinys*& mokiniai)
{
    ifstream duomenys("duomenys.txt");
    duomenys >> n >> k;

    koficientai = new float[k];
    mokiniai = new Mokinys[n];

    for(int i=0; i<n; i++)
    {
        mokiniai[i].pazymiai = new int[k];
    }

    for(int i=0; i<k; i++)
    {
        duomenys >> koficientai[i];
    }
    for(int i=0; i<n; i++)
    {
        duomenys.ignore(256, '\n');
        duomenys.get(mokiniai[i].vardas, 16);
        for(int j=0; j<k; j++)
        {
            duomenys >> mokiniai[i].pazymiai[j];
        }
    }
    duomenys.close();
}

void BaluSkaiciavimas(int n, int k, float* koficientai, Mokinys*& mokiniai)
{
    for(int i=0; i<n; i++)
    {
        float suma=0;
        for(int j=0; j<k; j++)
        {
            suma+=mokiniai[i].pazymiai[j]*koficientai[j];
        }
        mokiniai[i].balas=round(suma);
    }
}

int BaluVidurkis(int n, Mokinys* mokiniai)
{
    float suma=0;
    for(int i=0; i<n; i++)
    {
        suma+=mokiniai[i].balas;
    }
    return round(suma/n);
}

int GeriausiasBalas(int n, Mokinys* mokiniai)
{
    int max=0;
    for(int i=0; i<n; i++)
    {
        if(mokiniai[i].balas>mokiniai[max].balas) max=i;
    }
    return mokiniai[max].balas;
}

int BlogiausiasBalas(int n, Mokinys* mokiniai)
{
    int min=0; // kodel neveikia INT_MAX
    for(int i=0; i<n; i++)
    {
        if(mokiniai[i].balas<mokiniai[min].balas) min=i;
    }
    return mokiniai[min].balas;
}

int kiekTeigiamu(int n, Mokinys* mokiniai)
{
    int kiek=0;
    for(int i=0; i<n; i++)
    {
        if(mokiniai[i].balas>=4) kiek++;
    }
    return kiek;
}

void GeriausiuArBlogiausiuIsvedimas(int n, int kriterijus, Mokinys* mokiniai)
{
    for(int i=0; i<n; i++)
    {
        if(mokiniai[i].balas==kriterijus)
        {
            cout << mokiniai[i].vardas << " " << mokiniai[i].balas << endl;
        }
    }
}

void Isvedimas(int n, Mokinys* mokiniai, int vidurkis, int geriausias, int blogiausias, int kiek)
{
    ofstream rezultatai("rezultatai.txt");
    for(int i=0; i<n; i++)
    {
        cout << mokiniai[i].vardas << " " << mokiniai[i].balas << endl;
    }
    cout << vidurkis << endl;
    GeriausiuArBlogiausiuIsvedimas(n, geriausias, mokiniai);
    GeriausiuArBlogiausiuIsvedimas(n, blogiausias, mokiniai);
    cout << kiek << endl;
    rezultatai.close();
}
