
#include <QApplication>
#include <QFontDatabase>
#include <QFile>
#include <QDir>
#include <QDirIterator>
#include <QTextStream>
#include "menu.h"

void ajouter(QString& message_erreur,QString chaine,int& compteur)
{
    message_erreur+=chaine;
    compteur++;
}

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    bool erreur=false;
    int compteur=0;
    QString message_erreur("");

    if(QFontDatabase::addApplicationFont("Fonts\\Bleeding_Cowboys.ttf") == -1)
    {
        if(erreur==false)
        {
            ajouter(message_erreur,"Le(s) fichier(s) suivant est (sont) manquant(s):\n",compteur);
            erreur=true;

        }
        ajouter(message_erreur,"\t• Fonts\\Bleeding_Cowboys.ttf\n",compteur);
    }

    if(QFontDatabase::addApplicationFont("Fonts\\chalkmars_bold_sample.otf") == -1)
    {
        if(erreur==false)
        {
            ajouter(message_erreur,"Le(s) fichier(s) suivant est (sont) manquant(s):\n",compteur);
            erreur=true;
        }
        ajouter(message_erreur,"\t• Fonts\\chalkmars_bold_sample.otf\n",compteur);
    }

    if(QFontDatabase::addApplicationFont("Fonts\\ernesto.ttf") == -1)
    {
        if(erreur==false)
        {
            ajouter(message_erreur,"Le(s) fichier(s) suivant est (sont) manquant(s):\n",compteur);
            erreur=true;
        }
        ajouter(message_erreur,"\t• Fonts\\ernesto.ttf\n",compteur);
    }

    if(QFontDatabase::addApplicationFont("Fonts\\Oduda-Bold.otf") == -1)
    {
        if(erreur==false)
        {
            ajouter(message_erreur,"Le(s) fichier(s) suivant est (sont) manquant(s):\n",compteur);
            erreur=true;
        }
        ajouter(message_erreur,"\t• Fonts\\Oduda-Bold.otf\n",compteur);
    }

    if(QFontDatabase::addApplicationFont("Fonts\\True Lies.ttf") == -1)
    {
        if(erreur==false)
        {
            ajouter(message_erreur,"Le(s) fichier(s) suivant est (sont) manquant(s):\n",compteur);
            erreur=true;
        }
        ajouter(message_erreur,"\t• Fonts\\True Lies.ttf\n",compteur);
    }

    if(QFontDatabase::addApplicationFont("Fonts\\corbel.ttf") == -1)
    {
        if(erreur==false)
        {
            ajouter(message_erreur,"Le(s) fichier(s) suivant est (sont) manquant(s):\n",compteur);
            erreur=true;
        }
        ajouter(message_erreur,"\t• Fonts\\corbel.ttf\n",compteur);
    }

    QDir dir("Images");
    bool help1=false,help2=false,help3=false,icone=false;
    if(dir.exists()==true)
    {
        QDirIterator it(dir.dirName(), QStringList() << "*.jpg", QDir::Files, QDirIterator::Subdirectories);
        while (it.hasNext())
        {
            it.next();
            if((help1==false)&&(it.fileName()=="Help1.jpg")&&(it.fileInfo().size()==919576))
            {
                help1=true;
            }
            if((help2==false)&&(it.fileName()=="Help2.jpg")&&(it.fileInfo().size()==142461))
            {
                help2=true;
            }
            if((help3==false)&&(it.fileName()=="Help3.jpg")&&(it.fileInfo().size()==147657))
            {
                help3=true;
            }
            if((icone==false)&&(it.fileName()=="icone.jpg")&&(it.fileInfo().size()==98853))
            {
                icone=true;
            }
        }

        if(help1==false)
        {
            if(erreur==false)
            {
                ajouter(message_erreur,"Le(s) fichier(s) suivant est (sont) manquant(s):\n",compteur);
                erreur=true;
            }
            ajouter(message_erreur,"\t• Images\\Help1.jpg\n",compteur);
        }
        if(help2==false)
        {
            if(erreur==false)
            {
                ajouter(message_erreur,"Le(s) fichier(s) suivant est (sont) manquant(s):\n",compteur);
                erreur=true;
            }
            ajouter(message_erreur,"\t• Images\\Help2.jpg\n",compteur);
        }
        if(help3==false)
        {
            if(erreur==false)
            {
                ajouter(message_erreur,"Le(s) fichier(s) suivant est (sont) manquant(s):\n",compteur);
                erreur=true;
            }
            ajouter(message_erreur,"\t• Images\\Help3.jpg\n",compteur);
        }
        if(icone==false)
        {
            if(erreur==false)
            {
                ajouter(message_erreur,"Le(s) fichier(s) suivant est (sont) manquant(s):\n",compteur);
                erreur=true;
            }
            ajouter(message_erreur,"\t• Images\\icone.jpg\n",compteur);
        }
    }else
    {
        ajouter(message_erreur,"Le dossier Images est manquant.\n",compteur);
    }

    QDir rep("Sauvegardes");
    if(rep.exists()==false)
    {
        QDir().mkdir(rep.dirName());
        ajouter(message_erreur,"Création du dossier Sauvegardes.\n",compteur);
    }

    QFile file("Score.save");
    if(file.exists()==false)
    {
        file.open(QIODevice::WriteOnly);
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out<<0<<"\n"<<0<<"\n"<<0<<"\n"<<0<<"\n";
        for(int i=0;i<10;i++)
        {
            if(i!=9)
                out<<"score"<<i+1<<" "<<"MM:SS"<<"\n";
            else
                out<<"score"<<i+1<<" "<<"MM:SS";
        }
        out.flush();
        file.close();
        ajouter(message_erreur,"Création du fichier Score.",compteur);
    }

    menu jeu(message_erreur,compteur);
    return app.exec();

}

