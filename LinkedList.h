#pragma once
#pragma once
#include <iostream>
#include "node.h"
#include <math.h>
using namespace std;

template<typename T>
class LinkList {
private:
	Node<T>* head;
public:
	LinkList() { head = NULL; }
	void print() {
		if (!head) { cout << "empty list" << endl; }
		else {
			Node<T>* temp = head;
			while (temp) {
				cout << temp->getItem() << " ";
				temp = temp->getNext();
			}
			cout << endl;
		}
	};
	Node<T>* getlast() {
		Node<T>* temp = head;
		while (temp->getNext()) {
			temp = temp->getNext();
		}
		return temp;
	}
	void insertbeg(T x) {
		Node<T>* temp = new Node<T>(x);
		temp->setNext(head);
		head = temp;
	};
	void DeleteAll() {
		Node<T>* temp = head;
		while (head) {
			temp = head;
			head = head->getnext();
			delete temp;

		};
	};
	void insertend(T x) {
		if (!head) { insertbeg(x); return; }
		Node<T>* temp = new Node<T>(x);
		Node<T>* temp2 = head;
		while (temp2->getNext())
		{
			temp2 = temp2->getNext();
		}
		temp2->setNext(temp);
	}
	int converttodec(int bits) {
		Node<T>* temp = head;
		int dec = 0;
		while (bits != -1 && temp) {
			dec = dec + temp->getItem() * pow(2, bits - 1);
			temp = temp->getNext();
			bits--;
		}
		return dec;
	}
	bool search(T x) {
		if (!head) { return 0; }
		Node<T>* temp = head;
		while (temp)
		{
			if (temp->getitem() == x) {
				return true;
			}
			temp = temp->getnext();
		}
		return 0;
	}
	int counterofitm(T x) {
		int count = 0;
		if (!head) { return count; }
		Node<T>* temp = head;

		while (temp)
		{
			if (temp->getitem() == x) {
				count++;
			}
			temp = temp->getnext();
		}
		return count;
	}
	void deletefirst() {
		Node<T>* temp = head;
		head = head->getnext();
		delete temp;
	}
	void deletelast() {
		Node<T>* temp2 = head;
		while ((temp2->getNext())->getNext()) {
			temp2 = temp2->getNext();
		}
		delete temp2->getNext();
		temp2->setNext(NULL);
	}
	bool deleteNode(T x) {
		Node<T>* temp = head;
		int c = search(x);
		if (c == 0) {
			return false;
		}
		else {
			while ((temp->getnext())->getitem() != x) {
				temp = temp->getnext();
			}
			Node<T>* temp2 = temp->getnext()->getnext();
			delete temp->getnext();
			temp->setnext(temp2);
			return true;
		}
		return false;
	};
	bool deleteNodes(T x) {
		Node<T>* temp = head;
		int c = counterofitm(x);
		for (int i = 0; i < c; i++) {
			deleteNode(x);
		}
		return true;
	}
	void merge(const LinkList& L) {
		Node<T>* temp = head;
		while (temp->getnext()) {
			temp = temp->getnext();
		}
		temp->setnext(L.head);
	}
	void reverse()
	{
		Node<T>* current = head;
		Node<T>* prev = NULL;
		Node<T>* next = NULL;

		while (current != NULL) {
			// Store next
			next = current->getnext();


			current->setnext(prev);


			prev = current;
			current = next;
		}
		head = prev;
	}
	void rotatebyint(int x) {
		for (int i = 0; i < x; i++) {
			Node<T>* last = getlast();
			insertbeg(last->getItem());
			deletelast();
		}
	}
};