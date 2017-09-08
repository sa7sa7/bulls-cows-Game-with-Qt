#ifndef CALCUL_ESTIMATION_H
#define CALCUL_ESTIMATION_H

#include <QString>
#include <QFile>
#include <ctime>
#include <QTextStream>

typedef struct Nombre
{
    char* nombre;
    bool certain;
}Nombre;

typedef struct Groupe_des_chiffres
{
    char* groupe;
    bool certain;
    Nombre* liste_des_nombres_du_groupe;
    int effectif_des_nombres;
}Groupe_des_chiffres;

class tableau;
class calcul_estimation
{
private:
    int nombre_des_groupes_certains;
    Groupe_des_chiffres* groupe_des_chiffres;   
    tableau* tableau_des_estimation;
    void construire_liste_des_nombres_du_groupe(int numero);
    int calcul_chiffres_communs(char* nombre1,char* nombre2);
    int calcul_vaches(char* nombre1,char* nombre2);
    int calcul_taureaux(char* nombre1,char* nombre2);
public:
    calcul_estimation();
    calcul_estimation(QString file_name, qint64 pos);
    ~calcul_estimation();
    void sauvegarder(QString file_name);
    int calcul_effectif();
    void traitement();
    void copier_un_nombre(char* nombre_recepteur,char* nombre_source);
    void ajouter_estimation(char* nombre,int vache,int taureau);
    char* estimation_en_cours();
    char** mentir(QString &nombre, int& ligne);
};
#endif // CALCUL_ESTIMATION_H
