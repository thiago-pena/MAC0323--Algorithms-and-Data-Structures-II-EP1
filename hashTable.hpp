#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

//Tamanho padrão da HT, usando um número primo.
// Caso necessário, a HT é redimensionada automaticamente
// com o primeiro primo >= 2 ao atual.
#define INITIALPRIME 151

#define NULLKEY "NULL"
#define NULLITEM -1

int nextPrime(int n);
bool isPrime(int n);
int abs(int x);

class hashTable {
    public:
        hashTable(string nome_arquivo, int tam = INITIALPRIME);
        void insere(string chave, int valor);
        int devolve(string chave);
        void remove(string chave);
        int rank(string chave);
        string seleciona(int k);

    private:
        struct par {
            string chave;
            int valor;
            bool usado;
        };
        par *st;
        int N;
        int M;
        int hash(string);
        void resize(int);
};

hashTable::hashTable(string nome_arquivo, int tam): st(new par[tam]), N(0), M(tam)
{
    for (int i = 0; i < M; i++) {
        st[i].chave = NULLKEY;
        st[i].usado = false;
    }

    if(nome_arquivo == NULLKEY) return;
    regex e {"[_[:punct:]]"};
    ifstream f;
    f.open(nome_arquivo);

    string p;
    while (f >> p) {
        p = regex_replace(p, e, "");
        if (p == "") continue;
        for (int i = 0; (unsigned)i < p.length(); i++)
            p[i] = tolower(p[i]);

        int count = devolve(p);

        if (count == NULLITEM)
            insere(p, 1);
        else
            insere(p, ++count);
    }

    f.close();
}

int hashTable::hash(string s) {
    int h = 0;
    for (int i = 0; (unsigned)i < s.length(); i++)
        h = (31 * h + abs((int)s[i])) % M;
    if (h < 0) cout << "ERRO! " << s << endl;
    return h;
}

void hashTable::insere(string chave, int valor) {
    if (N >= M/2) resize(nextPrime(M));
    int i;
    for (i = hash(chave); st[i].chave != NULLKEY; i = (i + 1) % M) // chave já existe na ST
        if (chave == st[i].chave) {
            st[i].valor = valor;
            return;
        }
    // chave nova
    st[i].chave = chave;
    st[i].valor = valor;
    st[i].usado = true;
    N++;
}

int hashTable::devolve(string chave) {
    for (int i = hash(chave); st[i].usado; i = (i + 1) % M)
        if (chave == st[i].chave)
            return st[i].valor;
    return NULLITEM;
}

void hashTable::resize(int cap) {
    hashTable temp(NULLKEY, cap);
    for (int i = 0; i < this->M; i++) {
        if (st[i].chave != NULLKEY) {
            temp.insere(st[i].chave, st[i].valor);
        }
    }
    par *aux = this->st;
    this->st = temp.st;
    delete [] aux;
    this->M = temp.M;
}

void hashTable::remove(string chave) {
    for (int i = hash(chave); st[i].usado; i = (i + 1) % M)
        if (chave == st[i].chave) {
            st[i].chave = NULLKEY;
            N--;
            return;
        }
}

int hashTable::rank(string chave) {
    string arr[N];
    int j = 0;
    for (int i = 0; i < M; i++) {
        if (st[i].chave != NULLKEY) {
            arr[j] = st[i].chave;
            j++;
        }
    }
    quicksort<string>(arr, 0, N);
    int ini = 0, fim = N - 1;
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

string hashTable::seleciona(int k) {
    if (k < 0 || k >= N) return NULLKEY;
    int j = 0;
    string arr[N];
    for (int i = 0; i < M; i++) {
        if (st[i].chave != NULLKEY) {
            arr[j] = st[i].chave;
            j++;
        }
    }
    quicksort<string>(arr, 0, N);
    return arr[k];
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

int abs(int x) {
    if (x >= 0) return x;
    else return -x;
}

#endif
