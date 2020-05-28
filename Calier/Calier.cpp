// Calier.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <vector>
#include "Task.h"
#include <queue>
#include <fstream>


using namespace std;

int MAX_STEPS = 10;

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

struct CarlierResult
{
    int cmax;
    vector<Task> result;
};

int carlier(vector<Task>& tasks, int UB, int step);

SchrageResult schrmptn2(vector<Task>& tasks);

int findA(vector<Task>& tasks, int b, int cmax);
int findB(vector<Task>& tasks, int cmax);
int findC(vector<Task>& tasks, int a, int b);


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
            cout << schrageResult.result[j].index + 1 << " ";
        }

        cout << "\nUB: " << carlier(VectorOfDane[i].tasks, INT_MAX, 0) << endl;


        cout << endl;
        cout << "Carl: " << VectorOfDane[i].optimal << endl;
        cout << "Order: ";
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

SchrageResult schrage2(vector<Task>& tasks)
{
    priority_queue < Task, std::vector < Task >, Rmniejsze > N;
    priority_queue < Task, std::vector < Task >, Qwieksze > G;
    vector<Task> result;
    SchrageResult schrageResult;
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
    schrageResult.cmax = cmax;
    schrageResult.result = result;
    return schrageResult;
}

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


int carlier(vector<Task>& tasks, int UB, int step) {
    step++;
    int U;
    int LB = 0;
    int a=0, b=0, c = -1, rp = INT_MAX, qp = INT_MAX, pp=0, rdefault, qdefault,lbresult;
    
    vector<Task> optimalOrder;
    vector<Task> K;
    CarlierResult carlierResult;
    SchrageResult schrageResult = schrage2(tasks);
    SchrageResult schrageResult2;
    U = schrageResult.cmax;
    if (U < UB) {
        UB = U;
        optimalOrder = schrageResult.result;
    }
    b = findB(schrageResult.result, schrageResult.cmax);
    a = findA(schrageResult.result, b, schrageResult.cmax);
    c = findC(schrageResult.result, b, a);
    if (c < 0) {
        return UB;
    }
    for(int i = c + 1; i <= b; i++){
        rp = min(rp, schrageResult.result[i].r);
        qp = min(qp, schrageResult.result[i].q);
        pp += schrageResult.result[i].p;
    }
    rdefault = schrageResult.result[c].r;
    schrageResult.result[c].r = max(schrageResult.result[c].r, rp + pp);
    schrageResult2 = schrmptn2(schrageResult.result);
    LB = schrageResult2.cmax;
    if (LB < UB) {
        if (step < MAX_STEPS) {
            lbresult = carlier(schrageResult.result, UB, step);
            if (lbresult < UB) {
                UB = lbresult;
            }
        }
    }
    schrageResult.result[c].r = rdefault;
    qdefault = schrageResult.result[c].q;
    schrageResult.result[c].q =max(qp+pp,schrageResult.result[c].q);
    schrageResult2 = schrmptn2(schrageResult.result);
    LB = schrageResult2.cmax;
    if (LB < UB) {
        if (step < MAX_STEPS) {
            lbresult = carlier(schrageResult.result, UB, step);
            if (lbresult < UB) {
                UB = lbresult;
            }
        }
    }
    schrageResult.result[c].q = qdefault;
    return UB;
}

int doTask(vector<Task> tasks, int n) {
    int c=0;
    int m=0;
    for (int i = 0; i <= n; i++) {
        m = max(m, tasks[i].r) + tasks[i].p;
        c = max(m + tasks[i].q, c);
    }
    return m;
}

int findB(vector<Task>& tasks, int cmax) {
    int b = -1;
    for (int i = 0; i < tasks.size();i++) {
        if (doTask(tasks,i)+tasks[i].q == cmax) {
            b=i;
        }
    }
    return b;
}

int findA(vector<Task>& tasks, int b, int cmax) {
    for (int i = 0; i <=b; i++) {
        int suma = 0;
        for (int j = i; j <= b; j++) {
            suma += tasks[j].p;
        }
        if (cmax == (tasks[i].r + suma + tasks[b].q)) {
            return i;
        }
    }
}

int findC(vector<Task>& tasks, int b, int a) {
    int c = -1;
    for (int i = b; i >= a; i--) {
        if (tasks[i].q < tasks[b].q) {
            return c=i;
        }
    }
    return c;
}