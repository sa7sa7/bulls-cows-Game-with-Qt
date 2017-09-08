#include "tableau_des_estimations.h"

tableau::tableau()
{
    nombre_des_estimations=0;
    int i;
    tableau_des_estimations=new Estimation [20];
    for(i=0;i<nombre_des_estimations_maximal;i++)
    {
        tableau_des_estimations[i].nombre=new char [5];
        tableau_des_estimations[i].nombre[4]='\0';
        tableau_des_estimations[i].vache=0;
        tableau_des_estimations[i].taureau=0;
        tableau_des_estimations[i].somme_v_t=0;
    }
}

tableau::tableau(QString file_name, qint64 pos)
{
    QFile file("Sauvegardes\\"+file_name+".VTsave");
    file.open(QIODevice::ReadOnly);
    QTextStream out(&file);
    out.setCodec("UTF-8");
    out.seek(pos);
    out>>nombre_des_estimations;
    int i;
    tableau_des_estimations=new Estimation [20];
    for(i=0;i<nombre_des_estimations_maximal;i++)
    {
        tableau_des_estimations[i].nombre=new char [5];
        tableau_des_estimations[i].nombre[4]='\0';
        tableau_des_estimations[i].vache=0;
        tableau_des_estimations[i].taureau=0;
        tableau_des_estimations[i].somme_v_t=0;
    }

    for(i=0;i<nombre_des_estimations;i++)
    {
        out>>tableau_des_estimations[i].nombre;
        out>>tableau_des_estimations[i].vache;
        out>>tableau_des_estimations[i].taureau;
        tableau_des_estimations[i].somme_v_t=tableau_des_estimations[i].vache+tableau_des_estimations[i].taureau;
    }

    file.close();
}

tableau::~tableau()
{
    int i;
    for(i=0;i<nombre_des_estimations_maximal;i++)
    {
        delete[] tableau_des_estimations[i].nombre;
    }
    delete[] tableau_des_estimations;
}

void tableau::sauvegarder(QString file_name)
{
    QFile file("Sauvegardes\\"+file_name+".VTsave");
    file.open(QIODevice::Append);
    QTextStream out(&file);
    out.setCodec("UTF-8");
    out<<nombre_des_estimations<<"\n";
    for(int i=0;i<nombre_des_estimations;i++)
    {
        out<<tableau_des_estimations[i].nombre<<" ";
        out<<tableau_des_estimations[i].vache<<" ";
        out<<tableau_des_estimations[i].taureau<<"\n";
    }

    out.flush();
    file.close();
}

void tableau::ajouter_estimation(char* nombre,int vache,int taureau)
{
    int i;
    for(i=0;i<4;i++)
        tableau_des_estimations[nombre_des_estimations].nombre[i]=nombre[i];

    tableau_des_estimations[nombre_des_estimations].vache=vache;
    tableau_des_estimations[nombre_des_estimations].taureau=taureau;
    tableau_des_estimations[nombre_des_estimations].somme_v_t=vache+taureau;
    nombre_des_estimations++;
}

char* tableau::get_derniere_estimation()
{
    return tableau_des_estimations[nombre_des_estimations-1].nombre;
}

void tableau::get_derniere_information(int& vache,int& taureau,int& somme_v_t)
{
    vache=tableau_des_estimations[nombre_des_estimations-1].vache;
    taureau=tableau_des_estimations[nombre_des_estimations-1].taureau;
    somme_v_t=tableau_des_estimations[nombre_des_estimations-1].somme_v_t;
}

void tableau::get_information(int i, char *&estimation, int& vache, int& taureau)
{
    estimation=tableau_des_estimations[i].nombre;
    vache=tableau_des_estimations[i].vache;
    taureau=tableau_des_estimations[i].taureau;
}

int tableau::get_nombre_des_estimation()
{
   return nombre_des_estimations;
}
