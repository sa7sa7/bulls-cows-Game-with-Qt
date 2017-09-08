#ifndef SCORE_H
#define SCORE_H

#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTabWidget>
#include <QFile>
#include <QTextStream>

class menu;
class Scroll;
class Sous_fenetre;
class score : public QObject
{
    Q_OBJECT
public:
    score(menu *Parent, QGridLayout *Layout,Sous_fenetre* fenetre);
    ~score();
    void executer();
    void effacer();
public slots:
    void afficher_menu();
private:
    menu* parent;
    QGridLayout* layout_principale;
    QVBoxLayout *layout;
    QPushButton* retour;
    QTabWidget *onglets;
    Scroll* scroll;
    QWidget* widget;
    QLabel** vue;
    QLabel** labels;
    Sous_fenetre *sous_fenetre;
};

#endif // SCORE_H
