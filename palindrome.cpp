// palindrome of number;
#include <iostream>
using namespace std;
int main()
{
    int n, r, sum = 0, temp;
    cout << "enter the number=";
    cin >> n;
    temp = n;
    while (n > 0)
    {
        r = n % 10;
        sum = (sum * 10) + r;
        n = n / 10;
    }
    if (temp == sum)
        cout << "number is palindrome,";
    else
        cout << "number is not palindrome,";
    return 0;
}
