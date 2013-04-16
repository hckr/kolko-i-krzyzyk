#include <iostream>
#define Z 3 /* rozmiar planszy */
#define L 3 /* iloœæ znaków obok siebie wymagana do wygranej */

using namespace std;

char tab[Z][Z] = {};
unsigned const char granica = 197;
unsigned const char pion = 179;
unsigned const char poziom = 196;
// ramka [ asciitable.com ]
	unsigned const char gora_lewa = 201;
	unsigned const char gora_prawa = 187;
	unsigned const char dol_lewa = 200;
	unsigned const char dol_prawa = 188;
	unsigned const char pion_prawa = 186;
	unsigned const char srodek_lewa = 204;
	unsigned const char srodek_prawa = 185;
	unsigned const char poziom_prawa = 205;
	unsigned const char poziom_gora = 203;
	unsigned const char poziom_dol = 202;
//

void rysuj_plansze() {
	cout << "  ";
	for (int i = 1; i <= Z; ++i) {
		cout << (i<11 ? " " : "") << i;
	}
	cout << "\n  " << gora_lewa;
	for (int rt = 0; rt < Z; ++rt) {
		cout << poziom_prawa;
		if (rt < Z - 1) cout << poziom_gora;
		else cout << gora_prawa;
	}
	cout << "\n";
	for (int i = 0; i < Z; ++i) {
		cout << (i<9 ? " " : "") << i+1 << pion_prawa;
		for (int j = 0; j < Z; ++j) {
			cout << (tab[i][j] ? tab[i][j] : ' ');
			if (j < Z - 1) cout << pion;
		}
		cout << pion_prawa << "\n";
		if (i < Z - 1) cout << "  " << srodek_lewa;
		for (int x = 0; x < Z; ++x) {
			if (i < Z - 1) {
				cout << poziom;
				if (x < Z - 1) cout << granica;
				else cout << srodek_prawa << "\n";
			}
		}
	}
	cout << "  " << dol_lewa;
	for (int rb = 0; rb < Z; ++rb) {
		cout << poziom_prawa;
		if (rb < Z - 1) cout << poziom_dol;
		else cout << dol_prawa;
	}
	cout << "\n\n";
}

void ruch(bool czy_iksy, int wiersz, int kolumna) {
	tab[wiersz - 1][kolumna - 1] = (czy_iksy ? 'x' : 'o');
}

bool czy_wolne(int wiersz, int kolumna) {
	return tab[wiersz - 1][kolumna - 1] == 0;
}

bool czy_w_zasiegu(int wsp) {
	return (wsp > 0 && wsp <= Z);
}

bool czy_wygral(bool czy_iksy, int wiersz, int kolumna) {
	char szukany = (czy_iksy ? 'x' : 'o');
	int ile_juz=0; // ile ju¿ trafi³o nam siê po rz¹d
	// L - ilosc wymagana do wygranej
	// kolumna:
	for(int x = 0; x < Z; ++x) {
		if(tab[x][kolumna-1]==szukany) {
			if(++ile_juz==L) return true;
		} else {
			ile_juz=0;
		}
	}
	//
	ile_juz=0;
	// wiersz:
	for(int y = 0; y < Z; ++y) {
		if(tab[wiersz-1][y]==szukany) {
			if(++ile_juz==L) return true;
		} else {
			ile_juz=0;
		}
	}
	//
	ile_juz=0;
	// pierwsza przek¹tna:
	int x = wiersz - L;
	int y = kolumna - L;
	for(; (x < wiersz + L - 1) && (y < kolumna + L - 1); ++x, ++y) {
		if(!(czy_w_zasiegu(x+1) && czy_w_zasiegu(y+1))) continue;
		if(tab[x][y]==szukany) {
			if(++ile_juz==L) return true;
		}
	}
	//
	ile_juz=0;
	// druga przek¹tna:
	x = wiersz - L;
	y = kolumna + L - 2;
	for(; (x < wiersz + L - 1) && (y > kolumna - L - 1); ++x, --y) {
		if(!(czy_w_zasiegu(x+1) && czy_w_zasiegu(y+1))) continue;
		if(tab[x][y]==szukany) {
			if(++ile_juz==L) return true;
		}
	}
	//
	return false;
}

int main(int argc, char * argv[]) {
poczatek_gry:
	bool ktos_wygral = false;
	char kto_zaczyna;
	cout << "Kto zaczyna - (k)rzyzyki czy k(o)lka? ";
	do {
		cin >> kto_zaczyna;
	} while (!(kto_zaczyna=='k' || kto_zaczyna=='o'));
	bool ruch_x = (kto_zaczyna=='k');
	int kolumna, wiersz, ile_ruchow = 0;
	system("cls");
	rysuj_plansze();
	while (!ktos_wygral && ile_ruchow < Z * Z) {
		++ile_ruchow;
		bool podano_wsp = false;
		cout << "Podaj wspolrzedne dla ruchu \"" << (ruch_x ? "x" : "o") << "\":\n";
		do {
			if (podano_wsp) cout << "To pole jest juz zajete! Podaj wspolrzedne jeszcze raz:\n";
			wiersz=0;
			kolumna=0;
			cout << "Wiersz: ";
			do {
				if (cin.fail()) {
					cin.clear();
					cin.get();
				}
				cin >> wiersz;
			} while (!czy_w_zasiegu(wiersz));
			cout << "Kolumna: ";
			do {
				if (cin.fail()) {
					cin.clear();
					cin.get();
				}
				cin >> kolumna;
			} while(!czy_w_zasiegu(kolumna));
			podano_wsp = true;
		} while(!czy_wolne(wiersz, kolumna));
		ruch(ruch_x, wiersz, kolumna);
		system("cls");
		rysuj_plansze();
		if(czy_wygral(ruch_x, wiersz, kolumna)) {
			ktos_wygral=true;
			cout << "Wygraly \"" << (ruch_x ? "x" : "o") << "\"!\n\n";
		}
		ruch_x = !ruch_x;
	}
	if (!ktos_wygral) cout << "Mamy remis!\n\n";
	char jeszcze_raz;
	cout << "Chcesz zagrac jeszcze raz (t/n)? ";
	do {
		cin >> jeszcze_raz;
	} while (!(jeszcze_raz=='t' || jeszcze_raz=='n'));
	if(jeszcze_raz=='t') {
		for(int i = 0; i < Z; ++i)
			for(int j = 0; j < Z; ++j)
				tab[i][j]=0;
		goto poczatek_gry;
	}
	return 0;
}