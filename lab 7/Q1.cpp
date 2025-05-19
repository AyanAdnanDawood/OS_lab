#include <iostream>
#include <vector>
using namespace std;

class BankersAlgorithm {
private:
    int processes, resources;
    vector<vector<int>> current_allocation;
    vector<vector<int>> maximum_claim;
    vector<int> available;
    vector<int> work;
    vector<bool> finished;
    
public:
    void inputData() {
        cout << "Enter number of processes: ";
        cin >> processes;
        
        cout << "Enter number of resources: ";
        cin >> resources;
        
        // Initialize vectors
        current_allocation.resize(processes, vector<int>(resources));
        maximum_claim.resize(processes, vector<int>(resources));
        available.resize(resources);
        work.resize(resources);
        finished.resize(processes, false);
        
        cout << "Enter Claim Vector (total resources): ";
        for (int i = 0; i < resources; i++) {
            cin >> available[i];
        }
        
        cout << "Enter Allocated Resource Table:\n";
        for (int i = 0; i < processes; i++) {
            for (int j = 0; j < resources; j++) {
                cin >> current_allocation[i][j];
            }
        }
        
        cout << "Enter Maximum Claim Table:\n";
        for (int i = 0; i < processes; i++) {
            for (int j = 0; j < resources; j++) {
                cin >> maximum_claim[i][j];
            }
        }
    }
    
    void calculateAvailable() {
        vector<int> allocation(resources, 0);
        
        // Calculate total allocated resources
        for (int i = 0; i < processes; i++) {
            for (int j = 0; j < resources; j++) {
                allocation[j] += current_allocation[i][j];
            }
        }
        
        // Calculate available resources
        for (int i = 0; i < resources; i++) {
            available[i] -= allocation[i];
            work[i] = available[i];
        }
    }
    
    bool isSafeState() {
        vector<int> safe_sequence;
        int count = 0;
        
        while (count < processes) {
            bool found = false;
            
            for (int i = 0; i < processes; i++) {
                if (!finished[i]) {
                    bool can_execute = true;
                    
                    // Check if all resources can be allocated
                    for (int j = 0; j < resources; j++) {
                        if (maximum_claim[i][j] - current_allocation[i][j] > work[j]) {
                            can_execute = false;
                            break;
                        }
                    }
                    
                    if (can_execute) {
                        // Execute process and release resources
                        for (int j = 0; j < resources; j++) {
                            work[j] += current_allocation[i][j];
                        }
                        
                        safe_sequence.push_back(i);
                        finished[i] = true;
                        count++;
                        found = true;
                        
                        cout << "Process " << i + 1 << " is executing\n";
                        cout << "Available resources: ";
                        for (int res : work) cout << res << " ";
                        cout << endl;
                    }
                }
            }
            
            if (!found) {
                cout << "System is in an unsafe state!\n";
                return false;
            }
        }
        
        cout << "\nSystem is in a safe state\nSafe sequence: ";
        for (int proc : safe_sequence) cout << "P" << proc + 1 << " ";
        cout << endl;
        return true;
    }
    
    void displayData() {
        cout << "\nAllocated Resource Table:\n";
        for (int i = 0; i < processes; i++) {
            for (int j = 0; j < resources; j++) {
                cout << current_allocation[i][j] << "\t";
            }
            cout << endl;
        }
        
        cout << "\nMaximum Claim Table:\n";
        for (int i = 0; i < processes; i++) {
            for (int j = 0; j < resources; j++) {
                cout << maximum_claim[i][j] << "\t";
            }
            cout << endl;
        }
        
        cout << "\nAvailable resources: ";
        for (int res : available) cout << res << " ";
        cout << endl;
    }
};

int main() {
    BankersAlgorithm banker;
    
    banker.inputData();
    banker.calculateAvailable();
    banker.displayData();
    
    if (banker.isSafeState()) {
        cout << "No deadlock will occur.\n";
    } else {
        cout << "System is in an unsafe state - deadlock possible!\n";
    }
    
    return 0;
}