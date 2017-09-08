#include "menu.h"
#include "un_joueur.h"
#include "deux_joueurs.h"
#include "sous_fenetre.h"
#include "aide.h"
#include "charger.h"
#include "score.h"

menu::menu(QString erreur,int grandeur):QWidget()
{
    layout_principale = new QGridLayout(this);
    titre = new QLabel("JEU VACHES TAUREAUX",this);
    titre->setStyleSheet("QLabel{ color: rgb(219, 0, 115);font-size : 100px; font-family : Bleeding Cowboys}");
    titre->setAlignment(Qt::AlignCenter);

    boot = new QPushButton ("Contre un &Robot",this);
    boot->setStyleSheet("QPushButton{color: rgb(168, 216, 24); font-size : 35px; font-family : Oduda}");
    boot->setFixedSize(270,50);
    boot->setToolTip("Jouer contre un rebot");
    boot->setToolTipDuration(2000);
    deux_joueur = new QPushButton ("2 &Joueurs",this);
    deux_joueur->setFixedSize(270,50);
    deux_joueur->setStyleSheet("QPushButton{color: rgb(0, 162, 232); font-size : 35px; font-family : Oduda}");
    deux_joueur->setToolTip("Jouer contre un ami");
    deux_joueur->setToolTipDuration(2000);
    Charge = new QPushButton ("&Charger",this);
    Charge->setFixedSize(270,50);
    Charge->setStyleSheet("QPushButton{color: rgb(221, 121, 62); font-size : 35px; font-family : Oduda}");
    Charge->setToolTip("Charger une partie que vous avez sauvegarder");
    Charge->setToolTipDuration(2000);
    Aide = new QPushButton ("&Aide",this);
    Aide->setFixedSize(270,50);
    Aide->setStyleSheet("QPushButton{color: rgb(221, 121, 62); font-size : 35px; font-family : Oduda}");
    Aide->setToolTip("Savoir plus");
    Aide->setToolTipDuration(2000);
    Score = new QPushButton ("&Score",this);
    Score->setFixedSize(270,50);
    Score->setStyleSheet("QPushButton{color: rgb(221, 121, 62); font-size : 35px; font-family : Oduda}");
    Score->setToolTip("Voir vos meilleurs score");
    Score->setToolTipDuration(2000);
    quitter = new QPushButton ("&Quitter",this);
    quitter->setFixedSize(270,50);
    quitter->setStyleSheet("QPushButton{color: rgb(221, 121, 62); font-size : 35px; font-family : Oduda}");
    quitter->setToolTip("Quitter le jeu");
    quitter->setToolTipDuration(2000);

    vide= new QLabel* [2];
    vide[0] = new QLabel ("",this);
    vide[0]->setFixedSize(300,300);
    vide[1] = new QLabel ("",this);
    vide[1]->setFixedSize(300,300);
    owners = new QLabel("BY Nadhmi AND Salah",this);
    owners->setStyleSheet("QLabel{color: rgb(111, 0, 255); font-size : 22px; font-family : True Lies}");

    setMinimumSize(1300,800);
    setWindowTitle("Jeu vache taureau");

    sous_fenetre=new Sous_fenetre(this);
    help= new aide(this,layout_principale);
    jeu = new un_joueur(this,layout_principale,sous_fenetre);
    joueurs = new deux_joueurs(this,layout_principale,sous_fenetre);
    charge= new charger(this,layout_principale,sous_fenetre);
    statistique= new score(this,layout_principale,sous_fenetre);

    reaffichage=false;

    QObject::connect(boot, SIGNAL(clicked()), this, SLOT(vs_boot()));
    QObject::connect(deux_joueur, SIGNAL(clicked()), this, SLOT(joueur_vs_joueur()));
    QObject::connect(Charge, SIGNAL(clicked()), this, SLOT(charger_une_partie()));
    QObject::connect(Score, SIGNAL(clicked()), this, SLOT(afficher_score()));
    QObject::connect(Aide, SIGNAL(clicked()), this, SLOT(afficher_aide()));
    QObject::connect(quitter, SIGNAL(clicked()), this, SLOT(close()));
    executer();
    show();
    if(grandeur!=0)
    {
        sous_fenetre->afficher1(erreur,grandeur);
        sous_fenetre->show();
    }
}

menu::~menu()
{
   delete sous_fenetre;
   delete help;
   delete jeu;
   delete joueurs;
   delete charge;
   delete statistique;
   delete vide;
}

void menu::effacer()
{
    layout_principale->removeWidget(titre);
    titre->setVisible(false);
    layout_principale->removeWidget(vide[0]);
    vide[0]->setVisible(false);
    layout_principale->removeWidget(boot);
    boot->setVisible(false);
    layout_principale->removeWidget(deux_joueur);
    deux_joueur->setVisible(false);
    layout_principale->removeWidget(Charge);
    Charge->setVisible(false);
    layout_principale->removeWidget(Aide);
    Aide->setVisible(false);
    layout_principale->removeWidget(Score);
    Score->setVisible(false);
    layout_principale->removeWidget(quitter);
    quitter->setVisible(false);
    layout_principale->removeWidget(vide[1]);
    vide[1]->setVisible(false);
    layout_principale->removeWidget(owners);
    owners->setVisible(false);
}

void menu::executer()
{
    titre->setVisible(true);
    vide[0]->setVisible(true);  
    boot->setVisible(true);
    deux_joueur->setVisible(true);
    Charge->setVisible(true);
    Score->setVisible(true);
    Aide->setVisible(true);
    quitter->setVisible(true);
    vide[1]->setVisible(true);
    owners->setVisible(true);


    layout_principale->addWidget(titre,0,0);
    layout_principale->addWidget(vide[0],1,0);
    layout_principale->addWidget(boot,2,0);
    layout_principale->addWidget(deux_joueur,3,0);
    layout_principale->addWidget(Charge,4,0);
    layout_principale->addWidget(Score,5,0);
    layout_principale->addWidget(Aide,6,0);
    layout_principale->addWidget(quitter,7,0);
    layout_principale->addWidget(vide[1],8,0);
    layout_principale->addWidget(owners,9,0);
    layout_principale->setAlignment(boot,Qt::AlignCenter);
    layout_principale->setAlignment(deux_joueur,Qt::AlignCenter);
    layout_principale->setAlignment(Charge,Qt::AlignCenter);
    layout_principale->setAlignment(Score,Qt::AlignCenter);
    layout_principale->setAlignment(Aide,Qt::AlignCenter);
    layout_principale->setAlignment(quitter,Qt::AlignCenter);

}

void menu::vs_boot()
{
    reaffichage=false;
    effacer();
    jeu->executer();
}

void menu::vs_boot(QString file_name)
{
    reaffichage=false;
    jeu->executer(file_name);
}

void menu::joueur_vs_joueur()
{
    reaffichage=true;
    effacer();
    joueurs->executer();
}

void menu::sauvegarder(QString file_name)
{
    jeu->sauvegarder(file_name);
}

void menu::charger_une_partie()
{
    effacer();
    charge->executer();
}

void menu::reafficher()
{
    if(reaffichage==false)
        jeu->effacer();
    else
    if(reaffichage==true)
        joueurs->effacer();
    executer();
}

void menu::rejouer()
{
    if(reaffichage==false)
        rejouer_vs_boot();
    else
    if(reaffichage==true)
        rejouer_joueur_vs_joueur();
}

void menu::rejouer_vs_boot()
{
    jeu->effacer();
    jeu->executer();
}

void menu::rejouer_joueur_vs_joueur()
{
    joueurs->effacer();
    joueurs->executer();
}

void menu::afficher_aide()
{
    effacer();
    help->executer();
}

void menu::afficher_score()
{
    effacer();
    statistique->executer();
}

void menu::modifier_pause()
{
    jeu->modifier_pause();
}
