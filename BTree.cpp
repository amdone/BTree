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
		root->insertNoFull(rank,thePair,pointerCollector);
	}
	else
		root->insertNoFull(rank,thePair,pointerCollector);
	++treeSize;
}


template<class T>
std::pair<T,BTreeNode<T>**>* BTreeNode<T>::insertFull(int rank,T theElement,BTreeNode<T>* pc,BTreeNode<T> * root){
	BTreeNode<T>* r = new BTreeNode<T>(rank,true);

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

	if(!fullNode->leaf){
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

template<class K,class E>
int BTree<K,E>::SearchNode(BTreeNode<std::pair<K,E>> *r,K& k){
	int i = r->keyNum-1;
	if(k > r->element[i].first)
		return r->keyNum;
	while(i > 0)
	{
		if(k == r->element[i].first)
			return -1;
		else
			if(k > r->element[i-1].first)
				return i;
		--i;
	}
	return 0;
}


template<class K,class E>
E BTree<K,E>::SearchTree(BTreeNode<std::pair<K,E>> *r,K& theKey){
	while(r != pointerCollector)
	{
		int found = 0;
		found = SearchNode(r,theKey);
		if(found == -1)
			return r->element[found].first;
		else
			SearchTree(r->child[found],theKey);
	}
	return -99999;
}


template<class K,class E>
E BTree<K,E>::find(K theKey) {
	BTreeNode<std::pair<K, E> > *p = this->root;

	return SearchTree(p,theKey);
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
	 cout<<"element[0]-> "<<root->element[0]<<endl;
	 cout<<"element[1]-> "<<root->element[1]<<endl;
	 cout<<"element[2]-> "<<root->element[2]<<endl;
//	 cout<<"child[0]->0-> "<<root->child[0]->element[0]<<endl;
//	 cout<<"child[0]->1-> "<<root->child[0]->element[1]<<endl;
//	 cout<<"child[0]->2-> "<<root->child[0]->element[2]<<endl;
//	 cout<<"child[1]->0-> "<<root->child[1]->element[0]<<endl;
//	 cout<<"child[1]->1-> "<<root->child[1]->element[1]<<endl;
//	 cout<<"child[1]->2-> "<<root->child[1]->element[2]<<endl;
//	 cout<<"child[2]->0-> "<<root->child[2]->element[0]<<endl;
//	 cout<<"child[2]->1-> "<<root->child[2]->element[1]<<endl;
//	 cout<<"child[2]->2-> "<<root->child[2]->element[2]<<endl;
//	 cout<<"child[3]->0-> "<<root->child[3]->element[0]<<endl;
//	 cout<<"child[3]->1-> "<<root->child[3]->element[1]<<endl;
//	 cout<<"child[3]->2-> "<<root->child[3]->element[2]<<endl;
}

template<class K,class E>
void BTree<K,E>::BTree_print(BTreeNode<std::pair<K,E>> *r, BTreeNode<std::pair<K,E>> *pc,int layer)
{
    int i;
    BTreeNode<std::pair<K,E>>* node = r;

    if (node != pc) {
        printf("第 %d 层， %d node : ", layer, node->keyNum);

        //打印出结点中的全部元素，方便调试查看keyNum之后的元素是否为0(即是否存在垃圾数据)；而不是keyNum个元素。
        for (i = 0; i < node->keyNum; ++i) {
        //for (i = 0; i < node->keyNum; ++i) {
           cout<<node->element[i].first<<" ";
        }

        printf("\n");

        ++layer;
        for (i = 0 ; i <= node->keyNum; i++) {
            if (node->child[i] != pc) {
                BTree_print(node->child[i],pc, layer);
            }
        }
    }
    else {
        printf("树为空。\n");
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
