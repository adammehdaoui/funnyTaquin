# funnyTaquin (https://github.com/adammehdaoui/funnyTaquin), mini projet de jeu "Taquin"

## Documentation technique

La documentation technique du code est dans le **fichier Doxygen.html dans le répertoire doc à la racine du projet.**
<br>
Ce document est à ouvrir **avec un navigateur** car il est chargé à partir des fichiers de configuration Doxygen.

## Prérequis

**Avoir la librairie MLV installée.**
<br>
Tutoriel pour les O.S. linux : http://www-igm.univ-mlv.fr/~boussica/mlv/api/French/html/installation_linux.html

## Installation

Installer les packages nécessaires :
```sh 
sudo apt update && sudo apt install build-essential
```

Cloner le repo avec : 
```sh 
git clone https://github.com/adammehdaoui/funnyTaquin.git
```

## Utilisation et lancement du jeu

Pour lancer le taquin avec une image par défaut :

```sh
make run
```

Voici la commande pour lancer le jeu avec une image disponible (briques.png, hugo.jpg ou spirale.gif). Ici on lance le jeu avec l'image **briques.png** :

```sh
make
```
puis
```sh
./taquin briques.png
```

ou

```sh
make run ARG=briques.png
```

## Tutoriel en jeu

Cliquer sur une case proche de la case noire pour la déplacer.
À la fin du jeu, un message de félicitations s'affichera
et donnera le temps pris par l'utilisateur pour résoudre le taquin.
Bon courage!