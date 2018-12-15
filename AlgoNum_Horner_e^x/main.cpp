#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

bool isDouble(char a[])
{
  int i = 0;

  while(a[i] != 0)
  {
    if(!(isdigit(a[i]) || a[i] == '.'))
    {
      return false;
    }
    i++;
  }
  return true;
}

int main()
{
    char repUser;
    cout << "****************CALCUL DE e^X PAR LA METHODE DE HORNER***************" << endl;

    do
    {

        int k(1);
        double erreur(0.0), Sn(1.0), un(1.0), x(0); //Car u0 = 1, on commence par 1 pour ajouter les autres
        char tempX[10];
        char tempErreur[10];
        vector <double> lesUn;

        do
        {
            cout << "Entrer x : ";
            cin >> tempX;
        }while(!isDouble(tempX));

        x = atof(tempX);


        do
        {
            cout <<"\nEntrer l'erreur (sous forme de nombre à virgule) : ";
            cin >> tempErreur;
        }while(!isDouble(tempErreur));

        erreur = atof(tempErreur);

        do
        {
            un = ((double)x/k)*un;
            lesUn.push_back(un);
            k++;
        }while(un >= erreur);

        cout << "\nS" << k-1 << " = " ;

        for(int i(0); i<lesUn.size(); i++)
        {
            Sn += lesUn[i];
            cout << "u" << i+1;

            if(i != lesUn.size()-1)
            {
                cout << " + ";
            }else
            {
                cout << " = " << Sn;
            }
        }

        do
        {
            cout << "\nVoulez-vous reessayer ? (O/N) ";
            cin >> repUser;
        }while(repUser != 'O' && repUser != 'N');

    }while(repUser == 'O');

    cout << "\n\nMERCI D'AVOIR UTILISE CE PROGRAMME !\n";

    return 0;
}
