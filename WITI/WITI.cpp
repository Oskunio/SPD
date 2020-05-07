// WiTi.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <fstream>

using namespace std;

const int MAXNUMBER = 99;
const string DATAFILEPATH = "witi.data.txt";
const string OUTPUTDATA = "output.txt";

int checkDelayTime(int* P, int* W, int* D, int* Order, int numberOfTasks);
void showData(int* P, int* W, int* D, int numberOfTasks, string data);
void showOrder(int* order, int numberOfTasks);
void passElementInSpecificLocation(int firstElement, int secondElement, int* tab, int nbOfElementsInOrder);
bool isDone(int* tab, int nbOfTasks);



int main()
{
    fstream dane;
    fstream daneDoPliku;
    string data = "";
    string helper = "";
    int P[MAXNUMBER];
    int W[MAXNUMBER];
    int D[MAXNUMBER];
    int Opt[MAXNUMBER];
    int StartingOrder[MAXNUMBER];
    int BestOrder[MAXNUMBER];
    int CurrentOrder[MAXNUMBER];
    int doneTasks[MAXNUMBER];
    int optimalDelay = 0;
    int numberOfTasks=0;
    int count=0;
    int currentDelay = 0;
    int bestDelay = 9999999999999999;
    int currentBest = bestDelay;
    bool flag = false;

    for (int i = 0; i < MAXNUMBER; i++) {
        P[i] = -1;
        W[i] = -1;
        D[i] = -1;
        StartingOrder[i] = -1;
        doneTasks[i] = -1;
        BestOrder[i] = 0;
        CurrentOrder[i] = 0;
        Opt[i] = i;
    }

    dane.open(DATAFILEPATH, ios::in);
    daneDoPliku.open(OUTPUTDATA, ios::out);
    while(!dane.eof()) {
        dane >> data;
        dane >> numberOfTasks;
        for (int i = 0; i < numberOfTasks; i++) {
            dane >> P[i];
            dane >> W[i];
            dane >> D[i];
            StartingOrder[i] = i;
            doneTasks[i] = 0;
        }
        showData(P, W, D, numberOfTasks, data);
        dane >> helper;
        std::cout << helper << endl;
        dane >> optimalDelay;
        std::cout << optimalDelay << endl;
        for (int i = 0; i < numberOfTasks; i++) {
            dane >> Opt[i];
        }

        
        while (!isDone(doneTasks, numberOfTasks)) {
            for (int i = 0; i < numberOfTasks; i++) {
                flag = false;
                currentBest = 9999999999999999;
                for (int j = 0; j <= i; j++) {

                    for (int k = 0; k <= i; k++) {
                        CurrentOrder[k] = StartingOrder[k];
                    }
                    currentDelay = checkDelayTime(P, W, D, CurrentOrder, i + 1);
                    passElementInSpecificLocation(i, j, CurrentOrder, i + 1);
                    doneTasks[i] = 1;
                    std::cout << "\nI've got: " << checkDelayTime(P, W, D, CurrentOrder, i + 1) << endl << "For order: ";
                    showOrder(CurrentOrder, i+1);
                    std::cout << endl;
                    if (currentBest > checkDelayTime(P, W, D, CurrentOrder, i + 1)) {
                        currentBest = checkDelayTime(P, W, D, CurrentOrder, i + 1);
                        flag = true;
                        for (int k = 0; k <= i; k++) {
                            BestOrder[k] = CurrentOrder[k];
                        }
                    }
                    else {
                        for (int k = 0; k <= i; k++) {
                            CurrentOrder[k] = StartingOrder[k];
                        }
                    }
                }
                if (!flag) {
                    for (int k = 0; k <= i; k++) {
                        BestOrder[k] = CurrentOrder[k];
                    }
                }
                for (int k = 0; k <= i; k++) {
                    StartingOrder[k] = BestOrder[k];
                }
                bestDelay = currentBest;
            }

        }
        std::cout << "Wynik dla kolejnosci: ";
        showOrder(BestOrder, numberOfTasks);
        std::cout << endl << "Dla danych: " << data << "\nWynosi: " << bestDelay;
        std::cout << "\n\n\n";
        daneDoPliku << data << "," << bestDelay << "," << optimalDelay << endl;
    }
    dane.close();
    daneDoPliku.close();

}

void showOrder(int* order, int numberOfTasks) {
    std::cout << endl;
    for (int i = 0; i < numberOfTasks; i++) {
        std::cout << " " << order[i] << " ";
    }
    std::cout << endl;
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
    std::cout << data << endl;
    std::cout << "Number of tasks: " << numberOfTasks << endl;

    std::cout << "\n# - P - W - D" << endl;

    for (int i = 0; i < numberOfTasks; i++) {
        std::cout << i + 1 << " - " << P[i] << " - " << W[i] << " - " << D[i] << endl;
    }
    std::cout << endl;
}

void passElementInSpecificLocation(int oldPositionOfTheElement, int newPositionOfTheElement, int* tab, int nbOfElementsInOrder) {
    int oldOrder[MAXNUMBER];
    int oldPositionValue = tab[oldPositionOfTheElement];
    for (int i = 0; i < MAXNUMBER; i++) {
        oldOrder[i] = tab[i];
    }
    for (int i = newPositionOfTheElement; i < nbOfElementsInOrder; i++) {
        tab[i + 1] = oldOrder[i];
    }
    tab[newPositionOfTheElement] = oldPositionValue;
}

int main123() {
    int Order[6] = { 4,0,1,2,3,5 };
    int P[6] = { 1,46,5,93,83,1 };
    int W[6] = { 2,5,7,4,1,1 };
    int D[6] = { 748,216,673,514,52,1 };
    std::cout << checkDelayTime(P, W, D, Order, 5);
    //passElementInSpecificLocation(3, 2, Order, 5);
}