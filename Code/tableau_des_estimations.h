#ifndef TABLEAU_DES_ESTIMATIONS_H
#define TABLEAU_DES_ESTIMATIONS_H

#define nombre_des_estimations_maximal 10

#include <QString>
#include <QFile>
#include <QTextStream>

typedef struct Estimation
{
    char* nombre;
    int vache;
    int taureau;
    int somme_v_t;
}Estimation;

class tableau
{
    public:
        Estimation* tableau_des_estimations;
        int nombre_des_estimations;

    public:
        tableau();
        tableau(QString file_name, qint64 pos);
        ~tableau();
        char* get_derniere_estimation();
        void get_derniere_information(int& vache,int& taureau,int& somme_v_t);
        void get_information(int i, char*& estimation, int& vache, int& taureau);
        void ajouter_estimation(char* nombre,int vache,int taureau);
        void sauvegarder(QString file_name);
        int get_nombre_des_estimation();
};

#endif // TABLEAU_DES_ESTIMATIONS_H
