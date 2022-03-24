#pragma once

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif


class Sucelje
{
public:
    void clear() {
        if (system("CLS")) system("clear");
    }

    void meni(cls::glavna g) {
        clear();
        std::cout << "### Main ###" << std::endl;
        std::cout << "1.Upis artikla" << std::endl;
        std::cout << "2.Ispis artikla" << std::endl;
        std::cout << "3.Promjena artikla" << std::endl;
        std::cout << "4.Brisanje artikla" << std::endl;
        std::cout << "5.Provjera rokova" << std::endl;
        std::cout << "6.Password promjena" << std::endl;
        std::cout << "7.Izlaz" << std::endl << std::endl << std::endl;
        std::cout << "420.Auto unos test podataka" << std::endl << ">";

        int a;
        std::cin >> a;

        switch (a) {
        case 1:
            clear();
            upis(g);
        case 2:
            clear();
            ispis(g);
        case 3:
            clear();
            promjena(g);
        case 4:
            clear();
            brisanje(g);
        case 5:
            clear();
            rokovi(g);
        case 6:
            clear();
            password_change(g);
        case 7:
            exit1(g);
        case 420:
            clear();
            testPod(g);
        }
    }

    void exit1(cls::glavna g) {
        clear();

        std::cout << "Saving data..." << std::endl;
        g.saveData();

        std::cout << "Exiting!!!";
        exit(0);
    }

    void login(cls::glavna g)
    {
        std::string password;

        std::cout << "### Login ###\n";
        std::cout << "Password: ";
        std::cin >> password;

        if (g.checkPass(password) == true) {
            std::cout << "Password OK!";
            meni(g);
        }
        else {
            std::cout << "Bad Password";
            login(g);
        }
    }

    void password_change(cls::glavna g) {
        std::string password;
        std::string passOld;
        std::string password2;

        std::cout << "### Promjena passworda ###" << std::endl;
        std::cout << "Stari password: ";
        std::cin >> passOld;
        std::cout << "Novi password:";
        std::cin >> password;
        std::cout << "Potvrdi password:";
        std::cin >> password2;

        if (password == password2) {
            if (g.ChangePassword(password, passOld) == true) {
                std::cout << "Passwordi promijenjen";
                Sleep(500);
                clear();
                login(g);
            }
            else {
                std::cout << "Pogresan stari password.";
                Sleep(500);
                clear();
                meni(g);
            }
        }
        else {
            std::cout << "Passwordi nisu isti.";
            Sleep(500);
            clear();
            meni(g);
        }

    }

    void upis(cls::glavna g) {
        std::string ime;
        std::string rok;
        int kolicina1;
        double kolicina2;
        double cijena;
        int odabir;

        std::cout << "\n\n1. Proizvod na kolicinu\n2. Proizvod na kilazu\n";
        std::cin >> odabir;

        switch (odabir) {
        case 1:
            std::cout << "Unesi ime: ";
            std::cin >> ime;
            std::cout << "Unesi kolicinu: ";
            std::cin >> kolicina1;
            std::cout << "Unesi cijenu: ";
            std::cin >> cijena;
            std::cout << "Unesi rok oblika yyyy-mm-dd ili N/A: ";
            std::cin >> rok;

            if (rok == "N/A") { rok = "N/A"; }
            else if (rok.size() != 10) { rok = "1998-11-29"; }

            g.UpisProizvodaPaket(cls::PaketProizvod(ime, kolicina1, cijena, rok));

            break;
        case 2:
            std::cout << "Unesi ime: ";
            std::cin >> ime;
            std::cout << "Unesi kolicinu u kg: ";
            std::cin >> kolicina2;
            std::cout << "Unesi cijenu: ";
            std::cin >> cijena;
            std::cout << "Unesi rok oblika yyyy-mm-dd ili N/A: ";
            std::cin >> rok;

            if (rok == "N/A") { rok = "N/A"; }
            else if (rok.size() != 10) { rok = "1998-11-29"; }

            g.UpisProizvaodaKilaza(cls::KilazaProizvod(ime, kolicina2, cijena, rok));

            break;
        }


        clear();
        meni(g);
    }

    void ispis(cls::glavna g) {
        g.ispisProizvoda();

        if (system("pause")) system("read");
        clear();
        meni(g);
    }

    void promjena(cls::glavna g) {
        int idx;
        std::cout << "Unesite id proizvoda za promjenu: ";
        std::cin >> idx;

        g.promjenaArtikla(idx);
        if (system("pause")) system("read");

        clear();
        meni(g);
    }

    void brisanje(cls::glavna g) {
        int idx;
        std::cout << "Unesite id proizvoda za brisanje: ";
        std::cin >> idx;

        g.brisanjeProizvoda(idx);
        std::cout << "Proizvod izbrisan!!!" << std::endl;
        if (system("pause")) system("read");

        clear();
        meni(g);
    }

    void rokovi(cls::glavna g) {
        std::string datum;
        std::cout << "### Rokovi ###" << std::endl;
        std::cout << "Unesite datum isteka roka formata yyyy-mm-dd\n>";
        std::cin >> datum;

        g.datumIsteka(datum);

        if (system("pause")) system("read");
        clear();
        meni(g);
    }

    void testPod(cls::glavna g) {
        g.UpisProizvodaPaket(cls::PaketProizvod("Maslac", 64, 9.99, "2022-06-22"));
        g.UpisProizvaodaKilaza(cls::KilazaProizvod("Banana", 26.84, 9.99, "2022-03-01"));
        g.UpisProizvodaPaket(cls::PaketProizvod("Coca Cola", 106, 7.99, "2023-06-22"));
        g.UpisProizvodaPaket(cls::PaketProizvod("Jana", 24, 6.99, "2026-06-22"));
        g.UpisProizvaodaKilaza(cls::KilazaProizvod("Kruska", 1.86, 9.99, "2021-11-29"));

        g.ispisProizvoda();
        if (system("pause")) system("read");
        clear();
        meni(g);
    }


private:
};

