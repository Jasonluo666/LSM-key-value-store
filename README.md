# LSM-key-value-store

## CS 591 A1 Data System Project

Instructions：

There are mainly 2 ways of running this system.

First one, you can uncomment line 12 in main.cpp, and change parameters like buffer_size, page_size, max_level, runs_per_level, and FP_rate, to initialize the LSM-tree system. 

//LSM<int,int> tree(4096,4096,16,2, 0.01);

And then you can write code as follows to test its functions:

tree.insert(key,value);
tree.lookup(key);
tree.delete_key(key);
tree.range(key_min, key_max);

Another way is using test functions we write.

struct LSMParams {
	int buffer_size = 4096;
	int page_size = 4096;
	int max_level = 8;
	int runs_per_level = 2;
	double FP_rate = 0.01;
	int printout_num = 100;
};

First you need to define a LSMParams object with your own configuration, and then call functions in main.cpp as follows:

runsizeTest(param, num_opr);
throughputTest(param, num_opr);
bloomfilterTest(param, num_insert);

Here, num_opr or num_insert is how many times you want to test.
