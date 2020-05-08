// Shrage.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include "Task.h"
#include <fstream>
#include <algorithm>
#include <vector>
#include "Heap.h"
#include "MinHeap.h"

using namespace std;

int cMax(vector<Task>& tasks)
{
    int m = 0;
    int c = 0;
    for (int i = 0; i < tasks.size(); i++)
    {
        m = max(m, tasks[i].r) + tasks[i].p;
        c = max(m + tasks[i].q, c);
    }
    return c;
}
int shrage(vector<Task>& tasks)
{
    int inputSize = tasks.size();
    vector<Task> result;
    Heap available(inputSize);
    MinHeap notAvailable(inputSize);
    for (int i = 0; i < inputSize; i++)
    {
        notAvailable.add(tasks[i]);
    }
    int t = 0;
    Task e;

    while (available.getSize()!=0 || notAvailable.getSize() != 0)
    {
        while (notAvailable.getSize() != 0 && notAvailable.top() <= t)
        {
            e = notAvailable.RemoveRoot();
            available.add(e);
        }
        if (available.getSize() == 0)
        {
            t = notAvailable.top();
        }
        else
        {
            e = available.RemoveRoot();
            result.push_back(e);
            t = t + e.p;
        }
    }
    return cMax(result);
}

int main()
{
    ifstream stream("schr.data.txt");  // Otwarcie pliku do odczytu
    double excecutionTime = 0;
    if (!stream)
    {
        cout << "BŁĄD: nie można otworzyć pliku do odczytu." << endl;
    }
    string data;
    string text;
    int tasksNumber;
    int temp;
    int p = 0;
    while (p!=9)
    {
        stream >> data;
        cout << data << endl;
        stream >> tasksNumber;
        vector<Task> tasks;
        Task task;
        for (int i = 0; i < tasksNumber; i++)
        {
            task.index = i;
            stream >> task.r;
            stream >> task.p;
            stream >> task.q;
            tasks.push_back(task);
        }
        cout << shrage(tasks) << endl;
        stream >> text; // schrmptn
        stream >> temp; // czas
        stream >> text; // schr
        stream >> temp; // czas
        for (int i = 0; i < tasksNumber; i++) // uporzadkowanie schr
        {
            stream >> temp;
        }
        p++;
    }
    system("pause");
    
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
