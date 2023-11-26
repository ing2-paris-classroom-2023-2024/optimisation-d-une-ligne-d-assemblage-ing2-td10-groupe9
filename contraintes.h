#ifndef PROJET_CONTRAINTES_H
#define PROJET_CONTRAINTES_H
#define MAX_OPERATIONS 100

//c1
typedef struct {
    int operation1;
    int operation2;
} ExclusionPair;
//c2
typedef struct {
    int matrice[MAX_OPERATIONS][MAX_OPERATIONS];
} GraphePrecedence;
//c3
typedef struct {
    int matriceExclusions[MAX_OPERATIONS][MAX_OPERATIONS];
} ContraintesExclusion;

typedef struct {
    int matricePrecedence[MAX_OPERATIONS][MAX_OPERATIONS];
} ContraintesPrecedence;

typedef struct {
    int tempsCycle;
} ContraintesTempsCycle;

//c1
void chargerContraintesExclusion(ExclusionPair exclusions[], int* nombreContraintes);
int estExclue(ExclusionPair exclusions[], int nombreContraintes, int operation1, int operation2);
//c2
void chargerContraintesPrecedence(GraphePrecedence *graphe);
void initialiserGraphe(GraphePrecedence *graphe);
void ajouterRelationPrecedence(GraphePrecedence *graphe, int operationPrecedente, int operationSuivante);
int doitPreceder(GraphePrecedence *graphe, int operationPrecedente, int operationSuivante);
//c3
void initialiserContraintesExclusion(ContraintesExclusion *contraintes);
void initialiserContraintesPrecedence(ContraintesPrecedence *contraintes);
void initialiserContraintesTempsCycle(ContraintesTempsCycle *contraintes);
int respecteTempsCycle(ContraintesTempsCycle *contraintes, int dureeTotale);
void libererMemoireContraintes(ContraintesExclusion *exclusions, ContraintesPrecedence *precedence, ContraintesTempsCycle *tempsCycle);
int chargerTempsCycleMaximal();

////c3
void initialiserContraintesExclusion(ContraintesExclusion *contraintes);
void initialiserContraintesPrecedence(ContraintesPrecedence *contraintes);
void initialiserContraintesTempsCycle(ContraintesTempsCycle *contraintes);
int respecteTempsCycle(ContraintesTempsCycle *contraintes, int dureeTotale);
void libererMemoireContraintes(ContraintesExclusion *exclusions, ContraintesPrecedence *precedence, ContraintesTempsCycle *tempsCycle);
int chargerTempsCycleMaximal();



#endif //PROJET_CONTRAINTES_H
