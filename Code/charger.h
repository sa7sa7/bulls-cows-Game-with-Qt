#ifndef CHARGER_H
#define CHARGER_H

#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QDir>
#include <QFile>
#include <QDirIterator>
#include <QLabel>

class menu;
class Sous_fenetre;
class charger : public QObject
{
    Q_OBJECT
public:
    charger(menu *Parent, QGridLayout *Layout,Sous_fenetre* fenetre);
    ~charger();
    void executer();
    void effacer();

public slots:
    void selecter(int row1, int column1,int row2, int column2);
    void charger_une_partie();
    void supprimer();
    void afficher_menu();

private:
    menu* parent;
    QGridLayout* layout_principale;
    QTableWidget *tableau;
    QTableWidgetItem **Item;
    QPushButton* valider;
    QPushButton* Supprimer;
    QPushButton* retour;
    QLabel*  vue;
    QWidget* enveloppe;
    QVBoxLayout *layout;
    bool selecte;
    bool coin;
    int compteur;
    Sous_fenetre *sous_fenetre;
};
#endif // CHARGER_H
