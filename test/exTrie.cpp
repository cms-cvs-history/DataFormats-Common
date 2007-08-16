/*
 */

#include "DataFormats/Common/interface/Trie.h"


#include<string>
#include<iostream>



struct Print {
  typedef edm::TrieNode<int> const node;
  void operator()(node & n, std::string const & label) const {
    std::cout << label << " " << n.value() << std::endl;
  }
  
};

int main(int argc, char **argv)
{
  /// trie that associates a integer to strings
  /// 0 is the default value I want to receive when there is no match
  /// in trie
  edm::Trie<int>	trie(0);
  typedef edm::TrieNode<int> Node;
  typedef Node const * pointer; // sigh....
  typedef edm::TrieNodeIter<int> node_iterator;

  char tre[] = {'a','a','a'};
  char quattro[] = {'c','a','a','a'};

  for (int j=0;j<3;j++) {
    tre[2]='a';
    quattro[3]='a';
    for (int i=0;i<10;i++) {
       trie.insert(tre,3,i);
       trie.insert(quattro,4,i);
       tre[2]++;
       quattro[3]++;
    }
    tre[1]++;
    quattro[2]++;
  }

 
  std::cout << "get [aac] " << trie.find("aac", 3) << std::endl;
  std::cout << "get [caae] = " << trie.find("caae", 4) << std::endl;

  trie.setEntry("caag", 4, -2);
  std::cout << "get [caag] = " << trie.find("caag", 4) << std::endl;

  // no match
  std::cout << "get [abcd] = " << trie.find("abcd", 4) << std::endl;
  // no match
  std::cout << "get [ca] = " << trie.find("ca", 2) << std::endl;

  trie.display(std::cout);
  std::cout << std::endl;

  pointer pn = trie.node("ab",2);
  if (pn) pn->display(std::cout,0,' ');
  std::cout << std::endl;

  node_iterator e;
  std::cout << "\n ab iteration" << std::endl;
  for (node_iterator p(trie.node("ab",2)); p!=e; p++)
    std::cout << "ab" << p.label() << " = " << p->value() << std::endl;
 
  std::cout << "\n ab iteration: string" << std::endl;
  for (node_iterator p(trie.node("ab")); p!=e; p++)
    std::cout << "ab" << p.label() << " = " << p->value() << std::endl;

  std::cout << "\ntop iteration"<< std::endl;
  for (node_iterator p(trie.initialNode()); p!=e; p++)
    std::cout << p.label() << " = " << p->value() << std::endl;
  std::cout << std::endl;
	
  Print pr;
  edm::walkTrie(pr,*trie.initialNode());
  std::cout << std::endl;

}
