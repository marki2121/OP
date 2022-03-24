#pragma once


void meni(cls::glavna g) {
    clear();
    std::cout << "### Main ###" << std::endl;
    std::cout << "1.Upis artikla" << std::endl;
    std::cout << "2.Ispis artikla" << std::endl;
    std::cout << "3.Promjena artikla" << std::endl;
    std::cout << "4.Password promjena" << std::endl;
    std::cout << "5.Izlaz" << std::endl << ">";

    int a;
    std::cin >> a;

    switch (a) {
    case 1:
    case 2:
    case 3:
    case 4:
        clear();
        password_change(g);
    case 5:
        clear();
        std::cout << "Exiting!!!";
        exit(0);
    }
}