#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdexcept>
#include "Stack.hpp"

using namespace std;

namespace nStack {
	Stack::~Stack()
	{
		while (!Isempty()) {
			Node* _popNode = mtop;
			if (mbegin == mtop) {
				mtop = nullptr;
				mbegin = nullptr;
			}
			else {
				Node* _currentNode = mbegin;
				while (_currentNode->mnextNode != _popNode)
					_currentNode = _currentNode->mnextNode;
				free(mtop->mdata);
				free(mtop);
				mtop = _currentNode;
				_popNode = mtop;
			}
		}
	}
	//Stack�� ���� push�ϴ� �Լ�
	Node* Stack::Create_stack(char* data)
	{
		Node* _newStack = (Node*)malloc(sizeof(Node));
		_newStack->mdata = (char*)malloc(sizeof((strlen(data)) + 1));
		strcpy(_newStack->mdata, data);
		_newStack->mnextNode = nullptr;

		return _newStack;
	}

	void Stack::Push(Node* node)
	{
		if (mbegin == nullptr)
			mbegin = node;
		else
			mtop->mnextNode = node;
		mtop = node;
	}

	//POP�� ��ġ�� �ִ� ��� ����
	void Stack::Destroy_node(Node* deleteNode)
	{
		if (deleteNode != nullptr) {
			if ((deleteNode->mdata) != nullptr)
				free(deleteNode->mdata);
			free(deleteNode);
		}
	}

	void Stack::Destroy_stack()
	{
		while (!Isempty()) {
			Node* _popNode = Pop();
			Destroy_node(_popNode);
		}
	}
	//Stack�� �������� ���� ���Ҹ� POP�ϴ� �Լ�
	Node* Stack::Pop()
	{
		Node* _popNode = mtop;
		if (mbegin == mtop) {
			mtop = nullptr;
			mbegin = nullptr;
		}
		else {
			Node* _currentNode = mbegin;
			while (_currentNode->mnextNode != _popNode)
				_currentNode = _currentNode->mnextNode;
			mtop = _currentNode;
			mtop->mnextNode = nullptr;
		}
		return _popNode;
	}
	//���� top�� ��ġ�� ã�� �Լ�
	Node* Stack::Get_top()
	{
		return mtop;
	}
	//Stack�� ����ִ��� Ȯ���ϴ� �Լ�
	bool Stack::Isempty()
	{
		return (mbegin == nullptr && mtop == nullptr);
	}
}