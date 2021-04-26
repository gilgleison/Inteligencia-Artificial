//Author:
//        Gilgleison Paulino Lima 
//        Paulo Ricardo da Silva Lopes

#include <iostream>
#include <list>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iterator>
#include <stack>
#include <sstream>

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

public:

    Grafo(int V){
        this->V = V;
        this->adj = new list<int>[V];
    }

    void set_aresta(int v1, int v2){
        adj[v1].push_back(v2);
    }

    void set_custo(int chave1, int chave2, int valor){
        //Adicionando nas duas dimensões ao mesmo tempo, pois se A tem custo X até B, então B tem o mesmo custo até A
        this->custo[chave1][chave2] = valor;
        this->custo[chave2][chave1] = valor;
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

    int get_v(){
        return this->V;
    }
};

void povoar(Grafo *G){
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

}

string busca_profundidade(Grafo *G, int origem, int destino){
    //Cria pilha pra armazenar o custo e a medida que for desempilhando o grafo vai desempilhando o valor também. e
    // soma o custo do filho ao custo do pai, ao colocar o
    // pai em explorados e o filho em borda, dessa folrma a ordem de empilhar e esempilhar ficará a mesma para ambas as pilhas.
    stringstream ss;
    int no;
    stack<int> borda;
    bool bordaB[G->get_v()]; //variavel auxiliar que ajudará a verificar a borda
    bool explorados[G->get_v()];
    list<int>explorados_aux;
    bool ctrl = false; //variável de controle para parada do laço de repetição caso encontre o destino
    int custo_atual = 0; //Variável que guardará o custo acumulado para o nó atual
    stack<int> custo; //Pilha para armazenar os custos acumulados para os nós que estão empilhados

    //colococando false em todos os nós da borda auxiliar e explorados
    for(int i = 0;i<G->get_v();i++){
        bordaB[i] = false;
        explorados[i] = false;
    }
    //Adicionando a origem na borda
    borda.push(origem);
    //escrevendo na borda auxiliar o nó inicial
    bordaB[origem] = true;
    //para o nó inicial o custo acumulado é zero
    custo.push(0);

    while(!ctrl)
    {
        //Caso não existam elementos na borda retorna uma string com o erro;
        if(borda.empty()){
            ss << "Borda Vazia."<<endl;
            return ss.str();
        }    
        
        no = borda.top(); //passando para a variável no o valor do topo da pilha
        custo_atual = custo.top(); //passando o custo do nó atual 
        //cout << no << endl;
        borda.pop(); //desempilhando o valor do topo
        custo.pop(); //desempilhando o custo atual
        bordaB[no] = false; //retirando da borda auxiliar o valor de no
        explorados[no] = true; //adicionando o nó em explorados
        explorados_aux.push_back(no);
        
        for(auto it:G->get_vizinhos(no)){
            if(explorados[it] == false && bordaB[it] == false){
                if(it == destino){
                    custo.push(G->get_custo(no, it) + custo_atual);
                    ctrl = true;
                    break;
                }else{
                    borda.push(it);
                    bordaB[it] = true;
                    custo.push(G->get_custo(no, it) + custo_atual); //Adiciona a pilha o custo acumulado do pai + o custo do filho                   
                }
            }
        }       
    } 

    ss <<"\nNó " << destino <<" Encontrado." << endl;
    ss <<"Custo acumulado do caminho: " << custo.top() <<"."<< endl;
    ss << "\nExplorados:"<<endl;
    for(auto aux:explorados_aux) ss << aux << endl;
    ss <<  "Borda:"<<endl;
    for(int j = 0; j< G->get_v();j++) if(bordaB[j]) ss << j << endl;
    return ss.str();
}

int main(){
    Grafo romenia_map(20);
    povoar(&romenia_map);

    cout << busca_profundidade(&romenia_map, Neamt, Bucharest) <<endl;
        
}