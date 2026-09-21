
# Exercice 8 : Gestion et Annulation des Erreurs Courantes dans Git

## 1. Contexte 

L'objectif de cet exercice est de simuler six situations d'erreur fréquentes dans l'utilisation quotidienne de Git et d'appliquer la commande de corection appropriée pour chaque cas.

---

### Situation 1 : Annulation d'une modification non voulue
Une modification locale non désirée est apportée au fichier `fichier2.md`. La commande `git diff` permet de constater l'erreur, puis `git restore` annule le changement dans le répertoire de travail.

```powershell
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git diff
diff --git a/fichier2.md b/fichier2.md
index 57bbe47..ab7e9e2 100644
--- a/fichier2.md
+++ b/fichier2.md
@@ -1,7 +1,7 @@
 # Documentation du Système - Projet mbog
 
 ## 1. Présentation Générale
-Le projet **mbog** repose sur une architecture C++20 hautement modulaire, multi-threadée et axée sur les performances temps réel.
+Le projet **kaffka** repose sur une architecture C++20 hautement modulaire, multi-threadée et axée sur les performances temps réel.
 Ce document constitue la référence technique principale pour léquipe de développement et les collaborateurs externes.
 
 ## 2. Architecture Logicielle

PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git restore fichier2.md
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git diff               

```
on voit bien q'apret l'application de la commande `git restore fichier2.md`, le `git diff`suivant ne retourne rien . c'est la la preuve que tout est revenu à l'ordre

---

### Situation 2 : Retrait d'un fichier indexé par erreur (`git add` de trop)

Le fichier `fichier2.md` est modifié puis ajouté à la zone d'index via `git add .`. La commande `git restore --staged` le retire de l'index sans supprimer les modifications du fichier, ce qui est confirmé par l'apparition du diff en zone de travail .

```powershell
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git add .
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git diff 
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git restore --staged fichier2.md
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git diff                
diff --git a/fichier2.md b/fichier2.md
index 57bbe47..380e8d3 100644
--- a/fichier2.md
+++ b/fichier2.md
@@ -1,4 +1,4 @@
-# Documentation du Système - Projet mbog
+# Documentation du Système - Projet kaffka
 
 ## 1. Présentation Générale
 Le projet **mbog** repose sur une architecture C++20 hautement modulaire, multi-threadée et axée sur les performances temps réel.

```
le premier `git diff` n'affiche rien car les modifications ont deja étés indexés . puis, le `git restore --staged fichier2.md` desindex les modification et c'est pourquoi le secon diff les affiche.

---

### Situation 3 : Annulation d'un commit local en trop (`git reset`)

Un commit local est créé. Deux stratégies d'annulation locale sont démontrées :

1. **`git reset --soft HEAD~1` :** Annule le commit tout en conservant les modifications indexées (visibles dans `git status`).
2. **`git reset --hard HEAD~1` :** Annule le commit et nettoie intégralement le répertoire de travail.

```powershell
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git add .
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git commit -m "fix: duppression de la section de presentation du projet dans le fichier fichier2.md"
[master af35ec6] fix: duppression de la section de presentation du projet dans le fichier fichier2.md
 1 file changed, 1 insertion(+), 2 deletions(-)

PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git reset --soft HEAD~1
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git status             
On branch master
Your branch is up to date with 'origin/master'.

Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        modified:   fichier2.md

PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git commit -m "fix: duppression de la section de presentation du projet dans le fichier fichier2.md"
[master 38cfd45] fix: duppression de la section de presentation du projet dans le fichier fichier2.md
 1 file changed, 1 insertion(+), 2 deletions(-)

PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git reset --hard HEAD~1
HEAD is now at a0c537d Merge branch 'master' of [https://github.com/dikoume-stephane/ani-test](https://github.com/dikoume-stephane/ani-test)
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git status             
On branch master
Your branch is up to date with 'origin/master'.

nothing to commit, working tree clean

```

---

### Situation 4 : Annulation d'un commit déjà poussé sur le dépôt distant (`git revert`)

Après synchronisation (`git pull`) et publication d'un nouveau commit via `git push`, l'annulation est effectuée à l'aide de `git revert`. Un commit inverse est créé, préservant l'historique public.

```powershell
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git add .
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git commit -m "fix: duppression de la section de presentation du projet dans le fichier fichier2.md"
[master 08a92ab] fix: duppression de la section de presentation du projet dans le fichier fichier2.md
 1 file changed, 1 insertion(+), 2 deletions(-)

PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git push
To [https://github.com/dikoume-stephane/ani-test.git](https://github.com/dikoume-stephane/ani-test.git)
   639a99f..08a92ab  master -> master

PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git log -n 1
commit 08a92abad26a458f16993244779e839f16b5789e (HEAD -> master, origin/master, origin/HEAD)
Author: dikoume-stephane <dikoumeds@gmail.com>
Date:   Mon Sep 21 07:58:37 2026 +0100

    fix: duppression de la section de presentation du projet dans le fichier fichier2.md

PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git revert 08a92abad26a458f16993244779e839f16b5789e
[master 2a2d6df] Revert "fix: duppression de la section de presentation du projet dans le fichier fichier2.md"
 1 file changed, 2 insertions(+), 1 deletion(-)

PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git log -n 2                                        
commit 2a2d6df2eb95e9941ab9f3eb85af690a94abacb2 (HEAD -> master)
Author: dikoume-stephane <dikoumeds@gmail.com>
Date:   Mon Sep 21 07:59:56 2026 +0100

    Revert "fix: duppression de la section de presentation du projet dans le fichier fichier2.md"
    
    This reverts commit 08a92abad26a458f16993244779e839f16b5789e.

commit 08a92abad26a458f16993244779e839f16b5789e (origin/master, origin/HEAD)
Author: dikoume-stephane <dikoumeds@gmail.com>
Date:   Mon Sep 21 07:58:37 2026 +0100

    fix: duppression de la section de presentation du projet dans le fichier fichier2.md

```

---

### Situation 5 : Mise de côté d'un travail en cours (`git stash`)

Des modifications non terminées (ajout de la section `## economie`) sont temporairement remisées en mémoire grâce à `git stash`, rétablissant un répertoire de travail propre. Elles sont ensuite réappliquées à l'aide de `git stash pop`.

```powershell
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git diff    
diff --git a/fichier2.md b/fichier2.md
index 40c656f..c7a4b6b 100644
--- a/fichier2.md
+++ b/fichier2.md
@@ -85,3 +85,6 @@ Le projet s'étale sur un cycle intensif de 4 mois (16 semaines) réparti en 8 s
 - Chaque modification doit faire l'objet d'un commit atomique (un seul sujet par commit).
 - Les messages de commit doivent respecter le format *Conventional Commits* (`feat:`, `fix:`, `perf:`, `docs:`).
 - Aucun push direct sur la branche `main` n'est autorisé ; passage obligatoire par une Pull Request avec relecture.
+
+## economie
+

PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git stash
Saved working directory and index state WIP on master: 2a2d6df Revert"fix: duppression de la section de presentation du projet dans le fichier fichier2.md"

PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git diff 

PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git stash pop
On branch master
Your branch is ahead of 'origin/master' by 1 commit.
  (use "git push" to publish your local commits)

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   fichier2.md

no changes added to commit (use "git add" and/or "git commit -a")
Dropped refs/stash@{0} (6528c5da1d29e17e4a82383f47f7514933179538)

PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git diff     
diff --git a/fichier2.md b/fichier2.md
index 40c656f..c7a4b6b 100644
--- a/fichier2.md
+++ b/fichier2.md
@@ -85,3 +85,6 @@ Le projet s'étale sur un cycle intensif de 4 mois (16 semaines) réparti en 8 s
 - Chaque modification doit faire l'objet d'un commit atomique (un seul sujet par commit).
 - Les messages de commit doivent respecter le format *Conventional Commits* (`feat:`, `fix:`, `perf:`, `docs:`).
 - Aucun push direct sur la branche `main` n'est autorisé ; passage obligatoire par une Pull Request avec relecture.
+
+## economie
+

```

---

### Situation 6 : Récupération d'un commit perdu via le `git reflog`

Le commit ("fix: ajout d'une section economie") est supprimé accidentellement de branche par un `git reset --hard HEAD~1`. Le journal d'actions `git reflog` permet d'identifier son identifiant et de restaurer le pointeur de la branche sur ce commit.

```powershell
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git add .
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git commit -m "fix: ajout d'une section economie"                            
[master 397e28c] fix: ajout d'une section economie
 1 file changed, 3 insertions(+)

PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git reset --hard HEAD~1
HEAD is now at 2a2d6df Revert "fix: duppression de la section de presentation du projet dans le fichier fichier2.md"

PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git reflog
2a2d6df (HEAD -> master) HEAD@{0}: reset: moving to HEAD~1
397e28c HEAD@{1}: commit: fix: ajout d'une section economie
2a2d6df (HEAD -> master) HEAD@{2}: reset: moving to HEAD
2a2d6df (HEAD -> master) HEAD@{3}: revert: Revert "fix: duppression de la section de presentation du projet dans le fichier fichier2.md"
08a92ab (origin/master, origin/HEAD) HEAD@{4}: commit: fix: duppression de la section de presentation du projet dans le fichier fichier2.md
639a99f HEAD@{5}: pull: Fast-forward
a0c537d HEAD@{6}: reset: moving to HEAD~1
38cfd45 HEAD@{7}: commit: fix: duppression de la section de presentation du projet dans le fichier fichier2.md
a0c537d HEAD@{8}: reset: moving to HEAD~1
af35ec6 HEAD@{9}: commit: fix: duppression de la section de presentation du projet dans le fichier fichier2.md
a0c537d HEAD@{10}: pull: Merge made by the 'ort' strategy.
56e33bb HEAD@{11}: commit: fix(correction): correction du fichier fichier2.md sur la section reseau

PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git reset --hard 397e28c
HEAD is now at 397e28c fix: ajout d'une section economie

```

---

## 2. Synthèse 

---

### 1. `git restore` et `git restore --staged`

* **`git restore <fichier>` :** Agit sur le répertoire de travail . Annule les modifications non indexées en recopiant la version présente dans l'index.
* **`git restore --staged <fichier>` :** Agit sur la zone d'index . Retire le fichier de l'index sans altérer le contenu physique du fichier dans le répertoire de travail.

---

### 2. `git reset --soft` et `git reset --hard`

* **`git reset --soft HEAD~1` :** ramene la branche vers le commit parent tout en conservant l'état des fichiers modifiés dans l'index.
* **`git reset --hard HEAD~1` :** ramene la branche ET réinitialise complètement l'index et le répertoire de travail, détruisant toutes les modifications non commitées.

---

### 3. `git revert` pour les commits publiés

*  `git revert` applique le diff inverse du commit ciblé et génère un nouveau commit de correction, préservant l'intégrité de la chaîne chronologique de Git.

---

### 4. Rôle du `git reflog`

* **Fonctionnement :** `git reflog` tient un journal local de tous les déplacements du pointeur de la branche (commits, resets, merges, checkouts).
* **Récupération :** Même lorsqu'un commit devient orphelin suite à un `reset --hard`, il reste stocké en mémoire dans la base d'objets de Git. Le `reflog` permet d'obtenir son identifiant (`397e28c`) pour le réassocier immédiatement à la branche active.
