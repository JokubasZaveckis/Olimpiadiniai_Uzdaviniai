#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>

using namespace std;

struct Gyventojas
{
    string Vardas;
    int butoNumeris;
    float sildymas, elektra, vanduo;
    bool arSkolingas = false;
};

void Nuskaitymas(int& n, int& k, Gyventojas*& gyventojai, Gyventojas*& imokos);
void ImokuSutvarkymas(int n, int k, Gyventojas*& gyventojai, Gyventojas*& imokos);
void ArSkolingas(int n, Gyventojas*& gyventojai);
void Isvedimas(int n, Gyventojas* gyventojai);

int main()
{
    int n, k;
    Gyventojas* gyventojai = nullptr;
    Gyventojas* imokos = nullptr;

    Nuskaitymas(n, k, gyventojai, imokos);

    for(int i=0; i<n; i++)
    {
        //cout << gyventojai[i].Vardas << " " << gyventojai[i].butoNumeris << " " << gyventojai[i].sildymas << " " << gyventojai[i].elektra << " " << gyventojai[i].vanduo << endl;
    }

    ImokuSutvarkymas(n, k, gyventojai, imokos);
    ArSkolingas(n, gyventojai);
    Isvedimas(n, gyventojai);

    delete[] gyventojai;
    delete[] imokos;
    return 0;
}

void Nuskaitymas(int& n, int& k, Gyventojas*& gyventojai, Gyventojas*& imokos)
{
    ifstream duomenys("duomenys.txt");
    duomenys >> n;
    gyventojai = new Gyventojas[n];
    char vardas[21];
    for(int i=0; i<n; i++)
    {
        vardas[21]=0;
        duomenys.ignore(256, '\n');
        duomenys.get(vardas, 21);
        gyventojai[i].Vardas = vardas;
        //cout << gyventojai[i].Vardas << " ";
        duomenys >> gyventojai[i].butoNumeris >> gyventojai[i].sildymas >> gyventojai[i].elektra >> gyventojai[i].vanduo;
        //cout << gyventojai[i].butoNumeris << " " << gyventojai[i].sildymas << " " << gyventojai[i].elektra << " " << gyventojai[i].vanduo << endl;

    }
    duomenys.close();

    ifstream df("imokos.txt");
    df >> k;
    imokos = new Gyventojas[k];
    char name[21];
    for(int i=0; i<k; i++)
    {
        name[21]=0;
        df.ignore(256, '\n');
        df.get(name, 21);
        imokos[i].Vardas = name;
        df >> imokos[i].butoNumeris;
        df >> imokos[i].sildymas >> imokos[i].elektra >> imokos[i].vanduo;
    }
    df.close();
}

void ImokuSutvarkymas(int n, int k, Gyventojas*& gyventojai, Gyventojas*& imokos)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<k; j++)
        {
            if(gyventojai[i].Vardas==imokos[j].Vardas)
            {
                //cout << gyventojai[i].Vardas << " " << gyventojai[i].vanduo << " " << imokos[j].vanduo << endl; blogas rez failas?
                gyventojai[i].sildymas+=imokos[j].sildymas;
                gyventojai[i].elektra+=imokos[j].elektra;
                gyventojai[i].vanduo+=imokos[j].vanduo;
                //cout << gyventojai[i].vanduo << endl;
            }
        }
    }
}

void ArSkolingas(int n, Gyventojas*& gyventojai)
{
    for(int i=0; i<n; i++)
    {
        if(gyventojai[i].sildymas<0 || gyventojai[i].elektra<0 || gyventojai[i].vanduo<0)
        {
            gyventojai[i].arSkolingas=true;
        }
    }
}

void Isvedimas(int n, Gyventojas* gyventojai) // kaip veikia setw
{
    for(int i=0; i<n; i++)
    {
        cout << fixed << setprecision(2) << gyventojai[i].Vardas << " " << gyventojai[i].butoNumeris << " " << gyventojai[i].sildymas << " " << gyventojai[i].elektra << " " << gyventojai[i].vanduo << endl;
    }
    cout << endl;
    for(int i=0; i<n; i++)
    {
        if(gyventojai[i].arSkolingas)
        {
            cout << fixed << setprecision(2) << gyventojai[i].Vardas << " " << gyventojai[i].butoNumeris << " " << gyventojai[i].sildymas << " " << gyventojai[i].elektra << " " << gyventojai[i].vanduo << endl;
        }
    }
}
