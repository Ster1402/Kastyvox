#include "dialog.h"
#include <QRegExp>
#include <QValidator>
#include <QIntValidator>
#include <QMessageBox>

Dialog::Dialog()
{

}

Dialog::Dialog(QString *date, QString *cni, QString *nom, QString *prenom, QString *age, QString *profession, QString *contact, QString *pays, QString *ville, QString *adresse, QString *email, QString *date_fin_sejour, QString *date_butoire, QString *cni_le, QString *cni_a, QString *commentaires){
    //Pour pouvoir les modifier
    this->date = date;
    this->cni = cni;
    this->nom = nom;
    this->prenom = prenom;
    this->age = age;
    this->profession = profession;
    this->contact = contact;
    this->pays = pays;
    this->ville = ville;
    this->adresse = adresse;
    this->email = email;
    this->date_fin_sejour = date_fin_sejour;
    this->date_butoire = date_butoire;
    this->cni_le = cni_le;
    this->cni_a = cni_a;
    this->commentaires = commentaires;

    titre = new QLabel;
    principal = new QVBoxLayout;
        principal->addWidget (titre);
        //principal->addSpacing (20);

    tableau = new QTabWidget;

        w_form = new QWidget;

        w_dates = new QWidget;

        QGridLayout *grid_dates = new QGridLayout;
        //Date entrée
        QLabel *tt_debut = new QLabel(tr("Date d'entrée"));
        tt_debut->setObjectName ("den");

        get_date = new QCalendarWidget;
        get_date->setMinimumDate (QDate(2020,01,01));
        //get_date->setMaximumHeight (183);

        //Fin séjour
        QLabel *tt_fin = new QLabel(tr("Date de fin de séjour"));
        tt_fin->setObjectName ("dso");

        get_date_fin_sejour = new QCalendarWidget;
        get_date_fin_sejour->setMinimumDate (QDate(2021,01,01));
//        get_date_fin_sejour->setMaximumHeight (183);

        //Disposition
        grid_dates->addWidget (tt_debut,1,1,Qt::AlignCenter);
        grid_dates->addWidget (get_date,2,1,5,1,Qt::AlignCenter);

        grid_dates->addWidget (tt_fin,1,2,Qt::AlignCenter);
        grid_dates->addWidget (get_date_fin_sejour,2,2,5,1,Qt::AlignCenter);

        w_dates->setLayout (grid_dates);

    l_ajout = new QFormLayout;

        get_nom = new QLineEdit;
        get_nom->setPlaceholderText(tr("Obligatoire"));
        l_ajout->addRow (tr("Nom : "),get_nom);

        get_prenom = new QLineEdit;
        l_ajout->addRow (tr("Prenom : "),get_prenom);

        get_age = new QLineEdit;
        l_ajout->addRow (tr("Date de naissance : "),get_age);

        get_profession = new QLineEdit;
        l_ajout->addRow (tr("Profession : "),get_profession);

        get_cni = new QLineEdit;
        get_cni->setPlaceholderText(tr("Obligatoire"));
        get_cni->setToolTip (tr("Obligatoire !"));
        l_ajout->addRow (tr("Numéro cni : "),get_cni);

        //Délivré le..... à .....
        get_cni_le = new QLineEdit;
        l_ajout->addRow (tr("Délivrée le : "),get_cni_le);

        get_cni_a = new QLineEdit;
        l_ajout->addRow (tr("à : "),get_cni_a);

        get_pays = new QLineEdit;
        get_pays->setText(tr("Cameroun"));
        l_ajout->addRow (tr("Pays de provenance : "),get_pays);

        get_ville = new QLineEdit;
        l_ajout->addRow (tr("Ville de provenance : "),get_ville);

        get_adresse = new QLineEdit;
        l_ajout->addRow (tr("Adresse : "),get_adresse);

        get_contact = new QLineEdit;
        l_ajout->addRow (tr("Téléphone : "),get_contact);

        get_email = new QLineEdit;
        l_ajout->addRow (tr("Email : "),get_email);

        //Visuel date entrée, date de sortie prévu
        d_entree = new QPushButton;
        d_entree->setText (get_date->selectedDate ().toString (Qt::SystemLocaleLongDate));
        d_entree->setObjectName ("den");
        connect(d_entree, &QPushButton::clicked , [&](){
            tableau->setCurrentIndex(1);
        });

        d_sortie = new QPushButton;
        d_sortie->setText (get_date_fin_sejour->selectedDate ().toString (Qt::SystemLocaleLongDate));
        d_sortie->setObjectName ("dso");
        connect(d_sortie, &QPushButton::clicked , [&](){
            tableau->setCurrentIndex(1);
        });

        d_butoire = new QLineEdit;

        d_butoire->setText (get_date->selectedDate ().addMonths(5).toString (Qt::SystemLocaleLongDate));

        l_ajout->addRow (tr("Date d'entrée : " ),d_entree);
        l_ajout->addRow (tr("Date de fin de séjour : " ),d_sortie);
        l_ajout->addRow(tr("Date butoire de payement loyer : "),d_butoire);

        get_commentaires = new QTextEdit;
        get_commentaires->setMaximumHeight (40);
        l_ajout->addRow (tr("Observations"),get_commentaires);

        connect (get_date,&QCalendarWidget::selectionChanged,this,&Dialog::actu_date);
        connect (get_date_fin_sejour,&QCalendarWidget::selectionChanged,this,&Dialog::actu_date);
        connect(get_date, &QCalendarWidget::selectionChanged, [&](){
           d_butoire->setText (get_date->selectedDate ().addMonths(5).toString (Qt::SystemLocaleLongDate));
        });
        //Observation

        annuler = new QPushButton(tr("Fermer"));
        enregistrer = new QPushButton(tr("Enregistrer"));

        QHBoxLayout *h = new QHBoxLayout;

        h->addWidget (enregistrer);
        h->addWidget (annuler);

        l_ajout->setVerticalSpacing (10);

        w_form->setLayout (l_ajout);
        indxForm = tableau->addTab (w_form,tr("Formulaire"));
        indxCalen = tableau->addTab (w_dates,tr("Calendriers"));

        /*
        principal->addLayout (l_ajout,1);
        principal->addSpacing (5);*/

        principal->addWidget (tableau);
        principal->addLayout (h);

    titre->setObjectName ("titre");
    titre->setAlignment (Qt::AlignCenter);

    setStyleSheet ("QLabel{ font-weight: bold; font-size: 16px; border: none; }"
                   "QPushButton#den,QLabel#den{font-weight: bold; font-size: 16px; border: 1px solid maroon; color: rgb(62,161,36) }"
                   "QPushButton#dso,QLabel#dso{font-weight: bold; font-size: 16px; border: 1px solid maroon; color: rgb(201,72,66) }"
                   "QTextEdit { font-weight: 500; font-size: 15px; background: rgb(220,250,240) }"
                   "QLabel#titre{ font-weight: bold; font-size: 19px; border: 1px solid maroon; }");



    setLayout (principal);
    connection ();
    setSizeGripEnabled (true);
    setWindowIcon (QIcon("logo.png"));
    setWindowTitle (tr("Edition"));

}

void Dialog::actu_date (){
    d_sortie->setText (get_date_fin_sejour->selectedDate ().toString (Qt::SystemLocaleLongDate));
    d_entree->setText (get_date->selectedDate ().toString (Qt::SystemLocaleLongDate));

}

Dialog::Dialog(QString *date){
    this->date = date;

    principal = new QVBoxLayout;
    titre = new QLabel;
    titre->setObjectName ("titre");
    titre->setAlignment (Qt::AlignCenter);
    principal->addWidget (titre);

    get_date = new QCalendarWidget;
    get_date->setMinimumDate (QDate(2020,03,01));
    principal->addWidget (get_date);

    enregistrer = new QPushButton(tr("Valider"));

    principal->addWidget (enregistrer);

    connect (enregistrer,SIGNAL (clicked()),this,SLOT (rec_date ()));
    setStyleSheet ("QLabel{ font-weight: bold; font-size: 16px; border: none; }"
                   "QLabel#titre{ font-weight: bold; font-size: 19px; border: 1px solid maroon; }");
    setLayout (principal);
    setWindowIcon (QIcon("logo.png"));
    setWindowTitle (tr("Edition"));
    setSizeGripEnabled (true);
}

Dialog::Dialog(QString *probleme, QString *date){
    this->problem = probleme;
    this->date = date;

    this->date = date;

    principal = new QVBoxLayout;

    titre = new QLabel;
    titre->setObjectName ("titre");
    titre->setAlignment (Qt::AlignCenter);
    principal->addWidget (titre);

    get_date = new QCalendarWidget;

    get_problem = new QTextEdit;
    get_problem->setMinimumWidth (500);
    get_problem->setWordWrapMode (QTextOption::WordWrap);

    principal->addWidget (get_problem);
    principal->addSpacing (10);
    principal->addWidget (get_date);
    principal->addSpacing (10);

    enregistrer = new QPushButton(tr("Valider"));
    annuler = new QPushButton("Annuler");

    QHBoxLayout *h = new QHBoxLayout;
    h->addWidget (enregistrer);
    h->addWidget (annuler);

    principal->addLayout (h);
    setSizeGripEnabled (true);
    connect (annuler,SIGNAL (clicked()),this,SLOT (reject()));
    connect (enregistrer,SIGNAL (clicked()),this,SLOT (save_probleme ()));
    setStyleSheet ("QLabel{ font-weight: bold; font-size: 16px; border: none; }"
                   "QLabel#titre{ font-weight: bold; font-size: 19px; border: 1px solid maroon; }");
    setLayout (principal);
    setWindowIcon (QIcon("logo.png"));
    setWindowTitle (tr("Edition"));

}

void Dialog::save_probleme (){
    *date = get_date->selectedDate ().toString ("yyyy-MM-dd");
    *problem = get_problem->toPlainText ();

    accept ();
}

void Dialog::connection (){

    connect (enregistrer,SIGNAL (clicked()),this,SLOT (enregistreDonnee()));
    connect (annuler,SIGNAL (clicked()),this,SLOT (reject()));
}

void Dialog::rec_date (){
    *date = get_date->selectedDate ().toString ("yyyy-MM-dd");
    close ();
}

void Dialog::enregistreDonnee (){

    //On s'assure que l'on a pas enregistrer par erreur
    if(tableau->currentIndex () == indxCalen )
    {
        tableau->setCurrentIndex (indxForm);
        return;
    }

    //On vérifie que l'enregistrement ne se lance pas si le nom + cni sont vide
    if(get_cni->text().isEmpty() || get_nom->text().isEmpty())
    {
        QMessageBox::warning(this,"Attention",tr("Impossible d'enregistrer un occupant n'ayant pas de nom et un numéro de CNI !"));
        return;
    }

    *date = get_date->selectedDate ().toString ("yyyy-MM-dd");
    *cni = get_cni->text ();
    *nom = get_nom->text ();
    *prenom = get_prenom->text ();
    *age = get_age->text();
    *profession = get_profession->text ();
    *contact = get_contact->text ();
    *pays = get_pays->text ();
    *ville = get_ville->text ();
    *adresse = get_adresse->text ();
    *email = get_email->text ();
    *date_fin_sejour = get_date_fin_sejour->selectedDate ().toString ("yyyy-MM-dd");
    *date_butoire = d_butoire->text();
    *cni_le = get_cni_le->text();
    *cni_a = get_cni_a->text ();
    *commentaires = get_commentaires->toPlainText ();

    qDebug("Valeur chargée");
    accept ();

}
