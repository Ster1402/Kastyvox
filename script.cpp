#include "script.h"
#include "dialog.h"

#include <iostream>
#include <QFile>
#include <QLabel>
#include <QSqlRecord>
#include <QDate>
#include <QDebug>
#include <QMessageBox>
#include <QApplication>

Script::Script()
{
    chargerDB ();
    script_requete = new QSqlQuery(kastyvox_db);

    //Préparation de la palette rouge et verte
    colorG = QColor(62,201,36);
    colorR = QColor(201,72,66);

    paletteVerte = QPalette();
    paletteVerte.setColor (QPalette::Window,colorG);

    paletteRouge = QPalette();
    paletteRouge.setColor (QPalette::Base,colorR);
}

void Script::chargerDB(){
    kastyvox_db = QSqlDatabase::addDatabase ("QSQLITE");
        kastyvox_db.setHostName ("localhost");
        kastyvox_db.setDatabaseName ("KASTYVOX_DB.sqlite");

    if(kastyvox_db.open ())
        qDebug("Base de donnée ouverte");

}

void Script::updateDB(){
    qDebug("KASTYVOX_DB : updateDB ");

    //Update Personnes
    if(script_requete->exec("ALTER TABLE Personnes RENAME TO tmp;"))
        qDebug("RENAME SUCCESSFULL");

    if(script_requete->exec("CREATE TABLE Personnes (idP INTEGER PRIMARY KEY,cni VARCHAR(30) NOT NULL UNIQUE,nom VARCHAR(30) NOT NULL,prenom VARCHAR(30) NULL,age DATE,profession VARCHAR(30),contact VARCHAR(70), pays VARCHAR(30), ville VARCHAR(30), adresse VARCHAR(30),email VARCHAR(30), cni_le DATE, cni_a VARCHAR(20),commentaires VARCHAR(50));"))
        qDebug("NEW TABLE CREATE");

    if(script_requete->exec("INSERT INTO Personnes SELECT * FROM tmp;"))
        qDebug("VALUE COPY SUCCESSFULL");

    if(script_requete->exec("DROP TABLE tmp;"))
        qDebug("DROP TEMPORALY TABLE");

    //Update Occupants
    if(script_requete->exec("CREATE TABLE OccupantsNew (idPO INTEGER NOT NULL,date_entree DATE NOT NULL,date_sortie DATE NULL, date_fin_sejour DATE, date_butoire DATE,FOREIGN KEY(idPO) REFERENCES Personnes ON DELETE CASCADE, PRIMARY KEY(idPO,date_entree,date_fin_sejour));")) //A vérifier
        qDebug("OCCUPANTS NEW");

    if(script_requete->exec("INSERT INTO OccupantsNew(idPO,date_entree,date_sortie,date_fin_sejour,date_butoire) SELECT idPO,date_entree,date_sortie,date_fin_sejour,date_butoire FROM Occupants;"))
        qDebug("INSERT Occupants New");

    if(script_requete->exec("DROP TABLE Occupants;"))
        qDebug("DROP Occupants");

    if(script_requete->exec("ALTER TABLE OccupantsNew RENAME TO Occupants;"))
        qDebug("UPDATE Occupants FINISH");

    //Update OccupeAp
    if(script_requete->exec("CREATE TABLE OccupeAPNew(idAO INTEGER,numeroAO CHAR(2),FOREIGN KEY(idAO) REFERENCES Occupants(rowid) ON DELETE CASCADE,FOREIGN KEY(numeroAO) REFERENCES Appartements(numero),PRIMARY KEY(idAO,numeroAO) );")){
        qDebug("OccupeAp new créer");
    }

    if(script_requete->exec("INSERT INTO OccupeAPNew(idAO,numeroAO) SELECT idAO,numeroAO FROM OccupeAP;") )
        qDebug("Insertion réussit");

    if(script_requete->exec("DROP TABLE OccupeAP;"))
        qDebug("DROP Old OccupeAP");

    if(script_requete->exec("ALTER TABLE OccupeAPNew RENAME TO OccupeAP;"))
        qDebug("UPDATE OccupeAp FINISH");

    //Mettre le temoin...
    if(script_requete->exec("CREATE TABLE Temoin (id INTEGER );"))
        qDebug("Témoin créer");
}

//Actualiser la base de donnée
void Script::actualiserDB(){

    qDebug("KASTYVOX_DB : Actualisation");

    if(!script_requete->exec("CREATE TABLE Temoin (id INTEGER);"))
    {
        qDebug("L'update est déjà effectuer");
        return;
    }

    if(script_requete->exec("CREATE TABLE Appartements(numero CHAR(2) NOT NULL,etat CHAR(1) NOT NULL CHECK (etat='L' OR etat='O'),prix INTEGER NOT NULL,PRIMARY KEY(numero));"))
       qDebug("KASTYVOX_DB : ActualiserDB() creation Appartements réussit ");

    if(script_requete->exec("CREATE TABLE Boutiques(numero CHAR(2) NOT NULL,etat CHAR(1) NOT NULL CHECK (etat IN ('L','O')),prix INTEGER NOT NULL,PRIMARY KEY(numero));"))
       qDebug("KASTYVOX_DB : ActualiserDB() creation Boutiques réussit ");

    if(script_requete->exec("CREATE TABLE Chambres (numero CHAR(3) NOT NULL,etat CHAR(1) NOT NULL CHECK (etat IN ('L','O')),prix INTEGER NOT NULL,PRIMARY KEY(numero));"))
       qDebug("KASTYVOX_DB : ActualiserDB() creation Chambres réussit ");

    if(script_requete->exec("CREATE TABLE Studios(numero CHAR(2) NOT NULL,etat CHAR(1) NOT NULL CHECK (etat IN ('L','O')),prix INTEGER NOT NULL,PRIMARY KEY(numero));"))
       qDebug("KASTYVOX_DB : ActualiserDB() creation Studios réussit ");

    if(script_requete->exec("CREATE TABLE Observations ( idOP INTEGER,observation TEXT, date DATE,FOREIGN KEY(idOP) REFERENCES Personnes ON DELETE CASCADE);"))
       qDebug("KASTYVOX_DB : ActualiserDB() creation Observations réussit ");

    if(script_requete->exec("CREATE TABLE Occupants( idPO INTEGER NOT NULL,date_entree DATE NOT NULL,date_sortie DATE NULL, date_fin_sejour DATE, date_butoire DATE,FOREIGN KEY(idPO) REFERENCES Personnes ON DELETE CASCADE ON UPDATE CASCADE,PRIMARY KEY(idPO));"))
       qDebug("KASTYVOX_DB : ActualiserDB() creation Occupants réussit ");

    if(script_requete->exec("CREATE TABLE OccupeAP(idAO INTEGER,numeroAO CHAR(2),FOREIGN KEY(idAO) REFERENCES Occupants(idPO) ON DELETE CASCADE,FOREIGN KEY(numeroAO) REFERENCES Appartements(numero),PRIMARY KEY(idAO,numeroAO) );"))
       qDebug("KASTYVOX_DB : ActualiserDB() creation OccupeAp réussit ");

    if(script_requete->exec("CREATE TABLE OccupeBt(idBtO INTEGER,numeroBtO CHAR(2),FOREIGN KEY(idBtO) REFERENCES Occupants(idPO) ON DELETE CASCADE,FOREIGN KEY(numeroBtO) REFERENCES Boutiques(numero),PRIMARY KEY(idBtO,numeroBtO) );"))
       qDebug("KASTYVOX_DB : ActualiserDB() creation OccupeBt réussit ");

    if(script_requete->exec("CREATE TABLE OccupeCh(idChO INTEGER,numeroChO CHAR(2),FOREIGN KEY(idChO) REFERENCES Occupants(idPO) ON DELETE CASCADE,FOREIGN KEY(numeroChO) REFERENCES Chambres(numero),PRIMARY KEY(idChO,numeroChO) );"))
       qDebug("KASTYVOX_DB : ActualiserDB() creation OccupeCh réussit ");

    if(script_requete->exec("CREATE TABLE OccupeSt(idStO INTEGER,numeroStO CHAR(2),FOREIGN KEY(idStO) REFERENCES Occupants(idPO) ON DELETE CASCADE,FOREIGN KEY(numeroStO) REFERENCES Studios(numero),PRIMARY KEY(idStO,numeroStO) );"))
       qDebug("KASTYVOX_DB : ActualiserDB() creation OccupeSt réussit ");

    //A modifier
    if(script_requete->exec("CREATE TABLE Personnes (idP INTEGER PRIMARY KEY,cni VARCHAR(30) NOT NULL UNIQUE,nom VARCHAR(30) NOT NULL,prenom VARCHAR(30) NULL,age INTEGER CHECK(age >= 20 AND age <= 100),profession VARCHAR(30),contact VARCHAR(70), pays VARCHAR(30), ville VARCHAR(30), adresse VARCHAR(30),email VARCHAR(30), cni_le DATE, cni_a VARCHAR(20),commentaires VARCHAR(50));"))
       qDebug("KASTYVOX_DB : ActualiserDB() creation Personnes réussit (à modifier) ");

    if(script_requete->exec("CREATE TABLE ProblemeAp ( numeroA CHAR(2) NOT NULL,probleme TEXT, date DATE, FOREIGN KEY(numeroA) REFERENCES Appartements );"))
       qDebug("KASTYVOX_DB : ActualiserDB() creation ProblemeAp réussit ");

    if(script_requete->exec("CREATE TABLE ProblemeBt ( numeroB CHAR(2) NOT NULL,probleme TEXT, date DATE, FOREIGN KEY(numeroB) REFERENCES Boutiques );"))
       qDebug("KASTYVOX_DB : ActualiserDB() creation ProblemeBt réussit ");

    if(script_requete->exec("CREATE TABLE ProblemeCh ( numeroC CHAR(3) NOT NULL,probleme TEXT, date DATE, FOREIGN KEY(numeroC) REFERENCES Chambres );"))
       qDebug("KASTYVOX_DB : ActualiserDB() creation ProblemeCh réussit ");

    if(script_requete->exec("CREATE TABLE ProblemeSt ( numeroS CHAR(2) NOT NULL,probleme TEXT, date DATE, FOREIGN KEY(numeroS) REFERENCES Studios );"))
       qDebug("KASTYVOX_DB : ActualiserDB() creation ProblemeSt réussit ");

    //Insertions
    if(script_requete->exec("INSERT INTO Boutiques VALUES('B1','L',30000);"))
       qDebug("KASTYVOX_DB : ActualiserDB() insertion réussit ");

    if(script_requete->exec("INSERT INTO Boutiques VALUES('B2','L',30000);"))
       qDebug("KASTYVOX_DB : ActualiserDB() insertion réussit ");

    if(script_requete->exec("INSERT INTO Boutiques VALUES('B3','L',30000);"))
       qDebug("KASTYVOX_DB : ActualiserDB() insertion réussit ");


    if(script_requete->exec("INSERT INTO Chambres VALUES('CH1','L',15000);"))
       qDebug("KASTYVOX_DB : ActualiserDB() insertion réussit ");

    if(script_requete->exec("INSERT INTO Chambres VALUES('CH2','L',15000);"))
       qDebug("KASTYVOX_DB : ActualiserDB() insertion réussit ");

    if(script_requete->exec("INSERT INTO Chambres VALUES('CH3','L',15000);"))
       qDebug("KASTYVOX_DB : ActualiserDB() insertion réussit ");

    if(script_requete->exec("INSERT INTO Chambres VALUES('CH4','L',15000);"))
       qDebug("KASTYVOX_DB : ActualiserDB() insertion réussit ");


    if(script_requete->exec("INSERT INTO Studios VALUES('S1','L',30000);"))
       qDebug("KASTYVOX_DB : ActualiserDB() insertion réussit ");

    if(script_requete->exec("INSERT INTO Studios VALUES('S2','L',30000);"))
       qDebug("KASTYVOX_DB : ActualiserDB() insertion réussit ");

    if(script_requete->exec("INSERT INTO Studios VALUES('S3','L',30000);"))
       qDebug("KASTYVOX_DB : ActualiserDB() insertion réussit ");

    if(script_requete->exec("INSERT INTO Studios VALUES('S4','L',30000);"))
       qDebug("KASTYVOX_DB : ActualiserDB() insertion réussit ");

    if(script_requete->exec("INSERT INTO Studios VALUES('S5','L',30000);"))
       qDebug("KASTYVOX_DB : ActualiserDB() insertion réussit ");

    if(script_requete->exec("INSERT INTO Studios VALUES('S6','L',30000);"))
       qDebug("KASTYVOX_DB : ActualiserDB() insertion réussit ");

    if(script_requete->exec("INSERT INTO Studios VALUES('S7','L',30000);"))
       qDebug("KASTYVOX_DB : ActualiserDB() insertion réussit ");

    if(script_requete->exec("INSERT INTO Studios VALUES('S8','L',30000);"))
       qDebug("KASTYVOX_DB : ActualiserDB() insertion réussit ");


    if(script_requete->exec("INSERT INTO Appartements VALUES('A1','L',50000);"))
       qDebug("KASTYVOX_DB : ActualiserDB() insertion réussit ");

    if(script_requete->exec("INSERT INTO Appartements VALUES('A2','L',50000);"))
       qDebug("KASTYVOX_DB : ActualiserDB() insertion réussit ");

    if(script_requete->exec("INSERT INTO Appartements VALUES('A3','L',50000);"))
       qDebug("KASTYVOX_DB : ActualiserDB() insertion réussit ");

    if(script_requete->exec("INSERT INTO Appartements VALUES('A4','L',50000);"))
       qDebug("KASTYVOX_DB : ActualiserDB() insertion réussit ");

    //Actualisation
    updateDB();

}

//Initialisation des vues (ou actualisation)

void Script::liste_affiche_A1(QStringList& liste_A1){

  qDebug("liste_affiche_A1()");
  liste_A1.clear (); //On s'assure qu'il est vide

  liste_A1 << "Numéro :   APT 01 ";

  //Etat
  QString etat; //On vérifie l'état de l'appart L ou O ?
  QSqlTableModel table_appart(nullptr,kastyvox_db);
  table_appart.setTable ("Appartements"); //On récupère la table apparts
  table_appart.select (); //On sélectionne la table
  //On récupère l'état de l'Appart A1 : indice 0
  etat = table_appart.record (0).value ("etat").toString ();

  if(etat[0] == 'L' )
  {
      qDebug("A1 libre");

      liste_A1 << "Etat : Libre ";

      //On vérifie s'il a déjà été occupé
      //Si oui on récupère le nom et la date de libération du dernier Occ
      if(!script_requete->exec ("SELECT date_sortie, nom , prenom FROM OccupeAp, Occupants, Personnes WHERE numeroAO = 'A1' AND idPO=idP AND idAO=Occupants.rowid "))
      {
          qDebug("Requête incorrecte : liste_affiche_A1()");
      }
      else {
          qDebug("Requête correcte");
          if(script_requete->last ())
          {
              liste_A1 << "Date de libération : " +script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
              liste_A1 << "Ancien occupant : " + script_requete->value (1).toString () + "  " + script_requete->value (2).toString ();

          }else {

              liste_A1 << "Jamais occupé !";
          }

      }

  }
  else if (etat[0] == 'O') {
      qDebug("A1 occupé");

      //On récupère date_entree , nom , prenom ,

      if(script_requete->exec ("SELECT date_entree , nom , prenom , date_fin_sejour, date_butoire FROM Occupants, Personnes, OccupeAp WHERE numeroAO='A1' AND idPO=idP AND idAO=Occupants.rowid "))
      {
         qDebug("Requête correcte");
      }

      if(script_requete->last ())
          qDebug("Last correcte");

      liste_A1 << "Etat : Occupé ";
      liste_A1 << "Nom : " + script_requete->value (1).toString ();
      liste_A1 << "Prenom : "+ script_requete->value (2).toString ();
      liste_A1 << "Date d'entrée : " + script_requete->value (0).toDate().toString (Qt::SystemLocaleLongDate);
      liste_A1 << "Date butoire de payement loyer : " + script_requete->value(4).toString();
      liste_A1 << "Date de fin de séjour : " + script_requete->value (3).toDate().toString (Qt::SystemLocaleLongDate);

  }

     qDebug("Fin liste_affiche_A1");
}

void Script::liste_affiche_A2(QStringList& liste_A2){
    qDebug("liste_affiche_A2()");
    liste_A2.clear (); //On s'assure qu'il est vide
    liste_A2 << "Numéro :   APT 02";

    //Etat
    QString etat; //On vérifie l'état de l'appart L ou O ?
    QSqlTableModel table_appart(nullptr,kastyvox_db);
    table_appart.setTable ("Appartements"); //On récupère la table apparts
    table_appart.select (); //On sélectionne la table
    //On récupère l'état de l'Appart A2 : indice 1
    etat = table_appart.record (1).value ("etat").toString ();

    if(etat[0] == 'L' )
    {
        qDebug("A2 libre");

        liste_A2 << "Etat : Libre ";

        //On vérifie s'il a déjà été occupé
        //Si oui on récupère le nom et la date de libération du dernier Occ

        if(!script_requete->exec ("SELECT date_sortie, nom , prenom FROM OccupeAp, Occupants, Personnes WHERE numeroAO = 'A2' AND idPO=idP AND idAO=Occupants.rowid "))
        {
            qDebug("Requête incorrecte");
        }
        else {
            qDebug("Requête correcte");
            if(script_requete->last ())
            {
                liste_A2 << "Date de libération : " +script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
                liste_A2 << "Ancien occupant : " + script_requete->value (1).toString () + "  " + script_requete->value (2).toString ();

            }else {

                liste_A2 << "Jamais occupé !";
            }

        }

    }
    else if (etat[0] == 'O') {
        qDebug("A2 occupé");

        //On récupère date_entree , nom , prenom ,

        if(script_requete->exec ("SELECT date_entree , nom , prenom , date_fin_sejour, date_butoire FROM Occupants, Personnes, OccupeAp WHERE numeroAO='A2' AND idPO=idP AND idAO=Occupants.rowid "))
        {
           qDebug("Requête correcte");
        }

        if(script_requete->last ())
            qDebug("Last correcte");

        liste_A2 << "Etat : Occupé ";
        liste_A2 << "Nom : " + script_requete->value (1).toString ();
        liste_A2 << "Prenom : "+ script_requete->value (2).toString ();
        liste_A2 << "Date d'entrée : " + script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
        liste_A2 << "Date butoire de payement loyer : " + script_requete->value(4).toString();
        liste_A2 << "Date de fin de séjour : " + script_requete->value (3).toDate ().toString (Qt::SystemLocaleLongDate);

    }

       qDebug("Fin liste_affiche_A2");

}

void Script::liste_affiche_A3(QStringList& liste_A3){
    qDebug("liste_affiche_A3()");
    liste_A3.clear (); //On s'assure qu'il est vide
    liste_A3 << "Numéro :   APT 101";

    //Etat
    QString etat; //On vérifie l'état de l'appart L ou O ?
    QSqlTableModel table_appart(nullptr,kastyvox_db);
    table_appart.setTable ("Appartements"); //On récupère la table apparts
    table_appart.select (); //On sélectionne la table
    //On récupère l'état de l'Appart A3 : indice 2
    etat = table_appart.record (2).value ("etat").toString ();

    if(etat[0] == 'L' )
    {
        qDebug("A2 libre");

        liste_A3 << "Etat : Libre ";

        //On vérifie s'il a déjà été occupé
        //Si oui on récupère le nom et la date de libération du dernier Occ

        if(!script_requete->exec ("SELECT date_sortie, nom , prenom FROM OccupeAp, Occupants, Personnes WHERE numeroAO = 'A3' AND idPO=idP AND idAO=Occupants.rowid "))
        {
            qDebug("Requête incorrecte");
        }
        else {
            qDebug("Requête correcte");
            if(script_requete->last ())
            {
                liste_A3 << "Date de libération : " +script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
                liste_A3 << "Ancien occupant : " + script_requete->value (1).toString () + "  " + script_requete->value (2).toString ();

            }else {

                liste_A3 << "Jamais occupé !";
            }

        }

    }
    else if (etat[0] == 'O') {
        qDebug("A3 occupé");

        //On récupère date_entree , nom , prenom ,

        if(script_requete->exec ("SELECT date_entree , nom , prenom , date_fin_sejour, date_butoire FROM Occupants, Personnes, OccupeAp WHERE numeroAO='A3' AND idPO=idP AND idAO=Occupants.rowid "))
        {
           qDebug("Requête correcte");
        }

        if(script_requete->last ())
            qDebug("Last correcte");

        liste_A3 << "Etat : Occupé ";
        liste_A3 << "Nom : " + script_requete->value (1).toString ();
        liste_A3 << "Prenom : "+ script_requete->value (2).toString ();
        liste_A3 << "Date d'entrée : " + script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
        liste_A3 << "Date butoire de payement loyer : " + script_requete->value(4).toString();
        liste_A3 << "Date de fin de séjour : " + script_requete->value (3).toDate ().toString (Qt::SystemLocaleLongDate);

    }

       qDebug("Fin liste_affiche_A3");

}

void Script::liste_affiche_A4(QStringList& liste_A4){
    qDebug("liste_affiche_A4()");
    liste_A4.clear (); //On s'assure qu'il est vide
    liste_A4 << "Numéro :   APT 102";

    //Etat
    QString etat; //On vérifie l'état de l'appart L ou O ?
    QSqlTableModel table_appart(nullptr,kastyvox_db);
    table_appart.setTable ("Appartements"); //On récupère la table apparts
    table_appart.select (); //On sélectionne la table

    //On récupère l'état de l'Appart A4 : indice 3
    etat = table_appart.record (3).value ("etat").toString ();

    if(etat[0] == 'L' )
    {
        qDebug("A4 libre");

        liste_A4 << "Etat : Libre ";

        //On vérifie s'il a déjà été occupé
        //Si oui on récupère le nom et la date de libération du dernier Occ

        if(!script_requete->exec ("SELECT date_sortie, nom , prenom FROM OccupeAp, Occupants, Personnes WHERE numeroAO = 'A4' AND idPO=idP AND idAO=Occupants.rowid "))
        {
            qDebug("Requête incorrecte");
        }
        else {
            qDebug("Requête correcte");
            if(script_requete->last ())
            {
                liste_A4 << "Date de libération : " +script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
                liste_A4 << "Ancien occupant : " + script_requete->value (1).toString () + "  " + script_requete->value (2).toString ();

            }else {

                liste_A4 << "Jamais occupé !";
            }

        }

    }
    else if (etat[0] == 'O') {
        qDebug("A4 occupé");

        //On récupère date_entree , nom , prenom ,

        if(script_requete->exec ("SELECT date_entree , nom , prenom , date_fin_sejour, date_butoire FROM Occupants, Personnes, OccupeAp WHERE numeroAO='A4' AND idPO=idP AND idAO=Occupants.rowid "))
        {
           qDebug("Requête correcte");
        }

        if(script_requete->last ())
            qDebug("Last correcte");

        liste_A4 << "Etat : Occupé ";
        liste_A4 << "Nom : " + script_requete->value (1).toString ();
        liste_A4 << "Prenom : "+ script_requete->value (2).toString ();
        liste_A4 << "Date d'entrée : " + script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
        liste_A4 << "Date butoire de payement loyer : " + script_requete->value(4).toString();
        liste_A4 << "Date de fin de séjour : " + script_requete->value (3).toDate ().toString (Qt::SystemLocaleLongDate);

    }

       qDebug("Fin liste_affiche_A4");

}

//Pour les studios
void Script::liste_affiche_S1(QStringList& liste){
    qDebug("liste_affiche_S1()");
    liste.clear ();
    liste << "Numéro :   ST 01";

    //Etat
    QString etat;
    QSqlTableModel table_appart(nullptr,kastyvox_db);
    table_appart.setTable ("Studios"); //On récupère la table Studios
    table_appart.select (); //On sélectionne la table
    //On récupère l'état du Studio S1 : indice 0
    etat = table_appart.record (0).value ("etat").toString ();

    if(etat[0] == 'L' )
    {
        qDebug("S1 libre");

        liste << "Etat : Libre ";

        //On vérifie s'il a déjà été occupé
        //Si oui on récupère le nom et la date de libération du dernier Occ

        if(!script_requete->exec ("SELECT date_sortie, nom , prenom FROM OccupeSt, Occupants, Personnes WHERE numeroStO = 'S1' AND idPO=idP AND idStO=Occupants.rowid "))
        {
            qDebug("Requête incorrecte");
        }
        else {
            qDebug("Requête correcte");
            if(script_requete->last ())
            {
                liste << "Date de libération : " +script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
                liste << "Ancien occupant : " + script_requete->value (1).toString () + "  " + script_requete->value (2).toString ();

            }else {

                liste << "Jamais occupé !";
            }

        }

    }
    else if (etat[0] == 'O') {
        qDebug("S1 occupé");

        //On récupère date_entree , nom , prenom ,

        if(script_requete->exec ("SELECT date_entree , nom , prenom , date_fin_sejour, date_butoire FROM Occupants, Personnes, OccupeSt WHERE numeroStO='S1' AND idPO=idP AND idStO=Occupants.rowid "))
        {
           qDebug("Requête correcte");
        }

        if(script_requete->last ())
            qDebug("Last correcte");

        liste << "Etat : Occupé ";
        liste << "Nom : " + script_requete->value (1).toString ();
        liste << "Prenom : "+ script_requete->value (2).toString ();
        liste << "Date d'entrée : " + script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
        liste << "Date butoire de payement loyer : " + script_requete->value(4).toString();
        liste << "Date de fin de séjour : " + script_requete->value (3).toDate ().toString (Qt::SystemLocaleLongDate);

    }

       qDebug("Fin liste_affiche_S1");
}

void Script::liste_affiche_S2(QStringList& liste){
    qDebug("liste_affiche_S2()");
    liste.clear ();
    liste << "Numéro :   ST 02";

    //Etat
    QString etat; //On vérifie l'état de l'appart L ou O ?
    QSqlTableModel table_appart(nullptr,kastyvox_db);
    table_appart.setTable ("Studios"); //On récupère la table apparts
    table_appart.select (); //On sélectionne la table
    //On récupère l'état du Studio S2 : indice 1
    etat = table_appart.record (1).value ("etat").toString ();

    if(etat[0] == 'L' )
    {
        qDebug("S1 libre");

        liste << "Etat : Libre ";

        //On vérifie s'il a déjà été occupé
        //Si oui on récupère le nom et la date de libération du dernier Occ

        if(!script_requete->exec ("SELECT date_sortie, nom , prenom FROM OccupeSt, Occupants, Personnes WHERE numeroStO = 'S2' AND idPO=idP AND idStO=Occupants.rowid "))
        {
            qDebug("Requête incorrecte");
        }
        else {
            qDebug("Requête correcte");
            if(script_requete->last ())
            {
                liste << "Date de libération : " +script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
                liste << "Ancien occupant : " + script_requete->value (1).toString () + "  " + script_requete->value (2).toString ();

            }else {

                liste << "Jamais occupé !";
            }

        }

    }
    else if (etat[0] == 'O') {
        qDebug("S2 occupé");

        //On récupère date_entree , nom , prenom ,

        if(script_requete->exec ("SELECT date_entree , nom , prenom , date_fin_sejour, date_butoire FROM Occupants, Personnes, OccupeSt WHERE numeroStO='S2' AND idPO=idP AND idStO=Occupants.rowid "))
        {
           qDebug("Requête correcte");
        }

        if(script_requete->last ())
            qDebug("Last correcte");

        liste << "Etat : Occupé ";
        liste << "Nom : " + script_requete->value (1).toString ();
        liste << "Prenom : "+ script_requete->value (2).toString ();
        liste << "Date d'entrée : " + script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
        liste << "Date butoire de payement loyer : " + script_requete->value(4).toString();
        liste << "Date de fin de séjour : " + script_requete->value (3).toDate ().toString (Qt::SystemLocaleLongDate);

    }

       qDebug("Fin liste_affiche_S2");

}

void Script::liste_affiche_S3(QStringList& liste){
    qDebug("liste_affiche_S3()");
    liste.clear ();
    liste << "Numéro :   ST 03";

    //Etat
    QString etat;
    QSqlTableModel table_appart(nullptr,kastyvox_db);
    table_appart.setTable ("Studios"); //On récupère la table Studios
    table_appart.select (); //On sélectionne la table
    //On récupère l'état du Studio S3 : indice 2
    etat = table_appart.record (2).value ("etat").toString ();

    if(etat[0] == 'L' )
    {
        qDebug("S3 libre");

        liste << "Etat : Libre ";

        //On vérifie s'il a déjà été occupé
        //Si oui on récupère le nom et la date de libération du dernier Occ

        if(!script_requete->exec ("SELECT date_sortie, nom , prenom FROM OccupeSt, Occupants, Personnes WHERE numeroStO = 'S3' AND idPO=idP AND idStO=Occupants.rowid "))
        {
            qDebug("Requête incorrecte");
        }
        else {
            qDebug("Requête correcte");
            if(script_requete->last ())
            {
                liste << "Date de libération : " +script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
                liste << "Ancien occupant : " + script_requete->value (1).toString () + "  " + script_requete->value (2).toString ();

            }else {

                liste << "Jamais occupé !";
            }

        }

    }
    else if (etat[0] == 'O') {
        qDebug("S3 occupé");

        //On récupère date_entree , nom , prenom ,

        if(script_requete->exec ("SELECT date_entree , nom , prenom , date_fin_sejour, date_butoire FROM Occupants, Personnes, OccupeSt WHERE numeroStO='S3' AND idPO=idP AND idStO=Occupants.rowid "))
        {
           qDebug("Requête correcte");
        }

        if(script_requete->last ())
            qDebug("Last correcte");

        liste << "Etat : Occupé ";
        liste << "Nom : " + script_requete->value (1).toString ();
        liste << "Prenom : "+ script_requete->value (2).toString ();
        liste << "Date d'entrée : " + script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
        liste << "Date butoire de payement loyer : " + script_requete->value(4).toString();
        liste << "Date de fin de séjour : " + script_requete->value (3).toDate ().toString (Qt::SystemLocaleLongDate);

    }

       qDebug("Fin liste_affiche_S3");
}

void Script::liste_affiche_S4(QStringList& liste){
    qDebug("liste_affiche_S4()");
    liste.clear ();liste.clear ();
    liste << "Numéro :   ST 04";

    //Etat
    QString etat; //On vérifie l'état de l'appart L ou O ?
    QSqlTableModel table_appart(nullptr,kastyvox_db);
    table_appart.setTable ("Studios"); //On récupère la table Studios
    table_appart.select (); //On sélectionne la table
    //On récupère l'état du Studio S4 : indice 3
    etat = table_appart.record (3).value ("etat").toString ();

    if(etat[0] == 'L' )
    {
        qDebug("S4 libre");

        liste << "Etat : Libre ";

        //On vérifie s'il a déjà été occupé
        //Si oui on récupère le nom et la date de libération du dernier Occ

        if(!script_requete->exec ("SELECT date_sortie, nom , prenom FROM OccupeSt, Occupants, Personnes WHERE numeroStO = 'S4' AND idPO=idP AND idStO=Occupants.rowid "))
        {
            qDebug("Requête incorrecte");
        }
        else {
            qDebug("Requête correcte");
            if(script_requete->last ())
            {
                liste << "Date de libération : " +script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
                liste << "Ancien occupant : " + script_requete->value (1).toString () + "  " + script_requete->value (2).toString ();

            }else {

                liste << "Jamais occupé !";
            }

        }

    }
    else if (etat[0] == 'O') {
        qDebug("S4 occupé");

        //On récupère date_entree , nom , prenom ,

        if(script_requete->exec ("SELECT date_entree , nom , prenom , date_fin_sejour, date_butoire FROM Occupants, Personnes, OccupeSt WHERE numeroStO='S4' AND idPO=idP AND idStO=Occupants.rowid "))
        {
           qDebug("Requête correcte");
        }

        if(script_requete->last ())
            qDebug("Last correcte");

        liste << "Etat : Occupé ";
        liste << "Nom : " + script_requete->value (1).toString ();
        liste << "Prenom : "+ script_requete->value (2).toString ();
        liste << "Date d'entrée : " + script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
        liste << "Date butoire de payement loyer : " + script_requete->value(4).toString();
        liste << "Date de fin de séjour : " + script_requete->value (3).toDate ().toString (Qt::SystemLocaleLongDate);

    }

       qDebug("Fin liste_affiche_S4");
}

void Script::liste_affiche_S5(QStringList& liste){
    qDebug("liste_affiche_S5()");
    liste.clear ();
    liste << "Numéro :   ST 101";

    //Etat
    QString etat; //On vérifie l'état de l'appart L ou O ?
    QSqlTableModel table_appart(nullptr,kastyvox_db);
    table_appart.setTable ("Studios"); //On récupère la table Studios
    table_appart.select (); //On sélectionne la table
    //On récupère l'état du Studio S5 : indice 4
    etat = table_appart.record (4).value ("etat").toString ();

    if(etat[0] == 'L' )
    {
        qDebug("S5 libre");

        liste << "Etat : Libre ";

        //On vérifie s'il a déjà été occupé
        //Si oui on récupère le nom et la date de libération du dernier Occ

        if(!script_requete->exec ("SELECT date_sortie, nom , prenom FROM OccupeSt, Occupants, Personnes WHERE numeroStO = 'S5' AND idPO=idP AND idStO=Occupants.rowid "))
        {
            qDebug("Requête incorrecte");
        }
        else {
            qDebug("Requête correcte");
            if(script_requete->last ())
            {
                liste << "Date de libération : " +script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
                liste << "Ancien occupant : " + script_requete->value (1).toString () + "  " + script_requete->value (2).toString ();

            }else {

                liste << "Jamais occupé !";
            }

        }

    }
    else if (etat[0] == 'O') {
        qDebug("S5 occupé");

        //On récupère date_entree , nom , prenom ,

        if(script_requete->exec ("SELECT date_entree , nom , prenom , date_fin_sejour , date_butoire FROM Occupants, Personnes, OccupeSt WHERE numeroStO='S5' AND idPO=idP AND idStO=Occupants.rowid "))
        {
           qDebug("Requête correcte");
        }

        if(script_requete->last ())
            qDebug("Last correcte");

        liste << "Etat : Occupé ";
        liste << "Nom : " + script_requete->value (1).toString ();
        liste << "Prenom : "+ script_requete->value (2).toString ();
        liste << "Date d'entrée : " + script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
        liste << "Date butoire de payement loyer : " + script_requete->value(4).toString();
        liste << "Date de fin de séjour : " + script_requete->value (3).toDate ().toString (Qt::SystemLocaleLongDate);

    }

       qDebug("Fin liste_affiche_S5");
}

void Script::liste_affiche_S6(QStringList& liste){
    qDebug("liste_affiche_S6()");
    liste.clear ();
    liste << "Numéro :   ST 102";

    //Etat
    QString etat;
    QSqlTableModel table_appart(nullptr,kastyvox_db);
    table_appart.setTable ("Studios"); //On récupère la table Studios
    table_appart.select (); //On sélectionne la table
    //On récupère l'état du Studio S6 : indice 5
    etat = table_appart.record (5).value ("etat").toString ();

    if(etat[0] == 'L' )
    {
        qDebug("S6 libre");

        liste << "Etat : Libre ";

        //On vérifie s'il a déjà été occupé
        //Si oui on récupère le nom et la date de libération du dernier Occ

        if(!script_requete->exec ("SELECT date_sortie, nom , prenom FROM OccupeSt, Occupants, Personnes WHERE numeroStO = 'S6' AND idPO=idP AND idStO=Occupants.rowid "))
        {
            qDebug("Requête incorrecte");
        }
        else {
            qDebug("Requête correcte");
            if(script_requete->last ())
            {
                liste << "Date de libération : " +script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
                liste << "Ancien occupant : " + script_requete->value (1).toString () + "  " + script_requete->value (2).toString ();

            }else {

                liste << "Jamais occupé !";
            }

        }

    }
    else if (etat[0] == 'O') {
        qDebug("S6 occupé");

        //On récupère date_entree , nom , prenom ,

        if(script_requete->exec ("SELECT date_entree , nom , prenom , date_fin_sejour, date_butoire FROM Occupants, Personnes, OccupeSt WHERE numeroStO='S6' AND idPO=idP AND idStO=Occupants.rowid "))
        {
           qDebug("Requête correcte");
        }

        if(script_requete->last ())
            qDebug("Last correcte");

        liste << "Etat : Occupé ";
        liste << "Nom : " + script_requete->value (1).toString ();
        liste << "Prenom : "+ script_requete->value (2).toString ();
        liste << "Date d'entrée : " + script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
        liste << "Date butoire de payement loyer : " + script_requete->value(4).toString();
        liste << "Date de fin de séjour : " + script_requete->value (3).toDate ().toString (Qt::SystemLocaleLongDate);

    }

       qDebug("Fin liste_affiche_S6");
}

void Script::liste_affiche_S7(QStringList& liste){
    qDebug("liste_affiche_S7()");
    liste.clear ();
    liste << "Numéro :   ST 103";

    //Etat
    QString etat; //On vérifie l'état de l'appart L ou O ?
    QSqlTableModel table_appart(nullptr,kastyvox_db);
    table_appart.setTable ("Studios"); //On récupère la table apparts
    table_appart.select (); //On sélectionne la table
    //On récupère l'état du Studio S7 : indice 6
    etat = table_appart.record (6).value ("etat").toString ();

    if(etat[0] == 'L' )
    {
        qDebug("S7 libre");

        liste << "Etat : Libre ";

        //On vérifie s'il a déjà été occupé
        //Si oui on récupère le nom et la date de libération du dernier Occ

        if(!script_requete->exec ("SELECT date_sortie, nom , prenom FROM OccupeSt, Occupants, Personnes WHERE numeroStO = 'S7' AND idPO=idP AND idStO=Occupants.rowid "))
        {
            qDebug("Requête incorrecte");
        }
        else {
            qDebug("Requête correcte");
            if(script_requete->last ())
            {
                liste << "Date de libération : " +script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
                liste << "Ancien occupant : " + script_requete->value (1).toString () + "  " + script_requete->value (2).toString ();

            }else {

                liste << "Jamais occupé !";
            }

        }

    }
    else if (etat[0] == 'O') {
        qDebug("S7 occupé");

        //On récupère date_entree , nom , prenom ,

        if(script_requete->exec ("SELECT date_entree , nom , prenom , date_fin_sejour, date_butoire FROM Occupants, Personnes, OccupeSt WHERE numeroStO='S7' AND idPO=idP AND idStO=Occupants.rowid "))
        {
           qDebug("Requête correcte");
        }

        if(script_requete->last ())
            qDebug("Last correcte");

        liste << "Etat : Occupé ";
        liste << "Nom : " + script_requete->value (1).toString ();
        liste << "Prenom : "+ script_requete->value (2).toString ();
        liste << "Date d'entrée : " + script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
        liste << "Date butoire de payement loyer : " + script_requete->value(4).toString();
        liste << "Date de fin de séjour : " + script_requete->value (3).toDate ().toString (Qt::SystemLocaleLongDate);

    }

       qDebug("Fin liste_affiche_S7");
}

void Script::liste_affiche_S8(QStringList& liste){
    qDebug("liste_affiche_S8()");
    liste.clear ();
    liste << "Numéro :   ST 104";

    //Etat
    QString etat;
    QSqlTableModel table_appart(nullptr,kastyvox_db);
    table_appart.setTable ("Studios"); //On récupère la table Studios
    table_appart.select (); //On sélectionne la table
    //On récupère l'état du Studio S8 : indice 7
    etat = table_appart.record (7).value ("etat").toString ();

    if(etat[0] == 'L' )
    {
        qDebug("S8 libre");

        liste << "Etat : Libre ";

        //On vérifie s'il a déjà été occupé
        //Si oui on récupère le nom et la date de libération du dernier Occ

        if(!script_requete->exec ("SELECT date_sortie, nom , prenom FROM OccupeSt, Occupants, Personnes WHERE numeroStO = 'S8' AND idPO=idP AND idStO=Occupants.rowid "))
        {
            qDebug("Requête incorrecte");
        }
        else {
            qDebug("Requête correcte");
            if(script_requete->last ())
            {
                liste << "Date de libération : " +script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
                liste << "Ancien occupant : " + script_requete->value (1).toString () + "  " + script_requete->value (2).toString ();

            }else {

                liste << "Jamais occupé !";
            }

        }

    }
    else if (etat[0] == 'O') {
        qDebug("S8 occupé");

        //On récupère date_entree , nom , prenom ,

        if(script_requete->exec ("SELECT date_entree , nom , prenom , date_fin_sejour, date_butoire FROM Occupants, Personnes, OccupeSt WHERE numeroStO='S8' AND idPO=idP AND idStO=Occupants.rowid "))
        {
           qDebug("Requête correcte");
        }

        if(script_requete->last ())
            qDebug("Last correcte");

        liste << "Etat : Occupé ";
        liste << "Nom : " + script_requete->value (1).toString ();
        liste << "Prenom : "+ script_requete->value (2).toString ();
        liste << "Date d'entrée : " + script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
        liste << "Date butoire de payement loyer : " + script_requete->value(4).toString();
        liste << "Date de fin de séjour : " + script_requete->value (3).toDate ().toString (Qt::SystemLocaleLongDate);

    }

       qDebug("Fin liste_affiche_S8");
}


//Pour les chambres
void Script::liste_affiche_CH1(QStringList& liste){
    qDebug("liste_affiche_CH1()");
    liste.clear ();
    liste << "Numéro :   CH 101";

    //Etat
    QString etat;
    QSqlTableModel table_appart(nullptr,kastyvox_db);
    table_appart.setTable ("Chambres"); //On récupère la table Chambres
    table_appart.select (); //On sélectionne la table
    //On récupère l'état de la Chambre CH1 : indice 0
    etat = table_appart.record (0).value ("etat").toString ();

    if(etat[0] == 'L' )
    {
        qDebug("CH1 libre");

        liste << "Etat : Libre ";

        //On vérifie s'il a déjà été occupé
        //Si oui on récupère le nom et la date de libération du dernier Occ

        if(!script_requete->exec ("SELECT date_sortie, nom , prenom FROM OccupeCh, Occupants, Personnes WHERE numeroChO = 'CH1' AND idPO=idP AND idChO=Occupants.rowid "))
        {
            qDebug("Requête incorrecte");
        }
        else {
            qDebug("Requête correcte");
            if(script_requete->last ())
            {
                liste << "Date de libération : " +script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
                liste << "Ancien occupant : " + script_requete->value (1).toString () + "  " + script_requete->value (2).toString ();

            }else {

                liste << "Jamais occupé !";
            }

        }

    }
    else if (etat[0] == 'O') {
        qDebug("CH1 occupé");

        //On récupère date_entree , nom , prenom ,

        if(script_requete->exec ("SELECT date_entree , nom , prenom , date_fin_sejour, date_butoire FROM Occupants, Personnes, OccupeCh WHERE numeroChO='CH1' AND idPO=idP AND idChO=Occupants.rowid "))
        {
           qDebug("Requête correcte");
        }

        if(script_requete->last ())
            qDebug("Last correcte");

        liste << "Etat : Occupé ";
        liste << "Nom : " + script_requete->value (1).toString ();
        liste << "Prenom : "+ script_requete->value (2).toString ();
        liste << "Date d'entrée : " + script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
        liste << "Date butoire de payement loyer : " + script_requete->value(4).toString();
        liste << "Date de fin de séjour : " + script_requete->value (3).toDate ().toString (Qt::SystemLocaleLongDate);

    }

       qDebug("Fin liste_affiche_CH1");
}


void Script::liste_affiche_CH2(QStringList& liste){
    qDebug("liste_affiche_CH2()");
    liste.clear ();
    liste << "Numéro :   CH 102";


    //Etat
    QString etat;
    QSqlTableModel table_appart(nullptr,kastyvox_db);
    table_appart.setTable ("Chambres"); //On récupère la table Chambres
    table_appart.select (); //On sélectionne la table
    //On récupère l'état de la Chambre CH2 : indice 1
    etat = table_appart.record (1).value ("etat").toString ();

    if(etat[0] == 'L' )
    {
        qDebug("CH2 libre");

        liste << "Etat : Libre ";

        //On vérifie s'il a déjà été occupé
        //Si oui on récupère le nom et la date de libération du dernier Occ

        if(!script_requete->exec ("SELECT date_sortie, nom , prenom FROM OccupeCh, Occupants, Personnes WHERE numeroChO = 'CH2' AND idPO=idP AND idChO=Occupants.rowid "))
        {
            qDebug("Requête incorrecte");
        }
        else {
            qDebug("Requête correcte");
            if(script_requete->last ())
            {
                liste << "Date de libération : " +script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
                liste << "Ancien occupant : " + script_requete->value (1).toString () + "  " + script_requete->value (2).toString ();

            }else {

                liste << "Jamais occupé !";
            }

        }

    }
    else if (etat[0] == 'O') {
        qDebug("CH2 occupé");

        //On récupère date_entree , nom , prenom ,

        if(script_requete->exec ("SELECT date_entree , nom , prenom , date_fin_sejour, date_butoire FROM Occupants, Personnes, OccupeCh WHERE numeroChO='CH2' AND idPO=idP AND idChO=Occupants.rowid "))
        {
           qDebug("Requête correcte");
        }

        if(script_requete->last ())
            qDebug("Last correcte");

        liste << "Etat : Occupé ";
        liste << "Nom : " + script_requete->value (1).toString ();
        liste << "Prenom : "+ script_requete->value (2).toString ();
        liste << "Date d'entrée : " + script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
        liste << "Date butoire de payement loyer : " + script_requete->value(4).toString();
        liste << "Date de fin de séjour : " + script_requete->value (3).toDate ().toString (Qt::SystemLocaleLongDate);

    }

       qDebug("Fin liste_affiche_CH2");
}


void Script::liste_affiche_CH3(QStringList& liste){
    qDebug("liste_affiche_CH3()");
    liste.clear ();
    liste << "Numéro :   CH 103";


    //Etat
    QString etat;
    QSqlTableModel table_appart(nullptr,kastyvox_db);
    table_appart.setTable ("Chambres"); //On récupère la table Chambres
    table_appart.select (); //On sélectionne la table
    //On récupère l'état de la Chambre CH3 : indice 2
    etat = table_appart.record (2).value ("etat").toString ();

    if(etat[0] == 'L' )
    {
        qDebug("CH1 libre");

        liste << "Etat : Libre ";

        //On vérifie s'il a déjà été occupé
        //Si oui on récupère le nom et la date de libération du dernier Occ

        if(!script_requete->exec ("SELECT date_sortie, nom , prenom FROM OccupeCh, Occupants, Personnes WHERE numeroChO = 'CH3' AND idPO=idP AND idChO=Occupants.rowid "))
        {
            qDebug("Requête incorrecte");
        }
        else {
            qDebug("Requête correcte");
            if(script_requete->last ())
            {
                liste << "Date de libération : " +script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
                liste << "Ancien occupant : " + script_requete->value (1).toString () + "  " + script_requete->value (2).toString ();

            }else {

                liste << "Jamais occupé !";
            }

        }

    }
    else if (etat[0] == 'O') {
        qDebug("CH3 occupé");

        //On récupère date_entree , nom , prenom ,

        if(script_requete->exec ("SELECT date_entree , nom , prenom , date_fin_sejour, date_butoire FROM Occupants, Personnes, OccupeCh WHERE numeroChO='CH3' AND idPO=idP AND idChO=Occupants.rowid "))
        {
           qDebug("Requête correcte");
        }

        if(script_requete->last ())
            qDebug("Last correcte");

        liste << "Etat : Occupé ";
        liste << "Nom : " + script_requete->value (1).toString ();
        liste << "Prenom : "+ script_requete->value (2).toString ();
        liste << "Date d'entrée : " + script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
        liste << "Date butoire de payement loyer : " + script_requete->value(4).toString();
        liste << "Date de fin de séjour : " + script_requete->value (3).toDate ().toString (Qt::SystemLocaleLongDate);

    }

       qDebug("Fin liste_affiche_CH3");
}


void Script::liste_affiche_CH4(QStringList& liste){
    qDebug("liste_affiche_CH4()");
    liste.clear ();
    liste << "Numéro :   CH 104";

    //Etat
    QString etat;
    QSqlTableModel table_appart(nullptr,kastyvox_db);
    table_appart.setTable ("Chambres"); //On récupère la table Chambres
    table_appart.select (); //On sélectionne la table
    //On récupère l'état de la Chambre CH4 : indice 3
    etat = table_appart.record (3).value ("etat").toString ();

    if(etat[0] == 'L' )
    {
        qDebug("CH4 libre");

        liste << "Etat : Libre ";

        //On vérifie s'il a déjà été occupé
        //Si oui on récupère le nom et la date de libération du dernier Occ

        if(!script_requete->exec ("SELECT date_sortie, nom , prenom FROM OccupeCh, Occupants, Personnes WHERE numeroChO = 'CH4' AND idPO=idP AND idChO=Occupants.rowid "))
        {
            qDebug("Requête incorrecte");
        }
        else {
            qDebug("Requête correcte");
            if(script_requete->last ())
            {
                liste << "Date de libération : " +script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
                liste << "Ancien occupant : " + script_requete->value (1).toString () + "  " + script_requete->value (2).toString ();

            }else {

                liste << "Jamais occupé !";
            }

        }

    }
    else if (etat[0] == 'O') {
        qDebug("CH4 occupé");

        //On récupère date_entree , nom , prenom ,

        if(script_requete->exec ("SELECT date_entree , nom , prenom , date_fin_sejour, date_butoire FROM Occupants, Personnes, OccupeCh WHERE numeroChO='CH4' AND idPO=idP AND idChO=Occupants.rowid "))
        {
           qDebug("Requête correcte");
        }

        if(script_requete->last ())
            qDebug("Last correcte");

        liste << "Etat : Occupé ";
        liste << "Nom : " + script_requete->value (1).toString ();
        liste << "Prenom : "+ script_requete->value (2).toString ();
        liste << "Date d'entrée : " + script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
        liste << "Date butoire de payement loyer : " + script_requete->value(4).toString();
        liste << "Date de fin de séjour : " + script_requete->value (3).toDate ().toString (Qt::SystemLocaleLongDate);

    }

       qDebug("Fin liste_affiche_CH4");
}


//Pour les boutiques
void Script::liste_affiche_B1(QStringList& liste){
    qDebug("liste_affiche_B1()");
    liste.clear ();
    liste << "Numéro :   B 01";

    //Etat
    QString etat;
    QSqlTableModel table_appart(nullptr,kastyvox_db);
    table_appart.setTable ("Boutiques"); //On récupère la table Boutiques
    table_appart.select (); //On sélectionne la table
    //On récupère l'état de la Boutique B1 : indice 0
    etat = table_appart.record (0).value ("etat").toString ();

    if(etat[0] == 'L' )
    {
        qDebug("B1 libre");

        liste << "Etat : Libre ";

        //On vérifie s'il a déjà été occupé
        //Si oui on récupère le nom et la date de libération du dernier Occ

        if(!script_requete->exec ("SELECT date_sortie, nom , prenom FROM OccupeBt, Occupants, Personnes WHERE numeroBtO = 'B1' AND idPO=idP AND idBtO=Occupants.rowid "))
        {
            qDebug("Requête incorrecte");
        }
        else {
            qDebug("Requête correcte");
            if(script_requete->last ())
            {
                liste << "Date de libération : " +script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
                liste << "Ancien occupant : " + script_requete->value (1).toString () + "  " + script_requete->value (2).toString ();

            }else {

                liste << "Jamais occupé !";
            }

        }

    }
    else if (etat[0] == 'O') {
        qDebug("B1 occupé");

        //On récupère date_entree , nom , prenom ,

        if(script_requete->exec ("SELECT date_entree , nom , prenom , date_fin_sejour , date_butoire FROM Occupants, Personnes, OccupeBt WHERE numeroBtO='B1' AND idPO=idP AND idBtO=Occupants.rowid "))
        {
           qDebug("Requête correcte");
        }

        if(script_requete->last ())
            qDebug("Last correcte");

        liste << "Etat : Occupé ";
        liste << "Nom : " + script_requete->value (1).toString ();
        liste << "Prenom : "+ script_requete->value (2).toString ();
        liste << "Date d'entrée : " + script_requete->value (0).toDate().toString (Qt::SystemLocaleLongDate);
        liste << "Date butoire de payement loyer : " + script_requete->value(4).toString();
        liste << "Date de fin de séjour : " + script_requete->value (3).toDate ().toString (Qt::SystemLocaleLongDate);

    }

       qDebug("Fin liste_affiche_B1");
}

void Script::liste_affiche_B2(QStringList& liste){
    qDebug("liste_affiche_B2()");
    liste.clear ();
    liste << "Numéro :   B 02";
    //Etat
    QString etat;
    QSqlTableModel table_appart(nullptr,kastyvox_db);
    table_appart.setTable ("Boutiques"); //On récupère la table Boutiques
    table_appart.select (); //On sélectionne la table
    //On récupère l'état de la Boutique B2 : indice 1
    etat = table_appart.record (1).value ("etat").toString ();

    if(etat[0] == 'L' )
    {
        qDebug("B2 libre");

        liste << "Etat : Libre ";

        //On vérifie s'il a déjà été occupé
        //Si oui on récupère le nom et la date de libération du dernier Occ

        if(!script_requete->exec ("SELECT date_sortie, nom , prenom FROM OccupeBt, Occupants, Personnes WHERE numeroBtO = 'B2' AND idPO=idP AND idBtO=Occupants.rowid "))
        {
            qDebug("Requête incorrecte");
        }
        else {
            qDebug("Requête correcte");
            if(script_requete->last ())
            {
                liste << "Date de libération : " +script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
                liste << "Ancien occupant : " + script_requete->value (1).toString () + "  " + script_requete->value (2).toString ();

            }else {

                liste << "Jamais occupé !";
            }

        }

    }
    else if (etat[0] == 'O') {
        qDebug("B2 occupé");

        //On récupère date_entree , nom , prenom ,

        if(script_requete->exec ("SELECT date_entree , nom , prenom , date_fin_sejour , date_butoire FROM Occupants, Personnes, OccupeBt WHERE numeroBtO='B2' AND idPO=idP AND idBtO=Occupants.rowid "))
        {
           qDebug("Requête correcte");
        }

        if(script_requete->last ())
            qDebug("Last correcte");

        liste << "Etat : Occupé ";
        liste << "Nom : " + script_requete->value (1).toString ();
        liste << "Prenom : "+ script_requete->value (2).toString ();
        liste << "Date d'entrée : " + script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
        liste << "Date butoire de payement loyer : " + script_requete->value(4).toString();
        liste << "Date de fin de séjour : " + script_requete->value (3).toDate ().toString (Qt::SystemLocaleLongDate);

    }

       qDebug("Fin liste_affiche_B2");
}

void Script::liste_affiche_B3(QStringList& liste){
    qDebug("liste_affiche_B3()");
    liste.clear ();
    liste << "Numéro :   B 03";
    //Etat
    QString etat;
    QSqlTableModel table_appart(nullptr,kastyvox_db);
    table_appart.setTable ("Boutiques"); //On récupère la table Boutiques
    table_appart.select (); //On sélectionne la table
    //On récupère l'état de la Boutique B3 : indice 2
    etat = table_appart.record (2).value ("etat").toString ();

    if(etat[0] == 'L' )
    {
        qDebug("B3 libre");

        liste << "Etat : Libre ";

        //On vérifie s'il a déjà été occupé
        //Si oui on récupère le nom et la date de libération du dernier Occ

        if(!script_requete->exec ("SELECT date_sortie, nom , prenom FROM OccupeBt, Occupants, Personnes WHERE numeroBtO = 'B3' AND idPO=idP AND idBtO=Occupants.rowid "))
        {
            qDebug("Requête incorrecte");
        }
        else {
            qDebug("Requête correcte");
            if(script_requete->last ())
            {
                liste << "Date de libération : " +script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
                liste << "Ancien occupant : " + script_requete->value (1).toString () + "  " + script_requete->value (2).toString ();

            }else {

                liste << "Jamais occupé !";
            }

        }

    }
    else if (etat[0] == 'O') {
        qDebug("B3 occupé");

        //On récupère date_entree , nom , prenom ,

        if(script_requete->exec ("SELECT date_entree , nom , prenom , date_fin_sejour , date_butoire FROM Occupants, Personnes, OccupeBt WHERE numeroBtO='B3' AND idPO=idP AND idBtO=Occupants.rowid "))
        {
           qDebug("Requête correcte");
        }

        if(script_requete->last ())
            qDebug("Last correcte");

        liste << "Etat : Occupé ";
        liste << "Nom : " + script_requete->value (1).toString ();
        liste << "Prenom : "+ script_requete->value (2).toString ();
        liste << "Date d'entrée : " + script_requete->value (0).toDate ().toString (Qt::SystemLocaleLongDate);
        liste << "Date butoire de payement loyer : " +script_requete->value(4).toString();
        liste << "Date de fin de séjour : " + script_requete->value (3).toDate ().toString (Qt::SystemLocaleLongDate);
    }

       qDebug("Fin liste_affiche_B3");
}


//Ajouter Occupant

//Appartements
void Script::ajoutOccupantAp(QString Ap, QString date, QString cni, QString nom, QString prenom, QString age, QString profession, QString contact, QString pays, QString ville, QString adresse, QString email, QString date_fin_sejour, QString date_butoire, QString cni_le, QString cni_a, QString commentaires){

//Ajout dans la table Personnes

        script_requete->prepare ("INSERT INTO Personnes(cni,nom,prenom,age,profession,contact,pays,ville,adresse,email,cni_le,cni_a,commentaires) VALUES(:cni,:nom,:prenom,:age,:profession,:contact,:pays,:ville,:adresse,:email,:cni_le,:cni_a,:commentaires) ");
        script_requete->bindValue (":cni",cni);
        script_requete->bindValue (":nom",nom);
        script_requete->bindValue (":prenom",prenom);
        script_requete->bindValue (":age",age);
        script_requete->bindValue (":profession",profession);
        script_requete->bindValue (":contact",contact);
        script_requete->bindValue (":pays",pays);
        script_requete->bindValue (":ville",ville);
        script_requete->bindValue (":adresse",adresse);
        script_requete->bindValue (":email",email);
        script_requete->bindValue (":cni_le",cni_le);
        script_requete->bindValue (":cni_a",cni_a);
        script_requete->bindValue (":commentaires",commentaires);

//...
            qDebug("Ajout Personnes Appartements");

            if(script_requete->exec ())
                qDebug("Ajout Personnes réussit");

            //On récupère l'id de la nouvelle Personnes

            int idP = 0;

            while (idP == 0) {
                script_requete->prepare ("SELECT idP FROM Personnes WHERE cni = :cni ");
                script_requete->bindValue (":cni",cni);
                script_requete->exec ();
                script_requete->last ();
                idP = script_requete->value (0).toInt ();
            }

            //On l'ajout à la table Occupants
            script_requete->prepare ("INSERT INTO Occupants(idPO,date_entree,date_fin_sejour,date_butoire) VALUES(:idP,:date,:date_fin_sejour,:date_butoire) ");
            script_requete->bindValue (":idP",idP);
            script_requete->bindValue (":date",date);
            script_requete->bindValue (":date_fin_sejour",date_fin_sejour);
            script_requete->bindValue(":date_butoire",date_butoire);
            script_requete->exec ();

            int rowidOcc {0};

            while (rowidOcc == 0) {

                script_requete->prepare("SELECT rowid FROM Occupants WHERE idPO = :idP;");
                script_requete->bindValue (":idP",idP);
                script_requete->exec ();
                script_requete->last ();
                rowidOcc = script_requete->value (0).toInt ();
                qDebug("rowid du nouvel occupants en cours...");
            }
            qDebug("rowid du nouvel occupants récupérer");

            //On le met dans OccupeAp
            script_requete->prepare ("INSERT INTO OccupeAp(idAO,numeroAO) VALUES (:rowidOcc,:Ap) ");
            script_requete->bindValue (":rowidOcc",rowidOcc);
            script_requete->bindValue (":Ap",Ap);
            script_requete->exec ();

            //On UPDATE l'appart
            script_requete->prepare ("UPDATE Appartements SET etat='O' WHERE numero = :Ap ");
            script_requete->bindValue (":Ap",Ap);
            script_requete->exec ();
}

//...

//Studios
void Script::ajoutOccupantSt(QString St, QString date, QString cni, QString nom, QString prenom, QString age, QString profession, QString contact, QString pays, QString ville, QString adresse, QString email, QString date_fin_sejour, QString date_butoire, QString cni_le, QString cni_a, QString commentaires){

    //Ajout dans la table Personnes

            script_requete->prepare ("INSERT INTO Personnes(cni,nom,prenom,age,profession,contact,pays,ville,adresse,email,cni_le,cni_a,commentaires) VALUES(:cni,:nom,:prenom,:age,:profession,:contact,:pays,:ville,:adresse,:email,:cni_le,:cni_a,:commentaires) ");
            script_requete->bindValue (":cni",cni);
            script_requete->bindValue (":nom",nom);
            script_requete->bindValue (":prenom",prenom);
            script_requete->bindValue (":age",age);
            script_requete->bindValue (":profession",profession);
            script_requete->bindValue (":contact",contact);
            script_requete->bindValue (":pays",pays);
            script_requete->bindValue (":ville",ville);
            script_requete->bindValue (":adresse",adresse);
            script_requete->bindValue (":email",email);
            script_requete->bindValue (":cni_le",cni_le);
            script_requete->bindValue (":cni_a",cni_a);
            script_requete->bindValue (":commentaires",commentaires);


    //...

            qDebug("Ajout Personnes");
            if(script_requete->exec ())
                qDebug("Ajout Personnes réussit");

            //On récupère l'id de la nouvelle Personnes
            int idP = 0;

            while (idP == 0) {
                script_requete->prepare ("SELECT idP FROM Personnes WHERE cni = :cni ");
                script_requete->bindValue (":cni",cni);
                script_requete->exec ();
                script_requete->last ();
                idP = script_requete->value (0).toInt ();
            }
            //On l'ajout à la table Occupants
            script_requete->prepare ("INSERT INTO Occupants(idPO,date_entree,date_fin_sejour,date_butoire) VALUES(:idP,:date,:date_fin_sejour,:date_butoire) ");
            script_requete->bindValue (":idP",idP);
            script_requete->bindValue (":date",date);
            script_requete->bindValue (":date_fin_sejour",date_fin_sejour);
            script_requete->bindValue(":date_butoire",date_butoire);
            script_requete->exec ();


            //Gestion Occupants ajouter
            int rowidOcc {0};

            while (rowidOcc == 0) {

                script_requete->prepare("SELECT rowid FROM Occupants WHERE idPO = :idP;");
                script_requete->bindValue (":idP",idP);
                script_requete->exec ();
                script_requete->last ();
                rowidOcc = script_requete->value (0).toInt ();
                qDebug("rowid du nouvel occupants en cours...");
            }
            qDebug("rowid du nouvel occupants récupérer");

            //On le met dans OccupeSt
            script_requete->prepare ("INSERT INTO OccupeSt(idStO,numeroStO) VALUES (:rowidOcc,:St) ");
            script_requete->bindValue (":rowidOcc",rowidOcc);
            script_requete->bindValue (":St",St);
            script_requete->exec ();

            //On UPDATE le Studio
            script_requete->prepare ("UPDATE Studios SET etat='O' WHERE numero = :St ");
            script_requete->bindValue (":St",St);
            script_requete->exec ();
}

//...

//Chambres
void Script::ajoutOccupantCh(QString Ch, QString date, QString cni, QString nom, QString prenom, QString age, QString profession, QString contact, QString pays, QString ville, QString adresse, QString email, QString date_fin_sejour, QString date_butoire, QString cni_le, QString cni_a, QString commentaires){
    //Ajout dans la table Personnes

    script_requete->prepare ("INSERT INTO Personnes(cni,nom,prenom,age,profession,contact,pays,ville,adresse,email,cni_le,cni_a,commentaires) VALUES(:cni,:nom,:prenom,:age,:profession,:contact,:pays,:ville,:adresse,:email,:cni_le,:cni_a,:commentaires) ");
    script_requete->bindValue (":cni",cni);
    script_requete->bindValue (":nom",nom);
    script_requete->bindValue (":prenom",prenom);
    script_requete->bindValue (":age",age);
    script_requete->bindValue (":profession",profession);
    script_requete->bindValue (":contact",contact);
    script_requete->bindValue (":pays",pays);
    script_requete->bindValue (":ville",ville);
    script_requete->bindValue (":adresse",adresse);
    script_requete->bindValue (":email",email);
    script_requete->bindValue (":cni_le",cni_le);
    script_requete->bindValue (":cni_a",cni_a);
    script_requete->bindValue (":commentaires",commentaires);

    //...


            qDebug("Ajout Personnes");
            if(script_requete->exec ())
                qDebug("Ajout Personnes réussit");

            //On récupère l'id de la nouvelle Personnes
            int idP = 0;

            while (idP == 0) {
                script_requete->prepare ("SELECT idP FROM Personnes WHERE cni = :cni ");
                script_requete->bindValue (":cni",cni);
                script_requete->exec ();
                script_requete->last ();
                idP = script_requete->value (0).toInt ();
            }

            //On l'ajout à la table Occupants
            script_requete->prepare ("INSERT INTO Occupants(idPO,date_entree,date_fin_sejour,date_butoire) VALUES(:idP,:date,:date_fin_sejour,:date_butoire) ");
            script_requete->bindValue (":idP",idP);
            script_requete->bindValue (":date",date);
            script_requete->bindValue (":date_fin_sejour",date_fin_sejour);
            script_requete->bindValue(":date_butoire",date_butoire);
            script_requete->exec ();

            int rowidOcc {0};

            while (rowidOcc == 0) {

                script_requete->prepare("SELECT rowid FROM Occupants WHERE idPO = :idP;");
                script_requete->bindValue (":idP",idP);
                script_requete->exec ();
                script_requete->last ();
                rowidOcc = script_requete->value (0).toInt ();
                qDebug("rowid du nouvel occupants en cours...");
            }
            qDebug("rowid du nouvel occupants récupérer");

            //On le met dans OccupeCh
            script_requete->prepare ("INSERT INTO OccupeCh (idChO,numeroChO) VALUES (:rowidOcc,:Ch) ");
            script_requete->bindValue (":rowidOcc",rowidOcc);
            script_requete->bindValue (":Ch",Ch);
            script_requete->exec ();

            //On UPDATE la Chambre
            script_requete->prepare ("UPDATE Chambres SET etat='O' WHERE numero = :Ch ");
            script_requete->bindValue (":Ch",Ch);
            script_requete->exec ();

}

//...

//Boutiques
void Script::ajoutOccupantBt(QString Bt, QString date, QString cni, QString nom, QString prenom, QString age, QString profession, QString contact, QString pays, QString ville, QString adresse, QString email, QString date_fin_sejour, QString date_butoire, QString cni_le, QString cni_a, QString commentaires){

    //Ajout dans la table Personnes

    script_requete->prepare ("INSERT INTO Personnes(cni,nom,prenom,age,profession,contact,pays,ville,adresse,email,cni_le,cni_a,commentaires) VALUES(:cni,:nom,:prenom,:age,:profession,:contact,:pays,:ville,:adresse,:email,:cni_le,:cni_a,:commentaires) ");
    script_requete->bindValue (":cni",cni);
    script_requete->bindValue (":nom",nom);
    script_requete->bindValue (":prenom",prenom);
    script_requete->bindValue (":age",age);
    script_requete->bindValue (":profession",profession);
    script_requete->bindValue (":contact",contact);
    script_requete->bindValue (":pays",pays);
    script_requete->bindValue (":ville",ville);
    script_requete->bindValue (":adresse",adresse);
    script_requete->bindValue (":email",email);
    script_requete->bindValue (":cni_le",cni_le);
    script_requete->bindValue (":cni_a",cni_a);
    script_requete->bindValue (":commentaires",commentaires);

    //...

            qDebug("Ajout Personnes");
            if(script_requete->exec ())
                qDebug("Ajout Personnes réussit");

            //On récupère l'id de la nouvelle Personnes
            int idP = 0;

            while (idP == 0) {
                script_requete->prepare ("SELECT idP FROM Personnes WHERE cni = :cni ");
                script_requete->bindValue (":cni",cni);
                script_requete->exec ();
                script_requete->last ();
                idP = script_requete->value (0).toInt ();
            }

            //On l'ajout à la table Occupants
            script_requete->prepare ("INSERT INTO Occupants(idPO,date_entree,date_fin_sejour,date_butoire) VALUES(:idP,:date,:date_fin_sejour,:date_butoire) ");
            script_requete->bindValue (":idP",idP);
            script_requete->bindValue (":date",date);
            script_requete->bindValue (":date_fin_sejour",date_fin_sejour);
            script_requete->bindValue(":date_butoire",date_butoire);
            script_requete->exec ();

            //On le met dans OccupeBt
            int rowidOcc {0};

            while (rowidOcc == 0) {

                script_requete->prepare("SELECT rowid FROM Occupants WHERE idPO = :idP;");
                script_requete->bindValue (":idP",idP);
                script_requete->exec ();
                script_requete->last ();
                rowidOcc = script_requete->value (0).toInt ();
                qDebug("rowid du nouvel occupants en cours...");
            }
            qDebug("rowid du nouvel occupants récupérer");

            script_requete->prepare ("INSERT INTO OccupeBt(idBtO,numeroBtO) VALUES (:rowidOcc,:Bt) ");
            script_requete->bindValue (":rowidOcc",rowidOcc);
            script_requete->bindValue (":Bt",Bt);
            script_requete->exec ();

            //On UPDATE la Boutique
            script_requete->prepare ("UPDATE Boutiques SET etat='O' WHERE numero = :Bt ");
            script_requete->bindValue (":Bt",Bt);
            script_requete->exec ();


}

//...


//Suppression Occupant
void Script::supprimeOccupantAp(QString numeroAp){
    //On récupère la date
    QString *date = new QString("");

    Dialog *diag = new Dialog(date);
    diag->titre->setText ("Date de libération");
    diag->exec ();

    script_requete->prepare ("UPDATE Appartements SET etat='L' WHERE numero = :numero");
    script_requete->bindValue (":numero",numeroAp);
    script_requete->exec ();

    script_requete->prepare ("SELECT idAO FROM OccupeAp WHERE numeroAO = :numero ");
    script_requete->bindValue (":numero",numeroAp);
    script_requete->exec ();

    if(!script_requete->last ())
        return;

    int rowIdOcc = script_requete->value (0).toInt ();

    script_requete->prepare ("UPDATE Occupants SET date_sortie = :date WHERE rowid = :rowIdOcc");
    script_requete->bindValue (":date",*date);
    script_requete->bindValue (":rowIdOcc",rowIdOcc);
    script_requete->exec ();

}

void Script::supprimeOccupantSt(QString numeroSt){

    //On récupère la date
    QString *date = new QString;

    Dialog *diag = new Dialog(date);
    diag->titre->setText ("Date de libération");
    diag->exec ();

    script_requete->prepare ("UPDATE Studios SET etat='L' WHERE numero = :numero");
    script_requete->bindValue (":numero",numeroSt);
    script_requete->exec ();

    script_requete->prepare ("SELECT idStO FROM OccupeSt WHERE numeroStO = :numero ");
    script_requete->bindValue (":numero",numeroSt);
    script_requete->exec ();

    if(!script_requete->last ())
        return;

    int rowIdOcc = script_requete->value (0).toInt ();

    script_requete->prepare ("UPDATE Occupants SET date_sortie = :date WHERE rowid = :rowIdOcc");
    script_requete->bindValue (":date",*date);
    script_requete->bindValue (":rowIdOcc",rowIdOcc);
    script_requete->exec ();

}

void Script::supprimeOccupantCh(QString numeroCh){
    //On récupère la date
    QString *date = new QString;

    Dialog *diag = new Dialog(date);
    diag->titre->setText ("Date de libération");
    diag->exec ();

    script_requete->prepare ("UPDATE Chambres SET etat='L' WHERE numero = :numero");
    script_requete->bindValue (":numero",numeroCh);
    script_requete->exec ();

    script_requete->prepare ("SELECT idChO FROM OccupeCh WHERE numeroChO = :numero ");
    script_requete->bindValue (":numero",numeroCh);
    script_requete->exec ();

    if(!script_requete->last ())
        return;


    int rowIdOcc = script_requete->value (0).toInt ();

    script_requete->prepare ("UPDATE Occupants SET date_sortie = :date WHERE rowid = :rowIdOcc");
    script_requete->bindValue (":date",*date);
    script_requete->bindValue (":rowIdOcc",rowIdOcc);
    script_requete->exec ();

}

void Script::supprimeOccupantBt(QString numeroBt){
    //On récupère la date
    QString *date = new QString;

    Dialog *diag = new Dialog(date);
    diag->titre->setText ("Date de libération");
    diag->exec ();

    script_requete->prepare ("UPDATE Boutiques SET etat='L' WHERE numero = :numero");
    script_requete->bindValue (":numero",numeroBt);
    script_requete->exec ();

    script_requete->prepare ("SELECT idBtO FROM OccupeBt WHERE numeroBtO = :numero ");
    script_requete->bindValue (":numero",numeroBt);
    script_requete->exec ();

    if(!script_requete->last ())
        return;

    int rowIdOcc = script_requete->value (0).toInt ();

    script_requete->prepare ("UPDATE Occupants SET date_sortie = :date WHERE rowid = :rowIdOcc");
    script_requete->bindValue (":date",*date);
    script_requete->bindValue (":rowIdOcc",rowIdOcc);
    script_requete->exec ();
}


//Ajout probleme
void Script::ajoutProblemeAp(QString numero,QString probleme, QString date){
    script_requete->prepare ("INSERT INTO ProblemeAp VALUES (:num , :pro , :date )");
    script_requete->bindValue (":num",numero);
    script_requete->bindValue (":pro",probleme);
    script_requete->bindValue (":date",date);
    script_requete->exec ();
}

void Script::ajoutProblemeSt(QString numero, QString probleme, QString date){
    script_requete->prepare ("INSERT INTO ProblemeSt VALUES (:num , :pro , :date )");
    script_requete->bindValue (":num",numero);
    script_requete->bindValue (":pro",probleme);
    script_requete->bindValue (":date",date);
    script_requete->exec ();
}

void Script::ajoutProblemeCh(QString numero, QString probleme, QString date){
    script_requete->prepare ("INSERT INTO ProblemeCh VALUES (:num , :pro , :date )");
    script_requete->bindValue (":num",numero);
    script_requete->bindValue (":pro",probleme);
    script_requete->bindValue (":date",date);
    script_requete->exec ();
}

void Script::ajoutProblemeBt(QString numero, QString probleme, QString date){
    script_requete->prepare ("INSERT INTO ProblemeBt VALUES (:num , :pro , :date )");
    script_requete->bindValue (":num",numero);
    script_requete->bindValue (":pro",probleme);
    script_requete->bindValue (":date",date);
    script_requete->exec ();
}


