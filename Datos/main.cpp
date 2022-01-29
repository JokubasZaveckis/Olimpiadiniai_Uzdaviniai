#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

const int menesiuDienos[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const int keliamujuMetuMenesiuDienos[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

struct TikrinimoData
{
    int metai, menuo, diena;
    int dienuSkaicius=0;
    //bool arKeliamieji = false;
    bool galiojimas = false;
};

struct Produktas : TikrinimoData
{
    string Pavadinimas;
    int kiekDienuNuoTikrinimo=0;
};

struct Sarasas
{
    int kiekProduktu=0;
    string pavadinimai[500];
    int metai[500], menuo[500], diena[500];
};

void Nuskaitymas(int& n, TikrinimoData& data, Produktas produktai[]);
//void TikrinimasDelKeliamujuMetu(int n, TikrinimoData& data, Produktas produktai[]);
bool Keliamieji(int metai);
void KiekDienuMetuose(int n, TikrinimoData& data, Produktas produktai[]);
void DienuSkirtumas(int n, TikrinimoData data, Produktas produktai[]);
void GaliojimoTikrinimas(int n, Produktas produktai[]);
void SarasuSudarymas(int n, Produktas produktai[], Sarasas& ilgas, Sarasas& trumpas);
void Isvedimas(Sarasas sarasas, int a, ofstream& rezultatai);

int main()
{
    int n;
    TikrinimoData data;
    Produktas produktai[500];

    Nuskaitymas(n, data, produktai);

    Sarasas ilgas;
    Sarasas trumpas;

    //TikrinimasDelKeliamujuMetu(n, data, produktai);
    KiekDienuMetuose(n, data, produktai);
    DienuSkirtumas(n, data, produktai);
    GaliojimoTikrinimas(n, produktai);
    SarasuSudarymas(n, produktai, ilgas, trumpas);

    ofstream rezultatai("rezultatai.txt");
    int a=1;
    Isvedimas(ilgas, a, rezultatai);
    a=0;
    Isvedimas(trumpas, a, rezultatai);
    rezultatai.close();

    return 0;
}

void Nuskaitymas(int& n, TikrinimoData& data, Produktas produktai[])
{
    ifstream duomenys("duomenys.txt");
    duomenys >> n;
    duomenys >> data.metai >> data.menuo >> data.diena;
    for(int i=0; i<n; i++)
    {
        duomenys >> produktai[i].Pavadinimas;
        duomenys >> produktai[i].metai >> produktai[i].menuo >> produktai[i].diena;
    }
    duomenys.close();
}

/*void TikrinimasDelKeliamujuMetu(int n, TikrinimoData& data, Produktas produktai[])
{
    //Tikrinimo Datos patikrinimas

    if(data.metai%4==0 && data.metai%100!=0)
    {
        data.arKeliamieji=true;
    }

    else if(data.metai%4==0 && data.metai%100==0 && data.metai%400==0)
    {
        data.arKeliamieji=true;
    }

    //ProduktuDatos
    for(int i=0; i<n; i++)
    {
        if(produktai[i].metai%4==0 && produktai[i].metai%100!=0)
        {
            produktai[i].arKeliamieji=true;
        }

        else if(produktai[i].metai%4==0 && produktai[i].metai%100==0 && produktai[i].metai%400==0)
        {
            produktai[i].arKeliamieji=true;
        }
    }
}*/

bool Keliamieji(int metai)
{
    if(metai%4==0 && metai%100!=0)
    {
        return true;
    }

    else if(metai%4==0 && metai%100==0 && metai%400==0)
    {
        return true;
    }
    return false;
}

void KiekDienuMetuose(int n, TikrinimoData& data, Produktas produktai[])
{
    int metai, kiek=0;
    for(int i=0; i<data.metai; i++) //suka nuo 0000 iki 2017 imtinai
    {
        metai = i;
        if(Keliamieji(metai))
        {
            data.dienuSkaicius+=366;
            kiek++;
        }
        else
        {
            data.dienuSkaicius+=365;
        }
    }
    for(int i=0; i<data.menuo; i++) //suka 2018 metus
    {
        if(Keliamieji(data.metai))
        {
            data.dienuSkaicius+=keliamujuMetuMenesiuDienos[i];
        }
        else
        {
            data.dienuSkaicius+=menesiuDienos[i];
        }
    }
    data.dienuSkaicius+=data.diena;

    for(int j=0; j<n; j++)
    {
        for(int i=0; i<produktai[j].metai; i++) //suka nuo 0000 iki 2017 imtinai
        {
            metai = i;
            if(Keliamieji(metai))
            {
                produktai[j].dienuSkaicius+=366;
                kiek++;
            }
            else
            {
                produktai[j].dienuSkaicius+=365;
            }
        }
        for(int i=0; i<produktai[j].menuo; i++) //suka 2018 metus
        {
            if(Keliamieji(produktai[j].metai))
            {
                produktai[j].dienuSkaicius+=keliamujuMetuMenesiuDienos[i];
            }
            else
            {
                produktai[j].dienuSkaicius+=menesiuDienos[i];
            }
        }
        produktai[j].dienuSkaicius+=produktai[j].diena;
    }
}

void DienuSkirtumas(int n, TikrinimoData data, Produktas produktai[])
{
    for(int i=0; i<n; i++)
    {
        produktai[i].kiekDienuNuoTikrinimo = produktai[i].dienuSkaicius-data.dienuSkaicius;
        //cout << produktai[i].kiekDienuNuoTikrinimo << endl;
    }
}

void GaliojimoTikrinimas(int n, Produktas produktai[])
{
    for(int i=0; i<n; i++)
    {
        //cout << produktai[i].kiekDienuNuoTikrinimo << endl;
        if(produktai[i].kiekDienuNuoTikrinimo>=3)
        {
            produktai[i].galiojimas=true;
        }
    }
}

void SarasuSudarymas(int n, Produktas produktai[], Sarasas& ilgas, Sarasas& trumpas)
{
    for(int i=0; i<n; i++)
    {
        if(produktai[i].galiojimas)
        {
            ilgas.pavadinimai[ilgas.kiekProduktu]=produktai[i].Pavadinimas;
            ilgas.metai[ilgas.kiekProduktu]=produktai[i].metai;
            ilgas.menuo[ilgas.kiekProduktu]=produktai[i].menuo;
            ilgas.diena[ilgas.kiekProduktu++]=produktai[i].diena;
        }
        else
        {
            trumpas.pavadinimai[trumpas.kiekProduktu]=produktai[i].Pavadinimas;
            trumpas.metai[trumpas.kiekProduktu]=produktai[i].metai;
            trumpas.menuo[trumpas.kiekProduktu]=produktai[i].menuo;
            trumpas.diena[trumpas.kiekProduktu++]=produktai[i].diena;
        }
    }
}

void Isvedimas(Sarasas sarasas, int a, ofstream& rezultatai)
{
    if(a==1)
    {
        rezultatai << "ILGAS GALIOJIMO LAIKAS " << endl;
        if(sarasas.kiekProduktu==0)
        {
            cout << "NERA" << endl;
            rezultatai << "NERA" << endl;
        }
        for(int i=0; i<sarasas.kiekProduktu; i++)
        {
            cout << sarasas.pavadinimai[i] << " " << sarasas.metai[i] << " " << sarasas.menuo[i] << " " << sarasas.diena[i] << endl;
            rezultatai << sarasas.pavadinimai[i] << " " << sarasas.metai[i] << " " << sarasas.menuo[i] << " " << sarasas.diena[i] << endl;
        }
    }
    else
    {
        rezultatai << "TRUMPAS GALIOJIMO LAIKAS " << endl;
        if(sarasas.kiekProduktu==0)
        {
            cout << "NERA" << endl;
            rezultatai << "NERA" << endl;
        }
        for(int i=0; i<sarasas.kiekProduktu; i++)
        {
            cout << sarasas.pavadinimai[i] << " " << sarasas.metai[i] << " " << sarasas.menuo[i] << " " << sarasas.diena[i] << endl;
            rezultatai << sarasas.pavadinimai[i] << " " << sarasas.metai[i] << " " << sarasas.menuo[i] << " " << sarasas.diena[i] << endl;
        }
    }
}

