#include <iostream>
#include <vector>
#include <cstdlib> // for exit()
using namespace std;

class SegmentationMemoryManager {
private:
    vector<int> baseAddresses;
    vector<int> limits;
    int segmentCount;

public:
    void inputSegmentDetails() {
        cout << "\nProgram for Segmentation Memory Management\n";
        cout << "Enter the number of segments: ";
        cin >> segmentCount;

        baseAddresses.resize(segmentCount);
        limits.resize(segmentCount);

        cout << "Enter the base address and limit for each segment:\n";
        for (int i = 0; i < segmentCount; i++) {
            cout << "Segment " << i << " - Base Address: ";
            cin >> baseAddresses[i];
            cout << "           Limit: ";
            cin >> limits[i];
        }
    }

    void translateAddress() {
        int segmentNumber, offset;
        
        cout << "\nEnter logical address (segment number and offset): ";
        cin >> segmentNumber >> offset;

        if (segmentNumber < 0 || segmentNumber >= segmentCount) {
            cerr << "Error: Invalid segment number\n";
            exit(EXIT_FAILURE);
        }

        if (offset < 0 || offset >= limits[segmentNumber]) {
            cerr << "Error: Offset exceeds segment limit\n";
            exit(EXIT_FAILURE);
        }

        int physicalAddress = baseAddresses[segmentNumber] + offset;
        
        cout << "\nSegment Table Entry:" << endl;
        cout << "---------------------------------" << endl;
        cout << "Segment\tBase Address\tLimit" << endl;
        cout << segmentNumber << "\t" << baseAddresses[segmentNumber] 
             << "\t\t" << limits[segmentNumber] << endl;
        cout << "---------------------------------" << endl;
        cout << "Physical Address Calculation:" << endl;
        cout << "Base Address (" << baseAddresses[segmentNumber] << ") + "
             << "Offset (" << offset << ") = " << physicalAddress << endl;
        cout << "\nFinal Physical Address: " << physicalAddress << endl;
    }

    void run() {
        inputSegmentDetails();
        translateAddress();
    }
};

int main() {
    SegmentationMemoryManager manager;
    manager.run();
    return 0;
}