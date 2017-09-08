#ifndef SAUVEGARDER_H
#define SAUVEGARDER_H

#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDir>
#include <QDirIterator>

class menu;
class Sous_fenetre;
class Sauvegarder : public QObject
{
    Q_OBJECT
public:
    Sauvegarder(menu *Parent,Sous_fenetre *fenetre, QVBoxLayout *Layout);
    ~Sauvegarder();
    void preexecuter();
    void executer(int compteur);
    void effacer();
public slots :
    void valider();
    void Oui();
    void Non();
private:
    menu* parent;
    QVBoxLayout *layout_principale;
    Sous_fenetre *sous_fenetre;
    QPushButton *OK;
    QPushButton *bouton_valider;
    QPushButton *oui;
    QPushButton *non;
    QHBoxLayout* layout;
    QLabel*  vue;
    QLineEdit *input;

};

#endif // SAUVEGARDER_H
