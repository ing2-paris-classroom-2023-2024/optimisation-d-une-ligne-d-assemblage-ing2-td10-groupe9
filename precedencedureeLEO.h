//
// Created by lans0 on 03/12/2023.
//

#ifndef TESTJOSS_PRECEDENCE_H
#define TESTJOSS_PRECEDENCE_H

#endif //TESTJOSS_PRECEDENCE_H

typedef struct {
    int sommet;
    double temps;
    int positionne;
    int nb_predecesseurs;
    int* predecesseurs;
} Sommet;

typedef struct {
    int station;
    int* sommets;
    int nb_sommets;
    int temps_restant;
} Station;



int est_predecesseur(Sommet* sommet, int id, int nb_stations, Station* stations)
{
    // verifier qu'un sommet n'est pas prédécesseur d'un sommet qui n'est pas dans la station en cours ou les précédentes
    int nb_trouve=0;
    for (int i = 0; i < nb_stations; i++) // on percourt les stations existantes
    {
        for (int j=0; j < stations[i].nb_sommets; j++) // on parcourt les sommets de chaque stations
        {
            for (int k=0; k < sommet[id].nb_predecesseurs;k++) // on parcourt les predecesseurs du sommet recherché
            {
                if (stations[i].sommets[j] == sommet[id].predecesseurs[k])
                {
                    nb_trouve++;
                }
            }
        }
    }
    if (sommet[id].nb_predecesseurs==nb_trouve)
    {
        return 0;
    }
    return 1;
}
