#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP
#define NULLKEY "NULL"
#define INITIALPRIME 151

int nextPrime(int n);
bool isPrime(int n);

class hashTable {
    public:
        hashTable(int tam);
        bool contains(string chave);
        void insere(string chave, int valor);
        int devolve(string chave); // value paired with key ( null if key is absent)
        //void remove (string chave);
        //int rank(string chave); // find the number of keys less than a given key
        //string seleciona(int k); // find the key with a given rank -> pré-ordem

    private:
        struct par {
            string chave;
            int valor;
            bool ocupado;
            bool blabla;
            // par(string ch, int val) {
            //     chave = ch;
            //     valor = val;
            //     ocupado  = true;
            //     blabla = false;
            // }
        };
        par *st;
        int N;
        int M;
        int hash(string);
        void resize(int);
};

// arvoreBin<Chave, Item>::arvoreBin(Item nullItem): raiz(nullptr), nullItem(nullItem){};
// template <class Chave, class Item>

hashTable::hashTable(int tam): st(new par[tam]), N(0), M(tam) {
    for (int i = 0; i < M; i++)
        st[i].chave = NULLKEY;
}

int hashTable::hash(string s) {
    int h = 0;
    for (int i = 0; i < s.length(); i++)
        h = (31 * h + s[i]) % M;
    return h;
}

void hashTable::insere(string chave, int valor) {
    if (N >= M/2) resize(nextPrime(M));
    int i;
    cout << "insere: " << chave << " / hash: " << hash(chave) << " / N: " << N << " (M: " << M << ")" << endl;
    for (i = hash(chave); st[i].chave != NULLKEY; i = (i + 1) % M)
        if (chave == st[i].chave) {
            st[i].valor = valor;
            return;
        }
    st[i].chave = chave;
    st[i].valor = valor;
    N++;
}

int hashTable::devolve(string chave) {
    for (int i = hash(chave); st[i].chave != NULLKEY; i = (i + 1) % M)
        if (chave == st[i].chave)
            return st[i].valor;
    return -1;
}

void hashTable::resize(int cap) {
    cout << "RESIZE!\n";
    hashTable temp(cap);
    for (int i = 0; i < M; i++) {
        if (st[i].chave != NULLKEY) {
            temp.insere(st[i].chave, st[i].valor);
        }
    }
    this->st = temp.st;
    this->M = temp.M;
}

// @@@ alterar após a remoção
bool hashTable::contains(string chave) {
    int i = hash(chave);
    if (st[i].chave != NULLKEY) return true;
    return false;
}

// código baseado em:
// https://www.geeksforgeeks.org/program-to-find-the-next-prime-number/
// Retorna o primeiro primo >= 2*n
int nextPrime(int n) {
    // Base case
    if (n <= 1)
        return 2;

    int prime = 2*n;
    bool found = false;

    // Loop continuously until isPrime returns
    // true for a number greater than 2*n
    while (!found) {
        prime++;
        if (isPrime(prime))
            found = true;
    }
    return prime;
}

// código retirado de:
// https://www.geeksforgeeks.org/program-to-find-the-next-prime-number/
bool isPrime(int n) {
    // Corner cases
    if (n <= 1)  return false;
    if (n <= 3)  return true;

    // This is checked so that we can skip
    // middle five numbers in below loop
    if (n%2 == 0 || n%3 == 0) return false;

    for (int i=5; i*i<=n; i=i+6)
        if (n%i == 0 || n%(i+2) == 0)
           return false;

    return true;
}



#endif
