#include <iostream>
#include <string>

using namespace std;

void print_zigzag(string s, int width)
{
    int r = 1;
    int len = s.length() + ((s.length() % width == 0) ? 0 : width - (s.length() % width));
    for (int i = 0; i < len; i++)
    {
        if ((i != 0) && (i % width == 0))
        {
            r++;
            cout << endl;
        }

        int n;
        if (r % 2 != 0)
        { // odd, print normally
            n = i;
        }
        else
        { // even, print reversed
            int start = (r - 1) * width;
            int stop = start + width - 1;
            n = stop - (i - start);
        }
        if (i > s.length() - 1)
        {
            cout << ' ';
        }
        else
        {
            cout << s[n];
        }
    }
    cout << endl;
}

int main()
{
    string s;
    cout << "Press ENTER to start, press Ctrl+C to exit";
    while (true)
    {
        cin.ignore();
        cout << "Input: ";
        getline(cin, s);

        int w;
        cout << "Width: ";
        cin >> w;

        cout << "Output:" << endl;
        print_zigzag(s, w);
    }
    return 0;
}
