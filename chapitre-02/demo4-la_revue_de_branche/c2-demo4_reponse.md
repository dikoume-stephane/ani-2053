# Démonstration 4 : Revue de Code Croisée et Évaluation du Travail d'Équipe

## 1. Contexte et Répartition du Travail

* **Projet :** Calculatrice en C++ (`MonEssaie`)
* **Équipe Implémentation :** Prisca (`noumssiprisca6-star`)et Maël (`Nyeck-Abondo`)
* **Équipe Tests Unitaires :** Stéphane (moi) et emma 
* **Objectif de l'exercice :** Analyser l'historique Git des branches créées par le binôme d'implémentation pour évaluer la qualité de leur travail.

---

## 2. Rapport Écrit de Revue de Code

---

### 1. Ce que font les branches analysées
* **`origin/feature-multiplication` (Maël Abondo) :**
  * Ajoute la fonction pour la multiplication des types simples et des types personnalisés surchargeant l'opérateur `*`.
* **`origin/feature-soustraction` (Maël Abondo) :**
  * Ajoute la fonction de soustraction dans la classe `calculator`.
* **`origin/feature-add` (Prisca Noumssi) :**
  * Ajout et implémentation des fonctions de calcul dans le fichier `.cpp`.
* **`origin/feature-add-sous` (Prisca Noumssi) :**
  * Modifications d'en-tête et déclarations des méthodes de calcul de base.

---

### 2. Lisibilité et Qualité des Commits

* **Points Positifs :**
  * **Maël Abondo :** Ses messages respectent les règles professionnelles (`feat: ...`). Ils contiennent un titre clair et une explication détaillée de ce qu'apporte le code.
  * **Prisca Noumssi :** Elle a bien séparé la déclaration des fonctions (fichiers `.h`) et leur implémentation (fichiers `.cpp`).

* **Points à Améliorer / Défauts de Lisibilité :**
  * **Messages de commit trop vagues :** Plusieurs commits de Prisca ont des messages peu clairs (`amelioration.`, `enregistrement`, `modification de l'entete`).
  * **Allers-retours inutiles dans l'historique :** j'ai remarqué une suite de `Revert` successifs (`Revert "enregistrement"`, `Revert "la declaration..."`). Cela surcharge l'historique avec des actions d'annulation qui auraient pu être évitées avant de pousser.
  * **Erreurs de frappe :** Plusieurs fautes dans les messages de merge (ex: `merge branch ^Leature-calculinto main`).

---

### 3. Ce qui manque

* **Manque d'homogénéité dans le style de commit :** L'équipe devrait adopter une convention commune pour que tout l'historique soit lisible.

* **Nettoyage de l'historique :** une meilleure attention avant le push permettrait d'éviter les commits de test ("enregistrement") et les `Revert` répétés.

---

### 4. Ce qui ne devrait pas y etre

* **Historique pollué :** Les commits d'erreurs (`enregistrement`, `erreur pousse`) restent visibles dans l'historique partagé de la branche distant.
