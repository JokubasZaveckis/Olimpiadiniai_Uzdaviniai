#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

struct Zmogus
{
    string vardas;
    long long asmensKodas;

};

void Nuskaitymas(int& n, Zmogus zmones[]);

int main()
{
    int n;
    Zmogus zmones[100];

    float a = 50310241123;
    cout << a << endl;
    a/=1000000000;
    int b = a;
    cout << b << endl;


    Nuskaitymas(n, zmones);
    for(int i=0; i<n; i++)
    {
        cout << zmones[i].vardas << " " << zmones[i].asmensKodas << endl;
    }
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
