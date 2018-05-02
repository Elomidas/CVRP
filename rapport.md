# Rapport Optimisation Discrète - Printemps 2018

### Étudiants
 - **JACOUD Bastien**
 - **REMOND Victor**
 
 <br>
 
 * Lien [dépôt GitHub C++ classique](https://github.com/Elomidas/CVRP)
 
 * Lien [dépôt GitHub Qt](https://github.com/Elomidas/CVRP-Qt)
 
 * Téléchargement [Version Stable]() 
 
 * [GraphExample1] : (graphviz/example1.svg)
 
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

## II - Représentation d'un graphe

   Dans un premier temps, nous avons dû convenir d'un objet représentant un graphe afin de pouvoir manipuler nos données. L'une de nos principales préocupations étaient de pouvoir l'utiliser de façon relativement rapide, nous avons donc essayer de créer des fonctions de manipulation un minimum optimisées. La structure interne de notre classe ```Graph``` peut se décomposer en deux grosses partie : 
   
 -  La représentation des Nœuds et des Distances.
 -  La représentations des chemins empruntés pour l'instance actuelle du Graphe.
 
   Nous aborderons ensuite les choix que nous avons fait en ce qui concerne la visualisation de nos résultats :

 -  Visualisation en console.
 -  Graphe au format SVG.
 
   Enfin, nous expliqueront comment est construite la solution initiale.

### 1 - Représentation du graphe

#### A - Nœuds et Distances

   Nous chargeons tout d'abbord les nœuds depuis le fichier de sources, en sachant que chaque nœud possède un id, une quantité de produits à livrer, et une position représentée par un couple {x,y}. 
   
   Une fois ces nœuds chargés en mémoire, on génère la matrice des distances. Comme la distance entre deux nœuds A et B est la même qu'entre B et A, nous ne manipulons pas une matrice carrée complète mais simplement une matrice triangulaire, avec une vérification sur le indices demandés :
  
  - La fonction getDistance(index1, index2) réorganise les indices afin de lire distances\[i]\[j] avec i = max(index1, index2) et j = min(index1, index2).
  
#### B - Parcours du Graphe

   Pour représenté les chemins empruntés par les camions, nous avons créé une classe ```Truck```, qui est une liste chainée améliorée de nœuds. A chaque ajout d'un nœud sur le parcours d'un camion, ce dernier est marqué comme utilisé. De plus, avant d'ajouter un nœud au parcours d'un camion on vérifie que cela ne cause pas de dépassement de capacité, afin de ne pas générer de graphe qui ne serait pas une solution.
   
   Cette classe permet aussi de calculer la distance parcourue par le camion, ce qui simplifie le calcul du coût total du graph : il nous suffit de sommer la distance parcourue par chaque camion.
   
   Enfin cette classe nous permet d'obtenir un vecteur d'entiers représenatant le parcours du camion. Exemple avec le graph ci-dessous :
   
   ![GraphExamplePath][GraphExample1]
   
   Le parcours bleu sera représenté par le vecteur ```{ 0, 1, 2, 3, 4, 5, 6, 0 }``` et le rouge par le vecteur ```{ 0, 14, 12, 11, 10, 9, 8, 7, 0 }```. Ces vecteurs ne permettent pas de connaitre la distance du parcours, mais restent utiles pour se faire une idée du parcours et comparer rapidement deux graphes à la console.
   
### 2 - Visualisation

#### A - Mode console

   Au commencement du projet, nous avions à travailler en mode console, ce qui nous a obligé à trouver un affichage correct d'une solution. Pour cela, nous avons choiosi d'afficher les vecteurs représentant les différents camions, puis le coût du graphe.
   
   Un exemple de solution affichée serait :
   
```shell
Graphe de base
Truck 1 : 
0 -> 8 -> 18 -> 21 -> 22 -> 27 -> 28 -> 31 -> 0
Truck 2 : 
0 -> 1 -> 6 -> 11 -> 15 -> 24 -> 0
Truck 3 : 
0 -> 9 -> 13 -> 20 -> 25 -> 26 -> 29 -> 0
Truck 4 : 
0 -> 3 -> 4 -> 14 -> 17 -> 19 -> 30 -> 0
Truck 5 : 
0 -> 2 -> 5 -> 7 -> 10 -> 12 -> 16 -> 23 -> 0
Solution's cost : 2215.092281
```

#### B - Interface graphique

   Nous avons ensuite décidé de trouver un moyen pour afficher nos graphes sous leur véritable apparence. Nous avons ainsi choisi d'utiliser *GraphViz*, et plus précisément *dot* pour générer des graphes à partir de simples fichiers texte.
   
   Tous les graphes servant d'exemples dans ce rapport ont été générés par *dot*. Nous générons les fichiers grâce à notre classe ```GraphViz```, puis nous exécutons la ligne de commande permettant de générer les graphes. C'est pour cela que l'ordinateur sur lequel notre programme est executé doit avoir *dot* d'installé. Cette méthode fonctionne parfaitement sous Linux (testé sur plusieurs ordinateurs), mais son fonctionnement sur d'autres OS n'est pas assuré.
   
   Nous avons ensuite décidé de changer de base pour notre programme : nous avions commencé en C++ pur avec CLion comme IDE, mais nous sommes ensuite passé sous Qt afin de pouvoir créer une interface graphique rendant l'utilisation du programme plus intuitive. Parmis les améliorations apportées lors du passage sous Qt se trouve l'apparition d'une fenêtre *Settings* permettant de choisir quel algorithme utiliser et d'en renseigner les paramètres.
   
   ![SettingsWindow][SettingsWindow]
   
   Un objectif de notre passage sous Qt était aussi la création d'une fenêtre de monitoring de l'algorithm :
   
   ![AlgorithmDetails][AlgorithmDetails]
   
   Cependant la partie gauche de la fenêtre qui reste blanche est dûe à une erreur que nous n'avons pas réussi à régler : à cet endroit aurait dû être affiché le graphe de la meilleure solution rencontrée par l'algorithm jusqu'à maintenant.
   
   Les graphes générés restent cependant disponibles dans le dossier ```graphviz/```.
   
### 3 - Génération d'une solution aléatoire

   Afin de pouvoir lancer nos algorithmes, ils nous fallait la possibilité de créer une solution initiale (une seule pour l'algorithme Tabou, une par membre de la population dans le cas de l'algorithme génétique).
   
   Nous avons décidé de générer une simple solution aléatoire comme suit :
   
```algo
Soit N* une copie de l'ensemble des noeuds du graphe
Soit T& une liste de références vers les camions du graphe

Faire :
    go <- true
    Pour N dans N* :
    |   T* <- copie(T&)
    |   i  <- entier aléatoire dans [0;taille(T*)[
    |   ok <- false
    |   Faire :
    |   |   Si ( quantite(N) <= placeLibre(T*[i])
    |   |   |   ajouter N à T*[i]
    |   |   |   ok <- true
    |   |   Sinon
    |   |   |   T* <- T* privé de T[i]
    |   |   |   Si ( taille(T*) == 0 )
    |   |   |   |   //Plus aucun camion disponnible
    |   |   |   |   //Cette solution n'est pas viable
    |   |   |   |   go <- false
    |   |   |   Fin Si
    |   |   Fin Si
    |   Tant Que ( ok == false ET go == true )
    Fin Pour
Tant Que ( go == false )

//Tous les nœuds sont placés, la solution est viable
```

## III - Algorithme Tabou

### 1 - Implémentation

L'implémentation de l'Algorithme Tabou n'est pas des plus compliqué. Pour ce faire, nous utilisons une classe ```TabouAlgorithm```, contenant tous les 
élements indispensables au bon fonctionnement de l'algorithme.

### 2 - Résultats obtenu


## IV - Algorithme Génétique

### 1 - Implémentation

   Avant de se lancer dans l'implémentation de l'algorithme, nous avons déjà dû choisir une représentation pour les membre de la population qui soit relativement facile à manipuler dans le fonctions de reproduction ou de mutation.
   
   Nous avons ainsi fait le choix de voir un ensemble de trajets comme un seul et unique trajet en omettant les passage par le noeud racine. Exemple avec le graph suivant.
   
   ![GraphExampleGenetic][GraphExample1]
   
   Dans ce graph, on remarque deux chemins :
   
   Bleu : ```0 -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 0```
   
   Rouge : ```0 -> 14 -> 13 -> 12 -> 11 -> 10 -> 9 -> 8 -> 7 -> 0```
   
   On modélisera ces deux chemin par un seul vecteur d'entiers comme ci-dessous :
   
   Vecteur : ```{ 1, 2, 3, 4, 5, 6, 14, 13, 12, 11, 10, 9, 8, 7 }```

   La première implémentation de l'algorithme génétique était relativement basique, mais comportait plusieurs défauts. Par exemple, la population était entièrement renouvelée d'une itération à la suivante. 
    
   Les mutations et fonctions de reproduction déjà implémentées étaient cependant déjà bien choisie, avec par exemple une implémentation d'un algorithm de recombination des nœuds. Pour fonctionner, celui-ci créé une matrice d'adjacence pour chacun des deux parents choisis pour ensuite les mettre en commun et créer un fils. Source de l'algorithme *edgeRecombination* : [Wikipedia](https://en.wikipedia.org/wiki/Edge_recombination_operator).
   
   Une seconde fonction de reproduction utilisée était la fonction *NodeSwap*, qui permettait d'intervertir deux nœuds ou plus dans le schéma de représentation d'un membre de la population.

   

## V - Conclusion