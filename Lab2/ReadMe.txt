Automne 2020
Laboratoire 2 : 6GEI311-Architecture des logiciels
Jean-Philippe Lapointe, Antoine Boucher et Stéphane Tremblay
---------------------------------------------------------------------

Le laboratoire a été réalisé avec Visual Studio 2019 (à jour en date du 2020-09-22) en mode release pour architechture x64.
La solution peut être utilisée pour recompiler le module .pyd.
Une version compiler et fonctionnel du module trouve à l'emplacement Lab2\x64\Release\spam.pyd

fonctionnement du module:

le module comporte cinq méthodes:

1- run(path): lance la vidéo qui se trouve à l'endroit "path"
	codes d'erreurs:
	-1: les arguments ne sont pas valides
	-2: la vidéo n'a pas pu être joué
	-3: une vidéo est déjà entrain de jouer
2- play_pause: joue ou arrête la vidéo dépendement de son état
3- replay: relance la vidéo entrain de jouer
4- accelerate: accélère ou décélère la vidéo dépendement de son état
5- quit: ferme la vidéo entrain de jouer

Pour tester le module, le fichier .\Environement_debugage.ipynb peut être utilisé avec Jupyter Lab en suivant les étapes suivantes:

1- Cloner le repo GitHub
2- Lancer le fichier Environement_debugage.ipynb avec Jupyter Lab
3- modifier les chemins.
4- exécuter les cellules en ordre 

la vidéo joué est celle du nom de exemple.avi dans le dossier Lab1_2/Lab1_2