#pragma once

#include "pch.h"

template<typename Type>
class List 
{
public:
	Type elem;
	List<Type> * next = nullptr;

		List(const Type & elem) {
			this->elem = elem;
		};

		int Length() {
			if (next == nullptr) return 1;
			else return (1 + (next->Length()));
		}

		void Append(const Type & elem) {
			if (next == nullptr) next = new List(elem);
			else next->Append(elem);
		}

		 List<Type>* Concat(const Type & elem) 
		 {
			auto z = new List(elem);
			z->next = this;
			return z;
		 }

		List<Type>* Remove(const Type & elem) {
			if (this->elem == elem) 
			{
				auto r = next;
				this->next = nullptr;
				delete this;
				if (r != nullptr) 
				{ 
					return r->Remove(elem); 
				}
				else 
				{ 
					return nullptr; 
				}
			}
			else 
			{
				if (next) 
				{
					next = next->Remove(elem);
				}
				return this;
			}
		}

		bool Contains(const Type & elem) {
			if (this->elem = elem) {
				return true;
			}
			else if (next == nullptr) {
				return false;
			}
			else return next->Contains(elem);
		}
};

typedef List<int> IntList;

