#include <iostream>
#include <vector>
using namespace std;

class DeadlockDetector {
private:
    int num_processes;
    int num_resources;
    vector<vector<int>> max_matrix;
    vector<vector<int>> allocation;
    vector<int> available;
    vector<vector<int>> need;
    vector<bool> finished;

public:
    void inputData() {
        cout << "********** Deadlock Detection Algorithm ************\n";
        cout << "Enter the number of Processes: ";
        cin >> num_processes;
        cout << "Enter the number of resource instances: ";
        cin >> num_resources;

        // Initialize matrices
        max_matrix.resize(num_processes, vector<int>(num_resources));
        allocation.resize(num_processes, vector<int>(num_resources));
        available.resize(num_resources);
        need.resize(num_processes, vector<int>(num_resources));
        finished.resize(num_processes, false);

        cout << "Enter the Max Matrix:\n";
        for (int i = 0; i < num_processes; i++) {
            for (int j = 0; j < num_resources; j++) {
                cin >> max_matrix[i][j];
            }
        }

        cout << "Enter the Allocation Matrix:\n";
        for (int i = 0; i < num_processes; i++) {
            for (int j = 0; j < num_resources; j++) {
                cin >> allocation[i][j];
            }
        }

        cout << "Enter the available Resources:\n";
        for (int j = 0; j < num_resources; j++) {
            cin >> available[j];
        }
    }

    void calculateNeedMatrix() {
        for (int i = 0; i < num_processes; i++) {
            for (int j = 0; j < num_resources; j++) {
                need[i][j] = max_matrix[i][j] - allocation[i][j];
            }
        }
    }

    void displayStatus() {
        cout << "\nProcess\tAllocation\tMax\tAvailable\n";
        for (int i = 0; i < num_processes; i++) {
            cout << "P" << i + 1 << "\t";
            
            // Display allocation
            for (int j = 0; j < num_resources; j++) {
                cout << allocation[i][j] << " ";
            }
            cout << "\t";
            
            // Display max
            for (int j = 0; j < num_resources; j++) {
                cout << max_matrix[i][j] << " ";
            }
            cout << "\t";
            
            // Display available (only for first row)
            if (i == 0) {
                for (int j = 0; j < num_resources; j++) {
                    cout << available[j] << " ";
                }
            }
            cout << endl;
        }
    }

    void detectDeadlock() {
        calculateNeedMatrix();
        vector<int> work = available;
        vector<int> deadlocked_processes;
        bool changed = true;
        int count = 0;

        while (changed && count < num_processes) {
            changed = false;
            for (int i = 0; i < num_processes; i++) {
                if (!finished[i]) {
                    bool can_execute = true;
                    for (int j = 0; j < num_resources; j++) {
                        if (need[i][j] > work[j]) {
                            can_execute = false;
                            break;
                        }
                    }

                    if (can_execute) {
                        // Process can execute
                        for (int j = 0; j < num_resources; j++) {
                            work[j] += allocation[i][j];
                        }
                        finished[i] = true;
                        changed = true;
                        count++;
                        cout << "Process P" << i + 1 << " can execute. New available: ";
                        for (int res : work) cout << res << " ";
                        cout << endl;
                    }
                }
            }
        }

        // Check for deadlocked processes
        for (int i = 0; i < num_processes; i++) {
            if (!finished[i]) {
                deadlocked_processes.push_back(i);
            }
        }

        if (!deadlocked_processes.empty()) {
            cout << "\nSystem is in Deadlock. Deadlocked processes are:\n";
            for (int proc : deadlocked_processes) {
                cout << "P" << proc + 1 << " ";
            }
            cout << endl;
        } else {
            cout << "\nNo deadlock detected. System is in safe state." << endl;
        }
    }
};

int main() {
    DeadlockDetector detector;
    detector.inputData();
    detector.displayStatus();
    detector.detectDeadlock();
    return 0;
}