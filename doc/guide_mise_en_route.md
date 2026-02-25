# Guide de Mise en Route - LibGraph2 sur Linux 🐧

Ce guide explique comment compiler et utiliser la version Linux de **LibGraph2**, portée de Windows vers Linux en utilisant **SFML** et **tinyfiledialogs**.

---

## 🛠️ Prérequis

Avant de commencer, assurez-vous d'avoir les outils et bibliothèques suivants installés sur votre système (exemple pour Ubuntu/Debian) :

```bash
sudo apt update
sudo apt install build-essential cmake libsfml-dev
```

- **SFML (2.5+)** : Utilisée pour le rendu graphique, la gestion des fenêtres et des événements.
- **CMake (3.10+)** : Système de construction.
- **tinyfiledialogs** : Inclus dans les sources du projet (fichiers `tinyfiledialogs.c/h`).

---

## 🏗️ Compilation de la Bibliothèque

Pour compiler LibGraph2 et générer la bibliothèque partagée (`libLibGraph2.so`) ainsi qu'un programme de test :

1. Ouvrez un terminal dans le dossier `LibGraph2`.
2. Exécutez les commandes suivantes :

```bash
# Générer les fichiers de build
cmake .

# Compiler le projet
make
```

### Fichiers générés :
- `libLibGraph2.so` : La bibliothèque à lier à vos projets.
- `test_libgraph2` : Un programme de démonstration pour vérifier que tout fonctionne.

---

## 🚀 Utilisation dans votre projet

### 1. Structure du code minimal

LibGraph2 sur Linux utilise une API simplifiée via un singleton. Voici un exemple minimal (`main.cpp`) :

```cpp
#include "LibGraph2.h"
#include <iostream>

using namespace LibGraph2;

int main(int argc, char* argv[])
{
    // 1. Récupérer l'instance de LibGraph2
    ILibGraph2* libgraph = GetLibGraph2();

    // 2. Afficher la fenêtre (Taille 800x600)
    libgraph->show(CSize(800, 600));

    evt e;
    // 3. Boucle d'événements
    while (libgraph->waitForEvent(e))
    {
        switch (e.type)
        {
            case evt_type::evtRefresh:
                // Début du dessin
                libgraph->beginPaint();
                
                // Dessiner un rectangle rouge
                libgraph->setPen(MakeARGB(255, 255, 0, 0), 2.0f);
                libgraph->drawRectangle(CRectangle(CPoint(100, 100), CSize(200, 150)));
                
                // Dessiner du texte
                libgraph->drawString("LibGraph2 sur Linux!", CPoint(300, 50));
                
                // Fin du dessin
                libgraph->endPaint();
                break;

            case evt_type::evtMouseMove:
                // Gérer les mouvements de souris si besoin
                break;
        }
    }

    // 4. Libérer les ressources
    ReleaseLibGraph2();

    return 0;
}
```

### 2. Compilation de votre programme (avec g++)

Si vous ne souhaitez pas utiliser CMake pour votre projet, vous pouvez compiler directement avec `g++`. 

#### Fichiers nécessaires :
Copiez les fichiers suivants dans le dossier de votre projet :
- `LibGraph2.h`
- `libLibGraph2.so`

#### Commande de compilation :
```bash
g++ main.cpp -L. -lLibGraph2 -lsfml-graphics -lsfml-window -lsfml-system -o mon_programme
```

#### Exécution :
Si vous obtenez une erreur indiquant que `libLibGraph2.so` est introuvable au lancement, utilisez cette commande pour inclure le dossier courant dans le chemin des bibliothèques :
```bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
./mon_programme
```

---

## 🎨 Fonctionnalités Portées

| Catégorie | État | Détails |
|---------|------|---------|
| **Rendu 2D** | ✅ 100% | Lignes, Rectangles, Ellipses, Tartes (Pies), Bitmaps, Pixels. |
| **Texte** | ✅ 100% | Support des polices système (chargement via SFML). |
| **Événements** | ✅ 100% | Souris (clic, mouvement), Clavier, Redimensionnement, Rafraîchissement. |
| **Dialogues** | ✅ 100% | Boîtes de fichiers, couleur, saisie, messages (via tinyfiledialogs). |
| **Build** | ✅ 100% | Migration complète vers CMake. |

---

## 💡 Conseils de Développement

- **Coordonnées** : LibGraph2 gère automatiquement un système de coordonnées virtuelles. Utilisez `show()` pour définir la taille de travail.
- **Couleurs** : Utilisez toujours `MakeARGB(alpha, rouge, vert, bleu)` pour définir vos couleurs.
- **Nettoyage** : N'oubliez jamais d'appeler `ReleaseLibGraph2()` avant de quitter votre programme.
