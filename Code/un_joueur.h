#ifndef un_joueur_H
#define un_joueur_H

#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QTimeLine>
#include <QPushButton>
#include <QFile>
#include <QTextStream>

class menu;
class Sous_fenetre;
class calcul_estimation;
class un_joueur : public QObject
{
    Q_OBJECT
public:
    un_joueur(menu *Parent, QGridLayout *Layout,Sous_fenetre* fenetre);
    ~un_joueur();
    void executer();
    void executer(QString file_name);
    void effacer();
    void sauvegarder(QString file_name);
    void fin_de_partie(int mode);
    void modifier_pause();

public slots:
    void pause();
    void valider1();
    void valider2();
    void modifier_taureau(int n);
    void modifier_vache(int n);
    void changer();

private:
    void saisir_estimation_joueur(int mode);
    void saisir_vache_taureau(int mode);

    bool verifier_nombre(QString nombre);
    void input_valide1(QString nombre);
    void input_valide2(int Vache, int Taureau);
    int calcul_taureaux(char* nombre1,QString nombre2);
    int calcul_vaches(char* nombre1,QString nombre2);
    menu* parent;
    QGridLayout* layout_principale;

    QPushButton *bouton_valider1;
    QPushButton *bouton_valider2;
    QPushButton *bouton_pause;
    QLineEdit *input;
    QComboBox *vache;
    QComboBox *taureau;

    QGridLayout* layout_joueur;
    QGridLayout* layout_boot;
    QHBoxLayout* layout;

    QLabel** labels;
    QLabel*** messages1;
    QLabel*** messages2;
    QLabel* message;
    QLabel *temps;
    QTimeLine *temps_compteur;

    QGroupBox* box_joueur;
    QGroupBox* box_boot;

    calcul_estimation* generateur_des_estimations;
    char* boot_nombre;
    char* N;

    int ligne1;
    int ligne2;
    int colonne;
    bool gagner_joueur;
    bool gagner_boot;
    bool droit_incementer;
    Sous_fenetre *sous_fenetre;
};

#endif // FENETRE_H

