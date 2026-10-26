import os
from pathlib import Path

# Colle ici tes 12 lignes d'exercices
# Format attendu : "chemin/vers/dossier/fichier1, fichier2, fichier3"
devoirs = [
    "chapitre-07/exo10-trois_portes_trois_estimations/portes.txt",
    "chapitre-07/exo9-le_chemin_d_une_touche/touche.txt",
    "chapitre-07/exo8-le_fichier_long_et_le_fichier_difficile/fichiers.txt",
    "chapitre-07/exo7-le_carnet_d_une_heure/carnet.txt",
    "chapitre-07/exo6-la_sonde_qui_compte/sonde.cpp, sonde.txt",
    "chapitre-07/exo5-qui_appelle_vraiment/appelants.cpp, appelants.txt",
    "chapitre-07/exo4-le_mensonge_suivant/mensonge.txt",
    "chapitre-07/exo3-suivre_un_appel/appel.txt",
    "chapitre-07/exo2-les_trois_questions/questions.txt",
    "chapitre-07/exo1-trente_secondes_de_carte/carte.txt"
    # Ajoute les 10 autres lignes ici...
]

def generer_arborescence(liste_devoirs):
    for ligne in liste_devoirs:
        # Séparer les éléments par la virgule
        elements = ligne.split(',')
        
        if not elements:
            continue
            
        # Le premier élément contient le chemin complet du premier fichier
        premier_element = elements[0].strip()
        chemin_fichier1 = Path(premier_element)
        
        # Déduire le dossier parent
        dossier = chemin_fichier1.parent
        
        # 1. Créer les dossiers (parents inclus) sans erreur s'ils existent déjà
        dossier.mkdir(parents=True, exist_ok=True)
        
        # 2. Créer le premier fichier
        chemin_fichier1.touch(exist_ok=True)
        print(f"📁 Dossier prêt : {dossier}")
        print(f"  ├── 📄 {chemin_fichier1.name}")
        
        # 3. Créer les autres fichiers dans ce MÊME dossier
        for fichier_supp in elements[1:]:
            nom_fichier = fichier_supp.strip()
            if nom_fichier:
                chemin_complet = dossier / nom_fichier
                chemin_complet.touch(exist_ok=True)
                print(f"  ├── 📄 {nom_fichier}")

if __name__ == "__main__":
    print("🚀 Début de la génération du devoir...")
    generer_arborescence(devoirs)
    print("\n✅ Terminé avec succès !")