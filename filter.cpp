#include<fstream>
#include<string>
#include<iostream>

using namespace std;

int add_one(string num)
{
    if (num[num.length() - 1] == '9')
    {
        num[num.length() - 1] = '0';
        return stoi(num);
    }

    return stoi(num) + 1;
}

bool is_increased_by_one(string checkedRecord, string comparedToRecord)
{
    if (comparedToRecord == "991 = 719")
    {
        cout << "hello";
    }

    string halfOfChecked = "";
    string halfOfCompared = "";

    int i = 0, j = 0;

    for (; i < checkedRecord.length(); i++)
    {
        if (checkedRecord[i] == ' ')
            break;

        halfOfChecked += checkedRecord[i];
    }
    for (; j < comparedToRecord.length(); j++)
    {
        if (comparedToRecord[j] == ' ')
            break;

        halfOfCompared += comparedToRecord[j];
    }

    if (halfOfCompared.length() == halfOfChecked.length() + 1)
        halfOfChecked += '0';
    else if (halfOfCompared.length() + 1 == halfOfChecked.length())
        halfOfCompared += '0';

    if (stoi(halfOfChecked) != add_one(halfOfCompared))
        return false;

    halfOfChecked = "";
    halfOfCompared = "";
    i += 3;
    j += 3;

    for (; i < checkedRecord.length(); i++)
        halfOfChecked += checkedRecord[i];
    
    for (; j < comparedToRecord.length(); j++)
        halfOfCompared += comparedToRecord[j];

    if (halfOfCompared.length() == halfOfChecked.length() + 1)
        halfOfChecked += '0';
    else if (halfOfCompared.length() + 1 == halfOfChecked.length())
        halfOfCompared += '0';

    if (stoi(halfOfChecked) != add_one(halfOfCompared))
        return false;

    return true;
}

int main()
{
    ifstream knowDuplicates("fixedKnownDuplicates.txt");
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
