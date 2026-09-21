# Exercice 9 : Histoire Complète d'un Fichier du Moteur

## 1. Identification du Fichier Choisis
* **Fichier analysé :** `config/modules.jenga`
* **Rôle dans le moteur :** Fichier de configuration du système de build (*Jenga*) décrivant l'ensemble des modules du moteur (Kernel, Applications, briques de rendu, etc.) ainsi que leurs dépendances et options de compilation.
* **Nombre total de commits ayant impacté le fichier :** 23 commits.la commande tapée pour afficher les commit est `git log --stat --oneline  -- config/modules.jenga` pour afficher par la meme occasion les stat(lignes ajoutées et supprimées su commit) grace au tag `--stat`
---

## 2. Chronologie et Reconstitution Historique

---

### Étape 1 : Création du fichier
* **Commit de création :** `f19260db` les details sont revelé avec la commande `git show f19260db`
* **Auteur & Date :** LeTeguis (`teuguiasederis@gmail.com`)  Dimanche 14 Juin 2026 à 08:47:01 +0100
* **Message de commit :** `chore: snapshot etat complet — reorg sources NKSL + Nkoung (plateforme de jeux 2D: toolkit responsive + Laser Puzzle + Labyrinthe) + Kernel/AI & Kernel/Bare (scaffolds docs) + wiki Foundation + scripts git/.gitattributes`
* **Contexte :** Initialisation globale du dépôt du moteur. Le fichier `config/modules.jenga` a été créé pour définir l'architecture modulaire initiale de la solution (335 lignes introduites d'un coup pour déclarer la fondation du Kernel et des premiers outils).

---

### Étape 2 : Premier changement majeur (Portage de l'IDE NKCode & Réorganisation)
* **Commit :** `3c44a374` les details sont revelé par la commande `git show 3c44a374`
* **Auteur & Date :** LeTeguis Vendredi 31 Juillet 2026 à 16:58:39 +0100
* **Message de commit :** `feat(nkcode): lecteur PDF + portage Linux (XLib/XCB) + restauration des fenetres (#55)`
* **Volume de modifications (`git show --stat`) :** +87 lignes
* **Raisons identifiées dans le message :** 
  * Portage du moteur et de l'IDE `NKCode` sous Linux (dépendances XLib/XCB).
  * Intégration du module complet du lecteur PDF (`NkPdfProbe`, `NkPdfRaster`, `NkPdfRender`) et de ses outils de banc de test.
  * Déclaration de nouveaux symboles de build et de dépendances système nécessaires pour assurer la compilation multiplateforme.

---

### Étape 3 : Deuxième changement majeur (Alignement et Stabilisation de la branche publique)
* **Commit :** `addf709d`les details sont revelé par la commande `git show addf709d`
* **Message de commit :** `NKCode beta.8 a beta.11 : la ligne publiee rejoint enfin main (#86)`
* **Volume de modifications (`git show --stat`) :** 33 modifications (+30 insertions, -3 suppressions)
* **Raisons identifiées dans le message :** 
  * Consolidation et synchronisation des versions bêta (beta.8 à beta.11) de l'IDE `NKCode` vers la branche principale `main`.
  * Mise à jour des drapeaux de compilation, intégration de la gestion de la version `JENGA_VERSION` et mise en conformité des dépendances de la chaîne d'outils.

---

### Étape 4 : Troisième changement majeur (Intégration massive de 8 chantiers fonctionnels)
* **Commit :** `9c3fad33`les details sont revelé par la commande `git show 9c3fad33`
* **Auteur & Date :** LeTeguis Dimanche 13 Septembre 2026 à 07:31:25 +0100
* **Message de commit :** `transit : huit chantiers fusionnés, 226/226, prêt pour relecture (#89)`
* **Volume de modifications (`git show --stat`) :** 57 modifications (+42 insertions, -15 suppressions)
* **Raisons identifiées dans le message :** 
  * Fusion de 8 chantiers techniques majeurs : simulation physique de fluides SPH/DFSPH sur GPU, champs de force/vent (`NkForceField`), rendu vectoriel complexe dans `NKUIDesign` (gestion des contours et dégradés).
  * Le fichier de configuration des modules est révisé pour orchestrer ces nouvelles briques du Kernel et relier correctement les nouveaux bindings de shaders et de physique GPU.

---

## 3. Analyse 

L'analyse de l'historique du fichier `config/modules.jenga` via les commandes `git log` et `git show` montre clairement l'évolution architecturale du moteur :

1. **Phase de fondation (Juin 2026) :** Structure  initiale posant les bases du Kernel et des modules .
2. **Phase d'extension  (Juillet - Août 2026) :** Expansion du moteur pour supporter des outils complexes comme l'IDE `NKCode`, nécessitant des modules graphiques et de traitement de documents (PDF, polices).