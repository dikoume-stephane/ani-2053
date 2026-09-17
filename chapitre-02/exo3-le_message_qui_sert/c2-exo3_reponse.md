# Exercice 3 : Analyse et Critique des Messages de Commit

## 1 recuperation des commits
* affichage des 10 dernier commit avec la commande `git log --oneline -n 10`
```powershell
PS D:\2DS\projet\programmation_cpp\Nkentseu> git log --oneline -n 10
987304da (HEAD -> etude, main) cation des fichier cibles pour l exo 8
62e09e2e Merge branch 'main' of https://github.com/Rihen-Universe/Nkentseu
8e6cf0ce resolution des exo avant NKRef
9c3fad33 (origin/transit, origin/main, origin/HEAD) transit : huit chantiers fusionnés, 226/226, prêt pour relecture (#89)
dc2154ed Merge pull request #88 from Rihen-Universe/chantier/banc-coherence-registre
07845c6c (origin/chantier/banc-coherence-registre) Garde des chemins partages rapatriee vers main : et elle rougit VRAI
8b869240 Banc de coherence du registre de modules : DETECTER, et ne rien reparer
6fb634fc NKCode : le web sort du polissage et devient la phase 14, avec une echeance reelle
860e9d7f Refonte NK3DModeler : a jour avec main, et NKCode signe sur certificat (#85)
c1c815ff CI : les huit epinglages de Jenga passent par JENGA_VERSION (#87)
```
* apres le choix des commit, je controle leurs contenu avec la commande `git show <identifiant>` ou alors, pour afficher le contenu des trois directement avec `git show -s <liste des identifiants>`
* commande executée : `git show -s c1c815ff 860e9d7f 07845c6c`
```powershell
commit c1c815ffceffc3b66d7661b1ebdf6ec2d23c6b6a
Author: LeTeguis <69282466+LeTeguis@users.noreply.github.com>
Date:   Thu Sep 10 17:48:09 2026 +0100

    CI : les huit epinglages de Jenga passent par JENGA_VERSION (#87)
    
    * CI : les huit epinglages de Jenga passent par JENGA_VERSION
    
    Le 8 septembre, build-remote.yml a cesse d'ecrire la version de Jenga a la
    main et s'est mis a lire Applications/NKCode/JENGA_VERSION. Les TROIS AUTRES
    workflows sont restes epingles sur `feat/evenement-avertissement`, une branche
    figee en Jenga 2.4.0. La source unique n'en etait donc pas une.
    
    Tant que NKCode n'employait aucune fonction recente, rien ne le revelait. La
    ligne beta.11 a rejoint main (PR #86), NKCode.jenga y emploie appurl(), et les
    douze jobs de build-gemcrush et build-jeux-plateau se sont arretes net sur :
    
        Error loading workspace: name 'appurl' is not defined
        Multi-platform C/C++ Build System v2.4.0
    
    Un message qui ne prononce jamais le mot « Jenga » et laisse croire a une
    faute dans le fichier de projet. La version etait imprimee juste dessous,
    personne ne l'a regardee.
    
    Chacun des neuf jobs lit desormais JENGA_VERSION avant de cloner Jenga, et
    s'epingle sur le tag correspondant. Verifie apres coup : YAML valide partout,
    et dans chaque job le clonage de Nkentseu precede la lecture, qui precede le
    clonage de Jenga.
    
    Le numero n'existe plus qu'a UN endroit. Une release de Jenga se propage en
    changeant une ligne, et un nom de branche remis ici redeviendrait la meme
    panne.
    
    * CI jeux de plateau : libasound2-dev manquait, quatre erreurs par jeu
    
    Une fois l'epinglage de Jenga corrige, les trois jobs Linux sont alles bien
    plus loin et se sont arretes sur de VRAIES erreurs de compilation :
    
        NkAudioBackends.cpp:31:10: fatal error: 'alsa/asoundlib.h' file not found
        NkAudioCapture.cpp:...:10: fatal error: 'alsa/asoundlib.h' file not found
    
    NkDames, NkEchecs et NkLudo dependent de NKAudio, dont le filtre Linux lie
    `asound`. Le workflow installait X11 et GL, jamais ALSA. build-gemcrush.yml
    l'installait deja, avec un commentaire qui dit exactement pourquoi : cette
    ligne-la n'a simplement jamais ete recopiee ici.
    
    build-macos.yml n'en a pas besoin : son job Linux construit NkRef, qui ne
    depend d aucun audio. Verifie plutot que suppose.

commit 860e9d7f1f9ad11f7a238084eb7a86207af67368
Author: LeTeguis <69282466+LeTeguis@users.noreply.github.com>
Date:   Thu Sep 10 17:48:29 2026 +0100

    Refonte NK3DModeler : a jour avec main, et NKCode signe sur certificat (#85)
    
    * NkEditMesh : la table CHAINEE etait le cout de chaque edition -- table plate, et le banc qui mesure enfin l
a PORTEE de chaque operation
    
    Deux choses, dans l ordre impose : d abord la mesure, ensuite le code.
    
    1. BANC DE PORTEE (--perf, hors reference)
       Nouvelle section : pour chaque operation, combien d aretes elle touche
       VRAIMENT. Une arete est touchee si elle est creee, supprimee, ou si une
       extremite a bouge -- identite POSITIONNELLE, parce que ToPolygons /
       BuildFromPolygons RENUMEROTENT tout et qu une comparaison d indices
       rendrait 100 pour cent touchees pour toute operation, y compris pour
       celles qui ne changent rien.
       Resultat : une extrusion de 3 faces sur une grille 128x128 touche 32
       aretes sur 33 024 (0,10 pour cent) et coute pourtant le maillage entier.
       La courbe le dit : touchees CONSTANTES a 32, temps x4,7 par x4 faces.
       Les operations de portee GLOBALE ont leur ligne a part (Catmull-Clark
       touche 498 pour cent, Triangulate 49,6) au lieu d etre fondues dans une
       moyenne qui aurait cache les deux comportements.
    
    2. LE COUPABLE N EST PAS LA CLASSE, C EST LA TABLE
       NkHashMap est CHAINEE : un noeud alloue par insertion, ~195 ns par entree
       mesures hors moteur. Une extrusion sur 65 536 faces passe par 262 144 de
       ces insertions (LinkTwins) plus 66 049 (BuildVertexMerge).
       NkEmFlatMap : adressage ouvert, sondage lineaire, un seul bloc, aucune
       allocation par entree, meme finisseur splitmix64 qu en Q73. Employee aux
       trois points chauds : BuildVertexMerge, LinkTwins, RebuildEdges.
    
       Elle ne peut RIEN changer aux resultats : les trois appelants suivent
       tous la regle la premiere insertion gagne, qui ne depend que de l ordre
       de leur boucle et jamais de l ordre des seaux. La reference du harnais
       l atteste : 274 cas CONFORME, octet pour octet, empreintes aretes/
       comprises.
    
       Commentaire retire plutot que laisse mentir : la mesure sans Reserve
       27,3 ms / avec 18,9 ms portait sur une table qui n est plus employee la.
    
    Reference inchangee (274). Point de reprise : 631ad2bd.
    
    * Incrementalite : AddWireEdge cesse de tout reconstruire (959 ms -> 2,8 ms pour 20 clics) et EdgeBetween ces
se d etre lineaire -- avec les quatre controles qui rougissent chacun autrement
    
    LA MESURE D ABORD, comme convenu.
    
    Un banc mesure la CROISSANCE de 20 appels par taille de maillage. Il trouve
    les deux seules fonctions de cette classe ou la structure SURVIT a l
    operation -- partout ailleurs elle est detruite et refaite :
        65 536 faces   AddWireEdge 958,6 ms (~48 ms par clic, x4,6 par x4 faces)
                       EdgeBetween  41,1 ms pour 20 questions
    EdgeBetween appelait BuildVertexMerge A CHAQUE APPEL : une table de hachage
    sur tous les sommets pour repondre a une question que le cycle disque rend
    locale. La fonction qui EXISTE pour montrer l interet du disque le detruisait
    en entrant.
    
    CE QUI CHANGE
    1. `canonOf` (l identite soudee) est CONSERVE par RebuildEdges au lieu d etre
       jete. Meme duree de vie que edges/radialPool/diskPool, vide par Clear().
       Ce n est pas un cache de plus : recalculer canon frais tout en lisant un
       diskPool perime rendait la fonction plus fraiche que sa donnee.
    2. `diskStart/diskCount` ne sont plus ecrits que sur le sommet REPRESENTANT ;
commit 07845c6c9170f588ca46b8ef5023b5f30d997aab (origin/chantier/banc-coherence-registre)
Author: LeTeguis <teuguiasederis@gmail.com>
Date:   Sat Sep 12 17:49:20 2026 +0100

    Garde des chemins partages rapatriee vers main : et elle rougit VRAI
    
    Les regles de ce depot ne manquaient pas : elles vivaient sur
    integration/2026-09-06, une branche qui n'a jamais fusionne. Ce commit en porte
    UNE, par chemin, sans fusionner quoi que ce soit :
    
        verif_chemins.sh              la garde       (200 lignes)
        contre_epreuve_chemins.sh     son volet negatif (231 lignes)
        config/chemins_partages.list  sa donnee      (76 lignes)
    
    LA REGLE
        « Un chemin partage entre agents concurrents est une variable globale
        deguisee en fichier temporaire. » Le 24/08, le commit 9b774ab8 s'est
        retrouve avec le MESSAGE d'un autre agent et SES douze fichiers, parce que
        les messages etaient composes a un chemin FIXE sous /tmp. Deux agents qui
        ecrivent au meme instant echangent leurs contenus, ET RIEN N'ECHOUE.
    
    CE QU'ELLE TROUVE SUR MAIN : 7 OCCURRENCES, ET C EST UN ROUGE VRAI
        Kernel/Runtime/NKXR/tests/build_tests.sh:37-40    /tmp/nkxrtests
        Kernel/System/NKLogger/tests/build_bench.sh:20-22 /tmp/nklogbench
    
        Ce ne sont pas des artefacts de rapatriement. Ce sont deux scripts SUIVIS
        PAR MAIN qui font `mkdir -p /tmp/nkxrtests` puis compilent leurs .exe
        dedans, a un chemin FIXE. Cette machine porte 29 arbres de travail : deux
        agents qui lancent build_tests.sh en meme temps ecrivent le meme
:
```


## 2 Évaluation des trois commits retenus

---

### Commit 1 : `c1c815ff`
**Message :** `CI : les huit epinglages de Jenga passent par JENGA_VERSION (#87)`

* **Dit-il ce qu'il fait ?** **Oui.** Le titre et le corps expliquent clairement l'harmonisation du clonage de Jenga dans tous les workflows CI via la lecture du fichier `JENGA_VERSION`.
* **Pourquoi ?** **Oui, de façon exemplaire.** Le corps détaille la cause racine de la panne (incompatibilité due à la fonction `appurl()` avec Jenga 2.4.0) ainsi que le message d'erreur trompeur.
* **Porte-t-il un seul sujet ?** **Presque.** Il traite principalement de la CI Jenga, mais inclut à la fin une correction secondaire (ajout de la dépendance `libasound2-dev` pour Linux).
* **Verdict :** **Très bon commit.** Même s'il comporte un second volet, la documentation du contexte et du diagnostic est d'une grande qualité professionnelle.

---

### Commit 2 : `860e9d7f`
**Message :** `Refonte NK3DModeler : a jour avec main, et NKCode signe sur certificat (#85)`

* **Dit-il ce qu'il fait ?** **Non dans le titre, oui dans le corps.** Le titre est un assemblage vague ("Refonte", "a jour", "signe"), alors que le corps décrit une optimisation algorithmique très précise dans `NkEditMesh` (passage d'une table chaînée `NkHashMap` à une table plate `NkEmFlatMap`).
* **Pourquoi ?** **Oui.** La modification est fortement justifiée par des chiffres mesurés hors moteur (`195 ns` par entrée) et des gains de performance concrets.
* **Porte-t-il un seul sujet ?** **NON (Défaut majeur d'atomicité).** Le titre accumule au moins trois tâches distinctes : la refonte du modéleur 3D, la synchronisation avec la branche `main`, et la signature de certificat pour `NKCode`.
* **Verdict :** **Le plus faible sur le plan de la structure.** C'est un "commit fourre-tout" dont le titre masque le vrai travail technique réalisé dans le code.

---

### Commit 3 : `07845c6c`
**Message :** `Garde des chemins partages rapatriee vers main : et elle rougit VRAI`

* **Dit-il ce qu'il fait ?** **Oui dans le corps.** Il détaille l'ajout de scripts de vérification (`verif_chemins.sh`, `contre_epreuve_chemins.sh`) pour détecter les conflits de chemins temporaires sous `/tmp`. Le titre comporte toutefois une formule informelle (*": et elle rougit VRAI"*).
* **Pourquoi ?** **Oui.** Il explique parfaitement l'origine du bug historique (collision de deux agents écrivant au même instant sur un fichier temporaire fixe).
* **Porte-t-il un seul sujet ?** **Oui.** Le périmètre est bien centré sur la détection des collisions de chemins partagés.
* **Verdict :** **Moyen-Bon.** Le fond technique est irréprochable, mais la formulation du titre manque de rigueur conventionnelle.

---

## 2. Réécriture du commit le plus faible (`860e9d7f`)

### Problèmes identifiés
1. **Défaut d'atomicité :** Mélange de trois sujets indépendants dans un seul commit.
2. **Titre flou :** Le mot "Refonte" ne dit pas ce qui a été modifié.

### Proposition de découpage et réécriture (Règles de l'art)

Ce commit aurait dû être divisé en trois commits atomiques. Voici la réécriture du message principal axé sur la partie modélisation 3D :

```text
perf(NK3DModeler): replace NkHashMap with NkEmFlatMap in NkEditMesh

- Replace chained hash map with flat open-addressing table in hotspots
  (BuildVertexMerge, LinkTwins, RebuildEdges) to remove per-entry allocations.
- Reduce AddWireEdge execution time on 65k faces from 959 ms to 2.8 ms.

```