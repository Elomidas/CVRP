# Rapport Optimisation Discrète - Printemps 2018

### Étudiants
 -  JACOUD Bastien
 -  REMOND Victor
 
[GraphExampleGenetic] : (graphviz/example1.svg)
 
## I - Introduction



## II - Algorithme Tabou



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