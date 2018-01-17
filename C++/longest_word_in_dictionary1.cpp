class TrieNode {
public:
    vector<TrieNode*> next;
    bool isWord;
    string word;
    
    TrieNode() {
        word = "";
        isWord = false;
        next.resize(26, nullptr);
    }
};

class Trie {
private:
    TrieNode* root;
public:
    Trie() {
        root = new TrieNode();
    }
    
    void insert(string word) {
        TrieNode* cur = root;
        for (char c : word) {
            int pos = c - 'a';
            if (cur -> next[pos] == nullptr) {
                cur -> next[pos] = new TrieNode;
            }
            cur = cur -> next[pos];
        }
        cur -> isWord = true;
        cur -> word = word;
    }
    
    string getLongestWord() {
        queue<TrieNode*> prefix;
        prefix.push(root);
        string result = "";
        while (!prefix.empty()) {
            TrieNode* cur = prefix.front();
            if (cur -> isWord && (cur -> word).size() > result.size()) {
                result = cur -> word;
            }
            for (TrieNode* next : cur -> next) {
                if (next && next -> isWord) {
                    prefix.push(next);
                }
            }
            prefix.pop();
        }
        return result;
    }
};

class Solution {
public:
    string longestWord(vector<string>& words) {
        Trie trie;
        for (string word : words) {
            trie.insert(word);
        }
        return trie.getLongestWord();
    }
};
