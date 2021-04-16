#include <iostream>
#include <vector>
#include <time.h>
#include <math.h>
#include <list>

using namespace std;

template<class G>
class _Edge {
public:
	typedef typename G::Node Node;
	typedef typename G::EE E;
	E data;
	Node* nodes[2];
	_Edge(Node* A, Node* B, E x) {
		nodes[0] = A;
		nodes[1] = B;
		data = x;
	}
};

template<class G>
class _Node {
public:
	typedef typename G::Edge Edge;
	typedef typename G::NN N;
	N data;
	int index;
	int distance;
	bool marked;
	vector<Edge*> edges;

	_Node(N n, int index) {
		data = n;
		this->index = index;
	}

	void InsertEdge(Edge* arista) {
		edges.push_back(arista);
	}

	void DisplayEdges() {
		for (int i = 0; i < edges.size(); i++) {
			bool j = !(edges[i]->nodes[1]->data == data);
			cout << " -> " << edges[i]->nodes[j]->data.first << "," << edges[i]->nodes[j]->data.second << "(" << edges[i]->data << ")";
		}
	}
};

template<class N, class E>
class Graph {
public:
	typedef Graph<N, E> self;
	typedef _Node<self> Node;
	typedef _Edge<self> Edge;
	typedef N NN;
	typedef E EE;
	vector<Node*> nodes;

	bool InsertNode(N n, int index) {
		Node* node = new Node(n, index);
		nodes.push_back(node);
		return true;
	}

	void InsertEdge(int A, int B, E e) {
		Edge* arista = new Edge(nodes[A], nodes[B], e);
		nodes[A]->InsertEdge(arista);
		nodes[B]->InsertEdge(arista);
	}

	bool RemoveEdge(Node* A, Node* B, E e) {
		if (A and B) {
			for (int i = 0; i < A->edges.size(); i++) {
				if (A->edges[i]->data == e and A->edges[i]->nodes[A->edges[i]->nodes[1]->data == B->data] == B) {
					for (int j = 0; j < B->edges.size(); j++) {
						if (B->edges[j]->data == e and
							B->edges[j]->nodes[B->edges[j]->nodes[1]->data == A->data] == A) {
							Edge* ed = (A->edges[i]);
							A->edges.erase(A->edges.begin() + i);
							if (A != B)
								B->edges.erase(B->edges.begin() + j);
							delete ed;
							return true;
						}
					}
				}
			}
		}
		return false;
	}

	bool RemoveNode(int i) {
		Node* A = nodes[i];
		if (A) {
			while (A->edges.size() != 0) {
				Node* B = A->edges[0]->nodes[A->edges[0]->nodes[1] != A];
				E e = A->edges[0]->data;
				RemoveEdge(A, B, e);
			}
			nodes.erase(nodes.begin() + i);
			delete A;
			return true;
		}
		return false;
	}

	Node* findNode(N a) {
		for (auto node : nodes)
			if (node->data.first == a.first and node->data.second == a.second)
				return node;
		return nullptr;
	}

	double ff(N a, N b) {
		return sqrt(pow((a.first - b.first), 2) + pow((a.second - b.second), 2));
	}

	vector<pair<int, int>>busqueda_heuristica(N inicial, N objetivo) {
		vector<pair<int, int>> camino;
		Node* Actual = nullptr, * NMin = nullptr;
		Edge* EMin = nullptr;
		double minV, total;
		E acumulado = 0;
		vector<Edge*> Ecamino;
		vector<Node* > Ncamino;
		if ((Actual = findNode(inicial)) and findNode(objetivo)) {
			Ncamino.push_back(Actual);
			while (Actual->data != objetivo) {
				minV = INT_MAX;
				for (auto edge : Actual->edges) {
					Node* B = edge->nodes[edge->nodes[0] == Actual];
					if (find(Ncamino.begin(), Ncamino.end(), B) == Ncamino.end()) {
						total = acumulado + ff(B->data, objetivo);
						if (total < minV) {
							minV = total;
							NMin = B;
							EMin = edge;
						}
					}
				}
				Actual = NMin;
				acumulado += EMin->data;
				Ncamino.push_back(NMin);
				Ecamino.push_back(EMin);
			}
			cout << endl << "busqueda heuristica :" << endl;

			for (int i = Ncamino.size() - 1; i; i--) {
				for (auto edge : (Ncamino[i])->edges) {
					Node* B = edge->nodes[edge->nodes[0] == Ncamino[i]];
					int j = 0;
					while (Ncamino[j] != B && j < i) {
						++j;
					}
					++j;
					while (i > j) {
						Ncamino.erase(Ncamino.begin() + j);
						--i;
					}
				}
			}
			for (auto node : Ncamino) {
				cout << "(" << node->data.first << "," << node->data.second << "); ";
				camino.push_back(make_pair(node->data.first, node->data.second));
			}
		}
		return camino;
	}

	vector<pair<int, int>> busqueda_ciega(N inicial, N objetivo) {
		vector<pair<int, int>> camino;
		Node* Actual = nullptr;
		vector<Node* > Ncamino;
		if (!findNode(objetivo)) {
			cout << "La coordenada final no existe" << endl;
			if (!(Actual = findNode(inicial))) {
				cout << "La coordenada inicial no existe" << endl;
			}
		}
		else if (!(Actual = findNode(inicial))) {
			cout << "La coordenada inicial no existe" << endl;
		}
		else {
			list<Node*> cola;
			cola.push_back(Actual);
			Ncamino.push_back(Actual);
			while (!cola.empty() && cola.front()->data != objetivo) {
				Actual = cola.front();
				for (auto edge : Actual->edges) {
					Node* B = edge->nodes[edge->nodes[0] == Actual];
					if (!B->marked) {
						cola.push_back(B);
						Ncamino.push_back(B);
						B->marked = true;
					}
				}
				cola.pop_front();
			}
			if (!cola.empty())
				Ncamino.push_back(cola.front());
			cout << endl << "busqueda ciega : " << endl;
			for (auto node : Ncamino) {
				cout << "(" << node->data.first << "," << node->data.second << "); ";
				camino.push_back(make_pair(node->data.first, node->data.second));
				node->marked = false;
			}
		}
		return camino;
	}

	void PrintGraph() {
		cout << "numero de nodos: " << nodes.size() << endl << endl;
		for (auto it : nodes) {
			cout << "(" << it->data.first << "," << it->data.second << ") ";
			it->DisplayEdges();
			cout << endl;
		}
	}
};

Graph<pair<int, int>, int>* graph = new Graph<pair<int, int>, int>;
vector<pair<int, int>> caminoA;
vector<pair<int, int>> caminoBlind;

bool b = false;

int main(int argc, char** argv) {
	srand(time(NULL));
	int x = 100;
	for (int i = 0; i < x; ++i)
		for (int j = 0; j < x; ++j)
			graph->InsertNode(make_pair(i, j), i + j);

	for (int i = 0; i < x; ++i) {
		for (int j = 0; j < x; ++j) {
			if (i < x - 1)
				graph->InsertEdge(x * i + j, x * (i + 1) + j, 1);
			if (j < x - 1)
				graph->InsertEdge(x * i + j, x * i + j + 1, 1);
			if (j < x - 1 and i < x - 1)
				graph->InsertEdge(x * i + j, x * (i + 1) + j + 1, 1);
			if (j > 0 and i < x - 1)
				graph->InsertEdge(x * i + j, x * (i + 1) + j - 1, 1);
		}
	}
	graph->PrintGraph();
	for (int i = 0; i < 2000; ++i)
		graph->RemoveNode(rand() % (10000 - i));
	graph->PrintGraph();
	pair<int, int> inicial;
	pair<int, int> objetivo;
	cout << endl << "Ingresa las coordenadas iniciales: "; cin >> inicial.first >> inicial.second;
	cout << "Ingresa las coordenadas objetivos: "; cin >> objetivo.first >> objetivo.second;

	caminoA = graph->busqueda_heuristica(inicial, objetivo);
	caminoBlind = graph->busqueda_ciega(inicial, objetivo);
	delete graph;
	return 0;
}
