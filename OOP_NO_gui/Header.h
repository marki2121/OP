// Header.h
#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream> 

#define HEADER_H
#ifdef HEADER_H

int broj = 0;

namespace cls {
	class proizvodi {
	public:
		proizvodi(std::string ime_i, double cijena_i, std::string rokx) {
			id = broj;
			ime_artikla = ime_i;
			cijena = cijena_i;
			rok = rokx;
			broj++;
		}

		int id_get() {
			return id;
		}

		void change_id(int idx) {
			id = idx;
		}

		void changeIme(std::string imex) {
			ime_artikla = imex;
		}

		std::string getIme() {
			return ime_artikla;
		}

		void changeCijena(double cijenax) {
			cijena = cijenax;
		}

		double getCijena() {
			return cijena;
		}

		std::string getRok() {
			return rok;
		}

		void changeRok(std::string rokx) {
			rok = rokx;
		}


	private:
		int id;
		std::string ime_artikla;
		double cijena;
		std::string rok;
	};

	class PaketProizvod : public proizvodi {
	private:
		int kolicina;
	public:
		PaketProizvod(std::string ime_i, int kolicina_i, double cijena_i, std::string rokx)
			:proizvodi(ime_i, cijena_i, rokx) {
			kolicina = kolicina_i;
		}

		PaketProizvod(int idx, std::string ime_i, int kolicina_i, double cijena_i, std::string rokx)
			:proizvodi(ime_i, cijena_i, rokx) {
			kolicina = kolicina_i;
			change_id(idx);
		}

		void changeKolicina(int idx) {
			kolicina = idx;
		}

		int getKolicina() {
			return kolicina;
		}

		double getUkupnaCijena() {
			return (getCijena() * kolicina);
		}

		void print_proizvod() {
			std::cout << std::left << std::setw(5)  << id_get() << std::setw(30) << std::left << getIme() << std::setw(15) << std::left << getRok() << std::setw(10) << std::left << kolicina << std::setw(10) << std::left << getCijena() << std::setw(15) << std::left << std::fixed << std::setprecision(2) << getUkupnaCijena() << std::endl;
		}

		std::string send_proizvod() {
			std::string line;
			line = std::to_string(id_get()) + "," + getIme() + "," + getRok() + "," + std::to_string(getKolicina()) + "," + std::to_string(getCijena());
			return line;
		}

	};

	class KilazaProizvod : public proizvodi {
	private:
		double kolicina;
	public:
		KilazaProizvod(std::string ime_i, double kolicina_i, double cijena_i, std::string rokx)
			:proizvodi(ime_i, cijena_i, rokx) {
			kolicina = kolicina_i;
		}

		KilazaProizvod(int idx, std::string ime_i, double kolicina_i, double cijena_i, std::string rokx)
			:proizvodi(ime_i, cijena_i, rokx) {
			kolicina = kolicina_i;
			change_id(idx);
		}

		void changeKolicina(double idx) {
			kolicina = idx;
		}

		double getKolicina() {
			return kolicina;
		}

		double getUkupnaCijena() {
			return (getCijena() * kolicina);
		}

		void print_proizvod() {
			std::cout << std::left << std::setw(5) << id_get() << std::setw(30) << std::left << getIme() << std::setw(15) << std::left << getRok() << std::setw(10) << std::left << getKolicina() << std::setw(10) << std::left << getCijena() << std::setw(15) << std::left << std::fixed << std::setprecision(2) << getUkupnaCijena() << std::endl;
		}

		std::string send_proizvod() {
			std::string line;
			line = std::to_string(id_get()) + "," + getIme() + "," + getRok() + "," + std::to_string(getKolicina()) + "," + std::to_string(getCijena());
			return line;
		}
	};

	class glavna {
	private:
		std::string password;
		std::vector<KilazaProizvod> k;
		std::vector<PaketProizvod> p;
	public:

		glavna() {
			loadData();
		};

		//SAVE
		void saveData() {
			std::string line, line2;
			std::ofstream file;
			file.open("file.txt");

			file << "password," << password << std::endl;

			int size = p.size();
			for (int i = 0; i < size; i++) {
				PaketProizvod u1 = p[i];
				line2 = u1.send_proizvod();
				file << "koli" << "," << line2 << std::endl;
				line2 = "";
			}

			int size1 = k.size();
			for (int i = 0; i < size1; i++) {
				KilazaProizvod u = k[i];
				line = u.send_proizvod();
				line2 = u.send_proizvod();
				file << "kila" << "," << line << std::endl;
				line = "";
			}

			file << "id" << "," << broj << std::endl;

			file << "END";

			file.close();
		}

		//Brojac kod upisa ce bit u k zbog ovoga (rijesenje?! provjerit pri upisu el id veci od broja pa broj izjednacit)
		//LOAD
		void loadData() {
			std::fstream file;
			file.open("file.txt", std::fstream::in);
			std::string line;
			std::getline(file, line);
			if (line == "") {
				password = "admin";
			}
			else {
				file.close();
				std::string subline;
				std::stringstream X;
				std::fstream file;
				file.open("file.txt", std::fstream::in);
				bool pass = false;
				bool kol = false;
				bool kil = false;
				bool id = false;

				int idx = -1;
				std::string ime = "";
				std::string rok = "";
				int kolicina = -1;
				double kilaza = -1;
				double cijena = -1;
				int brojac = 0;

				std::getline(file, line);

				do {
					for (X.str(line); std::getline(X, subline, ','); ) {
						if (pass == true) {
							password = subline;
							pass = false;
						}
						else if (kol == true) {
							if (brojac == 0) { idx = std::stoi(subline); brojac++;  }
							else if (brojac == 1) { ime = subline; brojac++;
							}
							else if (brojac == 2) { rok = subline; brojac++;
							}
							else if (brojac == 3) { kolicina = std::stoi(subline); brojac++;
							}
							else if (brojac == 4) { cijena = std::stod(subline); brojac++;
							}
							else { 
								UpisProizvodaPaket(PaketProizvod(idx, ime, kolicina, cijena, rok)); 
								idx, kolicina = -1;
								ime, rok = "";
								kilaza, cijena = -1;
								kol = false;
								brojac = 0;
							}

						}
						else if (kil == true) {
							if (brojac == 0) { idx = std::stoi(subline); brojac++; }
							else if (brojac == 1) { ime = subline; brojac++; }
							else if (brojac == 2) { rok = subline; brojac++; }
							else if (brojac == 3) { kilaza = std::stod(subline); brojac++; }
							else if (brojac == 4) { cijena = std::stod(subline); brojac++; }
							else { 
								UpisProizvaodaKilaza(KilazaProizvod(idx, ime, kilaza, cijena, rok)); 
								idx, kolicina = -1;
								ime, rok = "";
								kilaza, cijena = -1;
								kil = false;
								brojac = 0;
							}
						}
						else if (id == true) {
							setBroj(std::stoi(subline));
						}

						if (subline == "password") {
							pass = true;
						}
						else if (subline == "koli") {
							kol = true;
						}
						else if (subline == "kila") {
							kil = true;
						}
						else if (subline == "id") {
							id = true; 
						}

					}
					std::getline(file, line);
					X.clear();
					if (line == "END") { break; }
				}while (true);
				file.close();
			}
		}

		void setBroj(int idx) {
			broj = idx;
		}

		bool checkPass(std::string pass1) {
			if(pass1 == password) { return true; }
			else { return false; };
		}

		bool ChangePassword(std::string password1, std::string passOld) {
			if (password == passOld) {
				password = password1;
				return true;
			}
			else return false;
		}

		std::string getPass() {
			return password;
		}

		void UpisProizvodaPaket(PaketProizvod s) {
			p.push_back(s);
		}

		void UpisProizvaodaKilaza(KilazaProizvod d) {
			k.push_back(d);
		}

		void ispisProizvoda() {
			double ukupna = 0;
			std::cout << std::left << std::setw(5) << "ID" << std::setw(30) << std::left << "Ime" << std::setw(15) << std::left << "Rok" << std::setw(10) << std::left << "Kolicina" << std::setw(10) << std::left << "Cijena" << std::setw(15) << std::left << "Ukupno" << std::endl;
			int size = k.size();
			for (int i = 0; i < size; i++) {
				KilazaProizvod u = k[i];
				u.print_proizvod();
				ukupna += u.getUkupnaCijena();
			}

			size = p.size();
			for (int i = 0; i < size; i++) {
				PaketProizvod u1 = p[i];
				u1.print_proizvod();
				ukupna += u1.getUkupnaCijena();
			}

			std::cout << "ukupna cijena artikala na stanju je: " << std::fixed << std::setprecision(2) << ukupna << std::endl;
		}

		void brisanjeProizvoda(int idx) {
			int size = k.size();
			for (int i = 0; i < size; i++) {
				KilazaProizvod u = k[i];
				if (u.id_get() == idx) {
					k.erase(k.begin()+i);
					break;
				}
			}

			size = p.size();
			for (int i = 0; i < size; i++) {
				PaketProizvod u = p[i];
				if (u.id_get() == idx) {
					p.erase(p.begin() + i);
					break;
				}
			}
		}

		void promjenaArtikla(int idx) {
			int size = k.size();
			for (int i = 0; i < size; i++) {
				KilazaProizvod u = k[i];
				if (u.id_get() == idx) {
					u.print_proizvod();

					std::string imex;
					std::string imexx;
					int idx;
					double kolicinax;
					double cijenax;


					idx = u.id_get();
					std::cout << std::endl << "Unesite nove vrijednosti ili ostavite prazno" << std::endl;
					std::cout << "Ime: ";
					std::getline(std::cin, imex);
					std::getline(std::cin, imex);

					if (imex != "") {
						u.changeIme(imex);
						imexx = u.getIme();
					}
					else imexx = u.getIme();

					imex = "";
					std::cout << "Kolicina: ";
					std::getline(std::cin, imex);

					if (imex != "") {
						kolicinax = std::stod(imex);
						u.changeKolicina(kolicinax);
						kolicinax = u.getKolicina();
					}
					else kolicinax = u.getKolicina();

					imex = "";
					std::cout << "Cijena: ";
					std::getline(std::cin, imex);

					if (imex != "") {
						cijenax = std::stod(imex);
						u.changeCijena(cijenax);
						cijenax = u.getCijena();
					}
					else cijenax = u.getCijena();

					imex = "";
					std::cout << "Rok: ";
					std::getline(std::cin, imex);

					if (imex != "" && imex.size() == 10 ) {
						u.changeRok(imex);
						imex = u.getRok();
					}
					else imex = u.getRok();

					std::cout << std::endl;

					brisanjeProizvoda(idx);
					UpisProizvaodaKilaza(cls::KilazaProizvod(idx, imexx, kolicinax, cijenax, imex));
				}
			}

			size = p.size();
			for (int i = 0; i < size; i++) {
				PaketProizvod u = p[i];
				if (u.id_get() == idx) {
					u.print_proizvod();

					std::string imex;
					std::string imexx;
					int idx;
					int kolicinax;
					double cijenax;

					idx = u.id_get();

					std::cout << std::endl << "Unesite nove vrijednosti ili ostavite prazno" << std::endl;
					std::cout << "Ime: ";
					std::getline(std::cin, imex);
					std::getline(std::cin, imex);

					if (imex != "") {
						u.changeIme(imex);
						imexx = u.getIme();
					}
					else imexx = u.getIme();


					imex = "";
					std::cout << "Kolicina: ";
					std::getline(std::cin, imex);

					if (imex != "") {
						kolicinax = std::stoi(imex);
						u.changeKolicina(kolicinax);
					}
					else kolicinax = u.getKolicina();

					imex = "";
					std::cout << "Cijena: ";
					std::getline(std::cin, imex);

					if (imex != "") {
						cijenax = std::stod(imex);
						u.changeCijena(cijenax);
					}
					else cijenax = u.getCijena();

					imex = "";
					std::cout << "Rok: ";
					std::getline(std::cin, imex);

					if (imex != "" && imex.size() == 10 ) {
						u.changeRok(imex);
						imex = u.getRok();
					}
					else imex = u.getRok();

					std::cout << std::endl;

					brisanjeProizvoda(idx);
					UpisProizvodaPaket(cls::PaketProizvod(idx, imexx, kolicinax, cijenax, imex));
				}
			}
		}

		void datumIsteka(std::string str) {
			int yyyy;
			int dd;
			int mm;
			int yyyy_p;
			int dd_p;
			int mm_p;
			std::string datum;

			std::cout << std::endl;
			std::cout << std::left << std::setw(5) << "ID" << std::setw(30) << std::left << "Ime" << std::setw(15) << std::left << "Rok" << std::setw(10) << std::left << "Kolicina" << std::setw(10) << std::left << "Cijena" << std::setw(15) << std::left << "Ukupno" << std::endl;

			yyyy = std::stoi(str.substr(0, 4));
			mm = std::stoi(str.substr(5, 2));
			dd = std::stoi(str.substr(8, 2));

			int size = k.size();
			for (int i = 0; i < size; i++) {
				KilazaProizvod u = k[i];
				datum = u.getRok();

				if(datum.size() == 10) {
					yyyy_p = std::stoi(datum.substr(0, 4));
					mm_p = std::stoi(datum.substr(5, 2));
					dd_p = std::stoi(datum.substr(8, 2));

					if (yyyy_p < yyyy) {
						u.print_proizvod();
					}
					else if (yyyy_p == yyyy) {
						if (mm_p < mm) {
							u.print_proizvod();
						}
						else if (mm_p == mm) {
							if (dd_p < dd) { u.print_proizvod(); }
						}
					}
				}
			}

			size = p.size();
			for (int i = 0; i < size; i++) {
				PaketProizvod u = p[i];
				datum = u.getRok();

				
				if(datum.size() == 10) {
					yyyy_p = std::stoi(datum.substr(0, 4));
					mm_p = std::stoi(datum.substr(5, 2));
					dd_p = std::stoi(datum.substr(8, 2));

					if (yyyy_p < yyyy) {
						u.print_proizvod();
					}
					else if (yyyy_p == yyyy) {
						if (mm_p < mm) {
							u.print_proizvod();
						}
						else if (mm_p == mm) {
							if (dd_p < dd) { u.print_proizvod(); }
						}
					}
				}
			}
		}
	};
}


#endif // HEADER_H
