#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>

using namespace std;

struct Dalyvis
{
    string vardas;
    int startoLaikas=0, finisoLaikas=0;
    int praeitiPunktai[20]={0};
    int kiekPunktuPraejo=0;
};

struct Punktas
{
    int kiekFinisavo, numeris;
    int apsilankiusiuDalyviuNumeriai[100];
};

void Nuskaitymas(int& n, int& p, Dalyvis*& dalyviai, Punktas*& punktai);
void PunktuFiksavimas(int n, int p, Dalyvis*& dalyviai, Punktas*& punktai);
void Punktai(int n, int p, Dalyvis*& dalyviai, Punktas*& punktai);
void Isvedimas(int n, Dalyvis* dalyviai);

int main()
{
    int n, p;
    Dalyvis* dalyviai = nullptr;
    Punktas* punktai = nullptr;

    Nuskaitymas(n, p, dalyviai, punktai);
    //PunktuFiksavimas(n, p, dalyviai, punktai);

    for(int i=0; i<n; i++)
    {
        cout << dalyviai[i].vardas << " ";
        for(int j=0; j<=5; j++)
        {
            cout << dalyviai[i].praeitiPunktai[j] << " ";
        }
        cout << endl;
    }

    Isvedimas(n, dalyviai);

    delete[] dalyviai;
    return 0;
}

void Nuskaitymas(int& n, int& p, Dalyvis*& dalyviai, Punktas*& punktai)
{
    ifstream duomenys("duomenys.txt");
    duomenys >> n;
    dalyviai = new Dalyvis[n];
    punktai = new Punktas[p];

    char vardas[17];
    int h, m, s;
    for(int i=0; i<n; i++)
    {
         duomenys.ignore(256, '\n');
         duomenys.get(vardas, 17);
         dalyviai[i].vardas = vardas;
         duomenys >> h >> m >> s;
         dalyviai[i].startoLaikas = h*3600+n*60+s;
         duomenys >> h >> m >> s;
         dalyviai[i].finisoLaikas = h*3600+n*60+s;
    }
    duomenys >> p;
    for(int i=0; i<p; i++)
    {
        duomenys >> punktai[i].numeris >> punktai[i].kiekFinisavo;
        for(int j=0; j<punktai[i].kiekFinisavo; j++)
        {
            duomenys >> punktai[i].apsilankiusiuDalyviuNumeriai[j];
        }
    }

    duomenys.close();
}

void PunktuIssirikiavimas(int p, Punktas*& punktai)
{
    for(int i=0; i<p-1; i++)
    {
        int max=i;
        for(int j=i+1; j<p; j++)
        {
            if(punktai[j].numeris<punktai[max].numeris)
            {
                max=j;
            }
        }
        if(max!=i)
        {
            swap(punktai[i], punktai[max]);
        }
    }
}

void PunktuFiksavimas(int n, int p, Dalyvis*& dalyviai, Punktas*& punktai)
{
    for(int i=0; i<n; i++)
    {
        for(int j=1; j<=p; j++)
        {
            //cout << punktai[j].kiekFinisavo << endl;
            for(int k=0; k<punktai[j].kiekFinisavo; k++)
            {
                //cout << dalyviai[i].praeitiPunktai[punktai[j].apsilankiusiuDalyviuNumeriai[k]] << " ";
                if(dalyviai[i].praeitiPunktai[punktai[j].apsilankiusiuDalyviuNumeriai[k]]==0)
                {
                    dalyviai[i].praeitiPunktai[punktai[j].apsilankiusiuDalyviuNumeriai[k]] = 1;
                    dalyviai[i].kiekPunktuPraejo++;
                }
            }
            //cout << endl;
        }
        cout << dalyviai[i].kiekPunktuPraejo << endl;
    }
}

void Punktai(int n, int p, Dalyvis*& dalyviai, Punktas*& punktai)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<p; j++)
        {
            for(int k=0; j<punktai[j].kiekFinisavo; k++)
            {
                dalyviai[punktai[j].apsilankiusiuDalyviuNumeriai[k]].praeitiPunktai[punktai[j].apsilankiusiuDalyviuNumeriai[k]]++;
            }
        }
    }
}

void Isvedimas(int n, Dalyvis* dalyviai)
{
    ofstream rezultatai("rezultatai.txt");

    for(int i=0; i<n; i++)
    {

    }
    rezultatai.close();
}
