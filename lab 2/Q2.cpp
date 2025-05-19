#include <iostream>
#include <algorithm> // for swap
#include <conio.h>   // for getch() - consider removing this for portability
using namespace std;

int main() {
    int p[20], bt[20], wt[20], tat[20], n;
    float wtavg = 0, tatavg = 0;
    
    system("cls"); // Clearing screen - Windows specific
    
    cout << "\nEnter the number of processes -- ";
    cin >> n;
    
    for(int i = 0; i < n; i++) {
        p[i] = i;
        cout << "Enter Burst Time for Process " << i << " -- ";
        cin >> bt[i];
    }
    
    // Sorting processes by burst time (Shortest Job First)
    for(int i = 0; i < n; i++) {
        for(int k = i + 1; k < n; k++) {
            if(bt[i] > bt[k]) {
                swap(bt[i], bt[k]);
                swap(p[i], p[k]);
            }
        }
    }
    
    // Calculate waiting and turnaround times
    wt[0] = 0;
    tat[0] = bt[0];
    tatavg = bt[0];
    
    for(int i = 1; i < n; i++) {
        wt[i] = wt[i-1] + bt[i-1];
        tat[i] = tat[i-1] + bt[i];
        wtavg += wt[i];
        tatavg += tat[i];
    }
    
    // Output results
    cout << "\n\tPROCESS\tBURST TIME\tWAITING TIME\tTURNAROUND TIME";
    for(int i = 0; i < n; i++) {
        cout << "\n\tP" << p[i] << "\t\t" << bt[i] << "\t\t" << wt[i] << "\t\t" << tat[i];
    }
    
    cout << "\nAverage Waiting Time -- " << wtavg/n;
    cout << "\nAverage Turnaround Time -- " << tatavg/n;
    
    getch(); // Wait for key press - consider removing for portability
    return 0;
}