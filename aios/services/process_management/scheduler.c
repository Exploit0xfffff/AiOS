#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 5

// Process structure
typedef struct {
    int pid; // Process ID
    int burst_time; // Time required for execution
    int remaining_time; // Remaining execution time
} Process;

// Round-robin scheduling function
void roundRobin(Process processes[], int n, int quantum) {
    int remaining_processes = n;
    int current_time = 0;

    while (remaining_processes > 0) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                if (processes[i].remaining_time > quantum) {
                    current_time += quantum;
                    processes[i].remaining_time -= quantum;
                } else {
                    current_time += processes[i].remaining_time;
                    processes[i].remaining_time = 0;
                    printf("Process %d completed at time %d\n", processes[i].pid, current_time);
                    remaining_processes--;
                }
            }
        }
    }
}

int main() {
    Process processes[MAX_PROCESSES] = {
        {1, 10, 10},
        {2, 5, 5},
        {3, 8, 8},
        {4, 3, 3},
        {5, 12, 12}
    };
    int quantum = 4; // Example quantum for round-robin scheduling

    printf("Round-Robin Scheduler\n");
    roundRobin(processes, MAX_PROCESSES, quantum);

    return 0;
}
#include <stdio.h>

#define MAX 1000 // Maximum size of the priority queue

int queue[MAX];
int n = 0;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void push(int data) {
    int i = n++;
    queue[i] = data;

    while (i > 0) {
        int parent = (i - 1) / 2;
        if (queue[parent] <= queue[i]) break;
        swap(&queue[i], &queue[parent]);
        i = parent;
    }
}

int pop() {
    int ret = queue[0];
    int data = queue[--n];

    int i = 0;
    while (i * 2 + 1 < n) {
        int child1 = i * 2 + 1;
        int child2 = i * 2 + 2;

        if (child2 < n && queue[child2] < queue[child1]) {
            child1 = child2;
        }

        if (queue[child1] >= data) break;
        queue[i] = queue[child1];
        i = child1;
    }

    queue[i] = data;
    return ret;
}

int main() {
    push(3);
    push(5);
    push(1);
    push(2);

    while (n > 0) {
        printf("%d\n", pop());
    }

    return 0;
}