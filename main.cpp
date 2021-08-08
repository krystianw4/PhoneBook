#include <iostream>
#include <windows.h>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Uzytkownik
{
    int idUzytkownika;
    string login, haslo;
};

struct Adresat
{
    int idAdresata, nrIdUzytkownika;
    string imie, nazwisko, numerTelefonu, adresEmail, adres;
};

string konwerjsaIntNaString (int liczba)
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

void rejestracjaUzytkownika(vector <Uzytkownik> &uzytkownicy)
{
    string loginUzytkownika, hasloUzytkownika;
    int idUzytkownika;
    string liniaZDanymiUzytkownika = "";
    Uzytkownik kontakt;

    cout << "Podaj login uzytkownika: ";
    cin >> loginUzytkownika;

    for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
    {
        while(itr -> login == loginUzytkownika)
        {
            cout << "Taki login uzytkownika juz istnieje. Wpisz inny login uzytkownika: ";
            cin >> loginUzytkownika;
        }
    }

    cout << "Podaj haslo: ";
    cin >> hasloUzytkownika;

    if (uzytkownicy.empty() == true)
    {
        kontakt.idUzytkownika = 1;
    }
    else
    {
        kontakt.idUzytkownika = uzytkownicy.back().idUzytkownika + 1;
    }

    kontakt.login = loginUzytkownika;
    kontakt.haslo = hasloUzytkownika;

    uzytkownicy.push_back(kontakt);

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out);

    if (plik.good() == true)
    {
        for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
        {
            liniaZDanymiUzytkownika += konwerjsaIntNaString(itr -> idUzytkownika) + '|';
            liniaZDanymiUzytkownika += itr -> login + '|';
            liniaZDanymiUzytkownika += itr -> haslo + '|';

            plik << liniaZDanymiUzytkownika << endl;
            liniaZDanymiUzytkownika = "";
        }
        plik.close();
    }
    cout<< "Konto uzytkownika zostalo zalozone." <<endl;
    Sleep(1000);
}

void wczytajUzytkownikowZPliku(vector <Uzytkownik> &uzytkownicy)
{
    string linia;
    string slowo;
    int iloscKresekPionowych = 0;
    int ileWyjacZnakow = 0;
    int poczatek = 0 ;
    int iloscUzytkownikow = 0;
    fstream plik;
    Uzytkownik pusty;

    uzytkownicy.clear();
    plik.open("Uzytkownicy.txt",ios::in);
    if (plik.good() == true)
    {
        while (getline(plik,linia))
        {
            uzytkownicy.push_back(pusty);
            iloscUzytkownikow++;
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
                        uzytkownicy[iloscUzytkownikow - 1].idUzytkownika = atoi(slowo.c_str());
                        break;
                    case 2:
                        uzytkownicy[iloscUzytkownikow - 1].login = slowo;
                        break;
                    case 3:
                        uzytkownicy[iloscUzytkownikow - 1].haslo = slowo;
                        break;
                    }
                    poczatek = poczatek + ileWyjacZnakow + 1;
                }
            }
        }
        plik.close();
    }
}

int logowanieUzytkownika(vector <Uzytkownik> &uzytkownicy)
{
    string loginUzytkownika, hasloUzytkownika;
    bool znalezionyUzytkownik = 0;
    int proby = 0;
    cout << "Podaj login uzytkownika: ";
    cin >>  loginUzytkownika;

    for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
    {
        if(itr -> login == loginUzytkownika)
        {
            znalezionyUzytkownik = 1;
            for(int iloscProb = 0; iloscProb < 3; iloscProb++)
            {
                proby = iloscProb + 1;
                cout << "Podaj haslo uzytkownika. Pozostalo prob " << 3 - iloscProb << ": ";
                cin >> hasloUzytkownika;
                if (itr -> haslo == hasloUzytkownika)
                {
                    cout<< "Zalogowales sie."<<endl;
                    return itr -> idUzytkownika;
                }
            }
            if( proby == 3)
            {
                cout << "Podales 3 razy bledne haslo. Poczekaj 3 sekundy zanim sprobujesz ponownie." << endl;
            }
        }
    }

    if(!znalezionyUzytkownik)
    {
        cout << "Nie ma uzytkownika z takim loginem." << endl;
    }

    Sleep(1500);
    return 0;
}

void zapiszDaneUzytkownikowDoPliku (vector <Uzytkownik> &uzytkownicy)
{
    fstream plik;
    string liniaZDanymiUzytkownika = "";
    plik.open("Uzytkownicy.txt", ios::out);

    if (plik.good() == true)
    {
        for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
        {
            liniaZDanymiUzytkownika += konwerjsaIntNaString(itr -> idUzytkownika) + '|';
            liniaZDanymiUzytkownika += itr -> login + '|';
            liniaZDanymiUzytkownika += itr -> haslo + '|';

            plik << liniaZDanymiUzytkownika << endl;
            liniaZDanymiUzytkownika = "";
        }
        plik.close();
        cout << "Dane uzytkownika zostaly zapisane." << endl;
        system("pause");
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
}

int znajdzKolejnyNumerIdAdresata ()
{
    string linia;
    string slowo;
    int iloscKresekPionowych = 0;
    int ileWyjacZnakow = 0;
    int poczatek = 0 ;
    int najwiekszyNrId = 0;
    int aktualnyNrId = 0;
    int kolejnyNrId = 0;
    fstream plik;

    plik.open("ksiazkaZAdresami.txt",ios::in);
    if (plik.good() == true)
    {
        while (getline(plik,linia))
        {
            ileWyjacZnakow = 0;
            poczatek = 0;
            iloscKresekPionowych = 0;

            for (int i = 0; i < linia.size(); i++)
            {
                ileWyjacZnakow = i - poczatek;
                if (linia[i] == '|')
                {
                    iloscKresekPionowych++;
                    slowo = linia.substr (poczatek, ileWyjacZnakow);
                    aktualnyNrId = atoi(slowo.c_str());
                    if ( iloscKresekPionowych == 1 )
                    {
                        if (aktualnyNrId > najwiekszyNrId)
                        {
                            najwiekszyNrId = aktualnyNrId;
                        }
                    }
                }
            }
        }
    }
    kolejnyNrId = najwiekszyNrId + 1;
    return kolejnyNrId;
}

void dodajAdresataDoKsiazki(vector <Adresat> &adresaci, int idZalogowanegoUzytkownika)
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

    kontakt.idAdresata = znajdzKolejnyNumerIdAdresata();
    kontakt.nrIdUzytkownika = idZalogowanegoUzytkownika;
    kontakt.imie = imie;
    kontakt.nazwisko = nazwisko;
    kontakt.numerTelefonu = numerTelefonu;
    kontakt.adresEmail = adresEmail;
    kontakt.adres = adres;

    adresaci.push_back(kontakt);

    fstream plik;
    plik.open("ksiazkaZAdresami.txt", ios::app);

    if (plik.good() == true)
    {
        liniaZDanymiAdresata += konwerjsaIntNaString(kontakt.idAdresata) + '|';
        liniaZDanymiAdresata += konwerjsaIntNaString(kontakt.nrIdUzytkownika) + '|';
        liniaZDanymiAdresata += kontakt.imie + '|';
        liniaZDanymiAdresata += kontakt.nazwisko + '|';
        liniaZDanymiAdresata += kontakt.numerTelefonu + '|';
        liniaZDanymiAdresata += kontakt.adresEmail + '|';
        liniaZDanymiAdresata += kontakt.adres + '|';

        plik << liniaZDanymiAdresata << endl;
        liniaZDanymiAdresata = "";

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

void usuwanieLiniiZPliku (int idZalogowanegoUzytkownika)
{
    vector <string> usunLinie;
    string linia;
    string slowo;
    int iloscKresekPionowych = 0;
    int ileWyjacZnakow = 0;
    int poczatek = 0 ;
    int idUzytkownikaZPliku;
    bool znalezionaLinia;

    fstream plik;
    ofstream nowyPlik;

    usunLinie.clear();
    plik.open("ksiazkaZAdresami.txt", ios::in);
    if (plik.good() == true)
    {
        while (getline(plik,linia))
        {
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
                    idUzytkownikaZPliku = atoi(slowo.c_str());
                    if ( iloscKresekPionowych == 2 && idZalogowanegoUzytkownika == idUzytkownikaZPliku)
                    {
                        usunLinie.push_back(linia);
                        break;
                    }
                    poczatek = poczatek + ileWyjacZnakow + 1;
                }
            }
        }
        plik.close();
    }

    nowyPlik.open("PlikBezLinii.txt");
    plik.open("ksiazkaZAdresami.txt", ios::in);

    while (getline(plik,linia))
    {
        znalezionaLinia = 0;
        for( int i = 0; i < usunLinie.size(); i++ )
        {
            if ( linia == usunLinie[i])
            {
                znalezionaLinia = 1;
            }
        }
        if (znalezionaLinia == 0)
            nowyPlik << linia << endl;
    }

    nowyPlik.close();
    plik.close();
    remove("ksiazkaZAdresami.txt");
    rename("PlikBezLinii.txt","ksiazkaZAdresami.txt");
}

void zapiszAdresatowUzytkownikaDoWektora (vector <Adresat> &adresaci, string linia, int iloscAdresatow)
{
    string slowo;
    int iloscKresekPionowych = 0;
    int ileWyjacZnakow = 0;
    int poczatek = 0 ;

    Adresat pusty;
    adresaci.push_back(pusty);

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
                adresaci[iloscAdresatow - 1].nrIdUzytkownika = atoi(slowo.c_str());
                break;
            case 3:
                adresaci[iloscAdresatow - 1].imie = slowo;
                break;
            case 4:
                adresaci[iloscAdresatow - 1].nazwisko = slowo;
                break;
            case 5:
                adresaci[iloscAdresatow - 1].numerTelefonu = slowo;
                break;
            case 6:
                adresaci[iloscAdresatow - 1].adresEmail = slowo;
                break;
            case 7:
                adresaci[iloscAdresatow - 1].adres = slowo;
                break;
            }
            poczatek = poczatek + ileWyjacZnakow + 1;
        }
    }
}

void wczytajAdresatowZPliku(vector <Adresat> &adresaci, int idZalogowanegoUzytkownika)
{

    string linia;
    string slowo;
    int iloscKresekPionowych = 0;
    int ileWyjacZnakow = 0;
    int poczatek = 0 ;
    int idUzytkownikaZPliku = 0;
    int iloscAdresatow = 0;
    fstream plik;

    adresaci.clear();
    plik.open("ksiazkaZAdresami.txt",ios::in);
    if (plik.good() == true)
    {
        while (getline(plik,linia))
        {
            ileWyjacZnakow = 0;
            poczatek = 0;
            iloscKresekPionowych = 0;

            for (int i = 0; i < linia.size(); i++)
            {
                ileWyjacZnakow = i - poczatek;
                if (linia[i] == '|')
                {
                    iloscKresekPionowych++;
                    slowo = linia.substr (poczatek, ileWyjacZnakow);
                    idUzytkownikaZPliku = atoi(slowo.c_str());
                    if ( iloscKresekPionowych == 2 && idZalogowanegoUzytkownika == idUzytkownikaZPliku)
                    {
                        iloscAdresatow++;
                        zapiszAdresatowUzytkownikaDoWektora(adresaci, linia, iloscAdresatow);
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
        cout << "Numer ID adresata: " << itr -> idAdresata << endl;
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
            cout << "Numer ID adresata: " << itr -> idAdresata << endl;
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
            cout << "Numer ID adresata: " << itr -> idAdresata << endl;
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
    char wybor;

    int poszukiwanyNrId;
    bool znalezionyAdresat = 0;
    int pozycjaZnalezionegoAdresata = 0;

    cout << "Podaj numer ID adresata: ";
    cin >> poszukiwanyNrId;

    for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
        if (itr -> idAdresata == poszukiwanyNrId)
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
            cout << "4.Edytuj adres email." << endl;
            cout << "5.Edytuj adres kontaktowy." << endl;
            cout << "6.Powrot do menu." << endl<<endl;
            cin>> wybor;

            switch(wybor)
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
        cout << endl << "Nie znaleziono adresata o podanym numerze ID." << endl << endl;
        system("pause");
    }
}

void usunAdresata (vector <Adresat> &adresaci)
{
    int poszukiwanyNrId;
    char potwierdzenieWyboru;

    cout << "Wyszukanie adresata. Podaj numer ID adresata: ";
    cin >> poszukiwanyNrId;
    cout << "Czy na pewno chcesz usunac tego adresata? Kliknij t: " << endl;
    cin >> potwierdzenieWyboru;

    if (potwierdzenieWyboru == 't')

        for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            if (itr -> idAdresata == poszukiwanyNrId)
            {
                itr = adresaci.erase(itr);
                cout << "Adresat zostal usuniety." << endl << endl;
                system("pause");
                break;
            }
        }
}

void zapiszDaneAdresatowDoPliku(vector <Adresat> &adresaci, int idZalogowanegoUzytkownika)
{
    fstream plik;
    string liniaZDanymiAdresata = "";

    usuwanieLiniiZPliku(idZalogowanegoUzytkownika);

    plik.open("ksiazkaZAdresami.txt", ios::out | ios::app);
    if (plik.good() == true)
    {
        for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            liniaZDanymiAdresata += konwerjsaIntNaString(itr -> idAdresata) + '|';
            liniaZDanymiAdresata += konwerjsaIntNaString(itr -> nrIdUzytkownika) + '|';
            liniaZDanymiAdresata += itr -> imie + '|';
            liniaZDanymiAdresata += itr -> nazwisko + '|';
            liniaZDanymiAdresata += itr -> numerTelefonu + '|';
            liniaZDanymiAdresata += itr -> adresEmail + '|';
            liniaZDanymiAdresata += itr -> adres + '|';

            plik << liniaZDanymiAdresata << endl;
            liniaZDanymiAdresata = "";
        }
        plik.close();
        cout << "Dane zostaly zapisne." << endl;
        system("pause");
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
}

void zmienHaslo(vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika)
{
    string hasloUzytkownika;
    int pozycjaZnalezionejOsoby = 0;
    cout << "Podaj nowe haslo: ";
    cin >> hasloUzytkownika;

    for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
    {
        if(itr -> idUzytkownika == idZalogowanegoUzytkownika)
        {
            uzytkownicy[pozycjaZnalezionejOsoby].haslo = hasloUzytkownika;
            cout << "Haslo zostalo zmienione"<< endl;
            Sleep(1500);
        }
        pozycjaZnalezionejOsoby++;
    }
}

void wyswietlMenuKsiazki()
{
    vector <Uzytkownik> uzytkownicy;
    vector <Adresat> adresaci;

    int idZalogowanegoUzytkownika = 0;

    wczytajUzytkownikowZPliku(uzytkownicy);
    char wybor;

    while(1)
    {
        wczytajUzytkownikowZPliku(uzytkownicy);
        if(idZalogowanegoUzytkownika == 0)
        {
            system("cls");
            cout << "*******KSIAZKA ADRESOWA*******" << endl;
            cout << "Wybierz jedna z opcji: " << endl;
            cout << "1.Rejestracja" << endl;
            cout << "2.Logowanie" << endl;
            cout << "3.Zakoncz program" << endl;
            cout << "Twoj wybor: " << endl;
            cin >> wybor;

            {
                if (wybor == '1')
                {

                    rejestracjaUzytkownika(uzytkownicy);
                }

                else if (wybor == '2')
                {

                    idZalogowanegoUzytkownika = logowanieUzytkownika(uzytkownicy);
                }
                else if (wybor == '3')
                {
                    exit(0);
                }
            }
        }
        else
        {
            wczytajAdresatowZPliku(adresaci, idZalogowanegoUzytkownika);
            system("cls");
            cout << "*******KSIAZKA ADRESOWA*******" << endl;
            cout << "Wybierz jedna z opcji: " << endl;
            cout << "1.Dodaj adresata." << endl;
            cout << "2.Wyszukaj adresata po imieniu." << endl;
            cout << "3.Wyszukaj adresata po nazwisku." << endl;
            cout << "4.Wyswietl wszystkich adresatow." << endl;
            cout << "5.Usun adresata." << endl;
            cout << "6.Edytuj adresata." << endl;
            cout << "7.Zmien haslo." << endl;
            cout << "8.Wyloguj sie." << endl<<endl;
            cout << "Twoj wybor: " << endl;
            cin>> wybor;

            {
                if (wybor == '1')
                {

                    dodajAdresataDoKsiazki(adresaci, idZalogowanegoUzytkownika);
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
                    zapiszDaneAdresatowDoPliku(adresaci, idZalogowanegoUzytkownika);
                }

                else if (wybor == '6')
                {
                    edytujAdresata(adresaci);
                    zapiszDaneAdresatowDoPliku(adresaci, idZalogowanegoUzytkownika);
                }

                else if (wybor == '7')
                {
                    zmienHaslo(uzytkownicy, idZalogowanegoUzytkownika);
                    zapiszDaneUzytkownikowDoPliku(uzytkownicy);
                }

                else if (wybor == '8')
                {
                    idZalogowanegoUzytkownika = 0;
                    system ("cls");
                    wyswietlMenuKsiazki();
                }
            }
        }
    }
}

int main()
{
    vector <Uzytkownik> uzytkownicy;
    vector <Adresat> adresaci;
    wczytajUzytkownikowZPliku(uzytkownicy);
    wyswietlMenuKsiazki();
}
