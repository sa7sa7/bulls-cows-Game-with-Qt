#include "charger.h"
#include "menu.h"
#include "sous_fenetre.h"

charger::charger(menu *Parent, QGridLayout *Layout, Sous_fenetre *fenetre) : QObject()
{
    parent=Parent;
    layout_principale=Layout;
    sous_fenetre=fenetre;

    valider = new QPushButton("&Charger",parent);
    valider->setStyleSheet("QPushButton{color: rgb(221, 121, 62); font-size : 35px; font-family : Oduda}");
    valider->setFixedSize(270,50);
    valider->setToolTip("Charger la partie selectionnée");
    valider->setToolTipDuration(2000);
    Supprimer = new QPushButton("&Supprimer",parent);
    Supprimer->setStyleSheet("QPushButton{color: rgb(221, 121, 62); font-size : 35px; font-family : Oduda}");
    Supprimer->setFixedSize(270,50);
    Supprimer->setToolTip("Supprimer la partie selectionnée");
    Supprimer->setToolTipDuration(2000);
    retour = new QPushButton("&Retour",parent);
    retour->setStyleSheet("QPushButton{color: rgb(221, 121, 62); font-size : 35px; font-family : Oduda}");
    retour->setFixedSize(270,50);
    retour->setToolTip("Retourner vers le menu du jeu");
    retour->setToolTipDuration(2000);

    tableau = new QTableWidget(parent);
    tableau->setFrameShape(QFrame::NoFrame);
    tableau->setColumnCount(1);
    tableau->setColumnWidth(0,500);
    tableau->horizontalHeader()->setVisible(false);
    tableau->verticalHeader()->setStyleSheet("QHeaderView {color : rgb(58, 142, 186); font-size : 40px; font-family : Corbel}");
    tableau->verticalHeader()->setFixedWidth(150);
    tableau->setCurrentCell(-1,-1,QItemSelectionModel::SelectCurrent);

    enveloppe = new QWidget(parent);
    layout = new QVBoxLayout;
    layout->addWidget(tableau);
    layout->setAlignment(tableau,Qt::AlignTop);
    enveloppe->setLayout(layout);
    enveloppe->setFixedSize(500,520);

    Item = new QTableWidgetItem* [10];
    vue = new QLabel("Veuillez selecter une partie: ",parent);
    vue->setAlignment(Qt::AlignCenter);
    vue->setStyleSheet("QLabel{color: rgb(29, 72, 81); font-size : 45px; border : 5px solid rgb(27, 1, 155); padding : 20%; font-family : ernesto}");
    vue->setFixedSize(650,130);
    coin=true;
    selecte=false;
    compteur=0;

    vue->setVisible(false);
    enveloppe->setVisible(false);
    valider->setVisible(false);
    Supprimer->setVisible(false);
    retour->setVisible(false);


    QObject::connect(valider, SIGNAL(clicked()), this, SLOT(charger_une_partie()));
    QObject::connect(Supprimer, SIGNAL(clicked()), this, SLOT(supprimer()));
    QObject::connect(retour, SIGNAL(clicked()), this, SLOT(afficher_menu()));
    QObject::connect(tableau, SIGNAL(currentCellChanged(int,int,int,int)), this, SLOT(selecter(int,int,int,int)));
}

charger::~charger()
{
    delete layout;
    delete Item;
}

void charger::effacer()
{
    for(int i=0;i<compteur;i++)
    {
        delete Item[i];
    }

    if(vue->isVisible()==true)
    {
        layout_principale->removeWidget(vue);
        vue->setVisible(false);
    }
    if(enveloppe->isVisible()==true)
    {
        layout_principale->removeWidget(enveloppe);
        enveloppe->setVisible(false);
    }
    if(valider->isVisible()==true)
    {
        layout_principale->removeWidget(valider);
        valider->setVisible(false);
    }
    if(Supprimer->isVisible()==true)
    {
        layout_principale->removeWidget(Supprimer);
        Supprimer->setVisible(false);
    }
    if(retour->isVisible()==true)
    {
        layout_principale->removeWidget(retour);
        retour->setVisible(false);
    }

    selecte=false;
    coin=false;
    compteur=0;
    tableau->setCurrentCell(-1,-1,QItemSelectionModel::SelectCurrent);
}

void charger::executer()
{
    QDir dir("Sauvegardes");
    tableau->setRowCount(10);
    if(dir.exists()==true)
    {
        QDirIterator it(dir.dirName(), QStringList() << "*.VTsave", QDir::Files, QDirIterator::NoIteratorFlags);
        while((it.hasNext())&&(compteur<10))
        {
            it.next();
            Item[compteur] = new QTableWidgetItem();
            Item[compteur]->setText(it.fileInfo().baseName());
            Item[compteur]->setFlags(Qt::ItemIsEditable);
            Item[compteur]->setTextColor(QColor(0,0,0));
            Item[compteur]->setFont(QFont("Oduda",25));
            tableau->setItem(compteur, 0, Item[compteur]);
            tableau->setRowHeight(compteur,100);
            compteur++;
        }

        if(compteur!=0)
        {
            tableau->setRowCount(compteur);
            if(compteur<=5)
                tableau->setFixedHeight(100*compteur);
            else
                tableau->setFixedHeight(500);

            layout_principale->addWidget(vue,0,0,1,2);
            vue->setVisible(true);
            layout_principale->setAlignment(vue,Qt::AlignCenter);
            layout_principale->addWidget(enveloppe,1,0,1,2);
            enveloppe->setVisible(true);
            layout_principale->setAlignment(enveloppe,Qt::AlignCenter);
            layout_principale->addWidget(valider,2,0);
            valider->setVisible(true);
            layout_principale->setAlignment(valider,Qt::AlignCenter);
            layout_principale->addWidget(Supprimer,2,1);
            Supprimer->setVisible(true);
            layout_principale->setAlignment(Supprimer,Qt::AlignCenter);
            layout_principale->addWidget(retour,3,0,1,2);
            retour->setVisible(true);
            retour->setAutoDefault(true);
            retour->setFocus(Qt::BacktabFocusReason);
            layout_principale->setAlignment(retour,Qt::AlignCenter);
        }else
        {
            parent->executer();
            sous_fenetre->afficher1("Le dossier Sauvegarde est vide.",-1);
            sous_fenetre->show();
        }
    }else
    {
        parent->executer();
        sous_fenetre->afficher1("Le dossier Sauvegarde n'existe pas.\nVeuillez relancer le jeu.",-3);
        sous_fenetre->show();
    }
}

void charger::selecter(int row1, int column1,int row2, int column2)
{
    selecte=true;
    if((row1!=-1)&&(column1!=-1))
    {
        tableau->item(row1,column1)->setTextColor(QColor(255,0,0));
    }else
        selecte=false;
    if((row2!=-1)&&(column2!=-1)&&(coin==true))
    {
        tableau->item(row2,column2)->setTextColor(QColor(0,0,0));
    }
    if(coin==false)
        coin=true;
}

void charger::charger_une_partie()
{
    if(selecte==true)
    {
        QFile file("Sauvegardes\\"+tableau->currentItem()->text()+".VTsave");
        if(file.exists())
        {
            QString file_name(tableau->currentItem()->text());
            effacer();
            parent->vs_boot(file_name);
        }else
        {
            sous_fenetre->afficher1(tableau->currentItem()->text()+".VTsave n'existe pas.",-1);
            sous_fenetre->show();
        }
    }
    else
    {
        sous_fenetre->afficher1("Vous n'avez choisit aucun fichier.",-1);
        sous_fenetre->show();
    }
}

void charger::supprimer()
{
    if(selecte==true)
    {
        QFile file("Sauvegardes\\"+tableau->currentItem()->text()+".VTsave");
        file.open(QIODevice::ReadOnly);
        if(file.exists())
        {
            file.remove();
            file.close();
            effacer();
            executer();
        }else
        {
            sous_fenetre->afficher1(tableau->currentItem()->text()+".VTsave n'existe pas.",-1);
            sous_fenetre->show();
        }
    }else
    {
        sous_fenetre->afficher1("Vous n'avez choisit aucun fichier.",-1);
        sous_fenetre->show();
    }
}

void charger::afficher_menu()
{
    effacer();
    parent->executer();
}
