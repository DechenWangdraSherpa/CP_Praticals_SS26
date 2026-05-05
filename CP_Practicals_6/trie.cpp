#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

// Each node in the Trie
struct TrieNode {
    map<char, TrieNode*> children; // stores child nodes
    bool is_end;                   // true if a word ends here

    TrieNode() {
        is_end = false;
    }
};

class Trie {
public:
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    // ---- INSERT ----
    void insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            // if letter doesn't exist, create a new node
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c]; // move to next node
        }
        node->is_end = true; // mark end of word
        cout << "  Inserted: '" << word << "'" << endl;
    }

    // ---- SEARCH ----
    bool search(string word) {
        TrieNode* node = root;
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                return false; // letter not found
            }
            node = node->children[c];
        }
        return node->is_end; // true only if complete word
    }

    // ---- PREFIX CHECK ----
    bool startsWith(string prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            if (node->children.find(c) == node->children.end()) {
                return false;
            }
            node = node->children[c];
        }
        return true;
    }

    // ---- DELETE (recursive helper) ----
    // Returns: {deleted, canDeleteNode}
    pair<bool, bool> deleteHelper(TrieNode* node, string word, int depth) {
        if (node == nullptr)
            return {false, false};

        if (depth == (int)word.size()) {
            if (!node->is_end)
                return {false, false}; // word not in trie
            node->is_end = false;      // unmark end of word
            bool canDelete = node->children.empty();
            return {true, canDelete};
        }

        char c = word[depth];
        if (node->children.find(c) == node->children.end())
            return {false, false}; // path doesn't exist

        auto [deleted, canDeleteChild] = deleteHelper(node->children[c], word, depth + 1);

        if (deleted && canDeleteChild) {
            delete node->children[c];
            node->children.erase(c);
            bool canDelete = (!node->is_end) && node->children.empty();
            return {true, canDelete};
        }
        return {deleted, false};
    }

    void deleteWord(string word) {
        auto [deleted, _] = deleteHelper(root, word, 0);
        if (deleted)
            cout << "  Deleted: '" << word << "'" << endl;
        else
            cout << "  '" << word << "' not found, nothing deleted" << endl;
    }

    // ---- DISPLAY all words ----
    void displayHelper(TrieNode* node, string prefix, vector<string>& words) {
        if (node->is_end)
            words.push_back(prefix);
        for (auto& pair : node->children) {
            displayHelper(pair.second, prefix + pair.first, words);
        }
    }

    void display() {
        vector<string> words;
        displayHelper(root, "", words);
        cout << "  Words in Trie: [ ";
        for (string& w : words) cout << "'" << w << "' ";
        cout << "]" << endl;
    }
};

// ============================================================
// MAIN
// ============================================================
int main() {
    cout << "==================================================" << endl;
    cout << "         TRIE DATA STRUCTURE DEMO (C++)" << endl;
    cout << "==================================================" << endl;

    Trie trie;

    // --- INSERT ---
    cout << "\n[1] INSERTING COUNTRIES:" << endl;
    string words[] = {"India", "Italy", "Ireland", "Brazil", "Bangladesh", "Bahrain", "Canada"};
    for (string w : words)
        trie.insert(w);

    cout << "\n";
    trie.display();

    // --- SEARCH ---
    cout << "\n[2] SEARCHING COUNTRIES:" << endl;
    string search_words[] = {"India", "Italy", "Ind", "Brazil", "Japan"};
    for (string w : search_words) {
        cout << "  Search '" << w << "': "
             << (trie.search(w) ? "FOUND" : "NOT FOUND") << endl;
    }

    // --- PREFIX CHECK ---
    cout << "\n[3] PREFIX (startsWith) CHECK:" << endl;
    string prefixes[] = {"Ind", "Ba", "Ir", "Can"};
    for (string p : prefixes) {
        cout << "  Prefix '" << p << "': "
             << (trie.startsWith(p) ? "EXISTS" : "NOT EXISTS") << endl;
    }

    // --- DELETE ---
    cout << "\n[4] DELETING COUNTRIES:" << endl;
    trie.deleteWord("Italy");
    trie.deleteWord("Japan");
    trie.deleteWord("Brazil");

    cout << "\n";
    trie.display();

    // --- SEARCH AFTER DELETE ---
    cout << "\n[5] SEARCH AFTER DELETION:" << endl;
    string check[] = {"Italy", "India", "Brazil", "Bangladesh"};
    for (string w : check) {
        cout << "  Search '" << w << "': "
             << (trie.search(w) ? "FOUND" : "NOT FOUND") << endl;
    }

    return 0;
}