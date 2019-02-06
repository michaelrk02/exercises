#include <iostream>
using namespace std;

int main()
{
	int n; cin >> n;
	char c; cin >> c;
	int x; cin >> x;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if ((j == i) || (j == n-i+1))
			{
				cout << x;
			}
			else
			{
				cout << c;
			}
		}
		cout << endl;
	}
	return 0;
}
