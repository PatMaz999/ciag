#include <iostream>
#include <initializer_list>
#include <cmath>

//popraw przypadek pustej listy inizjalizacyjnej (konstruktor)
//mechanizm kopiowania i przenoszenia
//dodaj funkcje wypisz();

using namespace std;

/*******************************deklaracje******************************************/

class ciag;
ostream& operator<<(ostream& strumien, ciag& c); //ciag const

/*******************************ciag************************************************/

class ciag {
private:
    int rozmiar; //liczymy od 0
    int stopien;
    //char znak; //dla konstruktora ze stringiem
    void wypisz_wartosc(ostream& strumien, const double* liczba, const int sto/*, bool ostatni = false*/);
    void wypisz_stopien(ostream& strumien, const int liczba/*, bool ostatni = false*/);
    //void znak(ostream& strumien, const double* liczba, bool ostatni = false);
protected:
    double* wzor;
public:
    ciag() : rozmiar(0), stopien(0)/*, znak('+')*/, wzor(new double[1]) { wzor[0] = 0; };
    ciag(initializer_list<double> lista/*, char zn = '+'*/); //znak bardziej jako dodatek
    ~ciag() { delete[] wzor; };
    friend ostream& operator<<(ostream& strumien, ciag & c); //ciag const
    //void wypisz();
    double suma(int n); // dla ci¹gu arytmetycznego
};

//////////////////*konstruktory*/

ciag::ciag(initializer_list<double> lista/*, char zn*/): /*znak(zn),*/ rozmiar(lista.size() - 1){
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
            c.wypisz_wartosc(strumien, c.wzor + i, c.rozmiar - i/*, true*/);
            break;
        }
        c.wypisz_wartosc(strumien, c.wzor + i, c.rozmiar - i);
        if (c.wzor[i+1] > 0 /*&& ostatni == false*/)
            strumien << " + ";
        else if(c.wzor[i + 1] != 0)
            strumien << " ";
    }
    return strumien;
}

void ciag::wypisz_wartosc(ostream& strumien, const double* liczba, const int sto/*, bool ostatni*/) {
    if (*liczba == -1) //je¿eli liczba wynosi -1 dodaj na pocz¹tku znak '-' i wykonaj operacje dla liczby 1
        strumien << "- ";
    if (*liczba == 1 || *liczba == -1) {
        if(sto != 0)
            wypisz_stopien(strumien, sto/*, ostatni*/);
        else
            strumien << *liczba;
    }
    else if (*liczba != 1 && liczba != 0){
        if (*liczba > 0) {
            strumien << *liczba;
            wypisz_stopien(strumien, sto/*, ostatni*/);
        }
        else if (*liczba < 0) {
            strumien << "- " << abs(*liczba);
            wypisz_stopien(strumien, sto/*, ostatni*/);
        }
        //wypisz_stopien(strumien, sto/*, ostatni*/); //zamiast dwóch oddzielnych instrukcji, z jakiegoœ powodu nie dzia³a
    }

    //if (*liczba > 0 && ostatni == false)
    //    strumien << " + ";
    //else
    //    strumien << " ";
}

void ciag::wypisz_stopien(ostream& strumien, const int sto/*, bool ostatni*/) {
    if (sto > 1) {
        strumien << "n^" << sto;
        //if (ostatni == false)
        //    strumien << " + ";
    }
    else if (sto == 1) {
        strumien << "n";
        //if (ostatni == false)
        //    strumien << " + ";
    }
}

//void ciag::znak(ostream& strumien, const double* liczba, bool ostatni) {
//    if (*liczba > 0 && ostatni == false)
//        strumien << " + ";
//}

////////////////////*suma*/

double ciag::suma(int n){
    double sum = 0.0;
    int sto = stopien; //nie modyfikuj stopnia
    for (int i = rozmiar - stopien; i < rozmiar; ++i) {
        sum += wzor[i] * pow(n, sto--);
    }
    return sum;
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
    ciag cba{0,0,-4,1,-2,0,0,-3,0,1,0};
    //ciag abc{ {0,2,0,1,0}, '-' };
    //ciag cba{0,1,0,1,0};
    cout << cba << "\t\t"/* << cba << endl*/;
    cout << cba.suma(2);
    //ciag abcd{ {1} };
    //cout << endl << abc.rozmiar << " " << abc.stopien;
}