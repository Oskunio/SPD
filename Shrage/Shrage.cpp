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
#include <chrono>

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
    int time1 = 0, time2 = 0, time3 = 0, time4 = 0;
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
        int schrageBez, schrageZ, schrageBez2, schrageZ2;
        

        auto start = std::chrono::steady_clock::now();
        schrageBez = schrage(tasks);
        auto end = std::chrono::steady_clock::now();
        double elapsed_seconds = double(std::chrono::duration_cast <std::chrono::nanoseconds>(end - start).count());
        cout << "schrage bez podzialu (kopiec): " << schrageBez << " | Czas: "<< elapsed_seconds / 1e9<<" s" << endl;
        time1 += elapsed_seconds;

        start = std::chrono::steady_clock::now();
        schrageBez2 = schrage2(tasks);
        end = std::chrono::steady_clock::now();
        elapsed_seconds = double(std::chrono::duration_cast <std::chrono::nanoseconds>(end - start).count());
        cout << "schrage bez podzialu (kolejka): " << schrageBez2 << " | Czas: " << elapsed_seconds / 1e9 << " s" << endl;
        time2 += elapsed_seconds;

        start = std::chrono::steady_clock::now();
        schrageZ = schrmptn(tasks);
        end = std::chrono::steady_clock::now();
        elapsed_seconds = double(std::chrono::duration_cast <std::chrono::nanoseconds>(end - start).count());
        cout << "schrage z podzialem (kopiec): " << schrageZ << " | Czas: " << elapsed_seconds / 1e9 << " s" << endl;
        time3 += elapsed_seconds;

        start = std::chrono::steady_clock::now();
        schrageZ2 = schrmptn2(tasks);
        end = std::chrono::steady_clock::now();
        elapsed_seconds = double(std::chrono::duration_cast <std::chrono::nanoseconds>(end - start).count());
        cout << "schrage z podzialem (kolejka): " << schrageZ2 << " | Czas: " << elapsed_seconds / 1e9 << " s" << endl;
        time4 += elapsed_seconds;

        stream >> text; // schrmptn
        stream >> temp; // czas
        //if (shrageZ != temp) cout << "Zly wynik shrage z podzialem !!!!!!!!!!!" << endl;
        stream >> text; // schr
        stream >> temp; // czas
        //if (shrageBez != temp) cout << "Zly wynik shrage bez podzialu !!!!!!!!!!!" << endl;
        for (int i = 0; i < tasksNumber; i++) // uporzadkowanie schr
        {
            stream >> temp;
        }
        p++;
    }
    cout << endl;
    cout << "Calkowity czas schrage bez podzialu (kopiec): " << time1 / 1e9 << " s" << endl;
    cout << "Calkowity czas schrage bez podzialu (kolejka): " << time2 / 1e9 << " s" << endl;
    cout << "Calkowity czas schrage z podzialem (kopiec): " << time3 / 1e9 << " s" << endl;
    cout << "Calkowity czas schrage z podzialem (kolejka): " << time4 / 1e9 << " s" << endl;
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
