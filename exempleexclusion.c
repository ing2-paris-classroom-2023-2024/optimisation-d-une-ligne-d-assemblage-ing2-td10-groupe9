#include <stdio.h>
#include <stdlib.h>

#define MAX_OPERATIONS 35

int exclusions[][2] = {{1, 4}, {1, 17}, {1, 20}, {2, 11}, {3, 24}, {4, 15}, {5, 22}, {6, 24}, {8, 21}, {9, 22},
                       {10, 15}, {11, 31}, {12, 13}, {12, 20}, {15, 17}, {16, 17}, {22, 26}, {30, 33}, {31, 32}, {33, 35}};

int is_valid(int schedule[MAX_OPERATIONS], int operation, int station) {
    for (int i = 0; i < MAX_OPERATIONS; ++i) {
        if (schedule[i] == station) {
            for (int j = 0; j < sizeof(exclusions) / sizeof(exclusions[0]); ++j) {
                if ((i + 1 == operation && schedule[exclusions[j][1] - 1] == station) ||
                    (i + 1 == exclusions[j][1] && schedule[operation - 1] == station)) {
                    return 0; // Invalid assignment due to exclusion constraint
                }
            }
        }
    }
    return 1;
}

int main() {
    int schedule[MAX_OPERATIONS];

    for (int i = 0; i < MAX_OPERATIONS; ++i) {
        schedule[i] = -1; // Initialize schedule to -1 (unassigned)
    }

    for (int i = 0; i < MAX_OPERATIONS; ++i) {
        for (int j = 0; j < MAX_OPERATIONS; ++j) {
            if (is_valid(schedule, i + 1, j)) {
                schedule[i] = j;
                break;
            }
        }
    }

    // Print the schedule
    for (int i = 0; i < MAX_OPERATIONS; ++i) {
        printf("Operation %d assigned to Station %d\n", i + 1, schedule[i]);
    }

    return 0;
}
