# Exercice 11 : Impact de la Suppression d'un Gros Fichier sur la Taille de `.git`

## 1. Contexte

L'objectif de cet exercice est d'observer le comportement interne de Git lorsqu'un gros fichier binaire (10 Mo) est ajouté puis supprimé dans deux commits successifs, et de mesurer son impact sur la taille du dossier caché `.git`.

---

### Étape 1 : Mesure initiale du dossier `.git`
Avant toute modification, la taille du dossier `.git` est mesurée via PowerShell.

```powershell
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> (Get-ChildItem .git -Recurse | Measure-Object -Property Length -Sum).Sum / 1MB
0,0805511474609375

```

*Taille initiale :* **~0,08 Mo**

---

### Étape 2 : Création, indexation et commit du fichier de 10 Mo

Un fichier binaire de 10 Mo (`gros_fichier.bin`) est généré avec `fsutil`, indexé via `git add`, puis validé sous le commit `b272367`.

```powershell
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> fsutil file createnew gros_fichier.bin 10485760
Le fichier D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test\gros_fichier.bin est créé

PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git add gros_fichier.bin
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git commit -m "ajout d'un gros fichier binaire de 10Mo"       
[master b272367] ajout d'un gros fichier binaire de 10Mo
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 gros_fichier.bin

```

---

### Étape 3 : Suppression du fichier au commit suivant

Le fichier est supprimé du répertoire de travail avec `Remove-Item`, puis la suppression est enregistrée dans l'historique sous le commit `c4e7b15`.

```powershell
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> Remove-Item gros_fichier.bin
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git add .
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> git commit -m "suppression du gros fichier binaire"       
[master c4e7b15] suppression du gros fichier binaire
 1 file changed, 0 insertions(+), 0 deletions(-)
 delete mode 100644 gros_fichier.bin

```

---

### Étape 4 : Nouvelle mesure de la taille du dossier `.git`

Une seconde mesure est effectuée pour évaluer l'impact du fichier supprimé sur le stockage interne de Git.

```powershell
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\ani-test> (Get-ChildItem .git -Recurse | Measure-Object -Property Length -Sum).Sum / 1MB
0,125423431396484

```

*Taille finale :* **~0,125 Mo**

---

## 2. Analyse et Conclusion

---

### 1. Pourquoi le fichier de 10 Mo ne fait-il que 0,12 Mo dans `.git` ?

* **Compression automatique:** Le fichier créé par la commande `fsutil file createnew` est un binaire, donc il contient exclusivement des octets nuls. Git compresse automatiquement tous les objets stockés dans à l'aide de l'algorithme. Une suite de 10 Mo de zéro est extrêmement compressible, ce qui réduit sa taille sur le disque à quelques kilo-octets seulement.
* **la taille :** Malgré cette compression, la taille du dossier `.git` est passée de **0,080 Mo** à **0,125 Mo**, montrant clairement une augmentation de volume conservée après la suppression.

---

### 2. Pourquoi Git conserve-t-il le fichier supprimé ?

* **la base d'objets :** Lorsqu'un fichier est validé par un `git commit`, Git crée un objet  definitif dans sa base de données interne.
* **Gestion du temps et de l'historique :** La commande `git rm` ou la suppression du fichier ne retire le fichier que du commit courant. L'objet binaire reste stocké dans le commit précédent (`b272367`) afin de permettre à n'importe quel développeur de remonter dans le temps et de retrouver le projet exactement comme il était à cet instant-là.

---

### 3. Conclusion générale

1. **Un fichier supprimé dans le répertoire de travail n'est PAS supprimé de la base de données Git.** Il reste stocké indéfiniment dans l'historique du dossier `.git`.
2. **Impact sur les dépôts réels :** Si le fichier binaire avait été une image, une vidéo ou un exécutable non compressible (ex: un `.zip` ou un `.exe` de 10 Mo), le dossier `.git` aurait grossi d'au moins 10 Mo et ne se serait pas dégonflé après le commit de suppression.
