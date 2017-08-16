#include <bits/stdc++.h>

using namespace std;

/* Grammar
 * E  -> TE'
 * E' -> +TE'
 *     | eps
 * T  -> FT'
 * T' -> *FT'
 *     | eps
 * F  -> (E)
 *     | i
 *
 * Sample input: ((i*i)+i)*i
 */

int it = 0;
string input;
string error = "extra characters";

bool S();
bool L();
bool L1();
bool alphaNum();
bool alphaNum1();
bool alphaNum11();
bool digit();
bool letter();

bool match(char c)
{
	if(input[it] == c) return true;
	return false;
}

bool isDigit(int it)
{
	char c = input[it];
	if(c >= '0' && c <= '9') return true;
	return false;
}

bool isLetter(int it)
{
	char c = input[it];
	if(c >= 'a' && c <= 'z') return true;
	return false;
}

bool S()
{
	bool ret = false;
	if(match('(')) {
		it++;
		ret = L();
		if(match(')')) {
			it++;
		}
		else {
			ret = false;
			error = "missing closing parenthesis";
		}
	}
	else if(isDigit(it) || isLetter(it)) {
		ret = alphaNum();
	}
	else error = "missing opening parenthesis";

	return ret;
}

bool L()
{
	bool ret = true;
	ret = ret && S();
	ret = ret && L1();
	return ret;
}

bool L1()
{
	bool ret = true;
	if(match(',')) {
		it++;
		ret = ret && S();
		ret = ret && L1();
	}
	return ret;
}

bool alphaNum()
{
	bool ret = true;
	if(isDigit(it) || isLetter(it)) {
		it++;
		ret = alphaNum11();
	}
	return ret;
}

bool alphaNum1()
{
	bool ret = true;
	if(isDigit(it) || isLetter(it)) {
		it++;
	}
	return ret;
}

bool alphaNum11()
{
	bool ret = true;
	if(isDigit(it) || isLetter(it)) {
		it++;
		ret = alphaNum11();
	}
	return ret;
}

int main()
{
	cout << "Enter a string to parse: ";
	cin >> input;

	if(S() && it == input.size()) cout << "Accepted!" << endl;
	else {
		cout << "Syntax error!" << endl;
		cout << error << endl;
	}

	return 0;
}
