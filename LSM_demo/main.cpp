#include "iostream"
#include "DiskRun.hpp"
#include "LSM.hpp"
#include "stdlib.h"
#include "test.hpp"

using namespace std;

int main(int argc, char* argv[]) {

	cout << "hello world" << endl;
	LSM<int,int> tree(4096,4096,16,2);
	for(int i = 0; i < 1000; i++){
        tree.insert(i,i);
	}
	for(int i = 0; i < 1000; i+=2){
        tree.insert(i,-1);
	}
	tree.delete_key(2);
	for(int i = 0; i < 1000; i++){
        prints(tree.lookup(i));
	}
	//prints(tree.range(-500,1500));
	system("pause");
	return 0;
}
