/*******************************************************************************************
* En fonction des fonctions

* Romain Larramendy, Lucas Bremard, Killian Baert, Valentin Hecht, Thomas Tissier, Maxence Dhaynaut, Benjamin Chane, Louis-Marie Bossard 

* FISA-TI23 Copyright 2020-2020
********************************************************************************************/
// Énumération des différents types de lexems existants
typedef enum
{
    REEL,
    OPERATEUR,
    FONCTION,
    ERREUR,
    FIN,
    PAR_OUV,
    PAR_FERM,
    VARIABLE,
    BAR_OUV,
    BAR_FERM,
    ABSOLU
} typelexem;
// Énumération des différents types d'opérateur existants
typedef enum
{
    PLUS,
    MOINS,
    FOIS,
    DIV,
    PUIS
} typeoperateur;
// Énumération des différents types de fonction existantes
typedef enum
{
    ABS,
    SIN,
    SQRT,
    LOG,
    COS,
    TAN,
    EXP,
    ENTIER,
    VAL_NEG
} typefonction;
// Énumération des différentes erreurs possible (coté évaluateur)
typedef enum
{
    DIV_ZERO,
    SQRT_NEG,
    PAR_NONFERM,
    PAR_NONOUVER,
    DOUBLE_OPE,
    ORTO_FONC,
    MAJ_FONC,
    BAR_NONFERME,
    VIRGULE
} typeerreur;
// Énumération des différents types de valeurs existantes
typedef union
{
    float reel;
    typefonction fonction;
    typeoperateur operateur;
    typeerreur erreur;
} typevaleur;
// Énumération des différents types de jetons existants
typedef struct
{
    typelexem lexem;
    typevaleur valeur;
} typejeton;
// Déclaration de l'arbre
typedef struct Noeud
{
    typejeton jeton;
    struct Noeud *pjetonpreced;
    struct Noeud *pjetonsuiv;
} Noeud;
typedef Noeud *Arbre;