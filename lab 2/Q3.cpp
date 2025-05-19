#include <iostream>
#include <vector>
#include <algorithm> // for max_element
using namespace std;

int main() {
    int n, t, max_burst;
    float awt = 0, att = 0, temp = 0;
    
    cout << "Enter the number of processes: ";
    cin >> n;
    
    vector<int> bu(n), wa(n), tat(n), ct(n);
    
    // Input burst times
    for(int i = 0; i < n; i++) {
        cout << "\nEnter Burst Time for process " << i+1 << ": ";
        cin >> bu[i];
        ct[i] = bu[i];
    }
    
    cout << "\nEnter time quantum: ";
    cin >> t;
    
    // Find maximum burst time
    max_burst = *max_element(bu.begin(), bu.end());
    
    // Round Robin scheduling
    for(int j = 0; j < (max_burst / t) + 1; j++) {
        for(int i = 0; i < n; i++) {
            if(bu[i] != 0) {
                if(bu[i] <= t) {
                    tat[i] = temp + bu[i];
                    temp += bu[i];
                    bu[i] = 0;
                } else {
                    bu[i] -= t;
                    temp += t;
                }
            }
        }
    }
    
    // Calculate waiting times and averages
    for(int i = 0; i < n; i++) {
        wa[i] = tat[i] - ct[i];
        att += tat[i];
        awt += wa[i];
    }
    
    // Output results
    cout << "\nThe Average Turnaround time is: " << att/n;
    cout << "\nThe Average Waiting time is: " << awt/n;
    
    cout << "\n\nPROCESS\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n";
    for(int i = 0; i < n; i++) {
        cout << i+1 << "\t" << ct[i] << "\t\t" << wa[i] << "\t\t" << tat[i] << endl;
    }
    
    return 0;
}