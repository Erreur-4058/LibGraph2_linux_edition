# Plan d'implémentation - Correction Polices et Guide g++

Ce plan vise à rendre le chargement des polices plus robuste et silencieux sur Linux, et à répondre à la demande de l'utilisateur concernant l'utilisation directe de g++.

## Proposed Changes

### [LibGraph2]

#### [MODIFY] [LibGraph2impSFML.cpp](file:///home/jeremi/Downloads/libGraph-master-LibGraph2/LibGraph2/LibGraph2impSFML.cpp)
- Améliorer la fonction `setFont` pour éviter les messages d'erreur de SFML en vérifiant l'existence des fichiers avant de tenter de les charger.
- Utiliser des chemins plus standards pour Linux.

### [Documentation]

#### [MODIFY] [guide_mise_en_route.md](file:///home/jeremi/.gemini/antigravity/brain/5ba806b3-211f-4cad-8c82-6f70d5d6e91b/guide_mise_en_route.md)
- Ajouter une section détaillée sur la compilation en ligne de commande avec `g++`.
- Lister les fichiers nécessaires à copier dans un nouveau projet.

## Verification Plan

### Automated Tests
- Lancer `make` pour reconstruire la bibliothèque.
- Lancer `./test_libgraph2` et vérifier que les messages "Failed to load font" ont disparu de la console (stderr).

### Manual Verification
- Créer un dossier de test `manual_test`.
- Copier `LibGraph2.h` et `libLibGraph2.so` dans ce dossier.
- Créer un fichier `min_main.cpp` simple.
- Compiler avec la commande `g++` recommandée et vérifier que l'exécutable se lance correctement.
