#include "calcul_estimation.h"
#include "tableau_des_estimations.h"

calcul_estimation::calcul_estimation()
{
    srand(time(NULL));
    nombre_des_groupes_certains=210;
    int i,x=0,y=1,z=2,w=3;
    groupe_des_chiffres= new Groupe_des_chiffres [nombre_des_groupes_certains];
    for(i=0;i<nombre_des_groupes_certains;i++)
    {
        groupe_des_chiffres[i].groupe=new char [5];
        groupe_des_chiffres[i].groupe[4]='\0';
        groupe_des_chiffres[i].certain=true;
        groupe_des_chiffres[i].liste_des_nombres_du_groupe=NULL;
        groupe_des_chiffres[i].effectif_des_nombres=0;
    }

    i=0;
    bool coin=true;
    do
    {
        coin=true;
        groupe_des_chiffres[i].groupe[0]=48+x;
        groupe_des_chiffres[i].groupe[1]=48+y;
        groupe_des_chiffres[i].groupe[2]=48+z;
        groupe_des_chiffres[i].groupe[3]=48+w;
        i++;
        w++;

        if((y==7)&&(coin==true))
        {
            x++;
            y=x+1;
            z=y+1;
            w=z+1;
            coin=false;
        }

        if((z==8)&&(coin==true))
        {
            y++;
            z=y+1;
            w=z+1;
            coin=false;
        }

        if((w==10)&&(coin==true))
        {
            z++;
            w=z+1;
            coin=false;
        }

    }while(x<=6);

    for(i=0;i<nombre_des_groupes_certains;i++)
    {
        construire_liste_des_nombres_du_groupe(i);
    }
    tableau_des_estimation=new tableau();
}

calcul_estimation::calcul_estimation(QString file_name,qint64 pos)
{
    srand(time(NULL));
    qint64 position;
    QFile file("Sauvegardes\\"+file_name+".VTsave");
    file.open(QIODevice::ReadOnly);
    QTextStream out(&file);
    out.setCodec("UTF-8");
    out.seek(pos);
    out>>nombre_des_groupes_certains;

    int i,j;
    groupe_des_chiffres= new Groupe_des_chiffres [nombre_des_groupes_certains];
    for(i=0;i<nombre_des_groupes_certains;i++)
    {
        groupe_des_chiffres[i].groupe=new char [5];
        out>>groupe_des_chiffres[i].groupe;
        groupe_des_chiffres[i].certain=true;
        groupe_des_chiffres[i].liste_des_nombres_du_groupe=NULL;
        groupe_des_chiffres[i].effectif_des_nombres=0;
    }

    for(i=0;i<nombre_des_groupes_certains;i++)
    {
        out>>groupe_des_chiffres[i].effectif_des_nombres;
        groupe_des_chiffres[i].liste_des_nombres_du_groupe=new Nombre [groupe_des_chiffres[i].effectif_des_nombres];

        for(j=0;j<groupe_des_chiffres[i].effectif_des_nombres;j++)
        {
            groupe_des_chiffres[i].liste_des_nombres_du_groupe[j].nombre=new char [5];
            out>>groupe_des_chiffres[i].liste_des_nombres_du_groupe[j].nombre;
            groupe_des_chiffres[i].liste_des_nombres_du_groupe[j].certain=true;
        }
    }

    position=out.pos();
    file.close();
    tableau_des_estimation=new tableau(file_name,position);
}

void calcul_estimation::sauvegarder(QString file_name)
{
    int i,j;
    QFile file("Sauvegardes\\"+file_name+".VTsave");
    file.open(QIODevice::Append);
    QTextStream out(&file);
    out.setCodec("UTF-8");
    out<<nombre_des_groupes_certains<<"\n";
    for(i=0;i<nombre_des_groupes_certains;i++)
    {
        if(i!=nombre_des_groupes_certains-1)
            out<<groupe_des_chiffres[i].groupe<<" ";
        else
            out<<groupe_des_chiffres[i].groupe;
    }
    out<<"\n";
    for(i=0;i<nombre_des_groupes_certains;i++)
    {
        out<<groupe_des_chiffres[i].effectif_des_nombres<<"\n";

        for(j=0;j<groupe_des_chiffres[i].effectif_des_nombres;j++)
        {
            if(j!=groupe_des_chiffres[i].effectif_des_nombres-1)
                out<<groupe_des_chiffres[i].liste_des_nombres_du_groupe[j].nombre<<" ";
            else
                out<<groupe_des_chiffres[i].liste_des_nombres_du_groupe[j].nombre<<"\n";
        }
    }

    out.flush();
    file.close();
    tableau_des_estimation->sauvegarder(file_name);
}

calcul_estimation::~calcul_estimation()
{
    int i,j;
    for(i=0;i<nombre_des_groupes_certains;i++)
    {
        delete[] groupe_des_chiffres[i].groupe;
        if(groupe_des_chiffres[i].liste_des_nombres_du_groupe!=NULL)
        {
            for(j=0;j<groupe_des_chiffres[i].effectif_des_nombres;j++)
            {
                delete[] groupe_des_chiffres[i].liste_des_nombres_du_groupe[j].nombre;
            }
            delete[] groupe_des_chiffres[i].liste_des_nombres_du_groupe;
        }
    }
    delete[] groupe_des_chiffres;
    delete tableau_des_estimation;
}

void calcul_estimation::construire_liste_des_nombres_du_groupe(int numero)
{
    int i,j,debut,rang=0,compteur=0,ind1=0,ind2=0,ind3=0;

    if(groupe_des_chiffres[numero].groupe[0]!='0')
        groupe_des_chiffres[numero].effectif_des_nombres=24;
    else
    groupe_des_chiffres[numero].effectif_des_nombres=18;
    groupe_des_chiffres[numero].liste_des_nombres_du_groupe=new Nombre [groupe_des_chiffres[numero].effectif_des_nombres];

    for(i=0;i<groupe_des_chiffres[numero].effectif_des_nombres;i++)
    {
        groupe_des_chiffres[numero].liste_des_nombres_du_groupe[i].nombre=new char [5];
        groupe_des_chiffres[numero].liste_des_nombres_du_groupe[i].nombre[4]='\0';
        groupe_des_chiffres[numero].liste_des_nombres_du_groupe[i].certain=true;
    }
    if(groupe_des_chiffres[numero].groupe[0]=='0')
        debut=1;
    else
        debut=0;
    for(i=debut;i<=3;i++)
    {
        compteur=0;
        ind1=0;
        ind2=0;
        ind3=0;
        for(j=0;j<=5;j++)
        {
            groupe_des_chiffres[numero].liste_des_nombres_du_groupe[rang].nombre[0]=groupe_des_chiffres[numero].groupe[i];

            if (compteur==2)
            {
                compteur=0;
                ind1++;
            }
            if(ind1==4)
                ind1=0;
            if(ind1==i)
                ind1++;
            groupe_des_chiffres[numero].liste_des_nombres_du_groupe[rang].nombre[1]=groupe_des_chiffres[numero].groupe[ind1];
            compteur++;

            do
            {
            ind2++;
            if(ind2==4)
                ind2=0;
            }while((ind2==i)||(ind2==ind1));
            groupe_des_chiffres[numero].liste_des_nombres_du_groupe[rang].nombre[2]=groupe_des_chiffres[numero].groupe[ind2];

            do
            {
            ind3++;
            if(ind3==4)
                ind3=0;
            }while((ind3==i)||(ind3==ind1)||(ind3==ind2));
            groupe_des_chiffres[numero].liste_des_nombres_du_groupe[rang].nombre[3]=groupe_des_chiffres[numero].groupe[ind3];
            rang++;
        }
    }
}

void calcul_estimation::copier_un_nombre(char* nombre_recepteur,char* nombre_source)
{
    int i;
    for(i=0;i<4;i++)
        nombre_recepteur[i]=nombre_source[i];
}

int calcul_estimation::calcul_chiffres_communs(char* nombre1,char* nombre2)
{
    int i,j,resultat=0;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(nombre1[i]==nombre2[j])
                resultat++;
        }
    }
    return resultat;
}

int calcul_estimation::calcul_taureaux(char* nombre1,char* nombre2)
{
    int i,resultat=0;
    for(i=0;i<4;i++)
    {
        if(nombre1[i]==nombre2[i])
            resultat++;
    }
    return resultat;
}

int calcul_estimation::calcul_vaches(char* nombre1,char* nombre2)
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

void calcul_estimation::traitement()
{
    int i,j,k,compteur=0,nombre_des_groupes_incertains=0,nombre_des_nombres_incertains=0;
    Groupe_des_chiffres* pointeur;
    Nombre* pointeur1;
    int vache,taureau,somme_v_t;
    tableau_des_estimation->get_derniere_information(vache,taureau,somme_v_t);
    char* estimation=tableau_des_estimation->get_derniere_estimation();

    for(compteur=0;compteur<nombre_des_groupes_certains;compteur++)
    {
        if(calcul_chiffres_communs(groupe_des_chiffres[compteur].groupe,estimation)!=somme_v_t)
        {
            groupe_des_chiffres[compteur].certain=false;
            nombre_des_groupes_incertains++;
        }
    }

    if(nombre_des_groupes_incertains!=0)
    {
        i=0;
        pointeur= new Groupe_des_chiffres [nombre_des_groupes_certains-nombre_des_groupes_incertains];
        for(compteur=0;compteur<nombre_des_groupes_certains;compteur++)
        {
            if(groupe_des_chiffres[compteur].certain==true)
            {
                pointeur[i].groupe=new char [5];
                copier_un_nombre( pointeur[i].groupe,groupe_des_chiffres[compteur].groupe);
                pointeur[i].groupe[4]='\0';
                pointeur[i].certain=true;
                pointeur[i].liste_des_nombres_du_groupe=groupe_des_chiffres[compteur].liste_des_nombres_du_groupe;
                pointeur[i].effectif_des_nombres=groupe_des_chiffres[compteur].effectif_des_nombres;
                i++;
            }else
            {
                if(groupe_des_chiffres[compteur].liste_des_nombres_du_groupe!=NULL)
                {
                    for(j=0;j<groupe_des_chiffres[compteur].effectif_des_nombres;j++)
                    {
                        delete[] groupe_des_chiffres[compteur].liste_des_nombres_du_groupe[j].nombre;
                    }
                    delete[] groupe_des_chiffres[compteur].liste_des_nombres_du_groupe;
                }
            }
            delete[] groupe_des_chiffres[compteur].groupe;
        }
        delete[] groupe_des_chiffres;
        groupe_des_chiffres=pointeur;
        nombre_des_groupes_certains-=nombre_des_groupes_incertains;
    }

    nombre_des_groupes_incertains=0;
    for(i=0;i<nombre_des_groupes_certains;i++)
    {

        nombre_des_nombres_incertains=0;
        for(compteur=0;compteur<groupe_des_chiffres[i].effectif_des_nombres;compteur++)
        {

            if(calcul_taureaux(groupe_des_chiffres[i].liste_des_nombres_du_groupe[compteur].nombre,estimation)!=taureau)
            {
                groupe_des_chiffres[i].liste_des_nombres_du_groupe[compteur].certain=false;
                nombre_des_nombres_incertains++;
                if(nombre_des_nombres_incertains==groupe_des_chiffres[i].effectif_des_nombres)
                {
                    groupe_des_chiffres[i].certain=false;
                    nombre_des_groupes_incertains++;
                }
            }

        }

        if(nombre_des_nombres_incertains!=0)
        {
            k=0;
            pointeur1=new Nombre [groupe_des_chiffres[i].effectif_des_nombres-nombre_des_nombres_incertains];
            for(compteur=0;compteur<groupe_des_chiffres[i].effectif_des_nombres;compteur++)
            {
                if(groupe_des_chiffres[i].liste_des_nombres_du_groupe[compteur].certain==true)
                {
                    pointeur1[k].nombre=new char [5];
                    copier_un_nombre(pointeur1[k].nombre,groupe_des_chiffres[i].liste_des_nombres_du_groupe[compteur].nombre);
                    pointeur1[k].nombre[4]='\0';
                    pointeur1[k].certain=true;
                    k++;
                }
                delete[] groupe_des_chiffres[i].liste_des_nombres_du_groupe[compteur].nombre;
            }
            delete[] groupe_des_chiffres[i].liste_des_nombres_du_groupe;
            groupe_des_chiffres[i].liste_des_nombres_du_groupe=pointeur1;
            groupe_des_chiffres[i].effectif_des_nombres-=nombre_des_nombres_incertains;
        }
    }

    if(nombre_des_groupes_incertains!=0)
    {
        i=0;
        pointeur= new Groupe_des_chiffres [nombre_des_groupes_certains-nombre_des_groupes_incertains];
        for(compteur=0;compteur<nombre_des_groupes_certains;compteur++)
        {
            if(groupe_des_chiffres[compteur].certain==true)
            {
                pointeur[i].groupe=new char [5];
                copier_un_nombre( pointeur[i].groupe,groupe_des_chiffres[compteur].groupe);
                pointeur[i].groupe[4]='\0';
                pointeur[i].certain=true;
                pointeur[i].liste_des_nombres_du_groupe=groupe_des_chiffres[compteur].liste_des_nombres_du_groupe;
                pointeur[i].effectif_des_nombres=groupe_des_chiffres[compteur].effectif_des_nombres;
                i++;
            }else
            {
                if(groupe_des_chiffres[compteur].liste_des_nombres_du_groupe!=NULL)
                {
                    for(j=0;j<groupe_des_chiffres[compteur].effectif_des_nombres;j++)
                    {
                        delete[] groupe_des_chiffres[compteur].liste_des_nombres_du_groupe[j].nombre;
                    }
                    delete[] groupe_des_chiffres[compteur].liste_des_nombres_du_groupe;
                }
            }
            delete[] groupe_des_chiffres[compteur].groupe;
        }
        delete[] groupe_des_chiffres;
        groupe_des_chiffres=pointeur;
        nombre_des_groupes_certains-=nombre_des_groupes_incertains;
    }
}

int calcul_estimation::calcul_effectif()
{
    int effectif=0,i=0;
    for(i=0;i<nombre_des_groupes_certains;i++)
    {
        effectif+=groupe_des_chiffres[i].effectif_des_nombres;
    }
    return effectif;
}

void calcul_estimation::ajouter_estimation(char* nombre,int vache,int taureau)
{
    tableau_des_estimation->ajouter_estimation(nombre,vache,taureau);
}

char* calcul_estimation::estimation_en_cours()
{
    int val1,val2;
    val1=rand()%nombre_des_groupes_certains;
    val2=rand()%groupe_des_chiffres[val1].effectif_des_nombres;
    return groupe_des_chiffres[val1].liste_des_nombres_du_groupe[val2].nombre;
}

char** calcul_estimation::mentir(QString &nombre,int& ligne)
{
    char** M;
    M= new char* [10];
    const char* N1= nombre.toStdString().c_str();
    char* N=new char[5];
    for(int i=0;i<4;i++)
    {
        N[i]=N1[i];
    }
    char* estimation;
    int vache,taureau;

    for(int i=0;i<tableau_des_estimation->get_nombre_des_estimation();i++)
    {
        tableau_des_estimation->get_information(i,estimation,vache,taureau);
        if((calcul_taureaux(N,estimation)!=taureau)||(calcul_vaches(N,estimation)!=vache))
        {
            M[ligne]=new char [59];
            M[ligne][0]=i+49;
            M[ligne][1]='-';

            for(int j=2;j<12;j++)
                M[ligne][j]=' ';

            for(int j=12;j<16;j++)
                M[ligne][j]=estimation[j-12];
            for(int j=16;j<36;j++)
                M[ligne][j]=' ';
            M[ligne][36]=vache+48;
            for(int j=37;j<57;j++)
                M[ligne][j]=' ';
            M[ligne][57]=taureau+48;
            M[ligne][58]='\0';
            ligne++;
        }
    }
    delete N;
    delete N1;
    return M;
}
