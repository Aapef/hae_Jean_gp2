#pragma once
#include <functional>
template<typename T>
class Node 
{
public:
	T elem;
	Node * left = nullptr;
	Node * right = nullptr;

	Node(const T&elem) {
		this->elem = elem;
	}

	void insert(const T & elem) {
		if (elem < this->elem) insertLeft(elem);
		else insertRight(elem);
	}

	void insertLeft(const T & elem) {
		if (left == nullptr) left = new Node(elem);
		else 
		{
			if (left->elem < elem) left->insertRight(elem);
			else left->insertLeft(elem);
		}
	}

	void insertRight(const T & elem) {
		if (right == nullptr) right = new Node(elem);
		else
		{
			if (right->elem < elem) right->insertRight(elem);
			else right->insertLeft(elem);
		}
	}

	void insertNode(Node* newBranch) {
		if (newBranch == nullptr) return;
		auto r = newBranch->right;
		auto l = newBranch->left;
		
		newBranch->left = nullptr;
		newBranch->right = nullptr;
		insert(newBranch->elem);
		delete newBranch;
		insertNode(l);
		insertNode(r);
	}

	bool Contains(const T & melem) {
		if (this->elem == melem) return true;
		else if (this->elem > melem) { if(left) return left->Contains(melem); }
		else if (this->elem < melem) { if(right) return right->Contains(melem); }
		return false;		
	}

	Node* Remove(const T & elem) {
		auto l = left;
		auto r = right;
		if (left) left = left->Remove(elem);
		if (right) right = right->Remove(elem);
		if (this->elem == elem) 
		{
			delete this;
			if (l == nullptr) return r;
			l->insertNode(r);
			return l;
		}
		else {
			return this;
		}
	}

	int getLength() {
		/*if (left == nullptr && right == nullptr) 
		{
			return 1;
		}*/
		int z = 1;
		if (left != nullptr)
			z = z  + left->getLength();
		if (right != nullptr)
			z = z  + right->getLength();
		return z;
	}

	void dfsprint() {
		if(left) left->dfsprint();
		printf("%f ",elem);
		if(right) right->dfsprint();
	}

	void bfsprint() {
		printf("%f ", elem);
		if (left) left->bfsprint();
		if (right) right->bfsprint();
	}

	void dfsprintreverse() {
		if (right) right->dfsprintreverse();
		printf("%f ", elem);
		if (left) left->dfsprintreverse();
		
		
	}

	void dfs(std::function<void(Node*)> fun)
	{

	}

	void bfs(std::function<void(Node*)> fun)
	{

	}

};



template<typename T>
class Tree {
public: 
	Node<T> * root = nullptr;
	Tree()
	{

	}
	~Tree() 
	{
		delete root;
		root = nullptr;
	}

	void insert(const T & elem) 
	{
		if (root == nullptr) this->root = new Node(elem);

	}

	void getLength() {
		if (root == nullptr) return 0;
		else return root->getLength();
	}
};

typedef Tree<float> FloatTree;