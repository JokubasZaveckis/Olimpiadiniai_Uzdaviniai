#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>

using namespace std;

struct IP
{
    string adresas;
    bool arTeisingas = true;
    string galiojimas;
};

void Nuskaitymas(int& n, IP ip[]);
bool TinkamumoIeskojimas(string ip);
void TinkamumoPavertimas(int n, IP ip[]);
void Isvedimas(int n, IP ip[]);

int main()
{
    int n=0;
    IP ip[10];

    Nuskaitymas(n, ip);

    /*for(int i=0; i<n; i++)
    {
        ip[i].arTeisingas = TinkamumoIeskojimas(ip[i].adresas);
    }*/

    ip[0].arTeisingas = TinkamumoIeskojimas(ip[0].adresas);
    ip[1].arTeisingas = TinkamumoIeskojimas(ip[1].adresas);
    ip[2].arTeisingas = TinkamumoIeskojimas(ip[2].adresas);
    ip[3].arTeisingas = TinkamumoIeskojimas(ip[3].adresas);
    ip[4].arTeisingas = TinkamumoIeskojimas(ip[4].adresas);

    TinkamumoPavertimas(n, ip);
    Isvedimas(n, ip);

    return 0;
}

void Nuskaitymas(int& n, IP ip[])
{
    ifstream duomenys("duomenys.txt");
    while(!duomenys.eof())
    {
        duomenys >> ip[n++].adresas;
    }
    duomenys.close();
}

bool TinkamumoIeskojimas(string ip)
{
    int kiekDaliu=0;
    int kurI[16]= {0};
    for(int i=0; i<16; i++)
    {
        if(ip[i]=='.')
        {
            kurI[kiekDaliu]=i;
            kiekDaliu++;
        }
    }
    for(int i=0; i<kiekDaliu; i++) //Patikrina kad nebutu dvieju tasku is eiles
    {
        if(kurI[i]==kurI[i+1])
        {
            return false;
        }
    }
    if(kiekDaliu!=3) //Patikrina kiek daliu (tasku)
    {
        return false;
    }

    if(ip[0]=='.') return false; //del ip pirmo simbolio .

    for(int i=16; i>0; i--)
    {
        if(isdigit(ip[i]))
        {
            break;
        }
        if(ip[i]=='.') return false; // del ip paskutinio simbolio .
    }
    for(int i=0; i<16; i++) // Patikrina del simboliu
    {
        if(!isdigit(ip[i]) && ip[i]!='.' && ip[i]!=0)
        {
            return false;
        }
    }
    int kiekSkaiciu[4]= {0};
    kiekSkaiciu[0]=kurI[0];
    for(int i=1; i<3; i++) //kas bus jei suksiu nuo 0
    {
        kiekSkaiciu[i]=kurI[i]-(kurI[i-1]+1);
        //cout << kiekSkaiciu[i] << endl; // kodel tiek daug isveda
    }

    for(int i=kurI[2]+1; i<16; i++) // iesko kiek paskutiniame skyriuje skaiciu
    {
        if(isdigit(ip[i]))
        {
            kiekSkaiciu[3]++;
        }
    }
    for(int i=0; i<4; i++) // tikrina del skaicio kiekiu skyriuje
    {
        if(kiekSkaiciu[i]>3) return false;
    }

    /*for(int i=1; i<4; i++)
    {
        int skaicius=0, a=100;
        if(kiekSkaiciu[i]==3)
        {
            cout << ip[kurI[i]+1] << " " << ip[kurI[i+1]] << endl;
            for(int j=kurI[i]+1; j<kurI[i+1]; j++)
            {
                skaicius+=(ip[j]-48)*a;
            }
            a/=10;
        }
        if(skaicius>255 || skaicius<0) return false;
    }*/

    int skaicius=0;
    if(kiekSkaiciu[0]==3)
    {
        skaicius+=(ip[0]-48)*100+(ip[1]-48)*10+ip[2]-48;
    }
    if (skaicius>255) return false;

    skaicius = 0;

    if(kiekSkaiciu[0]==3 && kiekSkaiciu[1]==3)
    {
        skaicius+=(ip[4]-48)*100+(ip[5]-48)*10+ip[6]-48;
    }
    else if(kiekSkaiciu[0]==2 && kiekSkaiciu[1]==3)
    {
        skaicius+=(ip[3]-48)*100+(ip[4]-48)*10+ip[5]-48;
    }
    else if(kiekSkaiciu[0]==1 && kiekSkaiciu[1]==3)
    {
        skaicius+=(ip[2]-48)*100+(ip[3]-48)*10+ip[4]-48;
    }
    if (skaicius>255) return false;

    skaicius=0;
    int a=100;
    if(kiekSkaiciu[2]==3)
    {
        for(int i=kurI[1]+1; i<kurI[2]; i++)
        {
            skaicius+=(ip[i]-48)*a;
            a/=10;
        }
    }
    if (skaicius>255) return false;

    skaicius = 0;
    a = 100;
    if(kiekSkaiciu[3]==3)
    {
        for(int i=kurI[2]+1; i<16; i++)
        {
            skaicius+=(ip[i]-48)*a;
            a/=10;
        }
    }
    if (skaicius>255) return false;

    return true;
}

void TinkamumoPavertimas(int n, IP ip[])
{
    for(int i=0; i<n; i++)
    {
        if(ip[i].arTeisingas==1)
        {
            ip[i].galiojimas = " Teisingas";
        }
        else ip[i].galiojimas = " Neteisingas";
    }
}

void Isvedimas(int n, IP ip[])
{
    ofstream rezultatai("rezultatai.txt");

    for(int i=0; i<n; i++)
    {
        cout << ip[i].adresas << ip[i].galiojimas << endl;
    }
    rezultatai.close();
}

