import os
from pathlib import Path

# Colle ici tes 12 lignes d'exercices
# Format attendu : "chemin/vers/dossier/fichier1, fichier2, fichier3"
devoirs = [
    "chapitre-06/exo10-le_joueur_fantome/fantome.cpp, fantome.txt",
    "chapitre-06/exo9-l_aller_retour/allerretour.cpp, mesures-rtt.txt, rtt.txtp",
    "chapitre-06/exo8-le_message_qui_compte_ses_octets/octets.cpp, tailles.txt",
    "chapitre-06/exo7-la_decouverte/decouverte.cpp, serveurs.txt",
    "chapitre-06/exo5-le_futur_qui_ne_bloque_pas/futur.cpp, cadence.txt",
    "chapitre-06/exo6-deux_machines_se_parlent/parle.cpp, echange.txt",
    "chapitre-06/exo4-l_etreinte_fatale/etreinte.cpp, etreinte.txt",
    "chapitre-06/exo3-la_course_corrigee/corrige.cpp, prix.txt",
    "chapitre-06/exo2-la_course_provoquee/course.cpp, totaux.txt",
    "chapitre-06/exo1-la_reserve/reserve.cpp, reserve.txt"
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