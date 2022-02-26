#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

const int AMZIAI[6] = {1800, 1800, 1900, 1900, 2000, 2000};
const string MENESIU_PAVADINIMAI[12] = {"sausio", "vasario", "kovo", "balandzio", "geguzes", "birzelio", "liepos", "rugpjucio", "rugsejo", "spalio", "lapkricio", "gruodzio"};

struct Zmogus
{
    string vardas;
    long long asmensKodas;
    int amzius, metai, diena, men;
    string menuo, lytis;

};

void Nuskaitymas(int& n, Zmogus zmones[]);
void VienoZmogausSutvarkymas(Zmogus& zmogus);
void MenesiuNustatymas(int skaicius, string& menuo);
void LyciuAtskyrimas(int& n, Zmogus zmones[], Zmogus vyrai[], Zmogus moterys[], int& kiekVyru, int& kiekMoteru);
void Rikiavimas(int n, Zmogus lytis[]);
void Isvedimas(int n, Zmogus lytis[], ofstream& rezultatai);

int main()
{
    int n, kiekVyru=0, kiekMoteru=0;
    Zmogus zmones[100], vyrai[100], moterys[100];
    Nuskaitymas(n, zmones);
    for(int i=0; i<n; i++)
    {
        VienoZmogausSutvarkymas(zmones[i]);
    }
    LyciuAtskyrimas(n, zmones, vyrai, moterys, kiekVyru, kiekMoteru);
    Rikiavimas(kiekVyru, vyrai);
    Rikiavimas(kiekMoteru, moterys);

    ofstream rezultatai("rezultatai.txt");

    rezultatai << "MOTERYS" << endl;
    Isvedimas(kiekMoteru, moterys, rezultatai);
    rezultatai << "VYRAI" << endl;
    Isvedimas(kiekVyru, vyrai, rezultatai);

    rezultatai.close();
    return 0;
}

void Nuskaitymas(int& n, Zmogus zmones[])
{
    ifstream duomenys("duomenys.txt");
    duomenys >> n;
    for(int i=0; i<n; i++)
    {
        duomenys >> zmones[i].vardas;
        duomenys >> zmones[i].asmensKodas;
    }
    duomenys.close();
}

void VienoZmogausSutvarkymas(Zmogus& zmogus)
{
    int amzius = zmogus.asmensKodas/10000000000;
    int metai = zmogus.asmensKodas/100000000%100;
    for(int i=0; i<6; i++)
    {
        if(amzius-1==i)
        {
            if((i+1)%2==0)
            {
                zmogus.amzius=AMZIAI[i];
                zmogus.lytis="Moteris";
                zmogus.amzius+=metai;
                //cout << zmogus.vardas << " " << zmogus.amzius << " " << zmogus.lytis << endl;
            }
            else
            {
                zmogus.amzius=AMZIAI[i];
                zmogus.lytis="Vyras";
                zmogus.amzius+=metai;
                //cout << zmogus.vardas << " " << zmogus.amzius << " " << zmogus.lytis << endl;
            }
            break;
        }
    }
    int skaicius = zmogus.asmensKodas/1000000%100;
    zmogus.men = skaicius;
    MenesiuNustatymas(skaicius, zmogus.menuo);
    zmogus.diena = zmogus.asmensKodas/10000%100;
    //cout << zmogus.vardas << " " << zmogus.diena << endl;
}

void MenesiuNustatymas(int skaicius, string& menuo)
{
    for(int i=0; i<12; i++)
    {
        if(skaicius==i+1)
        {
            menuo = MENESIU_PAVADINIMAI[i];
        }
    }
}

void LyciuAtskyrimas(int& n, Zmogus zmones[], Zmogus vyrai[], Zmogus moterys[], int& kiekVyru, int& kiekMoteru)
{
    for(int i=0; i<n; i++)
    {
        //cout << zmones[i].lytis << endl;
        if(zmones[i].lytis=="Vyras")
        {
            vyrai[kiekVyru++]=zmones[i];
        }
        else
        {
            moterys[kiekMoteru++]=zmones[i];
        }
    }
}

void Rikiavimas(int n, Zmogus lytis[])
{
    for(int i=0; i<n-1; i++)
    {
        int max=i;
        for(int j=i+1; j<n; j++)
        {
            if(lytis[j].amzius<lytis[max].amzius || (lytis[j].amzius==lytis[max].amzius && lytis[j].men<lytis[max].men) || (lytis[j].amzius==lytis[max].amzius && lytis[j].men==lytis[max].men && lytis[j].diena<lytis[max].diena))
            {
                max=j;
            }
        }
        if(max!=i)
        {
            swap (lytis[i], lytis[max]);
        }
    }
}

void Isvedimas(int n, Zmogus lytis[], ofstream& rezultatai)
{
    if(n==0)
    {
        rezultatai << "NERASTA" << endl;
    }
    for(int i=0; i<n; i++)
    {
        rezultatai << lytis[i].vardas << " " << lytis[i].amzius << " " << lytis[i].menuo << " " << lytis[i].diena << endl;
    }
}

