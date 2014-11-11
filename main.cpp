#include "hashtable.h"
#include <iostream> //for debug interface
#include <stdlib.h> //for atoi
using namespace std; //because who wants to type std:: thirty times?

/** Quick and dirty debug interface */
int main(){
  HashTable table;
  char *input=new char;
  int actualInput(0);
  string content;
  while(true){
    while(actualInput == 0){
      cout << "Pick an option:" << endl;
      cout << "1: Insert an item." << endl;
      cout << "2: Remove an item" << endl;
      cout << "3: Look up an item" << endl;
      cout << "4: Print table" << endl;
      cout << "Enter your choice: ";
      cin >> *input;
      actualInput = atoi(input);
      if(actualInput < 1 || actualInput > 4){
        cout << "Try again." << endl;
        actualInput=0;
      }
    }
    if(actualInput < 4) {
      cout << "Enter a string to insert: ";
      cin >> content;
    } else {
      table.printTable();
    }
    switch(actualInput){
      case 1: 
        table.insert(content);
        break;
      case 2:
        table.remove(content);
        break;
      case 3:
        cout << *table.getByKey(content) << endl;
    }
    actualInput=0;
  }
}
