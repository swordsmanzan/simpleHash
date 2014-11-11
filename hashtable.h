#ifndef HASHTABLE_H
#define HASHTABLE_H

/** A simple open-address hash table using linear probing
 *  Currently stores strings, but could easily be modified
 *  to take any data type.
 *  To be usable with this table with minimal modification,
 *  a data type must contain a char array of some sort to be
 *  used as a key.
 *  Presumably, some places will require an extra layer of
 *  indirection if another class is used in place of strings.
*/

#include <iostream> //for strings.

/** typedef so a more useful data type can easily be plugged in */
typedef std::string content;

/** The initial capacity of the hash table */
static const unsigned initTableSize(10); //setting this value to 0 will break the program

class HashTable {
public:
  HashTable();
  
  /** Insert an item into the table */
  void insert(content input);
  
  /** Determine if the array is full and resize if it is. */
  void checkFull();
  
  /** Returns the content found by the specified key.
      More useful for data types in which the key is not the entire content.
      A return of null indicates that there is no match in the table
      Note that we are returning a pointer to allow the user to edit existing data*/
  content *getByKey(content key);

  /** remove the specified item from the table. Returns true if a value was removed */
  bool remove(content key);
  
  /** Prints the contents of the table. Purely for debug. If using this class in real code, remove this function. */
  void printTable();

private:
  /** The array in which we will be storing data */
  content *table;
  /** Number of entities in the array */
  int population;
  /** Highest possible population with current array size. Note that this value is 1-based */
  int capacity;
  /** Are we resizing the array? */
  bool resizing;
  
  /** Just initializes our table to a bunch of nulls. Ho-hum. */
  void init();
  /** Returns the hash index calculated by a given set of characters. This is our hashing function. */
  int getHashIndex(content which);
};

#endif // HASHTABLE_H
