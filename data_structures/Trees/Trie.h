#ifndef __TRIE_H__
#define __TRIE_H__
#include <string>
#include <unordered_map>
#include <stack>
#define END_OF_WORD '$'
class Trie
{
private:
    class TrieNode;
    TrieNode *root;
    void removeRemainingBranch(TrieNode* node,TrieNode* prev_node,const char c);
    void deleteTrieTree(TrieNode* to_remove);

public:
    //static const char END_OF_WORD = '$';
    Trie();
    ~Trie();                                    //todo need to implement
    Trie(const Trie &trie) = delete;            //todo maybe implement in future
    Trie &operator=(const Trie &trie) = delete; //todo maybe implement in future
    void insert(const std::string &s);
    bool find(const std::string &s) const;
    void remove(const std::string &s);
}; //class Trie

class Trie::TrieNode
{
public:
    std::unordered_map<char, TrieNode *> letters;
    int rank;
    TrieNode() : letters(), rank(0) {}
    ~TrieNode() = default;
}; //class Trie::TrieNode

Trie::Trie() : root(nullptr) {}

Trie::~Trie()
{
    deleteTrieTree(root);
    root = nullptr;
}

void Trie::deleteTrieTree(Trie::TrieNode* to_remove)
{
    if(to_remove==nullptr)
    {
        return;
    }
    for(std::unordered_map<char,TrieNode*>::iterator it = to_remove->letters.begin();it!=to_remove->letters.end();++it)
    {
        deleteTrieTree(it->second);
    }
    delete to_remove;
}

void Trie::insert(const std::string& s)
{
    if (this->root == nullptr)
    {
        this->root = new TrieNode();
    }
    TrieNode *node = this->root;
    /*iterate over string to be inserted*/
    int len = s.length();
    for (int i = 0; i < len; ++i)
    {
        /*find if current letter in string is already inserted in the node of tree*/
        std::unordered_map<char, TrieNode *>::iterator search = node->letters.find(s[i]);
        /*if current letter wasn't inserted, create a new node and insert it*/
        if (search == node->letters.end())
        {
            node->letters.insert(std::make_pair(s[i], new TrieNode()));
        }
        ++(node->rank);
        /*continue to next node*/
        node = node->letters.find(s[i])->second;
    }
    /* add the END_OF_WORD symbol at the end*/
    if (node->letters.find(END_OF_WORD) == node->letters.end())
    {
        node->letters.insert(std::make_pair(END_OF_WORD, new TrieNode()));
    }
    ++(node->rank);
}

bool Trie::find(const std::string &s) const
{
    if (this->root == nullptr)
    {
        return false;
    }
    TrieNode *node = this->root;
    /*iterate over string to be searched*/
    int len = s.length();
    for (int i = 0; i < len; ++i)
    {
        std::unordered_map<char, TrieNode *>::iterator search = node->letters.find(s[i]);
        if (search == node->letters.end())
        {
            return false;
        }
        node = search->second;
    }
    if (node->letters.find(END_OF_WORD) == node->letters.end())
    {
        return false;
    }
    return true;
}

void Trie::remove(const std::string &s)
{
    if (this->root == nullptr)
    {
        return;
    }
    Trie::TrieNode *node = this->root;
    Trie::TrieNode* prev_node = nullptr;
    /*iterate over string to be searched*/
    int len = s.length();
    for (int i = 0; i < len; ++i)
    {
        std::unordered_map<char, TrieNode *>::iterator search = node->letters.find(s[i]);
        if (search == node->letters.end())
        {
            return;
        }
        --(node->rank);
        if (node->rank == 0)
        {
            this->removeRemainingBranch(node,prev_node,s[i-1]);
            break;
        }
        else
        {
            prev_node = node;
            node = search->second;
        }
    }
}

void Trie::removeRemainingBranch(Trie::TrieNode* node, Trie::TrieNode* prev_node,char c)
{
    prev_node->letters.erase(c);
    deleteTrieTree(node);
}


#endif //__TRIE_H__