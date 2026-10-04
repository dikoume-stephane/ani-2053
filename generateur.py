import os
from pathlib import Path

# Colle ici tes 12 lignes d'exercices
# Format attendu : "chemin/vers/dossier/fichier1, fichier2, fichier3"
devoirs = [
    "chapitre-04/exo10-l_interface_qui_ne_defile_pas/interface.cpp, journal.txt, reponse.txt",
    "chapitre-04/exo9-les_six_politiques/main.cpp",
    "chapitre-04/exo8-l_objet_dans_l_objet/main.cpp",
    "chapitre-04/exo7-la_planche_de_sprites/main.cpp",
    "chapitre-04/exo6-evenement_ou_interrogation/main.cpp",
    "chapitre-04/exo5-le_cercle_qui_n_en_est_pas_un/main.cpp",
    "chapitre-04/exo4-la_coquille_et_la_main/coquille.cpp, alamain.cpp, comparaison.txt, reponse.txt",
    "chapitre-04/exo3-le_pivot/main.cpp",
    "chapitre-04/exo2-ce_que_forment_les_sommets/main.cpp",
    "chapitre-04/exo1-la_fenetre_nue/fenetre.cpp, mesure.txt, reponse.txt"
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