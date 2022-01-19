#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

struct Produktas
{
    string pavadinimas;
    int metai, menuo, diena;
    int kiekDienuGalioja=0;
    string laikas;
};

struct TikrinimoData
{
    int metai, menuo, diena;
};

void Nuskaitymas(int& n, TikrinimoData& data, Produktas*& produktai);
void KiekDarDienuGalioja(int n, TikrinimoData& data, Produktas*& produktai);

int main()
{
    int n;
    Produktas* produktai = nullptr;
    TikrinimoData data;

    Nuskaitymas(n, data, produktai);
    //KiekDarDienuGalioja(n, data, produktai);


    delete[] produktai;
    return 0;
}

void Nuskaitymas(int& n, TikrinimoData& data, Produktas*& produktai)
{
    ifstream duomenys("duomenys.txt");
    duomenys >> n;
    duomenys >> data.metai >> data.menuo >> data.diena;
    for(int i=0; i<n; i++)
    {
        duomenys >> produktai[i].pavadinimas;
        duomenys >> produktai[i].metai >> produktai[i].menuo >> produktai[i].diena;
    }
    duomenys.close();
}

void KiekDarDienuGalioja(int n, TikrinimoData& data, Produktas*& produktai)
{
    for(int i=0; i<n; i++)
    {
        produktai[i].kiekDienuGalioja=(produktai[i].metai-data.metai)*365+(produktai[i].menuo-data.menuo)*30+(produktai[i].diena-data.diena);
        cout << produktai[i].kiekDienuGalioja << endl;
    }
}
