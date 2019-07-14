/*
 * BTreeNode.h
 *
 *  Created on: 2019Äê7ÔÂ13ÈÕ
 *      Author: Eichi
 */
#define M 3

#ifndef SRC_BTREENODE_H_
#define SRC_BTREENODE_H_
#include <iostream>
//using namespace std;
template <class T>
struct BTreeNode{
	int keyNum;
	bool leaf;
	T element[M];

	BTreeNode *child[M+1];

	BTreeNode() :element(T()){
		keyNum = 0;
		child = NULL;
		leaf = true;
	}

	void insertNoFull(T theElement);
	void splitChild(int index,BTreeNode *y);

};




#endif /* SRC_BTREENODE_H_ */





