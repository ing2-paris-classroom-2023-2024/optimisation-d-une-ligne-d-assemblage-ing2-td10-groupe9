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
        for (int j = 0; j < nombreStations; ++j) {
            if (!estExclue(exclusions, nombreContraintes, i, operationsParStation, j + 1)) {
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
