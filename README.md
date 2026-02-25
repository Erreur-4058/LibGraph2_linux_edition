# LibGraph2 - Version Linux (SFML) 🚀

**LibGraph2** est une bibliothèque graphique simplifiée conçue pour l'apprentissage de la programmation C++. Initialement développée pour Windows, cette version a été portée sous **Linux** en utilisant le moteur **SFML**.

Elle permet aux étudiants de passer de Windows à Linux sans modifier une seule ligne de leur code source original.

---

## ✨ Caractéristiques
- **Compatibilité Totale** : Supporte `WinMain`, `Windows.h` et les types Windows (`HINSTANCE`, `ARGB`, etc.) via une couche de compatibilité intégrée.
- **Moteur SFML** : Rendu fluide et performant sur Linux.
- **Niveau 0 à 4** : Support complet des différents niveaux d'expérience LibGraph2.
- **Mapping ASCII** : Les codes de touches clavier (`e.vkKeyCode`) sont synchronisés avec les codes ASCII standards.

---

## 🛠️ Installation des dépendances

Avant de compiler, vous devez installer la bibliothèque **SFML** sur votre système Linux.

Sur **Ubuntu / Debian / Mint** :
```bash
sudo apt update
sudo apt install libsfml-dev
```

---

## 🏗️ Compilation du Projet

### Avec le fichier Makefile (recommandé)
Pour compiler la bibliothèque et l'exemple de test fourni :
```bash
make clean
make
```

### Avec g++ directement
Si vous voulez compiler votre propre fichier (ex: `mon_code.cpp`) :
```bash
g++ mon_code.cpp -I. -L. -lLibGraph2 -lsfml-graphics -lsfml-window -lsfml-system -o mon_programme
```

---

## 🏃 Exécution du programme

Sur Linux, vous devez indiquer au système où se trouve le fichier `.so` de la bibliothèque au lancement :

```bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
./test_libgraph2
```

---

## 💻 Exemple de Code Portable
Voici un exemple de code qui tourne à l'identique sur Windows et sur cette version Linux :

```cpp
#include <Windows.h>
#include <tchar.h>
#include <LibGraph2.h>
using namespace LibGraph2;

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
    show();
    while(waitForEvent()) {
        if(getLastEventType() == evt_type::evtRefresh) {
            beginPaint();
            setSolidBrush(MakeARGB(255, 255, 0, 0));
            drawEllipse(100, 100, 200, 200);
            endPaint();
        }
    }
    ReleaseLibGraph2();
    return 0;
}
```

---

## 📝 Structure du projet
- `LibGraph2.h` : En-tête principal corrigé pour Linux.
- `Windows.h` & `tchar.h` : Couche de compatibilité Windows pour Linux.
- `LibGraph2impSFML.cpp` : Implémentation du moteur de rendu Linux.
- `libLibGraph2.so` : La bibliothèque compilée pour Linux.

---

## ⚖️ Licence
Ce projet est distribué sous licence **GPLv3**.
Copyright © 2010-2024 Benjamin ALBOUY-KISSI.
Projet original disponible sur le [GitLab de l'IUT](https://gitlab-lepuy.iut.uca.fr/bealbouy/libGraph).
Portage Linux réalisé par **Jeremi Roux** (avec l'assistance d'Antigravity).
