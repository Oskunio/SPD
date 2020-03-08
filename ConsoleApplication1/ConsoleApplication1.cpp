// ConsoleApplication1.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

const int TABLESSIZE = 99;

void loadData(string dataPath, int* R, int* P, int* Q, int* n) {
    fstream dane;
    dane.open(dataPath, ios::in);
    if (dane.good()) {
        dane >> *n;
        for (int i = 0; i < *n; i++) {
            dane >> R[i] >> P[i] >> Q[i];
        }
    }
    /*
    if (*n == 0) {
        cout << "Brak danych!";
    }
    else {
        cout << "Liczba danych(n): " << *n << endl;
        for (int i = 0; i < *n; i++) {
            cout << R[i] << " " << P[i] << " " << Q[i] << endl;
        }
    }*/
}

int doTask(int *R,int*P,int*Q,int*n,int* order) {
    int m = 0,c=0,i=0;
    for (int j = 0; j < *n; j++) {
        i = order[j];
        m = max(m, R[i]) + P[i];
        c = max(m + Q[i], c);
    }
    return c;
}

bool isOrderingDone(int* doneTable) {
    bool isDone = true;
    for (int i = 0; i < TABLESSIZE; i++) {
        if (doneTable[i] == 0) {
            isDone = false;
        }
    }
    return isDone;
}

void makeOrder(int* order,int*R,int*P,int*Q,int n) {
    int minr[2];
    int minq[2];
    int lastminr[2];
    int lastminq[2];
    int doneTable[TABLESSIZE];
    int begin = 0;
    int end = n;
    int helpi = 0;
    int newOrder[TABLESSIZE];
    int j = 0;
    int middle = n / 2;

    
    for (int i = 0; i < TABLESSIZE; i++) {
        order[i] = i;
        newOrder[i] = i;
    }

    for (int i = 0; i < TABLESSIZE; i++) {
        doneTable[i] = 1;
    }
    for (int i = 0; i < n; i++) {
        doneTable[i] = 0;
    }

    while (!isOrderingDone(doneTable)) {

        minr[0] = 999999999;
        minr[1] = helpi;
        minq[0] = 999999999;
        minq[1] = helpi;
        for (int i = 0; i < n; i++) {
            if ((doneTable[i] == 0)) {
                if ((minr[0] > R[i])) {
                    minr[0] = R[i];
                    minr[1] = i;
                }
                if (minq[0] > Q[i]) {
                    minq[0] = Q[i];
                    minq[1] = i;
                }
            }
        }
        if (minr[1] == minq[1]) {
            order[middle] = minq[1];
            middle++;
            doneTable[minq[1]]=1;
        }
        else {
            order[begin] = minr[1];
            doneTable[minr[1]] = 1;
            order[end] = minq[1];
            doneTable[minq[1]] = 1;
            end--;
            begin++;
            helpi++;
        }
    }
}


int main()
{
    int R[TABLESSIZE],P[TABLESSIZE],Q[TABLESSIZE],order[TABLESSIZE];
    int n=0;
    int time1, time2, time3, time4, alltime;

    loadData("dane1.txt", R, P, Q, &n);
    makeOrder(order,R,P,Q,n);
    cout << "Całkowity czas zadania danych 1 dla kolejnosci:";
    for (int i = 0; i < n; i++) {
        cout << order[i]<<" ";
    }
    time1 = doTask(R, P, Q, &n, order);
    cout << "\nWynosi: " << time1<<endl;

    loadData("dane2.txt", R, P, Q, &n);
    makeOrder(order, R, P, Q, n);
    cout << "Całkowity czas zadania danych 2 dla kolejnosci:";
    for (int i = 0; i < n; i++) {
        cout << order[i] << " ";
    }
    time2 = doTask(R, P, Q, &n, order);
    cout << "\nWynosi: " << time2<<endl;

    loadData("dane3.txt", R, P, Q, &n);
    makeOrder(order, R, P, Q, n);
    cout << "Całkowity czas zadania danych 3 dla kolejnosci:";
    for (int i = 0; i < n; i++) {
        cout << order[i] << " ";
    }
    time3= doTask(R, P, Q, &n, order);
    cout << "\nWynosi: " << time3<<endl;

    loadData("dane4.txt", R, P, Q, &n);
    makeOrder(order, R, P, Q, n);
    cout << "Całkowity czas zadania danych 4 dla kolejnosci:";
    for (int i = 0; i < n; i++) {
        cout << order[i] << " ";
    }
    time4= doTask(R, P, Q, &n, order);
    cout << "\nWynosi: " << time4<<endl;

    alltime = time1 + time2 + time3 + time4;
    cout << "Całkowity czas zadan dla 4 porcji danych wynosi: " << alltime;


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
