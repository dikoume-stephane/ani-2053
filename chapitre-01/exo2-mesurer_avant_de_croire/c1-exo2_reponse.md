## resultats obtenu

sur le projet NKensteu ,nous avons obtenu :
|types|nombre|
|----|-----|
|cpp| 1838|
|header(.h)|2754 |
|total|4 592|
ligne de code |  2891683(en tous)|

## outil utilisé
pour l'optention des resultat, nous avons utilisé l'outil **cloc** au lieu d'une simple commande bash pour plus de precision et pour avoir le nombre de ligne actuel du repo .
```bash
#installation
npm install -g cloc

#ouvrir le dissier de NKensteu et taper
cloc .
```
### resultat obtenu
```
  12654 text files.
   10419 unique files.
    4661 files ignored.

1 error:
Line count, exceeded timeout:  ./Applications/NKCode/src/NKCode/Shell/NkNewWorkspace.h

github.com/AlDanial/cloc v 2.06  T=294.62 s (35.4 files/s, 13440.3 lines/s)
---------------------------------------------------------------------------------------
Language                             files          blank        comment           code
---------------------------------------------------------------------------------------
C/C++ Header                          2754         170410         366094         989033
C++                                   1838         112359         170895         802021
Markdown                               797          54307             44         198137
C                                      311          28909          32099         191500
GLSL                                  3141          17721           3231         174766
JSON                                    66              1              0         156339
Text                                    93          28876              0         137040
XML                                     23            274             60          53809
Python                                 308          12926          17166          40927
TeX                                     94           5565            539          25419
Expect                                   2           3696              0          22253
SVG                                    185           1339            185          16955
HTML                                    69            143            153          14348
CMake                                  132           2242           3063          13262
reStructuredText                        33           3336           3043           5791
Objective-C++                           17           1032            627           5400
Pascal                                  19            336           2990           5274
m4                                       7            282             60           4874
yacc                                     1            269            147           4053
HLSL                                   139            248            599           3621
YAML                                    37            546            678           2942
Assembly                                 9           1033           1476           2810
Java                                    45           1627           5982           2421
PHP                                      4             78            126           1978
Bourne Shell                            65            475           1287           1847
CSV                                      5              0              0           1782
Ada                                     10            599            560           1681
WiX source                               2              0              0           1488
make                                    18            260            299           1419
PowerShell                              15            247            254           1240
C#                                       9            230            506            879
D                                       16            531           3714            786
Windows Resource File                    6            118            315            597
DOS Batch                               20            186            260            554
AsciiDoc                                 3            199              5            549
MSBuild script                           3              1              0            545
IDL                                      4             85              0            492
Metal                                   10             46             60            341
TypeScript                               2             63            220            328
Rust                                    35             48             74            324
SWIG                                    28             80             19            294
Starlark                                 1             20             41            250
Lua                                      4             34             19            231
Windows Module Definition                2             14             14            219
JavaScript                               7             20             66            191
F#                                       8             60             36            183
TOML                                     4             19              4             97
INI                                      5             10              0             79
Swift                                    1              3              9             60
Ant                                      1              8              0             46
Dockerfile                               2             16             14             45
Bourne Again Shell                       2             12             49             41
Visual Studio Solution                   2              2              2             36
ArkTs                                    1              3             17             28
NAnt script                              1              7              0             26
Bazel                                    1              3              0             24
Objective-C                              1              2              7              5
CSS                                      1              0              0              3
---------------------------------------------------------------------------------------
SUM:                                 10419         450956         617108        2891683
---------------------------------------------------------------------------------------
```
## comparaison 
pour les fichier ,les fichier souces etant les .cpp et .h, on obtien un total de 4 592 fichier source qui est largement superieur uax  2641 fichier souces anoncés et un total de 2891683 lignes de code encore superieur aux 1193385 ligne de code annoncées dans le chapitre . 
cet ecart est du a :

- Inclusion du dossier **Build** (Fichiers intermédiaires) : la commande de comptage de **cloc** a été exécutée sans ignorer le dossier **Build**, elle a compté les objets compilés, mais aussi la copie des en-têtes et les fichiers temporaires générés par Jenga. 
- Inclusion des fichiers de test :Le dépôt contient des suites de tests. et encore une fois, la  commande de **cloc** a pris en compte les dossiers **tests**, cela augmente le nombre de fichiers et de lignes par rapport à un comptage restreint au code source.
- L'évolution du dépôt :Comme l'indique le chapitre 1, les mesures du chapitre ont été faites « le jour où l'encadreur a écris cette page ». Le dépôt étant un projet qui évolue, des ajouts ou des corrections ont pu être faits depuis.  
pour les fichiers declares comme ignoré, ma theorie se porte sur les assets du projet (images, video et ...)