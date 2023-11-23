#include <stdio.h>

//contraintes d'exclusion :
//deux opérations ne peuvent pas être effectuées par la même station
//
#include "contraintes.h"

int main() {
    // Utilisation des fonctions de contraintes
    ExclusionPair exclusions[20];
    int nombreContraintes;
    int operation1 = 1;
    int operation2 = 2;
    GraphePrecedence graphe;
    initialiserGraphe(&graphe);

    chargerContraintesExclusion(exclusions, &nombreContraintes);

    // Test de contrainte d'exclusion
    if (estExclue(exclusions, nombreContraintes, operation1, operation2)) {
        printf("Les operations %d et %d ne peuvent pas etre affectees a la meme station.\n",operation1,operation2);
    } else {
        printf("Les operations %d et %d peuvent etre affectees a la meme station.\n",operation1,operation2);
    }

    // Ajouter des relations de précédence
    ajouterRelationPrecedence(&graphe, 1, 3);
    ajouterRelationPrecedence(&graphe, 3, 5);

    // Test de la contrainte de précédence
    if (doitPreceder(&graphe, 2, 3)) {
        printf("L'operation 1 doit etre effectuee avant l'operation 3.\n");
    } else {
        printf("L'operation 1 n'a pas de contrainte de precedence avec l'operation 3.\n");
    }

    // Utiliser la fonction pour charger le temps de cycle maximal
    int tempsCycleMaximal = chargerTempsCycleMaximal();

    // Vérifier si le chargement du temps de cycle a réussi
    if (tempsCycleMaximal == -1) {
        // Gérer l'erreur ici, par exemple, en utilisant une valeur par défaut ou en quittant le programme.
        printf("Erreur lors du chargement du temps de cycle maximal. Utilisation de la valeur par défaut.\n");
        tempsCycleMaximal = 10; // Valeur par défaut
    }

    // Utiliser le temps de cycle maximal dans votre logique métier
    ContraintesTempsCycle contraintesTempsCycle;
    initialiserContraintesTempsCycle(&contraintesTempsCycle);
    contraintesTempsCycle.tempsCycle = tempsCycleMaximal;

    if (respecteTempsCycle(&contraintesTempsCycle, tempsCycleMaximal)) {
        printf("Le temps de cycle maximal est respecte.\n");
    } else {
        printf("Le temps de cycle maximal n'est pas respecte.\n");
    }

    return 0;
}
