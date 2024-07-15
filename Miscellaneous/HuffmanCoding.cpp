#include<bits/stdc++.h>
using namespace std;

class Node{
    public:
    char data;
    int freq;
    Node *left, *right;
    Node(char data, int freq){
        this->data = data;
        this->freq = freq;
        left = right = NULL;
    }
};

int uniqueChars(string s) {
    string letters = "";
    for (int i=0; i<s.length(); i++) {
        if (letters.find(s[i]) == string::npos) {
            letters += s[i];
        }
    }
    return letters.length();
}

int** getFreq(string s) {
    int count = uniqueChars(s);
    int** freq = new int*[2];
    freq[0] = new int[count];
    freq[1] = new int[count];
    for (int i=0; i<count; i++) {
        freq[0][i] = 0;
        freq[1][i] = 0;
    }
    string letters = "";
    for (int i=0; i<s.length(); i++) {
        if (letters.find(s[i]) == string::npos) {
            letters += s[i];
            freq[0][letters.find(s[i])] = s[i] - 'A';
            freq[1][letters.find(s[i])]++;
        }
        else {
            freq[1][letters.find(s[i])]++;
        }
    }
    return freq;
}

void sort(int** freq, int count) {
    for(int i=0; i<count; i++) {
        for(int j=0; j<count-i-1; j++) {
            if(freq[1][j] > freq[1][j+1]) {
                swap(freq[0][j], freq[0][j+1]);
                swap(freq[1][j], freq[1][j+1]);
            }
        }
    }
}

void print(int** freq, int count) {
    for(int i=0; i<count; i++) {
        cout << (freq[0][i]) << " " << freq[1][i] << endl;
    }
}

Node* buildHuffmanTree(string s) {
    int count = uniqueChars(s);
    int** freq = getFreq(s);
    sort(freq, count);
    // print(freq, count);
    Node* first = new Node(freq[0][0]+'A', freq[1][0]);
    for (int i=1; i < count; i++) {
        Node* second = new Node(freq[0][i]+'A', freq[1][i]);
        Node* newNode = new Node('$', first->freq + second->freq);
        newNode->left = first;
        newNode->right = second;
        first = newNode;
    }
    return first;
}

void printHuffmanCode(Node* root, string s) {
    if(root->left == NULL && root->right == NULL) {
        cout << root->data << " " << s << endl;
        return;
    }
    printHuffmanCode(root->left, s + "1");
    printHuffmanCode(root->right, s + "0");
}

void huffmanCoding(string s) {
    Node* root = buildHuffmanTree(s);
    printHuffmanCode(root, "");
}
 
int main(){
    cout << "Enter the string: ";
    string s;
    cin >> s;
    huffmanCoding(s);

    return 0;
}
