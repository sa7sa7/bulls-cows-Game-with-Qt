#ifndef SCROLL_H
#define SCROLL_H

#include <QScrollArea>
#include <QPushButton>
#include <QLineEdit>

class menu;
class Scroll : public QScrollArea
{
public:
    Scroll(menu *Parent,QPushButton *Bouton);
    Scroll(menu *Parent,QPushButton *Bouton, QLineEdit *ligne);

protected:
    virtual void scrollContentsBy(int dx, int dy);

private:
    bool mode;
    QPushButton* bouton;
    QLineEdit* input;
};

#endif // SCROLL_H
