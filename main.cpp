#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

const int N = 3;
const int numWidth = 7;
const vector<pair<vector<vector<int>>, vector<vector<int>>>> AB =
    {
        {
            {{-1, 1, 1}, {-1, -1, -1}, {-2, 0, 0}}, // A1
            {{1, -1, -1}, {-2, 2, 0}, {1, -1, 1}}   // B1
        },
        {
            {{-1, 1, 1}, {2, -2, -2}, {-1, 1, 1}}, // A2
            {{0, -2, -2}, {-1, 3, 1}, {3, -3, -1}} // B2
        },
        {
            {{1, 1, 1}, {2, -2, -2}, {-1, 3, 3}},  // A3
            {{0, -2, -2}, {-1, 5, 3}, {3, -5, -3}} // B3
        },
        {
            {{1, 1, 1}, {-1, -3, -3}, {-2, 4, 4}},  // A4
            {{-1, -1, -1}, {-2, 6, 4}, {1, -7, -5}} // B4
        },
        {
            {{0, 0, 0}, {0, -4, -4}, {0, 4, 4}}, // A5
            {{-2, 0, 0}, {0, 6, 4}, {0, -8, -6}} // B5
        },
        {
            {{1, -1, -1}, {1, -3, -3}, {2, 4, 4}}, // A6
            {{-1, 1, 1}, {2, 6, 4}, {-1, -7, -5}}  // B6
        },
        {
            {{1, -1, -1}, {-2, -2, -2}, {1, 3, 3}}, // A7
            {{0, 2, 2}, {1, 5, 3}, {-3, -5, -3}}    // B7
        },
        {
            {{-1, -1, -1}, {-2, -2, -2}, {1, 1, 1}}, // A8
            {{0, 2, 2}, {1, 3, 1}, {-3, -3, -1}}     // B8
        },
        {
            {{-1, -1, -1}, {1, -1, -1}, {2, 0, 0}}, // A9
            {{1, 1, 1}, {2, 2, 0}, {-1, -1, 1}}     // B9
        }/*,
        {
            {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},          // A10
            {{2, 0, 0}, {0, 2, 0}, {0, 0, 2}}           // B10
        }*/
};

const vector<pair<vector<vector<int>>, vector<vector<int>>>> FG =
    {
        {
            {{-1, 1, -1}, {-1, -1, 1}, {2, 0, 0}}, // F1
            {{1, -1, 1}, {-2, 2, 0}, {-1, 1, 1}}   // G1
        },
        {
            {{-1, 1, -1}, {2, -2, 2}, {1, -1, 1}}, // F2
            {{0, -2, 2}, {-1, 3, -1}, {-3, 3, -1}} // G2
        },
        {
            {{1, 1, -1}, {2, -2, 2}, {1, -3, 3}},  // F3
            {{0, -2, 2}, {-1, 5, -3}, {-3, 5, -3}} // G3
        },
        {
            {{1, 1, -1}, {-1, -3, 3}, {2, -4, 4}},  // F4
            {{-1, -1, 1}, {-2, 6, -4}, {-1, 7, -5}} // G4
        },
        {
            {{0, 0, 0}, {0, -4, 4}, {0, -4, 4}}, // F5
            {{-2, 0, 0}, {0, 6, -4}, {0, 8, -6}} // G5
        },
        {
            {{1, -1, 1}, {1, -3, 3}, {-2, -4, 4}}, // F6
            {{-1, 1, -1}, {2, 6, -4}, {1, 7, -5}}  // G6
        },
        {
            {{1, -1, 1}, {-2, -2, 2}, {-1, -3, 3}}, // F7
            {{0, 2, -2}, {1, 5, -3}, {3, 5, -3}}    // G7
        },
        {
            {{-1, -1, 1}, {-2, -2, 2}, {-1, -1, 1}}, // F8
            {{0, 2, -2}, {1, 3, -1}, {3, 3, -1}}     // G8
        },
        {
            {{-1, -1, 1}, {1, -1, 1}, {-2, 0, 0}}, // F9
            {{1, 1, -1}, {2, 2, 0}, {1, 1, 1}}     // G9
        }/*,
        {
            {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},          // F10
            {{2, 0, 0}, {0, 2, 0}, {0, 0, 2}}           // G10
        }*/
};

vector<vector<int>> multiply(const vector<vector<int>> *a, const vector<vector<int>> *b)
{
    vector<vector<int>> result(N, vector<int>(N, 0));

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int sum = 0;
            for (int k = 0; k < N; k++)
                sum += (*a)[i][k] * (*b)[k][j];

            result[i][j] = sum;
        }
    }

    return result;
}

vector<vector<int>> add(const vector<vector<int>> *a, const vector<vector<int>> *b)
{
    vector<vector<int>> result(N, vector<int>(N, 0));

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            result[i][j] = (*a)[i][j] + (*b)[i][j];

    return result;
}
vector<vector<int>> add(const vector<vector<int>> *a, const vector<vector<int>> *b, const vector<vector<int>> *c)
{
    vector<vector<int>> result(N, vector<int>(N, 0));

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            result[i][j] = (*a)[i][j] + (*b)[i][j] + (*c)[i][j];

    return result;
}

// bool gotOddNumber = false;

void divide_by_2(vector<vector<int>> *a)
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            // if ((*a)[i][j] % 2 != 0)
            // {
            //     cout << "Attempt to divide the odd number by 2: " << (*a)[i][j] << endl;
            //     gotOddNumber = true;
            // }

            (*a)[i][j] /= 2;
        }
}

void calculate_by_formula(const vector<vector<int>> *a, const vector<vector<int>> *b,
                          const vector<vector<int>> *c, const vector<vector<int>> *d,
                          vector<vector<int>> *result1, vector<vector<int>> *result2)
{
    vector<vector<int>> ac = multiply(a, c);
    vector<vector<int>> ad = multiply(a, d);
    vector<vector<int>> bc = multiply(b, c);
    vector<vector<int>> bd = multiply(b, d);

    *result1 = add(&ac, &ad, &bc);
    *result2 = add(&ac, &bd);

    divide_by_2(result1);
    divide_by_2(result2);
}

void print_to_file(fstream *matrices, string pairHeader, const vector<vector<int>> *res1, const vector<vector<int>> *res2)
{
    (*matrices).clear();
    (*matrices).seekp(0, ios::end);

    (*matrices) << pairHeader << "\n{" << endl;

    for (int i = 0; i < N; i++)
    {
        (*matrices) << "\t[ ";

        for (int j = 0; j < N; j++)
            (*matrices) << setw(numWidth) << (*res1)[i][j] << (j < 2 ? ", " : " ]\t");

        (*matrices) << "\t[ ";

        for (int j = 0; j < N; j++)
            (*matrices) << setw(numWidth) << (*res2)[i][j] << (j < 2 ? ", " : " ]\n");
    }

    (*matrices) << "};" << endl << endl;
}

void read_pair(fstream *matrices, vector<vector<int>> *readTo1, vector<vector<int>> *readTo2)
{
    string line;

    getline((*matrices), line); // считать строку с открывающей скобкой '{'

    for (int i = 0; i < N; i++)
    {
        getline((*matrices), line);

        line = line.substr(3, line.length());
        for (int j = 0; j < N; j++)
        {
            (*readTo1)[i][j] = stoi(line.substr(0, numWidth));
            line = line.substr(numWidth + 2, line.length());
        }

        line = line.substr(4, line.length());
        for (int j = 0; j < N; j++)
        {
            (*readTo2)[i][j] = stoi(line.substr(0, numWidth));
            line = line.substr(numWidth + 2, line.length());
        }
    }

    getline((*matrices), line); // считать строку с закрывающей скобкой "};"
    getline((*matrices), line); // считать пустую строку
}

void search_for_duplicate(string pairHeader, fstream *matrices, ofstream *knownDuplicates, const vector<vector<int>> *res1, const vector<vector<int>> *res2)
{
    /*
                Идея для оптимизации
        для каждой пары матриц сначала искать самое длинное число, которое в неё входит
        (по модулю, наверное (тогда можно просто искать самое большое число, а потом взять его длину))
        (делать это удобнее в функции divide_by_two, чтоб не делать лишний пробег по обеим матрицам)
        содать какой-нибудь глобальный словарь (вроде это map), ключами которого являются длины чисел
        (1, 2, 3, 4, ...), а значениями ссылки на строки в matrices, начиная с которых
        появляются числа соответствующей длины
        тогда если у пары максимальное число длины t, то искать совпадения нужно начиная с той строки,
        с которой появляются числа длины t и до той строки, в которой появляются числа длины t+1
        (или до конца файла, если t - максимальная длина)
        чисел длины t+1 в паре матриц быть не может (т.к. тогда длина её самого длинного числа была бы t+1, а не t),
        а значит нет смысла смотреть те пары, в которых такие числа есть
        по обратному принципу отпадает необходимость проверять пары, максимальная длина числа в которых < t
        когда записываешь новую пару матриц в файл, максимальная длина числа может быть меньше, чем у предыдущей пары
        тогда надо сохранять ещё одну ссылку на максимальную длину или что? непонятно пока, что с этим делать
        надо придумать
    */

    string comparedPairHeader;
    vector<vector<int>> comparedM1(N, vector<int>(N));
    vector<vector<int>> comparedM2(N, vector<int>(N));
    bool isDuplicate;

    (*matrices).clear();
    (*matrices).seekg(0, ios::beg);

    while (getline((*matrices), comparedPairHeader) && comparedPairHeader != pairHeader)
    {
        isDuplicate = true;

        read_pair(matrices, &comparedM1, &comparedM2);

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if ((*res1)[i][j] != comparedM1[i][j] ||
                    (*res2)[i][j] != comparedM2[i][j])
                {
                    isDuplicate = false;
                    break;
                }
            }

            if (!isDuplicate)
                break;
        }

        if (isDuplicate)
        {
            (*knownDuplicates) << pairHeader.substr(0, pairHeader.length() - 2) << "  - копия  "
                               << comparedPairHeader.substr(0, comparedPairHeader.length() - 2) << endl
                               << endl;
            break;
        }
    }
}

void operate_on_length_two(fstream *matrices, ofstream *knownDuplicates)
{
    vector<vector<int>> a;
    vector<vector<int>> b;
    vector<vector<int>> f;
    vector<vector<int>> g;
    vector<vector<int>> res1, res2;

    string pairHeader;

    for (int i = 0; i < 9; i++)
    {
        a = AB[i].first;
        b = AB[i].second;

        for (int j = 0; j < 9; j++)
        {
            f = FG[j].first;
            g = FG[j].second;

            pairHeader = to_string(i + 1) + to_string(j + 1)  + " :";

            calculate_by_formula(&a, &b, &f, &g, &res1, &res2);
            print_to_file(matrices, pairHeader, &res1, &res2);
            search_for_duplicate(pairHeader, matrices, knownDuplicates, &res1, &res2);
        }
    }
}

int main()
{
    fstream matrices("matrices.txt", ios::in | ios::out | ios::trunc | ios::binary);
    ofstream knownDuplicates("knownDuplicates.txt", ios::trunc);
    matrices << setfill(' ');

    streampos readBegin = matrices.tellg();
    streampos nextReadBegin = matrices.tellg();
    streampos currentGetterPosition = matrices.tellg();

    string pairName;
    string basicMultiplierHeader;
    string currentMultiplierHeader;

    const vector<pair<vector<vector<int>>, vector<vector<int>>>> *basicMultiplier;
    vector<vector<int>> m1(N, vector<int>(N));
    vector<vector<int>> m2(N, vector<int>(N));
    vector<vector<int>> res1, res2;

    for (int l = 2; l <= 5; l++)
    {
        if (l == 2)
        {
            operate_on_length_two(&matrices, &knownDuplicates);
        }
        else
        {
            if (l % 2 == 1)
            {
                //указатель на AB
                basicMultiplier = &AB;
            }
            else
            {
                //указатель на FG
                basicMultiplier = &FG;
            }

            //матрицы начинают считываться с readBegin
            //пока не дойдём до nextReadBegin (не включая nextReadBegin)
            matrices.clear();
            matrices.seekg(readBegin);

            while (currentGetterPosition != nextReadBegin && getline(matrices, pairName))
            {
                pairName = pairName.substr(0, pairName.length() - 2);

                read_pair(&matrices, &m1, &m2);

                //    считали пару
                //    записали ссылку на текущую строку в переменную (currentGetterPosition)
                //    это будет строка с названием следующей пары
                currentGetterPosition = matrices.tellg();

                for (int i = 0; i < 9; i++)
                {
                    calculate_by_formula(&m1, &m2, &((*basicMultiplier)[i].first),
                                         &((*basicMultiplier)[i].second), &res1, &res2);

                    currentMultiplierHeader = to_string(i + 1) + " :";

                    print_to_file(&matrices, pairName + currentMultiplierHeader, &res1, &res2);
                    search_for_duplicate(pairName + currentMultiplierHeader, &matrices, &knownDuplicates, &res1, &res2);

                    //умножаем на (*basicMultiplier)[i].first, (*basicMultiplier)[i].second
                    //записываем в файл, ищем совпадения
                    //записывая в файл, нужно делать правильную строку с заголовком пары
                }
                matrices.clear();
                matrices.seekg(currentGetterPosition);
            }
        }

        //операции для этой длины закончены, записываем в readBegin nextReadBegin
        //записываем ссылку на конец файла в переменную nextReadBegin
        readBegin = nextReadBegin;
        matrices.clear();
        matrices.seekg(0, ios::end);
        nextReadBegin = matrices.tellg();
    }

    //тут конец программы
    //делаем все close() и т.п.
    matrices.close();
    knownDuplicates.close();
}