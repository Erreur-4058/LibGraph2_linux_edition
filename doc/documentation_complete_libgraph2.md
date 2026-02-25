# Documentation Complète - LibGraph2 Linux 📚

**LibGraph2** est une bibliothèque graphique C++ simplifiée, initialement conçue pour Windows (GDI+) et désormais portée sous **Linux** via **SFML**. Elle est idéale pour l'enseignement de l'informatique et le développement rapide d'applications graphiques 2D.

---

## 📋 Sommaire
1. [Introduction & Philosophie](#introduction--philosophie)
2. [Installation & Compilation](#installation--compilation)
3. [Niveaux d'utilisation (Levels)](#niveaux-dutilisation-levels)
4. [Types de base](#types-de-base)
5. [Gestion des Couleurs (ARGB)](#gestion-des-couleurs-argb)
6. [Référence de l'API (ILibGraph2)](#référence-de-lapi-ilibgraph2)
7. [Gestion des Événements](#gestion-des-événements)
8. [Boîtes de Dialogue (GUI)](#boîtes-de-dialogue-gui)

---

## 🌟 Introduction & Philosophie
LibGraph2 masque la complexité des API graphiques modernes (Win32, SFML, OpenGL) derrière une interface simple. 
- **Facilité** : Fonctions de dessin intuitives (`drawLine`, `drawRectangle`).
- **Événements** : Boucle de messages simplifiée (`waitForEvent`).
- **Virtuel** : Système de coordonnées indépendant de la résolution physique.

---

## 🏗️ Installation & Compilation

### Prérequis
```bash
sudo apt install build-essential cmake libsfml-dev
```

### Compilation
Le projet Linux utilise **CMake**.
```bash
cmake .
make
```
Cela produit `libLibGraph2.so` (bibliothèque partagée) et `test_libgraph2` (démo).

---

## 🎓 Niveaux d'utilisation (Levels)

LibGraph2 s'adapte à votre progression en C++ via la macro `LIBGRAPH2_LEVEL` :

- **Niveau 0 (Novice)** : Appels de fonctions directes, pas de pointeurs.
- **Niveau 1 (Débutant)** : Introduction des références.
- **Niveau 3 (Avancé)** : Utilisation d'objets et de pointeurs intelligents.
- **Niveau 4 (Expert - Défaut)** : Utilisation complète de l'interface `ILibGraph2`.

---

## 📦 Types de base

| Classe | Description | Attributs Clés |
|--------|-------------|----------------|
| `CPoint` | Représente un point (x, y) | `m_fX`, `m_fY` |
| `CSize` | Représente une taille (w, h) | `m_fWidth`, `m_fHeight` |
| `CRectangle` | Union d'un point et d'une taille | `m_ptTopLeft`, `m_szSize` |
| `CString` | Gestion transparente des chaînes (std::string/wstring) | Conversion auto UTF-8/UTF-16 |

---

## 🎨 Gestion des Couleurs (ARGB)

Les couleurs sont stockées dans un entier 32 bits (`ARGB`).

- **Création** : `ARGB couleur = MakeARGB(alpha, rouge, vert, bleu);`
- **Extraction** :
  - `GetA(c)`, `GetR(c)`, `GetG(c)`, `GetB(c)` : retournent un `uint8_t` (0-255).

---

## 🛠️ Référence de l'API (ILibGraph2)

L'instance unique s'obtient via `GetLibGraph2()`.

### Gestion de la fenêtre
- `show(CSize size, bool bFullScreen)` : Crée et affiche la fenêtre.
- `hide()` : Cache la fenêtre.
- `getSize()` : Retourne la taille de la zone de travail.

### Paramètres de dessin
- `setPen(ARGB color, float width, pen_Styles style)` : Définit le crayon (contour).
- `setSolidBrush(ARGB color)` : Définit le pinceau de remplissage uni.
- `setFont(CString fontName, float fontSize, font_Styles style)` : Définit la police.

### Fonctions de dessin
| Fonction | Paramètres |
|----------|------------|
| `drawLine(p1, p2)` | Dessine une ligne entre deux `CPoint`. |
| `drawRectangle(rect)` | Dessine et remplit un rectangle. |
| `drawEllipse(rect)` | Dessine une ellipse inscrite dans le rectangle. |
| `drawPie(rect, start, sweep)` | Dessine une "part de tarte". |
| `drawBitmap(file, pos, scale, angle, flip)` | Affiche une image (PNG, JPG, BMP). |
| `drawString(text, pos)` | Affiche du texte à la position donnée. |

---

## ⌨️ Gestion des Événements

La boucle principale repose sur `waitForEvent(evt& e)`.

### Structure `evt`
- `type` : `evt_type` (voir ci-dessous).
- `x`, `y` : Coordonnées de la souris.
- `vkKeyCode` : Code de la touche pressée (compatible avec les virtual keys).

### Types d'événements (`evt_type`)
- `evtRefresh` : Fenêtre doit être redessinée (appeler `beginPaint`/`endPaint`).
- `evtMouseDown` / `evtMouseUp` / `evtMouseMove` : Actions souris.
- `evtKeyDown` / `evtKeyUp` : Touches clavier.
- `evtResize` : Fenêtre redimensionnée.
- `evtClose` : Fenêtre fermée par l'utilisateur.

---

## 📂 Boîtes de Dialogue (GUI)

Fonctions intégrées pour simplifier l'interaction utilisateur (implémentées via tinyfiledialogs) :

- `guiGetFileName(CString& sFile, bool bOpen)` : Sélecteur de fichier.
- `guiGetColor(ARGB& color)` : Sélecteur de couleur.
- `guiGetValue(CString& strVal, title, label)` : Saisie de texte.
- `guiMessageBox(title, text, btns, icon)` : Message d'information/alerte.

---

## 🚀 Exemple Complet (Linux)

```cpp
#include "LibGraph2.h"
using namespace LibGraph2;

int main() {
    ILibGraph2* lib = GetLibGraph2();
    lib->show(CSize(800, 600));

    evt e;
    while(lib->waitForEvent(e)) {
        if(e.type == evt_type::evtRefresh) {
            lib->beginPaint();
            lib->setPen(MakeARGB(255,0,0,0), 1.0f);
            lib->setSolidBrush(MakeARGB(255, 100, 150, 255));
            lib->drawRectangle(CRectangle(CPoint(100, 100), CSize(200, 100)));
            lib->endPaint();
        }
    }
    ReleaseLibGraph2();
    return 0;
}
```

---

*Documentation générée pour la version Linux (SFML Port).*
