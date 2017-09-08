#include "aide.h"
#include "menu.h"
#include "scroll.h"

aide::aide(menu *Parent, QGridLayout *Layout):QObject()
{
    parent=Parent;
    layout_principale=Layout;
    retour = new QPushButton("&Retour",parent);
    retour->setStyleSheet("QPushButton{color: rgb(221, 121, 62); font-size : 35px; font-family : Oduda}");
    retour->setFixedSize(270,50);
    retour->setToolTip("Retourner vers le menu du jeu");
    retour->setToolTipDuration(2000);

    image1 = new QLabel(parent);
    image1->setPixmap(QPixmap("Images\\Help1.jpg"));
    image1->setAlignment(Qt::AlignCenter);

    scroll = new Scroll(parent,retour);
    scroll->setWidget(image1);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->setFixedSize(1220,700);
    image2 = new QLabel(parent);
    image2->setPixmap(QPixmap("Images\\Help2.jpg"));
    image2->setAlignment(Qt::AlignCenter);

    image3 = new QLabel(parent);
    image3->setPixmap(QPixmap("Images\\Help3.jpg"));
    image3->setAlignment(Qt::AlignCenter);

    onglets = new QTabWidget(parent);
    onglets->addTab(scroll, "Lois du jeu ");
    onglets->addTab(image2, "Jouer contre un robot?");
    onglets->addTab(image3, "Jouer contre un ami?");
    onglets->setElideMode(Qt::ElideMiddle);
    onglets->setTabPosition(QTabWidget::West);
    onglets->setFixedSize(1260,700);
    onglets->setStyleSheet("QTabWidget{font-size : 25px; font-family : Oduda}");

    retour->setVisible(false);
    onglets->setVisible(false);
    QObject::connect(retour, SIGNAL(clicked()), this, SLOT(afficher_menu()));
    QObject::connect(onglets, SIGNAL(currentChanged(int)), this, SLOT(retourner_focus()));

}

void aide::effacer()
{
    layout_principale->removeWidget(onglets);
    onglets->setVisible(false);
    layout_principale->removeWidget(retour);
    retour->setVisible(false);
    scroll->ensureVisible(0,0);
    onglets->setCurrentIndex(0);
}

void aide::executer()
{
    layout_principale->addWidget(onglets,0,0);
    onglets->setVisible(true);
    layout_principale->setAlignment(onglets,Qt::AlignCenter);
    layout_principale->addWidget(retour,1,0);
    retour->setVisible(true);
    retour->setAutoDefault(true);
    retour->setFocus(Qt::BacktabFocusReason);
    layout_principale->setAlignment(retour,Qt::AlignCenter);
}

void aide::afficher_menu()
{
    effacer();
    parent->executer();
}

void aide::retourner_focus()
{
    retour->setAutoDefault(true);
    retour->setFocus(Qt::BacktabFocusReason);
}
