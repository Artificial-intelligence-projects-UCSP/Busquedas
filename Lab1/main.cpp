#include <iostream>
#include <utility>
#include <vector>
#include <list>
using namespace std;
struct damas {
	list<pair<int, int>>Fichas_A;
	list<pair<int, int>>Fichas_B;
	int Numero_Fichas_A;
	int Numero_Fichas_B;
	list<pair<int, int>> Jugadores[2] = { Fichas_A ,Fichas_B };
	int max_X = 7;
	int min_X = 0;
	int max_Y = 7;
	int min_Y = 0;
	int turno;
	damas(int maximo_X, int minimo_X, int maximo_Y, int minimo_Y) {
		max_X = maximo_X;
		min_X = minimo_X;
		max_Y = maximo_Y;
		min_Y = minimo_Y;
		for (int i = min_X; i <= max_X; i = i + 2) {
			Fichas_A.push_back(make_pair(min_X + i, min_Y));
			Fichas_A.push_back(make_pair(min_X + i + 1, min_Y + 1));
			Fichas_A.push_back(make_pair(min_X + i, min_Y + 2));
			Fichas_B.push_back(make_pair(min_X + i + 1, max_Y - 2));
			Fichas_B.push_back(make_pair(min_X + i, max_Y - 1));
			Fichas_B.push_back(make_pair(min_X + i + 1, max_Y));
		}
		turno = 0;
		Numero_Fichas_A = 12;
		Numero_Fichas_B = 12;
	}
	damas(list<pair<int, int>>fichas_A, int numero_fichas_A, list<pair<int, int>>fichas_B, int numero_fichas_B, int Turno) {
		Fichas_A = fichas_A;
		Numero_Fichas_A = numero_fichas_A;
		Fichas_B = fichas_B;
		Numero_Fichas_B = numero_fichas_B;
		turno = Turno;
	}
	damas() {
		Numero_Fichas_A = 12;
		Numero_Fichas_B = 12;
	}
	int vacio(int x, int y) {
		list< pair<int, int>>::iterator it;
		if (turno == 0) {
			for (it = Fichas_A.begin(); it != Fichas_A.end() && ((*it).first != x || (*it).second != y); it++) {}
			if (it != Fichas_A.end())
				return 1;
			for (it = Fichas_B.begin(); it != Fichas_B.end() && ((*it).first != x || (*it).second != y); it++) {}
			if (it != Fichas_B.end())
				return -1;
		}
		else {
			for (it = Fichas_B.begin(); it != Fichas_B.end() && ((*it).first != x || (*it).second != y); it++) {}
			if (it != Fichas_B.end())
				return 1;
			for (it = Fichas_A.begin(); it != Fichas_A.end() && ((*it).first != x || (*it).second != y); it++) {}
			if (it != Fichas_A.end())
				return -1;
		}
		return 0;
	}
	bool mover(int Pieza_x, int Pieza_y, int x, int y) {
		if (x < min_X || x > max_X || y < min_Y || y > max_Y)
			return 0;
		list< pair<int, int>>::iterator it;
		if (turno == 0) {
			for (it = Fichas_A.begin(); it != Fichas_A.end() && ((*it).first != Pieza_x || (*it).second != Pieza_y); it++) {
			}
			if (it == Fichas_A.end())
				return 0;
			int VACIO = vacio(x, y);
			if (VACIO == 0) {
				(*it).first = x;
				(*it).second = y;
				return 1;
			}
			else if (VACIO == -1) {
				if (((x + (x - Pieza_x)) > max_X || (x + (x - Pieza_x)) < min_X || (y + (y - Pieza_y)) > max_Y || (y + (y - Pieza_y)) < min_Y) || vacio(x + (x - Pieza_x), y + (y - Pieza_y)) != 0)
					return 0;
				list< pair<int, int>>::iterator enemigo;
				for (enemigo = Fichas_B.begin(); enemigo != Fichas_B.end() && ((*enemigo).first != x || (*enemigo).second != y); enemigo++) {
				}
				if (enemigo == Fichas_B.end())
					return 0;
				Fichas_B.erase(enemigo);
				Numero_Fichas_B--;
				(*it).first = x + (x - Pieza_x);
				(*it).second = y + (y - Pieza_y);
				return 1;
			}
			return 0;
		}
		else {
			for (it = Fichas_B.begin(); it != Fichas_B.end() && ((*it).first != Pieza_x || (*it).second != Pieza_y); it++) {
			}
			if (it == Fichas_B.end())
				return 0;
			int VACIO = vacio(x, y);
			if (VACIO == 0) {
				(*it).first = x;
				(*it).second = y;
				return 1;
			}
			else if (VACIO == -1) {
				if (((x + (x - Pieza_x)) > max_X || (x + (x - Pieza_x)) < min_X || (y + (y - Pieza_y)) > max_Y || (y + (y - Pieza_y)) < min_Y) || vacio(x + (x - Pieza_x), y + (y - Pieza_y)) != 0)
					return 0;
				list< pair<int, int>>::iterator enemigo;
				for (enemigo = Fichas_A.begin(); enemigo != Fichas_A.end() && ((*enemigo).first != x || (*enemigo).second != y); enemigo++) {
				}
				if (enemigo == Fichas_A.end())
					return 0;
				Fichas_A.erase(enemigo);
				Numero_Fichas_A--;
				(*it).first = x + (x - Pieza_x);
				(*it).second = y + (y - Pieza_y);
				return 1;
			}
			return 0;
		}
	}
	void AcDatos(damas* PT) {
		Fichas_A = PT->Fichas_A;
		Fichas_B = PT->Fichas_B;
		Numero_Fichas_A = PT->Numero_Fichas_A;
		Numero_Fichas_B = PT->Numero_Fichas_B;
	}
	void VISUALIZAR() {
		list< pair<int, int>>::iterator it1;
		list< pair<int, int>>::iterator it2;
		int flag = 1;
		cout << " ";
		for (int j = min_X; j <= max_X; j++)
			cout << j;
		cout << endl;
		for (int i = min_Y; i <= max_Y; i++) {
			cout << i;
			for (int j = min_X; j <= max_X; j++) {
				flag = 1;
				for (it1 = Fichas_A.begin(); flag != 0 && it1 != Fichas_A.end(); it1++) {
					if ((*it1).first == j && (*it1).second == i) {
						flag = 0;
						cout << "o";
					}
				}
				for (it2 = Fichas_B.begin(); flag != 0 && it2 != Fichas_B.end(); it2++) {
					if ((*it2).first == j && (*it2).second == i) {
						flag = 0;
						cout << "x";
					}
				}
				if (flag == 1)
					cout << "*";
			}
			cout << endl;
		}
		cout << endl;
	}
};
struct Nodo {
	int nivel_max;
	int turno;
	damas* D;
	vector<Nodo*>VD;
	int Peso;
	int Mejor_Jugada;
	list<pair<int, int>>TFA;
	list<pair<int, int>>TFB;
	int numTFA;
	int numTFB;
	Nodo(list<pair<int, int>>fichas_A, int numero_fichas_A, list<pair<int, int>>fichas_B, int numero_fichas_B, int Turno, int nivel_maximo) {
		nivel_max = nivel_maximo;
		turno = Turno;
		D = new damas(fichas_A, numero_fichas_A, fichas_B, numero_fichas_B, turno);
		TFA = fichas_A;
		TFB = fichas_B;
		numTFA = numero_fichas_A;
		numTFB = numero_fichas_B;
		Nodo* PT;
		//function minmax
		if ((numTFA == 0 || numTFB == 0) || nivel_max == 0) {
			Peso = numTFB - numTFA;
			return;
		}
		else if (Turno == 0) {
			for (list< pair<int, int>>::iterator it = TFA.begin(); it != TFA.end(); it++) {
				if (D->mover((*it).first, (*it).second, (*it).first + 1, (*it).second + 1)) {
					PT = new Nodo(D->Fichas_A, D->Numero_Fichas_A, D->Fichas_B, D->Numero_Fichas_B, 1, nivel_maximo - 1);
					VD.push_back(PT);
				}
				D->Fichas_A = TFA;
				D->Fichas_B = TFB;
				D->Numero_Fichas_A = numTFB;
				D->Numero_Fichas_B = numTFB;
				if ((D->mover((*it).first, (*it).second, (*it).first - 1, (*it).second + 1))) {
					PT = new Nodo(D->Fichas_A, D->Numero_Fichas_A, D->Fichas_B, D->Numero_Fichas_B, 1, nivel_maximo - 1);
					VD.push_back(PT);
				}
				D->Fichas_A = TFA;
				D->Fichas_B = TFB;
				D->Numero_Fichas_A = numTFA;
				D->Numero_Fichas_B = numTFB;
			}
		}
		else {
			for (list< pair<int, int>>::iterator it = TFB.begin(); it != TFB.end(); it++) {
				if (D->mover((*it).first, (*it).second, (*it).first - 1, (*it).second - 1)) {
					PT = new Nodo(D->Fichas_A, D->Numero_Fichas_A, D->Fichas_B, D->Numero_Fichas_B, 0, nivel_maximo - 1);
					VD.push_back(PT);
				}
				D->Fichas_A = TFA;
				D->Fichas_B = TFB;
				D->Numero_Fichas_A = numTFA;
				D->Numero_Fichas_B = numTFB;
				if (D->mover((*it).first, (*it).second, (*it).first + 1, (*it).second - 1)) {
					PT = new Nodo(D->Fichas_A, D->Numero_Fichas_A, D->Fichas_B, D->Numero_Fichas_B, 0, nivel_maximo - 1);
					VD.push_back(PT);
				}
				D->Fichas_A = TFA;
				D->Fichas_B = TFB;
				D->Numero_Fichas_A = numTFA;
				D->Numero_Fichas_B = numTFB;
			}
		}
		if (VD.size() == 0)
		{
			Peso = numTFB - numTFA;
			return;
		}
		Peso = VD[0]->Peso;
		Mejor_Jugada = 0;
		for (int i = 1; i < VD.size(); i++) {
			if ((VD[i])->Peso > Peso) {
				Peso = VD[i]->Peso;
				Mejor_Jugada = i;
			}
		}
	}
	damas* M_J() { return VD[Mejor_Jugada]->D; }
};

class Arbol {
	Nodo* Padre;
	Arbol(int turno) {}
};
struct juego {
	int Dificultad;
	damas* Damas;
	Nodo* I_A;
	juego() {
		Damas = new damas(7, 0, 7, 0);
	}
	void tablero() {
		Damas->VISUALIZAR();
	}
	void elegir_turno() {
		cout << "Elija su turno:" << endl;
		cout << "Escriba 0 para empezar tu y escriba 1 para que empieze el computador" << endl;
		cin >> Damas->turno;
		if (Damas->turno == 0) {
			cout << "Empiezas tu y fichas : (o)" << endl;
			cout << endl;
		}
		else {
			cout << "El computador empieza y es fichas : (x)" << endl;
			cout << endl;
		}
	}
	void elegir_dificultad() {
		cout << "Elija dificultad que usted desea (la dificultad sera el nivel del arbol) : ";
		cin >> Dificultad;
	}
	void IA() {
		I_A = new Nodo(Damas->Fichas_A, Damas->Numero_Fichas_A, Damas->Fichas_B, Damas->Numero_Fichas_A, Damas->turno, Dificultad);
		Damas->AcDatos(I_A->M_J());
	}
	void jugar() {
		int x, y;
		int pos_x, pos_y;
		while (true) {
			Damas->VISUALIZAR();
			if (Damas->turno == 1) {
				cout << "Es turno del computador" << endl;
				cout << "computador es fichas negras" << endl;
				IA();
				Damas->turno = 0;
			}
			else {
				cout << "Es Tu Turno" << endl;
				cout << "Tu eres las fichas rojas" << endl;
				cout << "Ingrese la posicion de la ficha en el eje X " << endl;
				cin >> x;
				cout << "Ingrese la posicion de la ficha en el eje Y" << endl;
				cin >> y;
				cout << "Ingrese la posicion de la ficha a donde quiere mover en el eje X " << endl;
				cin >> pos_x;
				cout << "Ingrese la posicion de la ficha a donde quiere mover en el eje Y" << endl;
				cin >> pos_y;
				Damas->mover(x, y, pos_x, pos_y);
				Damas->turno = 1;
			}
		}
	}
	void prueba1() {
		elegir_turno();
		elegir_dificultad();
		jugar();
	}
	void prueba2() {
		elegir_turno();
		elegir_dificultad();
		while (true) {
			IA();
			tablero();
			Damas->turno = 1;
			IA();
			tablero();
			Damas->turno = 0;
		}
	}
};

int main() {
	juego xd;
	//xd.prueba1();
	xd.prueba2();
}
