#include<string>
#include<set>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
using namespace std;

int main(){
    std::set<std::string> block;
    std::set<std::string> succBlock;
    std::set<std::string>::iterator itB, itS;
    string str = "initial";
    while (str.compare("quit") != 0){
        cin >> str;
        cout << str << " first \n";
        block.insert(str);
    }
    for (itB = block.begin(); itB != block.end(); itB++)
      std::cout << *itB << " second \n";  
    itB = block.find("entry");
    succBlock.insert("bb2");
    if (itB != block.end())  block.erase(itB);
    for (itS = succBlock.begin(); itS != succBlock.end(); itS++)
      block.erase(block.find(*itS));
    for (itB = block.begin(); itB != block.end(); itB++)
      std::cout << *itB << "\n";  
}
