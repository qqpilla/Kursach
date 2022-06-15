#include<fstream>
#include<string>
#include<iostream>

using namespace std;

string invert(string word)
{
    string inverted = "";
    for (int i = 0; i < word.length(); i++)
        inverted += (((10 - (word[i] - '0')) % 10) + '0'); 
    
    word = inverted;
    inverted = "";

    for (int i = word.length() - 1; i >= 0; i--)
        inverted += word[i];

    return inverted;
}

string shift_cyclically(string word, int step)
{
    string shifted = word.substr(step, word.length() - step) + word.substr(0, step);
    return shifted;
}

string collapse_zero(string word, int position) 
{
    char sum = '0';

    while (sum == '0')
    {
        if (word.length() < 3)
        {
            cout << "It's less than 3 digits: " << word << endl;
            break;
        }

        while (position == word.length() - 1 || position == 0)
        {
            word = shift_cyclically(word, 2);
            position = (position - 2 + word.length()) % word.length();
        }

        sum = (((word[position - 1] - '0') + (word[position + 1] - '0')) % 10) + '0';

        word.replace(position - 1, 3, 1, sum);
        position--;
    }

    return word;
}

string get_index(string record)
{
    string word1 = "";
    string word2 = "";
    bool signMet = false;
    bool zeroAdded = false;
    string longWord = "";
    int smallest;
    string smallestOf7;
    string smallestOf8;

    for (int i = 0; i < record.length(); i++)
    {
        if (record[i] == ' ')
        {
            signMet = true;
            i += 2;
            continue;
        }

        if (!signMet)
            word1 += record[i];
        else
            word2 += record[i];
    }

    // 1)
    if (word1.length() % 2 != word2.length() % 2)
    {
        word1 += '0';
        zeroAdded = true;
    }

    if (word2 == "3739")
        cout << "3739" << endl;

    // 2)
    word2 = invert(word2);

    // 3)  
    longWord = word1 + '0' + word2;
    
    // 4)
    if (zeroAdded)
        longWord.erase(word1.length() - 1, 2);
    // 5)
    else
        longWord = collapse_zero(longWord, word1.length());

    // 6)
    longWord.replace(0, 1, 1, (((longWord[0] - '0') + (longWord[longWord.length() - 1] - '0')) % 10) + '0');
    longWord.erase(longWord.length() - 1, 1);
    if (longWord[0] == '0')
        longWord = collapse_zero(longWord, 0);

    // 7)
    smallest = stoi(longWord);
    for (int i = 2; i < longWord.length(); i += 2)
    {
        int curCycle = stoi(shift_cyclically(longWord, i));
        if (smallest > curCycle)
            smallest = curCycle;
    }
    smallestOf7 = to_string(smallest); 
    // longWord = smallestOf7;

    // 8)
    longWord = invert(shift_cyclically(longWord, 1));
    smallest = stoi(longWord);
    for (int i = 2; i < longWord.length(); i += 2)
    {
        int curCycle = stoi(shift_cyclically(longWord, i));
        if (smallest > curCycle)
            smallest = curCycle;
    }
    smallestOf8 = to_string(smallest); 

    // 9)
    return smallestOf7 < smallestOf8 ? smallestOf7 : smallestOf8;
}

bool is_present(fstream *database, string index)
{
    (*database).clear();
    (*database).seekg(0, ios::beg);

    string compared;
    int pos = 0;

    while (getline(*database, compared))
    {
        while (compared[pos] != '-')
            pos++;

        pos += 3;
        if (index == compared.substr(pos, compared.length()))
            return true;

        pos = 0;
        getline(*database, compared);
    }

    return false;
}

int main()
{
    ifstream knownDuplicates("cutKnownDuplicates.txt");
    fstream database("indexedKnownDuplicates.txt", ios::in | ios::out | ios::trunc | ios::binary);

    string record;
    string recordIndex;

    while (getline(knownDuplicates, record))
    {
        recordIndex = get_index(record);

        if (!is_present(&database, recordIndex))
        {
            database.clear();
            database.seekp(0, ios::end);

            database << record << "  -  " << recordIndex << endl << endl;
        }
        

        getline(knownDuplicates, record);
    }

    knownDuplicates.close();
    database.close();
}