#define _CRT_SECURE_NO_WARNINGS
#include <climits>
#include "Calculator.hpp"

namespace nStack {
	/*     �켱������
		   *, / = 1����
	*      +, - = 2����
	*         ( = 3����
	*      �̴�.
	*      �켱������ �̷������δ� �˰� �־�����, �켱������ ���ϴ� �Լ��� �������� ���Ͽ����ϴ�.
	*      �켱���� ���ϴ� �Լ��� �����ϱ� ���� ���۰˻����� ���� �߽��ϴ�. Isprior�Լ��� ���ذ� ���� �ʽ��ϴ�.
	*/
	int Calculator::Get_priority(char operate, int exist)
	{
		int _priority = INT_MAX;
		switch (operate)
		{
			case static_cast<char>(sign::LEFT_PARENTHESES) : {
				if (exist)
					_priority = 3;
				else
					_priority = 0;
				break;
			}
			case static_cast<char>(sign::MULTIPLY) : {}
			case static_cast<char>(sign::DIVIDE) : {
				_priority = 1;
				break;
			}
			case static_cast<char>(sign::PLUS) : {}
			case static_cast<char>(sign::MINUS) : {
				_priority = 2;
				break;
			}
		}
		return _priority;
	}
	bool Calculator::Isprior(char operation_1, char operation_2)
	{
		return (Get_priority(operation_1, 1) < Get_priority(operation_2, 0));
	}
	//���ÿ� �ִ� ���ڰ� ����(�ǿ�����)���� ���������� Ȯ���ϴ� �Լ�
	bool Calculator::Isnum(char sign)
	{
		for (int i = 0; i < sizeof(mnumber); i++)
			if (sign == mnumber[i])
				return true;

		return false;
	}

	int Calculator::Get_next_value(char* postfix, char* value, int& type)
	{
		int i = 0;
		for (i = 0; postfix[i] != NULL; i++)
		{
			//������ ���ڰ� ����(�ǿ�����)���� ���
			if (Isnum(postfix[i]) == true) {
				type = static_cast<int>(sign::OPERAND);
				value[i] = postfix[i];
				if (Isnum(postfix[i + 1]) == false)
					break;
			}
			else {
				//- ��꿡 ������ �־� NEGATIVE�� �߰��Ͽ� �������� +(-X)�� ��ȯ�Ͽ� ����ϱ� ���� �˰���
				type = postfix[i];
				value[i] = postfix[i];
				if (type == static_cast<int>(sign::MINUS)) {
					for (int j = i + 1; postfix[j] != NULL; j++)
					{
						if (postfix[j] == static_cast<char>(sign::SPACE))
							continue;
						if (Isnum(postfix[j]))
							type = static_cast<int>(sign::NEGATIVE);
						break;
					}
					if (type == static_cast<int>(sign::NEGATIVE)) {
						int tmp = i;
						for (i = i + 1; postfix[i] != NULL; i++)
						{
							if (postfix[i] == static_cast<char>(sign::SPACE))
								continue;
							value[++tmp] = postfix[i];
							if (!Isnum(postfix[i + 1]))
								break;
						}
					}
				}
				break;
			}
		}
		//���ڿ��� ������ �ε����� NULL�̹Ƿ� position�� ���ϱ� �� ������ �ε����� NULL�� �־��־�� �Ѵ�.
		value[++i] = '\0';
		return i;
	}
	//����ǥ����� ����ǥ������� ��ȯ�ϴ� �Լ�
	void Calculator::Get_post_fix(char* infixValue, char* postfixValue)
	{
		Stack _stack;
		Node* _popNode = nullptr;
		char* _value = (char*)malloc(strlen(infixValue) + 1);
		int _length = strlen(infixValue) + 1;
		int _type = -1;
		int _flag = 0;
		int _position = 0;

		while (_position < _length) {
			_position += Get_next_value(&infixValue[_position], _value, _type);
			if (_type == static_cast<int>(sign::SPACE) || _type == -1 || _type == NULL)
				continue;
			//�ǿ������̸� ����Ѵ�.
			if (_type == static_cast<int>(sign::OPERAND)) {
				_flag = 0;
				strcat(postfixValue, _value);
				strcat(postfixValue, " ");
			}
			else if (_type == static_cast<int>(sign::NEGATIVE)) {
				if (!_flag) {
					while (!_stack.Isempty() && Isprior(_stack.Get_top()->mdata[0], '+')) {
						_popNode = _stack.Pop();
						strcat(postfixValue, _popNode->mdata);
						strcat(postfixValue, " ");
						_stack.Destroy_node(_popNode);
					}
					_stack.Push(_stack.Create_stack((char*)"+"));
					_popNode = nullptr;
				}
				strcat(postfixValue, _value);
				strcat(postfixValue, " ");
				_flag = 0;
			}
			//������ ��ȣ�� ������
			else if (_type == static_cast<int>(sign::RIGHT_PARENTHESES)) {
				//���� ��ȣ�� ������ ������ ������ �����͵��� ������ �� ����ϰ�
				while (_stack.Get_top()->mdata[0] != (static_cast<int>(sign::LEFT_PARENTHESES))) {
					_popNode = _stack.Pop();
					strcat(postfixValue, _popNode->mdata);
					strcat(postfixValue, " ");
					_stack.Destroy_node(_popNode);
				}
				//���� ��ȣ�� ������ ��ȣ�� �����Ѵ�.
				_popNode = _stack.Pop();
				_stack.Destroy_node(_popNode);
				_popNode = nullptr;
			}
			//���� ���ڰ� �������̸�
			else {
				//������ ������� �ʰ�, ������ �ֻ�������� ���ڸ� ���ÿ��� ������ �� ����ϰ�
				_flag = 1;
				while (!_stack.Isempty() && Isprior(_stack.Get_top()->mdata[0], _value[0])) {
					_popNode = _stack.Pop();
					strcat(postfixValue, _popNode->mdata);
					strcat(postfixValue, " ");
					_stack.Destroy_node(_popNode);
				}
				//���� ���ڸ� ���ÿ� push�Ѵ�
				_stack.Push(_stack.Create_stack(_value));
				_popNode = nullptr;
			}
			//���� ����� ���� ������ �ʱ�ȭ�Ѵ�.
			memset(_value, 0, strlen(infixValue) + 1);
			_type = -1;
		}
		//���ÿ� ���� �����ڵ��� ����Ѵ�.
		while (!_stack.Isempty()) {
			_popNode = _stack.Pop();
			strcat(postfixValue, _popNode->mdata);
			strcat(postfixValue, " ");
			_stack.Destroy_node(_popNode);
		}
		//����� �� �� �� ������ �����.
		_stack.Destroy_stack();
		free(_value);
	}

	//����ǥ������� ��ȯ�� ������ ����ϴ� �Լ�
	double Calculator::Calculate(char* postfixvalue)
	{
		Stack _stack;
		char* _value = (char*)malloc(strlen(postfixvalue) + 1);
		int _position = 0;
		int _length = strlen(postfixvalue) + 1;
		int _type = -1;
		double _result = 0;
		char _strResult[51] = {};
		
		while (_length > _position) {
			_position += Get_next_value(&postfixvalue[_position], _value, _type);
			if (_type == -1 || _type == static_cast<int>(sign::SPACE) || _type == NULL)
				continue;
			//���� ���ڰ� ����(�ǿ�����)�̸�
			if (_type == static_cast<int>(sign::OPERAND) || _type == static_cast<int>(sign::NEGATIVE))
				//���ÿ� push�Ѵ�.
				_stack.Push(_stack.Create_stack(_value));
			//���� ���ڰ� �������̸�
			else {
				Node* _ntmp1 = _stack.Pop();
				Node* _ntmp2 = _stack.Pop();
				double _Rtmp = 0;
				//�������� Ÿ�Կ� ���� ���� �ֻ����� 2���� ���� ����Ѵ�.
				switch (_type) {
					case static_cast<int>(sign::MULTIPLY) : {
						_Rtmp = atof(_ntmp2->mdata) * atof(_ntmp1->mdata);
						break;
					}
					case static_cast<int>(sign::DIVIDE) : {
						_Rtmp = atof(_ntmp2->mdata) / atof(_ntmp1->mdata);
						break;
					}
					case static_cast<int>(sign::PLUS) : {
						_Rtmp = atof(_ntmp2->mdata) + atof(_ntmp1->mdata);
						break;
					}
					case static_cast<int>(sign::MINUS) : {
						_Rtmp = atof(_ntmp2->mdata) - atof(_ntmp1->mdata);
						break;
					}
				}
				//double������ ������ ������� char������ ��ȯ�Ѵ�.
				_gcvt(_Rtmp, 13, _strResult);
				//��ȯ�� ���� ���ÿ� push�Ѵ�.
				_stack.Push(_stack.Create_stack(_strResult));
				//_stack.Destroy_node(_ntmp1);
				//_stack.Destroy_node(_ntmp2);
			}
			memset(_value, ' ', strlen(postfixvalue) + 1);
			_type = -1;
		}
		//������� double������ ����Ѵ�.
		_result = atof(_stack.Pop()->mdata);
		free(_value);
		_stack.Destroy_stack();
		return _result;
	}
}