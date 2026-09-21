# Exercice 9 : Histoire Complète d'un Fichier du Moteur

## 1. Identification du Fichier Choisis
* **Fichier analysé :** `config/modules.jenga`
* **Rôle dans le moteur :** Fichier de configuration du système de build (*Jenga*) décrivant l'ensemble des modules du moteur (Kernel, Applications, briques de rendu, etc.) ainsi que leurs dépendances et options de compilation.
* **Nombre total de commits ayant impacté le fichier :** 23 commits.la commande tapée pour afficher les commit est `git log --stat --oneline  -- config/modules.jenga` pour afficher par la meme occasion les stat(lignes ajoutées et supprimées su commit) grace au tag `--stat`
```powershell
git log --stat --oneline  -- config/modules.jenga                                                                                              
9c3fad33 (origin/transit, origin/main, origin/HEAD) transit : huit chantiers fusionnés, 226/226, prêt pour relecture (#89)
 config/modules.jenga | 57 ++++++++++++++++++++++++++++++++++++++--------------
 1 file changed, 42 insertions(+), 15 deletions(-)
addf709d NKCode beta.8 a beta.11 : la ligne publiee rejoint enfin main (#86)
 config/modules.jenga | 33 ++++++++++++++++++++++++++++++---
 1 file changed, 30 insertions(+), 3 deletions(-)
964b3779 NKAnimation : le substrat d animation quitte le renderer
 config/modules.jenga | 10 +++++++---
 1 file changed, 7 insertions(+), 3 deletions(-)
d9e1f82d NKAnimPhysics : extraire la pose physiquement correcte hors du renderer
 config/modules.jenga | 9 ++++++++-
 1 file changed, 8 insertions(+), 1 deletion(-)
0702b028 NKXR etage 0 : runtime XR from scratch + simulateur desktop + demo stereo
 config/modules.jenga | 7 ++++++-
 1 file changed, 6 insertions(+), 1 deletion(-)
3c44a374 feat(nkcode): lecteur PDF + portage Linux (XLib/XCB) + restauration des fenetres (#55)
 config/modules.jenga | 87 ++++++++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 87 insertions(+)
ef1bb63b feat(nkai): DQN/PPO, deploiement transformer Qwen2, corps simule, TTS complet, emergence sociale, diffusion, personnalite agent
 config/modules.jenga | 16 +++++++++++++---
 1 file changed, 13 insertions(+), 3 deletions(-)
e562239a chore: consolidation des livraisons verifiees 23-25/07
 config/modules.jenga | 12 +++++++++---
 1 file changed, 9 insertions(+), 3 deletions(-)
e455ee91 fix: retire l'inclusion accidentelle de WIP d'autres agents dans 91a36ee4 (Mou.jenga, Nkentseu.jenga, config/modules.jenga, NkTextRenderer.cpp/h, NkDialogs.cpp) - ce n'etait pas m
on travail, le stash 'WIP autres agents' les conserve intacts pour la reprise
 config/modules.jenga | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)
91a36ee4 docs(nkmedia): ROADMAP a jour - PCM + MP3 embarque dans MP4 (commit 805e0c93)
 config/modules.jenga | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)
11c2da79 feat(renderdemo): mode NK_RECORD - capture multi-backend (SetFinalColorTarget + NkOffscreenTarget readback) -> viewport_capture.mp4 (video+audio+sous-titre, encodage threade)
 config/modules.jenga | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)
d6795b5a feat(nkmedia): nouveau module NKMedia - brique 1 NkMediaProbe (demux d'en-tete ISOBMFF/MP4 + EBML/WebM from-scratch) ; identifie conteneur+codec+params. Valide sur corpus reel (Ba
ssa->MP4/AAC, ghomala->WebM/Opus). ROADMAP conteneurs/codecs staged
 config/modules.jenga | 1 +
 1 file changed, 1 insertion(+)
86231d8e feat(nkspeech): brique 1 Phase 8 - NkAudioFeatures MFCC/log-Mel from-scratch (FFT radix-2 + filtres Mel + DCT + deltas), module NKSpeech + NKSpeechTest 1/1 (sinus 1kHz -> bon cana
l Mel)
 config/modules.jenga | 1 +
 1 file changed, 1 insertion(+)
ae341a7c refactor(nkai): NKGpt etape 2/2 - classe NkGptTrainer reutilisable (config + Prepare/Fit/Generate/reprise) ; main.cpp = pilote ~90 lignes. Conventions projet : NKMath (NkExp/NkCos
), NKLogger (status+texte via logger, sink console auto), une-instruction/ligne + indentation maison (fix .clang-format: NamespaceIndentation All + IndentAccessModifiers true). N'importe q
uelle app peut reutiliser l'entrainement GPT. Build 25/25 OK
 config/modules.jenga | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)
824530f0 refactor(nkai): module NKGpt reutilisable — extraction des briques BPE + corpus + checkpoint de NKGptTrain vers Kernel/AI/NKGpt (lib statique, namespace nkentseu::ai::gpt) ; main.
cpp 649->367 lignes ; utilisable par n'importe quelle app. Etape 1/2 (NkGptTrainer class = etape 2). Build 25/25 OK, comportement identique
 config/modules.jenga | 1 +
 1 file changed, 1 insertion(+)
ba3b0507 feat(editor): editeur de maillage facon Blender + structure n-gon half-edge (NkEditMesh) (#21)
 config/modules.jenga | 8 ++++++++
 1 file changed, 8 insertions(+)
d4fce7ee feat(render): grille infinie reutilisable + fix ombres GL (glClipControl/clipZ01) + fix freeze DX11 (ResizeBuffers/command list) + NkInput cross-platform + cap FPS/vsync + pool ob
ject-UBO dynamique + ombres instanciees ; consolidation WIP multi-modules (NKCode, Noge, ...) (#19)
 config/modules.jenga | 4 ++++
 1 file changed, 4 insertions(+)
137eefc4 feat(nkphysics): M0 — integration semi-implicite + boucle Step (gravite/damping, delegation detection NKCollision, sync shapes) ; NkPhysicsWorld CreateBody/Step + masse/inertie ; 
module enregistre ; self-test 4/4 (chute libre)
 config/modules.jenga | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)
3240b1ae feat(moteur): reconciliation NKRenderer complete + NkAnima (supersede #14) (#16)
 config/modules.jenga | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)
eaaad92b feat(nkcode): IDE NKCode (launcher + outillage) porte sur main (#12)
 config/modules.jenga | 10 +++++++++-
 1 file changed, 9 insertions(+), 1 deletion(-)
f19260db chore: snapshot etat complet — reorg sources NKSL + Nkoung (plateforme de jeux 2D: toolkit responsive + Laser Puzzle + Labyrinthe) + Kernel/AI & Kernel/Bare (scaffolds docs) + wik
i Foundation + scripts git/.gitattributes
 config/modules.jenga | 335 +++++++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 335 insertions(+)
```

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
2. **Phase d'extension  (Juillet - Août 2026) :** Expansion du moteur pour supporter des outils complexes comme l'IDE `NKCode`, nécessitant des modules graphiques et de traitement de documents (PDF, polices, backends XCB/Wayland).
3. ** d'optimisation (Septembre 2026) :** Découpage plus fin des sous-systèmes (Kernel AI, SPH GPU, VFX) nécessitant une mise à jour fréquente de la configuration pour isoler chaque module et optimiser le temps de compilation.