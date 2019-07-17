/*
 * BTree.cpp
 *
 *  Created on: 2019年7月13日
 *      Author: Eichi
 */

#include "BTree.h"
using std::cout;
using std::endl;

template<class K,class E>
BTree<K,E>::BTree(){
	root = NULL;
	treeSize = 0;
	rank = 0;
	pointerCollector = NULL;
}

template<class K,class E>
BTree<K,E>::BTree(int rank){
	if(rank<2)throw std::out_of_range("rank must >= 2!");
	this->rank = rank;
	root = NULL;
	treeSize = 0;
	pointerCollector = new BTreeNode<std::pair<K,E>>(rank);
	for(int i = 0;i<rank;i++)
	pointerCollector->child[i] = pointerCollector;
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
		for(int i = 0;i<rank;i++) {
			root->element[i] = std::pair<K,E>();
			root->child[i] = pointerCollector;
		}
		root->element[0] = thePair;
		root->keyNum = 1;
	}
	else if(root->keyNum == rank-1){
		int i = root->keyNum-1;

//		if(root->child[0]!=this->pointerCollector){
//
//			while(thePair.first < root->element[i].first)--i;
//			if(root->child[i+1]->keyNum == rank-1){
//				root->child[i+1]->insertFull(rank,thePair,pointerCollector,root);
//			}
//			else root->child[i+1]->insertNoFull(rank,thePair,pointerCollector);
//		}


		if(root->child[0]==this->pointerCollector){
			while(thePair.first < root->element[i].first){
				root->element[i+1] = root->element[i];
				--i;
			}
			root->element[i+1]= thePair;
//			int j = 0;
//			if(i>rank/2)j=1;
			BTreeNode<std::pair<K,E>> *tmp = new BTreeNode<std::pair<K,E>>(rank,false);
			for(int i = 0;i<rank;i++) {
				tmp->element[i] = std::pair<K,E>();
				tmp->child[i] = pointerCollector;
			}
			tmp->child[0] = root;
			tmp->splitChild(rank,0,root,pointerCollector);

			root = tmp;
		}
		else
			root->insertNoFull(rank,thePair,pointerCollector);
	}

	else
		root->insertNoFull(rank,thePair,pointerCollector);
	if(root->keyNum == rank){
		BTreeNode<std::pair<K,E>> *newRoot = new BTreeNode<std::pair<K,E>>(rank,false);
					for(int i = 0;i<rank;i++) {
						newRoot->element[i] = std::pair<K,E>();
						newRoot->child[i] = pointerCollector;
					}
					newRoot->child[0] = root;
					newRoot->splitChild(rank,0,root,pointerCollector);

					root = newRoot;
	}
	++treeSize;
}


template<class T>
void BTreeNode<T>::insertNoFull(int rank,T theElement,BTreeNode<T>* pc){
	int i = keyNum-1;

	if(leaf){
		while(0 <= i && theElement.first < element[i].first){
			element[1+i] = element[i];
			--i;
		}
		element[i+1] = theElement;
		++keyNum;
	}
	else{
		while(0 <= i && theElement <element[i])--i;
		BTreeNode<T>* testPointer = child[i+1];
		if(child[i+1] == pc){
			child[i+1] = new BTreeNode<T>(rank,true);
			for(int j = 0;j<rank;j++) testPointer->child[j] = pc;
		}
		if(child[i+1]->keyNum == rank-1){

			int j = child[i+1]->keyNum-1;
			while(theElement.first < child[i+1]->element[j].first){
				child[i+1]->element[j+1] = child[i+1]->element[j];
				--j;
			}
			child[i+1]->element[j+1]= theElement;

			splitChild(rank,i+1,child[i+1],pc);

		}
		else
		child[i+1]->insertNoFull(rank,theElement,pc);

	}

}




template<class T>
void BTreeNode<T>::splitChild(int rank,int index,BTreeNode *fullNode,BTreeNode *pc){
	BTreeNode *tmp = new BTreeNode(rank,fullNode->leaf);
	for(int i = 0;i<rank;i++) {
		tmp->element[i] = T();
		tmp->child[i] = pc;
	}

	tmp->keyNum = (rank-1)/2;

	for(int i = 0;i < (rank-1)/2; i++){
		tmp->element[i] = fullNode->element[i+rank/2+1];
		fullNode->element[i+rank/2+1] = T();
	}

	if(fullNode->keyNum == rank){
		for(int i = 0;i<rank/2+1;i++){
			tmp->child[i] = fullNode->child[i+rank/2+1];
		}
	}

	else if(!fullNode->leaf){
		for(int i = 0;i<rank/2;i++){
			tmp->child[i] = fullNode->child[i+rank/2];
		}
	}



	fullNode->keyNum = rank/2;

	for(int i = keyNum;i >= index+1; i--){
		child[i+1] = child[i];
	}

	child[index+1] = tmp;

	for(int i = keyNum - 1;i >= index; i--){
		element[i+1] = element[i];
	}

	element[index] = fullNode->element[rank/2];
	fullNode->element[rank/2] = T();
	keyNum++;


//	fullNode->keyNum--;
//	for(int j = 0;j < tmp->keyNum; j++){
//		tmp->element[j] = tmp->element[j+1];
//	}
//	keyNum--;

}



template<class T>
void BTreeNode<T>::output(){
	if(leaf){
		for(int i = 0;i<keyNum;i++){
			cout<<element[i]<<" ";
		}
	}
	int i=0;
	for(;i<keyNum;i++){
		if(leaf == false){
			child[i]->output();
			cout<<element[i]<<" ";
		}
	}
	if(leaf == false)child[i]->output();
}


template<class K,class E>
void BTree<K,E>::output(){
	 if (root != NULL) root->output();
	 cout<<endl;
}

template<class K,class E>
void BTree<K,E>::outTest(){

}

template<class K,class E>
void BTree<K,E>::BTree_print(BTreeNode<std::pair<K,E>> *r, BTreeNode<std::pair<K,E>> *pc,int layer)
{
    int i;
    BTreeNode<std::pair<K,E>>* node = r;

    if (node != pc) {

        cout<<"第"<<layer<<"层 , "<<node->keyNum<<"个key: ";

        for (i = 0; i < node->keyNum; ++i) {
           cout<<node->element[i]<<"  ";
        }

        cout<<endl;

        ++layer;
        for (i = 0 ; i <= node->keyNum; i++) {
            if (node->child[i] != pc) {
                BTree_print(node->child[i],pc, layer);
            }
        }
    }
    else {
        cout<<"该树为空树！"<<endl;
    }
}

template<class K,class E>
void BTree<K,E>::print()
{
	BTree_print(root,this->pointerCollector,0);
}

template<class K,class E>
bool operator>(const std::pair<const K,E>& a,std::pair<K,E>& b){
	return a.first > b.first;
}
