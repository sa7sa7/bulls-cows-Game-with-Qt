#include "sous_fenetre.h"
#include "menu.h"
#include "calcul_estimation.h"
#include "sauvegarder.h"

Sous_fenetre::Sous_fenetre(menu *Parent):QWidget(Parent)
{
    parent=Parent;
    OK = new QPushButton("",this);
    OK->setStyleSheet("QPushButton{color: rgb(58, 142, 186); font-size : 25px; font-family : Oduda}");
    quitter = new QPushButton("&Quitter",this);
    quitter->setFixedSize(170,50);
    quitter->setStyleSheet("QPushButton{color: rgb(58, 142, 186); font-size : 25px; font-family : Oduda}");
    Menu = new QPushButton("&Menu",this);
    Menu->setFixedSize(170,50);
    Menu->setStyleSheet("QPushButton{color: rgb(58, 142, 186); font-size : 25px; font-family : Oduda}");
    Rejouer = new QPushButton("&Rejouer",this);
    Rejouer->setFixedSize(170,50);
    Rejouer->setStyleSheet("QPushButton{color: rgb(58, 142, 186); font-size : 25px; font-family : Oduda}");
    sauvegarde = new QPushButton("&Sauvegarder",this);
    sauvegarde->setFixedSize(170,50);
    sauvegarde->setStyleSheet("QPushButton{color: rgb(58, 142, 186); font-size : 25px; font-family : Oduda}");
    bouton_valider = new QPushButton("&Valider",this);
    bouton_valider->setFixedSize(135,40);
    bouton_valider->setStyleSheet("QPushButton{color: rgb(58, 142, 186); font-size : 25px; font-family : Oduda}");
    input=new QLineEdit(this);
    input->setMaxLength(4);
    input->setFixedSize(140,35);
    input->setStyleSheet("QLineEdit{font-size : 20px; font-family : Corbel}");

    vue = new QLabel("",this);

    layout = new QVBoxLayout(this);

    ligne=0;

    labels = new QLabel* [10];
    for(int i=0;i<10;i++)
    {
        labels[i]=new QLabel ("",this);
        labels[i]->setStyleSheet("QLabel{color: red; font-size : 20px; font-family : Corbel;}");
        labels[i]->setVisible(false);
        labels[i]->setFixedSize(450,40);
    }

    OK->setVisible(false);
    Rejouer->setVisible(false);
    Menu->setVisible(false);
    quitter->setVisible(false);
    sauvegarde->setVisible(false);
    bouton_valider->setVisible(false);
    vue->setVisible(false);
    input->setVisible(false);

    sauvegarder = new Sauvegarder(parent,this,layout);
    save_bool=false;
    continuer_temps=false;
    droit_de_quitter=false;

    setWindowModality(Qt::WindowModal);
    setWindowFlags(Qt::Dialog);
    QObject::connect(OK, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(bouton_valider, SIGNAL(clicked()), this, SLOT(valider()));
    QObject::connect(input, SIGNAL(returnPressed()), this, SLOT(valider()));
    QObject::connect(Rejouer, SIGNAL(clicked()), parent, SLOT(rejouer()));
    QObject::connect(Rejouer, SIGNAL(clicked()), this, SLOT(Quitter()));
    QObject::connect(sauvegarde, SIGNAL(clicked()), this, SLOT(Sauvegarde()));
    QObject::connect(Menu, SIGNAL(clicked()), this, SLOT(reafficher_menu()));
    QObject::connect(Menu, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(quitter, SIGNAL(clicked()), parent, SLOT(close()));
    QObject::connect(quitter, SIGNAL(clicked()), this, SLOT(Quitter()));
}

Sous_fenetre::~Sous_fenetre()
{
    delete labels;
}

void Sous_fenetre::effacer()
{
    for(int i=0;i<ligne;i++)
    {
        layout->removeWidget(labels[i]);
        labels[i]->setVisible(false);
        labels[i]->setText("");
    }

    if(OK->isVisibleTo(this)==true)
    {
        layout->removeWidget(OK);
        OK->setVisible(false);
        OK->setText("");
    }
    if(Rejouer->isVisibleTo(this)==true)
    {
        layout->removeWidget(Rejouer);
        Rejouer->setVisible(false);
    }
    if(sauvegarde->isVisibleTo(this)==true)
    {
        layout->removeWidget(sauvegarde);
        sauvegarde->setVisible(false);
    }
    if(Menu->isVisibleTo(this)==true)
    {
        layout->removeWidget(Menu);
        Menu->setVisible(false);
    }
    if(quitter->isVisibleTo(this)==true)
    {
        layout->removeWidget(quitter);
        quitter->setVisible(false);
    }
    if(vue->isVisibleTo(this)==true)
    {
        layout->removeWidget(vue);
        vue->setVisible(false);
    }
    if(bouton_valider->isVisibleTo(this)==true)
    {
        layout->removeWidget(bouton_valider);
        bouton_valider->setVisible(false);
    }
    if(input->isVisibleTo(this)==true)
    {
        layout->removeWidget(input);
        input->setVisible(false);
    }

    vue->setText("");
    input->setText("");

    droit_de_quitter=false;
    save_bool=false;
    continuer_temps=false;
    ligne=0;
}

void Sous_fenetre::pause(int mode)
{
    setWindowTitle("Pause");
    layout->addWidget(OK);
    OK->setText("&Continuer");
    OK->setVisible(true);
    OK->setAutoDefault(true);
    OK->setFixedSize(170,50);
    OK->setFocus(Qt::BacktabFocusReason);
    layout->setAlignment(OK,Qt::AlignCenter);
    layout->addWidget(Rejouer);
    Rejouer->setVisible(true);
    layout->setAlignment(Rejouer,Qt::AlignCenter);
    if(mode==1)
    {
        layout->addWidget(sauvegarde);
        sauvegarde->setVisible(true);
        layout->setAlignment(sauvegarde,Qt::AlignCenter);
        continuer_temps=true;
    }

    layout->addWidget(Menu);
    Menu->setVisible(true);
    layout->setAlignment(Menu,Qt::AlignCenter);
    layout->addWidget(quitter);
    quitter->setVisible(true);
    layout->setAlignment(quitter,Qt::AlignCenter);

    if(mode==1)
    {
        move(parent->x()+parent->width()/2-110,parent->y()+parent->height()/2-155);
        setFixedSize(220,310);
    }else
    {
        move(parent->x()+parent->width()/2-110,parent->y()+parent->height()/2-120);
        setFixedSize(220,240);
    }
    adjustSize();
}

void Sous_fenetre::afficher1(QString ch,int input)
{
    layout->addWidget(vue);
    vue->setVisible(true);
    vue->setText(ch);
    vue->setAlignment(Qt::AlignCenter);
    layout->addWidget(OK);
    OK->setText("&OK");
    OK->setVisible(true);
    OK->setAutoDefault(true);
    OK->setFixedSize(135,40);
    OK->setFocus(Qt::BacktabFocusReason);
    layout->setAlignment(OK,Qt::AlignCenter);
    if(input==-1)
    {
        setWindowTitle("Input érroné");
        vue->setStyleSheet("QLabel{color: rgb(29, 72, 81); font-size : 35px;border : 3px solid rgb(27, 1, 155); padding : 20%; font-family : ernesto}");
        vue->setAlignment(Qt::AlignCenter);
        move(parent->x()+parent->width()/2-275,parent->y()+parent->height()/2-77);
        setFixedSize(550,155);
    }else
    if(input==-2)
    {
        setWindowTitle("Input érroné");
        vue->setStyleSheet("QLabel{color: rgb(29, 72, 81); font-size : 35px;border : 3px solid rgb(27, 1, 155); padding : 20%; font-family : ernesto}");
        vue->setAlignment(Qt::AlignCenter);
        move(parent->x()+parent->width()/2-215,parent->y()+parent->height()/2-77);
        setFixedSize(430,155);
    }else
    if(input==-3)
    {
        setWindowTitle("Attention");
        vue->setStyleSheet("QLabel{color: rgb(29, 72, 81); font-size : 30px;border : 3px solid rgb(27, 1, 155); padding : 20%; font-family : ernesto}");
        vue->setAlignment(Qt::AlignCenter);
        move(parent->x()+parent->width()/2-225,parent->y()+parent->height()/2-90);
        setFixedSize(450,180);
    }else
    {
        setWindowTitle("Attention");
        vue->setStyleSheet("QLabel{color: rgb(29, 72, 81); font-size : 25px;border : 3px solid rgb(27, 1, 155); padding : 20%; font-family : ernesto}");
        vue->setAlignment(Qt::AlignLeft);
        setFixedSize(500,120+input*32);
    }
    adjustSize();
}

void Sous_fenetre::afficher2()
{
    setWindowTitle("Fin de partie");
    droit_de_quitter=true;
    layout->addWidget(vue);
    vue->setVisible(true);
    vue->setText("Je doute que vous avez commis une faute ou bien vous m'avez menti\nAlors,veuillez entrer votre numero pour verifier");
    vue->setStyleSheet("QLabel{color: rgb(29, 72, 81); font-size : 22px; border : 3px solid rgb(27, 1, 155); padding : 20%; font-family : ernesto}");
    vue->setAlignment(Qt::AlignCenter);
    layout->addWidget(input);
    input->setClearButtonEnabled(true);
    input->setFocus(Qt::TabFocusReason);
    input->setVisible(true);
    layout->setAlignment(input,Qt::AlignCenter);
    layout->addWidget(bouton_valider);
    bouton_valider->setVisible(true);
    layout->setAlignment(bouton_valider,Qt::AlignCenter);
    move(parent->x()+parent->width()/2-345,parent->y()+parent->height()/2-105);
    setFixedSize(690,210);
    adjustSize();
}

void Sous_fenetre::valider()
{
    if(verifier_input(input->text())==true)
    {
        input_valide(input->text());
    }
}

void Sous_fenetre::input_valide(QString nombre)
{
    char** M=NULL;
    ligne=0;
    vue->setText("Liste des déclarations incorrectes: ");
    vue->setStyleSheet("QLabel{color: rgb(29, 72, 81); font-size : 30px; border : 3px solid rgb(27, 1, 155); padding : 15%; font-family : ernesto}");

    if(bouton_valider->isVisibleTo(this)==true)
    {
        layout->removeWidget(bouton_valider);
        bouton_valider->setVisible(false);
    }
    if(input->isVisibleTo(this)==true)
    {
        layout->removeWidget(input);
        input->setVisible(false);
    }

    M=generateur_des_estimations->mentir(nombre,ligne);
    for(int i=0;i<ligne;i++)
    {
        labels[i]->setText(M[i]);
        labels[i]->setVisible(true);
        layout->addWidget(labels[i]);
        delete M[i];
    }
    delete M;

    layout->addWidget(Rejouer);
    Rejouer->setVisible(true);
    Rejouer->setAutoDefault(true);
    Rejouer->setFocus(Qt::BacktabFocusReason);
    layout->setAlignment(Rejouer,Qt::AlignCenter);
    layout->addWidget(Menu);
    Menu->setVisible(true);
    layout->setAlignment(Menu,Qt::AlignCenter);
    layout->addWidget(quitter);
    quitter->setVisible(true);

    layout->setAlignment(quitter,Qt::AlignCenter);
    if((x()==parent->x()+parent->width()/2-345)&&(y()==parent->y()+parent->height()/2-105))
    {
        move(parent->x()+parent->width()/2-250,parent->y()+parent->height()/2-135-ligne*22);
    }
    setFixedSize(500,270+ligne*45);
    adjustSize();
}

bool Sous_fenetre::verifier_input(QString nombre)
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

void Sous_fenetre::afficher3(QString ch,int input)
{
    setWindowTitle("Fin de partie");
    droit_de_quitter=true;
    layout->addWidget(vue);
    vue->setVisible(true);
    vue->setText(ch);
    vue->setStyleSheet("QLabel{color: rgb(29, 72, 81); font-size : 40px;border : 3px solid rgb(27, 1, 155); padding : 20%; font-family : ernesto}");
    layout->addWidget(Rejouer);
    Rejouer->setVisible(true);
    Rejouer->setAutoDefault(true);
    Rejouer->setFocus(Qt::BacktabFocusReason);
    layout->setAlignment(Rejouer,Qt::AlignCenter);
    layout->addWidget(Menu);
    Menu->setVisible(true);
    layout->setAlignment(Menu,Qt::AlignCenter);
    layout->addWidget(quitter);
    quitter->setVisible(true);
    layout->setAlignment(quitter,Qt::AlignCenter);

    if(input==1)
    {
        vue->setAlignment(Qt::AlignCenter);
        move(parent->x()+parent->width()/2-250,parent->y()+parent->height()/2-175);
        setFixedSize(500,350);
    }else
    {
        vue->setAlignment(Qt::AlignCenter);
        move(parent->x()+parent->width()/2-200,parent->y()+parent->height()/2-155);
        setFixedSize(400,310);
    }
    adjustSize();
}

void Sous_fenetre::afficher4(QString temps)
{
    droit_de_quitter=true;

    QFile file("Score.save");
    QString** tab=new QString* [10];
    tab[0] =new QString("");
    tab[1] =new QString("");
    tab[2] =new QString("");
    tab[3] =new QString("");
    tab[4] =new QString("");
    tab[5] =new QString("");
    tab[6] =new QString("");
    tab[7] =new QString("");
    tab[8] =new QString("");
    tab[9] =new QString("");
    int a,b,c,d,j=0;
    int position=10;
    if(file.exists()==true)
    {
        file.open(QIODevice::ReadOnly);
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out>>a;out>>b;out>>c;out>>d;
        QString reste("");
        for(int i=0;i<10;i++)
        {
            out>>reste;
            out>>(*tab[i]);
        }
        file.close();

        for(int i=0;i<10;i++)
        {
            if(i==0)
            {
                if((*tab[i])>temps)
                {
                    position=i;
                    break;
                }
            }else
            {
                if(((*tab[i-1])<temps)&&((*tab[i])>temps))
                {
                    position=i;
                    break;
                }
            }
        }
        file.close();

        file.open(QIODevice::WriteOnly);
        out<<a<<"\n"<<b<<"\n"<<c<<"\n"<<d<<"\n";
        for(int i=0;i<10;i++)
        {
            if(i!=9)
            {
                if(i!=position)
                {
                    out<<"score"<<i+1<<" "<<(*tab[j])<<"\n";
                    j++;
                }else
                {
                    out<<"score"<<i+1<<" "<<temps<<"\n";
                }
            }else
            {
                if(i!=position)
                {
                    out<<"score"<<i+1<<" "<<(*tab[j]);
                    j++;
                }else
                {
                    out<<"score"<<i+1<<" "<<temps;
                }
            }

        }
        out.flush();
        file.close();
    }

    if(position!=10)
    {
        layout->addWidget(vue);
        vue->setVisible(true);
        vue->setText("BRAVO\nVous avez gagné avec un reccord.");
        vue->setStyleSheet("QLabel{color: rgb(29, 72, 81); font-size : 35px;border : 3px solid rgb(27, 1, 155); padding : 20%; font-family : ernesto}");
    }else
    {
        layout->addWidget(vue);
        vue->setVisible(true);
        vue->setText("BRAVO\n Vous avez gagné.");
        vue->setStyleSheet("QLabel{color: rgb(29, 72, 81); font-size : 40px;border : 3px solid rgb(27, 1, 155); padding : 20%; font-family : ernesto}");
    }
    layout->addWidget(Rejouer);
    Rejouer->setVisible(true);
    Rejouer->setAutoDefault(true);
    Rejouer->setFocus(Qt::BacktabFocusReason);
    layout->setAlignment(Rejouer,Qt::AlignCenter);
    layout->addWidget(Menu);
    Menu->setVisible(true);
    layout->setAlignment(Menu,Qt::AlignCenter);
    layout->addWidget(quitter);
    quitter->setVisible(true);
    layout->setAlignment(quitter,Qt::AlignCenter);

    vue->setAlignment(Qt::AlignCenter);
    move(parent->x()+parent->width()/2-250,parent->y()+parent->height()/2-175);
    setFixedSize(500,350);

    for(int i=0;i<10;i++)
    {
        delete tab[i];
    }
    delete tab;
}

void Sous_fenetre::Quitter()
{
    droit_de_quitter=false;
    close();
}

void Sous_fenetre::Sauvegarde()
{
    effacer();
    save_bool=true;
    continuer_temps=true;
    sauvegarder->preexecuter();
}

void Sous_fenetre::reafficher_menu()
{
    droit_de_quitter=true;
}

void Sous_fenetre::closeEvent(QCloseEvent* event)
{
    QWidget::closeEvent(event);
    bool coin=true;

    if(droit_de_quitter==true)
    {
        parent->reafficher();
        coin=false;
    }

    if((coin==true)&&(continuer_temps==true))
    {
        parent->modifier_pause();
    }

    if(save_bool==false)
        effacer();
    else
    {
        save_bool=false;
        sauvegarder->effacer();
    }
}

void Sous_fenetre::set_generateur(calcul_estimation* generateur)
{
    generateur_des_estimations=generateur;
}
