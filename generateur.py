import os
from pathlib import Path

# Colle ici tes 12 lignes d'exercices
# Format attendu : "chemin/vers/dossier/fichier1, fichier2, fichier3"
devoirs = [
    "chapitre-03/exo1-la_fenetre_nue/c3-exo1_main.cpp, c3-exo1_reponse.md",
    "chapitre-03/exo2-les_sept_droits/c3-exo2_main.cpp, c3-exo2_reponse.md",
    "chapitre-03/exo12-l_inventaire_des_ecrans/c3-exo12_main.cpp, c3-exo12_reponse.md",
    "chapitre-03/exo11-deux_fenetres/c3-exo11_main.cpp, c3-exo11_reponse.md",
    "chapitre-03/exo10-la_fenetre_sans_bordure/c3-exo10_main.cpp, c3-exo10_reponse.md",
    "chapitre-03/exo9-les_quatre_dialogues/c3-exo9_main.cpp, c3-exo9_reponse.md",
    "chapitre-03/exo8-le_presse_papiers_dans_les_deux_sens/c3-exo8_main.cpp, c3-exo8_reponse.md",
    "chapitre-03/exo7-le_glisser_qui_sort/c3-exo7_main.cpp, c3-exo7_reponse.md",
    "chapitre-03/exo6-les_sept_curseurs/c3-exo6_main.cpp, c3-exo6_reponse.md",
    "chapitre-03/exo5-le_titre_qui_informe/c3-exo5_main.cpp, c3-exo5_reponse.md",
    "chapitre-03/exo4-le_facteur_d_echelle/c3-exo4_main.cpp, c3-exo4_reponse.md",
    "chapitre-03/exo3-les_bornes/c3-exo3_main.cpp, c3-exo3_reponse.md"
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