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
	BTree<int,char> a(5);
//	a.insert(std::pair<int,int>(39,1));
//	a.insert(std::pair<int,int>(22,1));
//	a.insert(std::pair<int,int>(97,1));
//	a.insert(std::pair<int,int>(41,1));
//	a.insert(std::pair<int,int>(53,1));
//	a.insert(std::pair<int,int>(13,1));
//	a.insert(std::pair<int,int>(21,1));
//	a.insert(std::pair<int,int>(40,1));
//	a.insert(std::pair<int,int>(30,1));
//	a.insert(std::pair<int,int>(27,1));
//	a.insert(std::pair<int,int>(33,1));
//	a.insert(std::pair<int,int>(36,1));
//	a.insert(std::pair<int,int>(35,1));
//	a.insert(std::pair<int,int>(34,1));
//	a.insert(std::pair<int,int>(24,1));
//	a.insert(std::pair<int,int>(29,1));

	a.insert(std::pair<int,char>(1,'x'));
	a.insert(std::pair<int,char>(2,'x'));
	a.insert(std::pair<int,char>(6,'x'));
	a.insert(std::pair<int,char>(7,'x'));
	a.insert(std::pair<int,char>(11,'x'));
	a.insert(std::pair<int,char>(4,'x'));
	a.insert(std::pair<int,char>(8,'x'));
	a.insert(std::pair<int,char>(13,'x'));
	a.insert(std::pair<int,char>(10,'x'));
	a.insert(std::pair<int,char>(5,'x'));
	a.insert(std::pair<int,char>(17,'x'));
	a.insert(std::pair<int,char>(9,'x'));
	a.insert(std::pair<int,char>(16,'x'));
	a.insert(std::pair<int,char>(20,'x'));
	a.insert(std::pair<int,char>(3,'x'));
	a.insert(std::pair<int,char>(12,'x'));
	a.insert(std::pair<int,char>(14,'x'));
	a.insert(std::pair<int,char>(18,'x'));
	a.insert(std::pair<int,char>(19,'x'));
//	a.insert(std::pair<int,char>(15,'x'));
	//a.outTest();
	a.output();
	a.print();
	//cout<<a.find(12);
}



