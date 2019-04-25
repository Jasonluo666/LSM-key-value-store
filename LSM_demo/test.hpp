#ifndef _TEST
#define _TEST

#include <iostream>
#include <vector>
#include "Run.hpp"

using namespace std;

void prints( vector<Pair<int,int> > KV_pairs){
    for(int i = 0; i < (int)KV_pairs.size(); i++){
        cout<<"<"<<KV_pairs[i].key<<","<<KV_pairs[i].value<<">"<<endl;
    }
}

void prints(Pair<int,int>* aPair){
    if(aPair == NULL){
        cout<<"No such entry"<<endl;
    }
    else{
        cout<<"<"<<(*aPair).key<<","<<(*aPair).value<<">"<<endl;
    }
}

vector<Pair<int,int> > createvector(int n){
    vector<Pair<int,int> > Pairs;
    Pair<int,int> aPair;
    for(int i = 0; i < n; i++){
        aPair.key = i;
        aPair.value = i;
        Pairs.push_back(aPair);
    }
    return Pairs;
}

#endif // _TEST
