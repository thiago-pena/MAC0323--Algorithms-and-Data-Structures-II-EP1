#ifndef VETORORD_HPP
#define VETORORD_HPP
using namespace std;

template <class Chave, class Item>
class vetorOrd {
    private:
        struct par {
            Chave chave;
            Item valor;
        };
        par *st;
        int size; // Tamanho do vetor
        int n; // número de elementos na Tabela de Símbolos
        Item nullItem;
        bool null(Chave chave);
        bool isEmpty();
        void resize();
    public:
        vetorOrd(Item nullItem); // inserir nome do arquivo de texto como parâmetro
        bool contains(Chave chave);
        void insere(Chave chave, Item valor);
        Item devolve(Chave chave); // value paired with key ( null if key is absent)
        //void remove (Chave chave);
        int rank(Chave chave); // find the number of keys less than a given key
        Chave seleciona(int k); // find the key with a given rank
};

template <class Chave, class Item>
vetorOrd<Chave, Item>::vetorOrd(Item nullItem): st(new par[2]), size(2), n(0), nullItem(nullItem) {}

template <class Chave, class Item>
bool vetorOrd<Chave, Item>::isEmpty() {
    return n == 0;
}


// rank retorna onde deve inserir, se for nova
template <class Chave, class Item>
void vetorOrd<Chave, Item>::insere(Chave chave, Item valor) {
    int r = rank(chave);
    if (r < n && st[r].chave == chave) { // já existe
        st[r].valor = valor;
    }
    else { // chave é nova
        if (n == size) resize();
        for (int i = n; i > r; i--) {
            st[i].chave = st[i - 1].chave;
            st[i].valor =  st[i - 1].valor;
        }
        st[r].chave = chave;
        st[r].valor = valor;
        n++;
    }
}

// value paired with key ( null if key is absent)
template <class Chave, class Item>
Item vetorOrd<Chave, Item>::devolve(Chave chave) {
    if (n == 0) return nullItem;
    int r = rank(chave);
    if (r < n && st[r].chave == chave)
        return st[r].valor;
    return nullItem;
}

// find the number of keys less than a given key
// retorna -1 se a chave não pertence à ST
// fazer busca binária
template <class Chave, class Item>
int vetorOrd<Chave, Item>::rank(Chave chave) {
    int ini = 0, fim = n - 1;
    while (ini <= fim) {
        int meio = ini + (fim - ini)/2;
        if (chave < st[meio].chave)
            fim = meio - 1;
        else if (chave > st[meio].chave)
            ini = meio + 1;
        else
            return meio;
    }
    return ini;
}

// key of rank k
// find the key with a given rank
template <class Chave, class Item>
Chave vetorOrd<Chave, Item>::seleciona(int k) {
    // boolean contains(Key key) is there a value paired with key ?
    return st[k].chave;

/*
    When a method is to return a key and there is no key fitting the de-
    scription in the table, our convention is to throw an exception (an alternate approach,
    which is also reasonable, would be to return null in such cases). For example, min() ,
    max() , deleteMin() , deleteMax() , floor() , and ceiling() all throw exceptions if
    the table is empty, as does select(k) if k is less than 0 or not less than size() .
*/
}

template <class Chave, class Item>
bool vetorOrd<Chave, Item>::contains(Chave chave) {
    int r = rank(chave);
    if (r < n && st[r].chave == chave)
        return true;
    return false;
}

template <class Chave, class Item>
void vetorOrd<Chave, Item>::resize() {
    par *novoVetor = new par[2*size];
    for (int i = 0; i < n; i++) {
        novoVetor[i].chave = st[i].chave;
        novoVetor[i].valor = st[i].valor;
    }
    delete [] st;
    st = novoVetor;
    size *= 2;
}

#endif
