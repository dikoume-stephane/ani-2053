# Exercice 1 : Initialisation, Commits et Historique Git
## Création et initialisation du dossier local
* **creation du dossier du depot :** commande `mkdir exo-git`
```powershell
 mkdir exo-git


    Répertoire : D:\2DS\projet\programmation_cpp\niveau 2\sprint_1


Mode                 LastWriteTime         Length Name
----                 -------------         ------ ----
d-----        16/09/2026     12:51                exo-git


PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1> cd exo-git
```
* **initialisation du depot :** commande `git init`
```powershell
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\exo-git> git init
Initialized empty Git repository in D:/2DS/projet/programmation_cpp/niveau 2/sprint_1/exo-git/.git/
```
## creation des fichier et realisation des commits

* **les comandes utilisée sont :**`echo "contenu/message" > nom_du_fichier.extension` pour la creation des fichiers et `git commit -m "message"`pour faire un commit .
```powershell
 echo "Fichier 1" > fichier1.txt
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\exo-git> git add fichier1.txt
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\exo-git> git commit -m "feat: ajout du fichier 1"
[master (root-commit) 5265fec] feat: ajout du fichier 1
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 fichier1.txt
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\exo-git> echo "Fichier 2" > fichier2.md
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\exo-git> git add fichier2.md
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\exo-git> git commit -m "feat: ajout du fichier 2"
[master f2ba1c3] feat: ajout du fichier 2
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 fichier2.md
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\exo-git> echo "Fichier 3" > fichier3.bat
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\exo-git> git add fichier3.bat
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\exo-git> git commit -m "feat: ajout du fichier 3"
[master 4abb28d] feat: ajout du fichier 3
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 fichier3.bat
```
## affichage de l'historique
* **afficher l'historique avec une seule ligne par commit** `git log --oneline`
```powershell
D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\exo-git> git log --oneline
4abb28d (HEAD -> master) feat: ajout du fichier 3
f2ba1c3 feat: ajout du fichier 2
5265fec feat: ajout du fichier 1
```
* **affichage du graph de l'historique avec une ligne par commit** `git log --graph --oneline`
```powershell
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\exo-git> git log --graph --oneline --all
* 4abb28d (HEAD -> master) feat: ajout du fichier 3
* f2ba1c3 feat: ajout du fichier 2
* 5265fec feat: ajout du fichier 1
```
* pour la deuxieme commande, le graph n'est pas vraiment visible car il n'y a que trois commit tous fait sur la meme branche . avec des branches diferente(marquage de couleur pour chaque branche) et un nombre concequant de commit, on optiendrais un graph plus marqué.