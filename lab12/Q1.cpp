#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>
using namespace std;

class PageReplacement {
private:
    vector<int> reference_string;
    int frame_count;

    void displayFrames(const vector<int>& frames, int fault = -1) {
        for (int val : frames) {
            if (val == -1) cout << "- ";
            else cout << val << " ";
        }
        if (fault != -1) cout << "\tPF #" << fault;
        cout << endl;
    }

public:
    void inputData() {
        int n;
        cout << "Enter length of reference string: ";
        cin >> n;
        
        cout << "Enter reference string (space separated): ";
        reference_string.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> reference_string[i];
        }

        cout << "Enter number of frames: ";
        cin >> frame_count;
    }

    void fifo() {
        vector<int> frames(frame_count, -1);
        unordered_map<int, bool> in_memory;
        int pointer = 0, page_faults = 0;

        cout << "\nFIFO Page Replacement:\n";
        for (int page : reference_string) {
            if (in_memory.find(page) == in_memory.end()) {
                if (frames[pointer] != -1) {
                    in_memory.erase(frames[pointer]);
                }
                frames[pointer] = page;
                in_memory[page] = true;
                pointer = (pointer + 1) % frame_count;
                page_faults++;
                displayFrames(frames, page_faults);
            } else {
                displayFrames(frames);
            }
        }
        cout << "Total Page Faults: " << page_faults << endl;
    }

    void lru() {
        vector<int> frames(frame_count, -1);
        unordered_map<int, int> recent_use;
        int page_faults = 0, time = 0;

        cout << "\nLRU Page Replacement:\n";
        for (int page : reference_string) {
            time++;
            if (recent_use.find(page) == recent_use.end()) {
                if (frames.size() >= frame_count) {
                    int lru_page = frames[0], lru_time = recent_use[lru_page];
                    for (int p : frames) {
                        if (recent_use[p] < lru_time) {
                            lru_page = p;
                            lru_time = recent_use[p];
                        }
                    }
                    auto it = find(frames.begin(), frames.end(), lru_page);
                    *it = page;
                    recent_use.erase(lru_page);
                } else {
                    frames.push_back(page);
                }
                page_faults++;
                displayFrames(frames, page_faults);
            }
            recent_use[page] = time;
            displayFrames(frames);
        }
        cout << "Total Page Faults: " << page_faults << endl;
    }

    void optimal() {
        vector<int> frames(frame_count, -1);
        int page_faults = 0;

        cout << "\nOptimal Page Replacement:\n";
        for (int i = 0; i < reference_string.size(); i++) {
            int page = reference_string[i];
            if (find(frames.begin(), frames.end(), page) == frames.end()) {
                if (frames.size() >= frame_count) {
                    int farthest = -1, replace_index = 0;
                    for (int j = 0; j < frames.size(); j++) {
                        int next_use = INT_MAX;
                        for (int k = i + 1; k < reference_string.size(); k++) {
                            if (frames[j] == reference_string[k]) {
                                next_use = k;
                                break;
                            }
                        }
                        if (next_use > farthest) {
                            farthest = next_use;
                            replace_index = j;
                        }
                    }
                    frames[replace_index] = page;
                } else {
                    frames.push_back(page);
                }
                page_faults++;
                displayFrames(frames, page_faults);
            } else {
                displayFrames(frames);
            }
        }
        cout << "Total Page Faults: " << page_faults << endl;
    }

    void mru() {
        vector<int> frames(frame_count, -1);
        unordered_map<int, int> recent_use;
        int page_faults = 0, time = 0;

        cout << "\nMRU Page Replacement:\n";
        for (int page : reference_string) {
            time++;
            if (recent_use.find(page) == recent_use.end()) {
                if (frames.size() >= frame_count) {
                    int mru_page = frames[0], mru_time = recent_use[mru_page];
                    for (int p : frames) {
                        if (recent_use[p] > mru_time) {
                            mru_page = p;
                            mru_time = recent_use[p];
                        }
                    }
                    auto it = find(frames.begin(), frames.end(), mru_page);
                    *it = page;
                    recent_use.erase(mru_page);
                } else {
                    frames.push_back(page);
                }
                page_faults++;
                displayFrames(frames, page_faults);
            }
            recent_use[page] = time;
            displayFrames(frames);
        }
        cout << "Total Page Faults: " << page_faults << endl;
    }

    void run() {
        int choice;
        do {
            cout << "\nPage Replacement Algorithms:\n"
                 << "1. FIFO\n"
                 << "2. LRU\n"
                 << "3. Optimal\n"
                 << "4. MRU\n"
                 << "5. Exit\n"
                 << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: fifo(); break;
                case 2: lru(); break;
                case 3: optimal(); break;
                case 4: mru(); break;
                case 5: cout << "Exiting...\n"; break;
                default: cout << "Invalid choice!\n";
            }
        } while (choice != 5);
    }
};

int main() {
    PageReplacement pr;
    pr.inputData();
    pr.run();
    return 0;
}