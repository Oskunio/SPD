// Calier.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <vector>
#include "Task.h"
#include <queue>
#include <fstream>


using namespace std;

struct Dane {
    string numerDanych;
    vector<Task> tasks;
    int optimal;
    vector<int> optimalOrder;
};

struct SchrageResult {
    int cmax;
    vector<Task> result;
};


SchrageResult schrmptn2(vector<Task>& tasks);

int main()
{
    fstream dane;
    dane.open("carl.data.txt", ios::in);
    string data = "";
    int tasksNumber;
    vector<Dane> VectorOfDane;
    if (!dane)
    {
        cout << "BŁĄD: nie można otworzyć pliku do odczytu." << endl;
    }
    while(!dane.eof()) {
        vector<Task> tasks;
        Dane singleDane;
        dane >> data;
        singleDane.numerDanych = data[5];
        dane >> tasksNumber;
        Task task;
        for (int i = 0; i < tasksNumber; i++)
        {
            task.index = i;
            dane >> task.r;
            dane >> task.p;
            dane >> task.q;
            tasks.push_back(task);
        }
        vector<int> optOrder;
        singleDane.tasks = tasks;
        dane >> data;
        dane >> singleDane.optimal;
        int number;
        for (int i = 0; i < tasksNumber; i++) {
            dane >> number;
            optOrder.push_back(number);
        }
        singleDane.optimalOrder = optOrder;
        VectorOfDane.push_back(singleDane);
    }
    for (int i = 0; i < VectorOfDane.size(); i++) {
        cout<<"\nDane numer: "<<VectorOfDane[i].numerDanych<<endl;
        cout << "# R P Q"<<endl;
        for (int j = 0; j < VectorOfDane[i].tasks.size(); j++) {
            cout << "#" << VectorOfDane[i].tasks[j].index+1 << " " << VectorOfDane[i].tasks[j].r << " " << VectorOfDane[i].tasks[j].p << " " << VectorOfDane[i].tasks[j].q << endl;
        }
        SchrageResult schrageResult = schrmptn2(VectorOfDane[i].tasks);
        cout << "Schrage result: " << schrageResult.cmax<< endl;
        cout << "Schrage order: ";
        for (int j = 0; j < schrageResult.result.size(); j++) {
            cout << schrageResult.result[i].index + 1 << " ";
        }
        cout << endl;
        cout << "Optimal result: " << VectorOfDane[i].optimal << endl;
        cout << "Optimal order: ";
        for (int j = 0; j < VectorOfDane[i].optimalOrder.size(); j++) {
            cout << VectorOfDane[i].optimalOrder[j]+1 << " ";
        }
        cout << endl;
    }

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

SchrageResult schrmptn2(vector<Task>& tasks)
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
    SchrageResult schrageResult;
    schrageResult.cmax = cmax;
    schrageResult.result = result;
    return schrageResult;
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
