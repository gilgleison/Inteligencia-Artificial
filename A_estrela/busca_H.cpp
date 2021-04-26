
#include <iostream>
#include <list>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iterator>
#include <stack>
#include <sstream>
#include<stdio.h>
#include<stdlib.h>
#include <queue>

using namespace std;

const int Arad = 0;
const int Sibiu = 1;
const int Zerind = 2;
const int Timisoara = 3;
const int Lugoj = 4;
const int Mehadia = 5;
const int Drobeta = 6;
const int Craiova = 7;
const int RV = 8;
const int Pitest = 9;
const int Oradea = 10;
const int Fagaras = 11;
const int Bucharest = 12;
const int Giurgiu = 13;
const int Urziceni = 14;
const int Hirsova = 15; 
const int Eforie = 16;
const int Vaslui = 17;
const int Iasi = 18;
const int Neamt = 19;


class Grafo{
    int V; //número de vértices/nós no grafo
    // tabela que armazenará os custo de viagem entre as cidades
    int custo[20][20]; // o construtor não permite a matriz com tramanho dinamico, por isso está de tamanho fixo
    list<int> *adj; //adjacencias
    map <int, int> h;

public:
    Grafo(int V = 20){
        this->V = V;
        this->adj = new list<int>[V];
    }

    void set_aresta(int v1, int v2){
        this->adj[v1].push_back(v2);
    }

    void set_custo(int chave1, int chave2, int valor){
        //Adicionando nas duas dimensões ao mesmo tempo, pois se A tem custo X até B, então B tem o mesmo custo até A
        this->custo[chave1][chave2] = valor;
        this->custo[chave2][chave1] = valor;
    }

    void set_h(int cidade, int custo){
        this->h.insert(make_pair(cidade, custo));
    }

    bool check(int v1, int v2){
        if(find(adj[v1].begin(), adj[v1].end(), v2) != adj[v1].end())
		    return true;
	    return false;
    }
    
    list<int> get_vizinhos(int v){
        return this->adj[v];
    }

    int get_custo(int chave1, int chave2){
        return this->custo[chave1][chave2];
    }

    int get_h(int chave){
        for(auto it:this->h){
            if(it.first == chave) return it.second;
        }
        return 0;
    }

    int get_v(){
        return this->V;
    }
};

void povoar(Grafo *G){
    //Adicionando vizinhos
    //Vizinhos de Arad
    G->set_aresta(Arad,Sibiu);
    G->set_aresta(Arad,Zerind);
    G->set_aresta(Arad,Timisoara);
    //Vizinhos de Sibiu
    G->set_aresta(Sibiu,Fagaras);
    G->set_aresta(Sibiu,RV);
    G->set_aresta(Sibiu,Oradea);
    G->set_aresta(Sibiu, Arad);
    //Vizinhos de Timisoara
    G->set_aresta(Timisoara, Arad);
    G->set_aresta(Timisoara, Lugoj);
    //Vizinhos de Zerind
    G->set_aresta(Zerind, Arad);
    G->set_aresta(Zerind, Oradea);
    //Vizinhos de Oradea 
    G->set_aresta(Oradea, Zerind);
    G->set_aresta(Oradea, Sibiu);
    //Vizinhos de Lugoj
    G->set_aresta(Lugoj, Timisoara);
    G->set_aresta(Lugoj, Mehadia);
    //Vizinhos de Mehadia
    G->set_aresta(Mehadia, Lugoj);
    G->set_aresta(Mehadia, Drobeta);
    //Vizinhos de Drobeta
    G->set_aresta(Drobeta, Mehadia);
    G->set_aresta(Drobeta, Craiova);
    //Vizinhos de Craiova
    G->set_aresta(Craiova, Drobeta);
    G->set_aresta(Craiova, RV);
    G->set_aresta(Craiova, Pitest);
    //Vizinhos de RV
    G->set_aresta(RV, Craiova);
    G->set_aresta(RV, Pitest);
    G->set_aresta(RV, Sibiu);
    //Vizinhos de Fagaras
    G->set_aresta(Fagaras, Sibiu);
    G->set_aresta(Fagaras, Bucharest);
    //Vizinhos de Pitest
    G->set_aresta(Pitest, Craiova);
    G->set_aresta(Pitest, RV);
    G->set_aresta(Pitest, Bucharest);
    //Vizinhos de Bucharest
    G->set_aresta(Bucharest, Pitest);
    G->set_aresta(Bucharest, Fagaras);
    G->set_aresta(Bucharest, Giurgiu);
    G->set_aresta(Bucharest, Urziceni);
    //Vizinhos de Urziceni
    G->set_aresta(Urziceni, Bucharest);
    G->set_aresta(Urziceni, Hirsova);
    G->set_aresta(Urziceni, Vaslui);
    //Vizinhos de Hirsova
    G->set_aresta(Hirsova, Urziceni);
    G->set_aresta(Hirsova, Eforie);
    //Vizinhos de Eforie
    G->set_aresta(Eforie, Hirsova);
    //Vizinhos de Vaslui
    G->set_aresta(Vaslui, Urziceni);
    G->set_aresta(Vaslui, Iasi);
    //Vizinhos de Iasi
    G->set_aresta(Iasi, Vaslui);
    G->set_aresta(Iasi, Neamt);
    //Vizinhos de Neamt
    G->set_aresta(Neamt, Iasi);

    //Adicionando os custos da viagem
    //Vizinhos de Arad
    G->set_custo(Arad, Sibiu, 140);
    G->set_custo(Arad, Zerind, 75);
    G->set_custo(Arad, Timisoara, 118);
    //Vizinhos de Sibiu
    G->set_custo(Sibiu,Fagaras, 99);
    G->set_custo(Sibiu,RV, 80);
    G->set_custo(Sibiu,Oradea, 151);
    //Vizinhos de Timisoara
    G->set_custo(Timisoara, Lugoj, 111);
    //Vizinhos de Zerind
    G->set_custo(Zerind, Oradea, 71);
    //Vizinhos de Lugoj
    G->set_custo(Lugoj, Mehadia, 70);
    //Vizinhos de Mehadia
    G->set_custo(Mehadia, Drobeta, 75);
    //Vizinhos de Drobeta
    G->set_custo(Drobeta, Craiova, 120);
    //Vizinhos de Craiova
    G->set_custo(Craiova, RV, 146);
    G->set_custo(Craiova, Pitest, 138);
    //Vizinhos de RV
    G->set_custo(RV, Pitest, 97);
    //Vizinhos de Fagaras
    G->set_custo(Fagaras, Bucharest, 211);
    //Vizinhos de Pitest
    G->set_custo(Pitest, Bucharest, 101);
    //Vizinhos de Bucharest
    G->set_custo(Bucharest, Giurgiu, 90);
    G->set_custo(Bucharest, Urziceni, 85);
    //Vizinhos de Urziceni
    G->set_custo(Urziceni, Hirsova, 98);
    G->set_custo(Urziceni, Vaslui, 142);
    //Vizinhos de Hirsova
    G->set_custo(Hirsova, Eforie, 86);
    //Vizinhos de Vaslui
    G->set_custo(Vaslui, Iasi, 92);
    //Vizinhos de Iasi
    G->set_custo(Iasi, Neamt, 87);

    //Setando os valores heuristicos dos nós
    G->set_h(Arad, 366);
    G->set_h(Bucharest, 0);
    G->set_h(Craiova, 160);
    G->set_h(Drobeta, 242);
    G->set_h(Eforie, 161);
    G->set_h(Fagaras, 176);
    G->set_h(Giurgiu, 77);
    G->set_h(Hirsova, 151);
    G->set_h(Iasi, 226);
    G->set_h(Lugoj, 244);
    G->set_h(Mehadia, 241);
    G->set_h(Neamt, 234);
    G->set_h(Oradea, 380);
    G->set_h(Pitest, 100);
    G->set_h(RV, 193);
    G->set_h(Sibiu, 253);
    G->set_h(Timisoara, 329);
    G->set_h(Urziceni, 80);
    G->set_h(Vaslui, 199);
    G->set_h(Zerind, 374);
}

int menor(map<int,int> fila){
    int menor_val = fila.begin()->second;
    int no = fila.begin()->first;

    for(auto it:fila){
        if(menor_val > it.second){
            menor_val = it.second;
            no = it.first;
        }  
    }
    return no;   
}

bool check(map<int,int> fila, int no){
    auto it = fila.find(no);
    if (it == fila.end()) return false;
    else return true;
}

string A_estrela(Grafo G, int origem){
    stringstream ss;
    map<int,int> fila;  //O mapa armazenará os nós que estão na borda e os valores f(n)
    map<int,int> custo; //armazenará o custo atual para cada nó na fila
    bool explorados[G.get_v()];
    list<int> explorados_aux;
    int destino = Bucharest;
    bool ctrl = false; //variável de controle para parada do laço de repetição caso encontre o destino
    int custo_atual = 0; //guardará o custo acumulado do nó atual
    int fn_atual = 0; //guardará o F(n) do nó atual
    int fn_filho = 0; //usado para armazenar o F(n) do nó filho
    int no = 0;  // armazena o nó atual

    //colocando false em todas as posições de explorados
    for(int i = 0;i<G.get_v();i++){
        explorados[i] = false;
    }

    //Adicionando o nó inicial a fila
    fila.insert(make_pair(origem, G.get_h(origem)));
    // adicionando o custo acumulado até o nó atual
    custo.insert(make_pair(origem, 0));

    // O f(n) do filho será calculado da seguinte forma
    // custo acumulado do nó atual + custo do pai até o nó filho + h(n) do filho

    while(!ctrl){
        no = menor(fila); // verifica no map qual o menor f(n)
        fn_atual = fila.find(no)->second; // recebe o f(n) do nó atual
        custo_atual = custo.find(no)->second; // recebe o custo do nó atual
        fila.erase(no); // remove o nó da fila
        explorados[no] = true; // adiciona o nó em explorados
        explorados_aux.push_back(no);

        if(no == destino){
            ctrl = true;
            break;
        }
        else{
            for(auto it:G.get_vizinhos(no)){
                fn_filho = custo_atual + G.get_h(it) + G.get_custo(no, it);
                if(explorados[it] == false && check(fila, it) == false){
                    fila.insert(make_pair(it, fn_filho));
                    custo.insert(make_pair(it,(custo_atual + G.get_custo(no, it)))); // o custo do filho será o custo acumulado do pai + o custo do pai ao filho
                }else if(explorados[it] == false && check(fila, it) == true){
                    // verifica se o novo caminho tem um f(n) menor que o f(n) do nó que já está na fila 
                    // se sim apaga o antigo e insere o novo
                    if(fila.find(it)->second > fn_filho){
                        fila.erase(it);
                        custo.erase(it);
                        fila.insert(make_pair(it, fn_filho));
                        custo.insert(make_pair(it,(custo_atual + G.get_custo(no, it))));
                    }
                }
            }   
        }  
    }

    ss <<"\nNó " << destino <<" Encontrado." << endl;
    ss <<"F(n): " << fn_atual <<"."<< endl;
    ss << "\nExplorados:"<<endl;
    for(auto k:explorados_aux) ss << k << endl;
    ss <<  "\nFila:"<<endl;
    for(int i=0;i<=fila.size();i++){
        no = menor(fila);
        fn_atual = fila.find(no)->second;
        fila.erase(no);
        ss << "Nó: "<< no << ", F(n): " << fn_atual <<endl;
    }
    return ss.str();
}

int main(){
    Grafo romenia_map(20);
    povoar(&romenia_map);
    
    cout << A_estrela(romenia_map, Arad) << endl;
}
