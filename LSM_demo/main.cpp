#include "iostream"
#include "DiskRun.h"

using namespace std;

int main(int argc, char* argv) {

	cout << "hello world" << endl;

	DiskRun<int, int> diskRun;
	diskRun.rangeSearch(0, 1);

	system("pause");
	return 0;
}