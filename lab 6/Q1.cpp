#include <iostream>
using namespace std;

const int n = 4;
int completedPhilos = 0;

struct Fork {
    bool taken = false;
};

struct Philosopher {
    bool leftFork = false;
    bool rightFork = false;
};

Fork forks[n];
Philosopher philosophers[n];

void dine(int philID) {
    // Philosopher has both forks and completes dining
    if (philosophers[philID].leftFork && philosophers[philID].rightFork) {
        cout << "Philosopher " << philID + 1 << " completed his dinner\n";
        philosophers[philID].leftFork = philosophers[philID].rightFork = false;
        
        // Release forks
        forks[philID].taken = false;
        int otherFork = (philID == 0) ? n - 1 : philID - 1;
        forks[otherFork].taken = false;
        
        cout << "Philosopher " << philID + 1 << " released fork " 
             << philID + 1 << " and fork " << otherFork + 1 << "\n";
        completedPhilos++;
    }
    // Philosopher has left fork and tries to get right fork
    else if (philosophers[philID].leftFork && !philosophers[philID].rightFork) {
        if (philID == n - 1) {
            // Last philosopher tries right fork first to prevent deadlock
            if (!forks[philID].taken) {
                forks[philID].taken = philosophers[philID].rightFork = true;
                cout << "Fork " << philID + 1 << " taken by philosopher " 
                     << philID + 1 << "\n";
            } else {
                cout << "Philosopher " << philID + 1 << " is waiting for fork " 
                     << philID + 1 << "\n";
            }
        } else {
            int rightForkID = (philID == 0) ? n - 1 : philID - 1;
            if (!forks[rightForkID].taken) {
                forks[rightForkID].taken = philosophers[philID].rightFork = true;
                cout << "Fork " << rightForkID + 1 << " taken by philosopher " 
                     << philID + 1 << "\n";
            } else {
                cout << "Philosopher " << philID + 1 << " is waiting for fork " 
                     << rightForkID + 1 << "\n";
            }
        }
    }
    // Philosopher tries to get left fork first
    else if (!philosophers[philID].leftFork) {
        if (philID == n - 1) {
            // Last philosopher tries left fork (right neighbor's fork) first
            int leftForkID = philID - 1;
            if (!forks[leftForkID].taken) {
                forks[leftForkID].taken = philosophers[philID].leftFork = true;
                cout << "Fork " << leftForkID + 1 << " taken by philosopher " 
                     << philID + 1 << "\n";
            } else {
                cout << "Philosopher " << philID + 1 << " is waiting for fork " 
                     << leftForkID + 1 << "\n";
            }
        } else {
            if (!forks[philID].taken) {
                forks[philID].taken = philosophers[philID].leftFork = true;
                cout << "Fork " << philID + 1 << " taken by philosopher " 
                     << philID + 1 << "\n";
            } else {
                cout << "Philosopher " << philID + 1 << " is waiting for fork " 
                     << philID + 1 << "\n";
            }
        }
    }
}

int main() {
    // Initialize all forks and philosophers
    for (int i = 0; i < n; i++) {
        forks[i].taken = false;
        philosophers[i].leftFork = philosophers[i].rightFork = false;
    }

    while (completedPhilos < n) {
        for (int i = 0; i < n; i++) {
            dine(i);
        }
        cout << "\nNumber of philosophers completed dinner: " 
             << completedPhilos << "\n\n";
    }

    return 0;
}