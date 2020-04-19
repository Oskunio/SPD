// WiTi.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <fstream>

using namespace std;

const int MAXNUMBER = 99;
const string DATAFILEPATH = "witi.data.txt";

int checkDelayTime(int* P, int* W, int* D, int* Order, int numberOfTasks);
void showData(int* P, int* W, int* D, int numberOfTasks, string data);
void showOrder(int* order, int numberOfTasks);
void passElementInSpecificLocation(int firstElement, int secondElement, int* tab, int nbOfElementsInOrder);
bool isDone(int* tab, int nbOfTasks);



int main()
{
    fstream dane;
    string data = "";
    int P[MAXNUMBER];
    int W[MAXNUMBER];
    int D[MAXNUMBER];
    int Order[MAXNUMBER];
    int doneTasks[MAXNUMBER];
    int numberOfTasks=0;
    int count=0;
    int currentDelay = 0;

    for (int i = 0; i < MAXNUMBER; i++) {
        P[i] = -1;
        W[i] = -1;
        D[i] = -1;
        Order[i] = -1;
        doneTasks[i] = -1;
    }

    dane.open(DATAFILEPATH, ios::in);
    
    if (dane.good()) {
        dane >> data;
        dane >> numberOfTasks;
        for (int i = 0; i < numberOfTasks; i++) {
            dane >> P[i];
            dane >> W[i];
            dane >> D[i];
            Order[i] = i;
            doneTasks[i] = 0;
        }
    }
    showData(P, W, D, numberOfTasks, data);

    while (!isDone(doneTasks, numberOfTasks)) {
        for (int i = 0; i < numberOfTasks; i++) {
            Order[i] = i;
            for (int j = 0; j <= i; j++) {
                    currentDelay = checkDelayTime(P, W, D, Order, i + 1);
                    passElementInSpecificLocation(j, i, Order, i + 2);
                    if (currentDelay > checkDelayTime(P, W, D, Order, i + 1)) {
                    }
                    else {
                        passElementInSpecificLocation(j, i, Order, i + 2);
                    }
                
            }
            doneTasks[i] = 1;
            count = currentDelay;
        }

    }


    cout << "Wynik dla kolejnosci:";
    for (int i = 0; i < numberOfTasks; i++) {
        cout <<" "<< Order[i] + 1<<" ";
    }
    cout << endl << "Dla danych: "<<data<<"\nWynosi: " << count;
    cout << "\n\n\n";

}

void showOrder(int* order, int numberOfTasks) {
    cout << endl;
    for (int i = 0; i < numberOfTasks; i++) {
        cout << " " << order[i] << " ";
    }
    cout << endl;
}

int checkDelayTime(int* P, int* W, int* D, int* Order, int numberOfTasks) {

    int currentDelayCount = 0;
    int currentTime = 0;
    int currentTaskNumber = 0;

    for (int i = 0; i < numberOfTasks; i++) {
        currentTaskNumber = Order[i];
        currentTime += P[currentTaskNumber];
        if (D[currentTaskNumber] >= currentTime) {
            currentDelayCount += 0;
        }
        else {
            currentDelayCount += W[currentTaskNumber] * (currentTime - D[currentTaskNumber]);
        }
    }
    return currentDelayCount;
}

bool isDone(int* tab, int nbOfTasks) {
    bool flag = true;
    for (int i = 0; i < nbOfTasks;i++) {
        if (tab[i] != 1) {
            flag = false;
        }
    }
    return flag;
}

void showData(int* P, int* W, int* D, int numberOfTasks, string data) {
    cout << data << endl;
    cout << "Number of tasks: " << numberOfTasks << endl;

    cout << "\n# - P - W - D" << endl;

    for (int i = 0; i < numberOfTasks; i++) {
        cout << i + 1 << " - " << P[i] << " - " << W[i] << " - " << D[i] << endl;
    }
    cout << endl;
}

void passElementInSpecificLocation(int oldPositionOfTheElement, int newPositionOfTheElement, int* tab, int nbOfElementsInOrder) {
    int oldOrder[MAXNUMBER];
    int oldPositionValue = tab[oldPositionOfTheElement];
    int valueOfEdgeElement = 0;
    for (int i = 0; i < MAXNUMBER; i++) {
        oldOrder[i] = tab[i];
    }
    
    if (oldPositionOfTheElement < newPositionOfTheElement) {
        valueOfEdgeElement = tab[nbOfElementsInOrder-1];
        for (int i = newPositionOfTheElement + 1; i < nbOfElementsInOrder; i++) {
            tab[i] = oldOrder[i - 1];
        }
        tab[newPositionOfTheElement+1] = oldPositionValue;
        for (int i = oldPositionOfTheElement; i < nbOfElementsInOrder; i++) {
            if (i == (nbOfElementsInOrder-1)) {
                tab[i] = valueOfEdgeElement;
            }
            else {
                tab[i] = tab[i + 1];
            }
        }
    }
    else {
        valueOfEdgeElement = tab[nbOfElementsInOrder-1];
        for (int i = newPositionOfTheElement + 1; i < nbOfElementsInOrder; i++) {
            tab[i] = oldOrder[i - 1];
        }
        tab[newPositionOfTheElement] = oldPositionValue;
        for (int i = oldPositionOfTheElement+1; i < nbOfElementsInOrder; i++) {
            if (i == (nbOfElementsInOrder - 1)) {
                tab[i] = valueOfEdgeElement;
            }
            else {
                tab[i] = tab[i + 1];
            }
        }
    }
}