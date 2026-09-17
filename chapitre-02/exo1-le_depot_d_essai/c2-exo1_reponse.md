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

* apres verification avec la commande `git show HEAD~2` nous avont la sortie suivante .
```powershell
 git show HEAD~2
commit f2ba1c3a9f729e016abc66be1a11ed65ffcf3393
Author: dikoume-stephane <dikoumeds@gmail.com>
Date:   Wed Sep 16 12:54:12 2026 +0100

    feat: ajout du fichier 2

diff --git a/fichier2.md b/fichier2.md
new file mode 100644
index 0000000..872e7ac
Binary files /dev/null and b/fichier2.md differ
```
* La ligne `Binary files /dev/null and b/fichier2.md differ` apporte la preuve exacte du problème : Git refuse de traiter le fichier comme du texte brut et le gère comme un fichier binaire en raison de l'encodage UTF-16 LE généré par `echo >` sous PowerShell.
* **les solution :** utiliser `CMD` ou `bash` comme terminal. ou alors, utiliser une autre methode d'ecriture dans les fichiers (avec un editeur de code ou une autre commande.). j'ai choisi d'utiliser une autre commande .
* **les comandes utilisée sont :**`Set-Content -Path fichier1.txt -Value "Mon texte" -Encoding utf8` pour la creation des fichiers et `git commit -m "message"`pour faire un commit (le depot à été netoyé au prealable avec `Remove-Item -Recurse -Force .git` et `nRemove-Item fichier1.txt, fichier2.md, fichier3.bat` puis, reinitialisé avec `git init`pour plus de propretée dans l'historique).
```powershell
 PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\exo-git> Set-Content -Path fichier1.txt -Value "Fichier 1" -Encoding utf8
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\exo-git> git add fichier1.txt
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\exo-git> git commit -m "feat: ajout du fichier 1"
[master (root-commit) d16ea0f] feat: ajout du fichier 1
 1 file changed, 1 insertion(+)
 create mode 100644 fichier1.txt
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\exo-git> Set-Content -Path fichier2.md -Value "Fichier 2" -Encoding utf8
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\exo-git> git add fichier2.md
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\exo-git> git commit -m "feat: ajout du fichier 2"
[master 317cd70] feat: ajout du fichier 2
 1 file changed, 1 insertion(+)
 create mode 100644 fichier2.md
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\exo-git> Set-Content -Path fichier3.bat -Value "Fichier 3" -Encoding utf8
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\exo-git> git add fichier3.bat
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\exo-git> git commit -m "feat: ajout du fichier 3"
[master b338f00] feat: ajout du fichier 3
 1 file changed, 1 insertion(+)
 create mode 100644 fichier3.bat
```
## affichage de l'historique
* **afficher l'historique avec une seule ligne par commit** `git log --oneline`
```powershell
D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\exo-git> git log --oneline
b338f00 (HEAD -> master) feat: ajout du fichier 3
317cd70 feat: ajout du fichier 2
d16ea0f feat: ajout du fichier 1
```
* **affichage du graph de l'historique avec une ligne par commit** `git log --graph --oneline --all`
```powershell
D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\exo-git> git log --graph --oneline --all
* b338f00 (HEAD -> master) feat: ajout du fichier 3
* 317cd70 feat: ajout du fichier 2
* d16ea0f feat: ajout du fichier 1
```
* pour la deuxieme commande, le graph n'est pas vraiment visible car il n'y a que trois commit tous fait sur la meme branche . avec des branches diferente(marquage de couleur pour chaque branche) et un nombre concequant de commit, on optiendrais un graph plus marqué.