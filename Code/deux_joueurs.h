#ifndef DEUX_JOUEURS_H
#define DEUX_JOUEURS_H

#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

class menu;
class Scroll;
class Sous_fenetre;
class calcul_estimation;
class deux_joueurs : public QObject
{
    Q_OBJECT
public:
    deux_joueurs(menu *Parent, QGridLayout *Layout,Sous_fenetre* fenetre);
    ~deux_joueurs();
    void executer();
    void effacer();

public slots:
    void pause();
    void valider_joueur11();
    void valider_joueur12();
    void valider_joueur21();
    void valider_joueur22();
    void modifier_taureau(int n);
    void modifier_vache(int n);

private:
    void saisir_estimation_joueur1();
    void saisir_estimation_joueur2();

    bool verifier_nombre(QString nombre);
    void input_valide_joueur1(QString nombre);
    void input_valide_joueur1(int Vache, int Taureau);
    void input_valide_joueur2(QString nombre);
    void input_valide_joueur2(int Vache, int Taureau);
    menu* parent;
    QGridLayout* layout_principale;

    QPushButton *bouton_valider11;
    QPushButton *bouton_valider21;
    QPushButton *bouton_valider12;
    QPushButton *bouton_valider22;
    QPushButton *bouton_pause;
    QLineEdit *input1;
    QLineEdit *input2;
    QComboBox *vache;
    QComboBox *taureau;

    QGridLayout* layout_joueur1;
    QGridLayout* layout_joueur2;
    QHBoxLayout* layout;

    QVBoxLayout* layout1;
    QVBoxLayout* layout2;

    QWidget* widget1;
    QWidget* widget2;

    QLabel** labels;
    QLabel*** messages1;
    QLabel*** messages2;
    QLabel* message;

    QGroupBox* box_joueur1;
    QGroupBox* box_joueur2;

    Scroll* scroll1;
    Scroll* scroll2;


    int ligne1;
    int ligne2;

    bool gagner_joueur1;
    bool gagner_joueur2;

    Sous_fenetre *sous_fenetre;
};

#endif // DEUX_JOUEURS_H
