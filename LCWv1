#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

struct stringpair {
    string full;
    string foundpart;
    stringpair(string afull,string afoundpart):full(afull),foundpart(afoundpart) {}
};


class Node {
public:
    Node() { mContent = ' '; mMarker = false; }
    ~Node() {}
    char content() { return mContent; }
    void setContent(char c) { mContent = c; }
    bool wordMarker() { return mMarker; }
    void setWordMarker() { mMarker = true; }
    Node* findChild(char c);
    void appendChild(Node* child) { mChildren.push_back(child); }
    vector<Node*> children() { return mChildren; }

private:
    char mContent;
    bool mMarker;
    vector<Node*> mChildren;
};

class Trie {
public:
    Trie();
    ~Trie();
    void addWord(string s);
    void deleteWord(string s);
    void fillInitialCWs(Node *node, string currentWord);
    string findLCW();
    void checkRemainingPart(string full, string foundPart);

private:
    Node* root;
    list<string> mLCWStack;
    queue<stringpair*> mProcessingPairs;
    string mLCW;
};

Node* Node::findChild(char c)
{
    for ( int i = 0; i < mChildren.size(); i++ )
    {
        Node* tmp = mChildren.at(i);
        if ( tmp->content() == c )
        {
            return tmp;
        }
    }

    return NULL;
}

Trie::Trie()
{
    root = new Node();
}

Trie::~Trie()
{
    // Free memory
}

void Trie::addWord(string s)
{
    Node* current = root;

    if ( s.length() == 0 )
    {
        current->setWordMarker(); // an empty word
        return;
    }

    for ( int i = 0; i < s.length(); i++ )
    {
        Node* child = current->findChild(s[i]);
        if ( child != NULL )
        {
            current = child;
        }
        else
        {
            Node* tmp = new Node();
            tmp->setContent(s[i]);
            current->appendChild(tmp);
            current = tmp;
        }
        if ( i == s.length() - 1 )
            current->setWordMarker();
    }
}


void Trie::fillInitialCWs(Node *node, string currentWord)
{
    bool validWord = false;
    vector<Node*> children = node->children();
    char content = node->content();
    string newWord = currentWord.append(1,content);
    if ( node->wordMarker() ) {
        validWord = true;
        if (mLCWStack.size() > 0) {
            for (std::list<string>::iterator it = mLCWStack.begin(); it != mLCWStack.end(); it++) {
                mProcessingPairs.push(new stringpair(newWord,*it));
            }
        }

        mLCWStack.push_front(newWord);
    }
    for ( int i = 0; i < children.size(); i++ )
    {
        Node* tmp = children.at(i);
        fillInitialCWs(tmp,newWord);
    }

    if (validWord) {
        mLCWStack.pop_front();
    }

}

void Trie::checkRemainingPart(string full, string foundPart)
{
    string remPart = full.substr(foundPart.length(),full.length() - foundPart.length());
    Node* current = root;
    string currentWord = foundPart;

    for ( int i = 0; i < remPart.length(); i++ )
    {
        Node* tmp = current->findChild(remPart[i]);
        if ( tmp == NULL )
            return;
        currentWord.append(1,remPart[i]);
        if ( tmp->wordMarker() )
            mProcessingPairs.push(new stringpair(full,currentWord));
        current = tmp;
    }

}

string Trie::findLCW()
{
    // traverse the trie and fill the first set of compound words.
    fillInitialCWs(root,"");
    mLCW = "";
    int currentLCWLength = 0;
    while (!mProcessingPairs.empty()) {
        stringpair* it = mProcessingPairs.front();
        mProcessingPairs.pop();
        if (it->foundpart == it->full ) {
            if ( (it->full).length() >  currentLCWLength ) {
                currentLCWLength = (it->full).length();
                mLCW = it->full;
            }
        } else {
            checkRemainingPart(it->full, it->foundpart);
        }
    }
    return mLCW;
}

// Test program
int main()
{
    Trie* trie = new Trie();
	/*
    trie->addWord("hello");
    trie->addWord("balloon");
    trie->addWord("ball");
    trie->addWord("world");
    trie->addWord("helloworld");
    trie->addWord("helloxworld");
    trie->addWord("helloworldyball");
    trie->addWord("helloworldball");
    trie->addWord("helloworldballoon");
    trie->addWord("helloworldballoonxyz");
    trie->addWord("morninghelloworldball");
	*/
	clock_t t1,t2;
    t1=clock();
    //code goes here
	ifstream infile("C:\\Users\\windyue\\Documents\\CodeLite\\LCW\\wordsforproblem.txt");
	string line;
	while (getline(infile, line)){
		//cout << line << endl;
		trie->addWord(line);
	}	
    string LCW = trie->findLCW();
    cout << "Longest Compound World: " << LCW << endl;

    delete trie;
    t2=clock();
    float diff ((float)t2-(float)t1);
    cout<<diff/CLOCKS_PER_SEC <<endl;
    //system ("pause");	
	return 0;
}
