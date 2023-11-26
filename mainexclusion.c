#include "contraintes.h"
#include <stdio.h>

int main() {
    // Initialisation des structures
    ExclusionPair exclusions[MAX_EXCLUSIONS];
    int nombreContraintes = 0;

    // Charger les contraintes d'exclusion à partir du fichier
    chargerContraintesExclusion(exclusions, &nombreContraintes);

    // Appel de la fonction de répartition avec contrainte d'exclusion
    repartitionExclusion(exclusions, nombreContraintes);

    return 0;
}
