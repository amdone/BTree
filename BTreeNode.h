/*
 * BTreeNode.h
 *
 *  Created on: 2019年7月13日
 *      Author: Eichi
 */
#define M 3

#ifndef SRC_BTREENODE_H_
#define SRC_BTREENODE_H_
#include <iostream>
//using namespace std;
template <class T>
struct BTreeNode{
	int rank;
	int keyNum;
	bool leaf;
	T *element;

	BTreeNode **child;

	BTreeNode(){
		rank = 0;
		element = NULL;
		keyNum = 0;
		child = NULL;
		leaf = true;
	}

	BTreeNode(int rank){
		this->rank = rank;
		element = new T[rank];
		keyNum = 0;
		leaf = true;
		child = new BTreeNode*[rank+1];
	}

	BTreeNode(int rank,bool leaf){
		this->rank = rank;
		keyNum = 0;
		this->leaf = leaf;
		element = new T[rank];
		child = new BTreeNode*[rank+1];
	}

	void insertNoFull(T theElement);
	void splitChild(int index,BTreeNode *y);

};




#endif /* SRC_BTREENODE_H_ */





