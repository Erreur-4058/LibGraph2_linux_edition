# Guide d'utilisation - LibGraph2 sur Windows 11 🪟

LibGraph2 est parfaitement compatible avec Windows 11. Ce guide vous explique comment l'installer et l'utiliser avec **Visual Studio 2022**.

---

## 🛠️ Option 1 : Utilisation Classique (Originale)
C'est la méthode recommandée si vous développez uniquement pour Windows en utilisant l'API native (GDI+).

### 1. Prérequis
- **Visual Studio 2022** avec le module "Développement Desktop en C++" installé.

### 2. Configuration du Projet
1. Créez un nouveau projet **C++ / Projet vide**.
2. Copiez le fichier `LibGraph2.h` dans votre dossier de projet.
3. Ajoutez vos fichiers sources (`main.cpp`).
4. **Liaison de la bibliothèque** :
   - Si vous avez déjà une version compilée (`LibGraph2.lib` et `LibGraph2.dll`), ajoutez le `.lib` dans les dépendances de l'éditeur de liens.
   - Assurez-vous que la DLL est dans le même dossier que votre `.exe` final.

---

## 🏗️ Option 2 : Utilisation Multiplateforme (SFML)
Si vous avez utilisé la version portée sur Linux et que vous souhaitez garder le **même code** sur Windows.

### 1. Prérequis
- **Visual Studio 2022** ou **CMake** pour Windows.
- **SFML pour Windows** (téléchargeable sur [sfml-dev.org](https://www.sfml-dev.org/download/sfml/2.6.1/)).

### 2. Compilation avec CMake
Vous pouvez utiliser le même `CMakeLists.txt` que celui créé pour Linux :
1. Installez SFML dans un dossier (ex: `C:/SFML`).
2. Ouvrez un terminal (PowerShell) dans le dossier LibGraph2.
3. Lancez la configuration en spécifiant le chemin de SFML :
```powershell
cmake -DSFML_DIR="C:/SFML/lib/cmake/SFML" .
cmake --build .
```

---

## 🚀 Exemple de Code (main.cpp)

Sur Windows 11, le point d'entrée standard est généralement `main`. Si vous utilisez la version SFML, c'est identique à Linux.

```cpp
#include "LibGraph2.h"
#pragma comment(lib, "LibGraph2.lib") // Uniquement pour Visual Studio classique

using namespace LibGraph2;

int main(int argc, char* argv[])
{
    ILibGraph2* libgraph = GetLibGraph2();
    libgraph->show(CSize(800, 600));

    evt e;
    while (libgraph->waitForEvent(e))
    {
        if (e.type == evt_type::evtRefresh)
        {
            libgraph->beginPaint();
            libgraph->setPen(MakeARGB(255, 0, 0, 0), 2.0f);
            libgraph->drawRectangle(CRectangle(CPoint(50, 50), CSize(100, 100)));
            libgraph->endPaint();
        }
    }

    ReleaseLibGraph2();
    return 0;
}
```

---

## 💡 Différences Clés sur Windows

- **Chemin des polices** : Sur Windows, les polices sont dans `C:\Windows\Fonts`. La version SFML de LibGraph2 essaiera automatiquement de charger une police standard si elle ne trouve pas celle spécifiée.
- **Console** : Sous Windows, `showConsole()` peut ouvrir une fenêtre de terminal séparée si vous compilez en mode "Windows App". En mode "Console App", la sortie s'affiche dans le terminal actuel.
- **DLLs** : N'oubliez JAMAIS de copier les DLLs nécessaires (`LibGraph2.dll`, et si vous utilisez SFML : `sfml-graphics-2.dll`, etc.) à côté de votre fichier exécutable.

---

*Note : La version portée (SFML) permet de passer de Windows à Linux sans changer une seule ligne de votre code de dessin !*
