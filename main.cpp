#include <iostream>
#include <string>
#include "vector"

using namespace std;
struct Node {
    int value = 0;
    struct Node *next[256];

};

class TRIETree {
private:
    Node *root;

    /**
     * Zwracanie wartości powiązanej z kluczem z drzewa TRIE o korzeniu x
     *
     * @param x - węzeł od którego rozpoczynamy wyszukiwanie
     * @param key - słowo którego szukamy
     * @param d - indeks aktualnie przetwarzanej litery w słowie
     * @return - jeżeli nie znajdujemy wartości zwracamy 0, jeśli znajdujemy to zwracamy powiązany z nią indeks
     *
     * jeśli (węzeł nie istnieje) zwracamy null
       jeśli (aktualnie przetwarzana litera = długość słowa) zwracamy x
       deklaracja kolejnej litery w słowie = słowo którego szukamy[indeks aktualnie przetwarzanej litery w słowie]
       rekurencyjnie wywołujemy tę samą metodę z następującymi argumentami(następny węzeł odpowiadający konkretnej literze
       klucz, indeks aktualnie przetwarzanej litery w kluczu +1)
     *
     */
    Node *get(Node *x, string key, int d) {
        if (x == nullptr) return nullptr;
        if (d == key.length()) return x;
        char c = key[d];
        return get(x->next[c], key, d + 1);
    }

    /**
     * wstawia słowo do drzewa TRIE
     *
     * @param x - węzeł od którego rozpoczynamy wstawianie
     * @param key - słowo które wstawiamy
     * @param value - wartość odpowiadająca danemu słowu
     * @param d - indeks aktualnie przetwarzanej litery w słowie
     * @return - zwraca przetworzony węzeł
     *
     * jeśli węzeł x nie istnieje
     *  tworzymy go
       jeśli aktualnie przetwarzana pozycja w słowie jest równa jego końcowi
        do węzła końcowego przypisujemy wartość odpowiadającą wstawianemu słowu
        i zwracamy węzeł

       deklaracja kolejnej litery w słowie = słowo które wstawiamy[indeks aktualnie przetwarzanej litery w słowie]
       węzeł[następny poziom] = rekurencyjnie wywołanie tej samej metody aby w następnym poziomie wstawić daną literę
       (węzeł[następny poziom],słowo którego szukamy,wartość odpowiadająca danemu słowu, indeks aktualnie przetwarzanej litery w kluczu +1)
       zwracamy korzeń drzewa
     */
    Node *insert(Node *x, string key, int value, int d) {
        if (x == nullptr) {
            x = new Node();
        }
        if (d == key.size()) {
            x->value = value;
            return x;
        }
        char c = key[d];
        x->next[c] = insert(x->next[c], key, value, d + 1);
        return x;
    }

    /**
     * Wyszukuje najdłuższy przedrostek danego słowa
     *
     * @param x - węzeł który aktualnie przetwarzamy
     * @param query - łańcuch znaków dla którego szukamy najdłuższego przedrostka
     * @param d - indeks aktualnie przetwarzanej litery w słowie
     * @param length - ilość już pasujących do słowa liter
     * @return - zwraca ilość aktualnie pasujących do słowa liter
     *
     * jeśli (węzeł który aktualnie przetwarzamy nie istnieje) zwracamy zwraca ilość aktualnie pasujących do słowa liter
       jeśli (w danym węźle kończy się słowo) zwracana ilość aktualnie pasujących do słowa liter = indeks aktualnie przetwarzanej litery w słowie;
       jeśli (indeks aktualnie przetwarzanej litery w słowie = długość słowa) zwracamy długość przedrostka jako całe słowo
       deklaracja kolejnej litery w słowie = słowo którego prefiksu szukamy [indeks aktualnie przetwarzanej litery w słowie]
       rekurencyjne wywołujemy te samą metodę z argumentami (węzeł[następny poziom],łańcuch znaków dla którego szukamy najdłuższego przedrostka,
       indeks aktualnie przetwarzanej litery w słowie,ilość już pasujących do słowa liter)
     */
    int longestPrefixOf(Node *x, string query, int d, int length) {
        if (x == nullptr) return length;
        if (x->value != 0) length = d;
        if (d == query.length()) return length;
        char c = query[d];
        return longestPrefixOf(x->next[c], query, d + 1, length);
    }

    /**
     * Służy do zapisywania kluczy w metodach keys i keysWithPrefix
     *
     * @param x - węzeł który aktualnie przetwarzamy
     * @param key - klucz którego część już dopasowaliśmy
     * @param queue - służy do przechowywania wszystkich słów
     *
     * jeżeli (węzeł jest pusty)
     *  zakończ gałęź rekurencji
       jeśli w danym węźle kończy się słowo
        dodaj słowo do vectora
       przejdź przez cały alfabet w danym węźle
        i wywołaj rekurencyjnie metodę collect z argumentami (węzeł odpowiadający danej literze w alfabecie,klucz zwiększony o daną literę w alfabecie,
        vector)
        aby znaleźć pozostałe słowa
     */
    void collect(Node *x, string key, vector<string> &queue) {
        if (x == nullptr) {
            return;
        }
        if (x->value != 0) {
            queue.push_back(key);
        }
        for (int c = 0; c < 256; c++) {
            collect(x->next[c], key + (char) c, queue);
        }
    }

    /**
     * Usuwa klucz z drzewa TRIE
     *
     * @param x - węzeł który aktualnie przetwarzamy
     * @param key - klucz który zostanie usunięty
     * @param d - indeks aktualnie przetwarzanej litery w słowie
     * @return - zwraca przetworzony węzeł
     *
     * jeśli (węzeł który aktualnie przetwarzamy jest pusty) zwracamy pusty wskaźnik;
        jeśli (indeks aktualnie przetwarzanej litery w słowie jest równy długości słowa) usuń znacznik końca słowa w danym węźle = 0;
        w przeciwnym wypadku
         deklaracja kolejnej litery w słowie = słowo którego prefiksu szukamy [indeks aktualnie przetwarzanej litery w słowie]
         rekurencyjne wywołanie metody kasującej kolejne litery danego słowa klucza z argumentami(węzeł[następny poziom],
         klucz, indeks aktualnie przetwarzanej litery w słowie + 1)

        jeśli (wartość w aktualnie przetwarzanym węźle nie jest równa 0) zwracamy aktualnie przetwarzany węzeł;
        przejdź przez cały alfabet w danym węźle
            jeśli następny znak nie jest nullem
                zwracamy aktualnie przetwarzany węzeł;
        zwracamy nullptr;
     */
    Node *del(Node *x, string key, int d) {
        if (x == nullptr) return nullptr;
        if (d == key.length()) x->value = 0;
        else {
            char c = key[d];
            x->next[c] = del(x->next[c], key, d + 1);
        }
        if (x->value != 0) return x;
        for (int c = 0; c < 256; c++)
            if (x->next[c] != nullptr)
                return x;
        return nullptr;
    }

public:
    /**
     *
     * @param key - słowo którego szukamy
     * @return zwraca wartość przypisaną danemu słowu w drzewie TRIE, 0 jeśli klucz nie znajduje się w drzewie
     *
     * Węzeł = wywołanie prywatnej metody get z parametrami(korzeń, słowo którego szukamy,
     * indeks aktualnie przetwarzanej litery w słowie)
        jeśli nie znaleziono klucza w drzewoe zwróć 0;
        w przeciwnym wypadku
        zwracamy wartość odpowiadającą danemu słowu
     */
    int get(string key) {
        Node *x = get(root, key, 0);
        if (x == nullptr) return 0;
        return x->value;
    }

    /**
     *
     * @param key - klucz który sprawdzamy czy jest w drzewie
     * @return - wywołanie metody która sprawdza czy klucz znajduje się w drzewie z argumentem (klucz)
     *
     * zwracamy wywołanie metody get(klucz) jeśli zwraca ona wartość różną od zera.
     * Oznacza to że klucz znajduje się w drzewie.
     */
    bool contains(string key) {
        return get(key) != 0;
    }

    /**
     *
     * @param key - słowo które wstawiamy
     * @param value - indeks przypisany danemu słowu
     *
     * przypisujemy do korzenia wynik zwrócony przez metodę insert z argumentami(korzeń,klucz,wartość,
     * indeks aktualnie przetwarzanej litery w słowie)
     * insert z argumentami(root, key, value, 0);
     */
    //TUBYŁOAUTOJAKCOŚ
    void insert(string key, int value) {
        root = insert(root, key, value, 0);
    }

    /**
     *
     * @param query - łańcuch znaków dla którego szukamy najdłuższego przedrostka
     * @return - najdłuższy pasujący przedrostek odpowiadający danemu słowu
     *
     * długość najdłuższego pasującego przedrostku = wynik metody longestPrefixOf z argumentami
     * (korzeń, łańcuch znaków dla którego szukamy najdłuższego przedrostka, 0, 0);
        zwracamy najdłuższy prefiks pasujący dla danego słowa
     */
    string longestPrefixOf(string query) {
        int length = longestPrefixOf(root, query, 0, 0);
        return query.substr(0, length);
    }

    /**
     *
     * @return - wszystkie klucze dla których prefiksem jest puste słowo
     * czyli wszystkie klucze z drzewa
     *
     * zwracamy wartość zwróconą przez metodę keysWithPrefix z argumentem(puste słowo);
     */
    vector<string> keys() {
        return keysWithPrefix("");
    }

    /**
     *
     * @param prefix - dany przedrostek
     * @return - zwracamy kolekcję kluczy z danym przedrostkiem
     *
     * utworzenie kolekcji;
        Node *x = get(root, prefix, 0);
        collect(x, prefix, queue);
        return queue;
     */
    vector<string> keysWithPrefix(string prefix) {
        vector<string> queue;
        Node *x = get(root, prefix, 0);
        collect(x, prefix, queue);
        return queue;
    }

    /**
     *
     * @param pat
     * @return
     */
    vector<string> keysThatMatch(string pat) {
        vector<string> q;
        collect(root, "", pat, q);
        return q;
    }

    /**
     *
     * @param x
     * @param prefix
     * @param pat
     * @param q
     */
    void collect(Node *x, string prefix, string pat, vector<string> &q) {
        if (x == nullptr) return;
        if (prefix.length() == pat.length() && x->value != 0) q.push_back(prefix);
        if (prefix.length() == pat.length()) return;
        char next = pat[prefix.length()];
        for (int c = 0; c < 256; c++)
            if (next == '.' || next == c)
                collect(x->next[c], prefix + (char) c, pat, q);
    }

    /**
     *
     * @param key
     */
    void del(string key) {
        root = del(root, key, 0);
    }

    /**
     *
     */
    TRIETree() {
        Node *node;
        this->root = nullptr;
    }

    /**
     *
     * @param out
     * @param t
     * @return
     */
    friend ostream &operator<<(std::ostream &out, TRIETree &t) {
        for (auto x : t.keys()) {
            out << x << endl;
        }
        return out;
    }
};


int main() {
    TRIETree *a = new TRIETree;
    a->insert("xkw", 5);
    a->insert("banan", 4);
    a->insert("badupa", 6);
    a->insert("dupaa", 456);
    a->insert("asdf", 234);
//
//    cout << a->contains("banan") << endl;
//    cout << a->contains("dupa") << endl;
//    cout << a->longestPrefixOf("asdff")<<endl;
    cout << *a;
//    for (auto x : a->keysThatMatch("ba...")) {
//        cout << x << endl;
//    }
    cout << endl;
    a->del("badupa");
    cout << *a;

    return 0;
}

