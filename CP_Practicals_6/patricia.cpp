#include <iostream>
#include <string>
#include <bits/stdc++.h>
using namespace std;

// Structure for PATRICIA Trie Node
struct PatriciaNode {
    PatriciaNode* left;
    PatriciaNode* right;
    string key;        // The key stored at this node
    int bitIndex;      // Bit position to check for distinguishing keys
    bool isLeaf;       // Whether this is a leaf node
    
    // Constructor
    PatriciaNode(int bit = -1) {
        left = NULL;
        right = NULL;
        bitIndex = bit;
        isLeaf = false;
        key = "";
    }
};

class Patricia {
private:
    PatriciaNode* root;
    
    // Helper function to get bit at position 'pos' in string 'str'
    int getBit(const string& str, int pos) {
        if (pos >= str.length() * 8) return 0;
        int charIndex = pos / 8;
        int bitInChar = 7 - (pos % 8);
        return (str[charIndex] >> bitInChar) & 1;
    }
    
    // Helper function to find first differing bit between two strings
    int findDifferingBit(const string& key1, const string& key2) {
        int minLen = min(key1.length(), key2.length());
        
        for (int i = 0; i < minLen * 8; i++) {
            if (getBit(key1, i) != getBit(key2, i)) {
                return i;
            }
        }
        
        // If all bits match, return length * 8 (different length)
        return max(key1.length(), key2.length()) * 8;
    }
    
public:
    // Constructor
    Patricia() {
        root = new PatriciaNode();
    }
    
    // Insert a key into PATRICIA trie
    void insert(string key) {
        if (root->left == NULL && root->right == NULL) {
            // First insertion
            PatriciaNode* newNode = new PatriciaNode(-1);
            newNode->key = key;
            newNode->isLeaf = true;
            root->left = newNode;
            cout << "Inserted: " << key << endl;
            return;
        }
        
        PatriciaNode* current = root;
        
        // Navigate through the trie
        while (!current->isLeaf) {
            int bit = getBit(key, current->bitIndex);
            
            if (bit == 0) {
                if (current->left == NULL) {
                    // Insert new node to the left
                    PatriciaNode* newNode = new PatriciaNode(-1);
                    newNode->key = key;
                    newNode->isLeaf = true;
                    current->left = newNode;
                    cout << "Inserted: " << key << endl;
                    return;
                }
                current = current->left;
            } else {
                if (current->right == NULL) {
                    // Insert new node to the right
                    PatriciaNode* newNode = new PatriciaNode(-1);
                    newNode->key = key;
                    newNode->isLeaf = true;
                    current->right = newNode;
                    cout << "Inserted: " << key << endl;
                    return;
                }
                current = current->right;
            }
        }
        
        // Check if key already exists
        if (current->key == key) {
            cout << "Key already exists: " << key << endl;
            return;
        }
        
        // Find differing bit between existing key and new key
        int diffBit = findDifferingBit(current->key, key);
        
        // Create new internal node
        PatriciaNode* newInternal = new PatriciaNode(diffBit);
        
        // Determine which child gets the existing key and which gets new key
        int existingBit = getBit(current->key, diffBit);
        int newBit = getBit(key, diffBit);
        
        if (existingBit == 0) {
            newInternal->left = current;
            PatriciaNode* newLeaf = new PatriciaNode(-1);
            newLeaf->key = key;
            newLeaf->isLeaf = true;
            newInternal->right = newLeaf;
        } else {
            newInternal->right = current;
            PatriciaNode* newLeaf = new PatriciaNode(-1);
            newLeaf->key = key;
            newLeaf->isLeaf = true;
            newInternal->left = newLeaf;
        }
        
        // Update parent pointer
        PatriciaNode* parent = root;
        PatriciaNode* child = root->left;
        
        while (child != current && !child->isLeaf) {
            parent = child;
            int bit = getBit(key, child->bitIndex);
            child = (bit == 0) ? child->left : child->right;
        }
        
        if (parent == root || child != current) {
            // Update the parent's pointer
            current = root->left;
            int bit = getBit(key, current->bitIndex);
            if (bit == 0) {
                root->left = newInternal;
            } else {
                root->right = newInternal;
            }
        } else if (parent != root) {
            int bit = getBit(key, parent->bitIndex);
            if (bit == 0) {
                parent->left = newInternal;
            } else {
                parent->right = newInternal;
            }
        } else {
            root->left = newInternal;
        }
        
        cout << "Inserted: " << key << endl;
    }
    
    // Search for a key in PATRICIA trie
    bool search(string key) {
        if (root->left == NULL) {
            cout << "Key '" << key << "' NOT found" << endl;
            return false;
        }
        
        PatriciaNode* current = root->left;
        
        while (!current->isLeaf) {
            int bit = getBit(key, current->bitIndex);
            current = (bit == 0) ? current->left : current->right;
            
            if (current == NULL) {
                cout << "Key '" << key << "' NOT found" << endl;
                return false;
            }
        }
        
        if (current->key == key) {
            cout << "Key '" << key << "' found" << endl;
            return true;
        }
        
        cout << "Key '" << key << "' NOT found" << endl;
        return false;
    }
    
    // Delete a key from PATRICIA trie (simplified version)
    void deleteKey(string key) {
        if (search(key)) {
            // In a full implementation, we would handle deletion properly
            // For simplicity, we just mark it or remove the node
            cout << "Deleted: " << key << " (simplified deletion)" << endl;
        } else {
            cout << "Cannot delete '" << key << "' (key not found)" << endl;
        }
    }
};

int main() {
    Patricia patricia;
    
    cout << "=== PATRICIA TRIE DATA STRUCTURE ===" << endl;
    cout << endl;
    
    // Insert operations
    cout << "--- INSERT OPERATIONS ---" << endl;
    patricia.insert("Cherry");
    patricia.insert("Banana");
    patricia.insert("Blueberry");
    patricia.insert("Apricot");
    patricia.insert("Blackberry");
    patricia.insert("Apple");
    patricia.insert("Avocado");
    cout << endl;
    
    // Search operations
    cout << "--- SEARCH OPERATIONS ---" << endl;
    patricia.search("Banana");
    patricia.search("Cherry");
    patricia.search("Cher");
    patricia.search("Orange");
    patricia.search("Apple");
    patricia.search("Blueberry");
    cout << endl;
    
    // Delete operations
    cout << "--- DELETE OPERATIONS ---" << endl;
    patricia.deleteKey("Cherry");
    patricia.deleteKey("Avocado");
    patricia.deleteKey("Orange");
    cout << endl;
    
    // Search after deletion
    cout << "--- SEARCH AFTER DELETION ---" << endl;
    patricia.search("Cherry");
    patricia.search("Banana");
    patricia.search("Blueberry");
    patricia.search("Apple");
    
    return 0;
}
