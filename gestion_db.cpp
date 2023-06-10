#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QSqlRelationalDelegate>
#include <iostream>

#include <QMessageBox>
#include "fenetre.h"

#include "dialog.h"

//Script Manipulation KASTYVOX_DB.sqlite
//Ajout Occupant
void Fenetre::ajouterOccupantAp (){
    //Objet qui a émit le signal
    QAction *addAp = dynamic_cast<QAction*>(sender ());
    QString numeroAp = addAp->objectName ();

    //On vérifie d'abord que c'est libre

    //Affiche codification correcte
    QString codification = "";
    if(numeroAp == "A1")
    {
        codification = "APT 01";

        if(!liste_affiche_A1[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("L'appartement choisit est déjà occupé ! Veuillez le libérer d'abord ! "));

            return;
        }
    }
    else if (numeroAp == "A2") {
        codification = "APT 02";

        if(!liste_affiche_A2[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("L'appartement choisit est déjà occupé ! Veuillez le libérer d'abord ! "));

            return;
        }

    }else if (numeroAp == "A3") {
        codification = "APT 101";

        if(!liste_affiche_A3[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("L'appartement choisit est déjà occupé ! Veuillez le libérer d'abord ! "));

            return;
        }
    }
    else if (numeroAp == "A4") {
        codification = "APT 102";

        if(!liste_affiche_A4[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("L'appartement choisit est déjà occupé ! Veuillez le libérer d'abord ! "));

            return;
        }
    }

    //...
    //Appel de la procédure d'ajout
    date = cni = profession = nom = prenom = date_butoire =date_fin_sejour = pays = ville = email = adresse =  contact = "";
    cni_le = cni_a = commentaires = "";
    age = "";

    Dialog *diag = new Dialog(&date,&cni,&nom,&prenom,&age,&profession,&contact,&pays,&ville,&adresse,&email,&date_fin_sejour,&date_butoire,&cni_le,&cni_a,&commentaires);
    diag->titre->setText (tr("Appartement : ") + codification);
    diag->exec ();

    if(cni.isEmpty () || nom.isEmpty ())
        return;

    //On effectue l'ajout
    qDebug("Ajouter occupants");
    requetes.ajoutOccupantAp (numeroAp,date,cni,nom,prenom,age,profession,contact,pays,ville,adresse,email,date_fin_sejour,date_butoire,cni_le,cni_a,commentaires);

    //Actualisation des vues
    qDebug("Actualisation vue");
    chargerVue ();
    qDebug("fin actu");
    onglets->setCurrentIndex (indexA);
}

void Fenetre::ajouterOccupantSt (){
    //Objet qui a émit le signal
    QAction *addSt = dynamic_cast<QAction*>(sender ());
    QString numeroSt = addSt->objectName ();

    //Affiche codification correcte
    //En vérifiant que c'est libre

    QString codification = "";
    if(numeroSt == "S1")
    {
        codification = "ST 01";

        if(!liste_affiche_S1[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("Le studio choisit est déjà occupé ! Veuillez le libérer d'abord ! "));

            return;
        }

    }
    else if (numeroSt == "S2") {
        codification = "ST 02";


        if(!liste_affiche_S2[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("Le studio choisit est déjà occupé ! Veuillez le libérer d'abord ! "));

            return;
        }

    }else if (numeroSt == "S3") {
        codification = "ST 03";

        if(!liste_affiche_S3[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("Le studio choisit est déjà occupé ! Veuillez le libérer d'abord ! "));

            return;
        }

    }
    else if (numeroSt == "S4") {
        codification = "ST 04";

        if(!liste_affiche_S4[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("Le studio choisit est déjà occupé ! Veuillez le libérer d'abord ! "));

            return;
        }

    }else if (numeroSt == "S5") {
        codification = "ST 101";

        if(!liste_affiche_S5[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("Le studio choisit est déjà occupé ! Veuillez le libérer d'abord ! "));

            return;
        }

    }else if (numeroSt == "S6") {
        codification = "ST 102";

        if(!liste_affiche_S6[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("Le studio choisit est déjà occupé ! Veuillez le libérer d'abord ! "));

            return;
        }

    }else if (numeroSt == "S7") {
        codification = "ST 103";

        if(!liste_affiche_S7[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("Le studio choisit est déjà occupé ! Veuillez le libérer d'abord ! "));

            return;
        }

    }else if (numeroSt == "S8") {
        codification = "ST 104";

        if(!liste_affiche_S8[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("Le studio choisit est déjà occupé ! Veuillez le libérer d'abord ! "));

            return;
        }
    }

    //Appel de la procédure d'ajout
    date = cni = profession = nom = prenom = date_fin_sejour = date_butoire = pays = ville = email = adresse = "";
    cni_le = cni_a = commentaires = contact = "";
    age = "";

    Dialog *diag = new Dialog(&date,&cni,&nom,&prenom,&age,&profession,&contact,&pays,&ville,&adresse,&email,&date_fin_sejour,&date_butoire,&cni_le,&cni_a,&commentaires);
    diag->titre->setText (tr("Studio : ") + codification);
    diag->exec ();

    if(cni.isEmpty () || nom.isEmpty ())
        return;

    //On effectue l'ajout
    qDebug("Ajouter occupants");
    requetes.ajoutOccupantSt (numeroSt,date,cni,nom,prenom,age,profession,contact,pays,ville,adresse,email,date_fin_sejour,date_butoire,cni_le,cni_a,commentaires);

    //Actualisation des vues
    qDebug("Actualisation vue");

    //Actualisation des vues
    chargerVue ();
    onglets->setCurrentIndex (indexS);
}

void Fenetre::ajouterOccupantCh (){
    //Objet qui a émit le signal
    QAction *addCh = dynamic_cast<QAction*>(sender ());
    QString numeroCh = addCh->objectName ();

    //Affiche codification correcte
    QString codification = "";
    if(numeroCh == "CH1")
    {
        codification = "CH 101";

        if(!liste_affiche_Ch1[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("La chambre choisit est déjà occupé ! Veuillez le libérer d'abord ! "));

            return;
        }

    }
    else if (numeroCh == "CH2") {
        codification = "CH 102";

        if(!liste_affiche_Ch2[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("La chambre choisit est déjà occupé ! Veuillez le libérer d'abord ! "));

            return;
        }

    }else if (numeroCh == "CH3") {
        codification = "CH 103";

        if(!liste_affiche_Ch3[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("La chambre choisit est déjà occupé ! Veuillez le libérer d'abord ! "));

            return;
        }

    }
    else if (numeroCh == "CH4") {
        codification = "CH 104";

        if(!liste_affiche_Ch4[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("La chambre choisit est déjà occupé ! Veuillez le libérer d'abord ! "));

            return;
        }

    }

    //...

    //Appel de la procédure d'ajout
    date = cni = profession = nom = prenom = date_fin_sejour = date_butoire = pays = ville = email = adresse = "";
    cni_le = cni_a = commentaires = contact = "";
    age = "";

    Dialog *diag = new Dialog(&date,&cni,&nom,&prenom,&age,&profession,&contact,&pays,&ville,&adresse,&email,&date_fin_sejour,&date_butoire,&cni_le,&cni_a,&commentaires);
    diag->titre->setText (tr("Chambre  ") + codification);
    diag->exec ();

    if(cni.isEmpty () || nom.isEmpty ())
        return;

    //On effectue l'ajout
    qDebug("Ajouter occupants");
    requetes.ajoutOccupantCh (numeroCh,date,cni,nom,prenom,age,profession,contact,pays,ville,adresse,email,date_fin_sejour,date_butoire,cni_le,cni_a,commentaires);

    //Actualisation des vues
    qDebug("Actualisation vue");

    //Actualisation des vues
    chargerVue ();
    onglets->setCurrentIndex (indexC);

}

void Fenetre::ajouterOccupantBt (){

    //Objet qui a émit le signal
    QAction *addBt = dynamic_cast<QAction*>(sender ());
    QString numeroBt = addBt->objectName ();


    //Affiche codification correcte
    QString codification = "";
    if(numeroBt == "B1")
    {
        codification = "B 01";
        if(!liste_affiche_B1[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("La boutique choisit est déjà occupé ! Veuillez le libérer d'abord ! "));

            return;
        }

    }
    else if (numeroBt == "B2") {
        codification = "B 02";
        if(!liste_affiche_B2[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("La boutique choisit est déjà occupé ! Veuillez le libérer d'abord ! "));

            return;
        }

    }else if (numeroBt == "B3") {
        codification = "B 03";
        if(!liste_affiche_B3[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("La boutique choisit est déjà occupé ! Veuillez le libérer d'abord ! "));

            return;
        }

    }

    //...
    //Appel de la procédure d'ajout
    date = cni = profession = nom = prenom = date_fin_sejour= date_butoire = pays = ville = email = adresse = "";
    cni_le = cni_a = commentaires = contact = "";
    age = "";

    Dialog *diag = new Dialog(&date,&cni,&nom,&prenom,&age,&profession,&contact,&pays,&ville,&adresse,&email,&date_fin_sejour,&date_butoire,&cni_le,&cni_a,&commentaires);
    diag->titre->setText (tr("Boutique  ") + codification);
    diag->exec();

    if(cni.isEmpty () || nom.isEmpty ())
        return;

    //On effectue l'ajout
    qDebug("Ajouter occupants");
    requetes.ajoutOccupantBt (numeroBt,date,cni,nom,prenom,age,profession,contact,pays,ville,adresse,email,date_fin_sejour,date_butoire,cni_le,cni_a,commentaires);

    //Actualisation des vues
    qDebug("Actualisation vue");


    //Actualisation des vues
    chargerVue ();
    onglets->setCurrentIndex (indexB);
}

//Supprime Occupant
void Fenetre::supprimerOccupantAp (){
    //Recupérer le numéro de l'appart
    QAction* objet = dynamic_cast<QAction*>(sender ());
    QString numero = objet->objectName ();

    //Changement d'onglet
    onglets->setCurrentIndex (indexA);

    if(numero == "A1")
    {
        if(liste_affiche_A1[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("L'appartement choisit est vide "));

            return;
        }
    }
    else if (numero == "A2") {

        if(liste_affiche_A2[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("L'appartement choisit est vide "));

            return;
        }

    }else if (numero == "A3") {

        if(liste_affiche_A3[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("L'appartement choisit est vide "));

            return;
        }
    }
    else if (numero == "A4") {

        if(liste_affiche_A4[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("L'appartement choisit est vide "));

            return;
        }
    }

    //On demande confirmation avant
    //Affiche codification correcte
    QString codification = "";
    if(numero == "A1")
        codification = "APT 01";
    else if (numero == "A2") {
        codification = "APT 02";
    }else if (numero == "A3") {
        codification = "APT 101";
    }
    else if (numero == "A4") {
        codification = "APT 102";
    }

    //...

    int ok = QMessageBox::warning (this,"Confirmation","Voulez vous libérez l'appartement " + codification + " ? ",QMessageBox::Yes|QMessageBox::No);

    if(ok==QMessageBox::No)
        return;

    //Script
    requetes.supprimeOccupantAp (numero);

    //On actualise
    chargerVue ();
}

void Fenetre::supprimerOccupantSt (){
    //Recupérer le numéro de l'appart
    QAction* objet = dynamic_cast<QAction*>(sender ());
    QString numero = objet->objectName ();

    //Changement d'onglet
    onglets->setCurrentIndex (indexS);

    if(numero == "S1")
    {
        if(liste_affiche_S1[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("Le studio choisit vide "));

            return;
        }

    }
    else if (numero == "S2") {

        if(liste_affiche_S2[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("Le studio choisit vide "));

            return;
        }

    }else if (numero == "S3") {

        if(liste_affiche_S3[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("Le studio choisit vide "));

            return;
        }

    }
    else if (numero == "S4") {

        if(liste_affiche_S4[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("Le studio choisit vide "));

            return;
        }

    }else if (numero == "S5") {

        if(liste_affiche_S5[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("Le studio choisit vide "));

            return;
        }

    }else if (numero == "S6") {

        if(liste_affiche_S6[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("Le studio choisit vide "));

            return;
        }

    }else if (numero == "S7") {

        if(liste_affiche_S7[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("Le studio choisit vide "));

            return;
        }

    }else if (numero == "S8") {

        if(liste_affiche_S8[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("Le studio choisit est vide "));

            return;
        }
    }

    //On demande confirmation avant
    //Affiche codification correcte
    QString codification = "";
    if(numero == "S1")
        codification = "ST 01";
    else if (numero == "S2") {
        codification = "ST 02";

    }else if (numero == "S3") {
        codification = "ST 03";
    }
    else if (numero == "S4") {
        codification = "ST 04";

    }else if (numero == "S5") {
        codification = "ST 101"
                ;
    }else if (numero == "S6") {
        codification = "ST 102";

    }else if (numero == "S7") {
        codification = "ST 103";

    }else if (numero == "S8") {
        codification = "ST 104";
    }

    int ok = QMessageBox::warning (this,"Confirmation","Voulez vous libérez le studio " + codification + " ? ",QMessageBox::Yes|QMessageBox::No);

    if(ok==QMessageBox::No)
        return;

    //Script
    requetes.supprimeOccupantSt (numero);

    //On actualise
    chargerVue ();
}

void Fenetre::supprimerOccupantCh (){
    //Recupérer le numéro de l'appart
    QAction* objet = dynamic_cast<QAction*>(sender ());
    QString numero = objet->objectName ();

    //Changement d'onglet
    onglets->setCurrentIndex (indexC);
    if(numero == "CH1")
    {
        if(liste_affiche_Ch1[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("La chambre choisit est vide "));

            return;
        }

    }
    else if (numero == "CH2") {

        if(liste_affiche_Ch2[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("La chambre choisit est vide "));

            return;
        }

    }else if (numero == "CH3") {

        if(liste_affiche_Ch3[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("La chambre choisit est vide "));

            return;
        }

    }
    else if (numero == "CH4") {

        if(liste_affiche_Ch4[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("La chambre choisit est vide "));

            return;
        }

    }
    //On demande confirmation avant
    //Affiche codification correcte
    QString codification = "";
    if(numero == "CH1")
        codification = "CH 101";
    else if (numero == "CH2") {
        codification = "CH 102";

    }else if (numero == "CH3") {
        codification = "CH 103";
    }
    else if (numero == "CH4") {
        codification = "CH 104";
    }

    int ok = QMessageBox::warning (this,"Confirmation","Voulez vous libérez la chambre " + codification + " ? ",QMessageBox::Yes|QMessageBox::No);

    if(ok==QMessageBox::No)
        return;

    //Script
    requetes.supprimeOccupantCh (numero);

    //On actualise
    chargerVue ();

}

void Fenetre::supprimerOccupantBt (){
    //Recupérer le numéro de l'appart
    QAction* objet = dynamic_cast<QAction*>(sender ());
    QString numero = objet->objectName ();

    //Changement d'onglet
    onglets->setCurrentIndex (indexB);

    if(numero == "B1")
    {
        if(liste_affiche_B1[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("La boutique choisit est vide "));

            return;
        }

    }
    else if (numero == "B2") {

        if(liste_affiche_B2[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("La boutique choisit est vide "));

            return;
        }

    }else if (numero == "B3") {

        if(liste_affiche_B3[1].contains ("Libre")){
            QMessageBox::warning (this,tr("Attention"),tr("La boutique choisit est vide "));

            return;
        }

    }

    //On demande confirmation avant
    //Affiche codification correcte
    QString codification = "";
    if(numero == "B1")
        codification = "B 01";
    else if (numero == "B2") {
        codification = "B 02";
    }else if (numero == "B3") {
        codification = "B 03";
    }

    int ok = QMessageBox::warning (this,"Confirmation","Voulez vous libérez la boutique " + codification + " ? ",QMessageBox::Yes|QMessageBox::No);

    if(ok==QMessageBox::No)
        return;

    //Libération
    requetes.supprimeOccupantBt (numero);

    //On actualise
    chargerVue ();
}

//Ajout probleme
void Fenetre::ajoutProblemeAp (){
    QAction *objet = dynamic_cast<QAction*>( sender () );
    QString numero = objet->objectName ();

    //Affiche codification correcte
    QString codification = "";
    if(numero == "A1")
        codification = "APT 01";
    else if (numero == "A2") {
        codification = "APT 02";
    }else if (numero == "A3") {
        codification = "APT 101";
    }
    else if (numero == "A4") {
        codification = "APT 102";
    }

    //...

    //On récupère le information sur le probleme
    QString *probleme = new QString("");
    QString *date = new QString("");

    Dialog *diag = new Dialog(probleme,date);
    diag->titre->setText (tr("Décrire le problème de l'appartement ") + codification);
    diag->exec ();

    if(probleme->isEmpty ())
        return;

    //On lance le script d'ajout
    requetes.ajoutProblemeAp (numero,*probleme,*date);
}

void Fenetre::ajoutProblemeSt (){
    QAction *objet = dynamic_cast<QAction*>( sender () );
    QString numero = objet->objectName ();

    //Affiche codification correcte
    QString codification = "";
    if(numero == "S1")
        codification = "ST 01";
    else if (numero == "S2") {
        codification = "ST 02";

    }else if (numero == "S3") {
        codification = "ST 03";
    }
    else if (numero == "S4") {
        codification = "ST 04";

    }else if (numero == "S5") {
        codification = "ST 101"
                ;
    }else if (numero == "S6") {
        codification = "ST 102";

    }else if (numero == "S7") {
        codification = "ST 103";

    }else if (numero == "S8") {
        codification = "ST 104";
    }


    //On récupère le information sur le probleme
    QString *probleme = new QString("");
    QString *date = new QString("");

    Dialog *diag = new Dialog(probleme,date);
    diag->titre->setText (tr("Décrire le problème du studio ") + codification);
    diag->exec ();

    if(probleme->isEmpty ())
        return;

    //On lance le script d'ajout
    requetes.ajoutProblemeSt (numero,*probleme,*date);
}

void Fenetre::ajoutProblemeCh (){
    QAction *objet = dynamic_cast<QAction*>( sender () );
    QString numero = objet->objectName ();

    //Affiche codification correcte
    QString codification = "";
    if(numero == "CH1")
        codification = "CH 101";
    else if (numero == "CH2") {
        codification = "CH 102";

    }else if (numero == "CH3") {
        codification = "CH 103";
    }
    else if (numero == "CH4") {
        codification = "CH 104";
    }

    //On récupère le information sur le probleme
    QString *probleme = new QString("");
    QString *date = new QString("");

    Dialog *diag = new Dialog(probleme,date);
    diag->titre->setText (tr("Décrire le problème de la chambre  ") + codification);
    diag->exec ();

    if(probleme->isEmpty ())
        return;

    //On lance le script d'ajout
    requetes.ajoutProblemeCh (numero,*probleme,*date);
}

void Fenetre::ajoutProblemeBt (){
    QAction *objet = dynamic_cast<QAction*>( sender () );
    QString numero = objet->objectName ();

    //Affiche codification correcte
    QString codification = "";
    if(numero == "B1")
        codification = "B 01";
    else if (numero == "B2") {
        codification = "B 02";
    }else if (numero == "B3") {
        codification = "B 03";
    }

    //On récupère le information sur le probleme
    QString *probleme = new QString("");
    QString *date = new QString("");

    Dialog *diag = new Dialog(probleme,date);
    diag->titre->setText (tr("Décrire le problème de la boutique ") + codification);
    diag->exec ();

    if(probleme->isEmpty ())
        return;

    //On lance le script d'ajout
    requetes.ajoutProblemeBt (numero,*probleme,*date);
}


//Historique
void Fenetre::historiqueOccupantAp (){

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery ("SELECT numeroAO,nom,prenom,cni,age,profession,date_entree,date_sortie,contact,pays,ville,adresse,email FROM Personnes,Occupants,OccupeAp WHERE idP=idPO AND idAO=Occupants.rowid");

    model->setHeaderData (0,Qt::Horizontal,tr("Appartements"));
    model->setHeaderData (1,Qt::Horizontal,tr("Nom"));
    model->setHeaderData (2,Qt::Horizontal,tr("Prenom"));
    model->setHeaderData (3,Qt::Horizontal,tr("Carte d'identité"));
    model->setHeaderData (4,Qt::Horizontal,tr("Date naissance"));
    model->setHeaderData (5,Qt::Horizontal,tr("Profession"));
    model->setHeaderData (6,Qt::Horizontal,tr("Date d'entrée"));
    model->setHeaderData (7,Qt::Horizontal,tr("Date libération"));
    model->setHeaderData (8,Qt::Horizontal,tr("Téléphone"));
    model->setHeaderData (9,Qt::Horizontal,tr("Pays"));
    model->setHeaderData (10,Qt::Horizontal,tr("Ville"));
    model->setHeaderData (11,Qt::Horizontal,tr("Adresse"));
    model->setHeaderData (12,Qt::Horizontal,tr("Email"));

    if(model->record (0).value (0).isNull ())
    {
        QMessageBox::information (this,"Information","Aucun occupants enregistrer dans un appartement !");
        return;
    }

    QTableView *view = new QTableView;
    view->setModel (model);
    view->setColumnWidth (1,100);
    view->setColumnWidth (6,150);
    view->setMinimumSize (QSize(1017,480));
    view->setWordWrap (false);
    view->setFont (QFont("Arial",16,60));
    view->setWindowTitle (tr("KASTYVOX"));
    view->show ();
}

void Fenetre::historiqueOccupantSt (){
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery ("SELECT numeroStO,nom,prenom,cni,age,profession,date_entree,date_sortie,contact,pays,ville,adresse,email FROM Personnes , Occupants , OccupeSt WHERE idP=idPO AND idStO=Occupants.rowid");

    model->setHeaderData (0,Qt::Horizontal,tr("Appartements"));
    model->setHeaderData (1,Qt::Horizontal,tr("Nom"));
    model->setHeaderData (2,Qt::Horizontal,tr("Prenom"));
    model->setHeaderData (3,Qt::Horizontal,tr("Carte d'identité"));
    model->setHeaderData (4,Qt::Horizontal,tr("Date naissance"));
    model->setHeaderData (5,Qt::Horizontal,tr("Profession"));
    model->setHeaderData (6,Qt::Horizontal,tr("Date d'entrée"));
    model->setHeaderData (7,Qt::Horizontal,tr("Date libération"));
    model->setHeaderData (8,Qt::Horizontal,tr("Téléphone"));
    model->setHeaderData (9,Qt::Horizontal,tr("Pays"));
    model->setHeaderData (10,Qt::Horizontal,tr("Ville"));
    model->setHeaderData (11,Qt::Horizontal,tr("Adresse"));
    model->setHeaderData (12,Qt::Horizontal,tr("Email"));

    if(model->record (0).value (0).isNull ())
    {
        QMessageBox::information (this,"Information","Aucun occupants enregistrer dans un studio !");
        return;
    }

    QTableView *view = new QTableView;
    view->setModel (model);
    view->setColumnWidth (1,100);
    view->setColumnWidth (6,150);
    view->setMinimumSize (QSize(1017,480));
    view->setWordWrap (false);
    view->setFont (QFont("Arial",16,60));
    view->setWindowTitle (tr("KASTYVOX"));
    view->show ();
}

void Fenetre::historiqueOccupantCh (){
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery ("SELECT numeroChO,nom,prenom,cni,age,profession,date_entree,date_sortie,contact,pays,ville,adresse,email FROM Personnes , Occupants , OccupeCh WHERE idP=idPO AND idChO=Occupants.rowid");

    model->setHeaderData (0,Qt::Horizontal,tr("Appartements"));
    model->setHeaderData (1,Qt::Horizontal,tr("Nom"));
    model->setHeaderData (2,Qt::Horizontal,tr("Prenom"));
    model->setHeaderData (3,Qt::Horizontal,tr("Carte d'identité"));
    model->setHeaderData (4,Qt::Horizontal,tr("Date naissance"));
    model->setHeaderData (5,Qt::Horizontal,tr("Profession"));
    model->setHeaderData (6,Qt::Horizontal,tr("Date d'entrée"));
    model->setHeaderData (7,Qt::Horizontal,tr("Date libération"));
    model->setHeaderData (8,Qt::Horizontal,tr("Téléphone"));
    model->setHeaderData (9,Qt::Horizontal,tr("Pays"));
    model->setHeaderData (10,Qt::Horizontal,tr("Ville"));
    model->setHeaderData (11,Qt::Horizontal,tr("Adresse"));
    model->setHeaderData (12,Qt::Horizontal,tr("Email"));


    if(model->record (0).value (0).isNull ())
    {
        QMessageBox::information (this,"Information","Aucun occupants enregistrer dans une chambre !");
        return;
    }

    QTableView *view = new QTableView;
    view->setModel (model);
    view->setColumnWidth (1,100);
    view->setColumnWidth (6,150);
    view->setMinimumSize (QSize(1017,480));
    view->setWordWrap (false);
    view->setFont (QFont("Arial",16,60));
    view->setWindowTitle (tr("KASTYVOX"));
    view->show ();
}

void Fenetre::historiqueOccupantBt (){
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery ("SELECT numeroBtO,nom,prenom,cni,age,profession,date_entree,date_sortie,contact,pays,ville,adresse,email FROM Personnes , Occupants , OccupeBt WHERE idP = idPO AND idBtO=Occupants.rowid");

    model->setHeaderData (0,Qt::Horizontal,tr("Appartements"));
    model->setHeaderData (1,Qt::Horizontal,tr("Nom"));
    model->setHeaderData (2,Qt::Horizontal,tr("Prenom"));
    model->setHeaderData (3,Qt::Horizontal,tr("Carte d'identité"));
    model->setHeaderData (4,Qt::Horizontal,tr("Date naissance"));
    model->setHeaderData (5,Qt::Horizontal,tr("Profession"));
    model->setHeaderData (6,Qt::Horizontal,tr("Date d'entrée"));
    model->setHeaderData (7,Qt::Horizontal,tr("Date libération"));
    model->setHeaderData (8,Qt::Horizontal,tr("Téléphone"));
    model->setHeaderData (9,Qt::Horizontal,tr("Pays"));
    model->setHeaderData (10,Qt::Horizontal,tr("Ville"));
    model->setHeaderData (11,Qt::Horizontal,tr("Adresse"));
    model->setHeaderData (12,Qt::Horizontal,tr("Email"));

    if(model->record (0).value (0).isNull ())
    {
        QMessageBox::information (this,"Information","Aucun occupants enregistrer dans une boutiques !");
        return;
    }

    QTableView *view = new QTableView;
    view->setModel (model);
    view->setColumnWidth (1,100);
    view->setColumnWidth (6,150);
    view->setMinimumSize (QSize(1017,480));
    view->setWordWrap (false);
    view->setFont (QFont("Arial",16,60));
    view->setWindowTitle (tr("KASTYVOX"));
    view->show ();
}

//Probleme

void Fenetre::historiqueProblemeAp (){
    QSqlTableModel *model_tableau = new QSqlTableModel(this,requetes.kastyvox_db);
    model_tableau->setTable ("ProblemeAp");
    model_tableau->select ();

    QSqlRecord ligne;
    int i = 0;
    ligne = model_tableau->record (i); // Première ligne

    QString affichageLigne = "";

    QStringList historiques;

    //Avec QListView
    QStringListModel *model = new QStringListModel;
    QListView *vue = new QListView;
    vue->setObjectName ("normal");

    while (!ligne.value (0).isNull ()) {

        QString numero = ligne.value ("numeroA").toString ();
        //Affiche codification correcte
        QString codification = "";
        if(numero == "A1")
            codification = "APT 01";
        else if (numero == "A2") {
            codification = "APT 02";
        }else if (numero == "A3") {
            codification = "APT 101";
        }
        else if (numero == "A4") {
            codification = "APT 102";
        }

        //...

        affichageLigne = "\t\t Appartement  " + codification + "\n";
        affichageLigne += "\t\t Date : " + ligne.value ("date").toDate ().toString (Qt::SystemLocaleLongDate) + "\n\n";
        affichageLigne += "Problème  :  " + ligne.value ("probleme").toString () +"\n";

        historiques << affichageLigne;

        i++;
        ligne = model_tableau->record (i);
    }

    if(historiques.isEmpty ())
    {
        QMessageBox::information (this,"Info","Il n'y a pas de problème dans les appartements !");
        return;
    }

    model->setStringList (historiques);
    vue->setModel (model);
    vue->setWindowTitle (tr("KASTYVOX"));
    vue->setMinimumSize (QSize(640,480));
    vue->show();

}

void Fenetre::historiqueProblemeSt (){
    QSqlTableModel *model_tableau = new QSqlTableModel(this,requetes.kastyvox_db);
    model_tableau->setTable ("ProblemeSt");
    model_tableau->select ();

    QSqlRecord ligne;
    int i = 0;
    ligne = model_tableau->record (i); // Première ligne

    QString affichageLigne = "";

    QStringList historiques;

    //Avec QListView
    QStringListModel *model = new QStringListModel;
    QListView *vue = new QListView;
    vue->setObjectName ("normal");

    while (!ligne.value (0).isNull ()) {
        QString numero = ligne.value ("numeroS").toString ();
        //Affiche codification correcte
        QString codification = "";
        if(numero == "S1")
            codification = "ST 01";
        else if (numero == "S2") {
            codification = "ST 02";

        }else if (numero == "S3") {
            codification = "ST 03";
        }
        else if (numero == "S4") {
            codification = "ST 04";

        }else if (numero == "S5") {
            codification = "ST 101"
                    ;
        }else if (numero == "S6") {
            codification = "ST 102";

        }else if (numero == "S7") {
            codification = "ST 103";

        }else if (numero == "S8") {
            codification = "ST 104";
        }



        affichageLigne = "\t\t Studio  " + codification + "\n";
        affichageLigne += "\t\t Date : " + ligne.value ("date").toDate ().toString (Qt::SystemLocaleLongDate) + "\n\n";
        affichageLigne += "Problème  :  " + ligne.value ("probleme").toString () +"\n";

        historiques << affichageLigne;

        i++;
        ligne = model_tableau->record (i);
    }

    if(historiques.isEmpty ())
    {
        QMessageBox::information (this,"Info","Il n'y a pas de problème dans les studios !");
        return;
    }

    model->setStringList (historiques);
    vue->setModel (model);
    vue->setWindowTitle (tr("KASTYVOX"));
    vue->setMinimumSize (QSize(640,480));
    vue->show();

}

void Fenetre::historiqueProblemeCh (){
    QSqlTableModel *model_tableau = new QSqlTableModel(this,requetes.kastyvox_db);
    model_tableau->setTable ("ProblemeCh");
    model_tableau->select ();

    QSqlRecord ligne;
    int i = 0;
    ligne = model_tableau->record (i); // Première ligne

    QString affichageLigne = "";

    QStringList historiques;

    //Avec QListView
    QStringListModel *model = new QStringListModel;
    QListView *vue = new QListView;
    vue->setObjectName ("normal");

    while (!ligne.value (0).isNull ()) {

        QString numero = ligne.value ("numeroC").toString ();
        //Affiche codification correcte
        QString codification = "";
        if(numero == "CH1")
            codification = "CH 101";
        else if (numero == "CH2") {
            codification = "CH 102";

        }else if (numero == "CH3") {
            codification = "CH 103";
        }
        else if (numero == "CH4") {
            codification = "CH 104";
        }

        affichageLigne = "\t\t Chambre  " + codification + "\n";
        affichageLigne += "\t\t Date : " + ligne.value ("date").toDate ().toString (Qt::SystemLocaleLongDate) + "\n\n";
        affichageLigne += "Problème  :  " + ligne.value ("probleme").toString () +"\n";

        historiques << affichageLigne;

        i++;
        ligne = model_tableau->record (i);
    }

    if(historiques.isEmpty ())
    {
        QMessageBox::information (this,"Info","Il n'y a pas de problème dans les chambres !");
        return;
    }

    model->setStringList (historiques);
    vue->setModel (model);
    vue->setWindowTitle (tr("KASTYVOX"));
    vue->setMinimumSize (QSize(640,480));
    vue->show();

}

void Fenetre::historiqueProblemeBt (){
    QSqlTableModel *model_tableau = new QSqlTableModel(this,requetes.kastyvox_db);
    model_tableau->setTable ("ProblemeBt");
    model_tableau->select ();

    QSqlRecord ligne;
    int i = 0;
    ligne = model_tableau->record (i); // Première ligne

    QString affichageLigne = "";

    QStringList historiques;

    //Avec QListView
    QStringListModel *model = new QStringListModel;
    QListView *vue = new QListView;
    vue->setObjectName ("normal");

    while (!ligne.value (0).isNull ()) {

        QString numero = ligne.value ("numeroB").toString ();
        //Affiche codification correcte
        QString codification = "";
        if(numero == "B1")
            codification = "B 01";
        else if (numero == "B2") {
            codification = "B 02";
        }else if (numero == "B3") {
            codification = "B 03";
        }

        affichageLigne = "\t\t Boutique  " + codification + "\n";
        affichageLigne += "\t\t Date : " + ligne.value ("date").toDate ().toString (Qt::SystemLocaleLongDate) + "\n\n";
        affichageLigne += "Problème  :  " + ligne.value ("probleme").toString () +"\n";

        historiques << affichageLigne;

        i++;
        ligne = model_tableau->record (i);
    }

    if(historiques.isEmpty ())
    {
        QMessageBox::information (this,"Info","Il n'y a pas de problème dans les boutiques !");
        return;
    }

    model->setStringList (historiques);
    vue->setModel (model);

    vue->setMinimumSize (QSize(640,480));
    vue->setWindowTitle (tr("KASTYVOX"));
    vue->show();

}

//Détails occupants
void Fenetre::detailsOccupantsAp (){
    QAction *objet = dynamic_cast<QAction*>(sender ());
    QString numero = objet->objectName ();

    QSqlQuery *requet = new QSqlQuery(requetes.kastyvox_db);
    requet->prepare ("SELECT cni,nom,prenom,age,profession,contact,pays,ville,adresse,email,commentaires FROM Personnes , OccupeAp WHERE idP=idAO AND numeroAO = :num");
    requet->bindValue (":num",numero);
    requet->exec ();

    if(!requet->last ())
    {
        QMessageBox::information (this,"Information","Pas d'occupant correspondant !");
        return;
    }

    QStringList details;
    QStringListModel *model = new QStringListModel;
    QListView *vue = new QListView;

    details << "CNI  :  " + requet->value (0).toString ();
    details << "\nNom et prenom  :  " + requet->value (1).toString () + "  " +requet->value (2).toString ();
    details << "\nDate naissance : " + QString::fromLatin1 ("%1").arg (requet->value (3).toString ());
    details << "\nProfession :  "+requet->value (4).toString ();
    details << "\nTéléphone :  "+requet->value (5).toString ();
    details << "\nPays :  "+requet->value (6).toString ();
    details << "\nVille :  "+requet->value (7).toString ();
    details << "\nAdresse :  "+requet->value (8).toString ();
    details << "\nEmail :  "+requet->value (9).toString ();
    details << "\nObservation : "+requet->value (10).toString ();

    model->setStringList (details);
    vue->setModel (model);
    vue->setMinimumSize (QSize(640,500));
    vue->setObjectName ("vert");
    vue->setWindowTitle (tr("KASTYVOX"));
    vue->show ();
}

void Fenetre::detailsOccupantsSt (){
    QAction *objet = dynamic_cast<QAction*>(sender ());
    QString numero = objet->objectName ();

    QSqlQuery *requet = new QSqlQuery(requetes.kastyvox_db);
    requet->prepare ("SELECT cni,nom,prenom,age,profession,contact,pays,ville,adresse,email,commentaires FROM Personnes , OccupeSt WHERE idP=idStO AND numeroStO = :num");
    requet->bindValue (":num",numero);
    requet->exec ();

    if(!requet->last ())
    {
        QMessageBox::information (this,"Information","Pas d'occupant correspondant !");
        return;
    }

    QStringList details;
    QStringListModel *model = new QStringListModel;
    QListView *vue = new QListView;

    details << "CNI  :  " + requet->value (0).toString ();
    details << "\nNom et prenom  :  " + requet->value (1).toString () + "  " +requet->value (2).toString ();
    details << "\nDate naissance :  " + QString::fromLatin1 ("%1").arg (requet->value (3).toString());
    details << "\nProfession :  "+requet->value (4).toString ();
    details << "\nTéléphone :  "+requet->value (5).toString ();
    details << "\nPays :  "+requet->value (6).toString ();
    details << "\nVille :  "+requet->value (7).toString ();
    details << "\nAdresse :  "+requet->value (8).toString ();
    details << "\nEmail :  "+requet->value (9).toString ();
    details << "\nObservations : "+requet->value (10).toString ();

    model->setStringList (details);
    vue->setModel (model);
    vue->setMinimumSize (QSize(640,500));
    vue->setObjectName ("vert");
    vue->setWindowTitle (tr("KASTYVOX"));
    vue->show ();

}

void Fenetre::detailsOccupantsCh (){
    QAction *objet = dynamic_cast<QAction*>(sender ());
    QString numero = objet->objectName ();

    QSqlQuery *requet = new QSqlQuery(requetes.kastyvox_db);
    requet->prepare ("SELECT cni,nom,prenom,age,profession,contact,pays,ville,adresse,email,commentaires FROM Personnes , OccupeCh WHERE idP=idChO AND numeroChO = :num");
    requet->bindValue (":num",numero);
    requet->exec ();

    if(!requet->last ())
    {
        QMessageBox::information (this,"Information","Pas d'occupant correspondant !");
        return;
    }

    QStringList details;
    QStringListModel *model = new QStringListModel;
    QListView *vue = new QListView;

    details << "CNI  :  " + requet->value (0).toString ();
    details << "\nNom et prenom  :  " + requet->value (1).toString () + "  " +requet->value (2).toString ();
    details << "\nDate naissance :  " + QString::fromLatin1 ("%1").arg (requet->value (3).toString());
    details << "\nProfession :  "+requet->value (4).toString ();
    details << "\nTéléphone :  "+requet->value (5).toString ();
    details << "\nPays :  "+requet->value (6).toString ();
    details << "\nVille :  "+requet->value (7).toString ();
    details << "\nAdresse :  "+requet->value (8).toString ();
    details << "\nEmail :  "+requet->value (9).toString ();
    details << "\nObservations : "+requet->value (10).toString ();

    model->setStringList (details);
    vue->setModel (model);
    vue->setMinimumSize (QSize(640,500));
    vue->setObjectName ("vert");
    vue->setWindowTitle (tr("KASTYVOX"));
    vue->show ();

}

void Fenetre::detailsOccupantsBt (){
    QAction *objet = dynamic_cast<QAction*>(sender ());
    QString numero = objet->objectName ();

    QSqlQuery *requet = new QSqlQuery(requetes.kastyvox_db);
    requet->prepare ("SELECT cni,nom,prenom,age,profession,contact,pays,ville,adresse,email,commentaires FROM Personnes , OccupeBt WHERE idP=idBtO AND numeroBtO = :num");
    requet->bindValue (":num",numero);
    requet->exec ();

    if(!requet->last ())
    {
        QMessageBox::information (this,"Information","Pas d'occupant correspondant !");
        return;
    }

    QStringList details;
    QStringListModel *model = new QStringListModel;
    QListView *vue = new QListView;

    details << "CNI  :  " + requet->value (0).toString ();
    details << "\nNom et prenom  :  " + requet->value (1).toString () + "  " +requet->value (2).toString ();
    details << "\nDate naissance :  " + QString::fromLatin1 ("%1").arg (requet->value (3).toString());
    details << "\nProfession :  "+requet->value (4).toString ();
    details << "\nTéléphone :  "+requet->value (5).toString ();
    details << "\nPays :  "+requet->value (6).toString ();
    details << "\nVille :  "+requet->value (7).toString ();
    details << "\nAdresse :  "+requet->value (8).toString ();
    details << "\nEmail :  "+requet->value (9).toString ();
    details << "\nObservations : "+requet->value (10).toString ();

    model->setStringList (details);
    vue->setModel (model);
    vue->setMinimumSize (QSize(640,500));
    vue->setObjectName ("vert");
    vue->setWindowTitle (tr("KASTYVOX"));
    vue->show ();

}


//Modifier Personnes
void Fenetre::modifierPersonnes (){
    QSqlTableModel *model = new QSqlTableModel(nullptr,requetes.kastyvox_db);
        model->setTable("Personnes");
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->select();

        model->setHeaderData (0,Qt::Horizontal,"Index");
        model->setHeaderData (1,Qt::Horizontal,"Carte d'identité");
        model->setHeaderData (2,Qt::Horizontal,"Nom");
        model->setHeaderData (3,Qt::Horizontal,"Prenom");
        model->setHeaderData (4,Qt::Horizontal,"Date naissance");
        model->setHeaderData (5,Qt::Horizontal,"Profession");
        model->setHeaderData (6,Qt::Horizontal,"Téléphone");
        model->setHeaderData (7,Qt::Horizontal,"Pays");
        model->setHeaderData (8,Qt::Horizontal,"Ville");
        model->setHeaderData (9,Qt::Horizontal,"Adresse");
        model->setHeaderData (10,Qt::Horizontal,"Email");
        model->setHeaderData (11,Qt::Horizontal,"Cni Délivré le ");
        model->setHeaderData (12,Qt::Horizontal,"Cni Délivré à ");
        model->setHeaderData (13,Qt::Horizontal,"Observations ");

        QTableView *view = new QTableView;
        view->setModel(model);

        view->setMinimumWidth (1200);

        view->setColumnHidden(0,true);
        view->setColumnWidth (0,55);
        view->setColumnWidth (1,155);
        view->setColumnWidth (2,155);
        view->setColumnWidth (3,155);
        view->setColumnWidth (6,200);
        view->setColumnWidth (10,200);

        //view->setWindowTitle (tr("KASTYVOX"));
        view->setAcceptDrops (true);
        view->setDragEnabled (true);

        QDialog *boite = new QDialog;
        boite->setWindowTitle (tr("KASTYVOX"));

        QVBoxLayout *vbox = new QVBoxLayout;
            vbox->addWidget (view);
            QPushButton *bouton = new QPushButton(tr("Sauvegarder"));
            QPushButton *annuler = new QPushButton(tr("Annuler"));

            QHBoxLayout *hbox = new QHBoxLayout;
                hbox->addWidget (bouton);
                hbox->addWidget (annuler);

            vbox->addLayout (hbox);

            connect (bouton,&QPushButton::clicked,boite,&QDialog::accept);
            connect (annuler,&QPushButton::clicked,boite,&QDialog::reject);
            connect (boite,&QDialog::accepted,model,&QSqlRelationalTableModel::submitAll);
            connect (boite,&QDialog::accepted,model,&QSqlRelationalTableModel::submit);

        boite->setLayout (vbox);
        boite->exec ();

        chargerVue ();


}

//Modifier Dates
void Fenetre::modifierDates (){

    QHBoxLayout *princH = new QHBoxLayout;

    QSqlTableModel *modelPersonnes = new QSqlTableModel(nullptr,requetes.kastyvox_db);
        modelPersonnes->setTable("Personnes");
        modelPersonnes->setEditStrategy(QSqlTableModel::OnManualSubmit);
        modelPersonnes->select();

        modelPersonnes->setHeaderData (0,Qt::Horizontal,"Index");
        modelPersonnes->setHeaderData (1,Qt::Horizontal,"Carte d'identité");
        modelPersonnes->setHeaderData (2,Qt::Horizontal,"Nom");
        modelPersonnes->setHeaderData (3,Qt::Horizontal,"Prenom");
        modelPersonnes->setHeaderData (4,Qt::Horizontal,"Date naissance");
        modelPersonnes->setHeaderData (5,Qt::Horizontal,"Profession");
        modelPersonnes->setHeaderData (6,Qt::Horizontal,"Téléphone");
        modelPersonnes->setHeaderData (7,Qt::Horizontal,"Pays");
        modelPersonnes->setHeaderData (8,Qt::Horizontal,"Ville");
        modelPersonnes->setHeaderData (9,Qt::Horizontal,"Adresse");
        modelPersonnes->setHeaderData (10,Qt::Horizontal,"Email");
        modelPersonnes->setHeaderData (11,Qt::Horizontal,"Cni Délivré le ");
        modelPersonnes->setHeaderData (12,Qt::Horizontal,"Cni Délivré à ");
        modelPersonnes->setHeaderData (13,Qt::Horizontal,"Observations ");

        QTableView *viewPersonnes = new QTableView;
        viewPersonnes->setModel(modelPersonnes);

        viewPersonnes->setMinimumWidth(400);
        viewPersonnes->setColumnWidth (2,200);
        viewPersonnes->setColumnWidth (3,200);

        viewPersonnes->setColumnHidden(1,true);
        viewPersonnes->setColumnHidden(0,true);
        viewPersonnes->setColumnHidden(4,true);
        viewPersonnes->setColumnHidden(5,true);
        viewPersonnes->setColumnHidden(6,true);
        viewPersonnes->setColumnHidden(7,true);
        viewPersonnes->setColumnHidden(8,true);
        viewPersonnes->setColumnHidden(9,true);
        viewPersonnes->setColumnHidden(10,true);
        viewPersonnes->setColumnHidden(11,true);
        viewPersonnes->setColumnHidden(12,true);
        viewPersonnes->setColumnHidden(13,true);

        princH->addWidget(viewPersonnes);

    QSqlRelationalTableModel *model = new QSqlRelationalTableModel(nullptr,requetes.kastyvox_db);
        model->setTable("Occupants");
        model->select ();

        model->setHeaderData (1,Qt::Horizontal,"Date d'entrée");
        model->setHeaderData (2,Qt::Horizontal,"Date de sortie");
        model->setHeaderData (3,Qt::Horizontal,"Date de fin de séjour");


        model->setEditStrategy(QSqlTableModel::OnManualSubmit);

        QTableView *view = new QTableView;
        view->setModel(model);

        view->setItemDelegate (new QSqlRelationalDelegate(view));
        view->setColumnHidden(0,true);
        view->setMinimumWidth (900);
        view->setColumnWidth (4,200);
        view->setColumnWidth (1,200);
        view->setColumnWidth (2,200);
        view->setColumnWidth (3,200);

        //view->setWindowTitle (tr("KASTYVOX"));

        QDialog *boite = new QDialog;
        boite->setWindowTitle (tr("KASTYVOX"));

        QVBoxLayout *vbox = new QVBoxLayout;
            vbox->addWidget (view);
            QPushButton *bouton = new QPushButton(tr("Sauvegarder"));
            QPushButton *annuler = new QPushButton(tr("Annuler"));

            QHBoxLayout *hbox = new QHBoxLayout;
                hbox->addWidget (bouton);
                hbox->addWidget (annuler);

            vbox->addLayout (hbox);

            connect (bouton,&QPushButton::clicked,boite,&QDialog::accept);
            connect (annuler,&QPushButton::clicked,boite,&QDialog::reject);
            connect (boite,&QDialog::accepted,model,&QSqlRelationalTableModel::submitAll);
            connect (boite,&QDialog::accepted,model,&QSqlRelationalTableModel::submit);

        princH->addLayout(vbox);
        boite->setLayout (princH);
        boite->exec ();

        chargerVue ();

}
