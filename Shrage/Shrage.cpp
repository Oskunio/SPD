// Shrage.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include "Task.h"
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>


using namespace std;
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
    while (p!=7)
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
