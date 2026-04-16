 /*
 *  GRAFO.CPP - Plantilla para la implementaci�n de la clase GRAFOS
 *
 *
 *  Autores : Antonio Sedeno Noda, Sergio Alonso
 *  Cursos   : 2012-2021
 */

#include "grafo.h"

void GRAFO :: destroy()
{
	for (unsigned i=0; i< n; i++)
    {
		LS[i].clear();
		if (dirigido == 1)
        	   LP[i].clear();
	}
	LS.clear();
	if (dirigido == 1)
		LP.clear();

}

void GRAFO::build (char nombrefichero[85], int &errorapertura)
{
  ElementoLista dummy;
	ifstream textfile;
	textfile.open(nombrefichero);
	if (textfile.is_open()) {
		unsigned i, j, k;
		// leemos por conversion implicita el numero de nodos, arcos y el atributo dirigido
		textfile >> (unsigned &) n >> (unsigned &) m >> (unsigned &) dirigido;
		// los nodos internamente se numeran desde 0 a n-1
		// creamos las n listas de sucesores
		LS.resize(n);
		LP.resize(n);
        // leemos los m arcos
		for (k = 0; k < m; k++) {
			textfile >> (unsigned &) i  >> (unsigned &) j >> (int &) dummy.c;
			//damos los valores a dummy.j y dummy.c
			dummy.j = j-1;
			//situamos en la posici�n del nodo i a dummy mediante push_back
			LS[i-1].push_back(dummy);
			//pendiente de hacer un segundo push_back si es no dirigido. O no.
			if (dirigido == 1) {
				dummy.j = i-1;
				LP[j-1].push_back(dummy);
			}
			//pendiente la construcci�n de LP, si es dirigido
			//pendiente del valor a devolver en errorapertura
			//...
			errorapertura = 0;
		}
	} else errorapertura = 1;
}

GRAFO::~GRAFO()
{
	destroy();
}

GRAFO::GRAFO(char nombrefichero[85], int &errorapertura)
{
	build (nombrefichero, errorapertura);
}

void GRAFO:: actualizar (char nombrefichero[85], int &errorapertura)
{
    //Limpiamos la memoria dinamica asumida en la carga previa, como el destructor
    destroy();
    //Leemos del fichero y actualizamos G con nuevas LS y, en su caso, LP
    build(nombrefichero, errorapertura);
}

unsigned GRAFO::Es_dirigido()
{
	return dirigido;
}

void GRAFO::Info_Grafo()
{
	std::cout << "Nodos:" << n << " Arcos:" << m;
	if (dirigido == 1)
	std::cout << " Tipo:dirigido";
	else if (dirigido == 0)
	std::cout << " Tipo:no dirigido";
	std::cout << std::endl;
}

// void Mostrar_Lista(vector<LA_nodo> L) -> void GRAFO::Mostrar_Lista(vector<LA_nodo> L)
void GRAFO::Mostrar_Lista(vector<LA_nodo> L)
{
	for (unsigned i{0}; i < n; i++){
		for (unsigned k{0}; k < L[i].size(); k++){
			std::cout << (i + 1) << (L[i][k].j + 1) << L[i][k].c << std::endl;
		}
	}
}

void GRAFO::Mostrar_Listas (int l)
{
	if ((dirigido == 0) && (l == 0)) {
		Mostrar_Lista(LS);
	} else if ((dirigido == 1) && (l == 1)) {
		Mostrar_Lista(LS);
	} else if ((dirigido == 1) && (l == -1)) {
		Mostrar_Lista(LP);
	}
}
// void ListaPredecesores() -> void GRAFO::ListaPredecesores()
void GRAFO::ListaPredecesores() //Recorre la lista de sucesores LS para construir la de predecesores, LP
{
	for (unsigned i{0}; i < n; i++){
		for (unsigned k{0}; k < LS[i].size(); k++){
			LP[LS[i][k].j][i].j = i;
			LP[LS[i][k].j][i].c = LS[i][k].c;
		}
	}
}

void GRAFO::dfs_cc(unsigned i, vector<bool> &visitado) 
{
  visitado[i] = true; //visitamos el nodo i+1
  std::cout << i + 1; // i empieza en 0, mientras que los nodos se cuentan desde el 1
  for (unsigned j{0}; j < LS[i].size(); j++) { //recorremos la adyacencia del nodo visitado, esto es, i+1
    if (!visitado[LS[i][j].j]) { // si no está visitado el nodo
      std::cout << ", ";
      dfs_cc(LS[i][j].j, visitado); // vuelve a llamar a la función
    }
  }
}

void GRAFO::ComponentesConexas()
{
  unsigned i, componentesconexas = 0;
  vector<bool> visitado;
  visitado.resize(n, false);
  i = 0;
  while (i < n) {
    if (visitado[i] == false) {
      componentesconexas++; 
      std::cout << "Componente Conexa " << componentesconexas << ":{";
      dfs_cc(i, visitado); // realiza el recorrido
			std::cout << "}" << std::endl;
    }
    i++;
  }
}

void GRAFO::dfs_cfc(unsigned i, vector<bool> &visitado) 
{
  visitado[i] = true; 
  std::cout << i + 1;
  for (unsigned j{0}; j < LP[i].size(); j++) { 
    if (!visitado[LP[i][j].j]) {
      std::cout << ", ";
      dfs_cfc(LP[i][j].j, visitado); 
    }
  }
}

void GRAFO::dfs_postnum(unsigned i, vector<bool> &visitado, vector<unsigned> &postnum, unsigned &postnum_ind) 
{
  visitado[i] = true;
  for (size_t k{0}; k < LS[i].size(); ++k) {
    if (!visitado[LS[i][k].j]) {
        dfs_postnum(LS[i][k].j, visitado, postnum, postnum_ind);
    }
  }
  postnum[postnum_ind--] = i;
}

void GRAFO::ComponentesFuertementeConexas()
{
  unsigned i, postnum_ind, componentesfuertementeconexas = 0;
  vector<bool> visitado;
  vector<unsigned> postnum;
  visitado.resize(n, false);
  postnum.resize(n, UERROR);
  postnum_ind = n - 1;
  i = 0;
  while (i < n) {
    if (visitado[i] == false)
      dfs_postnum(i, visitado, postnum, postnum_ind);
    i++;
  }
  visitado.assign(n, false); 
  i = 0;
  while (i < n) {
    if (visitado[postnum[i]] == false) {
      componentesfuertementeconexas++;
      std::cout << "Componente Fuertemente Conexa " << componentesfuertementeconexas << ":{";
      dfs_cfc(postnum[i], visitado);
			std::cout << "}" << std::endl;
    }
    i++;
  }
}