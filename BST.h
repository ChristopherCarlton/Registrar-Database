#ifndef BST_H
#define BST_H

#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

template <typename T>
class TreeNode{
public:
  TreeNode(T d);
  ~TreeNode();
  TreeNode<T>* left;
  TreeNode<T>* right;
  T data;
};

template <typename T>
TreeNode<T>::TreeNode(T d){
  data = d;
  left = NULL;
  right = NULL;
}

template <typename T>
TreeNode<T>::~TreeNode(){
  //free all the memory
}

template <typename T>
class BST{
public:
  BST();
  ~BST();
  bool contains(T d);
  void insert(T d);
  bool recContains(T d);
  void printInOrder();
  void printInOrderToFile(std::ofstream& ofile); //samith
  void printPostOrder();
  void deleteValue(T d);
  void purgeAllNodes();
  T getMax();
  T getMin();
  T getMedian();
  T returnRecord(T d);
  private:
  TreeNode<T>* root;
  int size;
  bool recContainsHelper(TreeNode<T>* n, T d);
  void printIOHelper(TreeNode<T>* n);
  void printInOrderToFileHelper(TreeNode<T>* n, std::ofstream& ofile); 
  void printPOHelper(TreeNode<T>* n);
  void insertHelper(TreeNode<T>*& n, T& d);
  T getMaxHelper(TreeNode<T>* n);
  T getMinHelper(TreeNode<T>* n);
  TreeNode<T>* getSuccessor(TreeNode<T>* child);
  void findTarget(T key, TreeNode<T>*& target, TreeNode<T>*& parent);
  T returnRecordHelper(TreeNode<T>* n, T d);
  void purgeAllNodesHelper(TreeNode<T>* n);
};

template <typename T>
BST<T>::BST(){
  root = NULL;
  size = 0;
}

template <typename T>
BST<T>::~BST(){
  //free all memory
}

template <typename T>
void BST<T>::printInOrder(){
  printIOHelper(root);
}
template <typename T>
void BST<T>::printIOHelper(TreeNode<T>* n){
  if(n!=NULL){
    printIOHelper(n->left);
    cout << n->data << endl;
    printIOHelper(n->right);
  }
}

template <typename T>
void BST<T>::printPostOrder(){
  printPOHelper(root);
}
template <typename T>
void BST<T>::printPOHelper(TreeNode<T>* n){
  if(n!=NULL){
    printPOHelper(n->left);
    printPOHelper(n->right);
    cout << n->data << endl;
  }
}
//samith
template <typename T>
T BST<T>::returnRecord(T d){
  return returnRecordHelper(root,d);
}

template <typename T>
bool BST<T>::recContains(T d){
  return recContainsHelper(root,d);
}

template <typename T>
bool BST<T>::recContainsHelper(TreeNode<T>* n, T d){
  if(n==NULL){
    return false;
  }
  if(n->data==d){
    return true;
  }
  if(d > n->data){
    return recContainsHelper(n->right,d);
  } else{
    return recContainsHelper(n->left,d);
  }
}

template <typename T>
bool BST<T>::contains(T d){ //no repeated values
  if(root==NULL){
    return false;
  }
  if(root->data==d){
    return true;
  }
  bool found = false;
  TreeNode<T>* current = root;
  while(!found){
    if(d > current->data){
      current = current->right;
    } else{
      current = current->left;
    }
    if(current==NULL){
      found = false;
      break;
    }
    if(current->data==d){
      found = true;
      break;
    }
  }
  return found;
}

template <typename T>
void BST<T>::insert(T d){
  insertHelper(root,d);
}
template <typename T>
void BST<T>::purgeAllNodes() {
  purgeAllNodesHelper(root);
}

template <typename T>
void BST<T>::insertHelper(TreeNode<T>*& n, T& d){
  if(n==NULL){
    n = new TreeNode<T>(d);
  } else if(d < n->data){
    insertHelper(n->left,d);
  } else{
    insertHelper(n->right,d);
  }

}

template <typename T>
T BST<T>::getMax(){ //assume non-empty tree
  return getMaxHelper(root);
}

template <typename T>
T BST<T>::getMaxHelper(TreeNode<T>* n){ //assume non-empty tree
  if(n->right == NULL){
    return n->data;
  } else{
    return getMaxHelper(n->right);
  }
}

template <typename T>
T BST<T>::getMin(){ //assume non-empty tree
  return getMinHelper(root);
}

template <typename T>
T BST<T>::getMinHelper(TreeNode<T>* n){ //assume non-empty tree
  if(n->left == NULL){
    return n->data;
  } else{
    return getMinHelper(n->left);
  }
}

template <typename T> //must be a balanced tree to work
T BST<T>::getMedian(){ //assume non-empty tree
  return root->data;
}
template <typename T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T>* child){
  while(child->left != NULL){
    child = child->left;
  }
  return child;
}
template <typename T>
void BST<T>::findTarget(T key, TreeNode<T>*& target, TreeNode<T>*& parent){
  while(target != NULL && target->data != key){
    parent = target;
    if(key < target->data){
      target = target->left;
    } else{
      target = target->right;
    }
  }
}

template <typename T>
void BST<T>::deleteValue(T d){
  TreeNode<T>* parent = NULL;
  TreeNode<T>* current = NULL;

  current = root;

  findTarget(d,current,parent);
  if(current==NULL){
    return;
  }

  //check if leaf
  if(current->left==NULL && current->right==NULL){
    //leaf is root
    if(current==root){
      root=NULL;
    }else { //not root
      if(current==parent->left){
        parent->left = NULL;
      } else{
        parent->right = NULL;
      }
    } //end case 1
    delete current;
  } else if (current->left!=NULL && current->right!=NULL){
    TreeNode<T>* suc = getSuccessor(current->right);
    T temp = suc->data;
    //cout << suc->data << endl;
    this->deleteValue(suc->data);
    current->data = temp;

  } else{ //only 1 child
    TreeNode<T>* child;
    if(current->left!=NULL){
      child = current->left;
    } else{
      child = current->right;
    }
    if(current==root){
      root = child;
    } else{
      if(current==parent->left){
        parent->left = child;
      } else{
        parent->right = child;
      }
    }
    delete current; //free memory
  }

}
//samith
template <typename T>
T BST<T>::returnRecordHelper(TreeNode<T>* n, T d){
  if(n==NULL){
    return d;
  }
  if(n->data==d){
    return n->data;
  }
  if(d > n->data){
    return returnRecordHelper(n->right,d);
  } else{
    return returnRecordHelper(n->left,d);
  }
}
//samith
//Required to print all node data into file instead of standard output

template <typename T>
void BST<T>::printInOrderToFile(std::ofstream& ofile)
{
	printInOrderToFileHelper(root, ofile);
}

//samith
//Helper function Required to print all node data into file instead of standard output
template <typename T>
void BST<T>::printInOrderToFileHelper(TreeNode<T>* n, std::ofstream& ofile)
{
	//null check
	if (n != 0)
	{
		printInOrderToFileHelper(n->left, ofile);
    ofile << n->data;
		//n -> data.printToFileStudentInfo(ofile);
		printInOrderToFileHelper(n->right, ofile);
	}
}
//samith
// Free up all memory at the nodes 
template <typename T>
void  BST<T>::purgeAllNodesHelper(TreeNode<T>* n)
{
  if (n != 0) {
    purgeAllNodesHelper(n->left);
    //cout << "Freeing up Node..." << endl;
    free(n);
    purgeAllNodesHelper(n->right);
  }
}


#endif
