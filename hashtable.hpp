#ifndef HASHTABLE_HPP
#define  HASHTABLE_HPP
#include <iostream>
#include <ostream>
#include <vector>
#include <list>
using namespace std;
using namespace cop4530;

template <typename T>
HashTable<T>::HashTable(size_t size)
{
	theList.resize(prime_below(size));
	currentSize = 0;
}
template <typename T>
HashTable<T>::~HashTable()
{
	clear();
	//	delete theList;
}
template <typename T>
bool HashTable<T>::contains(const T& x)
{
	auto& type = theList[myhash(x)];
	return find(begin(type), end(type), x) != end(type);
}
template <typename T>
bool HashTable<T>::insert(const T& x)
{
	auto& whichList = theList[myhash(x)];
	if (find(begin(whichList), end(whichList), x) != end(whichList))
		return false; //return if found

	whichList.push_back(x);
	currentSize++;

	if (currentSize > theList.size())
		rehash();

	return true;

}
template <typename T>
bool HashTable<T>::insert(T&& x)
{
	auto& whichList = theList[myhash(x)];
	if (find(begin(whichList), end(whichList), x) != end(whichList))
		return false; //return if found
	
	whichList.push_back(x);
	currentSize++;
	if (currentSize > theList.size())
		rehash();
	return true;
}
template <typename T>
bool HashTable<T>::remove(const T& x)
{
	auto& whichList = theList[myhash(x)];
	auto itr = find(begin(whichList), end(whichList), x);

	if (itr == end(whichList))
		return false;
	else {
		whichList.erase(itr);
		--currentSize;
		return true;
	}
}
template <typename T>
void HashTable<T>::clear()
{
	makeEmpty();
	currentSize = 0;
}
template <typename T>
void HashTable<T>::makeEmpty()
{
	for (auto& thisList : theList)
	{
		thisList.clear();
	}
	currentSize = 0;
}

template <typename T>
bool HashTable<T>::load(const char* filename)
{
	string word;
	ifstream iss;
	string line;
	iss.clear();
	iss.open(filename);
	while (iss >> word)
	{
		insert(word);
	}
	iss.close();
	return true;
}

template <typename T>
void HashTable<T>::dump()
{
	if (currentSize == 0)
		return;
	else
	{
		for (auto& whichList : theList)
		{
			for (auto itr = whichList.begin(); itr != whichList.end(); ++itr) //needs to be checked
				cout << *itr << endl; //just display elements not keys
		}
	}

}

template <typename T>
bool HashTable<T>::write_to_file(const char* filename)
{
	ofstream out;
	out.open(filename);
	for (auto& whichlist : theList)
	{
		for (auto itr = whichlist.begin(); itr != whichlist.end(); ++itr) //needs to be checked
			out << *itr << endl; //just display elements 
	}
	out.close();
	return true;
}


// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename T>
unsigned long HashTable<T>::prime_below(long n)
{
	if (n > max_prime)
	{
		std::cerr << "** input too large for prime_below()\n";
		return 0;
	}
	if (n == max_prime)
	{
		return max_prime;
	}
	if (n <= 1)
	{
		std::cerr << "** input too small \n";
		return 0;
	}

	// now: 2 <= n < max_prime
	std::vector <long> v(n + 1);
	setPrimes(v);
	while (n > 2)
	{
		if (v[n] == 1)
			return n;
		--n;
	}

	return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename T>
void HashTable<T>::setPrimes(std::vector<long>& vprimes)
{
	int i = 0;
	int j = 0;

	vprimes[0] = 0;
	vprimes[1] = 0;
	int n = vprimes.capacity();

	for (i = 2; i < n; ++i)
		vprimes[i] = 1;

	for (i = 2; i * i < n; ++i)
	{
		if (vprimes[i] == 1)
			for (j = i + i; j < n; j += i)
				vprimes[j] = 0;
	}
}

template <typename T>
void HashTable<T>::rehash()
{
	auto oldLists = theList;

	// create new double-sized, empty table
	theList.resize(prime_below(2 * theList.size()));
	for (auto& thisList : theList)
		thisList.clear();

	// copy table over
	currentSize = 0;
	for (auto& thisList : oldLists)
		for (auto& x : thisList)
			insert(std::move(x));
}

template <typename T> 
int HashTable<T>::mySize()
{
	return currentSize;
}

template <typename T>
size_t HashTable<T>::myhash(const T& x) const
{
	static hash<T>f;
	return f(x) % theList.size();
}
#endif