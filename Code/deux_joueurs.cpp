#include "deux_joueurs.h"
#include "menu.h"
#include "scroll.h"
#include "sous_fenetre.h"
#include "calcul_estimation.h"

deux_joueurs::deux_joueurs(menu *Parent, QGridLayout *Layout, Sous_fenetre *fenetre):QObject()
{
    parent=Parent;
    layout_principale=Layout;
    sous_fenetre=fenetre;

    bouton_valider11 = new QPushButton("&valider",parent);
    bouton_valider11->setStyleSheet("QPushButton{color: rgb(58, 142, 186); font-size : 25px; font-family : Oduda}");
    bouton_valider11->setFixedSize(130,40);
    bouton_valider21 = new QPushButton("&valider",parent);
    bouton_valider21->setStyleSheet("QPushButton{color: rgb(58, 142, 186); font-size : 25px; font-family : Oduda}");
    bouton_valider21->setFixedSize(130,40);
    bouton_valider12 = new QPushButton("&valider",parent);
    bouton_valider12->setStyleSheet("QPushButton{color: rgb(58, 142, 186); font-size : 25px; font-family : Oduda}");
    bouton_valider12->setFixedSize(130,40);
    bouton_valider22 = new QPushButton("&valider",parent);
    bouton_valider22->setStyleSheet("QPushButton{color: rgb(58, 142, 186); font-size : 25px; font-family : Oduda}");
    bouton_valider22->setFixedSize(130,40);
    bouton_pause = new QPushButton("",parent);
    bouton_pause->setMask(QRegion(QRect(bouton_pause->x()+5,bouton_pause->y()+5,70,70),QRegion::Ellipse));
    bouton_pause->setIcon(QPixmap("Images\\icone.jpg"));
    bouton_pause->setFixedSize(80,80);
    bouton_pause->setIconSize(QSize(70,70));
    bouton_pause->setCursor(Qt::PointingHandCursor);

    input1 = new QLineEdit(parent);
    input1->setMaxLength(4);
    input1->setFixedSize(125,35);
    input1->setStyleSheet("QLineEdit{color:red; font-size : 20px; font-family : Corbel}");

    input2 = new QLineEdit(parent);
    input2->setMaxLength(4);
    input2->setFixedSize(125,35);
    input2->setStyleSheet("QLineEdit{color:red; font-size : 20px; font-family : Corbel}");

    vache = new QComboBox(parent);
    vache->addItem("0");
    vache->addItem("1");
    vache->addItem("2");
    vache->addItem("3");
    vache->addItem("4");
    vache->setStyleSheet("QComboBox{font-size : 20px; font-family : Corbel}");
    vache->setFixedSize(130,35);

    taureau = new QComboBox(parent);
    taureau->addItem("0");
    taureau->addItem("1");
    taureau->addItem("2");
    taureau->addItem("3");
    taureau->addItem("4");
    taureau->setStyleSheet("QComboBox{font-size : 20px; font-family : Corbel}");
    taureau->setFixedSize(130,35);

    layout_joueur1 = new QGridLayout;
    layout_joueur2 = new QGridLayout;
    layout_joueur1->setSizeConstraint(QLayout::SetMinAndMaxSize);
    layout_joueur2->setSizeConstraint(QLayout::SetMinAndMaxSize);

    labels= new QLabel* [8];
    labels[0] = new QLabel ("Estimation Joueur 1",parent);
    labels[0]->setFixedSize(130,40);
    labels[0]->setStyleSheet("QLabel{color: rgb(58, 142, 186); font-size : 15px; font-family : Calibri}");
    layout_joueur1->addWidget(labels[0],0,0);
    labels[1] = new QLabel ("Nombre de Vaches",parent);
    labels[1]->setFixedSize(130,40);
    labels[1]->setStyleSheet("QLabel{color: rgb(58, 142, 186); font-size : 15px; font-family : Calibri}");
    layout_joueur1->addWidget(labels[1],0,1);
    labels[2] = new QLabel ("Nombre de Taureaux",parent);
    labels[2]->setFixedSize(130,40);
    labels[2]->setStyleSheet("QLabel{color: rgb(58, 142, 186); font-size : 15px; font-family : Calibri}");
    layout_joueur1->addWidget(labels[2],0,2);
    labels[3] = new QLabel ("",parent);
    labels[3]->setFixedSize(130,40);
    layout_joueur1->addWidget(labels[3],0,3);

    labels[4] = new QLabel ("Estimation Joueur 2",parent);
    labels[4]->setFixedSize(130,40);
    labels[4]->setStyleSheet("QLabel{color: rgb(58, 142, 186); font-size : 15px; font-family : Calibri}");
    layout_joueur2->addWidget(labels[4],0,0);
    labels[5] = new QLabel ("Nombre de Vaches",parent);
    labels[5]->setFixedSize(130,40);
    labels[5]->setStyleSheet("QLabel{color: rgb(58, 142, 186); font-size : 15px; font-family : Calibri}");
    layout_joueur2->addWidget(labels[5],0,1);
    labels[6] = new QLabel ("Nombre de Taureaux",parent);
    labels[6]->setFixedSize(130,40);
    labels[6]->setStyleSheet("QLabel{color: rgb(58, 142, 186); font-size : 15px; font-family : Calibri}");
    layout_joueur2->addWidget(labels[6],0,2);
    labels[7] = new QLabel ("",parent);
    labels[7]->setFixedSize(130,40);
    layout_joueur2->addWidget(labels[7],0,3);

    messages1= new QLabel** [100];
    for(int i=0;i<100;i++)
    {
        messages1[i]=new QLabel* [3];
        for(int j=0;j<3;j++)
        {
            messages1[i][j]=new QLabel("",parent);
            if(j==0)
                messages1[i][j]->setStyleSheet("QLabel{color: red; font-size : 17px; font-family : Corbel}");
            else
                messages1[i][j]->setStyleSheet("QLabel{font-size : 17px; font-family : Corbel}");
            layout_joueur1->addWidget(messages1[i][j],i+1,j);
            messages1[i][j]->setVisible(false);
            messages1[i][j]->setFixedSize(130,40);
        }
    }

    messages2= new QLabel** [100];
    for(int i=0;i<100;i++)
    {
        messages2[i]=new QLabel* [3];
        for(int j=0;j<3;j++)
        {
            messages2[i][j]=new QLabel("",parent);
            if(j==0)
                messages2[i][j]->setStyleSheet("QLabel{color: red; font-size : 17px; font-family : Corbel}");
            else
                messages2[i][j]->setStyleSheet("QLabel{font-size : 17px; font-family : Corbel}");
            layout_joueur2->addWidget(messages2[i][j],i+1,j);
            messages2[i][j]->setVisible(false);
            messages2[i][j]->setFixedSize(130,40);
        }
    }

    message= new QLabel ("",parent);
    message->setAlignment(Qt::AlignCenter);
    message->setFixedHeight(150);
    layout= new QHBoxLayout;
    layout->addWidget(bouton_pause);
    layout->addWidget(message);

    layout1 = new QVBoxLayout;
    scroll1 = new Scroll(parent,bouton_valider12,input1);
    widget1 = new QWidget(parent);
    widget1->setLayout(layout_joueur1);
    scroll1->setWidget(widget1);
    scroll1->setFrameShape(QFrame::NoFrame);
    scroll1->setFixedSize(600,540);
    layout1->addWidget(scroll1);
    scroll1->setWidgetResizable(true);

    layout2 = new QVBoxLayout;
    scroll2 = new Scroll(parent,bouton_valider22,input2);
    widget2 = new QWidget(parent);
    widget2->setLayout(layout_joueur2);
    scroll2->setWidget(widget2);
    scroll2->setFrameShape(QFrame::NoFrame);
    scroll2->setFixedSize(600,540);
    layout2->addWidget(scroll2);
    scroll2->setWidgetResizable(true);

    box_joueur1 = new QGroupBox ("Estimations du Joueur 1",parent);
    box_joueur1->setStyleSheet("QGroupBox{color: rgb(34, 66, 124); font-size : 40px; font-family : Chalk Marks}");
    box_joueur1->setLayout(layout1);
    box_joueur1->setFixedSize(625,600);
    box_joueur2 = new QGroupBox ("Estimations du Joueur 2",parent);
    box_joueur2->setFixedSize(625,600);
    box_joueur2->setStyleSheet("QGroupBox{color: rgb(34, 66, 124); font-size : 40px; font-family : Chalk Marks}");
    box_joueur2->setLayout(layout2);

    bouton_valider11->setVisible(false);
    bouton_valider21->setVisible(false);
    bouton_valider12->setVisible(false);
    bouton_valider22->setVisible(false);
    bouton_pause->setVisible(false);
    input1->setVisible(false);
    input2->setVisible(false);
    vache->setVisible(false);
    taureau->setVisible(false);
    box_joueur1->setVisible(false);
    box_joueur2->setVisible(false);
    message->setVisible(false);


    QObject::connect(bouton_pause, SIGNAL(clicked()), this, SLOT(pause()));
    QObject::connect(bouton_valider11, SIGNAL(clicked()), this, SLOT(valider_joueur11()));
    QObject::connect(input1, SIGNAL(returnPressed()), this, SLOT(valider_joueur11()));
    QObject::connect(bouton_valider12, SIGNAL(clicked()), this, SLOT(valider_joueur12()));
    QObject::connect(bouton_valider21, SIGNAL(clicked()), this, SLOT(valider_joueur21()));
    QObject::connect(input2, SIGNAL(returnPressed()), this, SLOT(valider_joueur21()));
    QObject::connect(bouton_valider22, SIGNAL(clicked()), this, SLOT(valider_joueur22()));
    QObject::connect(vache,SIGNAL(currentIndexChanged(int)),this, SLOT(modifier_taureau(int)));
    QObject::connect(taureau,SIGNAL(currentIndexChanged(int)),this, SLOT(modifier_vache(int)));
}

deux_joueurs::~deux_joueurs()
{
    delete layout_joueur1;
    delete layout_joueur2;
    delete labels;
    delete layout;
    delete layout1;
    delete layout2;
    for(int i=0;i<100;i++)
    {
        delete messages1[i];
    }
    delete messages1;
    for(int i=0;i<100;i++)
    {
        delete messages2[i];
    }
    delete messages2;
}

void deux_joueurs::executer()
{
    gagner_joueur1= false;
    gagner_joueur2= false;

    ligne1=0;
    ligne2=0;

    layout_principale->addLayout(layout,0,0,1,2);
    layout_principale->addWidget(box_joueur1,1,0);
    layout_principale->addWidget(box_joueur2,1,1);
    bouton_pause->setVisible(true);
    message->setVisible(true);
    box_joueur1->setVisible(true);
    box_joueur2->setVisible(true);
    saisir_estimation_joueur1();
}

void deux_joueurs::effacer()
{
    int i,j;
    for(i=0;i<ligne1;i++)
    {
        for(j=0;j<3;j++)
        {
            messages1[i][j]->setText("");
            messages1[i][j]->setVisible(false);
        }
    }

    for(i=0;i<ligne2;i++)
    {
        for(j=0;j<3;j++)
        {
            messages2[i][j]->setText("");
            messages2[i][j]->setVisible(false);
        }
    }

    if(vache->isVisible()==true)
    {
        if(layout_joueur1->indexOf(vache)!=-1)
            layout_joueur1->removeWidget(vache);
        else
            layout_joueur2->removeWidget(vache);
        vache->setVisible(false);
    }
    if(taureau->isVisible()==true)
    {
        if(layout_joueur1->indexOf(taureau)!=-1)
            layout_joueur1->removeWidget(taureau);
        else
            layout_joueur2->removeWidget(taureau);
        taureau->setVisible(false);
    }

    if(bouton_valider11->isVisible()==true)
    {
        layout_joueur1->removeWidget(bouton_valider11);
        bouton_valider11->setVisible(false);
    }
    if(bouton_valider12->isVisible()==true)
    {
        layout_joueur1->removeWidget(bouton_valider12);
        bouton_valider12->setVisible(false);
    }
    if(bouton_valider21->isVisible()==true)
    {
        layout_joueur2->removeWidget(bouton_valider21);
        bouton_valider21->setVisible(false);
    }
    if(bouton_valider22->isVisible()==true)
    {
        layout_joueur2->removeWidget(bouton_valider22);
        bouton_valider22->setVisible(false);
    }

    if(input1->isVisible()==true)
    {
        layout_joueur1->removeWidget(input1);
        input1->setVisible(false);
    }

    if(input2->isVisible()==true)
    {
        layout_joueur2->removeWidget(input2);
        input2->setVisible(false);
    }

    layout_principale->removeItem(layout);
    bouton_pause->setVisible(false);
    message->setVisible(false);
    layout_principale->removeWidget(box_joueur1);
    box_joueur1->setVisible(false);
    layout_principale->removeWidget(box_joueur2);
    box_joueur2->setVisible(false);
}

void deux_joueurs::saisir_estimation_joueur1()
{
    ligne1++;
    message->setText("C'est le tour du Joueur 1.\nEssayez de trouver le nombre du Joueur 2 en proposant un autre nombre.");
    message->setStyleSheet("QLabel{color: rgb(29, 72, 81); font-size : 30px;border : 5px solid rgb(27, 1, 155); padding : 30%; font-family : ernesto}");
    layout_joueur1->addWidget(input1,ligne1,0);
    layout_joueur1->addWidget(bouton_valider11,ligne1,3);
    bouton_valider11->setVisible(true);
    input1->setVisible(true);
    input1->setText("");
    input1->setClearButtonEnabled(true);
    input1->setFocus(Qt::TabFocusReason);
    scroll1->ensureVisible(0,130*ligne1);
}

void deux_joueurs::saisir_estimation_joueur2()
{
    ligne2++;
    message->setText("C'est le tour du Joueur 2.\nEssayez de trouver le nombre du Joueur 1 en proposant un autre nombre.");
    message->setStyleSheet("QLabel{color: rgb(29, 72, 81); font-size : 30px;border : 5px solid rgb(27, 1, 155); padding : 30%; font-family : ernesto}");
    layout_joueur2->addWidget(input2,ligne2,0);
    layout_joueur2->addWidget(bouton_valider21,ligne2,3);
    bouton_valider21->setVisible(true);
    input2->setVisible(true);
    input2->setText("");
    input2->setClearButtonEnabled(true);
    input2->setFocus(Qt::TabFocusReason);
    scroll2->ensureVisible(0,130*ligne2);
}

void deux_joueurs::pause()
{
    sous_fenetre->pause(2);
    input1->setFocus(Qt::TabFocusReason);
    input2->setFocus(Qt::TabFocusReason);
    bouton_valider12->setAutoDefault(true);
    bouton_valider12->setFocus(Qt::BacktabFocusReason);
    bouton_valider22->setAutoDefault(true);
    bouton_valider22->setFocus(Qt::BacktabFocusReason);
    sous_fenetre->show();
}

void deux_joueurs::valider_joueur11()
{
    if(input1->text().isEmpty()==true)
    {
        sous_fenetre->afficher1("Vous n'avez entré aucun nombre",-1);
        input1->setFocus(Qt::TabFocusReason);
        sous_fenetre->show();
    }else
    if(verifier_nombre(input1->text())==true)
    {
        input_valide_joueur1(input1->text());
    }else
    {
        sous_fenetre->afficher1("Votre nombre est erroné",-2);
        input1->setFocus(Qt::TabFocusReason);
        sous_fenetre->show();
    }
}

void deux_joueurs::valider_joueur21()
{
    if(input2->text().isEmpty()==true)
    {
        sous_fenetre->afficher1("Vous n'avez entré aucun nombre",-1);
        input2->setFocus(Qt::TabFocusReason);
        sous_fenetre->show();
    }else
    if(verifier_nombre(input2->text())==true)
    {
        input_valide_joueur2(input2->text());
    }else
    {
        sous_fenetre->afficher1("Votre nombre est erroné",-2);
        input2->setFocus(Qt::TabFocusReason);
        sous_fenetre->show();
    }
}

void deux_joueurs::valider_joueur12()
{
    if((vache->currentText()=="1")&&(taureau->currentText()=="3"))
    {
        sous_fenetre->afficher1("Combinaison impossible",-2);
        sous_fenetre->show();
    }else
    {
        if(taureau->currentIndex()==4)
            gagner_joueur1=true;
        input_valide_joueur1(vache->currentIndex(),taureau->currentIndex());
    }
}

void deux_joueurs::valider_joueur22()
{
    if((vache->currentText()=="1")&&(taureau->currentText()=="3"))
    {
        sous_fenetre->afficher1("Combinaison impossible",-2);
        sous_fenetre->show();
    }else
    {
        if(taureau->currentIndex()==4)
            gagner_joueur2=true;
        input_valide_joueur2(vache->currentIndex(),taureau->currentIndex());
    }
}

void deux_joueurs::input_valide_joueur1(QString nombre)
{
    if(input1->isVisible()==true)
    {
        layout_joueur1->removeWidget(input1);
        input1->setVisible(false);
    }
    if(bouton_valider11->isVisible()==true)
    {
        layout_joueur1->removeWidget(bouton_valider11);
        bouton_valider11->setVisible(false);
    }

    message->setText("C'est le tour du Joueur 2.\nVeuillez saisir le nombre de vaches et de taureaux correspendant à la proposition du Joueur 1.");
    message->setStyleSheet("QLabel{color: rgb(29, 72, 81); font-size : 30px;border : 5px solid rgb(27, 1, 155); padding : 30%; font-family : ernesto}");

    messages1[ligne1-1][0]->setText(nombre);
    messages1[ligne1-1][0]->setVisible(true);
    layout_joueur1->addWidget(vache,ligne1,1);
    layout_joueur1->addWidget(taureau,ligne1,2);
    layout_joueur1->addWidget(bouton_valider12,ligne1,3);
    vache->setVisible(true);
    taureau->setVisible(true);
    vache->setCurrentIndex(0);
    taureau->setCurrentIndex(0);
    bouton_valider12->setVisible(true);
    bouton_valider12->setAutoDefault(true);
    bouton_valider12->setFocus(Qt::BacktabFocusReason);
}

void deux_joueurs::input_valide_joueur2(QString nombre)
{
    if(input2->isVisible()==true)
    {
        layout_joueur2->removeWidget(input2);
        input2->setVisible(false);
    }
    if(bouton_valider21->isVisible()==true)
    {
        layout_joueur2->removeWidget(bouton_valider21);
        bouton_valider21->setVisible(false);
    }

    message->setText("C'est le tour du Joueur 1.\nVeuillez saisir le nombre de vaches et de taureaux correspendant à la proposition du Joueur 2.");
    message->setStyleSheet("QLabel{color: rgb(29, 72, 81); font-size : 30px;border : 5px solid rgb(27, 1, 155); padding : 30%; font-family : ernesto}");

    messages2[ligne2-1][0]->setText(nombre);
    messages2[ligne2-1][0]->setVisible(true);
    layout_joueur2->addWidget(vache,ligne2,1);
    layout_joueur2->addWidget(taureau,ligne2,2);
    layout_joueur2->addWidget(bouton_valider22,ligne2,3);
    vache->setVisible(true);
    taureau->setVisible(true);
    vache->setCurrentIndex(0);
    taureau->setCurrentIndex(0);
    bouton_valider22->setVisible(true);
    bouton_valider22->setAutoDefault(true);
    bouton_valider22->setFocus(Qt::BacktabFocusReason);
}

void deux_joueurs::input_valide_joueur1(int Vache,int Taureau)
{
    if(vache->isVisible()==true)
    {
        layout_joueur1->removeWidget(vache);
        vache->setVisible(false);
    }
    if(taureau->isVisible()==true)
    {
        layout_joueur1->removeWidget(taureau);
        taureau->setVisible(false);
    }
    if(bouton_valider12->isVisible()==true)
    {
        layout_joueur1->removeWidget(bouton_valider12);
        bouton_valider12->setVisible(false);
    }

    messages1[ligne1-1][1]->setText(QString::number(Vache));
    messages1[ligne1-1][1]->setVisible(true);
    messages1[ligne1-1][2]->setText(QString::number(Taureau));
    messages1[ligne1-1][2]->setVisible(true);
    saisir_estimation_joueur2();
}

void deux_joueurs::input_valide_joueur2(int Vache,int Taureau)
{
    if(vache->isVisible()==true)
    {
        layout_joueur2->removeWidget(vache);
        vache->setVisible(false);
    }
    if(taureau->isVisible()==true)
    {
        layout_joueur2->removeWidget(taureau);
        taureau->setVisible(false);
    }
    if(bouton_valider22->isVisible()==true)
    {
        layout_joueur2->removeWidget(bouton_valider22);
        bouton_valider22->setVisible(false);
    }

    messages2[ligne2-1][1]->setText(QString::number(Vache));
    messages2[ligne2-1][1]->setVisible(true);
    messages2[ligne2-1][2]->setText(QString::number(Taureau));
    messages2[ligne2-1][2]->setVisible(true);

    if((gagner_joueur1==true)||(gagner_joueur2==true)||(ligne2==100))
    {
        message->setText("LA FIN DU JEU.");
        message->setStyleSheet("QLabel{color: rgb(29, 72, 81); font-size : 30px;border : 5px solid rgb(27, 1, 155); padding : 30%; font-family : ernesto}");
        if((gagner_joueur1==true)&&(gagner_joueur2==true))
        {
            sous_fenetre->afficher3("Egalité.",2);
        }else
        if(gagner_joueur1==true)
        {
            sous_fenetre->afficher3("Joueur 1 est le gagnant.",2);
        }else
        if(gagner_joueur2==true)
        {
            sous_fenetre->afficher3("Joueur 2 est le gagnant.",2);
        }else
        {
            sous_fenetre->afficher3("Pff il s'agit bien deux idiots.\nAlors, je vais arrêter le jeu.",1);
        }
        sous_fenetre->show();
    }else
    {
        saisir_estimation_joueur1();
    }
}

void deux_joueurs::modifier_taureau(int n)
{
    QString** tab=new QString* [5];
    tab[0] =new QString("0");
    tab[1] =new QString("1");
    tab[2] =new QString("2");
    tab[3] =new QString("3");
    tab[4] =new QString("4");

    int j=0,max=4;
    while(j<=max)
    {
        if(j+n>4)
        {
            taureau->removeItem(j);
            j--;
            max--;
        }
        j++;
    }

    for(j=0;j<=4;j++)
    {
        if(j+n<=4)
        {
            if(taureau->findText(*tab[j])==-1)
                taureau->addItem(*tab[j]);
        }

    }

     bouton_valider12->setAutoDefault(true);
     bouton_valider12->setFocus(Qt::BacktabFocusReason);
     bouton_valider22->setAutoDefault(true);
     bouton_valider22->setFocus(Qt::BacktabFocusReason);
     for(j=0;j<5;j++)
     {
         delete tab[j];
     }
     delete tab;
}

void deux_joueurs::modifier_vache(int n)
{
    QString** tab=new QString* [5];
    tab[0] =new QString("0");
    tab[1] =new QString("1");
    tab[2] =new QString("2");
    tab[3] =new QString("3");
    tab[4] =new QString("4");

    int j=0,max=4;
    while(j<=max)
    {
        if(j+n>4)
        {
            vache->removeItem(j);
            j--;
            max--;
        }
        j++;
    }

    for(j=0;j<=4;j++)
    {
        if(j+n<=4)
        {
            if(vache->findText(*tab[j])==-1)
                vache->addItem(*tab[j]);
        }

    }

    bouton_valider12->setAutoDefault(true);
    bouton_valider12->setFocus(Qt::BacktabFocusReason);
    bouton_valider22->setAutoDefault(true);
    bouton_valider22->setFocus(Qt::BacktabFocusReason);
    for(j=0;j<5;j++)
    {
        delete tab[j];
    }
    delete tab;
}

bool deux_joueurs::verifier_nombre(QString nombre)
{
    if(nombre[0]=='0')
        return false;
    if(nombre.length()!=4)
        return false;
    int i=0,j=0;
    for(i=0;i<4;i++)
    {
        if((nombre[i]<47)||(nombre[i]>57))
            return false;
    }
    i=0;
    while(i<3)
    {
        j=i+1;
        while(j<4)
        {
            if(nombre[i]==nombre[j])
                return false;
            else
                j++;
        }
        i++;
    }
    return true;
}
