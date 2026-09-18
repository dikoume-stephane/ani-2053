# Exercice 4 : Isolation de modifications non liées dans un même fichier avec `git add -p`

## Étape 1 : Sélection interactive du premier bloc de modification (Hunk 1/2)

* **Commande exécutée :** `git add -p`
* **Sortie du terminal**
```powershell
warning: in the working copy of 'fichier2.md', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of 'fichier2.md', LF will be replaced by CRLF the next time Git touches it
diff --git a/fichier2.md b/fichier2.md
index ee86d69..4c57663 100644
--- a/fichier2.md
+++ b/fichier2.md
@@ -1,7 +1,7 @@
-# Documentation du Système - Projet Kafka
+# Documentation du Système - Projet mbog
 
 ## 1. Présentation Générale
-Le projet **Kafka** repose sur une architecture C++20 hautement modulaire, multi-threadée et axée sur les performances temps réel.
+Le projet **mbog** repose sur architecture C++20 hautement modulaire, multi-threadée et axée sur les performances temps réel.
 Ce document constitue la référence technique principale pour l'équipe de développement et les collaborateurs externes.
 
 ## 2. Architecture Logicielle
(1/2) Stage this hunk [y,n,q,a,d,j,J,g,/,s,e,p,?]? y
@@ -83,5 +83,5 @@ Le projet s'étale sur un cycle intensif de 4 mois (16 semaines) réparti en 8 s
 
 ## 8. Conventions et Directives Git
 - Chaque modification doit faire l'objet d'un commit atomique (un seul sujet par commit).
-- Les messages de commit doivent respecter le format *Conventional Commits* (`feat:`, `fix:`, `perf:`, `docs:`).
+- Les messages de commit doivent respecter le format *Conventional Commits* (`feat:`, `fix:`, `perfe:`, `docs:`).
 - Aucun push direct sur la branche `main` n'est autorisé ; passage obligatoire par une Pull Request avec relecture.
(2/2) Stage this hunk [y,n,q,a,d,K,g,/,e,p,?]? n
```

* **Explication**
La commande `git add -p` analyse le fichier `fichier2.md` et isole deux modifications distinctes (*hunks*). La première modification concerne le changement de nom du projet (`Kafka` en `mbog`). En répondant `y` (yes) au premier bloc `(1/2)`, seule cette première modification est placée dans l'index (Staging Area). En répondant `n` (no) au second bloc `(2/2)`, la modification sur les formats de commit reste dans le répertoire de travail.

---

## Étape 2 : Création du premier commit atomique

* **Commande exécutée :**`git commit -m "meodification du nom du projet dans le fichier md"`

* **Sortie du terminal**
```powershell
[master 6592978] meodification du nom du projet dans le fichier md
 1 file changed, 2 insertions(+), 2 deletions(-)
```

* **Explication**
Ce commit isole uniquement le changement de sujet principal (le nom du projet). Bien que le fichier contienne une autre modification non enregistrée, le commit réalisé est rigoureusement atomique et ne contient que la première partie validée lors de l'étape 1.

---

## Étape 3 : Sélection interactive de la seconde modification ( 2/2)

* **Commande exécutée :**`git add -p`
* **Sortie du terminal**
```powershell
warning: in the working copy of 'fichier2.md', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of 'fichier2.md', LF will be replaced by CRLF the next time Git touches it
diff --git a/fichier2.md b/fichier2.md
index bbcbb50..4c57663 100644
--- a/fichier2.md
+++ b/fichier2.md
@@ -83,5 +83,5 @@ Le projet s'étale sur un cycle intensif de 4 mois (16 semaines) réparti en 8 s
 
 ## 8. Conventions et Directives Git
 - Chaque modification doit faire l'objet d'un commit atomique (un seul sujet par commit).
-- Les messages de commit doivent respecter le format *Conventional Commits* (`feat:`, `fix:`, `perf:`, `docs:`).
+- Les messages de commit doivent respecter le format *Conventional Commits* (`feat:`, `fix:`, `perfe:`, `docs:`).
 - Aucun push direct sur la branche `main` n'est autorisé ; passage obligatoire par une Pull Request avec relecture.
(1/1) Stage this hunk [y,n,q,a,d,e,p,?]? y
```

* **Explication**
En relançant `git add -p`, Git ne présente plus que la modification restante dans le fichier `fichier2.md` (la modification du mot `perf:` en `perfe:` dans la section conventions). En répondant `y`, ce second bloc est à son tour indexé.

---

## Étape 4 : Création du second commit atomique

* **Commande exécutée :**`git commit -m "meodification des formats de commit dans le fichier md"`

* **Sortie du terminal**
```powershell
[master de83a5b] meodification des formats de commit dans le fichier md
 1 file changed, 1 insertion(+), 1 deletion(-)
```

* **Explication**
Le deuxième commit est créé séparément du premier. Il traite uniquement du second sujet (la modification dans la liste des formats de commit conventionnels).

---

## Étape 5 : Vérification de l'historique des commits

* **Commande exécutée :**`git log --oneline -n 2`

* **Sortie du terminal**
```powershell
de83a5b (HEAD -> master) meodification des formats de commit dans le fichier md
6592978 meodification du nom du projet dans le fichier md
```

* **Explication**
L'inspection des deux derniers commits de l'historique confirme la réussite de l'exercice : un seul fichier modifié à deux endroits différents a généré deux commits distincts et ciblés.

---

## Remarque importante : Contrainte sur la distance des modifications pour `git add -p`

Pour que l'option `-p` (`--patch`) de Git puisse découper automatiquement un fichier en plusieurs blocs, **les lignes modifiées doivent être suffisamment éloignées les unes des autres** .

Si deux modifications sont apportées sur des lignes trop rapprochées, l'algorithme de diff de Git regroupe les changements au sein d'un bloc unique `(1/1)`. Dans ce cas précis, l'option `s` (split) ou l'option `e` (edit) du mode interactif devient nécessaire pour découper manuellement le bloc au niveau des lignes de texte.
