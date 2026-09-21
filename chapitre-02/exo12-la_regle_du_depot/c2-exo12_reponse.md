# Exercice 12 : Bonnes Pratiques et Règles Git pour l'Équipe

## 1. Contexte et Objectif

Ce document définit les règles de travail sur Git pour notre équipe de 4 étudiants. Son objectif est de garantir un projet propre, d'éviter les conflits de code inutiles et d'assurer une collaboration fluide et sécurisée tout au long du développement.

---

## 2. Guide de Nommage des Branches

Il est interdit de travailler directement sur la branche principale (`main` ou `master`). Chaque nouvelle fonctionnalité ou correction doit être développée dans une branche dédiée.

* **Format du nom :** `type/description-courte` (en minuscules, sans accents, mots séparés par des tirets).
* **Les préfixes autorisés :**
  * `feature/` : pour l'ajout d'une nouvelle fonctionnalité (ex: `feature/lecteur-pdf`).
  * `fix/` : pour la correction d'un bug (ex: `fix/encodage-utf8`).
  * `docs/` : pour la rédaction ou la mise à jour de la documentation.
  * `refect/` : pour la réorganisation du code sans changement de comportement.

---

## 3. Règles de Rédaction des Commits

Chaque commit doit représenter une unité de travail cohérente et terminée.

* **Principe:** Un commit ne doit traiter qu'un seul sujet à la fois. Si vous modifiez deux fonctionnalités différentes, faites deux commits distincts.
* **Format du message :** Utilisez des messages courts et explicites au format : `type: description courte pour l'entete du commit`
  * *Exemple valide :* `feat: ajout du bouton de validation dans le formulaire`
puis, une description detaillée apres un saut d'une ligne pour expliquer les modification si necessaire.

---

## 4. Relecture de Code et Validation

Pour garantir la qualité du code et s'assurer que toute l'équipe comprend le projet, **aucun code ne rejoint la branche principale sans relecture**.

1. **Création d'une Pull Request (PR) :** Une fois le travail sur votre branche terminé, ouvrez une Pull Request vers `main`.
2. **Binômes de relecture :** Deux binômes fixes sont établis pour relire le travail mutuel :
   * L'étudiant A relit le travail de l'étudiant B (et inversement).
   * L'étudiant C relit le travail de l'étudiant D (et inversement).
3. **Condition de fusion :** Une PR nécessite au moins **une validation explicite** du relecteur avant de pouvoir être fusionnée.

---

## 5. Ce qui est Strictement Interdit

1. **Push direct sur `main` :** Il est totalement interdit de faire un `git push` directement sur la branche principale. Tout passe par une Pull Request.
2. **Réécriture de l'historique public :** Ne jamais utiliser `git push --force` ou effectuer un `git rebase` sur des branches partagées avec les autres membres.
3. **Fichiers volumineux ou temporaires :** Interdiction d'ajouter des exécutables (`.exe`), des vidéos, des archives (`.zip`) ou des dossiers de compilation (`build/`, `.vscode/`) dans Git. Vérifiez que votre fichier `.gitignore` est bien configuré.
4. **Commits de code qui ne compile pas :** Tout commit poussé sur le dépôt doit être fonctionnel et compiler sans erreur.

---

## 6. Procédure d'Urgence : Que Faire quand `main` est Cassée ?

Si un bug ou un crash survient sur la branche principale malgré les précautions, appliquez la procédure suivante :

1. **Alerter immédiatement l'équipe :** Prévenez tout le groupe sur votre canal de discussion principal (Discord / WhatsApp) pour que personne ne mette à jour sa branche pendant la résolution.
2. **Identifier le commit fautif :** Utilisez `git log` pour trouver le dernier commit fusionné qui a causé la panne.
3. **Annuler proprement avec `git revert` :**
   * L'auteur du commit (ou le relecteur) crée immédiatement une branche d'urgence `fix/reparer-main`.
   * Il exécute la commande `git revert <hash_du_commit_fautif>` pour créer un commit d'annulation sécurisé.
4. **Fusionner en priorité :** La PR d'annulation est relue en urgence par l'un des membres disponibles et fusionnée immédiatement pour rétablir `main` dans un état stable.