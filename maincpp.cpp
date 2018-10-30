//Andre Barajas
//Professor Gold
//November 2017
//CECS 282
//Project5 BigInt class
//Program will compute large numbers past  2 billion a vector  container. 

#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;
#include <string>
#include <iostream>

#include <exception>
class BigInt
{
private:
	vector<int> storage;
	// I needed these next 2 functions but you may or may not need them depending how you implement your class
	//void borrow(BigInt &, int); // I used this in the subtraction function
	 // you need to make sure you don't have a number like this: '0123";
public:
	BigInt();
	BigInt(int);
	BigInt(string);
	void operator++(int);
	bool operator<=(const BigInt)const;
	bool operator==(int) const;
	bool operator==(const BigInt )const;
	BigInt operator-(BigInt);
	BigInt operator-(int);
	BigInt operator+(BigInt);
	bool operator<(const BigInt &) const;  // this is required for the map
	bool operator<(int) const;
	friend ostream &operator<<(ostream &,  BigInt &);
	BigInt& operator=(BigInt& c);
	BigInt stripLeadingZero();
};



using std::overflow_error;
BigInt GoldRabbits(BigInt bigN);
int fact(int n);

int main()
{
	BigInt bigX(28675), bigY("46368"), bigResult;

	bigResult = bigX + bigY;
	cout << bigX << "+" << bigY << "=" << bigResult;
	getchar(); // pause

	for (BigInt n = 0; n <= 1000; n++)
	{
		cout << (n<950 ? "\n" : "\n\n") << "The GoldRabbit of (" << n << ") is " << GoldRabbits(n);
		if (n == 30) // pause at 30
			getchar();

	}

	getchar();

	for (int i = 0; i<20; i++)
	{
		try 
		{
			cout << "Fact(" << i << "):" << fact(i) << endl;
		}
		catch (overflow_error &e)
		{
			cout << "Fact(" << i << "):" << "Overflow" << endl;
		}		
	}
	getchar();
	
	
	return 0;
}

int fact(int n)
{
	int a = n;
	
	if (n == 0)
		return 1;
	else 
	{
		int b = fact(n - 1);
		int z = a * b;
		if (b != z / a) {
			throw overflow_error("notvalid");
		}
		else {
			return z;
		}
	}
}
BigInt GoldRabbits(BigInt bigN)
{
	static map<BigInt, BigInt> fiboMap;

	
		if (bigN == 0 || bigN == 1)
		{
			return BigInt(1);
		}
		if (fiboMap.find(bigN) != fiboMap.end() )		{
			return fiboMap.at(bigN);
		}
		else
		{
			BigInt x = GoldRabbits(bigN - 1);
			BigInt y = GoldRabbits(bigN - 2);
			BigInt v =  x + y;
			fiboMap[bigN] = v;
			return v;
		}
	}

BigInt :: BigInt()
{
	storage.push_back(0);
}
BigInt BigInt :: stripLeadingZero() //BigInt& bigN
{
	BigInt temp;
	if (this->storage.size() > 1)
	{
		vector<int>::iterator it2;
		bool strip = true;
		for (it2 = this->storage.begin(); it2 != this->storage.end(); it2++)
		{
			int numb = *it2;
			if (strip)
			{
				if (numb == 0) {}
				else
				{
					strip = 0;
					temp.storage.at(0) = numb;
				}
			}
			else { temp.storage.push_back(numb); }
		}
		// std::reverse(temp.storage.begin(), temp.storage.end());

		*this = temp;

	}
	return temp;
}
BigInt :: BigInt(int n)
{
	std::string num = std::to_string(n);

	if (n < 9) { storage.push_back(n); }
	else
		for (int i = 0; i < num.length(); i++)
		{
			int num0 = num.at(i) - '0';
			storage.push_back(num0);
		}
}

BigInt::BigInt(string bigS)
{
	for (int i = 0; i < bigS.length(); i++)
	{
		int num0 = bigS.at(i) - '0';
		storage.push_back(num0);
	}
}
BigInt& BigInt ::operator= (BigInt& c)
{
	if (this != &c) //test the address of both objects
	{
		vector<int>::iterator it;
		this->storage.clear();
		for (it = c.storage.begin(); it != c.storage.end(); it++)
		{
			this->storage.push_back(*it);
		}
	}
	return *this;
}

bool BigInt :: operator<(int x) const
{
	BigInt bigN(x);
	bool equal = false;
	vector<int>::const_iterator it2;
	vector<int>::const_iterator it3;
	vector<int>::const_iterator it4;
	if (this->storage.size() > bigN.storage.size())
	{
		equal = false;
	}
	else if (this->storage.size() < bigN.storage.size())
	{
		equal = true;
	}
	else
	{
		it2 = this->storage.begin();
		it3 = bigN.storage.begin();
		it4 = this->storage.end();
	}
	bool greater = false;
	for (it2; it2 < it4; it2++)
	{
		if (equal == false && greater != true)
		{
			if (*it2 < *it3)
			{
				equal = true;
			}
			else if (*it2 > *it3) { greater = true; }
		}
		it3++;
	}
	return equal;
}
bool BigInt :: operator<(const BigInt& bigN) const
{
	bool equal = false;
	vector<int>::const_iterator it2;
	vector<int>::const_iterator it3;
	vector<int>::const_iterator it4;
	if (this->storage.size() > bigN.storage.size())
	{
		equal = false;
	}
	else if (this->storage.size() < bigN.storage.size())
	{
		equal = true;
	}
	else
	{
		it2 = this->storage.begin();
		it3 = bigN.storage.begin();
		it4 = this->storage.end();
	}
	bool greater = false;
	for (it2; it2 < it4; it2++)
	{
		if (equal == false && greater != true)
		{
			if (*it2 < *it3)
			{
				equal = true;
			}
			else if (*it2 > *it3) { greater = true; }
		}
		it3++;
	}
	return equal;
}

bool BigInt :: operator==(int x) const
{
	BigInt bigN(x);
	bool equal0 = false;
	bool equal1 = true;
	vector<int>::const_iterator it2;
	vector<int>::const_iterator it3;
	vector<int>::const_iterator it4;
	if (this->storage.size() > bigN.storage.size())
	{

		equal1 = false;
	}
	else if (this->storage.size() < bigN.storage.size())
	{
		equal1 = false;
	}
	else
	{
		it2 = this->storage.begin();
		it3 = bigN.storage.begin();
		it4 = this->storage.end();
	}
	bool greater = false;
	for (it2; it2 < it4; it2++)
	{
		if (equal0 == false && greater != true)
		{
			if (*it2 < *it3)
			{
				equal1 = false;
			}
			else if (*it2 > *it3) { greater = true; equal1 = false; }
		}
		it3++;
	}
	if (equal1) { equal0 = true; }
	return equal0;
}

bool BigInt :: operator==(const BigInt bigN) const
{
	bool equal0 = false;
	bool equal1 = true;
	vector<int>::const_iterator it2;
	vector<int>::const_iterator it3;
	vector<int>::const_iterator it4;
	if (this->storage.size() > bigN.storage.size())
	{

		equal1 = false;
	}
	else if (this->storage.size() < bigN.storage.size())
	{
		equal1 = false;
	}
	else
	{
		it2 = this->storage.begin();
		it3 = bigN.storage.begin();
		it4 = this->storage.end();
	}
	bool greater = false;
	for (it2; it2 < it4; it2++)
	{
		if (equal0 == false && greater != true)
		{
			if (*it2 < *it3)
			{
				equal1 = false;
			}
			else if (*it2 > *it3) { greater = true; equal1 = false; }
		}
		it3++;
	}
	if (equal1) { equal0 = true; }
	return equal0;
}
bool BigInt :: operator<=(const BigInt bigN)const
{
	bool equal0 = false;
	bool equal1 = true;
	vector<int>::const_iterator it2;
	vector<int>::const_iterator it3;
	vector<int>::const_iterator it4;
	if (this->storage.size() > bigN.storage.size())
	{
		equal0 = false;
		equal1 = false;
	}
	else if (this->storage.size() < bigN.storage.size())
	{
		equal0 = true;
		equal1 = true;
	}
	else
	{
		it2 = this->storage.begin();
		it3 = bigN.storage.begin();
		it4 = this->storage.end();
	}
	bool greater = false;
	for (it2; it2 < it4; it2++)
	{
		if (equal0 == false && greater != true)
		{
			if (*it2 < *it3)
			{
				equal0 = true;
				equal1 = false;
			}
			else if (*it2 > *it3) { greater = true; equal1 = false; }
		}
		it3++;
	}
	if (equal1) { equal0 = true; }
	return equal0;
}

BigInt BigInt :: operator-(int n)
{
	BigInt temp(*this);
	return (temp - BigInt(n));
	//return (*this - BigInt(n)); //freebi
}
BigInt BigInt :: operator-(BigInt bigN)
{

	BigInt temp;
	if ((*this).storage.size() == 1 && bigN.storage.size() == 1)
	{
		temp = BigInt(this->storage.at(0) - bigN.storage.at(0));
	}
	else
	{
		if (bigN == *this) {}// do nothing to return temp which is zero
		else
		{
			vector<int>::reverse_iterator it2;
			vector<int>::reverse_iterator it3;
			vector<int>::reverse_iterator it4;

			int carry = 0;
			int x;

			if (this->storage.size() > bigN.storage.size())
			{
				it2 = this->storage.rbegin();

				it4 = this->storage.rend();
				std::reverse(bigN.storage.begin(), bigN.storage.end());
				int stop = this->storage.size() - bigN.storage.size();
				for (int i = 0; i < stop; i++)
				{
					bigN.storage.push_back(0);
				}
				std::reverse(bigN.storage.begin(), bigN.storage.end());
				it3 = bigN.storage.rbegin();
			}
			else if (this->storage.size() < bigN.storage.size())
			{

				it2 = bigN.storage.rbegin();
				it4 = bigN.storage.rend();
				std::reverse(this->storage.begin(), this->storage.end());
				int stop = bigN.storage.size() - this->storage.size();
				for (int i = 0; i < stop; i++)
				{
					this->storage.push_back(0);
				}
				std::reverse(this->storage.begin(), this->storage.end());
				it3 = this->storage.rbegin();
			}
			else
			{
				it2 = this->storage.rbegin();
				it3 = bigN.storage.rbegin();
				it4 = this->storage.rend();
			}
			bool is = false;
			for (it2; it2 != it4; it2++)
			{
				int y;

				if (is)
				{
					*it2 = *it2 - 1;
				}

				if (*it2 < *it3)
				{
					y = ((*it2 + 10) - *it3);
					is = true;
					if (it2 == this->storage.rbegin())
					{
						temp.storage.at(0) = y;
					}
					else
					{
						temp.storage.push_back(y);
					}
				}
				else
				{
					y = (*it2 - *it3);
					is = false;
					if (it2 == this->storage.rbegin())
					{
						temp.storage.at(0) = y;
					}
					else
					{
						temp.storage.push_back(y);
					}
				}

				it3++;

			}
			std::reverse(temp.storage.begin(), temp.storage.end());
			temp.stripLeadingZero();
		}
	}
	return temp;
}

void BigInt::operator++(int)
{

	*this = *this + BigInt(1);
}
BigInt BigInt:: operator+(BigInt bigN)
{
	//(28675), bigY("46268")

	BigInt temp;
	if ((*this).storage.size() == 1 && bigN.storage.size() == 1)
	{
		temp = BigInt(this->storage.at(0) + bigN.storage.at(0));
	}
	else
	{
		vector<int>::reverse_iterator it2;
		vector<int>::reverse_iterator it3;
		vector<int>::reverse_iterator it4;
		int carry = 0;
		int x;

		if (this->storage.size() > bigN.storage.size())
		{

			int stop = this->storage.size() - bigN.storage.size();

			std::reverse(bigN.storage.begin(), bigN.storage.end());
			for (int i = 0; i < stop; i++)
			{
				bigN.storage.push_back(0);
			}
			std::reverse(bigN.storage.begin(), bigN.storage.end());
			it2 = this->storage.rbegin();
			it4 = this->storage.rend();
			it3 = bigN.storage.rbegin();
		}
		else if (this->storage.size() < bigN.storage.size())
		{
			int stop = bigN.storage.size() - this->storage.size();

			std::reverse(this->storage.begin(), this->storage.end());
			for (int i = 0; i < stop; i++)
			{
				this->storage.push_back(0);
			}
			std::reverse(this->storage.begin(), this->storage.end());
			it2 = this->storage.rbegin();
			it3 = bigN.storage.rbegin();
			it4 = this->storage.rend();

		}
		else
		{

			it2 = this->storage.rbegin();
			it3 = bigN.storage.rbegin();
			it4 = this->storage.rend();
		}
		bool carryd = false;
		for (it2; it2 != it4; it2++)
		{
			x = *it2 + *it3 + carry;
			if (x > 9)
			{
				std::string num = std::to_string(x);
				int num0 = num.at(1) - '0';
				if (it2 == this->storage.rbegin())
				{
					temp.storage.at(0) = num0;
				}
				else
				{
					temp.storage.push_back(num0);
				}
				int num1 = num.at(0) - '0';
				carry = num1;
				carryd = true;
			}
			else
			{
				if (it2 == this->storage.rbegin())
				{
					temp.storage.at(0) = x;
				}
				else
				{
					temp.storage.push_back(x);
					carry = 0;
					carryd = false;
				}
			}
			it3++;
		}
		if (carry) { temp.storage.push_back(carry); }

		std::reverse(temp.storage.begin(), temp.storage.end());
	}
	return temp;
}
 ostream& operator<<(ostream& out,  BigInt& bigN)
{
	vector<int>::iterator it;

	for (it = bigN.storage.begin(); it != bigN.storage.end(); it++)
	{
		out << *it;
	}
	return out;
}
