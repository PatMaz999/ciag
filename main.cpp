#include <iostream>
#include <initializer_list>
#include <cmath>
#include <string>

//popraw przypadek pustej listy inizjalizacyjnej (konstruktor)
//mechanizm kopiowania i przenoszenia
//dodaj funkcje wypisz();
//konstruktor dla string dzia³a tylko dla liczb dodatnich i nie obejmuje pomijania liczby 1 (np n^3 + 2)
//konstruktor dla string nie uwzglêdnia przypadku postawienie kilku kropek

using namespace std;

/*******************************deklaracje******************************************/

class ciag;
ostream& operator<<(ostream& strumien, ciag& c); //ciag const

/*******************************ciag************************************************/

class ciag {
private:
    int rozmiar; //liczymy od 1
    int stopien;
    //char znak; //dla konstruktora ze stringiem
    void wypisz_wartosc(ostream& strumien, const double* liczba, const int sto);
    void wypisz_stopien(ostream& strumien, const int liczba);
protected:
    double* wzor;
public:
    ciag() : rozmiar(0), stopien(0), wzor(new double[1]) { wzor[0] = 0; };
    ciag(initializer_list<double> lista);
    ciag(string napis);
    ~ciag() { delete[] wzor; };
    friend ostream& operator<<(ostream& strumien, ciag & c); //ciag const
    //void wypisz();
    double suma(int n); // dla ci¹gu arytmetycznego
};

//////////////////*konstruktory*/

ciag::ciag(initializer_list<double> lista): rozmiar(lista.size()){
    wzor = new double[rozmiar];
    for (int i = 0; i < lista.size(); ++i) {
        wzor[i] = *(lista.begin() + i);
    }
    stopien = rozmiar - 1;
    for (int i = 0; i < lista.size(); ++i) {
        if (wzor[i] == 0)
            --stopien;
        else
            break;
    }
}
// do zrobienia
// brak liczby (np n^2 + n)
// liczba nie jest podnoszona do potegi (proste przypadki)

ciag::ciag(string napis){
    string liczba = "";
    string liczba_stopien = "";
    int obecny_stopien = 0;
    double obecna_liczba = 0; //domyslnie 1 ???
    bool pierwszy_stopien = false;
    bool bylo_n = false;
    for (int i = 0; i < napis.size(); ++i) {
        if (isdigit(napis[i]) || napis[i] == '.') {
            for (; i < napis.size() && isdigit(napis[i]) && napis[i] != '.'; ++i)
                liczba += napis[i];
            --i; // jezeli przerywamy sprawdzanie to jestesmy o jeden indeks za daleko
            obecna_liczba = stof(liczba);
            liczba = "";
        }
        else if (isalpha(napis[i])) {
            bylo_n = true; //przed podnienieniem do potegi wystepuje n
            continue;
        }
        else if (napis[i] == '^' && bylo_n) {
            ++i;
            for (; i < napis.size() && isdigit(napis[i]); ++i)
                liczba_stopien += napis[i];
            //--i //nie ma --i bo kolejne jest ' '
            obecny_stopien = stoi(liczba_stopien);
            liczba_stopien = "";
            if (pierwszy_stopien == false) {
                this->rozmiar = obecny_stopien + 1;
                this->stopien = obecny_stopien; // konstrukcja obiektu
                this->wzor = new double[rozmiar]; // alokacja pamieci
                for (int j = 0; j < rozmiar; ++j) // przypisz 0 do tablicy
                    this->wzor[j] = 0;
                pierwszy_stopien = true;
            }
            wzor[this->stopien - obecny_stopien] = obecna_liczba;
            obecna_liczba = 0; //potrzebne bo jak nie ma liczby to w ostatnim przypisaniu jest domyœlnie 0
            obecny_stopien = 0;
            bylo_n = false; //podnieslismy do potegi wiec sprawdzamy kolejne
        }
        else if (bylo_n && napis[i] != '^') {
            wzor[this->stopien - 1] = obecna_liczba; //przedostatni element
            obecna_liczba = 0;
            bylo_n = false;
        }
    }
    if (bylo_n)
        wzor[this->stopien - 1] = obecna_liczba;
    else
        wzor[this->stopien] = obecna_liczba;
}

////////////////////*operator<<*/

ostream& operator<<(ostream& strumien, ciag& c) { //ciag const// //brag referencji do obiektu ciag powoduje podwójne wywo³anie destruktora
    if (c.rozmiar == 0) {
        strumien << c.wzor[0] << endl;
        return strumien;
    }
    int ile_zer = 0;
    for (int i = 0; i < c.rozmiar; ++i) {
        if (c.wzor[i] == 0)
            ++ile_zer;
        else
            break;
    }
    for (int i = ile_zer; i < c.rozmiar; ++i) {
        if (i == c.rozmiar - 1) {       //rozmiar - 1 bo indeksy liczymy od 0
            c.wypisz_wartosc(strumien, c.wzor + i, c.rozmiar - 1 - i); //ostatnie wywo³anie (bez dodawania + na koñcu)
            break;
        }
        c.wypisz_wartosc(strumien, c.wzor + i, c.rozmiar - 1 - i);
        if (c.wzor[i + 1] > 0) {
            strumien << " + ";
        }
        else if (c.wzor[i + 1] != 0) {
            strumien << " ";
        }
    }
    return strumien;
}

void ciag::wypisz_wartosc(ostream& strumien, const double* liczba, const int sto) {
    if (*liczba == -1) //je¿eli liczba wynosi -1 dodaj na pocz¹tku znak '-' i wykonaj operacje dla liczby 1
        strumien << "- ";
    if (*liczba == 1 || *liczba == -1) {
        if(sto != 0)
            wypisz_stopien(strumien, sto);
        else
            strumien << *liczba;
    }
    else if (*liczba != 1 && liczba != 0){
        if (*liczba > 0) {
            strumien << *liczba;
            wypisz_stopien(strumien, sto);
        }
        else if (*liczba < 0) {
            strumien << "- " << abs(*liczba);
            wypisz_stopien(strumien, sto);
        }
        //wypisz_stopien(strumien, sto); //zamiast dwóch oddzielnych instrukcji, z jakiegoœ powodu nie dzia³a
    }
}

void ciag::wypisz_stopien(ostream& strumien, const int sto) {
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

////////////////////*suma*/

double ciag::suma(int n){
    double sum = 0.0;
    int sto = stopien; //nie modyfikuj stopnia
    for (int i = rozmiar - 1 - stopien; i <= rozmiar; ++i) { // - 1 bo rozmiar liczymy od 1 a indeksy od 0, <= a nie < z tego samego powodu
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
    //ciag cba{0,0,0,-4,1,-2,0,0,-3,0,1,0,0,0};
    //ciag cba{3,0,0,1};
    ciag cba{"2n^3 + 2n^2 + 3n + 2"}; // dzia³a te¿ bez spacji
    //ciag cba{2,0,0};
    cout << cba << "\t\t"/* << cba << endl*/;
    cout << cba.suma(2);
    //ciag abcd{ {1} };
    //cout << endl << abc.rozmiar << " " << abc.stopien;
}