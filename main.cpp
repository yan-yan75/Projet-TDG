#include "grman/grman.h"
#include <iostream>

#include "graph.h"

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


    img1 = load_bitmap("ChoixG.bmp", NULL);
    if (!img1)
    {
        allegro_message("Impossible de charger l'img1.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    buffer1=create_bitmap(SCREEN_W,SCREEN_H);

    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC] )
    {
        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
        g.update();

        ///Affichage du Menu
         blit(buffer1, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
         blit(img1, buffer1, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        if (mouse_b & 1)
        {
            if ( (mouse_x >= 40) && (mouse_x <= 235) && (mouse_y >= 231) && (mouse_y <= 375) )
                {
                    clear_bitmap(img1);
                    std::cout<<"Affichage Graphe 1" << std::endl;
                    ///Affichage du 1er graphe

                    g.Lecture("sommets.txt", "aretes.txt");


                }
            if ( (mouse_x >= 313) && (mouse_x <= 512) && (mouse_y >= 231) && (mouse_y <= 375) )
                {
                    clear_bitmap(img1);

                    std::cout<<"Affichage Graphe 2";
                    ///Affichage du 2eme Graphe

                }
            if ( (mouse_x >= 574) && (mouse_x <= 777) && (mouse_y >= 231) && (mouse_y <= 375) )
                {
                    clear_bitmap(img1);
                    std::cout<<"Affichage Graphe 3";
                    ///Affichage du 3emeGraphe

                }
                ///quitte l'application quand on est sur le menu
            if ( (mouse_x >=640 && mouse_x <= 786 && mouse_y >=545 && mouse_y <= 585))
        {
            exit(1);
        }
        }

        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();
    }

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


