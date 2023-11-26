#include <stdio.h>
#include <stdlib.h>

#define MAX_OPERATIONS 35
#define MAX_EXCLUSIONS 21

typedef struct {
    int operation1;
    int operation2;
} ExclusionPair;

void chargerContraintesExclusion(ExclusionPair exclusions[], int *nombreContraintes) {
    FILE *fichier = fopen("exclusions.txt", "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier exclusions.txt");
        exit(EXIT_FAILURE);
    }
    *nombreContraintes = 0;
    while (fscanf(fichier, "%d %d", &exclusions[*nombreContraintes].operation1, &exclusions[*nombreContraintes].operation2) == 2) {
        (*nombreContraintes)++;
    }
    fclose(fichier);
}

int is_valid(int schedule[MAX_OPERATIONS], int operation, int station, ExclusionPair exclusions[], int numExclusions) {
    for (int i = 0; i < MAX_OPERATIONS; ++i) {
        if (schedule[i] == station) {
            for (int j = 0; j < numExclusions; ++j) {
                if ((i + 1 == operation && schedule[exclusions[j].operation2 - 1] == station) ||
                    (i + 1 == exclusions[j].operation2 && schedule[operation - 1] == station)) {
                    return 0; // Invalid assignment due to exclusion constraint
                }
            }
        }
    }
    return 1;
}

int main() {
    ExclusionPair exclusions[MAX_EXCLUSIONS];
    int numExclusions;

    chargerContraintesExclusion(exclusions, &numExclusions);

    int schedule[MAX_OPERATIONS];

    for (int i = 0; i < MAX_OPERATIONS; ++i) {
        schedule[i] = -1; // Initialize schedule to -1 (unassigned)
    }

    for (int i = 0; i < MAX_OPERATIONS; ++i) {
        for (int j = 0; j < MAX_OPERATIONS; ++j) {
            if (is_valid(schedule, i + 1, j, exclusions, numExclusions)) {
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