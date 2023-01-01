Projet c : CookiePlayTime
BOUHRARA Adam	CASSIET Clement   CERF Fabien   GAUTIER Jordan	 LEGRAND Joan

Informations générales :

Ce programme permet d'éxécuter un jeu dans lequel on controle un personnage qui se déplace sur une carte en 2D et qui cherche à rejoindre son point d'arrivée.	
Sur son chemin, le personnage pourra recontrer des obstacles qui lui font perdre de l'énergie et des bonus qui lui en font gagner. 
Si le joueur n'a plus d'énergie, la partie est perdue.
Le personnage peut se déplacer de haut en bas, avec les touches z/x, de droite à gauche, avec q/d, mais aussi en diagonale avec a/e/w/c.
Le joueur a également la possibilitée de faire jusqu'à 6 retours en arrières pour annuler le dernier mouvement.
Il est possible reprendre une partie en cours après avoir quitté le jeu, si cette dernière a été sauvegardée. Il est également possible de revoir une ancienne partie.

Démarrage :
Afin d'éxecuter le programme, il faut aller sur un invite de commandes, puis faire le chemin jusqu'au dossier contenant tous les fichiers fournis.
Ensuite, il faut compiler le programme en utilisant la commande : make
Après cela pour lancer une partie, il faut utiliser la commande : make run
Il existe également d'autres commandes pour : 
-vider les dossier obj et bin : make clean
-supprimer les dossier obj et bin : make hardClean
-afficher les parties sauvegardées : make save
-vider le fichier des sauvegardes : make cleanSaves
-supprimer les dossier obj et bin, compiler le programme et lancer une partie : make super

Il existe également une option make help : permet d'afficher les instructions permettant l'execution du programme.