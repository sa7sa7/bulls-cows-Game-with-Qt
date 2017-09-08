#ifndef MENU_H
#define MENU_H

#include <QLabel>
#include <QGridLayout>
#include <QPushButton>

class un_joueur;
class deux_joueurs;
class Sous_fenetre;
class aide;
class charger;
class score;
class menu :public QWidget
{
    Q_OBJECT
public:
    menu(QString erreur, int grandeur);
    ~menu();
    void executer();
    void effacer();
    void vs_boot(QString file_name);
    void sauvegarder(QString file_name);
    void rejouer_vs_boot();
    void rejouer_joueur_vs_joueur();
    void modifier_pause();

public slots:
    void reafficher();
    void vs_boot();
    void rejouer();
    void joueur_vs_joueur();
    void afficher_aide();
    void charger_une_partie();
    void afficher_score();

private:
    QPushButton* boot;
    QPushButton* deux_joueur;
    QPushButton* quitter;
    QPushButton* Aide;
    QPushButton* Charge;
    QPushButton* Score;
    QGridLayout* layout_principale;
    QLabel* titre;
    QLabel* owners;
    QLabel** vide;
    aide* help;
    Sous_fenetre *sous_fenetre;
    deux_joueurs *joueurs;
    un_joueur *jeu;
    charger *charge;
    score *statistique;
    bool reaffichage;
};

#endif // MENU_H
