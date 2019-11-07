#pragma once
#include <functional>

class Heap
{
public:
	int elem;
	Heap * more;
	Heap * less;

	Heap(int elem, Heap * more = nullptr, Heap * less = nullptr) 
	{
		this->elem = elem;
		this->more = more;
		this->less = less;
	}

	void Heapify(int elem) 
	{
		if (elem >= this->elem) {
			if (more == nullptr) { more = new Heap(elem, nullptr, this); }
			else if (elem < more->elem) {
				more = new Heap(elem, more, this);
				more->more->less = more;
			}
			else more->Heapify(elem);
		}
		else if (elem < this->elem) {
			if (less == nullptr) { less = new Heap(elem, this); }
			else if (elem > less->elem) {
				less = new Heap(elem, this, less);
				less->less->more = less;
			}
			else less->Heapify(elem);
		}
	}

	void callprintup() {
		printf("%i  ", elem);
		if (more != nullptr) more->callprintup();
		else printf("\n");
	}

	void callprintdown() {
		printf("%i  ", elem);
		if(less != nullptr) less->callprintdown();
		else printf("\n");
	}

	void GetElems() 
	{
		if (less != nullptr) less->GetElems();
		else 
		{
			callprintup();
		}
	}

	void GetElemsRev()
	{
		if (more != nullptr) more->GetElemsRev();
		else
		{
			callprintdown();
		}
	}

};
