# CSC4526-JIN4 - Post Me If You Can
Chaque jour, l’amour de Cyrano, ne cesse de grandir pour VOTRE crush, ceci n’est pas envisageable. Vous devez empêcher Cyrano de mettre son gros nez trop près de votre dulciné. Pour ce faire, vous devez l'empêcher chaque jour d’envoyer sa lettre. Cependant tous les jours il reviendra plus fort. Ainsi, vous devrez faire de même et armer votre poste préféré. 

## Idées précédentes :
- crossy road (cyrano va à la poste et doit éviter des obstacle)
- empiler des anneaux qui tombent sur le nez de cyrano
- Cyrano combat à la guerre avec son gros nez (escrime de nez)
- Ecrire un poème avec un gros nez qui bloque l’écran

## Grandes lignes : 
- Tower defense de la poste
- l'ennemi c’est cyrano qui arrive avec de plus en plus d’alliés
- armes du 17e (premières armes à feu : fusils recharge lente, armes blanches, chevaux, canons, grenades)
- chaque vague correspond une nouvelle journée
- pour gagner la vague il faut soit se débarrasser de tous les ennemis, soit “tuer” Cyrano pour le faire fuir
- Pour perdre : destruction de la porte de la poste (Cyrano rentre et envoie sa lettre)
- Jeu continue à l’infini jusqu'à que cyrano gagne

## Bibliothèques : 
- SFML
- probablement un truc de machine à état finis
- Dear ImGui ou Parser JSON/XML

## IA : 
- test unitaires
- débogage
- conseils

## Difficultés pressenties:
- les visuels 
- les menus
- organisation générale

## Organisation :
_Ysee_
- creation d’ennemis
- interactions
_Maxence_
- création de map procéduralement
- création bâtiments
- interface utilisateur

Tous les visuels sont en pixel art

## Map : 
- grille 
- chemin
- emplacement bâtiments
- entrées , sortie

## Ennemis : 
- Cyrano (boss) avec un lance pierre (stun car trop moche)
- soldats de base avec fusils coups lents
- soldats de base avec lance
- soldats à cheval avec fusils longue portée
- chiens
- alcoliques kamikases qui se font sauter aux cocktails molotovs

## Batiment :
- Poste (batiment arriere | non modifiable)
- Canon
- mousquetaire arme blanche
- mousquetaire arme à feu

- Attaques ulti
- grenade qui pue smr
- pigeons voyageur à caca corrosif 

## Menu : 
debut : 
- commencer une partie 
- continuer
- Quitter
- Param ???
Pause : 
- quitter
- sauvegarder
- parametres ???
- continuer

## interface utilisateur : 
- placer batiments
- supprimer batiments
- ameliorer batiment / voir stat 
- poser ulti
- barre de vie Cyrano

## Architecture : 
- Map : tableau d’objet tile(x,y) qui peut etre soit un chemin(pointeurs des ennemis) soit un emplacement (doit avoir le pointeur du batiment,) 
- classe ennemis : chaque type est une classe qui herite de ennemis (soldat, cyrano, …)(pv, vitesse de deplacement, vitesse d’attaque, position, tile, type d’attaque )
- classe batiment : heritage pour chaque type (tile, type d’attaque, niveau, vitesse d’attaque)
- classe ulti :  soit grenade(plusieurs attaques) soit pigeon(ennemi) (strategie)
- classe attaque : types d’attaque: degat, portee, vitesse, position de l’attaque, position de la cible

# Implementation

Actuellement les tours tire sur des tiles non vides, pour ce faire quand on ajoute un batiment a une map, on enregistre la distance a chaque path dans le batiment.
<br>
Ainsi le batiment peut choisir un tile dans son range

## TODO
