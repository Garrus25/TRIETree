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
     * Służy do zwracania wartości powiązanej z kluczem z drzewa TRIE o korzeniu x
     *
     * @param x - węzeł od którego rozpoczynamy wyszukiwanie
     * @param key - klucz, słowo którego szukamy
     * @param d - indeks aktualnie przetwarzanej litery w słowie
     * @return - jeżeli nie znajdujemy wartości zwracamy null, jeśli znajdujemy to zwracamy powiązany z nią węzeł
     *
     * jeśli (węzeł nie istnieje) zwracamy null
       jeśli (aktualnie przetwarzana litera = długość słowa) zwracamy znaleziony węzeł
       deklaracja kolejnej litery w słowie i przypisanie do niej słowa którego szukamy[indeks aktualnie przetwarzanej litery w słowie]
       przechodzimy do następnego węzła oraz sprawdzamy następną literę w danym słowie; rekurencyjnie wywołujemy metodę get z nastepującymi argumentami(następny węzeł odpowiadający konkretnej literze)
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
     * Służy do wstawiania słowa do drzewa TRIE
     *
     * @param x - węzeł od którego rozpoczynamy wstawianie
     * @param key - klucz, słowo które wstawiamy
     * @param value - wartość odpowiadająca danemu słowu
     * @param d - indeks aktualnie przetwarzanej litery w słowie
     * @return - zwraca przetworzony węzeł
     *
     * jeśli węzeł x nie istnieje
     *  tworzymy go
       jeśli aktualnie przetwarzana pozycja w słowie jest równa jego ostatniemu znakowi
        do węzła końcowego przypisujemy wartość odpowiadającą wstawianemu słowu
        usuwa klucz jeśli wartość przypisana danemu słowu jest równa 0
        i zwracamy ten wezeł

       deklaracja kolejnej litery w słowie i przypisanie do niej słowa które wstawiamy[indeks aktualnie przetwarzanej litery w słowie]
       ustawienie następnego poziomu węzła[na kolejną literę w słowie] - rekurencyjnie wywołanie tej samej metody aby w następnym poziomie wstawić daną literę
       (węzeł[następny poziom],słowo którego szukamy,wartość odpowiadająca danemu słowu, indeks aktualnie przetwarzanej litery w kluczu +1)
       zwracamy węzeł końcowy
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
     * Służy do wyszukiwania najdłuższego przedrostka danego słowa
     *
     * @param x - węzeł który aktualnie przetwarzamy
     * @param query - łańcuch znaków dla którego szukamy najdłuższego przedrostka
     * @param d - indeks aktualnie przetwarzanej litery w słowie
     * @param length - ilość już pasujących do słowa liter
     * @return - zwraca ilość aktualnie pasujących do słowa liter
     *
     * jeśli (węzeł który aktualnie przetwarzamy nie istnieje) zwracamy zwraca ilość aktualnie pasujących do słowa liter
       jeśli (w danym węźle kończy się słowo) ilość aktualnie pasujących do słowa liter = indeks aktualnie przetwarzanej litery w słowie;
       jeśli (indeks aktualnie przetwarzanej litery w słowie jest rowny długości słowa) zwracamy długość przedrostka jako całe słowo
       deklaracja kolejnej litery w słowie = słowo którego prefiksu szukamy [indeks aktualnie przetwarzanej litery w słowie]
       sprawdzamy następny poziom w drzewie dla następnej litery - rekurencyjne wywołujemy te samą metodę z argumentami (węzeł[następny poziom],łańcuch znaków dla którego szukamy najdłuższego przedrostka,
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
     * jeśli węzeł jest pusty
     *  przerywamy pracę metody
       jeśli w danym węźle kończy się słowo
        dodaj słowo do wektora
       przechodzimy przez cały alfabet w danym węźle
        i wywołujemy rekurencyjnie metodę collect z argumentami (węzeł odpowiadający danej literze w alfabecie,klucz zwiększony o daną literę w alfabecie,
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
     * Służy do usuwania kluczy z drzewa TRIE
     *
     * @param x - węzeł który aktualnie przetwarzamy
     * @param key - klucz który zostanie usunięty
     * @param d - indeks aktualnie przetwarzanej litery w słowie
     * @return - zwraca przetworzony węzeł
     *
     * jeśli (węzeł który aktualnie przetwarzamy jest pusty) zwracamy null;
        jeśli (indeks aktualnie przetwarzanej litery w słowie jest równy długości słowa) usuń znacznik końca słowa w danym węźle poprzez przypisanie do niego wartośći 0
        w przeciwnym wypadku
         deklaracja kolejnej litery w słowie = słowo którego prefiksu szukamy [indeks aktualnie przetwarzanej litery w słowie]
         rekurencyjne wywołanie metody usuwającej kolejne litery danego słowa klucza z argumentami(węzeł[następny poziom],
         klucz, indeks aktualnie przetwarzanej litery w słowie + 1)

        jeśli (wartość w aktualnie przetwarzanym węźle nie jest równa 0) zwracamy aktualnie przetwarzany węzeł;
        przejdź przez cały alfabet w danym węźle
            jeśli następny znak nie jest nullem
                zwracamy aktualnie przetwarzany węzeł;
        zwracamy null;
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


    /** Służy do zwracania ilości słów w drzewie
     *
     * @param x - węzeł od którego rozpoczynamy sprawdzanie
     * @return - ilość słów w drzewie
     *
     * jeśli węzeł od którego rozpoczynamy sprawdzanie nie istnieje zwracamy 0
        deklaracja licznika i zainicjowanie go wartością 0
        jeśli wartość w danym węźle nie jest rowna 0 inkrementujemy licznik
        przechodzimy przez cały alfabet
            do licznika przypisujemy wartość zwróconą przez rekurencyjne wywołanie tej samej metody z pracującej na następnym poziomie -  size(x->next[i]);
        zwracamy licznik
     */
    int size(Node *x) {
        if (x == nullptr) return 0;

        int counter = 0;
        if (x->value != 0) counter++;

        for (char i = 0; i < 127; i++) {
            counter += size(x->next[i]);
        }
        return counter;
    }

public:
    /** Służy do zwracania wartości powiązanej z kluczem z drzewa TRIE o korzeniu x
     *
     * @param key - słowo którego szukamy
     * @return zwraca wartość przypisaną danemu słowu w drzewie TRIE, 0 jeśli klucz nie znajduje się w drzewie
     *
     * Tworzymy nowy węzeł i przypisujemy do niego wartosć zwróconą przez prywatną metodę get z argumentami(korzeń, słowo którego szukamy,
     * indeks aktualnie przetwarzanej litery w słowie)
        jeśli nie znaleziono klucza w drzewie zwróć 0;
        w przeciwnym wypadku
        zwracamy wartość odpowiadającą danemu słowu
     */

    /** Służy do zwrócenia wartości korzneia
     *
     * @return korzeń
     *
     * zwracamy korzeń
     */
    Node* getRoot(){
        return root;
    }

    int get(string key) {
        Node *x = get(root, key, 0);
        if (x == nullptr) return 0;
        return x->value;
    }

    /** Służy do sprawdzenia czy dany klucz znajduje się w drzewie
     *
     *
     * @param key - sprawdzany klucz
     * @return - wywołanie metody która sprawdza czy klucz znajduje się w drzewie z argumentem (klucz)
     *
     * zwracamy wywołanie metody get(klucz) jeśli zwraca ona wartość różną od zera.
     * O oznacza to że klucz znajduje się w drzewie.
     */
    bool contains(string key) {
        return get(key) != 0;
    }

    /** Służy do wstawiania słowa do drzewa TRIE
     *
     * @param key - słowo które wstawiamy
     * @param value - indeks przypisany danemu słowu
     *
     * przypisujemy do korzenia wynik zwrócony przez prywatną metodę insert z argumentami(korzeń,klucz,wartość,
     * indeks aktualnie przetwarzanej litery w słowie)
     *
     */
    void insert(string key, int value) {
        root = insert(root, key, value, 0);
    }

    /** Służy do wyszukiwania najdłuższego przedrostka danego słowa
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

    /** Służy do zwracania wszystkich kluczy dla których prefiksem jest puste słowo
     *
     * @return - wszystkie klucze dla których prefiksem jest puste słowo
     * czyli wszystkie klucze z drzewa
     *
     * zwracamy wartość zwróconą przez metodę keysWithPrefix z argumentem(puste słowo);
     */
    vector<string> keys() {
        return keysWithPrefix("");
    }

    /** Służy do zebrania wszystkich słów pasujących do danego przedrostka w jednym wektorze
     *
     * @param prefix - dany przedrostek
     * @return - zwracamy kolekcję kluczy z danym przedrostkiem
     *
     * utworzenie wektora
        utworzenie nowego węzła i przypisanie do niego wartośći zwracanej przez prywatną metodę get z argumentami(korzeń, przedrostek, 0)
        zebranie do kolekcji wszystkich słów pasujących do danego przedrostka - wywołanie prywatnej metody collect z argumentami(aktualnie przetwarzany węzeł,przedrostek,wektor)
        zwracamy wektor słów pasujących do danego przedrostka
     */
    vector<string> keysWithPrefix(string prefix) {
        vector<string> queue;
        Node *x = get(root, prefix, 0);
        collect(x, prefix, queue);
        return queue;
    }

    /**
     * Wyszykuje słowa pasujące do danego wzorca, znakiem "." można zastąpić dowolny znak
     *
     * @param pat - wzorzec
     * @return - kolekcja słow pasujących do wzorca
     *
     * utworzenie wektora
       wywołanie metody której zadaniem jest dodanie do kolekcji wszystkich słow pasujących do danego wzorca z argumentami
       (korzeń, "", prefiks, kolekcja do której zostanie wstawione pasujące słowo)
       zwracamy wektor pasujących słów
     */
    vector<string> keysThatMatch(string pat) {
        vector<string> q;
        collect(root, "", pat, q);
        return q;
    }

    /**
     * Służy do zapisywania klucza w metodzie keysThatMatch
     *
     * @param x - węzeł który aktualnie przetwarzamy
     * @param prefix - szukany przedrostek
     * @param pat - wzorzec
     * @param q - kolekcja do której zostanie wstawione odpowiednie słowo
     *
     * jeśli węzeł który aktualnie przetwarzamy jest pusty przerywamy pracę metody
        jeśli długość prefiksu jest równa długości wzorca oraz wartość w węźle który aktualnie przetwarzamy nie jest równa 0
        wstawiany do wektora aktualny prefiks
        jeśli długość przedrostka jest równa długości wzorca przerywamy pracę metody
        deklaracja następnej litery w słowie oraz przypisanie do niej następnego znaku wzorca
        przechodzimy przez cały alfabet w danym węźle
            jeśli następny znak w danym słowie jest równy "." albo jest równy znakowi na danej pozycji we wzorcu
                wywołujemy metodę collect z argumentami (węzeł[następny poziom],prefiks + znak na danej pozycji we wzorcu,
                wzorzec, kolekcja) wstawiającą dany klucz do kolekcji
     *
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
     * Służy do usuwania danego klucza z drzewa
     *
     * @param key - klucz
     *
     * przypisanie do korzenia wartości zwróconych przez metodę del z argumentami (korzeń,klucz,0)
     *
     */
    void del(string key) {
        root = del(root, key, 0);
    }

    /**
     * Konstruktor domyślny,
     *
     * Utworzenie struktury przechowującej wartość oraz alfabet
     * Przypisanie do korzenia wartości null
     *
     */
    TRIETree() {
        Node *node;
        this->root = nullptr;
    }

    /**
     * Służy do zwracania ilości słów w drzewie
     *
     * @return zwraca ilość słów w drzewie
     *
     * zwracamy wartość zwracaną przez prywatną metodę size z argumentem (korzeń) -  size(root)
     */
    int size() {
        return size(root);
    }

    /**
     * Służy do wyświetlenia wszystkich kluczy w drzewie
     *
     * @param out - strumień wyjściowy na który zostaną wysłane dane
     * @param t - obiekt klasy TRIETree, którego klucze mamy za zadanie wyświetlić
     * @return - strumień wyjściowy
     *
     * dla każdego węzła w obiekcie t
            przekierowujemy na strumień wyjściowy dany klucz
        zwracamy strumień wyjściowy
     */
    friend ostream &operator<<(std::ostream &out, TRIETree &t) {
        for (auto x : t.keys()) {
            out << x << endl;
        }
        return out;
    }
    /**
     * Służy do sprawdzenia czy drzewo jest puste
     *
     * @return - czy drzewo jest puste
     *
     * jeśli rozmiar = 0 zwracamy true
     * w przeciwnym wypadku false
     */
    bool isEmpty(){
        if (size() == 0) return true;
        return false;
    }
};

int main() {
    TRIETree *a = new TRIETree;

    cout << " a->isEmpty():1: " << a->isEmpty() << endl;
    cout << " a->size():0: " << a->size() << endl;

    a->insert("banan", 1);
    a->insert("bananan", 2);
    a->insert("stos", 3);
    a->insert("stosy", 4);
    a->insert("stosowany", 5);
    a->insert("baner", 6);

//    for (int i = 6; i < 500; ++i) {
//        a->insert(, 5);
//    }

    cout << " a->isEmpty():0 " << a->isEmpty() << endl;
    cout << " a->size():5 " << a->size() << endl;
    cout << endl;

    cout << *a << endl;

    cout << "a->get(\"banan\"): 1:" << a->get("banan") << endl;
    cout << "a->get(\"bananan\"): 2:" << a->get("bananan") << endl;
    cout << "a->get(\"stos\"): 3:" << a->get("stos") << endl;
    cout << "a->get(\"stosy\"): 4:" << a->get("stosy") << endl;
    cout << "a->get(\"stosowany\"): 5:" << a->get("stosowany") << endl;
    cout << "a->get(\"zastosowany\"): 0:" << a->get("zastosowany") << endl;

    cout << endl;
    cout << "a->contains(\"banan\"): 1:" << a-> contains("banan") << endl;
    cout << "a->contains(\"bananan\"): 1:" << a-> contains("bananan") << endl;
    cout << "a->contains(\"stos\"): 1:" << a-> contains("stos") << endl;
    cout << "a->contains(\"stosy\"): 1:" << a-> contains("stosy") << endl;
    cout << "a->contains(\"stosowany\"): 1:" << a-> contains("stosowany") << endl;
    cout << "a->contains(\"zastosowany\"): 0:" << a-> contains("zastosowany") << endl;
    cout << endl;

    cout << "a->longestPrefixOf(\"banan\"):banan: "<< a->longestPrefixOf("banan") <<  endl;
    cout << "a->longestPrefixOf(\"banansss\"):banan: " << a->longestPrefixOf("banansss") << endl;
    cout << "a->longestPrefixOf(\"stosowac\"):stos: " << a->longestPrefixOf("stosowac") << endl;
    cout << "a->longestPrefixOf(\"stosowanie\"):stos: " << a->longestPrefixOf("stosowanie") << endl;
    cout << "a->longestPrefixOf(\"stosowanyy\"):stosowany: " << a->longestPrefixOf("stosowanyy") << endl;
    cout << endl;

    for (int i = 0; i < a->keys().size(); ++i) {
        cout << a->keys()[i] << endl;
    }

    cout << endl;
    vector<string> test = a->keysThatMatch("ban..");

    for (auto & i : test) {
        cout << i << endl;
    }
    cout << endl;

    vector<string> test2;

    a->collect(a->getRoot(),"","ban..",test2);

    for (auto & i : test2) {
        cout << i << endl;
    }
    cout << endl;

    a->del("banan");
    a->del("bananan");
    a->del("baner");

    cout << *a;
    return 0;
}

