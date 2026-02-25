#include <LibGraph2.h>
#include <Windows.h>
#include <tchar.h>
using namespace LibGraph2;

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                       LPTSTR lpCmdLine, int nCmdShow) {
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  // Récupération de l'objet principal de LibGraph 2
  ILibGraph2 *libgraph = GetLibGraph2();
  // Affiche la fenêtre graphique avec une taille par défaut
  libgraph->show();
  evt e; // Evénement LibGraph 2

  // Boucle principale d'événements
  while (libgraph->waitForEvent(e)) {
    switch (e.type) // En fonction du type d'événement
    {
    case evt_type::evtRefresh: { // Raffraichissement de l'affichage (tout
                                 // redessiner)
      // Utiliser éventuellement les fonctions libgraph->beginPaint() /
      // libgraph->endPaint() pour activer le backbuffer
      libgraph->beginPaint();

      CPoint center1 = CPoint(50, 50);
      CSize size1 = CSize(300, 150);
      CRectangle rect1 = CRectangle(center1, size1);
      ARGB colors = MakeARGB(255, 255, 0, 0);
      libgraph->setPen(colors, 10, pen_DashStyles::Dash);
      libgraph->setSolidBrush(MakeARGB(250, 255, 255, 0));
      libgraph->drawRectangle(rect1);

      ARGB color = MakeARGB(255, 255, 0, 0);
      libgraph->setPen(color, 10, pen_DashStyles::Dash);
      CPoint center(150, 150);
      CSize size(300, 300);
      CRectangle rect(center, size);
      libgraph->setSolidBrush(MakeARGB(150, 173, 216, 230));
      libgraph->drawEllipse(rect);

      // Utiliser ici les fonctions de dessins
      libgraph->endPaint();
      break;
    }
    case evt_type::evtKeyDown: // Enfoncement d'une touche
      switch (e.vkKeyCode)     // En fonction de la touche enfoncée
      {
      case 'A':
        // Touche 'A' enfoncée
        libgraph->hideConsole();
        break;

      case 'C':
        // Touche 'A' enfoncée
        libgraph->showConsole();
        break;
      }

    case evt_type::evtMouseMove: // Déplacement de la souris
      // Position de la souris dans les variables e.x et e.y
      break;
    case evt_type::evtMouseDown: // Enfoncement du bouton de la souris
      // Position de la souris dans les variables e.x et e.y
      std::cout << "Clic souris en position (" << e.x << "," << e.y << ")"
                << std::endl;
      break;
    }
  }

  // Libération de l'objet principal de LibGraph 2
  ReleaseLibGraph2();
  return 0;
}
