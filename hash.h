#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

struct product{
	string stockcode;
	int quantity;
	string description;
};

struct linkedlistnode {
	struct linkedlistnode *next;
	struct product product;
};

class hashT {
private:
	int tablesize;
	linkedlistnode** hashtable;
	product* arr;
	int nElements;

public:
	hashT(int size);
	~hashT();
	void search();
	int Hash(string stockcode);
	void insert(string stockcode, string description, int quantity);
	void printtable();
	double loadFactor();
	void maxquantity();
	void copytoarray();
	void swap(product &a, product &b);
	void bubblesort();
	void printTop10();
	int NofElements();

};

