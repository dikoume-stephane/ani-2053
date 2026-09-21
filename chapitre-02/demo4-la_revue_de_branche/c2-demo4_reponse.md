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

remarque: les modification de ma collaboratrice emma ne sont pas visibls car elle a ue un probleme et par la meme occasion un retard sur le groupe .

### 5. sorties utilisées pour la revue
```powershell
D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\MonEssaie> git branch -r
  origin/HEAD -> origin/main
  origin/feature-add
  origin/feature-add-sous
  origin/feature-calcul
  origin/feature-multiplication
  origin/feature-soustraction
  origin/feature/unitest
  origin/fix-calcul
  origin/main
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\MonEssaie> git log origin/feature-add
commit 663a359dc18dc71c253a2fc27b9b4f97ca70fbb8 (origin/feature-add)
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Mon Sep 21 11:18:45 2026 +0200

    feat :la calculatrice .cpp
    apres la declaration  des fonction , il faut desormais les implementer d'ou la presence de ce fichier pour inserer de nouvelle fonctionnalire de calcul

commit 54e8ac62e54d88e94677241f3c9e5fc1cccd1016
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Sun Sep 20 00:27:42 2026 +0200

    les fonction de calcul implementer dans le fichier .cpp afin de construire des fonctions actives

commit b4555be10163894907816b519c4b585c7692866a
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Sun Sep 20 00:04:34 2026 +0200

     amelioration.

commit badb5f6d68034c545ff788f3c058a8adf15fcc6b
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Sat Sep 19 23:58:09 2026 +0200

    Revert " enregistrement"
    
    This reverts commit e7e4ad45629caaa4dc749e430d41d2b7e7e3b830.

commit e7e4ad45629caaa4dc749e430d41d2b7e7e3b830
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Sat Sep 19 23:46:49 2026 +0200

     enregistrement

commit 07123e2406b912e86562bbd60f961b57cd6277d0
Merge: a9ffe1a ebbb3a2
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Sat Sep 19 23:24:17 2026 +0200

     merge branch ^Leature-calculinto main

commit ebbb3a2df832f79334131fce555be27fae45598d (origin/feature-add-sous)
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Sat Sep 19 23:18:57 2026 +0200

    modification de l'entete

commit a9ffe1a189f38076fc14a97253c8df12ff429dd2
Merge: 174c190 d8c080a
Author: Nyeck-Abondo <emilemaelnyeckabondo@gmail.com>
Date:   Sat Sep 19 22:18:47 2026 +0100

    Merge pull request #1 from noumssiprisca6-star/feature-add-sous
    
    Feature add sous

commit d8c080ac4c6e1f88daf25e5a9c272eadf7fd2126
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Sat Sep 19 22:50:33 2026 +0200

     la declaration des methodes necessaire pour l'implementation des fonctions de calcul simple

commit c6b0a4f79050d57b76ff1c49f2720500914b8781
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Sat Sep 19 22:48:55 2026 +0200

    Revert " la declaration des methodes necessaire pour l'implementation des fonctions de calcul simple"
    
    This reverts commit 1981037fd463a2b52e7eb6abb37bf05b65ebd41c.

commit 1981037fd463a2b52e7eb6abb37bf05b65ebd41c
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Sat Sep 19 22:41:59 2026 +0200

     la declaration des methodes necessaire pour l'implementation des fonctions de calcul simple

commit f3e2f111f44f7d80f6226063381ed7a5f19afae9
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Sat Sep 19 22:35:02 2026 +0200

    Revert " la declaration des methodes necessaire pour l'implementation des fonctions de calcul simple"
    
    This reverts commit 174c190cb9daa951c3fbdcb4f32b405dea90b02c.

commit 174c190cb9daa951c3fbdcb4f32b405dea90b02c (origin/feature-calcul)
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Sat Sep 19 22:06:21 2026 +0200

     la declaration des methodes necessaire pour l'implementation des fonctions de calcul simple

commit 1bb1be4cb3c4be33a579bf3049c2533f3ddf6d7b (main)
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Sat Sep 19 21:30:59 2026 +0200

    travail collaboratif sur GitHub
    L'objectif est d'évaluer la qualité du travail d'un autre groupe sur une branche Git donnée, de consigner nos remarques par écrit, puis d'en débattre oralement 
à quatre

commit 8e1243b07b9d126a6670b847e8479aa63581acf2
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Sat Sep 19 14:51:03 2026 +0200

     ajout du travail super important

commit c5690850a84441747346c27d4bdee311184b31a5
Merge: 13601be 042ed95
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Sat Sep 19 14:03:15 2026 +0200

    resolution du conflit sur test .cpp

commit 042ed95617cb5c195bcfe3dc1e80002c82bf5ab4
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Sat Sep 19 13:49:50 2026 +0200

    modification du message sur feature

commit 13601becb805a2581387d03046df3b4b176914d0
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Sat Sep 19 13:44:58 2026 +0200

    modification du message sur main

commit 45fb5e9e58d991390316c4189c10db3c11ad8906
Merge: 6962d2c ff48a8a
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Sat Sep 19 13:10:10 2026 +0200

    resolution es conflits

commit 6962d2c0e076d56e9b51786ac574565f03969ccb
Merge: bbadd86 e15be64
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Sat Sep 19 12:20:17 2026 +0200

    Merge Branch ^Leatureinto main

commit bbadd864fc306bb4fafb15dcc771f93decd99bcc
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Sat Sep 19 12:19:07 2026 +0200

    correction du bug sur main

commit e15be64a306b162fe0f3ae1840aa900d3e3029da
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Sat Sep 19 12:15:54 2026 +0200

    ajout de la nouvelle foctionnalite

commit a2d84645d94e6eda318a26d08d9368fda86d9dcb
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Sat Sep 19 12:05:57 2026 +0200

    initialisation du projet

commit 0e2cfd3c19567fefa58dccdeff627bd765662363
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Sat Sep 19 11:47:45 2026 +0200

    ajout d'une documentation descriptive a titre d'essaie dans mon nouveau depot appeler MonEssaie

commit 89f463b1ac9817cf630ea79c7ae0b58659ec21b0
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Fri Sep 18 19:05:26 2026 +0200

    suppression de la video

commit e4ff8cf99ce626ff581d5fa209660827ae7f5600
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Fri Sep 18 19:02:06 2026 +0200

    ajout d'une  video de 10Mo

commit afcc158864db683d917d6d159498cf863993d071
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Fri Sep 18 13:52:15 2026 +0200

    ajout de la fonction rebase

commit c0b2c46f5fbd8e5c520e085735d6368acb34276f
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Fri Sep 18 13:48:49 2026 +0200

     ajout de la fonction merge

commit fce2868ac260221bcaf92a2f1f6593a5cea1c85a
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Fri Sep 18 13:42:51 2026 +0200

    ajout de la fonction merge

commit ff48a8ad2f5d45d119ad9aae611b7d28011d8a3c
Merge: ff2fe46 9fb64fc
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Fri Sep 18 01:33:04 2026 +0200

    Merge branch 'main' of https://github.com/noumssiprisca6-star/MonEssaie

commit ff2fe4674b9fb46d55e1c7e761e3e4df300881c1
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Fri Sep 18 01:32:22 2026 +0200

    Modification du bas du fichier par  SecondRep

commit 9fb64fc2f4b58da5897e8f8716bd5eea6f9e12c9
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Fri Sep 18 01:25:30 2026 +0200

    modification ligne 3 du repertoire 1 MonEssaie

commit 3b416cc17d64371a08e4bc22377266cc3ae41e80
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Fri Sep 18 01:14:44 2026 +0200

    modification ligne 5 du repertoire 2 SecondRep MonEssaie .

commit 2a326d73d3a19c6e4b095034fef162a653ecab16
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Thu Sep 17 23:55:42 2026 +0200

    conflit resolu

commit 880732f412b2168efb38874c6ea16936a0107f55
Merge: 30c8f05 de87a31
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Thu Sep 17 23:40:03 2026 +0200

     resolution du conflit

commit 30c8f054be1f3e9c30a6118a04fb29b127dec34f
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Thu Sep 17 23:25:32 2026 +0200

    modification par le second depot

commit de87a3105394697e4feee2304a61f1b37ef8b393
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Thu Sep 17 23:18:24 2026 +0200

     modification par le premier depot

commit 34228c2fcdc88863f7e8c01c768e3947cb974d0e
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Thu Sep 17 16:36:15 2026 +0200

    erreur pousse

commit abdd5a9548f63f10c8a9936d210cbfb5fe2f16fd
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Thu Sep 17 15:19:42 2026 +0200

    mon troisieme commit

commit 5c267e52ad2f74de2626e6882caf16f4c54d8a1e
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Thu Sep 17 15:18:13 2026 +0200

    deuxieme commit

commit 8b3267f3c694527e0c7e12c6c299be0b82a4277e
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\MonEssaie> git log origin/feature-add-sous                  
commit ebbb3a2df832f79334131fce555be27fae45598d (origin/feature-add-sous)
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Sat Sep 19 23:18:57 2026 +0200

    modification de l'entete

commit d8c080ac4c6e1f88daf25e5a9c272eadf7fd2126
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Sat Sep 19 22:50:33 2026 +0200

     la declaration des methodes necessaire pour l'implementation des fonctions de calcul simple

commit c6b0a4f79050d57b76ff1c49f2720500914b8781
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Sat Sep 19 22:48:55 2026 +0200

    Revert " la declaration des methodes necessaire pour l'implementation des fonctions de calcul simple"
    
    This reverts commit 1981037fd463a2b52e7eb6abb37bf05b65ebd41c.

commit 1981037fd463a2b52e7eb6abb37bf05b65ebd41c
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Sat Sep 19 22:41:59 2026 +0200

     la declaration des methodes necessaire pour l'implementation des fonctions de calcul simple

commit f3e2f111f44f7d80f6226063381ed7a5f19afae9
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Sat Sep 19 22:35:02 2026 +0200

    Revert " la declaration des methodes necessaire pour l'implementation des fonctions de calcul simple"
    
    This reverts commit 174c190cb9daa951c3fbdcb4f32b405dea90b02c.

commit 174c190cb9daa951c3fbdcb4f32b405dea90b02c (origin/feature-calcul)
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Sat Sep 19 22:06:21 2026 +0200
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\MonEssaie> git log origin/feature-multiplication                       
commit ca1909a2f33e6ddd753661a338c4ec2b7078c9b0 (origin/feature-multiplication)
Author: Maël Abondo <emilemaelnyeckabondo@gmail.com>
Date:   Mon Sep 21 10:21:14 2026 +0100

    feat: Ajout de la multiplication par types simples.
    
    LA calculatrice ne bénéficiait pas encore de la capaicité de multiplier les types simples proposés par c++ ou encore les types définis par l'utilisateurs surdéfinissant l'opérateur *.
    La fonction Template Multiplication ajoute maintenant cette possibilité.

commit 46d57487086eadd04f8d38d13c581a91918ee011 (origin/feature-soustraction)
Author: Maël Abondo <emilemaelnyeckabondo@gmail.com>
Date:   Sat Sep 19 23:34:21 2026 +0100

    feat : ajout de l'opération de soustraction
    
    La classe calculator ne présentait pas encore de possibilité de faire l'opération de multiplication. LA fonction template Soustraction prends ainsi en charge l'
opération de soustraction pour tous les types de bases de c++.
    La calculatrice peut ainsi soustraire n'importe quelle valeur sans soucis.

commit 2a420a6f0a1972910e255a9a68bd96f6a7d11b55
Merge: a9ffe1a b4555be
Author: Nyeck-Abondo <emilemaelnyeckabondo@gmail.com>
Date:   Sat Sep 19 23:16:07 2026 +0100

    Merge pull request #3 from noumssiprisca6-star/feature-add
    
    Feature add

commit b4555be10163894907816b519c4b585c7692866a
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Sun Sep 20 00:04:34 2026 +0200

     amelioration.

commit badb5f6d68034c545ff788f3c058a8adf15fcc6b
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Sat Sep 19 23:58:09 2026 +0200

    Revert " enregistrement"
    
    This reverts commit e7e4ad45629caaa4dc749e430d41d2b7e7e3b830.

commit e7e4ad45629caaa4dc749e430d41d2b7e7e3b830
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Sat Sep 19 23:46:49 2026 +0200

     enregistrement

commit 07123e2406b912e86562bbd60f961b57cd6277d0
Merge: a9ffe1a ebbb3a2
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Sat Sep 19 23:24:17 2026 +0200

     merge branch ^Leature-calculinto main

commit ebbb3a2df832f79334131fce555be27fae45598d (origin/feature-add-sous)
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Sat Sep 19 23:18:57 2026 +0200

    modification de l'entete

commit a9ffe1a189f38076fc14a97253c8df12ff429dd2
Merge: 174c190 d8c080a
Author: Nyeck-Abondo <emilemaelnyeckabondo@gmail.com>
Date:   Sat Sep 19 22:18:47 2026 +0100

    Merge pull request #1 from noumssiprisca6-star/feature-add-sous
PS D:\2DS\projet\programmation_cpp\niveau 2\sprint_1\MonEssaie> git log origin/feature-soustraction
commit 46d57487086eadd04f8d38d13c581a91918ee011 (origin/feature-soustraction)
Author: Maël Abondo <emilemaelnyeckabondo@gmail.com>
Date:   Sat Sep 19 23:34:21 2026 +0100

    feat : ajout de l'opération de soustraction
    
    La classe calculator ne présentait pas encore de possibilité de faire l'opération de multiplication. LA fonction template Soustraction prends ainsi en charge l'opération de soustraction pour tous les types de bases de c++.
    La calculatrice peut ainsi soustraire n'importe quelle valeur sans soucis.

commit 2a420a6f0a1972910e255a9a68bd96f6a7d11b55
Merge: a9ffe1a b4555be
Author: Nyeck-Abondo <emilemaelnyeckabondo@gmail.com>
Date:   Sat Sep 19 23:16:07 2026 +0100

    Merge pull request #3 from noumssiprisca6-star/feature-add
    
    Feature add

commit b4555be10163894907816b519c4b585c7692866a
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Sun Sep 20 00:04:34 2026 +0200

     amelioration.

commit badb5f6d68034c545ff788f3c058a8adf15fcc6b
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Sat Sep 19 23:58:09 2026 +0200

    Revert " enregistrement"
```
