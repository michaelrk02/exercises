#include <iostream>
using namespace std;

bool is_prime(int n)
{
	for (int i = 2; i < n; i++)
	{
		if (n % i == 0)
			return false;
	}
	return true;
}

bool is_near_prime(int n)
{
	if (is_prime(n)) return false;

	for (int i = 2; i < n; i++)
	{
		if (((n % i) == 0) && !is_prime(i))
			return false;
	}
	return true;
}

int main()
{
	int t; cin >> t;
	for (int i = 0; i < t; i++)
	{
		int a, b; cin >> a >> b;
		int c = 0;
		for (int i = a; i <= b; i++)
		{
			if (is_near_prime(i))
				c++;
		}
		cout << c << endl;
	}
	return 0;
}
