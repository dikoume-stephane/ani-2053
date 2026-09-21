# Démonstration 3 : Destruction Volontaire (`reset --hard`) et Récupération d'Urgence via `git reflog`

## 1. Déroulement de la Démonstration

L'objectif de cette démonstration est de simuler une fausse manipulation destructrice (`git reset --hard`), de constater la perte du travail, puis d'appliquer la procédure de récupération via le journal de bord local de Git (`git reflog`).

---

### Étape 1 : Création du travail et validation
Un nouveau travail est enregistré dans l'historique via le commit `7e68b75`.

```powershell
git diff
diff --git a/fichier1.txt b/fichier1.txt
index b81650f..bb9715d 100644
--- a/fichier1.txt
+++ b/fichier1.txt
@@ -3,3 +3,5 @@ Ligne 2
 Ligne 3
 Ligne 4
 === PIED DE PAGE ===
+
+travail en cour....
\ No newline at end of file
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git add .
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git commit -m "travail en cour sur le fichier fichier1.txt"
[master 7e68b75] travail en cour sur le fichier fichier1.txt
 1 file changed, 2 insertions(+)
```

---

### Étape 2 : Destruction volontaire et constat de la perte

La commande `git reset --hard HEAD~1` est exécutée pour annuler le dernier commit et effacer les modifications du répertoire de travail.

```powershell
git reset --hard HEAD~1
HEAD is now at a31798a modification pour la demo 2
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git log -n 3
commit a31798a2ce989de52d9b5db6506ac12943fff2c3 (HEAD -> master, origin/master, origin/HEAD)
Author: dikoume-stephane <dikoumeds@gmail.com>
Date:   Mon Sep 21 22:10:06 2026 +0100

    modification pour la demo 2

commit c4e7b159e946926540a4142b1a050ad2e0e238aa
Author: dikoume-stephane <dikoumeds@gmail.com>
Date:   Mon Sep 21 18:52:46 2026 +0100

    suppression du gros fichier binaire

commit b272367dea40b7fc7b2030683b10e2a80be50ac8
Author: dikoume-stephane <dikoumeds@gmail.com>
Date:   Mon Sep 21 18:51:50 2026 +0100

    ajout d'un gros fichier binaire de 10Mo
```
Le commit `7e68b75` n'apparaît plus dans l'historique `git log` et le fichier dans le répertoire de travail a perdu ses modifications.

---

### Étape 3 : Inspection du journal de bord (`git reflog`)

Exécution de la commande `git reflog` pour consulter l'historique des mouvements.

```powershell
git reflog
a31798a (HEAD -> master, origin/master, origin/HEAD) HEAD@{0}: reset: moving to HEAD~1
7e68b75 HEAD@{1}: commit: travail en cour sur le fichier fichier1.txt
a31798a (HEAD -> master, origin/master, origin/HEAD) HEAD@{2}: commit: modification pour la demo 2
c4e7b15 HEAD@{3}: commit: suppression du gros fichier binaire
b272367 HEAD@{4}: commit: ajout d'un gros fichier binaire de 10Mo
221485d (feature-test) HEAD@{5}: merge feature-test: Fast-forward
0e4422a HEAD@{6}: checkout: moving from feature-test to master
221485d (feature-test) HEAD@{7}: rebase (finish): returning to refs/heads/feature-test
221485d (feature-test) HEAD@{8}: rebase (pick): feat: ajout sur la branche feature-test
```
L'entrée `HEAD@{1}` conserve l'identifiant exact (`7e68b75`) du commit effacé.

---

### Étape 4 : Restauration du commit « perdu »

Réinitialisation du pointeur de branche avec l'identifiant extrait du `reflog`.

```powershell
git reset --hard 7e68b75
HEAD is now at 7e68b75 travail en cour sur le fichier fichier1.txt
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git log -n 1
commit 7e68b7518f42b1dfb8c8490b332f4b487538a136 (HEAD -> master)
Author: dikoume-stephane <dikoumeds@gmail.com>
Date:   Mon Sep 21 22:44:13 2026 +0100

    travail en cour sur le fichier fichier1.txt
```
Le commit et les fichiers modifiés sont intégralement restaurés dans leur état d'origine.

---

## 2. Analyse Technique et Retours d'Expérience

1. **Rôle de la base d'objets Git :** La commande `git reset --hard` déplace le pointeur de la branche, mais elle ne supprime pas immédiatement l'objet commit de la base de données interne de Git.
2. **Le journal de `reflog` :** `git reflog` est un journal local qui enregistre chaque action modifiant le pointeur `HEAD`.
3. **Condition impérative :** Cette méthode de récupération ne fonctionne que pour du travail ayant fait l'objet d'au moins un `git commit` (ou un `git stash`). Des modifications non indexées et non commitées perdues suite à un `reset --hard` ne peuvent pas être retrouvées par le `reflog`.
