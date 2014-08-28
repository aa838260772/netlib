#include <iostream>
#include <string>
using namespace std;

int main(int argc, const char *argv[])
{
    string s;
    while(cin >> s)
    {
    cout << s <<endl;
    cout << "size:" << s.size() << endl;
    cout << "s[s.size() - 1]:" <<s[s.size() - 1] << endl;
    cout << "s[s.size() - 2]:" <<s[s.size() - 2] << endl;
    cout << "s[s.size() ]:" <<s[s.size() ] << endl;
    }
    return 0;
}
