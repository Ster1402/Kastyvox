#ifndef FENETRE_H
#define FENETRE_H

#include <QMainWindow>
#include <QObject>
#include <QLabel>
#include <QMenu>
#include <QAction>
#include <QWidget>
#include "script.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>

#include <QListView>
#include <QStringList>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QStandardItemModel>

#include <QFile>
#include <QMessageBox>
#include <QDialog>

#include <QTabWidget>

class Fenetre : public QMainWindow
{
    Q_OBJECT
public:
    //Information ajout
    QString date;
    QString cni;
    QString nom;
    QString prenom;
    QString age{};
    QString profession;
    QString contact;
    QString date_fin_sejour;
    QString date_butoire{};
    QString pays;
    QString ville;
    QString adresse;
    QString email;
    QString cni_le;
    QString cni_a;
    QString commentaires;

    //Central Widget
    QWidget *central_widget;
    QVBoxLayout *principale;

    //On connecte les différents slots
    void connection();

    //On crée le menu
    void creationMenu();

    //Actualisation des vues
    void chargerVue();

    //Initialisation variable
    void initialiser();

    void grilleApparts();
    void grilleStudios();
    void grilleChambres();
    void grilleBoutiques();

    void changementColoration();

    explicit Fenetre(QWidget *parent = nullptr);

public slots:
    //Ajout occupant
    void ajouterOccupantAp();

    void ajouterOccupantSt();

    void ajouterOccupantCh();

    void ajouterOccupantBt();

    //Ajout probleme
    void ajoutProblemeAp();
    void ajoutProblemeSt();
    void ajoutProblemeCh();
    void ajoutProblemeBt();

    //Supprimer occupant
    void supprimerOccupantAp();
    void supprimerOccupantSt();
    void supprimerOccupantCh();
    void supprimerOccupantBt();

    //Historique Occupants
    void historiqueOccupantAp();
    void historiqueOccupantSt();
    void historiqueOccupantCh();
    void historiqueOccupantBt();

    //Historique Problemes
    void historiqueProblemeAp();
    void historiqueProblemeSt();
    void historiqueProblemeCh();
    void historiqueProblemeBt();

    //Détails
    void detailsOccupantsAp();
    void detailsOccupantsSt();
    void detailsOccupantsCh();
    void detailsOccupantsBt();

    //Modifer
    void modifierPersonnes();
    void modifierDates();

    //Update modele
    void updateModele(QStandardItemModel*,const QStringList&);
    /*void actualiser();
     * actualise = new QAction(tr("Actualiser"));
        actualise->setShortcut (QKeySequence("Ctrl+A"));
        modifier->addAction (actualise);*/

private:


    int indexA;
    int indexS;
    int indexC;
    int indexB;

    //Element design

    QTabWidget *onglets;

    QWidget *w_apparts;
    QWidget *w_studios;
    QWidget *w_chambres;
    QWidget *w_boutiques;

    QLabel *titreA;
    QLabel *titreS;
    QLabel *titreC;
    QLabel *titreB;

    QGridLayout *grilleA;
    QGridLayout *grilleS;
    QGridLayout *grilleC;
    QGridLayout *grilleB;

    //Vue pour l'affichage des informations principales (par pièce)
    QListView *vueA1;
    QListView *vueA2;
    QListView *vueA3;
    QListView *vueA4;

    QListView *vueS1;
    QListView *vueS2;
    QListView *vueS3;
    QListView *vueS4;
    QListView *vueS5;
    QListView *vueS6;
    QListView *vueS7;
    QListView *vueS8;

    QListView *vueCH1;
    QListView *vueCH2;
    QListView *vueCH3;
    QListView *vueCH4;

    QListView *vueB1;
    QListView *vueB2;
    QListView *vueB3;


    //Modèles (par Pièce)
    QStandardItemModel *modele_A1;
    QStandardItemModel *modele_A2;
    QStandardItemModel *modele_A3;
    QStandardItemModel *modele_A4;

    QStandardItemModel *modele_S1;
    QStandardItemModel *modele_S2;
    QStandardItemModel *modele_S3;
    QStandardItemModel *modele_S4;
    QStandardItemModel *modele_S5;
    QStandardItemModel *modele_S6;
    QStandardItemModel *modele_S7;
    QStandardItemModel *modele_S8;

    QStandardItemModel *modele_CH1;
    QStandardItemModel *modele_CH2;
    QStandardItemModel *modele_CH3;
    QStandardItemModel *modele_CH4;

    QStandardItemModel *modele_B1;
    QStandardItemModel *modele_B2;
    QStandardItemModel *modele_B3;

    //QStringList pour chaque pièce(4 + 8 + 4 + 3) : Dans le central Widget
    QStringList liste_affiche_A1;
    QStringList liste_affiche_A2;
    QStringList liste_affiche_A3;
    QStringList liste_affiche_A4;

    QStringList liste_affiche_S1;
    QStringList liste_affiche_S2;
    QStringList liste_affiche_S3;
    QStringList liste_affiche_S4;
    QStringList liste_affiche_S5;
    QStringList liste_affiche_S6;
    QStringList liste_affiche_S7;
    QStringList liste_affiche_S8;

    QStringList liste_affiche_Ch1;
    QStringList liste_affiche_Ch2;
    QStringList liste_affiche_Ch3;
    QStringList liste_affiche_Ch4;

    QStringList liste_affiche_B1;
    QStringList liste_affiche_B2;
    QStringList liste_affiche_B3;

    //Srcipt
    Script requetes;

    //Menu Details
    QMenu *details_occupants;
            QMenu *details_o_appart;
                QAction *details_o_A1;
                QAction *details_o_A2;
                QAction *details_o_A3;
                QAction *details_o_A4;
            QMenu *details_o_studio;
                QAction *details_o_S1;
                QAction *details_o_S2;
                QAction *details_o_S3;
                QAction *details_o_S4;
                QAction *details_o_S5;
                QAction *details_o_S6;
                QAction *details_o_S7;
                QAction *details_o_S8;
            QMenu *details_o_chambre;
                QAction *details_o_CH1;
                QAction *details_o_CH2;
                QAction *details_o_CH3;
                QAction *details_o_CH4;

            QMenu *details_o_boutique;
                QAction *details_o_B1;
                QAction *details_o_B2;
                QAction *details_o_B3;

        //Menu Script
            //Scripts historiques
            QMenu *script_historiques;
                QMenu *h_occupants;
                    QAction *h_o_apparts;
                    QAction *h_o_studios;
                    QAction *h_o_chambres;
                    QAction *h_o_boutiques;
                QMenu *h_problemes;
                    QAction *p_apparts;
                    QAction *p_studios;
                    QAction *p_chambres;
                    QAction *p_boutiques;

            //Scripts Ajouter (Occupants GOOD)
            QMenu *script_ajouter;
                QMenu *add_occupants;
                    QMenu *add_o_apparts;
                        QAction *add_o_A1;
                        QAction *add_o_A2;
                        QAction *add_o_A3;
                        QAction *add_o_A4;
                    QMenu *add_o_studios;
                        QAction *add_o_S1;
                        QAction *add_o_S2;
                        QAction *add_o_S3;
                        QAction *add_o_S4;
                        QAction *add_o_S5;
                        QAction *add_o_S6;
                        QAction *add_o_S7;
                        QAction *add_o_S8;
                    QMenu *add_o_chambres;
                        QAction *add_o_Ch1;
                        QAction *add_o_Ch2;
                        QAction *add_o_Ch3;
                        QAction *add_o_Ch4;
                    QMenu *add_o_boutiques;
                        QAction *add_o_B1;
                        QAction *add_o_B2;
                        QAction *add_o_B3;

                QMenu *add_problemes;
                    QMenu *add_p_apparts;
                        QAction *add_p_A1;
                        QAction *add_p_A2;
                        QAction *add_p_A3;
                        QAction *add_p_A4;

                    QMenu *add_p_studios;
                        QAction *add_p_S1;
                        QAction *add_p_S2;
                        QAction *add_p_S3;
                        QAction *add_p_S4;
                        QAction *add_p_S5;
                        QAction *add_p_S6;
                        QAction *add_p_S7;
                        QAction *add_p_S8;

                    QMenu *add_p_chambres;
                        QAction *add_p_Ch1;
                        QAction *add_p_Ch2;
                        QAction *add_p_Ch3;
                        QAction *add_p_Ch4;

                    QMenu *add_p_boutiques;
                        QAction *add_p_B1;
                        QAction *add_p_B2;
                        QAction *add_p_B3;

            //Scripts remove occupant : GOOD
            QMenu *script_enlever;
                QMenu *rmv_occupants;
                    QMenu *rmv_o_apparts;
                        QAction *rmv_o_A1;
                        QAction *rmv_o_A2;
                        QAction *rmv_o_A3;
                        QAction *rmv_o_A4;
                    QMenu *rmv_o_studios;
                        QAction *rmv_o_S1;
                        QAction *rmv_o_S2;
                        QAction *rmv_o_S3;
                        QAction *rmv_o_S4;
                        QAction *rmv_o_S5;
                        QAction *rmv_o_S6;
                        QAction *rmv_o_S7;
                        QAction *rmv_o_S8;
                    QMenu *rmv_o_chambres;
                        QAction *rmv_o_Ch1;
                        QAction *rmv_o_Ch2;
                        QAction *rmv_o_Ch3;
                        QAction *rmv_o_Ch4;
                    QMenu *rmv_o_boutiques;
                        QAction *rmv_o_B1;
                        QAction *rmv_o_B2;
                        QAction *rmv_o_B3;

                    QMenu *modifier;
                        QAction *modifier_personnes;
                        QAction *modifier_dates;

};

#endif // FENETRE_H
//QMenu information appart
/* Si utile plutard
 * QMenu *info_appart;
            QAction *info_A1;
            QAction *info_A2;
            QAction *info_A3;
            QAction *info_A4;

        QMenu *info_studio;
            QAction *info_S1;
            QAction *info_S2;
            QAction *info_S3;
            QAction *info_S4;
            QAction *info_S5;
            QAction *info_S6;
            QAction *info_S7;
            QAction *info_S8;

       QMenu *info_chambre;
            QAction *info_CH1;
            QAction *info_CH2;
            QAction *info_CH3;
            QAction *info_CH4;

       QMenu *info_boutique;
            QAction *info_B1;
            QAction *info_B2;
            QAction *info_B3;
*/
