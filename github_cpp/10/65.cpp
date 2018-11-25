#include <fstream>
#include <iostream>
#include <queue>
#include <string.h>
#include <sys/stat.h>

#define ALPHABET_SIZE 26
#define MAX_WORD_LENGTH 50

struct Trie {
    Trie* children[ALPHABET_SIZE];
    bool isWord;
    bool visited;

    Trie() : isWord(false), visited(false) {
        for (int i = ALPHABET_SIZE - 1; i >= 0; --i) {
            children[i] = NULL;
        }
    }

    void add(char word[]) {
        Trie* node = this;

        int i = 0;
        while (word[i] != '\0') {
            int idx = word[i] - 'a';
            if (node->children[idx] == NULL) {
                node->children[idx] = new Trie();
            }

            node = node->children[idx];
            ++i;
        }

        node->isWord = true;
    }

    Trie* contains(char word[]) {
        Trie* node = this;

        int i = 0;
        while (word[i] != '\0') {
            if (node->children == NULL) {
                return NULL;
            }

            int idx = word[i] - 'a';
            if (node->children[idx] == NULL) {
                return NULL;
            }

            node = node->children[idx];
            ++i;
        }

        return node;
    }
};


Trie trie;
std::queue<char*> queue;
int numVisited = 0;
char* buffer;
int bufferIndex = 0;

void checkWord(Trie* trie, char word[], int wordLen, int startIndex=0) {
    Trie* node = trie->contains(word + startIndex);
    if (node != NULL && node->isWord && !node->visited) {
        node->visited = true;
        numVisited++;

        strcpy(buffer + bufferIndex, word);
        queue.push(buffer + bufferIndex);
        bufferIndex += wordLen + 1;
    }
}

int main(int argc, char* argv[]) {
    struct stat filestatus;
    stat(argv[1], &filestatus);

    buffer = new char[filestatus.st_size + 1];

    std::ifstream wordFile(argv[1]);
    if (wordFile.is_open()) {
        char word[MAX_WORD_LENGTH];

        while (wordFile.good()) {
            wordFile.getline(word, MAX_WORD_LENGTH);
            if (wordFile.gcount() != 0) {
                trie.add(word);
            }
        }
        wordFile.close();
    }

    char rootWord[] = "hello";
    trie.add(rootWord);
    checkWord(&trie, rootWord, strlen(rootWord));

    Trie* node;
    char slate[MAX_WORD_LENGTH + 1];
    while (!queue.empty()) {
        char* word = queue.front();
        queue.pop();

        int len = strlen(word);

        
        char* chars = word;
        node = &trie;
        int i = 0;
        while (word[i] != '\0') {
            char original = chars[i];
            for (char c = 'a'; c < original; ++c) {
                if (node->children[c - 'a'] != NULL) {
                    chars[i] = c;
                    checkWord(node, chars, len, i);
                }

            }
            
            for (char c = original + 1; c <= 'z'; ++c) {
                if (node->children[c - 'a'] != NULL) {
                    chars[i] = c;
                    checkWord(node, chars, len, i);
                }
            }
            chars[i] = original;

            node = node->children[original - 'a'];
            ++i;
        }

        
        chars = slate;
        chars[len + 1] = '\0';
        node = &trie;
        int idx = -2;
        for (i = 0; i <= len; ++i) {
            if (++idx >= 0)
                chars[idx] = word[idx];
            for (int j = i + 1; j <= len; ++j)
                chars[j] = word[j - 1];
            for (char c = 'a'; c <= 'z'; ++c) {
                if (node->children[c - 'a'] != NULL) {
                    chars[i] = c;
                    checkWord(node, chars, len + 1, i);
                }
            }

            node = node->children[word[i] - 'a'];
        }

        
        chars = slate;
        chars[len - 1] = '\0';
        idx = -2;
        for (i = 0; i < len; ++i) {
            if (++idx >= 0)
                chars[idx] = word[idx];
            for (int j = i + 1; j < len; ++j)
                chars[j - 1] = word[j];

            checkWord(&trie, chars, len - 1);
        }
    }

    
    std::cout << numVisited - 1 << std::endl;
    return 0;
}

