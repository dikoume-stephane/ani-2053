# Exercice 7 : Fusion Automatique de Modifications Éloignées 

## 1. Contexte et Déroulement des Commandes

L'objectif de cet exercice est de démontrer le comportement de Git lorsque deux personnes  modifient simultanément le même fichier, mais à des endroits suffisamment éloignés pour que Git réalise une fusion automatique sans déclencher de conflit manuel.

---

### 1 : Modification en haut du fichier depuis un clone (chez un camarade "daniel")
Sur cette copie du dépôt, une modification est apportée sur une premiere partie du fichier `fichier2.md`. La modification est indexée, validée par un commit, puis envoyée sur le dépôt distant.

* on peu voir la modification en question avec la commande `git diff`

```powershell
git diff
diff --git a/fichier2.md b/fichier2.md
index 4c57663..57bbe47 100644
--- a/fichier2.md
+++ b/fichier2.md
@@ -10,7 +10,7 @@ L'architecture du système repose sur un modèle en **couches strictes et indép
 
 +-----------------------------------------------------------+|        Interface Applicative (API)                 |+-----------------------------------------------------------+| (Appels / Événements)+-----------------------------------------------------------+|   Moteur d'Exécution (Kernel)                  |+-----------------------------------------------------------+/              / (Ordonnancement)                            \ (I/O Asynchrones)+---------------------------+       +-----------------------+|  Sous-système de Stockage |       |     Couche Réseau     |+---------------------------+       +-----------------------+
 
-### 2.1. Couche Réseau (Network Layer)
+### 2.1. Couche Réseau 
 Cette couche est responsable de la communication avec le monde extéri
eur. Elle abstrait la complexité des protocoles de transport et maximi
se le débit de données.
 
 * **Gestion des connexions asynchrones :** Utilisation d'un modèle d'
I/O non bloquant basé sur des multiplexeurs natifs (comme `epoll` sous
 Linux, `kqueue` sous macOS ou `IOCP` sous Windows). Cela permet de gé
rer des dizaines de milliers de connexions simultanées avec un nombre 
minimal de threads système.
```
* ajout et validation du commit. puis envoi:

```powershell
git add .
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git commit -m "fix(correction): correction du fichier fichier2.md sur la section reseau"
[master 56e33bb] fix(correction): correction du fichier fichier2.md sur la section reseau
 1 file changed, 1 insertion(+), 1 deletion(-)
 git push
Enumerating objects: 6, done.
Counting objects: 100% (6/6), done.
Delta compression using up to 4 threads
Compressing objects: 100% (4/4), done.
Writing objects: 100% (4/4), 541 bytes | 180.00 KiB/s, done.
Total 4 (delta 2), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (2/2), completed with 2 local objects.
To https://github.com/dikoume-stephane/ani-test.git
   774b58e..a0c537d  master -> master
```
## 2 : Modification en bas du fichier depuis le deuxième clone & Refus du Push
Sans effectuer de git pull préalable, une seconde modification est apportée dans l'autre clone de mon coté, cette fois-ci sur une ligne en bas du fichier mesure.md.

Au moment de pousser vers le serveur distant, la commande git push est refusée car le dépôt distant contient le commit non présent localement.

* on peu voir la modification en question avec la commande `git diff`
```powershell
git diff          
warning: in the working copy of 'fichier2.md', LF will be replaced byCRLF the next time Git touches it
diff --git a/fichier2.md b/fichier2.md
index 4c57663..bbcbb50 100644
--- a/fichier2.md
+++ b/fichier2.md
@@ -83,5 +83,5 @@ Le projet s'étale sur un cycle intensif de 4 mois (16 semaines) réparti en 8 s
 
 ## 8. Conventions et Directives Git
 - Chaque modification doit faire l'objet d'un commit atomique (un seul sujet par commit).
-- Les messages de commit doivent respecter le format *Conventional Commits* (`feat:`, `fix:`, `perfe:`, `docs:`).
+- Les messages de commit doivent respecter le format *Conventional Commits* (`feat:`, `fix:`, `perf:`, `docs:`).
 - Aucun push direct sur la branche `main` n'est autorisé ; passage ob
ligatoire par une Pull Request avec relecture.
```
* ajout et validation du commit. puis envoi:
```powershell
git add .                                                                     
warning: in the working copy of 'fichier2.md', LF will be replaced byCRLF the next time Git touches it
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\exo-git> git commit -m "fix(correction): correction du fichier fichier2.md sur la section conventios git"
[master 94d5e5f] fix(correction): correction du fichier fichier2.md sur la section conventios git
 1 file changed, 1 insertion(+), 1 deletion(-)
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\exo-git> git push

To https://github.com/dikoume-stephane/ani-test.git
 ! [rejected]        master -> master (fetch first)
error: failed to push some refs to 'https://github.com/dikoume-stephane/ani-test.git'
hint: Updates were rejected because the remote contains work that youdo not
hint: have locally. This is usually caused by another repository pushing to
hint: the same ref. If you want to integrate the remote changes, use
hint: 'git pull' before pushing again.
hint: See the 'Note about fast-forwards' in 'git push --help' for details.
```
## 3 : Rapatriement avec git pull, Fusion Automatique et Publication
Pour intégrer la version distante, la commande `git pull` est exécutée. Contrairement à l'exercice 6, aucune intervention manuelle n'est requise : Git détecte que les lignes modifiées sont physiquement distantes, réussit l'auto-fusion .

La mise à jour est ensuite finalisée avec un git push.
```powershell
git pull

remote: Enumerating objects: 6, done.
remote: Counting objects: 100% (6/6), done.
remote: Compressing objects: 100% (2/2), done.
remote: Total 4 (delta 2), reused 4 (delta 2), pack-reused 0 (from 0)
Unpacking objects: 100% (4/4), 521 bytes | 12.00 KiB/s, done.
From https://github.com/dikoume-stephane/ani-test
   774b58e..a0c537d  master     -> origin/master
Auto-merging fichier2.md
Merge made by the 'ort' strategy.
 fichier2.md | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\exo-git> git push

Enumerating objects: 10, done.
Counting objects: 100% (10/10), done.
Delta compression using up to 4 threads
Compressing objects: 100% (6/6), done.
Writing objects: 100% (6/6), 655 bytes | 3.00 KiB/s, done.
Total 6 (delta 4), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (4/4), completed with 2 local objects.
To https://github.com/dikoume-stephane/ani-test.git
   a0c537d..639a99f  master -> master
```
## Analyse 
Pourquoi Git n'a-t-il pas déclenché de conflit cette fois-ci ?
**Distance entre les lignes**: Dans l'exercice 6, les deux modifications portaient exactement sur la même ligne. Dans cet exercice, les modifications touchent deux régions distinctes du fichier .

**Analyse contextuelle** : Le moteur de fusion de Git analyse les blocs de lignes modifiés (hunks). Si les blocs sont séparés par des lignes inchangées, Git est capable de combiner automatiquement les deux ensembles de modifications sans équivoque.