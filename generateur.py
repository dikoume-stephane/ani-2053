import os
from pathlib import Path

# Colle ici tes 12 lignes d'exercices
# Format attendu : "chemin/vers/dossier/fichier1, fichier2, fichier3"
devoirs = [
    "chapitre-05/exo10-l_erreur_claire/lecteur.cpp, resultats.txt, reponse.txt",
    "chapitre-05/exo9-conteneur_et_codec/main.cpp",
    "chapitre-05/exo8-un_son_vingt_voix/main.cpp",
    "chapitre-05/exo7-le_calcul_puis_le_fichier/main.cpp",
    "chapitre-05/exo6-la_ligne_de_base/main.cpp",
    "chapitre-05/exo5-trois_polices_un_atlas/main.cpp",
    "chapitre-05/exo4-l_atlas_vu/atlas.cpp, compte.txt, reponse.txt",
    "chapitre-05/exo3-les_six_formats/main.cpp",
    "chapitre-05/exo2-l_extension_qui_ment/main.cpp",
    "chapitre-05/exo1-le_calcul_puis_la_mesure/mesure.cpp, mesures.txt, reponse.txt"
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