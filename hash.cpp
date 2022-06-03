#include "hash.h"

hashT::hashT(int size) {

	tablesize = size;
	hashtable = new linkedlistnode*[tablesize];
	

	for (int i = 0; i < tablesize; i++)
	{
		hashtable[i] = NULL;
		
	}

}

hashT::~hashT() {
	// for (int i = 0; i < tablesize; i++)
	// {
	// 	linkedlistnode *temp = hashtable[i];
		
	// 	while (temp !=NULL)
	// 	{
	// 		linkedlistnode *iter = temp->next;
	// 		delete temp;
	// 		temp = iter;
	// 	}
	// 	delete[] hashtable;
	// }
}

int hashT::Hash(string stockcode) {

	int hash = 1;
	int index;
	for (size_t i = 0; i < stockcode.length(); i++)
	{
		hash = hash * (1 + (int)stockcode[i]);
		//cout << "hash=" << hash << endl;
	}
	index = (hash < 0 ? -hash : hash) % tablesize;

	return index;
}

void hashT::insert(string stockcode, string description, int quantity) {

	int index = Hash(stockcode);

	linkedlistnode *head =hashtable[index];

	if (hashtable[index]==NULL)
	{
		hashtable[index] = new linkedlistnode;
		hashtable[index]->product.description = description;
		hashtable[index]->product.stockcode = stockcode;
		hashtable[index]->product.quantity = quantity;
		hashtable[index]->next = NULL;
	}

	else
	{
		while(head != NULL){
			if(head->product.stockcode == stockcode){
				head->product.quantity += quantity;
				break;
			}
			head = head->next;
		}

		if(head == NULL){
			linkedlistnode* temp = new linkedlistnode;
			temp->next = hashtable[index];

			temp->product.description = description;
			temp->product.quantity = quantity;
			temp->product.stockcode = stockcode;

			hashtable[index] = temp;
		}

	}
}

double hashT::loadFactor()
{
	int nNonEmptyLists = 0;
	int nElements = 0;

	for (int i = 0; i < tablesize; i++)
	{
		if(hashtable[i]){
			nNonEmptyLists++;

			linkedlistnode *head = hashtable[i];

			while(head != NULL){
				nElements++;
				head = head->next;
			}
		}
	}	

	return nNonEmptyLists / (double) nElements;
}


void hashT::maxquantity(){
	int count=0;

	for(int i=0;i<tablesize;i++){
		if(hashtable[i]){
			linkedlistnode *head=hashtable[i];
			while(head != NULL){
				if(hashtable[i]->product.quantity > count){
					count=hashtable[i]->product.quantity;
				}
				head=head->next;
			}
		}

	}
	cout<<"max quantity = "<<count<<endl;

}
int hashT::NofElements() {

	nElements = 0;
	int nNonEmptyLists = 0;

	for (int i = 0; i < tablesize; i++)
	{
		if (hashtable[i]) {
			nNonEmptyLists++;

			linkedlistnode *head = hashtable[i];

			while (head != NULL) {
				nElements++;
				head = head->next;
			}
		}
	}
	

	return nElements;
}
void hashT::copytoarray() {
	arr = new product[nElements];
	int j = 0;

	product tmp;
	
	for (int i = 0; i < tablesize; i++)
	{
		if (hashtable[i]) {
			linkedlistnode *head = hashtable[i];
			while (head != NULL) {
				tmp.quantity = head->product.quantity;
				tmp.description = head->product.description;
				tmp.stockcode = head->product.stockcode;
				arr[j++] = tmp;
				head = head->next;
			}
		}
	}
}

void hashT::swap(product &a, product &b){
	product temp = a;
	a = b;
	b = temp;
}

void hashT::bubblesort(){
	for(int i=0; i<nElements-1;i++){
		for(int j=0;j<nElements-i-1;j++){
			if(arr[j].quantity > arr[j+1].quantity){
				swap(arr[j], arr[j+1]);
			}
		}

	}
}
void hashT::printTop10() {
	for (int i = nElements-1; i > nElements-11; i--)
	{
		cout << "\t(" << "Stockcode : "<< arr[i].stockcode << ", ";
		cout << " Description : "<<arr[i].description << ", ";
		cout <<" Quantity : "<<arr[i].quantity << ")" << endl;
	}

}


void hashT::printtable() {

	
	for (int i = 0; i < tablesize; i++)
	{
		if(hashtable[i]){
			cout << "-----------------------" << endl;
			cout << "index=" << i << endl;
			linkedlistnode *head = hashtable[i];

			while(head != NULL){
				cout << "\t(" << head->product.stockcode << ", ";
				cout << head->product.description << ", ";
				cout << head->product.quantity << ")" << endl;

				head = head->next;
			}

			cout << "-----------------------" << endl;
		}
	}

}
