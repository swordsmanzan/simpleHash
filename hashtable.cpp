#include "hashtable.h"

HashTable::HashTable():
table(new content[initTableSize]),
population(0),
capacity(initTableSize),
resizing(false){
  init();
}

void HashTable::init(){
  for(int i=0; i<capacity; ++i){
    table[i]="\0"; //initialize to nulls so we can detect collisions  
  }
}

int HashTable::getHashIndex(content which){
  int total(0);
  int i(0);
  while(which[i] != '\0'){ //we are assuming null termination
    total += which[i]; //implicit cast to int
    ++i;
  }
  return total % capacity; //get a number between zero and our array size
}

void HashTable::insert(content input){
  int location(getHashIndex(input)); //where we think 'input' belongs in our table

  while(table[location].compare("\0")){ //detecting collisions
    ++location; //check the next index
    if(location >= capacity){ //don't run off the end
      location = 0; //our table is circular
    }
  }
  table[location] = input;
  if(!resizing){ //if we are resizing, avoid calling checkFull, as this will cause recursion...
     ++population;
    checkFull(); //...and, for very large array sizes, may overflow our stack
  }
}

void HashTable::checkFull(){
  if(population >= capacity){ //this is where we're detecting if we are full
    resizing = true;
    capacity *= 2; //we want to double in size when full.
    content *oldTable = table;
    table = new content[capacity];
    for(int i=0; i<population; ++i){
      insert(oldTable[i]); //put all old values into the new table
    }
    resizing = false;
  }
}

content *HashTable::getByKey(content key){
  int index = getHashIndex(key);
  for(int i=index; i<=capacity; ++i){ //we will never exit this loop conventionally
    if(i==capacity) i=0; //the array is circular
    if(table[i].compare(key)==0 || table[i].compare('\0')){
      return &table[i]; //return the match or the null to indicate that there is no match
    }
    //else, let the loop increment 'i' and try again
  }
  return '\0'; //Non-embedded environments should consider an exception. We should never get here because we detect 'table full' on insert.
}

bool HashTable::remove(content key){
  content *toRemove(getByKey(key));
  if(toRemove->compare("\0")==0){
    return false;
  }
  *toRemove = '\0';
  return true;
}

void HashTable::printTable(){
  for(int i=0; i<capacity; ++i){
    std::cout << table[i] << std::endl;
  }
}
