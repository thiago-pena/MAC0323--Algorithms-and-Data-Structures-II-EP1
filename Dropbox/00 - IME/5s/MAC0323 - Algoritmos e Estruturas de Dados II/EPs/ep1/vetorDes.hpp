#ifndef VETORDES_HPP
#define VETORDES_HPP
#include "vetorDes.hpp" // contém as funções de sorting de arrays
using namespace std;

template <class Chave>
int separa (Chave *arr, int ini, int fim);

template <class Chave>
void quicksort (Chave *arr, int ini, int fim);

template <class Chave>
void swap(Chave *arr, int i, int j);

template <class Chave, class Item>
class vetorDes {
    private:
        struct par {
            Chave chave;
            Item valor;
        };
        par *st;
        int size; // tamanho de vetor
        int n;
        Item nullItem;
        bool null(Chave chave);
        void resize();
    public:
        vetorDes(Item nullItem);
        void insere(Chave chave, Item valor);
        Item devolve(Chave chave);
        void remove (Chave chave);
        int rank(Chave chave);
        Chave seleciona(int k);
};

template <class Chave, class Item>
vetorDes<Chave, Item>::vetorDes(Item nullItem): st(new par[2]), size(2), n(0), nullItem(nullItem) {}

template <class Chave, class Item>
void vetorDes<Chave, Item>::insere(Chave chave, Item valor) {
    for (int i = 0; i < n; i++) // já existe na ST
        if (chave == st[i].chave) {
            st[i].valor = valor;
            return;
        }
    // chave nova
    if (n == size) resize();
    st[n].chave = chave;
    st[n].valor = valor;
    n++;
}

template <class Chave, class Item>
Item vetorDes<Chave, Item>::devolve(Chave chave) {
    for (int i = 0; i < n; i++)
        if (chave == st[i].chave)
            return st[i].valor;
    return nullItem;
}

template <class Chave, class Item>
int vetorDes<Chave, Item>::rank(Chave chave) {
    Chave arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = st[i].chave;
    }
    quicksort<Chave>(arr, 0, n);
    int ini = 0, fim = n - 1;
    while (ini <= fim) {
        int meio = ini + (fim - ini)/2;
        if (chave < arr[meio])
            fim = meio - 1;
        else if (chave > arr[meio])
            ini = meio + 1;
        else
            return meio;
    }
    return ini;
}

template <class Chave, class Item>
void vetorDes<Chave, Item>::resize() {
    par *novoVetor = new par[2*size];
    for (int i = 0; i < n; i++) {
        novoVetor[i].chave = st[i].chave;
        novoVetor[i].valor = st[i].valor;
    }
    delete [] st;
    st = novoVetor;
    size *= 2;
}

template <class Chave, class Item>
void vetorDes<Chave, Item>::remove(Chave chave) {
    bool achou = false;
    int i;
    for (i = 0; i < n; i++)
        if (chave == st[i].chave) {
            achou = true;
            break;
        }
    if (!achou) return;
    while (i < n) {
        st[i] = st[i+1];
        i++;
    }
    n--;
}

template <class Chave, class Item>
Chave vetorDes<Chave, Item>::seleciona(int k) {
    if (k < 0 || k >= n) return "Erro! Rank não encontrado.";
    Chave arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = st[i].chave;
    }
    quicksort<Chave>(arr, 0, n);
    return arr[k];
}

template <class Chave>
int separa (Chave *arr, int ini, int fim) {
    int p = ini, q = fim-1;
    Chave pivo;
    pivo = arr[ini];
    while (p < q) {
        while (arr[q] > pivo) q--;
        if (p < q) swap<Chave>(arr, p, q);
        while (p < q && arr[p] <= pivo) p++;
        if (p < q) swap<Chave>(arr, p, q);
    }
    return p;
}

template <class Chave>
void quicksort (Chave *arr, int ini, int fim) {
    int pivo;
    if (fim - ini >= 2) {
        pivo = separa<Chave>(arr, ini, fim);
        quicksort<Chave>(arr, ini, pivo);
        quicksort<Chave>(arr, pivo+1,fim);
    }
}

template <class Chave>
void swap(Chave *arr, int i, int j) {
    Chave temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
    return;
}

#endif
