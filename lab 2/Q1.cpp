#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int bt[20], wt[20], tat[20], n;
    float wtavg = 0, tatavg = 0;

    cout << "Enter the number of processes -- ";
    cin >> n;

    for(int i = 0; i < n; i++) {
        cout << "Enter Burst Time for Process " << i << " -- ";
        cin >> bt[i];
    }

    // Calculate waiting and turnaround times
    wt[0] = 0;
    tat[0] = bt[0];

    for(int i = 1; i < n; i++) {
        wt[i] = wt[i-1] + bt[i-1];
        tat[i] = tat[i-1] + bt[i];
        wtavg += wt[i];
        tatavg += tat[i];
    }

    // Add first process to averages
    wtavg += wt[0];
    tatavg += tat[0];

    // Display results
    cout << "\n" << setw(10) << "PROCESS" << setw(15) << "BURST TIME" 
         << setw(15) << "WAITING TIME" << setw(20) << "TURNAROUND TIME" << endl;
    
    for(int i = 0; i < n; i++) {
        cout << setw(10) << "P" << i 
             << setw(15) << bt[i] 
             << setw(15) << wt[i] 
             << setw(20) << tat[i] << endl;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time -- " << wtavg/n;
    cout << "\nAverage Turnaround Time -- " << tatavg/n << endl;

    return 0;
}