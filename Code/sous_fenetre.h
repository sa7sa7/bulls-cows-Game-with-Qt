#ifndef Sous_fenetre_H
#define Sous_fenetre_H

#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTimeLine>
#include <QFile>
#include <QTextStream>

class menu;
class calcul_estimation;
class Sauvegarder;
class Sous_fenetre : public QWidget
{
    Q_OBJECT
public:
    Sous_fenetre(menu *Parent);
    ~Sous_fenetre();
    void pause(int mode);
    void afficher1(QString ch, int input);
    void afficher2();
    void afficher3(QString ch, int input);
    void afficher4(QString temps);
    void effacer();
    void closeEvent(QCloseEvent* event);
    void set_generateur(calcul_estimation* generateur);

public slots :
    void valider();
    void Quitter();
    void Sauvegarde();
    void reafficher_menu();

private:
    bool verifier_input(QString nombre);
    void input_valide(QString nombre);
    menu* parent;
    calcul_estimation* generateur_des_estimations;
    Sauvegarder *sauvegarder;
    QPushButton *OK;
    QPushButton *quitter;
    QPushButton *Menu;
    QPushButton *Rejouer;
    QPushButton *sauvegarde;
    QPushButton *bouton_valider;
    QLabel*  vue;
    QLabel** labels;
    QLineEdit *input;
    QVBoxLayout *layout;
    QTimeLine *temps;
    int ligne;
    bool droit_de_quitter;
    bool save_bool;
    bool continuer_temps;
};

#endif // Sous_fenetre_H
