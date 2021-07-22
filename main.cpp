#include <iostream>
#include <windows.h>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Adresat
{
    string imie, nazwisko, numerTelefonu, adresEmail, adres;
    int idAdresata = 0;
};

string konwersjaIntNaString ( int liczba)
{
    ostringstream ss;
    ss << liczba;
    string lancuch = ss.str();
    return lancuch;
}

string zamianaPierwszejLiteryNaDuzaAPozostaleNaMale(string pozycja)
{
    if (!pozycja.empty())
    {
        transform(pozycja.begin(), pozycja.end(), pozycja.begin(), ::tolower);
        pozycja[0] = toupper(pozycja[0]);
    }
    return pozycja;
}

void dodajAdresataDoKsiazki(vector <Adresat> &adresaci)
{
    string imie, nazwisko, adres, numerTelefonu, adresEmail;
    string liniaZDanymiAdresata = "";
    Adresat kontakt;

    cout << endl << "Dodawanie nowego adresata." << endl << endl;
    cout << "Podaj imie: ";
    cin >> imie;
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    cout << "Podaj numer telefonu: ";
    cin.sync();
    getline(cin,numerTelefonu);
    cout << "Podaj adres email: ";
    cin >> adresEmail;
    cout << "Podaj adres: ";
    cin.sync();
    getline(cin,adres);

    if (adresaci.empty() == true)
    {
        kontakt.idAdresata = 1;
    }
    else
    {
        kontakt.idAdresata = adresaci.back().idAdresata + 1;
    }

    kontakt.imie = imie;
    kontakt.nazwisko = nazwisko;
    kontakt.numerTelefonu = numerTelefonu;
    kontakt.adresEmail = adresEmail;
    kontakt.adres = adres;

    adresaci.push_back(kontakt);

    fstream plik;
    plik.open("ksiazkaZAdresami.txt", ios::out);

    if (plik.good() == true)
    {
        for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            liniaZDanymiAdresata += konwersjaIntNaString(itr -> idAdresata) + '|';
            liniaZDanymiAdresata += itr -> imie + '|';
            liniaZDanymiAdresata += itr -> nazwisko + '|';
            liniaZDanymiAdresata += itr -> numerTelefonu + '|';
            liniaZDanymiAdresata += itr -> adresEmail + '|';
            liniaZDanymiAdresata += itr -> adres + '|';

            plik << liniaZDanymiAdresata << endl;
            liniaZDanymiAdresata = "";
        }
        plik.close();
        cout << "Adresat zostal dodany do ksiazki adresowej." << endl;
        system("pause");
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego adresata." << endl;
        system("pause");
    }
}

void wczytajAdresatowZPliku(vector <Adresat> &adresaci)
{
    string linia;
    string slowo;
    int iloscKresekPionowych = 0;
    int ileWyjacZnakow = 0;
    int poczatek = 0 ;
    int iloscAdresatow = 0;
    fstream plik;
    Adresat pusty;

    adresaci.clear();
    plik.open("ksiazkaZAdresami.txt",ios::in);
    if (plik.good() == true)
    {
        while (getline(plik,linia))
        {
            adresaci.push_back(pusty);
            iloscAdresatow++;
            ileWyjacZnakow = 0;
            poczatek = 0;
            iloscKresekPionowych = 0;

            for (int i = 0; i < linia.size(); i++)
            {
                ileWyjacZnakow = i - poczatek;
                if (linia[i] == '|')
                {
                    iloscKresekPionowych++;
                    slowo = linia.substr (poczatek,ileWyjacZnakow);
                    switch (iloscKresekPionowych)
                    {
                    case 1:
                        adresaci[iloscAdresatow - 1].idAdresata = atoi(slowo.c_str());
                        break;
                    case 2:
                        adresaci[iloscAdresatow - 1].imie = slowo;
                        break;
                    case 3:
                        adresaci[iloscAdresatow - 1].nazwisko = slowo;
                        break;
                    case 4:
                        adresaci[iloscAdresatow - 1].numerTelefonu = slowo;
                        break;
                    case 5:
                        adresaci[iloscAdresatow - 1].adresEmail = slowo;
                        break;
                    case 6:
                        adresaci[iloscAdresatow - 1].adres = slowo;
                        break;
                    }
                    poczatek = poczatek + ileWyjacZnakow + 1;
                }
            }
        }
        plik.close();
    }
}

void wyswietlWszystkichAdresatow(vector <Adresat> &adresaci)
{
    for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
        cout << endl;
        cout << "Numer ID:          " << itr -> idAdresata << endl;
        cout << "Imie:              " << itr -> imie << endl;
        cout << "Nazwisko:          " << itr -> nazwisko << endl;
        cout << "Numer telefonu:    " << itr -> numerTelefonu << endl;
        cout << "Adres email:       " << itr -> adresEmail << endl;
        cout << "Adres:             " << itr -> adres << endl;
        cout << endl;
    }
    system("pause");
}

void wyszukajAdresataPoImieniu(vector <Adresat> &adresaci)
{
    string szukaneImie;
    bool znalezionyAdresat = 0;
    cout << endl << "Podaj imie szukanego adresata: ";
    cin >> szukaneImie;
    szukaneImie = zamianaPierwszejLiteryNaDuzaAPozostaleNaMale(szukaneImie);

    for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
        if (itr -> imie == szukaneImie)
        {
            znalezionyAdresat = 1;
            cout << endl;
            cout << "Numer ID:          " << itr -> idAdresata << endl;
            cout << "Imie:              " << itr -> imie << endl;
            cout << "Nazwisko:          " << itr -> nazwisko << endl;
            cout << "Numer telefonu:    " << itr -> numerTelefonu << endl;
            cout << "Adres email:       " << itr -> adresEmail << endl;
            cout << "Adres:             " << itr -> adres << endl;
            cout << endl;
        }
    }

    if(!znalezionyAdresat)
    {
        cout << endl << "Nie znaleziono adresata o tym imieniu." << endl << endl;
    }
    system("pause");
}

void wyszukajAdresataPoNazwisku(vector <Adresat> &adresaci)
{
    string szukaneNazwisko;
    bool znalezionyAdresat = 0;
    cout << endl << "Podaj nazwisko szukanego adresata: ";
    cin >> szukaneNazwisko;
    szukaneNazwisko = zamianaPierwszejLiteryNaDuzaAPozostaleNaMale(szukaneNazwisko);

    for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
        if (itr -> nazwisko == szukaneNazwisko)
        {
            znalezionyAdresat = 1;
            cout << "Numer ID:          " << itr -> idAdresata << endl;
            cout << "Imie:              " << itr -> imie << endl;
            cout << "Nazwisko:          " << itr -> nazwisko << endl;
            cout << "Numer telefonu:    " << itr -> numerTelefonu << endl;
            cout << "Adres email:       " << itr -> adresEmail << endl;
            cout << "Adres:             " << itr -> adres << endl;
            cout << endl;
        }
    }

    if(!znalezionyAdresat)
    {
        cout << endl << "Nie znaleziono adresata o tym nazwisku." << endl << endl;
    }
    system("pause");
}

void edytujAdresata (vector <Adresat> &adresaci)
{
    string imie, nazwisko, numerTelefonu, adresEmail, adres;
    char wybranaPozycjaMenu;

    int poszukiwanyNumerID;
    bool znalezionyAdresat = 0;
    int pozycjaZnalezionegoAdresata = 0;

    cout << "Podaj numer ID adresata: ";
    cin >> poszukiwanyNumerID;

    for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
        if (itr -> idAdresata == poszukiwanyNumerID)
        {
            znalezionyAdresat = 1;
            system("cls");
            cout << "Edycja adresata." << endl << endl;
            cout << "Numer ID:          " << itr -> idAdresata << endl;
            cout << "Imie:              " << itr -> imie << endl;
            cout << "Nazwisko:          " << itr -> nazwisko << endl;
            cout << "Numer telefonu:    " << itr -> numerTelefonu << endl;
            cout << "Adres email:       " << itr -> adresEmail << endl;
            cout << "Adres:             " << itr -> adres << endl;
            cout << endl;
            cout << "1.Edytuj imie." << endl;
            cout << "2.Edytuj nazwisko." << endl;
            cout << "3.Edytuj numer telefonu." << endl;
            cout << "4.Edytuj adres emailowy." << endl;
            cout << "5.Edytuj adres kontaktowy." << endl;
            cout << "6.Powrot do menu." << endl<<endl;
            cin>> wybranaPozycjaMenu;

            switch(wybranaPozycjaMenu)
            {
            case '1':
                cout << "Podaj nowe imie: ";
                cin >>  imie;
                adresaci[pozycjaZnalezionegoAdresata].imie = imie;
                break;
            case '2':
                cout << "Podaj nowe nazwisko: ";
                cin >>  nazwisko;
                adresaci[pozycjaZnalezionegoAdresata].nazwisko = nazwisko;
                break;
            case '3':
                cout << "Podaj nowy numer telefonu: ";
                cin.sync();
                getline(cin,numerTelefonu);
                adresaci[pozycjaZnalezionegoAdresata].numerTelefonu = numerTelefonu;
                break;
            case '4':
                cout << "Podaj nowy adres email: ";
                cin >>  adresEmail;
                adresaci[pozycjaZnalezionegoAdresata].adresEmail = adresEmail;
                break;
            case '5':
                cout << "Podaj nowy adres: ";
                cin.sync();
                getline(cin,adres);
                adresaci[pozycjaZnalezionegoAdresata].adres = adres;
                break;
            default :
                break;
            }
            cout << "Edycja adresata przebiegla pomyslnie." << endl << endl;

        }
        pozycjaZnalezionegoAdresata++;
    }

    if(!znalezionyAdresat)
    {
        cout << endl << "Nie znaleziono osoby o podanym numerze ID." << endl << endl;
        system("pause");
    }
}

void usunAdresata (vector <Adresat> &adresaci)
{
    int poszukiwanyNumerID;
    char potwierdzenieWyboru;

    cout << "Podaj numer ID adresata, ktorego chcesz usunac: ";
    cin >> poszukiwanyNumerID;
    cout << "Czy na pewno chcesz usunac tego adresata? Kliknij t: " << endl;
    cin >> potwierdzenieWyboru;
    if (potwierdzenieWyboru == 't')
        for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {

            if (itr -> idAdresata == poszukiwanyNumerID)
            {
                itr = adresaci.erase(itr);
                cout << "Adresat zostal usuniety." << endl << endl;
                system("pause");
                break;
            }
        }
}

void zapisDanychDoPliku (vector <Adresat> &adresaci)
{
    fstream plik;
    string liniaZDanymiAdresata = "";
    plik.open("ksiazkaZAdresami.txt", ios::out);

    if (plik.good() == true)
    {
        for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            liniaZDanymiAdresata += konwersjaIntNaString(itr -> idAdresata) + '|';
            liniaZDanymiAdresata += itr -> imie + '|';
            liniaZDanymiAdresata += itr -> nazwisko + '|';
            liniaZDanymiAdresata += itr -> numerTelefonu + '|';
            liniaZDanymiAdresata += itr -> adresEmail + '|';
            liniaZDanymiAdresata += itr -> adres + '|';

            plik << liniaZDanymiAdresata << endl;
            liniaZDanymiAdresata = "";
        }
        plik.close();
        cout << "Dane zostaly zapisane." << endl;
        system("pause");
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
}

void wyswietlMenuKsiazki()
{
    vector <Adresat> adresaci;
    while (1)
    {
        char wybor;
        wczytajAdresatowZPliku(adresaci);
        system("cls");
        cout << "*******KSIAZKA ADRESOWA*******" << endl;
        cout << "Wybierz jedna z opcji: " << endl;
        cout << "1.Dodaj adresata." << endl;
        cout << "2.Wyszukaj po imieniu." << endl;
        cout << "3.Wyszukaj po nazwisku." << endl;
        cout << "4.Wyswietl wszystkich adresatow." << endl;
        cout << "5.Usun adresata." << endl;
        cout << "6.Edytuj adresata." << endl;
        cout << "9.Zakoncz program." << endl<<endl;
        cout << "Twoj wybor: " << endl;
        cin>> wybor;


        if (wybor == '1')
        {
            dodajAdresataDoKsiazki(adresaci);
        }
        else if (wybor == '2')
        {
            wyszukajAdresataPoImieniu(adresaci);
        }
        else if (wybor == '3')
        {
            wyszukajAdresataPoNazwisku(adresaci);
        }

        else if (wybor == '4')
        {
            wyswietlWszystkichAdresatow(adresaci);
        }
        else if (wybor == '5')
        {
            usunAdresata(adresaci);
            zapisDanychDoPliku(adresaci);
        }
        else if (wybor == '6')
        {
            edytujAdresata(adresaci);
            zapisDanychDoPliku(adresaci);
        }
        else if (wybor == '9')
        {
            exit(0);
        }
    }
}

int main()
{
    vector <Adresat> adresaci;
    wczytajAdresatowZPliku(adresaci);
    wyswietlMenuKsiazki();
}
