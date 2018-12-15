#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

string binairyConversion(int nombre) {
    if (nombre == 0) {
        return "0";
    } else {
        string resultat = "";
        while (nombre >= 1) {
            resultat += ('0' + nombre % 2);
            nombre = (int)(nombre / 2);
        }

        reverse(resultat.begin(), resultat.end());

        return resultat;
    }

}

string combleEspace(string binaire) {
    if (binaire.length() < 6) {

        int manque = 6 - binaire.length();

        for (int i(0); i < manque; i++) {
            binaire = "0" + binaire;
        }
    }

    return binaire;

}

int main() {

    int h(0), m(0), s(0), nbreCas(0);
    string unResultat = "";
    vector < string > resultats;
    cin >> nbreCas;

    do {
        scanf("%d:%d:%d", & h, & m, & s);

        unResultat = combleEspace(binairyConversion(h));
        unResultat += combleEspace(binairyConversion(m));
        unResultat += combleEspace(binairyConversion(s));

        unResultat += " ";

        for (int i(0); i < 6; i++) {
            unResultat += unResultat[i];
            unResultat += unResultat[i + 6];
            unResultat += unResultat[i + 12];
        }

        resultats.push_back(unResultat.substr(unResultat.find_first_of("\ "), unResultat.length() - 1) + " " + unResultat.substr(0, unResultat.find_first_of("\ ")));

        nbreCas--;
    } while (nbreCas != 0);

    for (int i(0); i < resultats.size(); i++) {
        cout << i + 1 << " " << resultats[i] << endl;
    }

    return 0;
}
