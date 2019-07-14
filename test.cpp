/*
 * test.cpp
 *
 *  Created on: 2019年7月13日
 *      Author: Eichi
 */

#include "BTree.cpp"
using std::cout;
using std::endl;

int main(){

	cout<<"Test Start!"<<endl;
	BTree<int,int> a(3);
	a.insert(std::pair<int,int>(10,1));
	a.insert(std::pair<int,int>(20,1));
	a.insert(std::pair<int,int>(5,1));
	a.insert(std::pair<int,int>(6,1));
	a.insert(std::pair<int,int>(12,1));
	a.insert(std::pair<int,int>(30,1));
	a.insert(std::pair<int,int>(7,1));
	a.insert(std::pair<int,int>(17,1));
	a.output();
}



