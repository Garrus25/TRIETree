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

    auto insert(Node *x, string key, int value, int d) -> Node *;

public:
    Node *root;
    TRIETree();

    auto insert(string key, int value) -> Node;


    int get(string key) {
        Node *x = get(root, key, 0);
        if (x == nullptr) return 0;
        return x->value;
    }

    Node *get(Node *x, string key, int d) {
        if (x == nullptr) return nullptr;
        if (d == key.length()) return x;
        char c = key[d];
        return get(x->next[c], key, d + 1);
    }


    bool contains(string key) {
        return get(key) != 0;
    }

    int longestPrefixOf(Node *x, string query, int d, int length) {
        if (x == nullptr) return length;
        if (x->value != 0) length = d;
        if (d == query.length()) return length;
        char c = query[d];
        return longestPrefixOf(x->next[c], query, d + 1, length);
    }

    string longestPrefixOf(string query) {
        int length = longestPrefixOf(root, query, 0, 0);
        return query.substr(0, length);
    }

    vector<string> keys() {
        return keysWithPrefix("");
    }

    vector<string> keysWithPrefix(string prefix) {
        vector<string> queue;
        Node *x = get(root, prefix, 0);
        collect(x, prefix, queue);
        return queue;
    }

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

    vector<string> keysThatMatch(string pat) {
        vector<string> q;
        collect(root, "", pat, q);
        return q;
    }

    void collect(Node *x, string prefix, string pat, vector<string> &q) {
        if (x == nullptr) return;
        if (prefix.length() == pat.length() && x->value != 0) q.push_back(prefix);
        if (prefix.length() == pat.length()) return;
        char next = pat[prefix.length()];
        for (int c = 0; c < 256; c++)
            if (next == '.' || next == c)
                collect(x->next[c], prefix + (char) c, pat, q);
    }

    void del(string key) {
        root = del(root, key, 0);
    }

    Node *del(Node *x, string key, int d) {
        if (x == nullptr) return nullptr;
        if (d == key.length()) x->value = 0;
        else {
            char c = key[d];
            x->next[c] = del (x->next[c], key, d + 1);
        }
        if (x->value != 0) return x;
        for (int c = 0; c < 256; c++)
            if (x->next[c] != nullptr)
                return x;
        return nullptr;
    }


};

TRIETree::TRIETree() {
    Node *node;
    this->root = nullptr;
}

auto TRIETree::insert(string key, int value) -> Node {
    root = insert(root, key, value, 0);
    // insert(nullptr, "a", 0, 0);
}

auto TRIETree::insert(Node *x, string key, int value, int d) -> Node * {
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



ostream &operator<<(std::ostream &out, TRIETree &t) {
    for (auto x : t.keys()) {
        out << x << endl;
    }
    return out;
}


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

