#include <stdio.h>
#include <stdlib.h>
#include <algorithm> // for sort function
#include <vector>    // for dynamic arrays
#include <limits>    // for INT_MAX
#include <cstdlib>   // for system()

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

void clearScreen() {
    system(CLEAR);
}

void fcfs(const std::vector<int>& requests, int head) {
    int total_movement = 0;
    int current = head;
    
    printf("\nFCFS Scheduling:\n");
    printf("Head Movement: %d -> ", current);
    
    for(int req : requests) {
        total_movement += abs(req - current);
        current = req;
        printf("%d", current);
        if(&req != &requests.back()) printf(" -> ");
    }
    
    printf("\nTotal Head Movement: %d\n", total_movement);
    printf("Average Head Movement: %.2f\n", static_cast<float>(total_movement)/requests.size());
}

void sstf(std::vector<int> requests, int head) {
    int total_movement = 0;
    int current = head;
    
    printf("\nSSTF Scheduling:\n");
    printf("Head Movement: %d -> ", current);
    
    while(!requests.empty()) {
        auto closest = std::min_element(requests.begin(), requests.end(),
            [current](int a, int b) {
                return abs(a - current) < abs(b - current);
            });
        
        total_movement += abs(*closest - current);
        current = *closest;
        printf("%d", current);
        if(requests.size() > 1) printf(" -> ");
        
        requests.erase(closest);
    }
    
    printf("\nTotal Head Movement: %d\n", total_movement);
    printf("Average Head Movement: %.2f\n", static_cast<float>(total_movement)/requests.size());
}

void scan(std::vector<int> requests, int head, int direction) {
    int total_movement = 0;
    int current = head;
    
    // Add boundary values (0 and 199 are typical disk boundaries)
    requests.push_back(0);
    requests.push_back(199);
    
    // Sort all requests
    std::sort(requests.begin(), requests.end());
    
    printf("\nSCAN Scheduling (Direction: %s):\n", direction ? "Right" : "Left");
    printf("Head Movement: %d -> ", current);
    
    if(direction) { // Right direction
        // Find first request >= head
        auto it = std::lower_bound(requests.begin(), requests.end(), head);
        
        // Move right to end
        for(; it != requests.end(); ++it) {
            total_movement += abs(*it - current);
            current = *it;
            printf("%d -> ", current);
        }
        
        // Move left from next-to-last left of original position
        auto rit = std::lower_bound(requests.begin(), requests.end(), head);
        if(rit != requests.begin()) {
            for(--rit; rit != requests.begin(); --rit) {
                total_movement += abs(*rit - current);
                current = *rit;
                printf("%d -> ", current);
            }
            total_movement += abs(*rit - current);
            current = *rit;
            printf("%d", current);
        }
    } else { // Left direction
        // Find first request <= head
        auto it = std::upper_bound(requests.begin(), requests.end(), head);
        if(it != requests.begin()) --it;
        
        // Move left to start
        for(; it != requests.begin(); --it) {
            total_movement += abs(*it - current);
            current = *it;
            printf("%d -> ", current);
        }
        total_movement += abs(*it - current);
        current = *it;
        printf("%d -> ", current);
        
        // Move right from next position
        auto fit = std::upper_bound(requests.begin(), requests.end(), head);
        for(; fit != requests.end(); ++fit) {
            total_movement += abs(*fit - current);
            current = *fit;
            printf("%d", current);
            if(fit + 1 != requests.end()) printf(" -> ");
        }
    }
    
    printf("\nTotal Head Movement: %d\n", total_movement);
    printf("Average Head Movement: %.2f\n", static_cast<float>(total_movement)/(requests.size()-2)); // -2 for boundaries
}

int main() {
    std::vector<int> requests;
    int n, head, direction;
    
    printf("Enter number of disk requests: ");
    scanf("%d", &n);
    
    printf("Enter the requests: ");
    for(int i = 0; i < n; i++) {
        int req;
        scanf("%d", &req);
        requests.push_back(req);
    }
    
    printf("Enter initial head position: ");
    scanf("%d", &head);
    
    while(true) {
        clearScreen();
        printf("\nDisk Scheduling Algorithms:\n");
        printf("1. FCFS\n");
        printf("2. SSTF\n");
        printf("3. SCAN\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        
        int choice;
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                fcfs(requests, head);
                break;
            case 2:
                sstf(requests, head);
                break;
            case 3:
                printf("Enter direction (1 for Right, 0 for Left): ");
                scanf("%d", &direction);
                scan(requests, head, direction);
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice!\n");
        }
        
        printf("\nPress Enter to continue...");
        while(getchar() != '\n'); // Clear input buffer
        getchar(); // Wait for Enter
    }
    
    return 0;
}