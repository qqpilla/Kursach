#include<fstream>
#include<string>

using namespace std;

int main()
{
    ifstream knowDuplicates("knownDuplicates.txt");
    ofstream fixed("fixedKnownDuplicates.txt");

    string line;
    string res, h1, h2, mid1, mid2;

    while (getline(knowDuplicates, line))
    {
        knowDuplicates >> h1 >> mid1 >> mid2 >> h2;
        res = h1 + " = " + h2;

        fixed << res << endl << endl;
    }

    knowDuplicates.close();
    fixed.close();
}