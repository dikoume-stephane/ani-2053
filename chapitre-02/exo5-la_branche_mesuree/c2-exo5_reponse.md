# Exercice 5 : Création de branche, commits et mesure de l'espace disque

## Étape 1 : Mesure de la taille initiale du dossier `.git`

* **Commande exécutée :**`(Get-ChildItem .git -Recurse | Measure-Object -Property Length -Sum).Sum / 1KB`

* **Sortie du terminal**
```text
47,6015625
```

* **Explication**
Avant d'effectuer la moindre modification, la taille totale du dossier `.git` est mesurée à **47,60 Ko**. Ce dossier contient l'intégralité de la base de données du dépôt (historique, objets, références).

---

## Étape 2 : Création et basculement sur une nouvelle branche

* **Commande exécutée :**`git switch -c feature/mesure-taille`

* **Sortie du terminal**
```powershell
Switched to a new branch 'feature/mesure-taille'
```

* **Explication**
La commande `git switch -c` crée la branche `feature/mesure-taille` et bascule directement dessus. Dans Git, créer une branche ne duplique aucun fichier du projet : cela crée simplement un fichier texte très léger (environ 41 octets) dans `.git/refs/heads/feature/mesure-taille` contenant le hash SHA-1 du commit courant.

---

## Étape 3 : Premier commit (Création du fichier `mesure.md`)

* **Commandes exécutées :**
```powershell
Set-Content -Path mesure.md -Value "# Fichier de mesure`nLigne 1" -Encoding utf8
git add mesure.md
git commit -m "feat: ajout initial du fichier de mesure"
```

* **Sortie du terminal**
```powershell
warning: in the working copy of 'mesure.md', LF will be replaced by CRLF the next time Git touches it
[feature/mesure-taille ca79033] feat: ajout initial du fichier de mesure
 1 file changed, 2 insertions(+)
 create mode 100644 mesure.md
```

* **Explication**
Création du fichier `mesure.md` avec deux lignes de texte, suivi de son indexation et de sa validation. Git génère ici ses trois premiers objets lâches (*loose objects*) pour cette branche : un **Blob** (contenu du fichier), un **Tree** (arborescence) et un **Commit** (métadonnées).

---

## Étape 4 : Deuxième commit (Ajout de la ligne 2)

* **Commandes exécutées :**
```powershell
Add-Content -Path mesure.md -Value "Ligne 2" -Encoding utf8
git add mesure.md
git commit -m "feat: ajout de la ligne 2"
```

* **Sortie du terminal**
```powershell
warning: in the working copy of 'mesure.md', LF will be replaced by CRLF the next time Git touches it
[feature/mesure-taille 38f6070] feat: ajout de la ligne 2
 1 file changed, 1 insertion(+)
```

* **Explication**
Une ligne supplémentaire est ajoutée au fichier.
---

## Étape 5 : Troisième commit (Ajout de la ligne 3)

* **Commandes exécutées :**
```powershell
Add-Content -Path mesure.md -Value "Ligne 3" -Encoding utf8
git add mesure.md
git commit -m "feat: ajout de la ligne 3"
```

* **Sortie du terminal**
```powershell
warning: in the working copy of 'mesure.md', LF will be replaced by CRLF the next time Git touches it
[feature/mesure-taille 255efd1] feat: ajout de la ligne 3
 1 file changed, 1 insertion(+)
```

* **Explication**
Troisième modification validée.

---

## Étape 6 : Mesure de la taille finale et analyse des résultats

* **Commande exécutée :**
```powershell
(Get-ChildItem .git -Recurse | Measure-Object -Property Length -Sum).Sum / 1KB
```

* **Sortie du terminal**
```text
50,1533203125
```

* **Explication et analyse de la variation d'espace**
- **Taille initiale :** `47,60 Ko`
- **Taille finale :** `50,15 Ko`
- **Évolution totale :** `+2,55 Ko`

#### Pourquoi cette augmentation ?
1. **Poids minime d'une branche :** La création de la branche n'ajoute qu'un pointeur de quelques octets.
2. **Création d'objets :** Les trois commits ont généré pluisieurs nouveaux objets dans le répertoire `.git/objects/` (3 Blobs, 3 Trees, 3 Commits).
3. **Efficacité de la compression :** Chaque instantané complet du fichier est compressé avant d'être écrit sur le disque, ce qui explique pourquoi 3 commits complets n'ont ajouté que **2,55 Ko** d'espace supplémentaire.
