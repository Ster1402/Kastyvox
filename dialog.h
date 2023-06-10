#ifndef DIALOG_H
#define DIALOG_H

#include <QObject>
#include <QWidget>
#include <QDialog>

#include <QVBoxLayout>
#include <QFormLayout>
#include <QGridLayout>
#include <QHBoxLayout>

#include <QTabWidget>

#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QDate>
#include <QCalendarWidget>
#include <QTextEdit>

class Dialog : public QDialog
{
    Q_OBJECT

public:

    Dialog();
    Dialog(QString *date);
    Dialog(QString *probleme,QString *date);
    QTextEdit *get_problem;
    QString *problem;

    Dialog(QString *date,QString *cni,QString *nom,QString *prenom,QString *age,QString *profession,QString* contact, QString *pays, QString *ville, QString *adresse, QString *email, QString *date_fin_sejour,QString *date_butoire,QString *cni_le,QString *cni_a,QString *commentaires);

    //Layouts
    QVBoxLayout *principal;
        QLabel *titre;
    //Ajout d'un Occupant
    QFormLayout *l_ajout;
        QCalendarWidget *get_date;
        QLineEdit *get_nom;
        QLineEdit *get_prenom;
        QLineEdit *get_age;
        QLineEdit *get_profession;
        QLineEdit *get_cni;
        QLineEdit *get_cni_le;
        QLineEdit *get_cni_a;
        QLineEdit *get_contact;
        QLineEdit *get_pays;
        QLineEdit *get_ville;
        QLineEdit *get_adresse;
        QLineEdit *get_email;
        QCalendarWidget *get_date_fin_sejour;
        QPushButton *d_entree;
        QPushButton *d_sortie;
        QLineEdit *d_butoire;
        QTextEdit *get_commentaires;

        QString *date;
        QString *cni;
        QString *nom;
        QString *prenom;
        QString *age;
        QString *profession;
        QString *contact;
        QString *pays;
        QString *ville;
        QString *adresse;
        QString *email;
        QString *date_fin_sejour;
        QString *date_butoire;
        QString *cni_le;
        QString *cni_a;
        QString *commentaires;

        //Avec QTabWidget
        QTabWidget *tableau;
        QWidget *w_form;
        QWidget *w_dates;
        QVBoxLayout *v_dates;


        QPushButton *enregistrer;
        QPushButton *annuler;

        int indxForm;
        int indxCalen;

        void connection();

public slots:
        void rec_date();
        void save_probleme();
        void enregistreDonnee();
        void actu_date();
};

#endif // DIALOG_H
