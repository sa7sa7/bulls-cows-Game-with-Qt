#include "sauvegarder.h"
#include "menu.h"
#include "sous_fenetre.h"

Sauvegarder::Sauvegarder(menu *Parent, Sous_fenetre *fenetre, QVBoxLayout *Layout):QObject()
{
    parent=Parent;
    layout_principale=Layout;
    sous_fenetre=fenetre;
    OK = new QPushButton("&OK",sous_fenetre);
    OK->setStyleSheet("QPushButton{color: rgb(58, 142, 186); font-size : 25px; font-family : Oduda}");
    OK->setFixedSize(135,40);
    bouton_valider = new QPushButton("&Valider",sous_fenetre);
    bouton_valider->setFixedSize(135,50);
    bouton_valider->setStyleSheet("QPushButton{color: rgb(58, 142, 186); font-size : 25px; font-family : Oduda}");
    oui = new QPushButton("&Oui",sous_fenetre);
    oui->setFixedSize(135,50);
    oui->setStyleSheet("QPushButton{color: rgb(58, 142, 186); font-size : 25px; font-family : Oduda}");
    non = new QPushButton("&Non",sous_fenetre);
    non->setFixedSize(135,50);
    non->setStyleSheet("QPushButton{color: rgb(58, 142, 186); font-size : 25px; font-family : Oduda}");
    input=new QLineEdit(sous_fenetre);
    input->setMaxLength(20);
    input->setFixedSize(200,35);
    input->setStyleSheet("QLineEdit{font-size : 20px; font-family : Corbel}");

    vue = new QLabel("",sous_fenetre);
    vue->setAlignment(Qt::AlignCenter);

    layout= new QHBoxLayout;
    layout->addWidget(oui);
    layout->addWidget(non);

    OK->setVisible(false);
    bouton_valider->setVisible(false);
    oui->setVisible(false);
    non->setVisible(false);
    vue->setVisible(false);
    input->setVisible(false);

    QObject::connect(OK, SIGNAL(clicked()), sous_fenetre, SLOT(close()));
    QObject::connect(bouton_valider, SIGNAL(clicked()), this, SLOT(valider()));
    QObject::connect(input, SIGNAL(returnPressed()), this, SLOT(valider()));
    QObject::connect(oui, SIGNAL(clicked()), this, SLOT(Oui()));
    QObject::connect(non, SIGNAL(clicked()), this, SLOT(Non()));
}

Sauvegarder::~Sauvegarder()
{
    delete layout;
}

void Sauvegarder::effacer()
{
    if(OK->isVisibleTo(sous_fenetre)==true)
    {
        layout_principale->removeWidget(OK);
        OK->setVisible(false);
    }
    if(bouton_valider->isVisibleTo(sous_fenetre)==true)
    {
        layout_principale->removeWidget(bouton_valider);
        bouton_valider->setVisible(false);
    }
    if(oui->isVisibleTo(sous_fenetre)==true)
    {
        layout_principale->removeItem(layout);
        oui->setVisible(false);
        non->setVisible(false);
    }
    if(vue->isVisibleTo(sous_fenetre)==true)
    {
        layout_principale->removeWidget(vue);
        vue->setVisible(false);
    }
    if(input->isVisibleTo(sous_fenetre)==true)
    {
        layout_principale->removeWidget(input);
        input->setVisible(false);
    }
    vue->setText("");
    input->setText("");
}

void Sauvegarder::preexecuter()
{
    sous_fenetre->setWindowTitle("Sauvegarder");
    QDir dir("Sauvegardes");
    int erreur=0,compteur=0;
    if(dir.exists()==true)
    {
        QDirIterator it(dir.dirName(), QStringList() << "*.VTsave", QDir::Files, QDirIterator::Subdirectories);
        while (it.hasNext())
        {
            it.next();
            compteur++;
        }

        if(compteur<10)
        {
            erreur=0;
        }else
        {
            erreur=1;
        }
    }else
    {
        erreur=2;
    }

    if(erreur!=0)
    {
        if(erreur==1)
            vue->setText("Vous avez 10 sauvegardes ou plus.\nSumpprimez quelqu'uns pour sauvegarder autres.");
        else
            vue->setText("Le dossier Sauvegarde n'existe pas.\nVeuillez relancer le jeu.");
        vue->setStyleSheet("QLabel{color: rgb(29, 72, 81); font-size : 30px;border : 3px solid rgb(27, 1, 155); padding : 20%; font-family : ernesto}");
        layout_principale->addWidget(vue);
        vue->setVisible(true);
        layout_principale->setAlignment(vue,Qt::AlignCenter);
        layout_principale->addWidget(OK);
        OK->setVisible(true);
        OK->setAutoDefault(true);
        OK->setFocus(Qt::BacktabFocusReason);
        layout_principale->setAlignment(OK,Qt::AlignCenter);
        if(erreur==1)
        {
            if((sous_fenetre->x()==parent->x()+parent->width()/2-110)&&(sous_fenetre->y()==parent->y()+parent->height()/2-155))
            {
                sous_fenetre->move(parent->x()+parent->width()/2-300,parent->y()+parent->height()/2-90);
            }
            sous_fenetre->setFixedSize(600,180);
        }else
        {
            if((sous_fenetre->x()==parent->x()+parent->width()/2-110)&&(sous_fenetre->y()==parent->y()+parent->height()/2-155))
            {
                sous_fenetre->move(parent->x()+parent->width()/2-255,parent->y()+parent->height()/2-90);
            }
            sous_fenetre->setFixedSize(450,180);
        }
        sous_fenetre->adjustSize();
    }else
    {
        executer(compteur+1);
    }
}

void Sauvegarder::executer(int compteur)
{
    vue->setText("Veuillez entrer le nom de votre sauvegarde:");
    vue->setStyleSheet("QLabel{color: rgb(29, 72, 81); font-size : 25px;border : 3px solid rgb(27, 1, 155); padding : 20%; font-family : ernesto}");
    layout_principale->addWidget(vue);
    vue->setVisible(true);
    layout_principale->setAlignment(vue,Qt::AlignCenter);
    layout_principale->addWidget(input);
    input->setFocus(Qt::TabFocusReason);
    input->setVisible(true);
    if(compteur!=-1)
        input->setText("sauvegarde "+QString::number(compteur));
    input->selectAll();
    layout_principale->setAlignment(input,Qt::AlignCenter);
    layout_principale->addWidget(bouton_valider);
    bouton_valider->setVisible(true);
    layout_principale->setAlignment(bouton_valider,Qt::AlignCenter);
    if(((sous_fenetre->x()==parent->x()+parent->width()/2-110)&&(sous_fenetre->y()==parent->y()+parent->height()/2-155))||((sous_fenetre->x()==parent->x()+parent->width()/2-275)&&(sous_fenetre->y()==parent->y()+parent->height()/2-100)))
    {
        sous_fenetre->move(parent->x()+parent->width()/2-235,parent->y()+parent->height()/2-110);
    }
    sous_fenetre->setFixedSize(470,220);
    sous_fenetre->adjustSize();
}

void Sauvegarder::valider()
{
    if(input->isVisibleTo(sous_fenetre)==true)
    {
        layout_principale->removeWidget(input);
        input->setVisible(false);
    }
    if(bouton_valider->isVisibleTo(sous_fenetre)==true)
    {
        layout_principale->removeWidget(bouton_valider);
        bouton_valider->setVisible(false);
    }

    QDir dir("Sauvegardes");
    bool erreur=false;
    if(dir.exists()==true)
    {
        QDirIterator it(dir.dirName(), QStringList() << "*.VTsave", QDir::Files, QDirIterator::Subdirectories);
        while (it.hasNext()&&(erreur==false))
        {
            it.next();
            if(it.fileInfo().baseName()==input->text())
            {
                erreur=true;
            }
        }

        if(erreur==true)
        {
            vue->setText(input->text()+".VTsave existe déjà.\n voulez vous continuer la sauvegarde?");
            vue->setStyleSheet("QLabel{color: rgb(29, 72, 81); font-size : 35px;border : 3px solid rgb(27, 1, 155); padding : 20%; font-family : ernesto}");
            layout_principale->addWidget(vue);
            vue->setVisible(true);
            layout_principale->setAlignment(vue,Qt::AlignCenter);
            layout_principale->addLayout(layout);
            oui->setVisible(true);
            non->setVisible(true);
            non->setAutoDefault(true);
            non->setFocus(Qt::BacktabFocusReason);
            if((sous_fenetre->x()==parent->x()+parent->width()/2-235)&&(sous_fenetre->y()==parent->y()+parent->height()/2-110))
            {
                sous_fenetre->move(parent->x()+parent->width()/2-275,parent->y()+parent->height()/2-100);
            }
            sous_fenetre->setFixedSize(550,200);
        }else
        {
            vue->setText("Sauvegarde réussite.");
            vue->setStyleSheet("QLabel{color: rgb(29, 72, 81); font-size : 35px;border : 3px solid rgb(27, 1, 155); padding : 20%; font-family : ernesto}");
            layout_principale->addWidget(vue);
            layout_principale->addWidget(OK);
            OK->setVisible(true);
            OK->setAutoDefault(true);
            OK->setFocus(Qt::BacktabFocusReason);
            layout_principale->setAlignment(OK,Qt::AlignCenter);
            if((sous_fenetre->x()==parent->x()+parent->width()/2-235)&&(sous_fenetre->y()==parent->y()+parent->height()/2-110))
            {
                sous_fenetre->move(parent->x()+parent->width()/2-225,parent->y()+parent->height()/2-90);
            }
            sous_fenetre->setFixedSize(450,180);
            sous_fenetre->adjustSize();
            parent->sauvegarder(input->text());
        }
    }else
    {
        vue->setText("Le dossier Sauvegarde n'existe pas.\nVeuillez relancer le jeu.");
        vue->setStyleSheet("QLabel{color: rgb(29, 72, 81); font-size : 30px;border : 3px solid rgb(27, 1, 155); padding : 20%; font-family : ernesto}");
        layout_principale->setAlignment(vue,Qt::AlignCenter);
        layout_principale->addWidget(OK);
        OK->setVisible(true);
        OK->setAutoDefault(true);
        OK->setFocus(Qt::BacktabFocusReason);
        layout_principale->setAlignment(OK,Qt::AlignCenter);
        if((sous_fenetre->x()==parent->x()+parent->width()/2-235)&&(sous_fenetre->y()==parent->y()+parent->height()/2-110))
        {
            sous_fenetre->move(parent->x()+parent->width()/2-255,parent->y()+parent->height()/2-90);
        }
        sous_fenetre->setFixedSize(450,180);
        sous_fenetre->adjustSize();
    }
}

void Sauvegarder::Oui()
{
    if(oui->isVisibleTo(sous_fenetre)==true)
    {
        layout_principale->removeItem(layout);
        oui->setVisible(false);
        non->setVisible(false);
    }
    vue->setText("Sauvegarde réussite.");
    vue->setStyleSheet("QLabel{color: rgb(29, 72, 81); font-size : 35px;border : 3px solid rgb(27, 1, 155); padding : 20%; font-family : ernesto}");
    layout_principale->addWidget(vue);
    layout_principale->addWidget(OK);
    OK->setVisible(true);
    OK->setAutoDefault(true);
    OK->setFocus(Qt::BacktabFocusReason);
    layout_principale->setAlignment(OK,Qt::AlignCenter);
    if((sous_fenetre->x()==parent->x()+parent->width()/2-275)&&(sous_fenetre->y()==parent->y()+parent->height()/2-100))
    {
        sous_fenetre->move(parent->x()+parent->width()/2-225,parent->y()+parent->height()/2-90);
    }
    sous_fenetre->setFixedSize(450,180);
    sous_fenetre->adjustSize();
    parent->sauvegarder(input->text());  
}

void Sauvegarder::Non()
{
    if(oui->isVisibleTo(sous_fenetre)==true)
    {
        layout_principale->removeItem(layout);
        oui->setVisible(false);
        non->setVisible(false);
    }
    if(vue->isVisibleTo(sous_fenetre)==true)
    {
        layout_principale->removeWidget(vue);
        vue->setVisible(false);
    }
    executer(-1);
}
