#include "contraintes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int trouverStationMin(int operationsParStation[], int nombreStations) {
    int stationMin = 0;
    for (int i = 1; i < nombreStations; ++i) {
        if (operationsParStation[i] < operationsParStation[stationMin]) {
            stationMin = i;
        }
    }
    return stationMin;
}

void chargerContraintesExclusion(ExclusionPair exclusions[], int* nombreContraintes) {
    FILE* fichier = fopen("exclusions.txt", "r"); //ouverture du fichier
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier exclusions.txt");
        return;
    }
    *nombreContraintes = 0;
    while (fscanf(fichier, "%d %d", &exclusions[*nombreContraintes].operation1, &exclusions[*nombreContraintes].operation2) == 2) {
        (*nombreContraintes)++;
    }
    fclose(fichier); //fermeture du fichier
}

int estExclue(ExclusionPair exclusions[], int nombreContraintes, int operation, int operationsParStation[], int station) {
    // Vérifier si l'opération est exclue avec une opération déjà assignée à la station
    for (int i = 0; i < nombreContraintes; ++i) {
        int autreOperation = operationsParStation[station - 1];

        if ((exclusions[i].operation1 == operation && exclusions[i].operation2 == autreOperation) ||
            (exclusions[i].operation1 == autreOperation && exclusions[i].operation2 == operation)) {
            return 1; // Les opérations ne peuvent pas être affectées à la même station
        }
    }
    return 0; // Les opérations peuvent être affectées à la même station
}

void initialiserGraphe(GraphePrecedence *graphe) {
    for (int i = 0; i < MAX_OPERATIONS; ++i) {
        for (int j = 0; j < MAX_OPERATIONS; ++j) {
            graphe->matrice[i][j] = 0;
        }
    }
}



//c3
void initialiserContraintesExclusion(ContraintesExclusion *contraintes) {
    for (int i = 0; i < MAX_OPERATIONS; ++i) {
        for (int j = 0; j < MAX_OPERATIONS; ++j) {
            contraintes->matriceExclusions[i][j] = 0;
        }
    }

}


int calculerNombreStations(ExclusionPair exclusions[], int nombreContraintes, int nombreTotalOperations) {
    int nombreStations = 0;

    // Utiliser un tableau pour suivre le nombre d'opérations assignées à chaque station
    int operationsParStation[nombreTotalOperations];

    for (int i = 0; i < nombreTotalOperations; ++i) {
        operationsParStation[i] = 0;
    }

    for (int i = 1; i <= nombreTotalOperations; ++i) {
        int station = -1;

        // Trouver la première station où l'opération peut être affectée
        for (int j = 0; j < nombreStations; j++) {
            if (!estExclue(exclusions, nombreContraintes, i, operationsParStation, j)) {
                station = j;
                break;
            }
        }

        // Si aucune station n'est trouvée, ajouter une nouvelle station
        if (station == -1) {
            station = nombreStations;
            nombreStations++;
        }

        // Affecter l'opération à la station trouvée
        operationsParStation[station]++;
    }

    return nombreStations;
}


//Affichage repartition par station et nombre de station pour exclusion :
void repartitionExclusion(ExclusionPair exclusions[], int nombreContraintes) {
    // Calculer le nombre total d'opérations
    int nombreTotalOperations = MAX_OPERATIONS;

    // Calculer le nombre total de stations nécessaires
    int nombreStations = calculerNombreStations(exclusions,nombreContraintes,nombreTotalOperations);

    // Tableau pour stocker le nombre d'opérations par station
    int operationsParStation[nombreStations];

    // Initialiser le tableau à zéro
    for (int i = 0; i < nombreStations; ++i) {
        operationsParStation[i] = 0;
    }

    // Affecter les opérations à chaque station en tenant compte de la contrainte d'exclusion
    for (int i = 1; i <= nombreTotalOperations; ++i) {
        // Trouver la station avec le moins d'opérations affectées
        int stationMin = trouverStationMin(operationsParStation, nombreStations);

        // Vérifier si l'opération i peut être affectée à une station
        if (!estExclue(exclusions, nombreContraintes, i, operationsParStation, stationMin+1))/* autre opération à vérifier */ {
            // Affecter l'opération à la station avec le moins d'opérations affectées
            operationsParStation[stationMin]++;
        }
    }

    // Afficher les résultats de la répartition
    printf("Repartition avec contrainte d'exclusion :\n");
    printf("Nombre total de stations : %d\n", nombreStations);

    // Afficher les opérations affectées à chaque station
    for (int station = 0; station < nombreStations; ++station) {
        printf("Station %d :", station + 1);
        // Afficher le nombre d'opérations affectées à cette station
        printf(" %d opérations\n", operationsParStation[station]);
    }
}


int main() {
    // Initialisation des structures
    ExclusionPair exclusions[100];
    int nombreContraintes = 0;

    // Demander à l'utilisateur le nom du fichier d'exclusion
    char nomFichier[100];  // Choisissez une taille maximale raisonnable
    printf("Veuillez entrer le nom du fichier d'exclusion : ");

    if (fgets(nomFichier, sizeof(nomFichier), stdin) == NULL) {
        fprintf(stderr, "Erreur lors de la lecture du nom du fichier.\n");
        return EXIT_FAILURE;
    }

    // Supprimer le caractère de nouvelle ligne (\n) du nom du fichier
    size_t len = strlen(nomFichier);
    if (len > 0 && nomFichier[len - 1] == '\n') {
        nomFichier[len - 1] = '\0';
    }

    // Charger les contraintes d'exclusion à partir du fichier
    chargerContraintesExclusion(exclusions, &nombreContraintes);

    // Appel de la fonction de répartition avec contrainte d'exclusion
    repartitionExclusion(exclusions, nombreContraintes);

    return EXIT_SUCCESS;
}
