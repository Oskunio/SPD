// Shrage.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include "Task.h"
#include <fstream>
#include <algorithm>
#include <vector>
#include "Heap.h"
#include "MinHeap.h"
#include <queue>

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
int schrage(vector<Task>& tasks)
{
    int inputSize = tasks.size();
    int cmax = 0;
    vector<Task> result;
    Heap available(inputSize);
    MinHeap notAvailable(inputSize);
    for (int i = 0; i < inputSize; i++)
    {
        notAvailable.add(tasks[i]);

    }

    int t = 0;
    Task e;

    while (available.getSize() != 0 || notAvailable.getSize() != 0)
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
            cmax = max(cmax, t + e.q);
        }
    }

    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i].index + 1 << " ";
    }
    cout << endl;
    //return cMax(result);
    return cmax;
}

struct Rmniejsze
{
    bool operator()(Task& a, Task& b)
    {
        if (a.r > b.r)return true;
        if (a.r < b.r)return false;
        return false;
    }
};
struct Qwieksze
{
    bool operator()(Task& a, Task& b)
    {
        if (a.q < b.q)return true;
        if (a.q > b.q)return false;       
        return false;
    }
};
int schrage2(vector<Task>& tasks)
{
    priority_queue < Task, std::vector < Task >, Rmniejsze > N;
    priority_queue < Task, std::vector < Task >, Qwieksze > G;
    vector<Task> result;
    int t = 0;
    int cmax = 0;
    Task e;
    for (int i = 0; i < tasks.size(); i++)
    {
        N.push(tasks[i]);
    }
    while (!(N.empty()) || !(G.empty()))
    {
        while (!(N.empty()) && N.top().r <= t) {
            e = N.top();
            N.pop();
            G.push(e);
        }

        if (G.empty()) {
            t = N.top().r;
        }
        else
        {
            e = G.top();
            G.pop();
            result.push_back(e);
            t = t + e.p;
            cmax = max(cmax, t + e.q);
            
        }
       
    }
    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i].index + 1 << " ";
    }
    cout << endl;
    return cmax;
}
int schrmptn(vector<Task>& tasks)
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
    Task l;
    l.r = 0;
    l.p = 0;
    l.q = 9999999999;
    l.index = 0;

    while (available.getSize() != 0 || notAvailable.getSize() != 0)
    {
        while (notAvailable.getSize() != 0 && notAvailable.top() <= t)
        {
            e = notAvailable.RemoveRoot();
            available.add(e);
            if (e.q > l.q)
            {
                l.p = t - e.r;
                t = e.r;
                if (l.p > 0)
                {
                    available.add(l);
                    result.pop_back();
                }
            }
        }
        if (available.getSize() == 0)
        {
            t = notAvailable.top();
        }
        else
        {
            e = available.RemoveRoot();
            result.push_back(e);
            l = e;
            t = t + e.p;
            
        }
    }
    return cMax(result);
}
int schrmptn2(vector<Task>& tasks)
{
    priority_queue < Task, std::vector < Task >, Rmniejsze > N;
    priority_queue < Task, std::vector < Task >, Qwieksze > G;
    vector<Task> result;
    int t = 0;
    int cmax = 0;
    Task e;
    Task l;
    l.r = 0;
    l.p = 0;
    l.q = 9999999999;
    l.index = 0;
    for (int i = 0; i < tasks.size(); i++)
    {
        N.push(tasks[i]);
    }
    while (!(N.empty()) || !(G.empty()))
    {
        while (!(N.empty()) && N.top().r <= t) {
            e = N.top();
            N.pop();
            G.push(e);
            if (e.q > l.q)
            {
                l.p = t - e.r;
                t = e.r;
                if (l.p > 0)
                {
                    G.push(l);
                    result.pop_back();
                }
            }
        }

        if (G.empty()) {
            t = N.top().r;
        }
        else
        {
            e = G.top();
            G.pop();
            result.push_back(e);
            t = t + e.p;
            l = e;
            cmax = max(cmax, t + e.q);

        }

    }
    
    return cmax;
}

int main()
{
    ifstream stream("schr.data3.txt");  // Otwarcie pliku do odczytu
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
    while (p!=1)
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
        int shrageBez, shrageZ;
        shrageBez = schrage(tasks);
        shrageZ = schrmptn2(tasks);
        cout << "shrage z podzialem:" << shrageZ << endl;
        cout << "shrage bez podzialu:"<< shrageBez << endl;
        
        stream >> text; // schrmptn
        stream >> temp; // czas
        if (shrageZ != temp) cout << "Zly wynik shrage z podzialem !!!!!!!!!!!" << endl;
        stream >> text; // schr
        stream >> temp; // czas
        if (shrageBez != temp) cout << "Zly wynik shrage bez podzialu !!!!!!!!!!!" << endl;
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
