#include <iostream>
#include <cstdlib>
using namespace std;


class Jugador {
public:
	
	
	Jugador(string nombre) : m_nombre(nombre) { }
	string Nombre() const { return m_nombre; }
	
	/
	virtual string Jugar() =0;
	
	virtual void Resultado(bool gane) { /*me da igual c�mo me fue*/ }
	
	virtual ~Jugador() { }
	
private:
	string m_nombre;
};

// esta func implementa la interfaz del juego y las reglas (decide cuando
// juega cada uno y quien gana)
void gran_funcion_del_juego(Jugador *j1, Jugador *j2) {
	// el while es para poder hacer varias partidas
	bool seguir_jugando = true;
	while(seguir_jugando) {
		
		// que cada uno elija su jugada
		cout << endl << "Piedra, papel, tijeras..." << endl;
		string e1 = j1->Jugar(), e2 = j2->Jugar();
		cout << j1->Nombre() << " elige " << e1 << endl;
		cout << j2->Nombre() << " elige " << e2 << endl;
		
		// determinar e informar el resultado de la partida
		if (e1==e2) {
			cout << "Empate!" << endl;
			j1->Resultado(false);
			j2->Resultado(false);
		} else {
			bool gana_j1;
			if        (e1=="piedra")    gana_j1 = e2=="tijeras";
			else if   (e1=="papel")     gana_j1 = e2=="piedra";
			else /*if (e1=="tijeras")*/ gana_j1 = e2=="papel";
			
			j1->Resultado(gana_j1);
			j2->Resultado(not gana_j1);
			
			if (gana_j1) cout << "Gana " << j1->Nombre() << endl;
			else         cout << "Gana " << j2->Nombre() << endl;
		}
		
		// ver si se queire seguir jugando
		cout << endl << "Seguir jugando? (s/n) ";
		char c; cin >> c; 
		seguir_jugando = c=='s';
	}
}

// clase para el jugador humano, que pregunta la jugada con cin
class HumanoAlTeclado : public Jugador {
public:
	HumanoAlTeclado(string nombre) : Jugador(nombre) { }
	string Jugar() override {
		int r;
		cout << "Elige tu jugada (1-piedra, 2-papel, 3-tijeras): ";
		cin >> r;
		switch(r) {
		case 1:  return "piedra";
		case 2:  return "papel";
		default: return "tijeras";
		}
	}
};

// clase para el nivel facil, casi siempre elige piedra
class MrPiedras : public Jugador {
public:
	MrPiedras() : Jugador("Mr. Piedras") { }
	string Jugar() override {
		switch(rand()%10) {
		case 0:  return "tijeras";
		case 1:  return "papel";
		default: return "piedra";
		}
	}
};

// clase para el nivel medio, elige completamente al azar
class JohnyRandom : public Jugador {
public:
	JohnyRandom() : Jugador("J. Random") { }
	string Jugar() override {
		switch(rand()%3) {
		case 0:  return "piedra";
		case 1:  return "papel";
		default: return "tijeras";
		}
	}
};

// clase para el nivel difi
cil... sabe que los humanos tienden a mantener la
// jugada si ganan, y cambiar si pierden... y usualmente van rotando en el orden
// del nombre del juego (piedra->papel->tijeras->piedra->papel->...)
class Multivac : public Jugador {
public:
	Multivac() : Jugador("Multivac") { }
	string Jugar() override {
		if (m_previa.empty()) {
			return m_previa="piedra";
		} else {
			if (m_gane) {
				if        (m_previa=="piedra")    return m_previa="papel";
				else if   (m_previa=="papel")     return m_previa="tijeras";
				else /*if (m_previa=="tijeras")*/ return m_previa="piedra";
			} else {
				if        (m_previa=="piedra")    return m_previa="tijeras";
				else if   (m_previa=="papel")     return m_previa="piedra";
				else /*if (m_previa=="tijeras")*/ return m_previa="papel";
			}
		}
	}
	void Resultado(bool gane) override { m_gane = gane; }
private:
	string m_previa;
	bool m_gane;
};

int main() {
	
	string nombre;
	cout << "Saludos terricola! Dime tu nombre: ";
	getline(cin,nombre);
	HumanoAlTeclado j1(nombre);
	
	cout << "Elige el nivel de dificultad: " << endl;
	cout << " 1- gallina" << endl;
	cout << " 2- estandar" << endl;
	cout << " 3- cerebrito" << endl;
	int nivel;
	cin >> nivel;
	
	Jugador *j2;
	if        (nivel==1)   j2 = new MrPiedras();
	else   if (nivel==2)   j2 = new JohnyRandom();
	else /*if (nivel==3)*/ j2 = new Multivac();
	
	gran_funcion_del_juego(&j1,j2);
	
	delete j2;
	
	return 0;
}

