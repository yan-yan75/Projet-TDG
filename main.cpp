#include "grman/grman.h"
#include <iostream>

#include "graph.h"
#include "grman/widget.h"

void fonction(int x, int p, Graph g, int M, BITMAP *img1, BITMAP *buffer1);

void AffichageMenu(BITMAP *img1, BITMAP *buffer1);

int main()
{
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Graph g;
    //g.make_example();

    ///Initialisation des variables pour le menu Allegro
    BITMAP *img1;
    BITMAP *buffer1;

    int x;
    int M=0;
    bool y=1;

    img1 = load_bitmap("ChoixG.bmp", NULL);
    if (!img1)
    {
        allegro_message("Impossible de charger l'img1.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    buffer1=create_bitmap(SCREEN_W,SCREEN_H);


    AffichageMenu(img1, buffer1);

    while (y==1)
    {
        if ( (mouse_b & 1) && (mouse_x >= 40) && (mouse_x <= 235) && (mouse_y >= 231) && (mouse_y <= 375))
        {
            x=1;
            clear_bitmap(buffer1);
            y=0;
        }
        if ( (mouse_b & 1) && (mouse_x >= 313) && (mouse_x <= 512) && (mouse_y >= 231) && (mouse_y <= 375))
        {
            x=2;
            y=0;
        }
        if ( (mouse_b & 1) && (mouse_x >= 574) && (mouse_x <= 777) && (mouse_y >= 231) && (mouse_y <= 375))
        {
            x=3;
            y=0;
        }
        if ( (mouse_b & 1) && (mouse_x >=640 && mouse_x <= 786 && mouse_y >=545 && mouse_y <= 585))
        {
            x=4;
            y=0;
        }
        switch(x)
        {
        case 0 :
            break;
        case 1 :
            g.Lecture("sommets.txt", "aretes.txt");
        case 2 :

            g.Lecture("sommets2.txt", "aretes2.txt");
        case 3 :
            break;
        case 4 :
            std::cout<<"Application quitte";
            exit(1);
            break;
        }
    }
    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC] )
    {
        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets

        int p = g.updateb();

        ///Appel de la fonction
        fonction(x, p, g, M, img1, buffer1);

        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();
    }
    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


void fonction(int x, int p, Graph g, int M, BITMAP *img1, BITMAP *buffer1)
{
    if (x==1)
        {
            if(p==1)
            {
                g.AjouterSommet();
            }
            if(p==2)
            {
                g.sauvegarder("sommets.txt", "aretes.txt");
            }
            if (p==3)
            {
            std::cout<<"Afficher menu";
            }
            ///Affichage du 1er graphe
            g.update();
        }

        if (x==2)
        {
            if(p==1)
            {
                //g.AjouterSommet();
            }
            if(p==2)
            {
                //g.sauvegarder("sommets2.txt", "aretes2.txt");
            }
            if (p==3)
            {
                //AffichageMenu(img1, buffer1);
            }
            ///Affichage du 2eme Graphe
            g.update();
        }
        if (x==3)
        {
            if(p==1)
            {
                //g.AjouterSommet();
            }
            if(p==2)
            {
                //g.sauvegarder("sommet.txt", "arete.txt");
            }
            if (p==3)
            {
                //M=1;
            }
            ///Affichage du 3emeGraphe
            g.update();
        }
        ///quitte l'application quand on est sur le menu
        if (x==4)
        {
            exit(1);
        }
}

void AffichageMenu(BITMAP *img1, BITMAP *buffer1)
{
            ///Affichage du Menu
        blit(img1, buffer1, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        blit(buffer1, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}
