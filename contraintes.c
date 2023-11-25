#include "contraintes.h"
#include <stdio.h>

//contrainte exclusion  :

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

int estExclue(ExclusionPair exclusions[], int nombreContraintes, int operation1, int operation2) {
    for (int i = 0; i < nombreContraintes; ++i) {
        if ((exclusions[i].operation1 == operation1 && exclusions[i].operation2 == operation2) ||
            (exclusions[i].operation1 == operation2 && exclusions[i].operation2 == operation1)) {
            return 1; //les operations ne peuvent pas être affectées à la même station
        }
    }
    return 0; //les operations peuvent être affectées à la même station
}

//contrainte precedence :

void chargerContraintesPrecedence(GraphePrecedence *graphe) {
    FILE* fichier = ouvrirFichier("precedences.txt", "r");
    if (fichier != NULL) {
        while (fscanf(fichier, "%d %d", &graphe->operationPrecedente, &graphe->operationSuivante) == 2) {
            ajouterRelationPrecedence(graphe, graphe->operationPrecedente, graphe->operationSuivante);
        }
        fclose(fichier);
    }
}

void initialiserGraphe(GraphePrecedence *graphe) {
    for (int i = 0; i < MAX_OPERATIONS; ++i) {
        for (int j = 0; j < MAX_OPERATIONS; ++j) {
            graphe->matrice[i][j] = 0;
        }
    }
}

void ajouterRelationPrecedence(GraphePrecedence *graphe, int operationPrecedente, int operationSuivante) {
    graphe->matrice[operationPrecedente][operationSuivante] = 1;
}

int doitPreceder(GraphePrecedence *graphe, int operationPrecedente, int operationSuivante) {
    return graphe->matrice[operationPrecedente][operationSuivante];
}

//c3
void initialiserContraintesExclusion(ContraintesExclusion *contraintes) {
    for (int i = 0; i < MAX_OPERATIONS; ++i) {
        for (int j = 0; j < MAX_OPERATIONS; ++j) {
            contraintes->matriceExclusions[i][j] = 0;
        }
    }

}
void initialiserContraintesTempsCycle(ContraintesTempsCycle *contraintes) {
    contraintes->tempsCycle = 0;
}

int respecteTempsCycle(ContraintesTempsCycle *contraintes, int dureeTotale) {
    return dureeTotale <= contraintes->tempsCycle;
}

//contrainte temps de cycle
int chargerTempsCycleMaximal() {
    FILE* fichier = fopen("temps_cycle.txt", "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier temps_cycle.txt");
        return -1; // Ou une valeur par défaut en cas d'erreur
    }

    int tempsCycle;
    fscanf(fichier, "%d", &tempsCycle);

    fclose(fichier);

    return tempsCycle;
}

//Affichage repartition par station et nombre de station pour exclusion :
void repartitionExclusion(ExclusionPair exclusions[], int nombreContraintes) {
    // Calculer le nombre total d'opérations
    int nombreTotalOperations = MAX_OPERATIONS;

    // Calculer le nombre total de stations nécessaires
    int nombreStations = calculerNombreStations(nombreTotalOperations);

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
        if (!estExclue(exclusions, nombreContraintes, i, /* autre opération à vérifier */)) {
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

int trouverStationMin(int operationsParStation[], int nombreStations) {
    int stationMin = 0;
    for (int i = 1; i < nombreStations; ++i) {
        if (operationsParStation[i] < operationsParStation[stationMin]) {
            stationMin = i;
        }
    }
    return stationMin;
}
