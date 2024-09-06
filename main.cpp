#include <iostream>

using namespace std;

/*******************************ciag************************************************/
class ciag {
private:
    int rozmiar; //liczymy od 0
    int stopien;
    static void wypisz_wartosc(double* liczba, int sto, bool ostatni = false);
    static void wypisz_stopien(int liczba, bool ostatni = false);
protected:
    double* wzor;
public:
    ciag() : rozmiar(0), stopien(0), wzor(new double[1]) { wzor[0] = 0; };
    ciag(initializer_list<double> lista);
    ~ciag() { delete[] wzor; };
    void wypisz();
};

ciag::ciag(initializer_list<double> lista): rozmiar(lista.size() - 1){ //popraw przypadek pustej listy
    wzor = new double[lista.size()];
    for (int i = 0; i < lista.size(); ++i) {
        wzor[i] = *(lista.begin() + i);
    }
    stopien = rozmiar;
    for (int i = 0; i < lista.size(); ++i) {
        if (wzor[i] == 0)
            --stopien;
        else
            break;
    }
}
                                        /*wypisz*/
void ciag::wypisz() {
    if(rozmiar == 0){
        cout << wzor[0] << endl;
        return;
    }
    int ile_zer = 0;
    for (int i = rozmiar; i >= 0; i--) {
        if (wzor[i] == 0)
            ++ile_zer;
        else
            break;
    }
    for (int i = 0; i <= rozmiar; ++i) {
        if ((i + ile_zer) == rozmiar) {
            wypisz_wartosc(wzor + i, rozmiar - i, true);
            break;
        }
        wypisz_wartosc(wzor + i, rozmiar - i);
    }
}

void ciag::wypisz_wartosc(double* liczba, int sto, bool ostatni) {
    if (*liczba > 1) {
        cout << *liczba;
        wypisz_stopien(sto, ostatni);
    }
    else if (*liczba == 1) {
        if(sto != 0)
            wypisz_stopien(sto, ostatni);
        else
            cout << *liczba;
    }
}

void ciag::wypisz_stopien(int sto, bool ostatni) {
    if (sto > 1) {
        cout << "n^" << sto;
        if (ostatni == false)
            cout << " + ";
    }
    else if (sto == 1) {
        cout << "n";
        if (ostatni == false)
            cout << " + ";
    }
}
                                        /*wypisz*/



/*******************************ciag_arytmetyczny************************************/
class ciag_arytmetyczny {

};

/*******************************ciag_geometryczny************************************/
class ciag_geometryczny {

};

/*******************************main*************************************************/
int main()
{
    ciag abc{0,0,0,1,2,0,0,3,0,0,0};
    abc.wypisz();
    //ciag abcd{ {1} };
    //cout << endl << abc.rozmiar << " " << abc.stopien;
}