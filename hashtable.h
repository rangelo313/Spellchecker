#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include <ostream>
#include <functional>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
namespace cop4530
{
	template <typename T>
	class HashTable {
	public:
		// used when improper size is given (for example
		// size is 0 or negatiave)
		static const unsigned int default_capacity = 11;
		static const unsigned int max_prime = 1301081;

		HashTable(size_t size = 101);
		~HashTable();
		
		bool contains(const T& x);
		bool insert(const T& x);
		bool insert(T&& x); 
		bool remove(const T& x);
		
		void clear();
		int mySize();
		bool load(const char* filename);
		void dump();
		bool write_to_file(const char* filename);

	private:
		std::vector<std::list<T>> theList; // the array of the lists
		int currentSize;
		void makeEmpty();
		void rehash();
		size_t myhash(const T& x) const;
		unsigned long prime_below(long);
		void setPrimes(std::vector<long>&);
		
	};
	#include "hashtable.hpp"
}
#endif