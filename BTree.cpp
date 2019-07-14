/*
 * BTree.cpp
 *
 *  Created on: 2019年7月13日
 *      Author: Eichi
 */

#include "BTree.h"

template<class K,class E>
BTree<K,E>::BTree(){
	root = NULL;
	treeSize = 0;
	rank = 0;
}

template<class K,class E>
BTree<K,E>::BTree(int rank){
	this->rank = rank;
	root = NULL;
	treeSize = 0;
}


template<class K, class E>
BTree<K,E>::~BTree(){
	//BTreeNode<std::pair<K,E>> *p;

}


template<class K, class E>
bool BTree<K,E>::empty() const {
	return 0==treeSize;
}


template<class K, class E>
int BTree<K,E>::size() const {
	return treeSize;
}


template<class K, class E>
void BTree<K,E>::insert(const std::pair<const K,E>&thePair){
	if(NULL == root){
		root = new BTreeNode<std::pair<K,E>>(rank,true);
		root->element[0] = thePair;
		root->keyNum = 1;

	}
	else if(root->keyNum == rank){
		BTreeNode<std::pair<K,E>> *tmp = new BTreeNode<std::pair<K,E>>(rank,false);
		tmp->child[0] = root;
		tmp->splitChild(0,root);

		if(thePair > tmp->element[0]){
			tmp->child[1]->insertNoFull(thePair);
		}
		else tmp->child[0]->insertNoFull(thePair);

		root = tmp;
	}
	else{
		root->insertNoFull(thePair);
	}
}


template<class T>
void BTreeNode<T>::insertNoFull(T theElement){
	int i = M;

	if(leaf){
		while(0 <= i && theElement < element[i]){
			element[1+i] = element[i];
			--i;
		}
		element[++i] = theElement;
		++keyNum;
	}
	else{
		while(0 <= i && theElement <element[i])--i;

		if(child[i+1].keyNum == M){
			splitChild(i+1,child[i+1]);

			if(theElement > element[i+1]) ++i;
		}
		child[i+1].insertNoFull(theElement);
	}

}


template<class T>
void BTreeNode<T>::splitChild(int index,BTreeNode *fullNode){
	BTreeNode *tmp = new BTreeNode(rank,fullNode->leaf);
	tmp->keyNum = M/2;

	for(int i = 0;i < M/2; i++){
		tmp->element[i] = fullNode->element[i+(M+1)/2];
	}

	if(!fullNode->leaf){
		for(int i = 0;i<(M+1)/2;i++){
			tmp->child[i] = fullNode->child[i+(M+1)/2];
		}
	}

	fullNode->keyNum = M/2;

	for(int i = keyNum;i >= index+1; i--){
		child[i+1] = child[i];
	}

	child[index+1] = tmp;

	for(int i = keyNum - 1;i >= index; i--){
		element[i+1] = element[i];
	}

	element[index] = fullNode->element[M/2];

	keyNum++;

}




