#include "graph.h"

using namespace std;

/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les éléments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de réglage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
    m_slider_value.set_dim(20,80);
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_x(grman::GravityX::Right);
    }

    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_box_label_idx.set_dim(20,12);
    m_box_label_idx.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( std::to_string(idx) );
}


/// Gestion du Vertex avant l'appel à l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_value vers le slider associé
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donnée m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Vertex après l'appel à l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_value locale
    m_value = m_interface->m_slider_value.get_value();
}



/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les éléments de l'interface
EdgeInterface::EdgeInterface(Vertex& from, Vertex& to)
{
    // Le WidgetEdge de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating EdgeInterface between vertices having no interface" << std::endl;
        throw "Bad EdgeInterface instanciation";
    }
    m_top_edge.attach_from(from.m_interface->m_top_box);
    m_top_edge.attach_to(to.m_interface->m_top_box);
    m_top_edge.reset_arrow_with_bullet();

    // Une boite pour englober les widgets de réglage associés
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de réglage de valeur
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}


/// Gestion du Edge avant l'appel à l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_weight vers le slider associé
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donnée m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Edge après l'appel à l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();
}



/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(800,600);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(100, 590);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(690,590);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);

    ///Parametrisation du ButtonQ pour quitter
    m_top_box.add_child(m_buttonQ);
    m_buttonQ.set_frame(20, 560, 70, 30);
    m_buttonQ.set_bg_color(BLANCJAUNE);

    m_buttonQ.add_child(m_butQ);
    m_butQ.set_message(" Quitter ");

    ///Parametrisation du buttonS pour sauvegarder
    m_top_box.add_child(m_buttonS);
    m_buttonS.set_frame(20, 520, 70, 30);
    m_buttonS.set_bg_color(BLANCJAUNE);

    m_buttonS.add_child(m_butS);
    m_butS.set_message(" Sauver ");

    ///Parametrisation du buttonA pour Ajouter
    m_top_box.add_child(m_buttonA);
    m_buttonA.set_frame(20, 480, 70, 30);
    m_buttonA.set_bg_color(BLANCJAUNE);

    m_buttonA.add_child(m_butA);
    m_butA.set_message(" Ajouter ");

    ///Parametrisation du Button R pour retour
    m_top_box.add_child(m_buttonR);
    m_buttonR.set_frame(20, 50, 70, 30);
    m_buttonR.set_bg_color(BLANCJAUNE);

    m_buttonR.add_child(m_butR);
    m_butR.set_message(" Menu ");



}


/*

/// Méthode spéciale qui construit un graphe arbitraire (démo)
/// Cette méthode est à enlever et remplacer par un système
/// de chargement de fichiers par exemple.
/// Bien sûr on ne veut pas que vos graphes soient construits
/// "à la main" dans le code comme ça.
void Graph::make_example()
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    /// Les sommets doivent être définis avant les arcs
    // Ajouter le sommet d'indice 0 de valeur 30 en x=200 et y=100 avec l'image clown1.jpg etc...
    add_interfaced_vertex(0, 30.0, 200, 100, "clown1.jpg");
    add_interfaced_vertex(1, 60.0, 400, 100, "clown2.jpg");
    add_interfaced_vertex(2,  50.0, 200, 300, "clown3.jpg");
    add_interfaced_vertex(3,  0.0, 400, 300, "clown4.jpg");
    add_interfaced_vertex(4,  100.0, 600, 300, "clown5.jpg");
    add_interfaced_vertex(5,  0.0, 100, 500, "bad_clowns_xx3xx.jpg", 0);
    add_interfaced_vertex(6,  0.0, 300, 500, "bad_clowns_xx3xx.jpg", 1);
    add_interfaced_vertex(7,  0.0, 500, 500, "bad_clowns_xx3xx.jpg", 2);

    /// Les arcs doivent être définis entre des sommets qui existent !
    // AJouter l'arc d'indice 0, allant du sommet 1 au sommet 2 de poids 50 etc...
    add_interfaced_edge(0, 1, 2, 50.0);
    add_interfaced_edge(1, 0, 1, 50.0);
    add_interfaced_edge(2, 1, 3, 75.0);
    add_interfaced_edge(3, 4, 1, 25.0);
    add_interfaced_edge(4, 6, 3, 25.0);
    add_interfaced_edge(5, 7, 3, 25.0);
    add_interfaced_edge(6, 3, 4, 0.0);
    add_interfaced_edge(7, 2, 0, 100.0);
    add_interfaced_edge(8, 5, 2, 20.0);
    add_interfaced_edge(9, 3, 7, 80.0);
}

*/


/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update()
{
    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();

    if (m_interface -> m_buttonQ.clicked())
    {
        exit(1);
    }
}

int Graph::updateb()
{
    update();
    int x;

    if (m_interface -> m_buttonA.clicked())
    {
        x=1;
    }

    if (m_interface -> m_buttonS.clicked())
    {
        x=2;
    }

    if (m_interface -> m_buttonR.clicked())
    {
        x=3;
    }

    return x;
}

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Création d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Vertex(value, vi);
}

/// Aide à l'ajout d'arcs interfacés
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight)
{
    if ( m_edges.find(idx)!=m_edges.end() )
    {
        std::cerr << "Error adding edge at idx=" << idx << " already used..." << std::endl;
        throw "Error adding edge";
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        std::cerr << "Error adding edge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding edge";
    }

    EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
    m_interface->m_main_box.add_child(ei->m_top_edge);
    m_edges[idx] = Edge(weight, ei);

    m_edges[idx].m_from = id_vert1;
    m_edges[idx].m_to = id_vert2;

    m_vertices[id_vert1].m_out.push_back(idx);
    m_vertices[id_vert2].m_in.push_back(idx);
}

void Graph::Lecture(std::string nom_fichiers, std::string nom_fichiera)
{
    ///Sommet
    ifstream fichiers(nom_fichiers, ios::in); ///lecture seule

    m_interface = std::make_shared<GraphInterface>(50, 0, 1000, 400);
    std::string nom; // nom de l'image
    int indice, x, y, poids, ordre1;
    int ordre2, id, sommet1, sommet2, pds;

    if(fichiers) // Si ouverture du fichier est un succes
    {
        fichiers >> ordre1; // on recupere le nombre de sommets

        for(int i = 0; i < ordre1; i++)
        {
            fichiers >> indice >> poids >> x >> y >> nom;
            add_interfaced_vertex(indice,poids,x,y,nom); // affichage sommets
        }
        fichiers.close();
    }
    else
    {
        cout <<"Erreur lors de l'ouverture du fichier Sommet" << endl;
    }

    ///Aretes

    ifstream fichiera(nom_fichiera, ios::in); ///lecture seule

    if (fichiera)
    {
        fichiera >> ordre2; //Récupère le nombre d'aretes
        for (int j  = 0; j < ordre2; j++)
        {
            fichiera >> id >> sommet1 >> sommet2 >> pds;
            add_interfaced_edge(id, sommet1, sommet2, pds);
        }
        fichiera.close();
    }
    else
    {
        cout << "Erreur lors de l'ouverture du fichier Arete" << endl;
    }
}

void Graph::sauvegarder(std::string nom_fichierS, std::string nom_fichierA)
{
    int nbsommet,nbarete;
    std::string nom_fichier1;
    std::string nom_fichier2;

    nom_fichier1 = "sommets.txt";

    ///sommet

    std::ofstream fichier(nom_fichier1.c_str(), ios::out | ios::trunc);  // Ecriture

    if(fichier)  // Succes ouverture
    {
        nbsommet = m_vertices.size();
        fichier	<< nbsommet << endl;

        for(auto &el : m_vertices)
        {
            fichier<<el.first<<endl;
            fichier<<el.second.m_value<<endl;
            fichier<<el.second.m_interface->m_top_box.get_posx()<<endl;
            fichier<<el.second.m_interface->m_top_box.get_posy()<<endl;
            fichier<<el.second.m_interface->m_img.getname()<<endl;
        }
        fichier.close();
    }
    else
    {
        cout<<"Erreur lors de l'ouverture du fichier"<<endl;
    }

    /// Aretes

    nom_fichier2 = "aretes.txt";
    ofstream fichier2(nom_fichier2.c_str(), ios::out | ios::trunc);  // Ecriture

    if(fichier2)  // Si succes
    {
        nbarete = m_edges.size();
        fichier2<< nbarete << endl;

        for(auto &el : m_edges)
        {
            fichier2<<el.first<<endl;
            fichier2<<el.second.m_from<<endl;
            fichier2<<el.second.m_to<<endl;
            fichier2<<el.second.m_weight<<endl;

        }

        fichier2.close();
    }
    else
    {
        cout<<"Erreur lors de l'ouverture du fichier"<<endl;
    }
    cout << "SAUVEGARDE REUSSIE" << endl;
}

            ///Methode pour ajouter sommets et arcs
void Graph::AjouterSommet()
{
    int indice, x, y, taille;  /// Variables sommets
    std::string namepic;
    int poids; /// variables pour indice
    int sommet1, sommet2, indice2;
    bool ajout = true;
    std::string saisit;


    indice = m_vertices.size(); /// on recupere l'ordre

    std::cout << "      Ajout d'un sommet" << endl;

    std::cout << " Quel est la taille du sommet? (0-100) : ";
    std:: cin>> taille;
    std::cout << "La taille du sommet est: " << taille;

// Par defaut, on met le nouveau sommet a un endroit fixe
    x = 100;
    y = 100;

    std::cout << endl << "Quelle image voulez-vous affecter au sommet? (sans le.jpg) : ";
    std::cin >> namepic;

    std::string namepicjpg;
    namepicjpg = namepic +".jpg";

    add_interfaced_vertex(indice,taille,x,y,namepicjpg);
    std::cout << "Creation du sommet avec succes" << endl ; // si l'image n'existe pas, ca créer quand meme le sommet sans image mais on a son indice en bas a droite.
    std::cout << "Le sommet qui vient d'etre creer est d'indice : " << indice << endl;
// m_vertices.insert(add_interfaced_vertex(indice,taille,x,y,namepic));  /// ??? bail sombre.


    while(ajout == true)
    {
        std::cout << "      Voulez vous ajouter des aretes? (oui||non): " << endl;
        std::cin >> saisit;
        if( saisit == "oui")
        {
            std::cout << "Saisir sommet 1 : ";
            std::cin >> sommet1;
            std::cout << "Saisir sommet 2 : ";
            std::cin >> sommet2;

            while (sommet1 == sommet2)
            {
                std::cout << " Saisit eronnee, impossible de creer une arete si le sommet1=sommet2" << endl;
            std::cout << "Resaisir sommet 1 : ";
            std::cin >> sommet1;
            std::cout << "Resaisir sommet 2 : ";
            std::cin >> sommet2;
            }

            while ((sommet1 >= m_vertices.size()) || (sommet2 >= m_vertices.size()))
            {
            std::cout << " Saisit eronnee, un des deux sommets n'existe pas" << endl;
            std::cout << "Resaisir sommet 1 : ";
            std::cin >> sommet1;
            std::cout << "Resaisir sommet 2 : ";
            std::cin >> sommet2;
            }

            std::cout << "sommet" << sommet1 << "---" << "sommet" << sommet2 << endl;


            std:: cout << "Quel est le poids de l'arete ? : ";
            std:: cin >> poids;
            std::cout << "Le poid de l'arete est : " << poids << endl;

            indice2 = m_edges.size();

            add_interfaced_edge(indice2, sommet1, sommet2, poids);
            std::cout << "Creation de l'arete avec succes" << endl;
// m_edges.insert(add_interfaced_edge(indice2, indice, sommet2, poids)); /// ??? bail sombre numero 2
        }
        else if (saisit == "non")
        {
            ajout = false;
        }
    }
}
//void Graphe::Suppression();

