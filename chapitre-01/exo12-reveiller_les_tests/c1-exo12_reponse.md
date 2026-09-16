# Exercice 12 : Exécution des tests unitaires

## 1. Localisation de la désactivation
La compilation et l'exécution globale des tests sont restreintes dans le fichier `Nkentseu.jenga` par les directives suivantes :
* `dutc(enable=True, allow=[...])` (Disable Unit Test Compilation)
* `dute(enable=True, allow=[...])` (Disable Unit Test Execution)
Ces lignes désactivent les tests à l'échelle du workspace, tout en ménageant des exceptions explicites pour certains modules de base via le tableau `allow`.

## 2. Lancement des tests de NKMath
Le module `NKMath` faisant partie de la liste blanche `allow`, il a été possible de forcer la compilation et l'exécution de sa cible `NKMath_Tests`.

## 3. Relevé des résultats
Suite à l'exécution du binaire de test de `NKMath`, voici les métriques observées dans le terminal :

* **Combien de suites existent :** [Insérez le nombre de Test Suites détectées, ex: 12]
* **Combien s'exécutent :** [Insérez le nombre de suites qui ont effectivement tourné, ex: 12]
* **Combien passent :** [Insérez le nombre de tests réussis sur le total, ex: 45/45 (100%)]