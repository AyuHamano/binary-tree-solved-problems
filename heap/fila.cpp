#include<bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#define N 10001
using namespace std;
 
// Estrutura de dados para armazenar um nó min-heap
class PriorityQueue
{
private:
    // vector para armazenar elementos de heap
    vector<int> A;
 
    // retorna o pai de `A[i]`
    // não chame esta função se `i` já for um nó raiz
    int PARENT(int i) {
        return (i - 1) / 2;
    }
 
    // retorna o filho esquerdo de `A[i]`
    int LEFT(int i) {
        return (2*i + 1);
    }
 
    // retorna o filho direito de `A[i]`
    int RIGHT(int i) {
        return (2*i + 2);
    }
 
    // Algoritmo de heapify-down recursivo.
    // O nó no índice `i` e seus dois filhos diretos
    // viola a propriedade heap
    void heapify_down(int i)
    {
        // obtém filho esquerdo e direito do nó no índice `i`
        int left = LEFT(i);
        int right = RIGHT(i);
 
        int smallest = i;
 
        // compara `A[i]` com seu filho esquerdo e direito
        // e encontrar o menor valor
        if (left < size() && A[left] < A[i]) {
            smallest = left;
        }
 
        if (right < size() && A[right] < A[smallest]) {
            smallest = right;
        }
 
        // troca com um filho de menor valor e
        // chama heapify-down no filho
        if (smallest != i)
        {
            swap(A[i], A[smallest]);
            heapify_down(smallest);
        }
    }
 
    // Algoritmo heapify-up recursivo
    void heapify_up(int i)
    {
        // verifica se o nó no índice `i` e seu pai violam a propriedade heap
        if (i && A[PARENT(i)] > A[i])
        {
            // troca os dois se a propriedade heap for violada
            swap(A[i], A[PARENT(i)]);
 
            // chama heapify-up no pai
            heapify_up(PARENT(i));
        }
    }
 
public:

    // retorna o tamanho do heap
    unsigned int size() {
        return A.size();
    }
 
    // Função para verificar se o heap está vazio ou não
    bool empty() {
        return size() == 0;
    }
 
    // insere a chave no heap
    void push(int key)
    {
        // insere um novo elemento no final do vector
        A.push_back(key);
 
        // obtém o índice do elemento e chama o procedimento heapify-up
        int index = size() - 1;
        heapify_up(index);
    }
 
    // Função para remover um elemento de menor prioridade (presente na raiz)
    int pop()
    {
        try {
            // se o heap não tiver elementos, lança uma exceção
            if (size() == 0)
            {
                throw out_of_range("Vector<X>::at() : "
                        "index is out of range(Heap underflow)");
            }
 
            // substitui a raiz do heap pelo último elemento
            // do vector
            int menor = A[0];
            A[0] = A.back();
            A.pop_back();
 
            // chama heapify-down no nó raiz
            heapify_down(0);
            return menor;
        }
        // captura e imprime a exceção
        catch (const out_of_range &oor) {
            cout << endl << oor.what();
        }
    }
 
    // Função para retornar um elemento com a prioridade mais baixa (presente na raiz)
    int top()
    {
        try {
            // se o heap não tiver elementos, lança uma exceção
            if (size() == 0)
            {
                throw out_of_range("Vector<X>::at() : "
                        "index is out of range(Heap underflow)");
            }
 
            // caso contrário, retorna o elemento superior (primeiro)
            return A.at(0);        // ou return A[0];
        }
        // captura e imprime a exceção
        catch (const out_of_range &oor) {
            cout << endl << oor.what();
        }
    }
};
 
// Implementação de Min Heap em C++
int main()
{
    int caixa, resto=0, cliente, tempo, indiceCaixa, menorTempo, tempoTotal=0, aux;
    vector<int>tempoCaixa;
    vector<int>tempoCliente;
    vector<int>itemCliente;
    PriorityQueue caixaLivre, tempoGasto;
    cin >> caixa;
    cin >> cliente;

    for(int j=0; j<caixa; j++) {
        cin >> aux;
        tempoCaixa.push_back(aux);
        caixaLivre.push(j);
        tempoCliente.push_back(0);
    }
    for(int k=0; k<cliente; k++) {
        cin >> aux;
        itemCliente.push_back(aux);
        
    }
    for(int i=0; i<cliente; i++) {
        if(caixaLivre.size() != 0) {
            indiceCaixa = caixaLivre.pop();
            tempo = itemCliente[i] * tempoCaixa[indiceCaixa]; //o caixa disponivel de menor indice
            tempoCliente[indiceCaixa] = tempo;
            tempoGasto.push(tempo);
        }
        else {
            menorTempo = tempoGasto.pop();
            for(int s=0; s<tempoCliente.size(); s++) {
                tempoCliente[s] = abs(tempoCliente[s] - menorTempo);
                if(tempoCliente[s]==0) caixaLivre.push(s);
                else tempoGasto.push(tempoCliente[s]);
            }
            i--;
            tempoTotal += menorTempo;
            //cout << "count --> " << tempoTotal << "\n";
        }
    }
    for(int e=0; e< caixa; e++) {
        if(resto < tempoCliente[e]) {
            resto = tempoCliente[e];
        }
    }
    //cout << "leftover -->" << resto << "\n";
    tempoTotal += resto;
    cout << tempoTotal << "\n";
    //caixaLivre.imprime();
    
 
    return 0;
}