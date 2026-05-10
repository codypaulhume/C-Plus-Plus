#include <iostream>
#include <vector>

using namespace std;

class TrieNode{
    public:
        bool endWord;
        TrieNode* children[26];

        TrieNode(){
            endWord  = false;
            for(int i = 0; i < 26; i++){
                children[i] = nullptr;
            }
        }
};

class Trie{
    private:
        TrieNode* root;
    public:
        Trie(){
            root = new TrieNode();
        }

        void insert(string word){
            TrieNode* temp = root;
            for(auto c : word){
                // Each character is simply ASCII. Subtract each character from the ASCII of 'a' to keep the range from 0 - 25.
                int index = c - 'a';
                // If the character at that index doesn't exist... create a new node at that index.
                if(!temp->children[index]){
                    temp->children[index] = new TrieNode();
                }
                // Iterate to the next node
                temp = temp->children[index];
            }
            temp->endWord = true;
        }

        bool search(string word){
            TrieNode* temp = root;

            for(auto c : word){
                int index = c - 'a';
                // If something exists at the index... iterate to its child.
                if(temp->children[index]){
                    temp = temp->children[index];
                }else{
                    return false;
                }
            }
            if(temp->endWord == true){
                return true;
            }
            return false;
        }

        void dfs(TrieNode* node, string currentWord, vector<string>& returnList){

            // Base case
            if(node->endWord == true){
                // Need "&" in vector parameter to share same vector across recursive calls
                    returnList.push_back(currentWord);
                }

            for(int i = 0; i < 26; i++){
                if(node->children[i]){
                    // Recursion - Pass the child, the word with character, and the vector.
                    dfs(node->children[i], currentWord + char('a' + i), returnList);
                }
                
            }
        }

        vector<string> searchPre(string prefix){
            TrieNode* temp = root;
            vector<string> returnList;

            for(auto c : prefix){
                int index = c - 'a';
                // Iterate to where the prefix ends.
                if(temp->children[index]){
                    temp = temp->children[index];
                }else{
                    return returnList;
                }
            }

            // Depth first search for each word beginning with the prefix
            dfs(temp, prefix, returnList);

            // Return the list
            return returnList;
        }

        void print(vector<string> vector){
            
            for(auto word : vector){
                cout << "- " + word << endl;
            }
        }
};

int main(){
    Trie myTrie;
    myTrie.insert("cat");
    myTrie.insert("catch");
    myTrie.insert("catcher");

    cout << "Autocomplete matches: " << endl;
    myTrie.print(myTrie.searchPre("catc"));
}

// Notes for next time. Figure out printing and pushing back to vector. Its not working. I am currently cout-ing the final word