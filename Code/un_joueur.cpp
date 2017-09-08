#include "un_joueur.h"
#include "menu.h"
#include "sous_fenetre.h"
#include "calcul_estimation.h"

un_joueur::un_joueur(menu *Parent, QGridLayout *Layout, Sous_fenetre *fenetre):QObject()
{
    parent=Parent;
    layout_principale=Layout;
    sous_fenetre=fenetre;

    bouton_valider1 = new QPushButton("&valider",parent);
    bouton_valider1->setStyleSheet("QPushButton{color: rgb(58, 142, 186); font-size : 25px; font-family : Oduda}");
    bouton_valider1->setFixedSize(135,40);
    bouton_valider2 = new QPushButton("&valider",parent);
    bouton_valider2->setStyleSheet("QPushButton{color: rgb(58, 142, 186); font-size : 25px; font-family : Oduda}");
    bouton_valider2->setFixedSize(135,40);
    bouton_pause = new QPushButton("",parent);
    bouton_pause->setMask(QRegion(QRect(bouton_pause->x()+5,bouton_pause->y()+5,70,70),QRegion::Ellipse));
    bouton_pause->setIcon(QPixmap("Images\\icone.jpg"));
    bouton_pause->setFixedSize(80,80);
    bouton_pause->setIconSize(QSize(70,70));
    bouton_pause->setCursor(Qt::PointingHandCursor);

    input = new QLineEdit(parent);
    input->setMaxLength(4);
    input->setFixedSize(140,35);
    input->setStyleSheet("QLineEdit{color: red; font-size : 20px; font-family : Corbel}");

    vache = new QComboBox(parent);
    vache->addItem("0");
    vache->addItem("1");
    vache->addItem("2");
    vache->addItem("3");
    vache->addItem("4");
    vache->setStyleSheet("QComboBox{font-size : 20px; font-family : Corbel}");
    vache->setFixedSize(145,35);

    taureau = new QComboBox(parent);
    taureau->addItem("0");
    taureau->addItem("1");
    taureau->addItem("2");
    taureau->addItem("3");
    taureau->addItem("4");
    taureau->setStyleSheet("QComboBox{font-size : 20px; font-family : Corbel}");
    taureau->setFixedSize(145,35);

    layout_joueur = new QGridLayout;
    layout_boot = new QGridLayout;
    layout_joueur->setRowStretch(20,10);
    layout_boot->setRowStretch(20,10);

    labels= new QLabel* [8];
    labels[0] = new QLabel ("Votre estimation",parent);
    labels[0]->setFixedSize(150,40);
    labels[0]->setStyleSheet("QLabel{color: rgb(58, 142, 186); font-size : 17px; font-family : Calibri}");
    layout_joueur->addWidget(labels[0],0,0);
    labels[1] = new QLabel ("Nombre de Vaches",parent);
    labels[1]->setFixedSize(150,40);
    labels[1]->setStyleSheet("QLabel{color: rgb(58, 142, 186); font-size : 17px; font-family : Calibri}");
    layout_joueur->addWidget(labels[1],0,1);
    labels[2] = new QLabel ("Nombre de Taureaux",parent);
    labels[2]->setFixedSize(150,40);
    labels[2]->setStyleSheet("QLabel{color: rgb(58, 142, 186); font-size : 17px; font-family : Calibri}");
    layout_joueur->addWidget(labels[2],0,2);
    labels[3] = new QLabel ("",parent);
    labels[3]->setFixedSize(150,40);
    layout_joueur->addWidget(labels[3],0,3);

    labels[4] = new QLabel ("Mon estimation",parent);
    labels[4]->setFixedSize(150,40);
    labels[4]->setStyleSheet("QLabel{color: rgb(58, 142, 186); font-size : 17px; font-family : Calibri}");
    layout_boot->addWidget(labels[4],0,0);
    labels[5] = new QLabel ("Nombre de Vaches",parent);
    labels[5]->setFixedSize(150,40);
    labels[5]->setStyleSheet("QLabel{color: rgb(58, 142, 186); font-size : 17px; font-family : Calibri}");
    layout_boot->addWidget(labels[5],0,1);
    labels[6] = new QLabel ("Nombre de Taureaux",parent);
    labels[6]->setFixedSize(150,40);
    labels[6]->setStyleSheet("QLabel{color: rgb(58, 142, 186); font-size : 17px; font-family : Calibri}");
    layout_boot->addWidget(labels[6],0,2);
    labels[7] = new QLabel ("",parent);
    labels[7]->setFixedSize(150,40);
    layout_boot->addWidget(labels[7],0,3);

    messages1= new QLabel** [10];
    for(int i=0;i<10;i++)
    {
        messages1[i]=new QLabel* [3];
        for(int j=0;j<3;j++)
        {
            messages1[i][j]=new QLabel("",parent);
            if(j==0)
                messages1[i][j]->setStyleSheet("QLabel{color: red; font-size : 20px; font-family : Corbel}");
            else
                messages1[i][j]->setStyleSheet("QLabel{font-size : 20px; font-family : Corbel}");
            layout_joueur->addWidget(messages1[i][j],i+1,j);
            messages1[i][j]->setVisible(false);
            messages1[i][j]->setFixedSize(150,40);
        }
    }

    messages2= new QLabel** [10];
    for(int i=0;i<10;i++)
    {
        messages2[i]=new QLabel* [3];
        for(int j=0;j<3;j++)
        {
            messages2[i][j]=new QLabel("",parent);
            if(j==0)
                messages2[i][j]->setStyleSheet("QLabel{color: red; font-size : 20px; font-family : Corbel}");
            else
                messages2[i][j]->setStyleSheet("QLabel{font-size : 20px; font-family : Corbel}");
            layout_boot->addWidget(messages2[i][j],i+1,j);
            messages2[i][j]->setVisible(false);
            messages2[i][j]->setFixedSize(150,40);
        }
    }

    message= new QLabel ("",parent);
    message->setAlignment(Qt::AlignCenter);
    message->setFixedHeight(150);

    temps = new QLabel("00:00",parent);
    temps->setAlignment(Qt::AlignCenter);
    temps->setFixedSize(100,100);
    temps->setStyleSheet("QLabel{font-size : 30px; font-family : Corbel}");
    temps_compteur = new QTimeLine (60*60*1000,parent);
    temps_compteur->setCurveShape(QTimeLine::LinearCurve);
    temps_compteur->setUpdateInterval(50);
    layout= new QHBoxLayout;
    layout->addWidget(bouton_pause);
    layout->addWidget(message);
    layout->addWidget(temps);

    box_joueur = new QGroupBox ("Vos Estiamtions",parent);
    box_joueur->setFixedSize(625,600);
    box_joueur->setStyleSheet("QGroupBox{color: rgb(34, 66, 124); font-size : 40px; font-family : Chalk Marks}");
    box_joueur->setLayout(layout_joueur);
    box_boot = new QGroupBox ("Mes Estimations",parent);
    box_boot->setFixedSize(625,600);
    box_boot->setStyleSheet("QGroupBox{color: rgb(34, 66, 124); font-size : 40px; font-family : Chalk Marks}");  
    box_boot->setLayout(layout_boot);

    bouton_valider1->setVisible(false);
    bouton_valider2->setVisible(false);
    bouton_pause->setVisible(false);
    input->setVisible(false);
    vache->setVisible(false);
    taureau->setVisible(false);
    box_boot->setVisible(false);
    box_joueur->setVisible(false);
    temps->setVisible(false);
    message->setVisible(false);

    boot_nombre= new char [5];
    boot_nombre[4]='\0';
    N= new char [5];
    N[0]='*';
    N[1]='*';
    N[2]='*';
    N[3]='*';
    N[4]='\0';
    generateur_des_estimations=NULL;

    QObject::connect(bouton_pause, SIGNAL(clicked()), this, SLOT(pause()));
    QObject::connect(bouton_valider1, SIGNAL(clicked()), this, SLOT(valider1()));
    QObject::connect(bouton_valider2, SIGNAL(clicked()), this, SLOT(valider2()));
    QObject::connect(input, SIGNAL(returnPressed()), this, SLOT(valider1()));
    QObject::connect(vache,SIGNAL(currentIndexChanged(int)),this, SLOT(modifier_taureau(int)));
    QObject::connect(taureau,SIGNAL(currentIndexChanged(int)),this, SLOT(modifier_vache(int)));
    QObject::connect(temps_compteur, SIGNAL(valueChanged(qreal)), this, SLOT(changer()));
}

un_joueur::~un_joueur()
{
    delete boot_nombre;
    delete N;
    delete generateur_des_estimations;
    delete layout_joueur;
    delete layout_boot;
    delete labels;
    delete layout;
    for(int i=0;i<10;i++)
    {
        delete messages1[i];
    }
    delete messages1;
    for(int i=0;i<10;i++)
    {
        delete messages2[i];
    }
    delete messages2;
}

void un_joueur::executer()
{
    droit_incementer=true;
    fin_de_partie(0);
    if(generateur_des_estimations!=NULL)
        delete generateur_des_estimations;
    generateur_des_estimations= new calcul_estimation;
    sous_fenetre->set_generateur(generateur_des_estimations);
    generateur_des_estimations->copier_un_nombre(boot_nombre,generateur_des_estimations->estimation_en_cours());

    gagner_joueur= false;
    gagner_boot=false;
    temps_compteur->start();
    ligne1=0;
    ligne2=0;
    colonne=0;
    layout_principale->addLayout(layout,0,0,1,2);
    layout_principale->addWidget(box_joueur,1,0);
    layout_principale->addWidget(box_boot,1,1);
    bouton_pause->setVisible(true);
    temps->setVisible(true);
    message->setVisible(true);
    box_boot->setVisible(true);
    box_joueur->setVisible(true);
    saisir_estimation_joueur(0);
}

void un_joueur::executer(QString file_name)
{
    droit_incementer=false;
    QString chaine("");
    int i,j,limite,boulean;
    qint64 position;

    QFile file("Sauvegardes\\"+file_name+".VTsave");
    file.open(QIODevice::ReadOnly);
    QTextStream out(&file);

    out>>ligne1;
    out>>ligne2;
    out>>colonne;
    out>>boulean;
    if(boulean==1)
        gagner_joueur=true;
    else
        gagner_joueur=false;

    out>>boulean;
    if(boulean==1)
        gagner_boot=true;
    else
        gagner_boot=false;

    out>>boot_nombre;
    out>>N;
    out>>i;
    temps_compteur->setCurrentTime(i);

    out>>boulean;
    if(boulean==1)
    {
        out>>chaine;
        if(chaine!="****")
            input->setText(chaine);
    }else
    {
        out>>i;
        vache->setCurrentIndex(i);
        out>>i;
        taureau->setCurrentIndex(i);
    }

    if((ligne1!=1)||(ligne2!=0))
    {
        if(ligne1!=ligne2)
            limite=ligne1-1;
        else
            limite=ligne1;

        for(i=0;i<limite;i++)
        {
            for(j=0;j<3;j++)
            {
                    out>>chaine;
                    messages1[i][j]->setText(chaine);
                    messages1[i][j]->setVisible(true);
            }
        }

        for(i=0;i<ligne2;i++)
        {
            if(i!=ligne2-1)
            {
                for(j=0;j<3;j++)
                {
                    out>>chaine;
                    messages2[i][j]->setText(chaine);
                    messages2[i][j]->setVisible(true);
                }
            }else
            {
                for(j=0;j<colonne;j++)
                {
                    out>>chaine;
                    messages2[i][j]->setText(chaine);
                    messages2[i][j]->setVisible(true);
                }
            }
        }
    }

    position=out.pos();
    file.close();

    if(generateur_des_estimations!=NULL)
        delete generateur_des_estimations;
    generateur_des_estimations= new calcul_estimation(file_name,position);
    sous_fenetre->set_generateur(generateur_des_estimations);

    temps_compteur->resume();

    layout_principale->addLayout(layout,0,0,1,2);
    layout_principale->addWidget(box_joueur,1,0);
    layout_principale->addWidget(box_boot,1,1);
    bouton_pause->setVisible(true);
    temps->setVisible(true);
    message->setVisible(true);
    box_boot->setVisible(true);
    box_joueur->setVisible(true);

    if(ligne1!=ligne2)
        saisir_estimation_joueur(1);
    else
        saisir_vache_taureau(1);
}

void un_joueur::sauvegarder(QString file_name)
{
    QFile file("Sauvegardes\\"+file_name+".VTsave");
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    out.setCodec("UTF-8");

    out<<ligne1<<"\n";
    out<<ligne2<<"\n";
    out<<colonne<<"\n";
    out<<gagner_joueur<<" "<<gagner_boot<<"\n";
    out<<boot_nombre<<"\n";
    out<<N<<"\n";
    out<<temps_compteur->currentTime()<<"\n";

    if(ligne1!=ligne2)
    {
        if(input->text()!="")
            out<<1<<" "<<input->text()<<"\n";
        else
            out<<1<<" ****\n";
    }
    else
        out<<2<<" "<<vache->currentIndex()<<" "<<taureau->currentIndex()<<"\n";

    int i,j;
    for(i=0;i<ligne1;i++)
    {
        for(j=0;j<3;j++)
        {
            if(messages1[i][j]->text()!="")
                out<<messages1[i][j]->text()<<" ";
        }
    }

    if(messages1[0][0]->text()!="")
        out<<"\n";

    for(i=0;i<ligne2;i++)
    {
        if(i!=ligne2-1)
        {
            for(j=0;j<3;j++)
            {
                out<<messages2[i][j]->text()<<" ";
            }
        }else
        {
            for(j=0;j<colonne;j++)
            {
                out<<messages2[i][j]->text()<<" ";
            }
        }
    }

    if(ligne2!=0)
        out<<"\n";

    out.flush();
    file.close();

    generateur_des_estimations->sauvegarder(file_name);
}

void un_joueur::effacer()
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
        if(i!=ligne2-1)
        {
            for(j=0;j<3;j++)
            {
                messages2[i][j]->setText("");
                messages2[i][j]->setVisible(false);
            }
        }else
        {
            for(j=0;j<colonne;j++)
            {
                messages2[i][j]->setText("");
                messages2[i][j]->setVisible(false);
            }
        }
    }

    if(vache->isVisible()==true)
    {
        layout_boot->removeWidget(vache);
        vache->setVisible(false);
    }
    if(taureau->isVisible()==true)
    {
        layout_boot->removeWidget(taureau);
        taureau->setVisible(false);
    }
    if(bouton_valider2->isVisible()==true)
    {
        layout_boot->removeWidget(bouton_valider2);
        bouton_valider2->setVisible(false);
    }

    if(input->isVisible()==true)
    {
        layout_joueur->removeWidget(input);
        input->setVisible(false);
    }
    if(bouton_valider1->isVisible()==true)
    {
        layout_joueur->removeWidget(bouton_valider1);
        bouton_valider1->setVisible(false);
    }

    layout_principale->removeItem(layout);
    bouton_pause->setVisible(false);
    message->setVisible(false);
    temps->setVisible(false);
    layout_principale->removeWidget(box_joueur);
    box_joueur->setVisible(false);
    layout_principale->removeWidget(box_boot);
    box_boot->setVisible(false);
    temps_compteur->stop();
    temps_compteur->setCurrentTime(0);
    temps->setText("00:00");
    input->setText("");
    vache->setCurrentIndex(0);
    taureau->setCurrentIndex(0);
    N[0]='*';
    N[1]='*';
    N[2]='*';
    N[3]='*';
}

void un_joueur::saisir_estimation_joueur(int mode)
{
    if(mode==0)
    {
        ligne1++;
        input->setText("");
    }
    message->setText("C'est votre tour.\nEssayez de trouver mon nombre en proposant un autre nombre.");
    message->setStyleSheet("QLabel{color: rgb(29, 72, 81); font-size : 30px;border : 5px solid rgb(27, 1, 155); padding : 30%; font-family : ernesto}");  
    layout_joueur->addWidget(input,ligne1,0);
    layout_joueur->addWidget(bouton_valider1,ligne1,3);
    bouton_valider1->setVisible(true);
    input->setVisible(true);
    input->setClearButtonEnabled(true);
    input->setFocus(Qt::TabFocusReason);
}

void un_joueur::saisir_vache_taureau(int mode)
{
    message->setText("C'est mon tour.\nVeuilez saisir le nombre de vaches et de taureaux dans mon nombre estimé.");
    message->setStyleSheet("QLabel{color: rgb(29, 72, 81); font-size : 30px;border : 5px solid rgb(27, 1, 155); padding : 30%; font-family : ernesto}");

    if(colonne==3)
        colonne=0;

    if(mode==0)
    {
        ligne2++;
        generateur_des_estimations->copier_un_nombre(N,generateur_des_estimations->estimation_en_cours());
        messages2[ligne2-1][colonne]->setText(N);
        messages2[ligne2-1][colonne]->setVisible(true);
        vache->setCurrentIndex(0);
        taureau->setCurrentIndex(0);
        colonne++;
    }

    layout_boot->addWidget(vache,ligne2,1);
    layout_boot->addWidget(taureau,ligne2,2);
    layout_boot->addWidget(bouton_valider2,ligne2,3);

    vache->setVisible(true);
    taureau->setVisible(true);
    bouton_valider2->setVisible(true);
    bouton_valider2->setAutoDefault(true);
    bouton_valider2->setFocus(Qt::BacktabFocusReason);
}

void un_joueur::pause()
{
    temps_compteur->setPaused(true);
    sous_fenetre->pause(1);
    message->setText("PAUSE!!");
    message->setStyleSheet("QLabel{color: rgb(29, 72, 81); font-size : 50px;border : 5px solid rgb(27, 1, 155); padding : 30%; font-family : ernesto}");
    box_boot->setVisible(false);
    box_joueur->setVisible(false);
    sous_fenetre->show();
}

void un_joueur::modifier_pause()
{
    if(ligne1==ligne2)
    {
        message->setText("C'est mon tour.\nVeuilez saisir le nombre de vaches et de taureaux dans mon nombre estimé.");
        message->setStyleSheet("QLabel{color: rgb(29, 72, 81); font-size : 30px;border : 5px solid rgb(27, 1, 155); padding : 30%; font-family : ernesto}");
    }else
    {
        message->setText("C'est votre tour.\nEssayez de trouver mon nombre en proposant un autre nombre.");
        message->setStyleSheet("QLabel{color: rgb(29, 72, 81); font-size : 30px;border : 5px solid rgb(27, 1, 155); padding : 30%; font-family : ernesto}");
    }
    temps_compteur->setPaused(false);
    box_boot->setVisible(true);
    box_joueur->setVisible(true);
    input->setFocus(Qt::TabFocusReason);
    bouton_valider2->setAutoDefault(true);
    bouton_valider2->setFocus(Qt::BacktabFocusReason);
}

void un_joueur::valider1()
{
    if(input->text().isEmpty()==true)
    {
        sous_fenetre->afficher1("Vous n'avez entré aucun nombre",-1);
        input->setFocus(Qt::TabFocusReason);
        sous_fenetre->show();
    }else
    if(verifier_nombre(input->text())==true)
    {
        input_valide1(input->text());
    }else
    {
        sous_fenetre->afficher1("Votre nombre est erroné",-2);
        input->setFocus(Qt::TabFocusReason);
        sous_fenetre->show();
    }
}

void un_joueur::valider2()
{
    if((vache->currentText()=="1")&&(taureau->currentText()=="3"))
    {
        sous_fenetre->afficher1("Combinaison impossible",-2);
        sous_fenetre->show();
    }else
    {
        if(taureau->currentIndex()==4)
            gagner_boot=true;
        input_valide2(vache->currentIndex(),taureau->currentIndex());
    }

}

bool un_joueur::verifier_nombre(QString nombre)
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

void un_joueur::input_valide1(QString nombre)
{
    if(input->isVisible()==true)
    {
        layout_joueur->removeWidget(input);
        input->setVisible(false);
    }
    if(bouton_valider1->isVisible()==true)
    {
        layout_joueur->removeWidget(bouton_valider1);
        bouton_valider1->setVisible(false);
    }

    int T=calcul_taureaux(boot_nombre,nombre);
    messages1[ligne1-1][0]->setText(nombre);
    messages1[ligne1-1][0]->setVisible(true);
    messages1[ligne1-1][1]->setText(QString::number(calcul_vaches(boot_nombre,nombre)));
    messages1[ligne1-1][1]->setVisible(true);
    messages1[ligne1-1][2]->setText(QString::number(T));
    messages1[ligne1-1][2]->setVisible(true);

    if(T==4)
        gagner_joueur=true;
    saisir_vache_taureau(0);
}

void un_joueur::input_valide2(int Vache,int Taureau)
{
    if(vache->isVisible()==true)
    {
        layout_boot->removeWidget(vache);
        vache->setVisible(false);
    }
    if(taureau->isVisible()==true)
    {
        layout_boot->removeWidget(taureau);
        taureau->setVisible(false);
    }
    if(bouton_valider2->isVisible()==true)
    {
        layout_boot->removeWidget(bouton_valider2);
        bouton_valider2->setVisible(false);
    }

    messages2[ligne2-1][colonne]->setText(QString::number(Vache));
    messages2[ligne2-1][colonne]->setVisible(true);
    colonne++;
    messages2[ligne2-1][colonne]->setText(QString::number(Taureau));
    messages2[ligne2-1][colonne]->setVisible(true);
    colonne++;
    generateur_des_estimations->ajouter_estimation(N,Vache,Taureau);
    generateur_des_estimations->traitement();

    int nombre_des_effectif;
    nombre_des_effectif=generateur_des_estimations->calcul_effectif();
    if((nombre_des_effectif==0)||(gagner_boot==true)||(gagner_joueur==true))
    {
        message->setText("LA FIN DU JEU.");
        temps_compteur->setPaused(true);
        message->setStyleSheet("QLabel{color: rgb(29, 72, 81); font-size : 30px;border : 5px solid rgb(27, 1, 155); padding : 30%; font-family : ernesto}");
        if(nombre_des_effectif==0)
        {
            sous_fenetre->afficher2();
            fin_de_partie(2);
        }else
        if((gagner_boot==true)&&(gagner_joueur==true))
        {
            sous_fenetre->afficher3("Egalité.",2);
            fin_de_partie(3);
        }else
        if(gagner_boot==true)
        {
            sous_fenetre->afficher3("Je suis le gagnant.\n Mon nombre est "+QString(boot_nombre)+".",1);
            fin_de_partie(2);
        }else
        if(gagner_joueur==true)
        {
            if(droit_incementer==true)
                sous_fenetre->afficher4(temps->text());
            else
                sous_fenetre->afficher3("BRAVO\n Vous avez gagné.",1);
            fin_de_partie(1);
        }
        sous_fenetre->show();
    }else
    {
        saisir_estimation_joueur(0);
    }
}

void un_joueur::fin_de_partie(int mode)
{
    QFile file("Score.save");
    int a,b,c,d;
    if((file.exists()==true)&&(droit_incementer==true))
    {
        file.open(QIODevice::ReadOnly);
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out>>a;
        out>>b;
        out>>c;
        out>>d;
        switch (mode)
        {
            case 1:{b++;}break;
            case 2:{c++;}break;
            case 3:{d++;}break;
            default:a++;break;
        }
        QString reste("");
        reste=out.readAll();
        file.close();
        file.open(QIODevice::WriteOnly);
        out<<a<<"\n"<<b<<"\n"<<c<<"\n"<<d;

        out<<reste;
        out.flush();
        file.close();
    }
}

int un_joueur::calcul_vaches(char* nombre1,QString nombre2)
{
    int i,j,resultat=0;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if((nombre1[i]==nombre2[j])&&(i!=j))
                resultat++;
        }
    }
    return resultat;
}

int un_joueur::calcul_taureaux(char* nombre1,QString nombre2)
{
    int i,resultat=0;
    for(i=0;i<4;i++)
    {
        if(nombre1[i]==nombre2[i])
            resultat++;
    }
    return resultat;
}

void un_joueur::modifier_taureau(int n)
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

     bouton_valider2->setAutoDefault(true);
     bouton_valider2->setFocus(Qt::BacktabFocusReason);
     for(j=0;j<5;j++)
     {
         delete tab[j];
     }
     delete tab;
}

void un_joueur::modifier_vache(int n)
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

    bouton_valider2->setAutoDefault(true);
    bouton_valider2->setFocus(Qt::BacktabFocusReason);
    for(j=0;j<5;j++)
    {
        delete tab[j];
    }
    delete tab;
}

void un_joueur::changer()
{
    long l=temps_compteur->currentTime();
    QString min(QString::number(l/60000));
    if(min.length()==1)
        min="0"+min;

    QString sec(QString::number(l%60000));

    if(sec.length()==5)
    {
        sec.remove(sec.length()-3,3);
        temps->setText(min+":"+sec);
    }else
    if(sec.length()==4)
    {
        sec.remove(sec.length()-3,3);
        sec="0"+sec;
        temps->setText(min+":"+sec);
    }else
    if(sec.length()==3)
    {
        temps->setText(min+":00");
    }
}
