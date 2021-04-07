#ifndef __STACK
#define __STACK
#include <cstring>
#include <cstdlib>

namespace nStack {

	class Node {
	private:
		char* mdata;
		Node* mnextNode;

		friend class Stack;
		friend class Calculator;
	public:
		Node() :mdata(nullptr), mnextNode(nullptr) {}
	};

	class Stack {
	private:
		Node* mbegin;
		Node* mtop;
	public:
		Stack() : mbegin(nullptr), mtop(nullptr) {}
		~Stack();
		Node* Create_stack(char* data);
		void Push(Node* node);
		void Destroy_node(Node* deleteNode);
		void Destroy_stack();
		Node* Pop();
		Node* Get_top();
		bool Isempty();
	};
}

#endif __STACK