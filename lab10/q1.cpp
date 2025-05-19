#include <iostream>
#include <vector>
using namespace std;

class PagingMemoryManager {
private:
    int memorySize;
    int pageSize;
    int totalPages;
    int remainingPages;
    int processCount;
    vector<int> pagesRequired;
    vector<vector<int>> pageTables;

public:
    void inputMemoryDetails() {
        cout << "Enter the memory size (in bytes): ";
        cin >> memorySize;
        
        cout << "Enter the page size (in bytes): ";
        cin >> pageSize;
        
        totalPages = memorySize / pageSize;
        remainingPages = totalPages;
        
        cout << "\nNumber of pages available in memory: " << totalPages << endl;
    }

    void inputProcessDetails() {
        cout << "Enter number of processes: ";
        cin >> processCount;
        
        pagesRequired.resize(processCount + 1); // 1-based indexing
        pageTables.resize(processCount + 1);
        
        for (int i = 1; i <= processCount; i++) {
            cout << "\nEnter number of pages required for process[" << i << "]: ";
            cin >> pagesRequired[i];
            
            if (pagesRequired[i] > remainingPages) {
                cout << "Memory is Full. Cannot allocate more processes." << endl;
                processCount = i - 1; // Adjust process count
                break;
            }
            
            remainingPages -= pagesRequired[i];
            
            cout << "Enter page table for process[" << i << "] (frame numbers for each page):\n";
            pageTables[i].resize(pagesRequired[i]);
            
            for (int j = 0; j < pagesRequired[i]; j++) {
                cout << "Page " << j << " -> Frame: ";
                cin >> pageTables[i][j];
            }
        }
    }

    void translateAddress() {
        int processNum, pageNum, offset;
        
        cout << "\nEnter Logical Address to find Physical Address:" << endl;
        cout << "Enter process number, page number, and offset: ";
        cin >> processNum >> pageNum >> offset;
        
        if (processNum < 1 || processNum > processCount) {
            cout << "Invalid Process Number" << endl;
            return;
        }
        
        if (pageNum < 0 || pageNum >= pagesRequired[processNum]) {
            cout << "Invalid Page Number" << endl;
            return;
        }
        
        if (offset < 0 || offset >= pageSize) {
            cout << "Invalid Offset" << endl;
            return;
        }
        
        int physicalAddress = pageTables[processNum][pageNum] * pageSize + offset;
        cout << "\nThe Physical Address is: " << physicalAddress << endl;
    }

    void run() {
        inputMemoryDetails();
        inputProcessDetails();
        translateAddress();
    }
};

int main() {
    PagingMemoryManager manager;
    manager.run();
    return 0;
}