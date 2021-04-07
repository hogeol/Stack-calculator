#define _CRT_SECURE_NO_WARNINGS
#include <climits>
#include "Calculator.hpp"

namespace nStack {
	/*     우선순위는
		   *, / = 1순위
	*      +, - = 2순위
	*         ( = 3순위
	*      이다.
	*      우선순위는 이론적으로는 알고 있었으나, 우선순위를 구하는 함수를 구현하지 못하였습니다.
	*      우선순위 구하는 함수를 구현하기 힘들어서 구글검색에서 보고 했습니다. Isprior함수는 이해가 되지 않습니다.
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
	//스택에 있는 문자가 숫자(피연산자)인지 연산자인지 확인하는 함수
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
			//현재의 문자가 숫자(피연산자)인지 계산
			if (Isnum(postfix[i]) == true) {
				type = static_cast<int>(sign::OPERAND);
				value[i] = postfix[i];
				if (Isnum(postfix[i + 1]) == false)
					break;
			}
			else {
				//- 계산에 오류가 있어 NEGATIVE를 추가하여 음수값을 +(-X)로 변환하여 계산하기 위한 알고리즘
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
		//문자열의 마지막 인덱스는 NULL이므로 position을 구하기 전 마지막 인덱스에 NULL을 넣어주어야 한다.
		value[++i] = '\0';
		return i;
	}
	//중위표기식을 후위표기식으로 변환하는 함수
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
			//피연산자이면 출력한다.
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
			//오른쪽 괄호를 만나면
			else if (_type == static_cast<int>(sign::RIGHT_PARENTHESES)) {
				//왼쪽 괄호를 만나기 전까지 스택의 데이터들을 제거한 후 출력하고
				while (_stack.Get_top()->mdata[0] != (static_cast<int>(sign::LEFT_PARENTHESES))) {
					_popNode = _stack.Pop();
					strcat(postfixValue, _popNode->mdata);
					strcat(postfixValue, " ");
					_stack.Destroy_node(_popNode);
				}
				//왼쪽 괄호를 만나면 괄호를 삭제한다.
				_popNode = _stack.Pop();
				_stack.Destroy_node(_popNode);
				_popNode = nullptr;
			}
			//다음 문자가 연산자이면
			else {
				//스택이 비어있지 않고, 스택의 최상위노드의 문자를 스택에서 제거한 후 출력하고
				_flag = 1;
				while (!_stack.Isempty() && Isprior(_stack.Get_top()->mdata[0], _value[0])) {
					_popNode = _stack.Pop();
					strcat(postfixValue, _popNode->mdata);
					strcat(postfixValue, " ");
					_stack.Destroy_node(_popNode);
				}
				//다음 문자를 스택에 push한다
				_stack.Push(_stack.Create_stack(_value));
				_popNode = nullptr;
			}
			//다음 계산을 위해 변수를 초기화한다.
			memset(_value, 0, strlen(infixValue) + 1);
			_type = -1;
		}
		//스택에 남은 연산자들을 출력한다.
		while (!_stack.Isempty()) {
			_popNode = _stack.Pop();
			strcat(postfixValue, _popNode->mdata);
			strcat(postfixValue, " ");
			_stack.Destroy_node(_popNode);
		}
		//출력을 다 한 후 스택을 지운다.
		_stack.Destroy_stack();
		free(_value);
	}

	//후위표기식으로 변환한 수식을 계산하는 함수
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
			//현재 문자가 숫자(피연산자)이면
			if (_type == static_cast<int>(sign::OPERAND) || _type == static_cast<int>(sign::NEGATIVE))
				//스택에 push한다.
				_stack.Push(_stack.Create_stack(_value));
			//현재 문자가 연산자이면
			else {
				Node* _ntmp1 = _stack.Pop();
				Node* _ntmp2 = _stack.Pop();
				double _Rtmp = 0;
				//연산자의 타입에 따라 스택 최상위의 2개의 값을 계산한다.
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
				//double형으로 저장한 계산결과를 char형으로 변환한다.
				_gcvt(_Rtmp, 13, _strResult);
				//변환한 값을 스택에 push한다.
				_stack.Push(_stack.Create_stack(_strResult));
				//_stack.Destroy_node(_ntmp1);
				//_stack.Destroy_node(_ntmp2);
			}
			memset(_value, ' ', strlen(postfixvalue) + 1);
			_type = -1;
		}
		//결과값을 double형으로 출력한다.
		_result = atof(_stack.Pop()->mdata);
		free(_value);
		_stack.Destroy_stack();
		return _result;
	}
}