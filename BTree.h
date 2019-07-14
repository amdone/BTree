/*
 * BTree.h
 *
 *  Created on: 2019年7月13日
 *      Author: Eichi
 */


#ifndef SRC_BTREE_H_
#define SRC_BTREE_H_

#include "BTreeNode.h"


template<class K,class E>
class BTree{
	public:
		BTree();

		~BTree();
		BTree(int rank);
		bool empty() const;
		int size() const;
		//bool opeator>(std::pair<const K, E>& thePair) const;
		void insert(const std::pair<const K, E>& thePair);
		void output();


	private:
		BTreeNode<std::pair<K,E>> *root;
		int treeSize;
		int rank;

};

template <class K, class E>
std::ostream& operator<<(std::ostream& out,std::pair<K, E>& x){
	out << x.first << '-' << x.second;
	return out;
}


#endif /* SRC_BTREE_H_ */
