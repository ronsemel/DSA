#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__
#include <iostream>

#define PRINT_KEY_EXISTS_IN_TREE_MSG(key)                                      \
    {                                                                          \
        std::cout << "Key #" << key << " already exists in tree" << std::endl; \
    }

static int max(int n1, int n2)
{
    return n1 > n2 ? n1 : n2;
}

/**                                                                            
 * class AvlTree: A balanced and ranked binary search tree                     
 * @pre 1. assumes T has a copy c'tor and assignment operator                  
 *      2. tree is indexed by int key                                          
 **/
template <class T>
class AvlTree
{
private:
    class TreeNode;
    TreeNode *root;
    /**
     * addNewNodeWithoutBalance: recieves id and val creates a new node and 
     * inserts it into the tree without balancing the tree.
     * @param key - the id of the new node to be created
     * @param val - the value of the new node to be created
     * @return - if the id already exists in the tree nullptr, otherwise, a ptr to the new node
    **/
    TreeNode *addNewNodeWithoutBalance(int key, T &val);

    TreeNode *removeNodeWithouBalance(int key);

    TreeNode *find(int key);
    /**
     * balanceTreeAfterInsertion: recieves a ptr to newly inserted node, balances the tree 
     * from that point upwards.
     * @param node - the newly inserted node from which we start the balance alorithm
    **/
    void balanceTreeAfterInsertion(TreeNode *node);

    void balanceTreeAfterRemoval(TreeNode *to_remove);

    /**
     * calcBalanceFactor: calculates the balance factor of curr node and returns it
     * @param node - the node for which we calculate the balance factor
     * @return the current node's balance factor
    **/
    int calcBalanceFactor(TreeNode *node) const;

    /**
     * leftLeftRoll: performs a left left roll
     * add pic       
    **/
    void leftLeftRoll(TreeNode *node);

    /**
     * leftRightRoll: performs a left left roll
     * add pic
    **/
    void leftRightRoll(TreeNode *node);

    /**
     * rightrightRoll: performs a left left roll
     * add pic
    **/
    void rightRightRoll(TreeNode *node);

    /**
     * rightLeftRoll: performs a left left roll
     * add pic
    **/
    void rightLeftRoll(TreeNode *node);
    //todo update ranks in all of rolls

    void deleteTree(TreeNode *node);

    void removeLeaf(TreeNode *to_remove);

    void removeOneChild(TreeNode *to_remove);

    void removeTwoChildren(TreeNode *to_remove);

    TreeNode *getNextInOrder(TreeNode *node);

public:
    AvlTree();                                    //c'tor
    AvlTree(const AvlTree &) = delete;            //copy c'tor
    AvlTree &operator=(const AvlTree &) = delete; //assignment operator
    ~AvlTree();                                   //d'tor
    void add(int key, T &val);
    void remove(int key); //todo implement
    class iterator;
    iterator begin() const { return iterator(this->root, this->root); }
    iterator end() const { return iterator(this->root, nullptr); }

}; //class AvlTree

template <class T>
AvlTree<T>::AvlTree() : root(nullptr) {}

template <class T>
AvlTree<T>::~AvlTree()
{
    deleteTree(this->root);
}

template <class T>
void AvlTree<T>::deleteTree(AvlTree<T>::TreeNode *node)
{
    if (node == nullptr)
    {
        return;
    }
    AvlTree<T>::TreeNode *left = node->getLeftSon();
    AvlTree<T>::TreeNode *right = node->getRightSon();
    delete node;
    deleteTree(left);
    deleteTree(right);
}

/**
* << operator overload, prints the tree in-order
* @pre: T has a << operator overload
* @return an ostream variable ready to print
**/
template <class T>
std::ostream &operator<<(std::ostream &os, const AvlTree<T> &tree)
{
    int counter = 1;
    for (typename AvlTree<T>::iterator it = tree.begin(); it != tree.end(); ++it)
    {
        os << "Element #:" << counter << " " << *it << '\n';
        ++counter;
    }
    return os;
}

template <class T>
void AvlTree<T>::add(int key, T &val)
{
    /*add to tree the new node without balancing it*/
    AvlTree<T>::TreeNode *new_node = this->addNewNodeWithoutBalance(key, val);
    /*if new_node = nullptr than key already exists, print message and return*/
    if (new_node == nullptr)
    {
        PRINT_KEY_EXISTS_IN_TREE_MSG(key);
        return;
    }
    /*otherwise balance tree*/
    this->balanceTreeAfterInsertion(new_node);
}

template <class T>
void AvlTree<T>::remove(int key)
{
    AvlTree<T>::TreeNode *to_remove = this->find(key);
    /*if key wasn't found return nullptr*/
    if (to_remove == nullptr)
    {
        return;
    }
    /*if the node to remove is a leaf then remove it according to leaf protocol*/
    if (to_remove->getLeftSon() == nullptr && to_remove->getRightSon() == nullptr)
    {
        removeLeaf(to_remove);
    }
    /*if the node to remove has only one child remove it according to one child protocol*/
    else if ((to_remove->getLeftSon() == nullptr && to_remove->getRightSon() != nullptr) ||
             (to_remove->getLeftSon() != nullptr && to_remove->getRightSon() == nullptr))
    {
        removeOneChild(to_remove);
    }
    /*if the node to remove has two children then remove it according to two children protocol*/
    else
    {
        removeTwoChildren(to_remove);
    }
}

template <class T>
void AvlTree<T>::removeLeaf(AvlTree<T>::TreeNode *to_remove)
{
    /*edge case, if tree has only one node*/
    if (to_remove == this->root)
    {
        delete root;
        this->root = nullptr;
        return;
    }

    /*save the parent of the node to be removed*/
    AvlTree<T>::TreeNode *to_remove_parent = to_remove->getParent();
    /*if to_remove is left child of parent, set the left child to null*/
    if (to_remove_parent->getLeftSon() == to_remove)
    {
        to_remove_parent->setLeftSon(nullptr);
    }
    /*if to_remove is right child of parent, set right child to null*/
    else
    {
        to_remove_parent->setRightSon(nullptr);
    }
    /*remove the node*/
    delete to_remove;
    /*balance the tree from the parent upwards*/
    balanceTreeAfterRemoval(to_remove_parent); //todo check if this is what i need to send
}

template <class T>
void AvlTree<T>::removeOneChild(AvlTree<T>::TreeNode *to_remove)
{
    /*find the only child of the node to_remove*/
    AvlTree<T>::TreeNode *child = nullptr;
    if (to_remove->getLeftSon() != nullptr)
    {
        child = to_remove->getLeftSon();
    }
    else
    {
        child = to_remove->getRightSon();
    }

    /*swap the node to remove and its child, then remove node*/
    child->setParent(to_remove->getParent());
    /*if to_remove is the root, reset the root to child*/
    if (to_remove->getParent() == nullptr)
    {
        this->root = child;
    }
    /*otherwise, set the child to be the son of to_remove's parent*/
    else
    {
        /*if to remove is the left son then update the parent's left son*/
        if (to_remove->getParent()->getLeftSon() == to_remove)
        {
            to_remove->getParent()->setLeftSon(child);
        }
        /*if to remove is the right son then updated the parent's right son*/
        else
        {
            to_remove->getParent()->setRightSon(child);
        }
    }

    delete to_remove;
    balanceTreeAfterRemoval(child->getParent());
}

template <class T>
void AvlTree<T>::removeTwoChildren(AvlTree<T>::TreeNode *to_remove)
{
    /*get the next in order node of to_remove, there has to be one because to_remove has a right child*/
    AvlTree<T>::TreeNode *next_in_order = getNextInOrder(to_remove);

    /*swap the to_remove and next_in_order*/
    to_remove->setKey(next_in_order->getKey());
    to_remove->setVal(next_in_order->getVal());
    /*remove next_in_order from tree*/
    if (next_in_order->getLeftSon() == nullptr && next_in_order->getRightSon() == nullptr)
    {
        removeLeaf(next_in_order);
    }
    else
    {
        removeOneChild(next_in_order);
    }
}

template <class T>
typename AvlTree<T>::TreeNode *AvlTree<T>::getNextInOrder(AvlTree<T>::TreeNode *node)
{
    /*if the current node's right son isn't null the next in order is one to the right and then all the way to the left*/
    if (node->getRightSon() != nullptr)
    {
        /*go one right*/
        node = node->getRightSon();
        /*go all the way right*/
        while (node->getLeftSon() != nullptr)
        {
            node = node->getLeftSon();
        }
    }
    /*if current node's right son is null, next in order is up until we reach a parent who's left son is the previous node*/
    else
    {
        /* go up until the current node is his parent's left child*/
        AvlTree<T>::TreeNode *parent = node->getParent();
        while (parent != nullptr && parent->getRightSon() == node)
        {
            node = parent;
            parent = parent->getParent();
        }
        node = parent;
    }
    return node;
}

template <class T>
void AvlTree<T>::balanceTreeAfterRemoval(AvlTree<T>::TreeNode *node)
{
    /*run post removal balance algorithm*/
    while (node != nullptr)
    {
        /*update the current node's height*/
        int left_height = node->getLeftSon() == nullptr ? -1 : node->getLeftSon()->getHeight();
        int right_height = node->getRightSon() == nullptr ? -1 : node->getRightSon()->getHeight();
        node->setHeight(max(left_height, right_height) + 1);
        /*calculate the current node's balance factor*/
        int balance_factor = calcBalanceFactor(node);
        /*store the prev height for later calc*/
        int prev_height = node->getHeight();
        bool is_node_a_right_child = false;
        if (true)
        {
            if (node->getParent()->getRightSon() == node)
            {
                is_node_a_right_child = true;
            }
        }
        /*if balance factor = 2, perform a left type roll*/
        if (balance_factor == 2)
        {
            /*calculate the left son's balance factor and perform the correct roll according to result*/
            int left_balance_factor = calcBalanceFactor(node->getLeftSon());
            if (left_balance_factor >= 0)
            {
                leftLeftRoll(node);
            }
            else if (left_balance_factor == -1)
            {
                leftRightRoll(node);
            }
        }
        /*if balance factor = -2, perform a right type roll*/
        else if (balance_factor == -2)
        {
            /*calculate the right son's balance factor and perform the correct roll according to result*/
            int right_balance_factor = calcBalanceFactor(node->getRightSon());
            if (right_balance_factor <= 0)
            {
                rightRightRoll(node);
            }
            else if (right_balance_factor == 1)
            {
                rightLeftRoll(node);
            }
        }
        /*if node is root than we can't go higher*/
        if (node == this->root)
        {
            return;
        }
        /*if prev height of sub tree is equal to curr height of sub tree than the tree is balanced*/
        if (is_node_a_right_child)
        {
            if (prev_height == node->getParent()->getRightSon()->getHeight())
            {
                return;
            }
        }
        else
        {
            if (prev_height == node->getParent()->getLeftSon()->getHeight())
            {
                return;
            }
        }
        node = node->getParent();
    }
}

template <class T>
typename AvlTree<T>::TreeNode *AvlTree<T>::find(int key) //todo check that works
{
    AvlTree<T>::TreeNode *it = this->root;
    while (true)
    {
        /*check if need to go right*/
        if (it->getKey() < key)
        {
            /*if need to go right and right son  is nullptr, key doesn't exist in tree*/
            if (it->getRightSon() == nullptr)
            {
                return nullptr;
            }
            /*otherwise go right*/
            else
            {
                it = it->getRightSon();
            }
        }
        /*check if need to go left*/
        else if (it->getKey() > key)
        {
            /*if need to go left and left son  is nullptr, key doesn't exist in tree*/
            if (it->getLeftSon() == nullptr)
            {
                return nullptr;
            }
            /*otherwise go left*/
            else
            {
                it = it->getLeftSon();
            }
        }
        //if we got here than key already exists in tree, return nullptr
        else
        {
            return it;
        }
    }
    return nullptr;
}

template <class T>
typename AvlTree<T>::TreeNode *AvlTree<T>::addNewNodeWithoutBalance(int key, T &val)
{
    /*if tree is empty create new node as the root*/
    if (this->root == nullptr)
    {
        this->root = new TreeNode(key, val);
        return this->root;
    }
    /*if tree isn't empty than iterate over the tree*/
    AvlTree<T>::TreeNode *it = this->root;
    while (true)
    {
        /*check if need to go right*/
        if (it->getKey() < key)
        {
            /*if need to go right and right son  is nullptr, put new node as right son*/
            if (it->getRightSon() == nullptr)
            {
                TreeNode *new_node = new TreeNode(key, val);
                it->setRightSon(new_node);
                new_node->setParent(it);
                return new_node;
            }
            /*otherwise go right*/
            else
            {
                it = it->getRightSon();
            }
        }
        /*check if need to go left*/
        else if (it->getKey() > key)
        {
            /*if need to go left and left son  is nullptr, put new node as left son*/
            if (it->getLeftSon() == nullptr)
            {
                TreeNode *new_node = new TreeNode(key, val);
                it->setLeftSon(new_node);
                new_node->setParent(it);
                return new_node;
            }
            /*otherwise go left*/
            else
            {
                it = it->getLeftSon();
            }
        }
        //if we got here than key already exists in tree, return nullptr
        else
        {
            return nullptr;
        }
    }
}

template <class T>
void AvlTree<T>::balanceTreeAfterInsertion(AvlTree<T>::TreeNode *node)
{
    while (node != this->root)
    {
        /*if the parent height >= current node height + 1 than the tree is balanced, return*/
        if (node->getParent()->getHeight() >= node->getHeight() + 1)
        {
            return;
        }
        /*update the node's parent height*/
        node->getParent()->setHeight(node->getHeight() + 1);
        /*calculate the parents balance factor*/
        int balance_factor = calcBalanceFactor(node->getParent());
        /*if parents balance factor = 2 perform a left type roll*/
        if (balance_factor == 2)
        {
            /*calculate the left son's balance factor and perform the correct roll according to result*/
            int left_balance_factor = calcBalanceFactor(node->getParent()->getLeftSon());
            if (left_balance_factor >= 0)
            {
                leftLeftRoll(node->getParent());
            }
            else if (left_balance_factor == -1)
            {
                leftRightRoll(node->getParent());
            }
            /*after roll the tree is balanced so return*/
            return;
        }
        /*if parents balance factor = -2 perform a right type roll*/
        else if (balance_factor == -2)
        {
            /*calculate the right son's balance factor and perform the correct roll according to result*/
            int right_balance_factor = calcBalanceFactor(node->getParent()->getRightSon());
            if (right_balance_factor <= 0)
            {
                rightRightRoll(node->getParent());
            }
            else if (right_balance_factor == 1)
            {
                rightLeftRoll(node->getParent());
            }
            /*after roll the tree is balanced so return*/
            return;
        }
        else
        {
            node = node->getParent();
        }
    }
}

template <class T>
int AvlTree<T>::calcBalanceFactor(AvlTree<T>::TreeNode *node) const
{
    if (node == nullptr)
    {
        return 0;
    }
    int left_height = node->getLeftSon() == nullptr ? 0 : node->getLeftSon()->getHeight() + 1;
    int right_height = node->getRightSon() == nullptr ? 0 : node->getRightSon()->getHeight() + 1;
    return left_height - right_height;
}

template <class T>
void AvlTree<T>::leftLeftRoll(AvlTree<T>::TreeNode *node)
{
    AvlTree<T>::TreeNode *B = node;
    AvlTree<T>::TreeNode *B_parent = B->getParent();  //can be null
    AvlTree<T>::TreeNode *B_right = B->getRightSon(); //can be null
    AvlTree<T>::TreeNode *A = B->getLeftSon();
    AvlTree<T>::TreeNode *A_right = A->getRightSon(); //can be null

    A->setParent(B_parent);
    A->setRightSon(B);
    B->setParent(A);
    B->setLeftSon(A_right);
    /*if A's right son isn't null then reset its parent to B*/
    if (A_right != nullptr)
    {
        A_right->setParent(B);
    }
    /*if B's parent isn't null than reset it's right or left son to A*/
    if (B_parent != nullptr)
    {
        /*check if need to reset right son*/
        if (B_parent->getRightSon() == B)
        {
            B_parent->setRightSon(A);
        }
        /*check if need to reset left son*/
        else if (B_parent->getLeftSon() == B)
        {
            B_parent->setLeftSon(A);
        }
    }
    /*if B is root than we need to update root to A*/
    if (this->root == B)
    {
        this->root = A;
    }
    /*update heights*/
    int height_a_right = A_right == nullptr ? -1 : A_right->getHeight();
    int height_b_right = B_right == nullptr ? -1 : B_right->getHeight();
    B->setHeight(max(height_a_right, height_b_right) + 1);
    A->setHeight(max(B->getHeight(), A->getLeftSon()->getHeight()) + 1);
}

template <class T>
void AvlTree<T>::leftRightRoll(AvlTree<T>::TreeNode *node)
{
    AvlTree<T>::TreeNode *C = node;
    AvlTree<T>::TreeNode *C_parent = C->getParent();  //can be null
    AvlTree<T>::TreeNode *C_right = C->getRightSon(); //can be null
    AvlTree<T>::TreeNode *A = C->getLeftSon();
    AvlTree<T>::TreeNode *A_left = A->getLeftSon(); //can be null
    AvlTree<T>::TreeNode *B = A->getRightSon();
    AvlTree<T>::TreeNode *B_left = B->getLeftSon();   //can be null
    AvlTree<T>::TreeNode *B_right = B->getRightSon(); //can be null

    /*update B's pointers*/
    B->setLeftSon(A);
    B->setRightSon(C);
    B->setParent(C_parent);
    /*if C's parent isn't null than reset it's right or left son to B*/
    if (C_parent != nullptr)
    {
        /*check if need to reset right son*/
        if (C_parent->getRightSon() == C)
        {
            C_parent->setRightSon(B);
        }
        /*check if need to reset left son*/
        else if (C_parent->getLeftSon() == C)
        {
            C_parent->setLeftSon(B);
        }
    }
    /*update A's pointers*/
    A->setParent(B);
    A->setRightSon(B_left);
    /*if B's left son isn't null update its parent to A*/
    if (B_left != nullptr)
    {
        B_left->setParent(A);
    }
    /*update C's pointers*/
    C->setParent(B);
    C->setLeftSon(B_right);
    /*if B's right son isn't null udpate its parent to C*/
    if (B_right != nullptr)
    {
        B_right->setParent(C);
    }
    /*if C is root than we need to update root to B*/
    if (this->root == C)
    {
        this->root = B;
    }
    /*update heights*/
    int height_b_right = B_right == nullptr ? -1 : B_right->getHeight();
    int height_c_right = C_right == nullptr ? -1 : C_right->getHeight();
    C->setHeight(max(height_b_right, height_c_right) + 1);

    int height_a_left = A_left == nullptr ? -1 : A_left->getHeight();
    int height_b_left = B_left == nullptr ? -1 : B_left->getHeight();
    A->setHeight(max(height_a_left, height_b_left) + 1);

    B->setHeight(max(A->getHeight(), C->getHeight()) + 1);
}

template <class T>
void AvlTree<T>::rightRightRoll(AvlTree<T>::TreeNode *node)
{
    AvlTree<T>::TreeNode *B = node;
    AvlTree<T>::TreeNode *B_parent = B->getParent(); //can be null
    AvlTree<T>::TreeNode *B_left = B->getLeftSon();
    AvlTree<T>::TreeNode *A = B->getRightSon();
    AvlTree<T>::TreeNode *A_left = A->getLeftSon(); //can be null

    A->setParent(B_parent);
    A->setLeftSon(B);
    B->setParent(A);
    B->setRightSon(A_left);
    /*if A's left son isn't null then reset its parent to B*/
    if (A_left != nullptr)
    {
        A_left->setParent(B);
    }
    /*if B's parent isn't null than reset it's right or left son to A*/
    if (B_parent != nullptr)
    {
        /*check if need to reset right son*/
        if (B_parent->getRightSon() == B)
        {
            B_parent->setRightSon(A);
        }
        /*check if need to reset left son*/
        else if (B_parent->getLeftSon() == B)
        {
            B_parent->setLeftSon(A);
        }
    }
    /*if B is root than we need to update root to A*/
    if (this->root == B)
    {
        this->root = A;
    }
    /*update heights*/
    int height_a_left = A_left == nullptr ? -1 : A_left->getHeight();
    int height_b_left = B_left == nullptr ? -1 : B_left->getHeight();
    B->setHeight(max(height_a_left, height_b_left) + 1);
    A->setHeight(max(B->getHeight(), A->getRightSon()->getHeight()) + 1);
}

template <class T>
void AvlTree<T>::rightLeftRoll(AvlTree<T>::TreeNode *node)
{
    AvlTree<T>::TreeNode *C = node;
    AvlTree<T>::TreeNode *C_parent = C->getParent(); //can be null
    AvlTree<T>::TreeNode *C_left = C->getLeftSon();  //can be null
    AvlTree<T>::TreeNode *A = C->getRightSon();
    AvlTree<T>::TreeNode *A_right = A->getRightSon(); //can be null
    AvlTree<T>::TreeNode *B = A->getLeftSon();
    AvlTree<T>::TreeNode *B_left = B->getLeftSon();   //can be null
    AvlTree<T>::TreeNode *B_right = B->getRightSon(); //can be null

    /*update B's pointers*/
    B->setLeftSon(C);
    B->setRightSon(A);
    B->setParent(C_parent);
    /*if C's parent isn't null than reset it's right or left son to B*/
    if (C_parent != nullptr)
    {
        /*check if need to reset right son*/
        if (C_parent->getRightSon() == C)
        {
            C_parent->setRightSon(B);
        }
        /*check if need to reset left son*/
        else if (C_parent->getLeftSon() == C)
        {
            C_parent->setLeftSon(B);
        }
    }
    /*update A's pointers*/
    A->setParent(B);
    A->setLeftSon(B_right);
    /*if B's right son isn't null update its parent to A*/
    if (B_right != nullptr)
    {
        B_right->setParent(A);
    }
    /*update C's pointers*/
    C->setParent(B);
    C->setRightSon(B_left);
    /*if B's left son isn't null udpate its parent to C*/
    if (B_left != nullptr)
    {
        B_left->setParent(C);
    }
    /*if C is root than we need to update root to B*/
    if (this->root == C)
    {
        this->root = B;
    }
    /*update heights*/
    int height_b_left = B_left == nullptr ? -1 : B_left->getHeight();
    int height_c_left = C_left == nullptr ? -1 : C_left->getHeight();
    C->setHeight(max(height_b_left, height_c_left) + 1);

    int height_a_right = A_right == nullptr ? -1 : A_right->getHeight();
    int height_b_right = B_right == nullptr ? -1 : B_right->getHeight();
    A->setHeight(max(height_a_right, height_b_right) + 1);

    B->setHeight(max(A->getHeight(), C->getHeight()) + 1);
}

/*****************class AvlTree<T>::TreeNode Implementation******************
****************************************************************************/
template <class T>
class AvlTree<T>::TreeNode
{
private:
    int key;
    int rank;
    T val;
    int height;
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;

public:
    TreeNode(int key, T &data);                     //c'tor
    TreeNode(const TreeNode &) = delete;            //copy c'tor
    TreeNode &operator=(const TreeNode &) = delete; //assignment operator
    ~TreeNode() = default;                          //d'tor
    int getKey();
    void setKey(int new_key);
    T &getVal();
    void setVal(T &new_val);
    int getRank();
    void setRank(int new_rank);
    int getHeight();
    void setHeight(int new_height);
    TreeNode *getLeftSon();
    TreeNode *getRightSon();
    TreeNode *getParent();
    void setLeftSon(TreeNode *node);
    void setRightSon(TreeNode *node);
    void setParent(TreeNode *node);

}; //class AvlTree<T>::TreeNode

template <class T>
AvlTree<T>::TreeNode::TreeNode(int key, T &val) : key(key), rank(0), height(0), val(val),
                                                  left(nullptr), right(nullptr), parent(nullptr) {}

template <class T>
int AvlTree<T>::TreeNode::getKey()
{
    return this->key;
}

template <class T>
void AvlTree<T>::TreeNode::setKey(int new_key)
{
    this->key = new_key;
}

template <class T>
T &AvlTree<T>::TreeNode::getVal()
{
    return this->val;
}

template <class T>
void AvlTree<T>::TreeNode::setVal(T &new_val)
{
    this->val = new_val;
}

template <class T>
int AvlTree<T>::TreeNode::getRank()
{
    return this->rank;
}

template <class T>
void AvlTree<T>::TreeNode::setRank(int new_rank)
{
    this->rank = new_rank;
}

template <class T>
int AvlTree<T>::TreeNode::getHeight()
{
    return this->height;
}

template <class T>
void AvlTree<T>::TreeNode::setHeight(int new_height)
{
    this->height = new_height;
}

template <class T>
typename AvlTree<T>::TreeNode *AvlTree<T>::TreeNode::getLeftSon()
{
    return this->left;
}

template <class T>
typename AvlTree<T>::TreeNode *AvlTree<T>::TreeNode::getRightSon()
{
    return this->right;
}

template <class T>
typename AvlTree<T>::TreeNode *AvlTree<T>::TreeNode::getParent()
{
    return this->parent;
}

template <class T>
void AvlTree<T>::TreeNode::setLeftSon(AvlTree<T>::TreeNode *node)
{
    this->left = node;
}

template <class T>
void AvlTree<T>::TreeNode::setRightSon(AvlTree<T>::TreeNode *node)
{
    this->right = node;
}

template <class T>
void AvlTree<T>::TreeNode::setParent(AvlTree<T>::TreeNode *node)
{
    this->parent = node;
}

/*****************class AvlTree<T>::iterator Implementation******************
****************************************************************************/

template <class T>
class AvlTree<T>::iterator
{
private:
    AvlTree<T>::TreeNode *root;
    AvlTree<T>::TreeNode *curr_node;

public:
    iterator(AvlTree<T>::TreeNode *root, AvlTree<T>::TreeNode *curr_node);
    iterator(const iterator &it) = default;
    iterator &operator=(const iterator &it) = default;

    T &operator*();
    iterator &operator++();    //prefix (++it)
    iterator &operator++(int); //postfix (it++)
    bool operator==(const iterator &it) const;
    bool operator!=(const iterator &it) const;

}; //class AvlTree<T>::iterator

template <class T>
AvlTree<T>::iterator::iterator(AvlTree<T>::TreeNode *root, AvlTree<T>::TreeNode *curr_node) : root(root), curr_node(curr_node)
{
    if (curr_node != nullptr)
    {
        while (this->curr_node->getLeftSon() != nullptr)
        {
            this->curr_node = this->curr_node->getLeftSon();
        }
    }
}

template <class T>
T &AvlTree<T>::iterator::operator*()
{
    return this->curr_node->getVal();
}

template <class T>
typename AvlTree<T>::iterator &AvlTree<T>::iterator::operator++()//todo use nextInOrder function to reduce code duplication
{
    /*if iterator is already at the end do nothing*/
    if (this->curr_node == nullptr && this->root == nullptr)
    {
        return *this;
    }

    /*if the current node's right son isn't null the next in order is one to the right and then all the way to the left*/
    if (this->curr_node->getRightSon() != nullptr)
    {
        /*go one right*/
        this->curr_node = this->curr_node->getRightSon();
        /*go all the way right*/
        while (this->curr_node->getLeftSon() != nullptr)
        {
            curr_node = curr_node->getLeftSon();
        }
    }
    /*if current node's right son is null, next in order is up until we reach a parent who's left son is the previous node*/
    else
    {
        /* go up until the current node is his parent's left child*/
        AvlTree<T>::TreeNode *parent = this->curr_node->getParent();
        while (parent != nullptr && parent->getRightSon() == curr_node)
        {
            curr_node = parent;
            parent = parent->getParent();
        }
        this->curr_node = parent;
    }
    return *this;
}

template <class T>
typename AvlTree<T>::iterator &AvlTree<T>::iterator::operator++(int)
{
    AvlTree<T>::iterator result = *this;
    ++(*this);
    return result;
}

template <class T>
bool AvlTree<T>::iterator::operator==(const AvlTree<T>::iterator &it) const
{
    return this->root == it.root && this->curr_node == it.curr_node;
}

template <class T>
bool AvlTree<T>::iterator::operator!=(const AvlTree<T>::iterator &it) const
{
    return !(*this == it);
}

#endif //__AVL_TREE_H__