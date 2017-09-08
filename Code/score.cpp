#include "score.h"
#include "menu.h"
#include "scroll.h"
#include "sous_fenetre.h"

score::score(menu *Parent, QGridLayout *Layout, Sous_fenetre *fenetre):QObject()
{
    parent=Parent;
    layout_principale=Layout;
    sous_fenetre=fenetre;

    retour = new QPushButton("&Retour",parent);
    retour->setStyleSheet("QPushButton{color: rgb(221, 121, 62); font-size : 35px; font-family : Oduda}");
    retour->setFixedSize(270,50);
    retour->setToolTip("Retourner vers le menu du jeu");
    retour->setToolTipDuration(2000);

    vue= new QLabel*[4];
    vue[0] = new QLabel("Total des parties jouées: ",parent);
    vue[0]->setAlignment(Qt::AlignLeft);
    vue[0]->setStyleSheet("QLabel{color: rgb(29, 72, 81); font-size : 35px; font-family : ernesto}");
    vue[0]->setFixedSize(450,70);
    vue[1] = new QLabel("Total des parties gagnées: ",parent);
    vue[1]->setAlignment(Qt::AlignLeft);
    vue[1]->setStyleSheet("QLabel{color: rgb(29, 72, 81); font-size : 35px; font-family : ernesto}");
    vue[1]->setFixedSize(450,70);
    vue[2] = new QLabel("Total des parties perdues: ",parent);
    vue[2]->setAlignment(Qt::AlignLeft);
    vue[2]->setStyleSheet("QLabel{color: rgb(29, 72, 81); font-size : 35px; font-family : ernesto}");
    vue[2]->setFixedSize(450,70);
    vue[3] = new QLabel("Total des égalités: ",parent);
    vue[3]->setAlignment(Qt::AlignLeft);
    vue[3]->setStyleSheet("QLabel{color: rgb(29, 72, 81); font-size : 35px; font-family : ernesto}");
    vue[3]->setFixedSize(450,70);


    layout = new QVBoxLayout;
    layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    labels = new QLabel* [10];
    for(int i=0;i<10;i++)
    {
        labels[i]=new QLabel ("",parent);
        labels[i]->setStyleSheet("QLabel{color: red; font-size : 25px; font-family : Corbel;}");
        layout->addWidget(labels[i]);
        labels[i]->setFixedSize(450,75);
    }

    scroll = new Scroll(parent,retour);
    widget = new QWidget(parent);
    widget->setLayout(layout);
    widget->setFixedSize(500,400);
    scroll->setWidget(widget);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->setFixedSize(500,400);
    scroll->setWidgetResizable(true);

    retour->setVisible(false);
    vue[0]->setVisible(false);
    vue[1]->setVisible(false);
    vue[2]->setVisible(false);
    vue[3]->setVisible(false);
    scroll->setVisible(false);

    QObject::connect(retour, SIGNAL(clicked()), this, SLOT(afficher_menu()));
}

score::~score()
{
    delete vue;
    delete layout;
    delete labels;
}

void score::executer()
{
    QFile file("Score.save");
    if(file.exists()==true)
    {
        QString chaine1(""),chaine2("");
        file.open(QIODevice::ReadOnly);
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out>>chaine1;
        vue[0]->setText("Total des parties jouées: "+chaine1);
        out>>chaine1;
        vue[1]->setText("Total des parties gagnées: "+chaine1);
        out>>chaine1;
        vue[2]->setText("Total des parties perdues: "+chaine1);
        out>>chaine1;
        vue[3]->setText("Total des égalités: "+chaine1);
        for(int i=0;i<10;i++)
        {
            out>>chaine1;
            out>>chaine2;
            labels[i]->setText(QString::number(i+1)+"- "+chaine1+"\t\t"+chaine2);
        }
        file.close();

        layout_principale->addWidget(vue[0],0,0);
        vue[0]->setVisible(true);
        layout_principale->setAlignment(vue[0],Qt::AlignCenter);
        layout_principale->addWidget(vue[1],1,0);
        vue[1]->setVisible(true);
        layout_principale->setAlignment(vue[1],Qt::AlignCenter);
        layout_principale->addWidget(vue[2],2,0);
        vue[2]->setVisible(true);
        layout_principale->setAlignment(vue[2],Qt::AlignCenter);
        layout_principale->addWidget(vue[3],3,0);
        vue[3]->setVisible(true);
        layout_principale->setAlignment(vue[3],Qt::AlignCenter);

        layout_principale->addWidget(scroll,4,0);
        scroll->setVisible(true);
        layout_principale->setAlignment(scroll,Qt::AlignCenter);

        layout_principale->addWidget(retour,5,0);
        retour->setVisible(true);
        retour->setAutoDefault(true);
        retour->setFocus(Qt::BacktabFocusReason);
        layout_principale->setAlignment(retour,Qt::AlignCenter);
    }else
    {
        parent->executer();
        sous_fenetre->afficher1("Le dossier Score.stat n'existe pas.\nVeuillez relancer le jeu.",-3);
        sous_fenetre->show();
    }
}

void score::effacer()
{
    for(int i=0;i<4;i++)
    {
        if(vue[i]->isVisible()==true)
        {
            layout_principale->removeWidget(vue[i]);
            vue[i]->setText("");
            vue[i]->setVisible(false);
        }
    }
    for(int i=0;i<10;i++)
    {
        labels[i]->setText("");
    }
    if(scroll->isVisible()==true)
    {
        layout_principale->removeWidget(scroll);
        scroll->setVisible(false);
    }
    if(retour->isVisible()==true)
    {
        layout_principale->removeWidget(retour);
        retour->setVisible(false);
    }
    scroll->ensureVisible(0,0);
}

void score::afficher_menu()
{
    effacer();
    parent->executer();
}
