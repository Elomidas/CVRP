# Rapport Optimisation Discrète - Printemps 2018

### Étudiants
 - **JACOUD Bastien**
 - **REMOND Victor**
 
 <br>
 
 * Lien [dépôt GitHub Clion](https://github.com/Elomidas/CVRP)
 
 * Lien [dépôt GitHub QT](https://github.com/Elomidas/CVRP-Qt)
 
 * Téléchargement [Version Stable]() 
 
 * [GraphExampleGenetic] : (graphviz/example1.svg)
 
## I - Introduction

Dans le cadre d'un projet, nous avons eu à traiter le cas du *Capacited Vehicule Routing Problem*, ou *CVRP*. 
Le but de cet exercice est de déterminer le meilleur ensemble d'itinéraires, commançant et finissant tous au même point, aussi appelé *dépot*.
Cet ensemble d'itinéraires doit être capable de desservir chacun des points préalablement définis. Il faut alors non seulement déterminer un trajet solution capable de
désservir chacun des points, mais aussi en **minimisant le coût**, c'est à dire en **minimisant la somme des distances** effectuées par les camions.

Pour ce projet, nous avons eu à réaliser deux étapes principales :
 
 - La modélisation du problème sous forme de graphe.
 - L'implémentation des deux algorithmes permettant de diminuer le coût de la solution.
 
Nous avons donc eu à réaliser un algorithme à base de voisinage et un algorithme à base de population. 
Nous avons finalement fait le choix de réaliser une **Recherche Tabou** comme algorithme à base de voisinage ainsi qu'un **Algorithme
Génétique** comme algorithme à base de population.

Afin de minimiser le temps d'exécution de notre application, nous avons fait le choix de réaliser ce projet avec le langage *C++*. Dans un premier temps, 
nous avons utilisé l'IDE *CLion*, puis nous avons par la suite utilisé *QT* afin de réaliser une interface Graphique. 

Pour générer nos graphes, nous utilisons *Graphviz*, comme mention dans notre [Readme](README.md).

## II - Algorithme Tabou

### 1 - Implémentation

L'implémentation de l'Algorithme Tabou n'est pas des plus compliqué. Pour ce faire, nous utilisons une classe ```TabouAlgorithm```, contenant tous les 
élements indispensables au bon fonctionnement de l'algorithme.

### 2 - Résultats obtenu


## III - Algorithme Génétique

### 1 - Implémentation

   Avant de se lancer dans l'implémentation de l'algorithme, nous avons déjà dû choisir une représentation pour les membre de la population qui soit relativement facile à manipuler dans le fonctions de reproduction ou de mutation.
   
   Nous avons ainsi fait le choix de voir un ensemble de trajets comme un seul et unique trajet en omettant les passage par le noeud racine. Exemple avec le graph suivant.
   
   ![GraphExampleGenetic][GraphExampleGenetic]
   
   Dans ce graph, on remarque deux chemins :
   
   Bleu : ```0 -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 0```
   
   Rouge : ```0 -> 14 -> 13 -> 12 -> 11 -> 10 -> 9 -> 8 -> 7 -> 0```
   
   On modélisera ces deux chemin par un seul vecteur d'entiers comme ci-dessous :
   
   Vecteur : ```1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 14 -> 13 -> 12 -> 11 -> 10 -> 9 -> 8 -> 7```

   La première implémentation de l'algorithme génétique était relativement basique, mais comportait plusieurs défauts. Par exemple, la population était entièrement renouvelée d'une itération à la suivante. 
    
   Les mutations et fonctions de reproduction déjà implémentées étaient cependant déjà bien choisie, avec par exemple une implémentation d'un algorithm de recombination des nœuds. Pour fonctionner, celui-ci créé une matrice d'adjacence pour chacun des deux parents choisis pour ensuite les mettre en commun et créer un fils. Source de l'algorithme *edgeRecombination* : [Wikipedia](https://en.wikipedia.org/wiki/Edge_recombination_operator).
   
   Une seconde fonction de reproduction utilisée était la fonction *NodeSwap*, qui permettait d'intervertir deux nœuds ou plus dans le schéma de représentation d'un membre de la population.


## IV - Conclusion