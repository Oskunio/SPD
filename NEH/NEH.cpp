// NEH.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include "Job.h"
#include <chrono>

using namespace std;

int cmax(vector<Job> &jobs, int prace, int maszyny)
{
    int czas;
    prace++;
    maszyny++;
    // alokacja tablicy
    int** cmaxTab = new int* [prace];
    for (int i = 0; i < prace; i++)
    {
        cmaxTab[i] = new int[maszyny];
    }

    // uzupełnienienie tablicy elementami, ktore sa rowne zero
    for (int i = 0; i < prace; i++)
    {
        cmaxTab[i][0] = 0;
    }
    for (int i = 0; i < maszyny; i++)
    {
        cmaxTab[0][i] = 0;
    }
    // liczenie kolejnych elementow
    for (int i = 1; i < prace; i++)
    {
        for (int j = 1; j < maszyny; j++)
        {
            cmaxTab[i][j] = max(cmaxTab[i - 1][j], cmaxTab[i][j - 1]) + jobs[i - 1].timesOnMachines[j - 1];
        }
    }


    czas = cmaxTab[prace - 1][maszyny - 1];

    // dealokacja tablicy
    for (int i = 0; i < prace; i++)
        delete[] cmaxTab[i];

    delete[] cmaxTab;

    return czas;
}


int NEH(vector<Job> jobs, int prace, int maszyny)
{
    int min = 99999999999;
    int currCmax;
    int wielkosc = 0; // zmienna przechowująca wielkosc składanego uporządkowania
    int swapNumber = 0;
    int bestSwapNumber = 0;
    
    vector<Job> resultJobs; // wynikowe uporządkowanie

    //sortowanie sum 
    sort(jobs.begin(), jobs.end());
    
    // dodanie pierwszego elementu
    Job temp = jobs.back();
    resultJobs.push_back(temp);
    jobs.pop_back();
    int size = jobs.size();

    // dodanie kolejnych elementow
    for (int i = 0; i < size; i++)
    {
        temp = jobs.back();
        resultJobs.push_back(temp);
        jobs.pop_back();

        currCmax = cmax(resultJobs, resultJobs.size(), maszyny);

        bestSwapNumber = 0;
        min = 9999999999;
        if (currCmax < min) min = currCmax;

        int wielkosc = resultJobs.size();
        for (int j = wielkosc - 1; j > 0; j--)
        {
            swap(resultJobs[j], resultJobs[j - 1]);
            swapNumber++;
            currCmax = cmax(resultJobs, wielkosc, maszyny);
            if (currCmax <= min)
            {
                min = currCmax;
                bestSwapNumber = swapNumber;
            }
        }

        // cofanie swapów do najlepszego
        for (int k = 0; k < (swapNumber - bestSwapNumber); k++)
        {
            swap(resultJobs[k], resultJobs[k + 1]);
        }

        swapNumber = 0;
        // wyswietlanie kolejnych uszeregowan
        /*
        for (Job job : resultJobs)
        {
            cout << job.index + 1<< " ";
        }
        cout << endl;
        */
    }

    // wyswietlenie tablicy wynikowej
    /*
    for (Job job:resultJobs)
    {
        for (int t : job.timesOnMachines)
        {
            cout << t << " ";
        }
        cout << endl;
    }
    */

    
    return min;
}

int main()
{
    ifstream stream("neh.data.txt");  // Otwarcie pliku do odczytu
    double excecutionTime = 0;
    if (!stream)
    {
        cout << "BŁĄD: nie można otworzyć pliku do odczytu." << endl;
    }

    string text; // nazwa danych
    int prace;
    int maszyny;
    int p = 0;
    while(p!=121)
    {
        stream >> text;
        cout << text;
        stream >> prace;
        stream >> maszyny;
        string linia;
        double czas; // wczytany czas
        double time; // czas dzialania algorytmu NEH

        vector<Job> jobs;
        Job job;
        for (int i = 0; i < prace; i++)
        {
            job.index = i;
            
            jobs.push_back(job);
            for (int j = 0; j < maszyny; j++)
            {
                stream >> time;
                jobs[i].timesOnMachines.push_back(time);
            }
            jobs[i].setSum();
        }

        auto start = std::chrono::steady_clock::now();

        cout << " " << NEH(jobs, prace, maszyny) <<" "; // alogrytm NEH

        auto end = std::chrono::steady_clock::now();

        double elapsed_seconds = double(std::chrono::duration_cast <std::chrono::nanoseconds>(end - start).count());
        cout << elapsed_seconds/1e9<<endl;
        excecutionTime += elapsed_seconds;

        stream >> linia;
        stream >> czas;
        for (int i = 0; i < prace; i++)
        {
            stream >> linia;
        }
        p++;
    }
    cout << endl;
    cout << "Total time:" << excecutionTime / 1e9 << " s " << endl;
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
