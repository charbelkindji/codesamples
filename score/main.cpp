#include <iostream>
#include <vector>

using namespace std;

class Equipe {
private:
    int m_num;

public:
    Equipe(int num)
        : m_num(num)
    {
    }

    int getNum()
    {
        return m_num;
    }
};

class Cas {
private:
    int m_num;
    int m_nbreEquipe;

public:
    Cas(int numCas)
        : m_num(numCas)
    {
    }
    Cas(int num, int nbreEquipe)
        : m_num(num)
        , m_nbreEquipe(nbreEquipe)
    {
    }
    int getNum()
    {
        return m_num;
    }
    int getNbreEquipe()
    {
        return m_nbreEquipe;
    }
};

class Probleme {
private:
    int m_num;

public:
    Probleme(int num)
        : m_num(num)
    {
    }
    int getNum()
    {
        return m_num;
    }
};

class EquipeCas {
private:
    Equipe m_equipe;
    Cas m_cas;
    int m_rang;
    int m_tempsTotal;
    int m_nbResolus;

public:
    EquipeCas(int numEquipe, int numCas)
        : m_equipe(numEquipe)
        , m_cas(numCas)
        , m_rang(0)
        , m_tempsTotal(0)
        , m_nbResolus(0)
    {
    }

    Equipe getEquipe()
    {
        return m_equipe;
    }
    Cas getCas()
    {
        return m_cas;
    }
    int getRang()
    {
        return m_rang;
    }
    int tempsTotal()
    {
        return m_tempsTotal;
    }

    int getTempsTotal()
    {
        return m_tempsTotal;
    }
    int getNbResolus()
    {
        return m_nbResolus;
    }

    void setNbreResolu()
    {
        m_nbResolus++;
    }
    void setTempsTotal(int temps)
    {
        m_tempsTotal += temps;
    }

    void setRang(int rang)
    {
        m_rang = rang;
    }
};

class CasProbleme {
    Cas m_cas;
    Probleme m_probleme;
};

class Run {
private:
    Cas m_cas; // Cle primaire
    int m_tempsConsomme;
    Equipe m_equipe; // Cle primaire
    Probleme m_probleme; // Cle primaire
    int m_penalite;
    bool m_resolu;

public:
    Run(int numCas, int tempsConsomme, int numEquipe, int numProbleme)
        : m_cas(numCas)
        , m_tempsConsomme(tempsConsomme)
        , m_equipe(numEquipe)
        , m_probleme(numProbleme)
        , m_penalite(0)
        , m_resolu(false)
    {
    }

    Equipe getEquipe()
    {
        return m_equipe;
    }
    Cas getCas()
    {
        return m_cas;
    }
    Probleme getProbleme()
    {
        return m_probleme;
    }
    bool getResolu()
    {
        return m_resolu;
    }
    int getTempsConsomme()
    {
        return m_tempsConsomme;
    }
    void setPenalite()
    {
        m_penalite += 20;
    }
    void setTempsConsomme(int tempsSoumission)
    {
        m_tempsConsomme = tempsSoumission + m_penalite;
    }
};

//******************************************
int debut(0);
void trier(vector<EquipeCas>& tab, Cas cas)
{

    if (cas.getNum() > 1) {
        for (size_t i(0); i < tab.size(); i++) {
            EquipeCas courant = tab[i];
            if (courant.getCas().getNum() == (cas.getNum() - 1)) {
                debut++;
            }
        }
    }

    cout << "Debut=" << debut << "\n";

    for (int i(debut); i < (cas.getNbreEquipe() + debut); i++) {
        for (int j(debut); j < (cas.getNbreEquipe() + debut); j++) {
            if (tab[i].getNbResolus() > tab[j].getNbResolus()) {
                EquipeCas temp = tab[i];
                tab[i] = tab[j];
                tab[j] = temp;
            }
            else if (tab[i].getNbResolus() == tab[j].getNbResolus()) {
                if (tab[i].getTempsTotal() < tab[j].getTempsTotal()) {
                    EquipeCas temp = tab[i];
                    tab[i] = tab[j];
                    tab[j] = temp;
                }
                else if (tab[i].getTempsTotal() == tab[j].getTempsTotal()) {
                    if (tab[i].getEquipe().getNum() < tab[j].getEquipe().getNum()) {
                        EquipeCas temp = tab[i];
                        tab[i] = tab[j];
                        tab[j] = temp;
                    }
                }
            }
        }
    }

    tab[debut].setRang(1);

    int rang(0);
    for (int i(debut + 1); i < (cas.getNbreEquipe() + debut); i++) {
        rang++;
        EquipeCas courant = tab[i];
        EquipeCas avant = tab[i - 1];
        if (courant.getNbResolus() == avant.getNbResolus() && courant.getTempsTotal() == avant.getTempsTotal()) {
            courant.setRang(avant.getRang());
            tab[i] = courant;
        }
        else {
            courant.setRang(rang + 1);
            tab[i] = courant;
        }
    }
}
//******************************************************

int main()
{
    bool nouveauCas(true), nouveauRun(true);
    int nbEquipe(0), tempsConsomme(0), numEquipe(0), numProbleme(0), numCas(0);
    string resoluStr(""), erreurs("");

    vector<Cas> tabCas;
    vector<EquipeCas> tabEquipeCas;
    vector<Run> tabRun;

    do {
        //cout << "Cas: " ;
        nouveauRun = true;
        cin >> nbEquipe;

        if (nbEquipe < 3 || nbEquipe > 99) {
            if (nbEquipe == 0) {
                nouveauCas = false;
            }
            else {
                cout << "Nombre dEquipe incorrect ";
            }
        }
        else {
            // Si la saisie dun est correct
            numCas++;
            Cas cas(numCas, nbEquipe);
            tabCas.push_back(cas);
            for (int i(0); i < nbEquipe; i++) {
                EquipeCas equipeCas(i + 1, numCas);
                tabEquipeCas.push_back(equipeCas);
            }

            // On saisit les runs
            do {
                erreurs = "";
                cin >> tempsConsomme;
                if (tempsConsomme == 0) {
                    nouveauRun = false;
                }
                else {
                    if (tempsConsomme < 0) {
                        erreurs = "Temps incorrect ";
                    }
                    cin >> numEquipe >> numProbleme >> resoluStr;
                    if (numEquipe < 1 || numEquipe > nbEquipe) {
                        erreurs += "Numero equipe incorrect ";
                    }
                    if (numProbleme < 1 || numProbleme > 8) {
                        erreurs += "Probleme incorrect ";
                    }
                    if (resoluStr != "oui" && resoluStr != "non") {
                        erreurs += "Resolu incorrect ";
                    }
                }

                if (erreurs != "" && nouveauRun) {
                    cout << erreurs << "\n";
                }
                else if (nouveauRun && erreurs == "") {

                    // On effectue les traitements

                    bool trouve(false) /*, trouve1(false), trouve2(false)*/;

                    // Si le renu existe deja
                    for (size_t i(0); i < tabRun.size(); i++) {
                        Run courant(tabRun[i]);
                        if (courant.getEquipe().getNum() == numEquipe && courant.getCas().getNum() == numCas && courant.getProbleme().getNum() == numProbleme) {
                            trouve = true;

                            if (resoluStr == "oui") {
                                courant.setTempsConsomme(tempsConsomme);
                                for (size_t j(0); j < tabEquipeCas.size(); j++) {
                                    EquipeCas equipeCas = tabEquipeCas[j];
                                    if (equipeCas.getEquipe().getNum() == numEquipe && equipeCas.getCas().getNum() == numCas) {
                                        equipeCas.setNbreResolu();
                                        equipeCas.setTempsTotal(courant.getTempsConsomme());
                                        tabEquipeCas[j] = equipeCas;
                                    }
                                }
                                tabRun[i] = courant;
                            }
                            else {
                                courant.setPenalite();
                                tabRun[i] = courant;
                            }
                        }
                    }

                    if (trouve == false) {
                        //cout << "Nouveau run\n" ;
                        Run nouveau(numCas, tempsConsomme, numEquipe, numProbleme);

                        EquipeCas equipeCas(numEquipe, numCas);
                        int occurence(0);
                        for (size_t j(0); j < tabEquipeCas.size(); j++) {
                            EquipeCas courant = tabEquipeCas[j];

                            if (courant.getEquipe().getNum() == numEquipe && courant.getCas().getNum() == numCas) {
                                trouve = true;
                                equipeCas = courant;
                                occurence = j;
                            }
                        }

                        /*EquipeCas equipeCas( numEquipe, numCas) ;*/

                        if (resoluStr == "oui") {
                            nouveau.setTempsConsomme(tempsConsomme);
                            equipeCas.setNbreResolu();
                            equipeCas.setTempsTotal(tempsConsomme);
                            if (trouve == false) {
                                tabEquipeCas.push_back(equipeCas);
                            }
                            else {
                                tabEquipeCas[occurence].setTempsTotal(tempsConsomme);
                                tabEquipeCas[occurence].setNbreResolu();
                            }
                            tabRun.push_back(nouveau);
                        }
                        else {
                            nouveau.setPenalite();
                            tabRun.push_back(nouveau);
                            if (trouve == false)
                                tabEquipeCas.push_back(equipeCas);
                        }
                    }
                }
            } while (nouveauRun);
        }
    } while (nouveauCas);

    for (int i(0); i < numCas; i++) {

        Cas cas(tabCas[i]);
        cout << "Cas #" << cas.getNum() << ":\n";
        cout << "No.Equipe\tRang\tProblemes Resolus\t   Temps consomme\n";

        trier(tabEquipeCas, cas);
        vector<EquipeCas> equipes;
        for (size_t j(0); j < tabEquipeCas.size(); j++) {
            EquipeCas courant(tabEquipeCas[j]);
            if (courant.getCas().getNum() == cas.getNum() && courant.getRang() <= 3) {
                equipes.push_back(courant);
            }
        }
        //trier(equipes) ;

        for (size_t k(0); k < equipes.size(); k++) {
            cout << "\t" << equipes[k].getEquipe().getNum() << "\t" << equipes[k].getRang() << "\t\t\t" << equipes[k].getNbResolus() << "\t\t\t" << equipes[k].getTempsTotal() << "\n";
        }
    }

    return 0;
}
