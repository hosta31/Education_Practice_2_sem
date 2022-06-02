#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

vector<string> linesToWords(list<string>& lines) // перевод строк в слова
{
    vector <string> result;
    string bufferString;
    for (string str : lines)
    {
        for (char symbol : str)
        {
            if ((isalnum(symbol)) || (symbol == '\'') || ((symbol == '-')&&(bufferString.length() != 0)))
            {
                bufferString += symbol;
            }
            else
            {
                if (bufferString.length() != 0)
                {
                    result.push_back(bufferString);
                    bufferString = "";
                }
            }
        }
        if (bufferString.length() != 0)
        {
            result.push_back(bufferString);
            bufferString = "";
        }
    }
    return result;
}

const double FACTOR = 1.2473309;

void combSort(vector<string> &words) // сортировка расческой
{
    int N = words.size(); 
    int i=N-1;
    string buffer;
    while (i > 0)
    {
        for (int j = 0; j < N - i; j++)
        {
            if (words[j].size() < words[j + i].size())
            {
                buffer = words[j];
                words[j] = words[j + i];
                words[j + i] = buffer;
            }
        }
        i /= FACTOR;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    list<string> lines;
    string filePath;
    cin >> filePath;
    ifstream fileIn(filePath + "/fileIn.txt");//C:/Users/79818/Desktop/UchPr
    ofstream fileOutAnalysis(filePath + "/analysis.txt");
    fileOutAnalysis << "Введенный текст: \n";
    cout << "Введенный текст: \n";
    string bufferLine;
    while (!fileIn.eof())
    {
        getline(fileIn, bufferLine);
        lines.push_back(bufferLine);
        fileOutAnalysis << bufferLine << '\n';
        cout << bufferLine << '\n';
    }
    fileIn.close();

    vector<string> words = linesToWords(lines); 

    double start_time = clock();
    combSort(words);
    double end_time = clock();
    double search_time = ((double)(end_time - start_time)) / (double)CLOCKS_PER_SEC;
    //for (int i = 0; i < words.size(); i++) cout << words[i].length() << ' ';

    fileOutAnalysis << "\n\nВариант 14: латиница, по кол-ву символов в слове, по убыванию, учитывать числа, сортировка Расческой\nКоличество слов: " << words.size();
    cout << "\n\nВариант 14: латиница, по кол-ву символов в слове, по убыванию, учитывать числа, сортировка Расческой\nКоличество слов: " << words.size();
    fileOutAnalysis << "\nВремя сортировки: " << search_time << " сек\nСтатистика (количество слов каждой длины)\n";
    cout << "\nВремя сортировки: " << search_time << " сек\nСтатистика (количество слов каждой длины)\n";
    ofstream fileOutResult(filePath + "/result.txt");

    int j = 0, counter;
    for (int i = words[0].length(); i > 0; i--)
    {
        counter = 0;
        fileOutAnalysis << i << " - ";
        cout << i << " - ";
        while ((j != words.size()) &&  (words[j].length() == i))
        {
            fileOutResult << words[j++] << ' ';
            counter++;
        }
        fileOutAnalysis << counter << '\n';
        cout << counter << '\n';
        if (counter != 0) 
            fileOutResult << '\n';
    }

    fileOutAnalysis.close();
    fileOutResult.close();
    return 0;
}
