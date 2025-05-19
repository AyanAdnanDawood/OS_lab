#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int DISK_SIZE = 50;

void initializeDisk(vector<int>& disk) {
    fill(disk.begin(), disk.end(), 0);
}

void printDisk(const vector<int>& disk) {
    cout << "\nCurrent Disk Allocation:\n";
    for (int i = 0; i < DISK_SIZE; i++) {
        if (i % 10 == 0) cout << "\n";
        cout << i << ":" << disk[i] << " ";
    }
    cout << "\n";
}

void contiguousAllocation(vector<int>& disk) {
    int start, length;
    cout << "\nCONTIGUOUS ALLOCATION\n";
    cout << "Enter starting block and length of file: ";
    cin >> start >> length;

    if (start < 0 || start >= DISK_SIZE || (start + length) > DISK_SIZE) {
        cout << "Invalid range! Disk size is " << DISK_SIZE << " blocks.\n";
        return;
    }

    // Check if blocks are available
    for (int i = start; i < start + length; i++) {
        if (disk[i] != 0) {
            cout << "Block " << i << " is already allocated!\n";
            return;
        }
    }

    // Allocate blocks
    for (int i = start; i < start + length; i++) {
        disk[i] = 1;
        cout << i << " -> " << disk[i] << "\n";
    }

    cout << "File allocated successfully in contiguous blocks.\n";
}

void indexedAllocation(vector<int>& disk) {
    int indexBlock;
    cout << "\nINDEXED ALLOCATION\n";
    cout << "Enter index block number: ";
    cin >> indexBlock;

    if (indexBlock < 0 || indexBlock >= DISK_SIZE) {
        cout << "Invalid block number!\n";
        return;
    }

    if (disk[indexBlock] != 0) {
        cout << "Index block is already allocated!\n";
        return;
    }

    disk[indexBlock] = 1; // Mark index block as allocated

    int n;
    cout << "Enter number of blocks needed for file: ";
    cin >> n;

    vector<int> blocks(n);
    cout << "Enter " << n << " block numbers for file: ";
    for (int i = 0; i < n; i++) {
        cin >> blocks[i];
        if (blocks[i] < 0 || blocks[i] >= DISK_SIZE) {
            cout << "Invalid block number " << blocks[i] << "!\n";
            disk[indexBlock] = 0; // Free index block
            return;
        }
        if (disk[blocks[i]] != 0) {
            cout << "Block " << blocks[i] << " is already allocated!\n";
            disk[indexBlock] = 0; // Free index block
            return;
        }
    }

    // Allocate all blocks
    for (int block : blocks) {
        disk[block] = 1;
    }

    cout << "\nFile allocated successfully with index block " << indexBlock << "\n";
    cout << "Index Block -> Data Blocks:\n";
    for (int block : blocks) {
        cout << indexBlock << " -> " << block << ":" << disk[block] << "\n";
    }
}

void linkedAllocation(vector<int>& disk) {
    cout << "\nLINKED ALLOCATION\n";
    
    // Show already allocated blocks
    cout << "Enter number of blocks already allocated: ";
    int p;
    cin >> p;
    
    if (p > 0) {
        cout << "Enter block numbers already allocated: ";
        for (int i = 0; i < p; i++) {
            int a;
            cin >> a;
            if (a >= 0 && a < DISK_SIZE) {
                disk[a] = 1;
            }
        }
    }

    int start, length;
    cout << "Enter starting block and length of file: ";
    cin >> start >> length;

    if (start < 0 || start >= DISK_SIZE) {
        cout << "Invalid starting block!\n";
        return;
    }

    if (disk[start] != 0) {
        cout << "Starting block " << start << " is already allocated!\n";
        return;
    }

    vector<int> allocatedBlocks;
    allocatedBlocks.push_back(start);
    disk[start] = 1;
    cout << start << " -> " << disk[start] << " (Start)";

    int current = start;
    int blocksAllocated = 1;
    int nextBlock;

    while (blocksAllocated < length) {
        cout << "\nEnter next block number for link (or -1 to find next available): ";
        cin >> nextBlock;

        if (nextBlock == -1) {
            // Find next available block
            for (int i = 0; i < DISK_SIZE; i++) {
                if (disk[i] == 0) {
                    nextBlock = i;
                    break;
                }
            }
            if (nextBlock == -1) {
                cout << "No more free blocks available!\n";
                break;
            }
        }

        if (nextBlock < 0 || nextBlock >= DISK_SIZE) {
            cout << "Invalid block number!\n";
            continue;
        }

        if (disk[nextBlock] != 0) {
            cout << "Block " << nextBlock << " is already allocated!\n";
            continue;
        }

        disk[nextBlock] = 1;
        allocatedBlocks.push_back(nextBlock);
        cout << current << " -> " << nextBlock << ":" << disk[nextBlock];
        current = nextBlock;
        blocksAllocated++;
    }

    cout << "\nFile allocated successfully with " << blocksAllocated << " blocks.\n";
    cout << "Allocation chain: ";
    for (size_t i = 0; i < allocatedBlocks.size(); i++) {
        cout << allocatedBlocks[i];
        if (i != allocatedBlocks.size() - 1) cout << " -> ";
    }
    cout << "\n";
}

int main() {
    vector<int> disk(DISK_SIZE, 0);
    int choice;

    while (true) {
        cout << "\nFILE ALLOCATION METHODS\n";
        cout << "1. Contiguous Allocation\n";
        cout << "2. Indexed Allocation\n";
        cout << "3. Linked Allocation\n";
        cout << "4. Show Disk Status\n";
        cout << "5. Reset Disk\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                contiguousAllocation(disk);
                break;
            case 2:
                indexedAllocation(disk);
                break;
            case 3:
                linkedAllocation(disk);
                break;
            case 4:
                printDisk(disk);
                break;
            case 5:
                initializeDisk(disk);
                cout << "Disk reset to all free blocks.\n";
                break;
            case 6:
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
}