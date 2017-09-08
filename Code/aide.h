#ifndef AIDE_H
#define AIDE_H

#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QTabWidget>

class menu;
class Scroll;
class aide : public QObject
{
    Q_OBJECT
public:
    aide(menu *Parent, QGridLayout *Layout);
    void executer();
    void effacer();
public slots:
    void afficher_menu();
    void retourner_focus();
private:
    menu* parent;
    QGridLayout* layout_principale;
    QPushButton* retour;
    QTabWidget *onglets;
    Scroll* scroll;
    QLabel* image1;
    QLabel* image2;
    QLabel* image3;
};

#endif // AIDE_H
