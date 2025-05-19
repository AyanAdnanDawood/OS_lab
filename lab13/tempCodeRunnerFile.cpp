#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void fcfs(int requests[], int n, int head) {
    int total_movement = 0;
    int current = head;
    
    printf("\nFCFS Scheduling:\n");
    printf("Head Movement: %d -> ", current);
    
    for(int i = 0; i < n; i++) {
        total_movement += abs(requests[i] - current);
        current = requests[i];
        printf("%d", current);
        if(i != n-1) printf(" -> ");
    }
    
    printf("\nTotal Head Movement: %d\n", total_movement);
    printf("Average Head Movement: %.2f\n", (float)total_movement/n);
}

void sstf(int requests[], int n, int head) {
    int total_movement = 0;
    int current = head;
    int completed = 0;
    int visited[100] = {0};
    
    printf("\nSSTF Scheduling:\n");
    printf("Head Movement: %d -> ", current);
    
    while(completed < n) {
        int min_distance = 9999;
        int next_index = -1;
        
        for(int i = 0; i < n; i++) {
            if(!visited[i]) {
                int distance = abs(requests[i] - current);
                if(distance < min_distance) {
                    min_distance = distance;
                    next_index = i;
                }
            }
        }
        
        visited[next_index] = 1;
        total_movement += min_distance;
        current = requests[next_index];
        completed++;
        
        printf("%d", current);
        if(completed != n) printf(" -> ");
    }
    
    printf("\nTotal Head Movement: %d\n", total_movement);
    printf("Average Head Movement: %.2f\n", (float)total_movement/n);
}

void scan(int requests[], int n, int head, int direction) {
    int total_movement = 0;
    int current = head;
    int sorted[100];
    int count = 0;
    
    // Create a sorted array including 0 and head position
    for(int i = 0; i < n; i++) {
        sorted[count++] = requests[i];
    }
    sorted[count++] = head;
    sorted[count++] = 0; // Assuming 0 is the minimum track
    
    // Sort the array
    for(int i = 0; i < count; i++) {
        for(int j = i+1; j < count; j++) {
            if(sorted[i] > sorted[j]) {
                int temp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }
        }
    }
    
    printf("\nSCAN Scheduling (Direction: %s):\n", direction == 1 ? "Right" : "Left");
    printf("Head Movement: %d -> ", current);
    
    if(direction == 1) { // Right direction
        // Find head position in sorted array
        int pos = 0;
        while(pos < count && sorted[pos] < head) pos++;
        
        // Move right
        for(int i = pos; i < count; i++) {
            total_movement += abs(sorted[i] - current);
            current = sorted[i];
            printf("%d -> ", current);
        }
        
        // Move left
        for(int i = pos-1; i >= 0; i--) {
            total_movement += abs(sorted[i] - current);
            current = sorted[i];
            printf("%d", current);
            if(i != 0) printf(" -> ");
        }
    } else { // Left direction
        // Find head position in sorted array
        int pos = count-1;
        while(pos >= 0 && sorted[pos] > head) pos--;
        
        // Move left
        for(int i = pos; i >= 0; i--) {
            total_movement += abs(sorted[i] - current);
            current = sorted[i];
            printf("%d -> ", current);
        }
        
        // Move right
        for(int i = pos+1; i < count; i++) {
            total_movement += abs(sorted[i] - current);
            current = sorted[i];
            printf("%d", current);
            if(i != count-1) printf(" -> ");
        }
    }
    
    printf("\nTotal Head Movement: %d\n", total_movement);
    printf("Average Head Movement: %.2f\n", (float)total_movement/n);
}

int main() {
    int n, head, direction;
    int requests[100];
    
    clrscr();
    printf("Enter number of disk requests: ");
    scanf("%d", &n);
    
    printf("Enter the requests: ");
    for(int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }
    
    printf("Enter initial head position: ");
    scanf("%d", &head);
    
    while(1) {
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
                fcfs(requests, n, head);
                break;
            case 2:
                sstf(requests, n, head);
                break;
            case 3:
                printf("Enter direction (1 for Right, 0 for Left): ");
                scanf("%d", &direction);
                scan(requests, n, head, direction);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
        
        printf("\nPress any key to continue...");
        getch();
        clrscr();
    }
    
    return 0;
}