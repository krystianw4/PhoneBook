#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

struct Adresat
{
    string imie, nazwisko, numerTelefonu, adresEmail, adres;
    int idUzytkownika, id;
};

struct Uzytkownik
{
    string login, haslo;
    int id;
};

string zamianaPierwszejLiteryNaDuzaAPozostaleNaMale(string pozycja)
{
    if (!pozycja.empty())
    {
        transform(pozycja.begin(), pozycja.end(), pozycja.begin(), ::tolower);
        pozycja[0] = toupper(pozycja[0]);
    }
    return pozycja;
}

vector<Adresat> wczytajAdresatowZPliku(int iloscAdresatow, Adresat adresaci, int idZalogowanegoUzytkownika)
{
    string linia;
    fstream plik;
    vector<Adresat> Adresaci;
    char szukanyZnak='|';

    plik.open("ksiazkaZAdresami.txt", ios::in);

    if(plik.good() == true)
    {
        while (!plik.eof())
        {
            for (int i=0; i<iloscAdresatow; i++)
            {
                getline(plik,linia);

                size_t pozycja1 = linia.find(szukanyZnak);
                adresaci.id = atoi((linia.substr(0,pozycja1)).c_str());

                size_t pozycja2 = linia.find(szukanyZnak, pozycja1 + 1);
                adresaci.idUzytkownika = atoi((linia.substr(pozycja1+1,(pozycja2-pozycja1-1))).c_str());

                size_t pozycja3 = linia.find(szukanyZnak, pozycja2 + 1);
                adresaci.imie = linia.substr(pozycja2+1,(pozycja3-pozycja2-1));

                size_t pozycja4 = linia.find(szukanyZnak, pozycja3 + 1);
                adresaci.nazwisko = linia.substr(pozycja3+1,(pozycja4-pozycja3-1));

                size_t pozycja5 = linia.find(szukanyZnak, pozycja4 + 1);
                adresaci.numerTelefonu = linia.substr(pozycja4+1,(pozycja5-pozycja4-1));

                size_t pozycja6 = linia.find(szukanyZnak, pozycja5 + 1);
                adresaci.adresEmail = linia.substr(pozycja5+1,(pozycja6-pozycja5-1));

                size_t pozycja7 = linia.find(szukanyZnak, pozycja6 + 1);
                adresaci.adres = linia.substr(pozycja6+1,(pozycja7-pozycja6-1));

                if (adresaci.idUzytkownika == idZalogowanegoUzytkownika)
                {
                    Adresaci.push_back(adresaci);
                }
            }
        }
    }
    plik.close();

    return Adresaci;
}

vector<Uzytkownik> wczytajUzytkownikowZPliku(int iloscUzytkownikow, Uzytkownik uzytkownicy)
{
    string linia;
    fstream plik;
    vector<Uzytkownik> Uzytkownicy;
    char szukanyZnak='|';

    plik.open("Uzytkownicy.txt", ios::in);

    if(plik.good()==true)
    {
        while (!plik.eof())
        {
            for (int i=0; i<iloscUzytkownikow; i++)
            {
                getline(plik,linia);

                size_t pozycja1 = linia.find(szukanyZnak);
                uzytkownicy.id = atoi((linia.substr(0,pozycja1)).c_str());

                size_t pozycja2 = linia.find(szukanyZnak, pozycja1 + 1);
                uzytkownicy.login = linia.substr(pozycja1+1,(pozycja2-pozycja1-1));

                size_t pozycja3 = linia.find(szukanyZnak, pozycja2 + 1);
                uzytkownicy.haslo = linia.substr(pozycja2+1,(pozycja3-pozycja2-1));

                Uzytkownicy.push_back(uzytkownicy);
            }
        }
    }
    plik.close();

    return Uzytkownicy;
}

int sprawdzIloscAdresatow ()
{
    int iloscAdresatow;
    int numerLinii=0;

    fstream plik;
    plik.open("ksiazkaZAdresami.txt", ios::in);

    if(plik.good()==false)
        iloscAdresatow=0;

    else
    {
        string linia;
        while (getline(plik, linia))
        {
            numerLinii++;
        }
        iloscAdresatow=numerLinii;
    }

    plik.close();
    return iloscAdresatow;
}

int sprawdzIloscUzytkownikow ()
{
    int iloscUzytkownikow;
    int numerLinii=0;

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::in);

    if(plik.good()==false)
        iloscUzytkownikow=0;

    else
    {
        string linia;
        while (getline(plik, linia))
        {
            numerLinii++;
        }
        iloscUzytkownikow = numerLinii;
    }

    plik.close();
    return iloscUzytkownikow;
}

int sprawdzOstatnieId (int iloscAdresatow)
{
    fstream plik;
    string linia;
    int ostatnieId = 0;

    plik.open("ksiazkaZAdresami.txt", ios::in);
    for (int i = 0; i < iloscAdresatow; i++)
    {
        getline(plik,linia);

        char szukanyZnak='|';
        size_t pozycja = linia.find(szukanyZnak);
        ostatnieId = atoi((linia.substr(0,pozycja)).c_str());
    }
    plik.close();

    return ostatnieId;
}

void dodajAdresataDoKsiazki(Adresat adresaci, vector<Adresat>Adresaci, int iloscAdresatow, int idZalogowanegoUzytkownika)
{
    string imie, nazwisko, numerTelefonu, adresEmail, adres;
    int id;

    cout<<"Podaj imie: ";
    cin >> imie;
    cout<<"Podaj nazwisko: ";
    cin >> nazwisko;
    cout<<"Podaj numer telefonu: ";
    cin >> numerTelefonu;
    cout<<"Podaj e-mail: ";
    cin >> adresEmail;
    cout<<"Podaj adres: ";
    cin.sync();
    getline(cin, adres);

    fstream plik;
    plik.open("ksiazkaZAdresami.txt", ios::in);

    if(plik.good()==false)
        id = 1;

    else
        id = sprawdzOstatnieId(iloscAdresatow) + 1;

    plik.close();

    plik.open("ksiazkaZAdresami.txt", ios::out | ios::app);
    plik << id << '|' << idZalogowanegoUzytkownika << '|' << imie << '|' << nazwisko << '|' << numerTelefonu << '|' << adresEmail << '|' << adres << '|' << endl;
    plik.close();

    cout << "Adresat zostal dodany do ksiazki adresowej. " << endl;
    cout << imie << " " << nazwisko << endl;
    Sleep(2000);
}

void wyszukajAdresataPoImieniu(vector<Adresat>Adresaci)
{
    string szukaneImie;
    string poprawneDane = "";

    cout << "Podaj imie szukanego adresata: ";
    cin >> szukaneImie;
    szukaneImie = zamianaPierwszejLiteryNaDuzaAPozostaleNaMale(szukaneImie);

    for(int i=0; i < Adresaci.size(); i++)
    {
        if(Adresaci[i].imie==szukaneImie)
        {
            poprawneDane = "OK";
            cout<<endl;
            cout<<"Numer ID adresata:   " << Adresaci[i].id << endl;
            cout<<"Imie:                " << Adresaci[i].imie << endl;
            cout<<"Nazwisko:            " << Adresaci[i].nazwisko << endl;
            cout<<"Numer telefonu:      " << Adresaci[i].numerTelefonu << endl;
            cout<<"Adres Email:         " << Adresaci[i].adresEmail << endl;
            cout<<"Adres:               " << Adresaci[i].adres << endl ;
        }
    }
    cout<<endl;

    if(poprawneDane == "OK")
    {
        cout << "Wyswietlono wszystkie kontakty o takim imieniu." << endl;
    }
    else
    {
        cout << "Nie znaleziono adresata o takim imieniu.." << endl;
    }

    cout<<"Wcisnij enter aby wrocic do menu glownego.";
    getchar();
    getchar();
}

void wyszukajAdresataPoNazwisku(vector<Adresat>Adresaci)
{
    string szukaneNazwisko;
    string poprawneDane = "";

    cout << "Podaj nazwisko szukanego adresata: ";
    cin >> szukaneNazwisko;
    szukaneNazwisko = zamianaPierwszejLiteryNaDuzaAPozostaleNaMale(szukaneNazwisko);


    for(int i=0; i < Adresaci.size(); i++)
    {
        if(Adresaci[i].nazwisko == szukaneNazwisko)
        {
            poprawneDane = "OK";
            cout<<endl;
            cout<<"Numer ID adresata:   " << Adresaci[i].id << endl;
            cout<<"Imie:                " << Adresaci[i].imie << endl;
            cout<<"Nazwisko:            " << Adresaci[i].nazwisko << endl;
            cout<<"Numer telefonu:      " << Adresaci[i].numerTelefonu << endl;
            cout<<"Adres Email:         " << Adresaci[i].adresEmail << endl;
            cout<<"Adres:               " << Adresaci[i].adres << endl ;
        }
    }
    cout<<endl;

    if(poprawneDane == "OK")
    {
        cout << "Wyswietlono wszystkie kontakty o takim nazwisku." << endl;
    }
    else
    {
        cout << "Nie znaleziono adresata o takim nazwisku." << endl;
    }

    cout<<"Wcisnij enter aby wrocic do menu glownego.";
    getchar();
    getchar();
}

void wyswietlWszystkichAdresatow(vector<Adresat> Adresaci)
{
    fstream plik;
    plik.open("ksiazkaZAdresami.txt", ios::in);

    if(plik.good()==false)
    {
        cout<<"Twoja ksiazka adresowa jest pusta." << endl;
    }

    else
    {
        for(int i=0; i < Adresaci.size(); i++)
        {
            cout<<endl;
            cout<<endl;
            cout<<"Numer ID adresata:   " << Adresaci[i].id << endl;
            cout<<"Imie:                " << Adresaci[i].imie << endl;
            cout<<"Nazwisko:            " << Adresaci[i].nazwisko << endl;
            cout<<"Numer telefonu:      " << Adresaci[i].numerTelefonu << endl;
            cout<<"Adres Email:         " << Adresaci[i].adresEmail << endl;
            cout<<"Adres:               " << Adresaci[i].adres << endl ;
        }
    }
    plik.close();

    cout<<endl;
    cout<<"Wcisnij enter aby wrocic do menu glownego.";
    getchar();
    getchar();

}

void usunAdresata (int iloscAdresatow, vector<Adresat> Adresaci)
{
    int id;
    char potwierdzenieWyboru;
    cout << "Podaj numer ID adresata, ktorego chcesz usunac: ";
    cin >> id;
    cout << "Czy na pewno chcesz usunac adresata o numerze ID: " << id << "? (potwierdz klawiszem t/n): ";
    cin >> potwierdzenieWyboru;
    cout << endl;
    bool warunek = false;

    if (potwierdzenieWyboru == 't')
    {
        for(int i=0; i<Adresaci.size(); i++)
        {
            if (Adresaci[i].id == id)
                warunek = true;
        }

        if (warunek == false)
        {
            cout << "Adresat o podanym numerze ID nie istnieje!" << endl;
        }

        else
        {
            fstream plik, plik2;
            string linia;

            plik.open("ksiazkaZAdresami.txt", ios::in);
            plik2.open("ksiazka_tymczasowa.txt", ios::out);

            for (int i=0; i < iloscAdresatow; i++)
            {
                getline(plik,linia);

                char szukanyZnak='|';
                size_t pozycja = linia.find(szukanyZnak);
                int sprawdzId = atoi((linia.substr(0,pozycja)).c_str());

                if (sprawdzId != id)
                {
                    plik2 << linia << endl;
                }
            }

            plik.close();
            plik2.close();

            remove("ksiazkaZAdresami.txt");
            rename( "ksiazka_tymczasowa.txt", "ksiazkaZAdresami.txt" );

            cout << "Adresat zostal usuniety.";
        }

        cout << endl;
        cout << "Wcisnij enter aby wrocic do menu glownego.";
        getchar();
        getchar();
    }
}

void edytujAdresata (int iloscAdresatow, vector<Adresat> Adresaci)
{
    int id;
    char wyborMenu;
    string zmienioneDane;
    string poprawneId="";

    cout << "Podaj numer ID adresata, ktorego chcesz edytowac: ";
    cin >> id;

    for(int i = 0; i < Adresaci.size(); i++)
    {
        if(Adresaci[i].id == id)
        {
            poprawneId = "ID poprawne";
        }
    }

    if (poprawneId == "ID poprawne")
    {
        cout << "Edycja adresata." << endl << endl;
        cout << "1. Edytuj imie." << endl;
        cout << "2. Edytuj nazwisko." << endl;
        cout << "3. Edytuj numer telefonu." << endl;
        cout << "4. Edytuj adres email." << endl;
        cout << "5. Edytuj adres." << endl;
        cout << "6. Powrot do menu." << endl;
        cout << "Twoj wybor: ";
        cin >> wyborMenu;
        cout << endl;

        if (wyborMenu == '1')
        {
            for(int i = 0; i < Adresaci.size(); i++)
            {
                if(Adresaci[i].id == id)
                {
                    cout << "Aktualne imie: " << Adresaci[i].imie <<endl;
                    cout << "Zmiana na : " ;
                    cin >> zmienioneDane;
                    Adresaci[i].imie = zmienioneDane;
                    cout << endl << "Imie zostalo zmienione."<< endl;
                }
            }
        }

        else if (wyborMenu == '2')
        {
            for(int i = 0; i < Adresaci.size(); i++)
            {
                if(Adresaci[i].id == id)
                {
                    cout << "Aktualne nazwisko: " << Adresaci[i].nazwisko <<endl;
                    cout << "Zmiana na : " ;
                    cin >> zmienioneDane;
                    Adresaci[i].nazwisko = zmienioneDane;
                    cout << endl << "Nazwisko zostalo zmienione."<< endl;
                }
            }
        }

        else if (wyborMenu == '3')
        {
            for(int i = 0; i < Adresaci.size(); i++)
            {
                if(Adresaci[i].id == id)
                {
                    cout << "Aktualny numer telefonu : " << Adresaci[i].numerTelefonu <<endl;
                    cout << "Zmiana na : " ;
                    cin >> zmienioneDane;
                    Adresaci[i].numerTelefonu = zmienioneDane;
                    cout << endl << "Numer telefonu zostal zmieniony."<< endl;
                }
            }
        }

        else if (wyborMenu == '4')
        {
            for(int i = 0; i < Adresaci.size(); i++)
            {
                if(Adresaci[i].id == id)
                {
                    cout << "Aktualny adres email: " << Adresaci[i].adresEmail <<endl;
                    cout << "Zmiana na : " ;
                    cin >> zmienioneDane;
                    Adresaci[i].adresEmail = zmienioneDane;
                    cout << endl << "Adres email zostal zmieniony."<< endl;
                }
            }
        }

        else if (wyborMenu == '5')
        {
            for(int i = 0; i < Adresaci.size(); i++)
            {
                if(Adresaci[i].id == id)
                {
                    cout << "Aktualny adres: " << Adresaci[i].adres <<endl;
                    cout << "Zmiana na : " ;
                    cin.sync();
                    getline(cin, zmienioneDane);
                    Adresaci[i].adres = zmienioneDane;
                    cout << endl << "Adres zostal zmieniony."<< endl;
                }
            }
        }

        else if (wyborMenu=='6')
        {
            exit(0);
        }

        fstream plik, plik2;
        string linia;

        plik.open("ksiazkaZAdresami.txt", ios::in);
        plik2.open("ksiazka_tymczasowa.txt", ios::out);

        for (int i=0; i < iloscAdresatow; i++)
        {
            getline(plik,linia);

            char szukanyZnak='|';
            size_t pozycja = linia.find(szukanyZnak);
            int sprawdzId = atoi((linia.substr(0,pozycja)).c_str());

            if (sprawdzId == id)
            {
                for(int zmienionaPozycja = 0; zmienionaPozycja < Adresaci.size(); zmienionaPozycja++)
                {
                    if(Adresaci[zmienionaPozycja].id == id)
                    {
                        plik2 << Adresaci[zmienionaPozycja].id << '|' << Adresaci[zmienionaPozycja].idUzytkownika << '|' << Adresaci[zmienionaPozycja].imie << '|' << Adresaci[zmienionaPozycja].nazwisko << '|' << Adresaci[zmienionaPozycja].numerTelefonu << '|' << Adresaci[zmienionaPozycja].adresEmail << '|' << Adresaci[zmienionaPozycja].adres << '|' << endl;
                    }
                }
            }
            else
            {
                plik2 << linia << endl;
            }
        }

        plik.close();
        plik2.close();

        remove("ksiazkaZAdresami.txt");
        rename( "ksiazka_tymczasowa.txt", "ksiazkaZAdresami.txt" );
    }

    else
    {
        cout << "Kontakt o podanym numerze ID nie istnieje." << endl;
    }

    cout << endl;
    cout << "Wcisnij enter aby wrocic do menu glownego.";
    getchar();
    getchar();
}

void rejestracjaUzytkownika (int iloscUzytkownikow, vector<Uzytkownik> Uzytkownicy)
{
    int id;
    string loginUzytkownika, hasloUzytkownika;
    cout << "Podaje login uzytkownika: ";
    cin >> loginUzytkownika;

    int i = 0;
    while (i < iloscUzytkownikow)
    {
        if (Uzytkownicy[i].login == loginUzytkownika)
        {
            cout << "Taki login uzytkownika juz istnieje. Wpisz inny login uzytkownika: ";
            cin >> loginUzytkownika;
            i = 0;
        }
        else
        {
            i++;
        }
    }
    cout << "Podaj haslo: ";
    cin >> hasloUzytkownika;

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::in);

    if(plik.good()==false)
        id = 1;
    else
        id = Uzytkownicy[iloscUzytkownikow-1].id + 1;

    plik.close();

    plik.open("Uzytkownicy.txt", ios::out | ios::app);
    plik << id << '|' << loginUzytkownika << '|' << hasloUzytkownika << '|' << endl;
    plik.close();

    cout << "Konto uzytkownika zostalo zalozone.";
    Sleep(1000);
}

int logowanieUzytkownika (int iloscUzytkownikow, vector<Uzytkownik> Uzytkownicy)
{
    string loginUzytkownika, hasloUzytkownika;
    cout << "Podaj nazwe uzytkownika: ";
    cin >> loginUzytkownika;

    int i = 0;
    while (i < iloscUzytkownikow)
    {
        if (Uzytkownicy[i].login == loginUzytkownika)
        {
            for (int proba=0; proba < 3; proba++)
            {
                cout << "Podaj haslo. Pozostalo prob: "  << 3-proba << ": ";
                cin >> hasloUzytkownika;
                if (Uzytkownicy[i].haslo == hasloUzytkownika)
                {
                    cout << "Zalogowales sie." << endl;
                    Sleep (1000);
                    return Uzytkownicy[i].id;
                }
            }
            cout << "Podales 3 razy bledne haslo! Odczekaj 3 sekundy przed kolejna proba." << endl;
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout << "Podany uzytkownik nie istnieje!";
    Sleep (1500);
    return 0;
}

void zmienHaslo (int iloscUzytkownikow, vector<Uzytkownik> Uzytkownicy, int idZalogowanegoUzytkownika)
{
    fstream plik;
    string hasloUzytkownika;
    cout << "Podaj nowe haslo: ";
    cin >> hasloUzytkownika;

    for (int i=0; i < iloscUzytkownikow; i++)
    {
        if (Uzytkownicy[i].id == idZalogowanegoUzytkownika)
        {
            Uzytkownicy[i].haslo = hasloUzytkownika;
            cout << "Haslo zostalo zmienione."<<endl;
            Sleep (1500);
        }
    }

    plik.open("Uzytkownicy.txt", ios::out);
    for(int i = 0; i < iloscUzytkownikow; i++)
    {
        plik << Uzytkownicy[i].id << '|' << Uzytkownicy[i].login << '|' << Uzytkownicy[i].haslo << '|' << endl;
    }
    plik.close();
}

void wyswietlMenuKsiazki()
{
    Adresat adresaci;
    Uzytkownik uzytkownicy;

    int iloscAdresatow = sprawdzIloscAdresatow();
    int iloscUzytkownikow = sprawdzIloscUzytkownikow();

    vector<Adresat> Adresaci;
    vector<Uzytkownik> Uzytkownicy = wczytajUzytkownikowZPliku(iloscUzytkownikow, uzytkownicy);

    char wyborMenuLogowania;
    char wyborMenuGlowne;

    int idZalogowanegoUzytkownika = 0;

    while(1)
    {
        if (idZalogowanegoUzytkownika == 0)
        {
            system("cls");
            cout << "*******KSIAZKA ADRESOWA*******" << endl;
            cout << "Wybierz jedna z opcji: " << endl;
            cout << "1. Rejestracja." << endl;
            cout << "2. Logowanie." << endl;
            cout << "9. Zakoncz program." << endl;
            cout << "Twoj wybor: ";
            cin >> wyborMenuLogowania;
            cout << endl;

            if (wyborMenuLogowania=='1')
            {
                rejestracjaUzytkownika (iloscUzytkownikow, Uzytkownicy);
                iloscUzytkownikow = sprawdzIloscUzytkownikow();
                Uzytkownicy = wczytajUzytkownikowZPliku(iloscUzytkownikow, uzytkownicy);
            }

            else if (wyborMenuLogowania=='2')
            {
                idZalogowanegoUzytkownika = logowanieUzytkownika (iloscUzytkownikow, Uzytkownicy);
            }

            else if (wyborMenuLogowania=='1')
            {
                rejestracjaUzytkownika (iloscUzytkownikow, Uzytkownicy);
                iloscUzytkownikow = sprawdzIloscUzytkownikow();
                Uzytkownicy = wczytajUzytkownikowZPliku(iloscUzytkownikow, uzytkownicy);
            }

            else if (wyborMenuLogowania=='9')
            {
                exit(0);
            }
        }

        else
        {
            system("cls");
            cout << "*******KSIAZKA ADRESOWA*******" << endl;
            cout << "Wybierz jedna z opcji: " << endl;
            cout << "1. Dodaj adresata." << endl;
            cout << "2. Wyszukaj adresata po imieniu." << endl;
            cout << "3. Wyszukaj adresata po nazwisku." << endl;
            cout << "4. Wyswietl wszystkich adresatow." << endl;
            cout << "5. Usun adresta." << endl;
            cout << "6. Edytuj adresata." << endl;
            cout << "7. Zmien haslo." << endl;
            cout << "8. Wyloguj sie." << endl;
            cout << "9. Zakoncz program." << endl;
            cout << "Twoj wybor: ";
            cin >> wyborMenuGlowne;
            cout << endl;

            iloscAdresatow = sprawdzIloscAdresatow();
            Adresaci = wczytajAdresatowZPliku(iloscAdresatow, adresaci, idZalogowanegoUzytkownika);

            if (wyborMenuGlowne=='1')
            {
                dodajAdresataDoKsiazki(adresaci, Adresaci, iloscAdresatow, idZalogowanegoUzytkownika);
            }

            else if (wyborMenuGlowne=='2')
            {
                wyszukajAdresataPoImieniu(Adresaci);
            }

            else if (wyborMenuGlowne=='3')
            {
                wyszukajAdresataPoNazwisku(Adresaci);
            }

            else if (wyborMenuGlowne=='4')
            {
                wyswietlWszystkichAdresatow(Adresaci);
            }

            else if (wyborMenuGlowne=='5')
            {
                usunAdresata(iloscAdresatow, Adresaci);
                iloscAdresatow = sprawdzIloscAdresatow();
            }

            else if (wyborMenuGlowne=='6')
            {
                edytujAdresata(iloscAdresatow, Adresaci);
            }

            else if (wyborMenuGlowne=='7')
            {
                zmienHaslo(iloscUzytkownikow, Uzytkownicy, idZalogowanegoUzytkownika);
                Uzytkownicy = wczytajUzytkownikowZPliku(iloscUzytkownikow, uzytkownicy);
            }

            else if (wyborMenuGlowne=='8')
            {
                idZalogowanegoUzytkownika = 0;
            }

            else if (wyborMenuGlowne=='9')
            {
                exit(0);
            }
        }
    }
}


int main()
{
    Adresat adresaci;
    Uzytkownik uzytkownicy;

    int iloscAdresatow = sprawdzIloscAdresatow();
    int iloscUzytkownikow = sprawdzIloscUzytkownikow();

    vector<Adresat> Adresaci;
    vector<Uzytkownik> Uzytkownicy = wczytajUzytkownikowZPliku(iloscUzytkownikow, uzytkownicy);
    wyswietlMenuKsiazki();
}
