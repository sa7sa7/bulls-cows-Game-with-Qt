#include "scroll.h"
#include "menu.h"

Scroll::Scroll(menu *Parent,QPushButton *Bouton):QScrollArea(Parent)
{
    mode=true;
    bouton=Bouton;
}


Scroll::Scroll(menu *Parent, QPushButton *Bouton, QLineEdit *ligne):QScrollArea(Parent)
{
    mode=false;
    bouton=Bouton;
    input=ligne;
}

void Scroll::scrollContentsBy(int dx, int dy)
{
    QScrollArea::scrollContentsBy(dx,dy);
    if(mode==true)
    {
        bouton->setAutoDefault(true);
        bouton->setFocus(Qt::BacktabFocusReason);
    }else
    {
        bouton->setAutoDefault(true);
        bouton->setFocus(Qt::BacktabFocusReason);
        input->setFocus(Qt::TabFocusReason);
    }
}
