#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class MemoryAllocator {
private:
    vector<int> processes;
    vector<int> blocks;
    vector<int> allocations;
    vector<bool> flags;

public:
    void inputData() {
        int np, nb;
        
        cout << "Enter the number of processes: ";
        cin >> np;
        
        cout << "Enter the number of memory blocks: ";
        cin >> nb;
        
        processes.resize(np);
        blocks.resize(nb);
        allocations.resize(np, -1);
        flags.resize(np, false);
        
        cout << "Enter the size of each process:\n";
        for (int i = 0; i < np; i++) {
            cout << "Process " << i << ": ";
            cin >> processes[i];
        }
        
        cout << "Enter the block sizes:\n";
        for (int j = 0; j < nb; j++) {
            cout << "Block " << j << ": ";
            cin >> blocks[j];
        }
    }

    void firstFit() {
        vector<int> tempBlocks = blocks;
        fill(flags.begin(), flags.end(), false);
        fill(allocations.begin(), allocations.end(), -1);
        
        cout << "\nFirst Fit Allocation:\n";
        for (int i = 0; i < processes.size(); i++) {
            for (int j = 0; j < tempBlocks.size(); j++) {
                if (processes[i] <= tempBlocks[j]) {
                    allocations[i] = j;
                    tempBlocks[j] -= processes[i];
                    flags[i] = true;
                    cout << "Process " << i << " (size " << processes[i] 
                         << ") allocated to Block " << j << " (remaining size " 
                         << tempBlocks[j] << ")\n";
                    break;
                }
            }
            if (!flags[i]) {
                cout << "Process " << i << " (size " << processes[i] 
                     << ") could not be allocated\n";
            }
        }
    }

    void bestFit() {
        vector<int> tempBlocks = blocks;
        fill(flags.begin(), flags.end(), false);
        fill(allocations.begin(), allocations.end(), -1);
        
        cout << "\nBest Fit Allocation:\n";
        for (int i = 0; i < processes.size(); i++) {
            int bestIdx = -1;
            for (int j = 0; j < tempBlocks.size(); j++) {
                if (processes[i] <= tempBlocks[j]) {
                    if (bestIdx == -1 || tempBlocks[j] < tempBlocks[bestIdx]) {
                        bestIdx = j;
                    }
                }
            }
            
            if (bestIdx != -1) {
                allocations[i] = bestIdx;
                tempBlocks[bestIdx] -= processes[i];
                flags[i] = true;
                cout << "Process " << i << " (size " << processes[i] 
                     << ") allocated to Block " << bestIdx << " (remaining size " 
                     << tempBlocks[bestIdx] << ")\n";
            } else {
                cout << "Process " << i << " (size " << processes[i] 
                     << ") could not be allocated\n";
            }
        }
    }

    void worstFit() {
        vector<int> tempBlocks = blocks;
        fill(flags.begin(), flags.end(), false);
        fill(allocations.begin(), allocations.end(), -1);
        
        cout << "\nWorst Fit Allocation:\n";
        for (int i = 0; i < processes.size(); i++) {
            int worstIdx = -1;
            for (int j = 0; j < tempBlocks.size(); j++) {
                if (processes[i] <= tempBlocks[j]) {
                    if (worstIdx == -1 || tempBlocks[j] > tempBlocks[worstIdx]) {
                        worstIdx = j;
                    }
                }
            }
            
            if (worstIdx != -1) {
                allocations[i] = worstIdx;
                tempBlocks[worstIdx] -= processes[i];
                flags[i] = true;
                cout << "Process " << i << " (size " << processes[i] 
                     << ") allocated to Block " << worstIdx << " (remaining size " 
                     << tempBlocks[worstIdx] << ")\n";
            } else {
                cout << "Process " << i << " (size " << processes[i] 
                     << ") could not be allocated\n";
            }
        }
    }

    void run() {
        inputData();
        
        if (processes.size() > blocks.size()) {
            cout << "\nWarning: More processes than blocks - some processes may not be allocated\n";
        }
        
        int choice;
        do {
            cout << "\nMemory Allocation Algorithms:\n"
                 << "1. First Fit\n"
                 << "2. Best Fit\n"
                 << "3. Worst Fit\n"
                 << "4. Exit\n"
                 << "Enter your choice: ";
            cin >> choice;
            
            switch (choice) {
                case 1: firstFit(); break;
                case 2: bestFit(); break;
                case 3: worstFit(); break;
                case 4: cout << "Exiting...\n"; break;
                default: cout << "Invalid choice. Try again.\n";
            }
        } while (choice != 4);
    }
};

int main() {
    MemoryAllocator allocator;
    allocator.run();
    return 0;
}