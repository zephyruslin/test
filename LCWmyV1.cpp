#include <stdio.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
#include <memory>
#include <time.h>

using namespace std;

struct Trie{
	private:
		struct TrieNode{
			bool isString;
			unordered_map<char, shared_ptr<TrieNode>> cMap;
		};
		shared_ptr<TrieNode> root;
		int wordCounter;
		int topK;
		vector<string> topKLongestWord;
		queue<pair<string, string>> qWord;
		
public:
		unordered_set<string> wordSet;
		Trie(int k = 1){
			root=shared_ptr<TrieNode>(new TrieNode{false});
			wordCounter=0;
			topK = k;
			topKLongestWord.resize(topK);
			for(int i=0;i<topK;i++)
				topKLongestWord[i] = "";
			
			//qWord.resize(0);
		}
		void insert(string &S){
			shared_ptr<TrieNode> p = root;
			for (char &c : S){
				if (p->cMap.find(c)==p->cMap.cend()){
					p->cMap[c] = shared_ptr<TrieNode>(new TrieNode{false});
				}
				p = p->cMap[c];
			}
			if (not p->isString)
				p->isString =true;
		}
		bool isCompoundWord(string &S){
			shared_ptr<TrieNode> p = root;
			for (unsigned int i=0;i<S.length();i++){
				if (p->cMap.find(S[i])!=p->cMap.cend()){
					p = p->cMap[S[i]];
					if (p->isString){
						qWord.push(pair<string, string>(S.substr(0,i),S.substr(i)));
					}
				}
				else
					break;
			}
			//cout << qWord.size() <<endl;
			while(not qWord.empty()){
				pair<string, string> wordPair = qWord.front();
				qWord.pop();
				if (wordSet.find(wordPair.second)!=wordSet.cend() or isCompoundWord(wordPair.second))
					return true;
			}
			return false;
		}
		//binary search to find where the compound word should be inserted.
		void updateLongestWord(string &S){
			int l=0,r=topK-1,m;
			while(l<r){
				m = l+((r-l)>>1);
				if (S.length()<=topKLongestWord[m].length()){
					l = m+1;
				}
				else{
					r = m-1;
				}
			}
			topKLongestWord.insert(topKLongestWord.begin()+m, S);
			topKLongestWord.pop_back();
		}
		void updateCompoundWord(string &S){
			if (isCompoundWord(S)){
				wordCounter++;
				if (S.length()>topKLongestWord[topK-1].length()){
					updateLongestWord(S);
				}
			}
		}
		vector<string> getLongestCompoundWords(){
			return topKLongestWord;
		}
		int getCompoundWordNum(){
			return wordCounter;
		}
};
int main(int argc, char **argv)
{
	clock_t t1,t2;
    t1=clock();
	//get the top k longest compound word.
	int k=2;
	Trie T(k);
	ifstream ifs("C:\\Users\\yul33\\Downloads\\wordsforproblem.txt");
	string word;
	vector<string> wordList;
	while(getline(ifs, word)){
		//Add word to trie
		T.insert(word);
		T.wordSet.emplace(word);
		wordList.push_back(word);
		//cout << word << endl;
	}
	for (int i=0;i<wordList.size();i++){
		T.updateCompoundWord(wordList[i]);
	}
	// get the longest compound words, first ordered by length, then ordered by lexicographicalorder
	vector<string> LCWs = T.getLongestCompoundWords();
	cout << "The longest words made of other words are:";
	for (int i=0;i<k;i++)
		cout << "\n" << LCWs[i];
	cout << endl;
	cout << T.getCompoundWordNum() << endl;
	t2=clock();
    float diff ((float)t2-(float)t1);
    cout<<diff/CLOCKS_PER_SEC <<endl;
	return 0;
}
