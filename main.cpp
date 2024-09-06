#include <iostream>
#include <initializer_list>

//popraw przypadek pustej listy inizjalizacyjnej (konstruktor)
//mechanizm kopiowania i przenoszenia
//dodaj funkcje wypisz();

using namespace std;

/*******************************ciag************************************************/
class ciag;
ostream& operator<<(ostream& strumien, ciag & c); //ciag const
class ciag {
private:
    int rozmiar; //liczymy od 0
    int stopien;
    void wypisz_wartosc(ostream& strumien, const double* liczba, const int sto, bool ostatni = false);
    void wypisz_stopien(ostream& strumien, const int liczba, bool ostatni = false);
protected:
    double* wzor;
public:
    ciag() : rozmiar(0), stopien(0), wzor(new double[1]) { wzor[0] = 0; };
    ciag(initializer_list<double> lista);
    ~ciag() { delete[] wzor; };
    friend ostream& operator<<(ostream& strumien, ciag & c); //ciag const
    //void wypisz();
};

//////////////////*konstruktory*/

ciag::ciag(initializer_list<double> lista): rozmiar(lista.size() - 1){
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

////////////////////*operator<<*/

ostream& operator<<(ostream& strumien, ciag& c) { //ciag const// //brag referencji do obiektu ciag powoduje podwójne wywo³anie destruktora
    if (c.rozmiar == 0) {
        strumien << c.wzor[0] << endl;
        return strumien;
    }
    int ile_zer = 0;
    for (int i = c.rozmiar; i >= 0; i--) {
        if (c.wzor[i] == 0)
            ++ile_zer;
        else
            break;
    }
    for (int i = 0; i <= c.rozmiar; ++i) {
        if ((i + ile_zer) == c.rozmiar) {
            c.wypisz_wartosc(strumien, c.wzor + i, c.rozmiar - i, true);
            break;
        }
        c.wypisz_wartosc(strumien, c.wzor + i, c.rozmiar - i);
    }
    return strumien;
}

void ciag::wypisz_wartosc(ostream& strumien, const double* liczba, const int sto, bool ostatni) {
    if (*liczba > 1) {
        strumien << *liczba;
        wypisz_stopien(strumien, sto, ostatni);
    }
    else if (*liczba == 1) {
        if(sto != 0)
            wypisz_stopien(strumien, sto, ostatni);
        else
            strumien << *liczba;
    }
}

void ciag::wypisz_stopien(ostream& strumien, const int sto, bool ostatni) {
    if (sto > 1) {
        strumien << "n^" << sto;
        if (ostatni == false)
            strumien << " + ";
    }
    else if (sto == 1) {
        strumien << "n";
        if (ostatni == false)
            strumien << " + ";
    }
}

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
    cout << abc << "\t" << abc;
    //ciag abcd{ {1} };
    //cout << endl << abc.rozmiar << " " << abc.stopien;
}