# Exercice 10 : Comparaison des d'Intégration – Fusion (`merge`) vs Rebasage (`rebase`)

## 1. Contexte 

L'objectif de cet exercice est de comparer l'impact visuel et structurel de deux méthodes d'intégration d'une branche de fonctionnalité (`feature-test`) dans la branche principale (`master`) :
1. **L'intégration par Fusion (`git merge`) :** Génère un commit de raccordement et conserve les bifurcations d'origine.
2. **L'intégration par Rebasage (`git rebase`) :** Réécrit l'historique de la branche de fonctionnalité au-dessus de la cible(*master*), permettant une intégration en ligne droite .

---

### Étape 1 : Création de la branche et commits 
Une branche `feature-test` est créée et reçoit un commit de modification. En parallèle, la branche `master` avance séparément avec un autre commit sur un autre fichier.
```powershell
 git checkout -b feature-test
Switched to a new branch 'feature-test'
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git add .
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git commit -m "feat: ajout sur la branche feature-test"
[feature-test edc3eca] feat: ajout sur la branche feature-test
 1 file changed, 1 insertion(+)
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git checkout master                                    
Switched to branch 'master'
Your branch is ahead of 'origin/master' by 2 commits.
  (use "git push" to publish your local commits)
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git checkout master      
Switched to branch 'master'
Your branch is ahead of 'origin/master' by 2 commits.
  (use "git push" to publish your local commits)
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git add .          
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git commit -m "feat: ajout des modifications sur la branche master"
[master 0e4422a] feat: ajout des modifications sur la branche master
 1 file changed, 2 insertions(+), 1 deletion(-)
```


---

### Étape 2 : Intégration par Fusion (`git merge`)
L'exécution de `git merge feature-test` depuis `master` génère le commit de fusion `1d0c03b`. L'inspection via `git log --graph` montre clairement la création d'une branche parallèle qui se raccorde à `master`.

```powershell
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git merge feature-test -m "merge: fusion de feature-test dans master"
Merge made by the 'ort' strategy.
 fichier3.bat | 1 +
 1 file changed, 1 insertion(+)

PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git log --graph --oneline -n 6
*   1d0c03b (HEAD -> master) merge: fusion de feature-test dans master
|\  
| * edc3eca (feature-test) feat: ajout sur la branche feature-test
* | 0e4422a feat: ajout des modifications sur la branche master
|/  
* 397e28c fix: ajout d'une section economie
* 2a2d6df Revert "fix: duppression de la section de presentation du projet dans le fichier fichier2.md"
* 08a92ab (origin/master, origin/HEAD) fix: duppression de la sectionde presentation du projet dans le fichier fichier2.md
```

---

### Étape 3 : Annulation de la fusion et Intégration par Rebasage (`git rebase`)

La fusion est annulée par `git reset --hard HEAD~1` pour replacer `master` sur le commit `0e4422a`.

La branche `feature-test` est ensuite rebasée sur `master` (`git rebase master`). Enfin, le retour sur `master` suivi de `git merge feature-test` effectue un simple alignement .

```powershell
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git reset --hard HEAD~1
HEAD is now at 0e4422a feat: ajout des modifications sur la branche master

PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git checkout feature-test
Switched to branch 'feature-test'

PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git rebase master
Successfully rebased and updated refs/heads/feature-test.

PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git checkout master
Switched to branch 'master'

PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git merge feature-test
Updating 0e4422a..221485d
Fast-forward
 fichier3.bat | 1 +
 1 file changed, 1 insertion(+)

PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git log --graph --oneline -n 8
* 221485d (HEAD -> master, feature-test) feat: ajout sur la branche feature-test
* 0e4422a feat: ajout des modifications sur la branche master
* 397e28c fix: ajout d'une section economie
* 2a2d6df Revert "fix: duppression de la section de presentation du projet dans le fichier fichier2.md"
* 08a92ab (origin/master, origin/HEAD) fix: duppression de la sectionde presentation du projet dans le fichier fichier2.md
*   639a99f Merge branch 'master' of [https://github.com/dikoume-stephane/ani-test](https://github.com/dikoume-stephane/ani-test)
|\  
| *   a0c537d Merge branch 'master' of [https://github.com/dikoume-stephane/ani-test](https://github.com/dikoume-stephane/ani-test)
| |\  

```

---

## 2. Comparaison des Deux Graphes

| Critère | Intégration par Fusion (`git merge`) | Intégration par Rebasage (`git rebase`) |
| --- | --- | --- |
| **Structure du graphe** | courbé |  présence de des lignes parallèles. |
| **Commits de raccordement** | Génère un commit de merge explicite (`1d0c03b`). | Aucun commit de merge créé . |
| **Hash du commit intégré** | Conserve le commit d'origine (`edc3eca`). | Réécrit le commit sous un nouvel identifiant (`221485d`). |
| **visuel** | encombrement visuel Élevé dès que plusieurs branches s'entrecroisent. | Minimal, lisibilité optimale de la chronologie. |

---

## 3. Préférence et Argumentation

### Préférence : **Intégration par Fusion (`git merge`)**

#### Argument principal : **Sécurité de l'historique et conservation de la chronologie**

* **Non-altération des commits (Sécurité) :** Contrairement au `rebase` qui réécrit l'historique en créant de nouveaux identifiants, le `merge` ne modifie jamais les commits existants. Il n'y a aucun risque de perdre du travail ou de déstabiliser le dépôt partagé des collaborateurs.
* **Fidélité de l'historique :** Le `merge` conserve la trace exacte de ce qui s'est réellement passé dans le temps. Cette traçabilité est essentielle dans un cadre de travail rigoureux.
* **Prévention des erreurs en équipe :** L'usage du `merge` évite les conflits complexes liés à la réécriture d'une branche déjà publiée, ce qui en fait la méthode la plus sûre et la plus naturelle pour le travail collaboratif.
