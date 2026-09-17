# Exercice 2 : utilisation de la commande `git status`
## apres une modification
* **modification d'un fichier :** commande `echo "j'ajoute Une nouvelle ligne de texte" >> fichier1.txt` et `git status`apres.
```powershell
D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\exo-git> echo "j'ajoute Une nouvelle ligne de texte" >> fichier1.txt
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\exo-git> git status
On branch master
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   fichier1.txt

no changes added to commit (use "git add" and/or "git commit -a")
```
* **analyse de la sortie :**Le fichier fichier1.txt apparaît en rouge sous la section Changes not staged for commit (ou Modifications qui ne sont pas en zone de commit).La modification existe physiquement sur votre disque dur (dans le Wdossier de travail), mais Git ne l'a pas encore enregistrée dans la zone de préparation.et nous propose de l'ajouter en utilisant `git add <file>...` ou d'abandonner la modification avec `git restore <file>...` pour que le fichier retrouve son etat du dernier commit .

## apres `git add`
* **ajout des modifications du fichier :** commande `git add fichier1.txt` et `git status`apres.
```powershell
D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\exo-git> git add fichier1.txt
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\exo-git> git status
On branch master
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        modified:   fichier1.txt

```
* **analyse de la sortie :**Le fichier fichier1.txt passe en vert sous la section Changes to be committed (ou Modifications qui seront validées).Le fichier a été placé dans la zone de transit . Il est prêt à être figé dans l'historique lors du prochain commit.git nous propose d'utiliser la commande `git restore --staged <file>...` pour annuler l'ajout des modifications.

## apres un commit

* **commit de l'etat actuel :** commande `git commit -m "mise a jour de fichier1.txt"` et `git status`apres.
```powershell
D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\exo-git> git commit -m "mise a jour de fichier1.txt"
[master d4738eb] mise a jour de fichier1.txt
 1 file changed, 0 insertions(+), 0 deletions(-)
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\exo-git> git status
On branch master
nothing to commit, working tree clean
```
* **analyse de la sortie :**nothing to commit, working tree clean (ou rien à valider, la copie de travail est propre).

Analyse : La modification est officiellement enregistrée dans l'historique du dépôt (Repository).La zone de transit est vidée et le dossier de travail est synchronisé avec le dernier commit.