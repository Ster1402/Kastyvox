#ifndef SCRIPT_H
#define SCRIPT_H

#include <QSqlQuery>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlRelation>
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>
#include <QTableView>

#include <QStringList>
#include <QStringListModel>

#include <QPalette>
#include <QColor>

class Script
{
public:
    Script();

    //DATABASE
    QSqlDatabase kastyvox_db;

    void actualiserDB();

    void updateDB();

    void chargerDB();

    //Chargement des StringList Pour chacune des vues : au lancement et l'actualisation des vues

    //Pour les apparts
    void liste_affiche_A1(QStringList &liste_A1);
    void liste_affiche_A2(QStringList& liste_A2);
    void liste_affiche_A3(QStringList& liste_A3);
    void liste_affiche_A4(QStringList& liste_A4);

    //Pour les studios
    void liste_affiche_S1(QStringList& liste);
    void liste_affiche_S2(QStringList& liste);
    void liste_affiche_S3(QStringList& liste);
    void liste_affiche_S4(QStringList& liste);
    void liste_affiche_S5(QStringList& liste);
    void liste_affiche_S6(QStringList& liste);
    void liste_affiche_S7(QStringList& liste);
    void liste_affiche_S8(QStringList& liste);

    //Pour les chambres
    void liste_affiche_CH1(QStringList& liste);
    void liste_affiche_CH2(QStringList& liste);
    void liste_affiche_CH3(QStringList& liste);
    void liste_affiche_CH4(QStringList& liste);

    //Pour les boutiques
    void liste_affiche_B1(QStringList& liste);
    void liste_affiche_B2(QStringList& liste);
    void liste_affiche_B3(QStringList& liste);

    //Ajout d'un Occupant
    void ajoutOccupantAp(QString Ap, QString date, QString cni, QString nom, QString prenom, QString age, QString profession, QString contact, QString pays, QString ville, QString adresse, QString email, QString date_fin_sejour, QString date_butoire,QString cni_le,QString cni_a,QString commentaires);

    void ajoutOccupantSt(QString St,QString date,QString cni, QString nom,QString prenom,QString age,QString profession, QString contact, QString pays, QString ville, QString adresse, QString email, QString date_fin_sejour, QString date_butoire,QString cni_le,QString cni_a,QString commentaires);

    void ajoutOccupantCh(QString Ch,QString date,QString cni, QString nom,QString prenom,QString age,QString profession, QString contact, QString pays, QString ville, QString adresse, QString email, QString date_fin_sejour, QString date_butoire,QString cni_le,QString cni_a,QString commentaires);

    void ajoutOccupantBt(QString Bt, QString date, QString cni, QString nom, QString prenom, QString age, QString profession, QString contact, QString pays, QString ville, QString adresse, QString email, QString date_fin_sejour, QString date_butoire, QString cni_le, QString cni_a, QString commentaires);

    //Suppression occupant
    void supprimeOccupantAp(QString numeroAp);
    void supprimeOccupantSt(QString numeroSt);
    void supprimeOccupantCh(QString numeroCh);
    void supprimeOccupantBt(QString numeroBt);

    //Ajout probleme
    void ajoutProblemeAp(QString numero, QString probleme, QString date);
    void ajoutProblemeSt(QString numero, QString probleme, QString date);
    void ajoutProblemeCh(QString numero, QString probleme, QString date);
    void ajoutProblemeBt(QString numero, QString probleme, QString date);

    //Détails sur un Occupant


    //Ajout Problème


    //Getters and Setters
    void setScript_requete(QSqlQuery* rq){ script_requete = rq; }
    QSqlQuery* getScript_requete(){ return script_requete; }

    //Palette
    QPalette getPaletteVerte(){return paletteVerte;}

    QPalette getPaletteRouge(){return paletteRouge;}

private:
    QSqlQuery *script_requete;

    QPalette paletteVerte;
    QColor colorG; //Vert : Libre

    QPalette paletteRouge;
    QColor colorR; // Rouge : Occupé
};

#endif // SCRIPT_H
