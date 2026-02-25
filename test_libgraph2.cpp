#include <Windows.h>
#include <tchar.h>

// 1. On définit le niveau de difficulté (0 = fonctions simples)
#define LIBGRAPH2_LEVEL 0
#include <LibGraph2.h>

// 2. On utilise l'espace de nom de la bibliothèque
using namespace LibGraph2;

// Point d'entrée principal pour une application Windows
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
    // Variables pour stocker l'état de notre dessin
    int mouseX = 100;
    int mouseY = 100;
    ARGB cercleCouleur = MakeARGB(255, 255, 0, 0); // Rouge par défaut

    // Affiche la fenêtre graphique
    show();

    // Boucle principale d'événements
    while(waitForEvent())
    {
        switch(getLastEventType()) 
        {
            // --- GESTION DE L'AFFICHAGE ---
            case evt_type::evtRefresh:
                beginPaint(); // Active le mode dessin (double buffering)
                
                // On efface l'écran (fond blanc par défaut)
                // On définit le pinceau pour remplir le cercle
                setSolidBrush(cercleCouleur);
                setPen(MakeARGB(255, 0, 0, 0), 2.0f); // Contour noir, épaisseur 2
                
                // Dessine un cercle de 50 pixels de rayon autour de la souris
                drawEllipse(mouseX - 50, mouseY - 50, 100, 100);
                
                endPaint(); // Affiche le résultat
                break;

            // --- GESTION DU CLAVIER ---
            case evt_type::evtKeyDown:
                if(getLastEventKeyCode() == 'A') // Si on appuie sur 'A'
                {
                    // On change la couleur en Vert
                    cercleCouleur = MakeARGB(255, 0, 255, 0);
                    askForRefresh(); // Demande de redessiner la fenêtre
                }
                break;

            // --- GESTION DE LA SOURIS ---
            case evt_type::evtMouseMove:
                mouseX = getLastEventMouseX();
                mouseY = getLastEventMouseY();
                askForRefresh(); // Redessine pour que le cercle suive la souris
                break;

            // --- FERMETURE ---
            case evt_type::evtClose:
                // La boucle s'arrêtera d'elle-même
                break;
        }
    }

    // Libère la mémoire proprement
    ReleaseLibGraph2();
    return 0;
}