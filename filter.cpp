#include<fstream>
#include<string>

using namespace std;

bool is_increased_by_one(string checkedRecord, string comparedToRecord)
{
    string halfOfChecked = "";
    string halfOfcompared = "";

    int i = 0, j = 0;

    for (; i < checkedRecord.length(); i++)
    {
        if (checkedRecord[i] == ' ')
            break;

        halfOfChecked += checkedRecord[i];
    }
    for (; j < comparedToRecord.length(); j++)
    {
        if (comparedToRecord[i] == ' ')
            break;

        halfOfcompared += comparedToRecord[j];
    }

    if (stoi(halfOfChecked) != stoi(halfOfcompared) + 1)
        return false;

    halfOfChecked = "";
    halfOfcompared = "";

    for (i += 2; i < checkedRecord.length(); i++)
        halfOfChecked += checkedRecord[i];
    
    for (j += 2; j < checkedRecord.length(); j++)
        halfOfcompared += comparedToRecord[j];

    if (stoi(halfOfChecked) != stoi(halfOfcompared) + 1)
        return false;

    return true;
}

int main()
{
    ifstream knowDuplicates("knownDuplicates.txt");
    ofstream cut("cutKnownDuplicates.txt", ios::trunc);

    string firstRecord;
    string secondRecord;
    string ingoredLine;

    getline(knowDuplicates, firstRecord);
    cut << firstRecord << endl << endl;

    getline(knowDuplicates, ingoredLine);

    while (getline(knowDuplicates, secondRecord))
    {
        if (!is_increased_by_one(secondRecord, firstRecord))
            cut << secondRecord << endl << endl;
        
        firstRecord = secondRecord;
        getline(knowDuplicates, ingoredLine);
    }

    knowDuplicates.close();
    cut.close();
}
