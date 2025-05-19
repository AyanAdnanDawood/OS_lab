#include <iostream>
#include <algorithm> // for swap
#include <iomanip>   // for formatting
using namespace std;

struct Process {
    int id;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
};

int main() {
    int n;
    float avg_waiting = 0, avg_turnaround = 0;
    
    cout << "Enter the number of processes: ";
    cin >> n;
    
    Process p[n];
    
    // Input process details
    for(int i = 0; i < n; i++) {
        p[i].id = i;
        cout << "Enter the Burst Time & Priority of Process " << i << ": ";
        cin >> p[i].burst_time >> p[i].priority;
    }
    
    // Sort processes by priority (lower number = higher priority)
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j < n; j++) {
            if(p[i].priority > p[j].priority) {
                swap(p[i], p[j]);
            }
        }
    }
    
    // Calculate waiting and turnaround times
    p[0].waiting_time = 0;
    p[0].turnaround_time = p[0].burst_time;
    avg_turnaround = p[0].turnaround_time;
    
    for(int i = 1; i < n; i++) {
        p[i].waiting_time = p[i-1].waiting_time + p[i-1].burst_time;
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
        
        avg_waiting += p[i].waiting_time;
        avg_turnaround += p[i].turnaround_time;
    }
    
    // Display results
    cout << "\nPROCESS\tPRIORITY\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n";
    cout << "-------------------------------------------------------------\n";
    
    for(int i = 0; i < n; i++) {
        cout << p[i].id << "\t" << p[i].priority << "\t\t" 
             << p[i].burst_time << "\t\t" << p[i].waiting_time 
             << "\t\t" << p[i].turnaround_time << endl;
    }
    
    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << avg_waiting/n;
    cout << "\nAverage Turnaround Time: " << avg_turnaround/n << endl;
    
    return 0;
}