#include "hash.h"
#include <iostream>
#include <string>

#define NUM_VALUES 8

using namespace std;


// small -> return a negative number
// equal -> 0
// bigger -> a positive number
int compare_dates(int d1, int m1, int y1, 
				   int d2, int m2, int y2){
	if(y1 < y2) return -1;
	else if(y1 > y2) return 1;
	else{
		if(m1 < m2) return -1;
		else if(m1 > m2) return 1;
		else return d2 - d1;
	}

	return 0;
}

bool is_between(string date, int d1, int m1, int y1,
							 int d2, int m2, int y2){
	int dot1 = date.find('.');
	int dot2 = date.find('.', dot1+1);

	int day = stoi(date.substr(0, dot1));

	int month = stoi(date.substr(dot1+1, dot2-dot1-1));
	int year  = stoi(date.substr(dot2+1));

	return compare_dates(day, month, year, d1, m1, y1) >= 0 
		&& compare_dates(day, month, year, d2, m2, y2) <= 0;
}

int main() {

	hashT product(10000);
	ifstream myfile;
	string row;


	// clock_t time_req;
	//time_req = clock();

	// product.insert("44EF34", "bebe", 835);
	// product.insert("44CS74", "bebeF", 8555);
	// product.insert("CFE233", "bebeR", 853);
	// product.insert("48844G", "bebeK", 386);
	// product.insert("47744A4", "bebeO", 186);
	// product.insert("44EF34", "bebe", 835);

	

	myfile.open("OnlineRetail.csv");

	if (!myfile.is_open()) {cout << "ERROR OPENING FILE" << endl;}

	char delim = ';';

	string rowValues[NUM_VALUES];

	int skip = 1, count = 0;
    while (getline(myfile, row))
	{
		if(count++ < skip) continue;

		int pos = 0;
		for(int i = 0; i < NUM_VALUES; i++){
			int nextPos = row.find(delim, pos);
			if(nextPos != std::string::npos)
				rowValues[i] = row.substr(pos, nextPos-pos);
			else 
				rowValues[i] = row.substr(pos);
			pos = nextPos + 1;
		}
		if(rowValues[NUM_VALUES-1].compare("United Kingdom") != 0 && 
		   is_between(rowValues[4].substr(0, 10), 1, 12, 2010, 9, 12, 2011) ){
			
		product.insert(rowValues[1], rowValues[2], stoi(rowValues[3]));
		}
	}

	// cout << product.loadFactor() << endl;
	//cout<<product.NofElements()<<endl;
	
	product.NofElements();
	product.copytoarray();
	
	
	//product.maxquantity();
	// product.printtable();
	product.bubblesort();
	product.printTop10();
	//time_req=clock()-time_req;
	//cout << "elapsed time: " << (float)time_req / CLOCKS_PER_SEC << "seconds" << endl;

	//myfile.close();


	cout << "Program Ends" << endl;

	return 0;
}
