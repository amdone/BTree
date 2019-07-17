/*
 * BTreeNode.h
 *
 *  Created on: 2019年7月13日
 *      Author: Eichi
 */

#ifndef SRC_BTREENODE_H_
#define SRC_BTREENODE_H_
#include <iostream>
//using namespace std;
template <class T>
struct BTreeNode{
	int keyNum;
	bool leaf;
	T *element;
	BTreeNode **child;
	BTreeNode *_parent;

	BTreeNode(){
		element = NULL;
		keyNum = 0;
		child = NULL;
		leaf = true;
		_parent = NULL;
	}

	BTreeNode(int rank){
		element = new T[rank];
		keyNum = 0;
		leaf = true;
		child = new BTreeNode*[rank];
		_parent = NULL;
	}

	BTreeNode(int rank,bool leaf){
		keyNum = 0;
		this->leaf = leaf;
		element = new T[rank-1];
		child = new BTreeNode*[rank];
		_parent = NULL;
	}
	std::pair<T,BTreeNode<T>**>* insertFull(int rank,T theElement,BTreeNode * pc,BTreeNode<T>* root);
	void insertNoFull(int rank,T theElement,BTreeNode* pc);
	void splitChild(int rank,int index,BTreeNode *y,BTreeNode *pc);
	void output();

};




#endif /* SRC_BTREENODE_H_ */





