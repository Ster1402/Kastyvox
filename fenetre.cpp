#include "fenetre.h"
#include <QIcon>
#include <QMenuBar>
#include <QApplication>
#include <QStandardItem>
#include <QStandardItemModel>


Fenetre::Fenetre(QWidget *parent) : QMainWindow(parent)
{
    creationMenu ();
    initialiser ();

    requetes.actualiserDB ();

    grilleApparts ();
    grilleStudios ();
    grilleChambres ();
    grilleBoutiques ();

    central_widget = new QWidget(this);

    principale->addWidget (onglets);

    central_widget->setLayout (principale);

    chargerVue ();
    connection ();
    setCentralWidget (central_widget);
    setWindowIcon (QIcon("logo.png"));
    setWindowTitle (tr("KASTYVOX"));
    setMinimumSize (1024,640);
}

void Fenetre::creationMenu(){
    //Détails Occupants
    details_occupants = menuBar ()->addMenu (tr("Détails"));

        details_o_appart = new QMenu(tr("Occupants Appartements"));
          details_occupants->addMenu (details_o_appart);
            details_o_A1 = new QAction(tr("Appart : APT 01"));
                details_o_appart->addAction (details_o_A1);
            details_o_A2 = new QAction(tr("Appart : APT 02"));
                details_o_appart->addAction (details_o_A2);
            details_o_A3 = new QAction(tr("Appart : APT 101"));
                details_o_appart->addAction (details_o_A3);
            details_o_A4 = new QAction(tr("Appart : APT 102"));
                details_o_appart->addAction (details_o_A4);

        details_o_studio = new QMenu(tr("Occupants Studios"));
            details_occupants->addMenu (details_o_studio);

            details_o_S1 = new QAction(tr("Studio : ST 01"));
                details_o_studio->addAction (details_o_S1);
            details_o_S2 = new QAction(tr("Studio : ST 02"));
                details_o_studio->addAction (details_o_S2);
            details_o_S3 = new QAction(tr("Studio : ST 03"));
                details_o_studio->addAction (details_o_S3);
            details_o_S4 = new QAction(tr("Studio : ST 04"));
                details_o_studio->addAction (details_o_S4);
            details_o_S5 = new QAction(tr("Studio : ST 101"));
                details_o_studio->addAction (details_o_S5);
            details_o_S6 = new QAction(tr("Studio : ST 102"));
                details_o_studio->addAction (details_o_S6);
            details_o_S7 = new QAction(tr("Studio : ST 103"));
                details_o_studio->addAction (details_o_S7);
            details_o_S8 = new QAction(tr("Studio : ST 104"));
                details_o_studio->addAction (details_o_S8);

        details_o_chambre = new QMenu(tr("Occupants Chambres"));
            details_occupants->addMenu (details_o_chambre);

            details_o_CH1 = new QAction(tr("Chambre : CH 101"));
                details_o_chambre->addAction (details_o_CH1);
            details_o_CH2 = new QAction(tr("Chambre : CH 102"));
                details_o_chambre->addAction (details_o_CH2);
            details_o_CH3 = new QAction(tr("Chambre : CH 103"));
                details_o_chambre->addAction (details_o_CH3);
            details_o_CH4 = new QAction(tr("Chambre : CH 104"));
                details_o_chambre->addAction (details_o_CH4);

        details_o_boutique = new QMenu(tr("Occupants Boutiques"));
            details_occupants->addMenu (details_o_boutique);

            details_o_B1 = new QAction(tr("Boutiques : B 01"));
                details_o_boutique->addAction (details_o_B1);
            details_o_B2 = new QAction(tr("Boutiques : B 02"));
                details_o_boutique->addAction (details_o_B2);
            details_o_B3 = new QAction(tr("Boutiques : B 03"));
                details_o_boutique->addAction (details_o_B3);

    //Scripts

    //Scripts Historiques
    script_historiques = menuBar ()->addMenu (tr("Historiques"));

        h_occupants = new QMenu(tr("Historiques occupants"));
            script_historiques->addMenu (h_occupants);

            h_o_apparts = new QAction(tr("Appartements"));
                h_occupants->addAction (h_o_apparts);
            h_o_studios = new QAction(tr("Studios"));
                h_occupants->addAction (h_o_studios);
            h_o_chambres = new QAction(tr("Chambres"));
                h_occupants->addAction (h_o_chambres);
            h_o_boutiques = new QAction(tr("Boutiques"));
                h_occupants->addAction (h_o_boutiques);

        h_problemes = new QMenu(tr("Historiques des problèmes survenus"));
            script_historiques->addMenu (h_problemes);

            p_apparts = new QAction(tr("Appartements"));
                h_problemes->addAction (p_apparts);
            p_studios = new QAction(tr("Studios"));
                h_problemes->addAction (p_studios);
            p_chambres = new QAction(tr("Chambres"));
                h_problemes->addAction (p_chambres);
            p_boutiques = new QAction(tr("Boutiques"));
                h_problemes->addAction (p_boutiques);


    //Scripts Ajouter
    script_ajouter = menuBar ()->addMenu (tr("Ajouter"));
        //Occupants
        add_occupants = new QMenu(tr("Ajouter Occupants"));
        script_ajouter->addMenu (add_occupants);
            add_o_apparts = new QMenu(tr("Dans un Appartement"));
            add_occupants->addMenu (add_o_apparts);

                add_o_A1 = new QAction(tr("Apparts : APT 01"));
                add_o_apparts->addAction (add_o_A1);

                add_o_A2 = new QAction(tr("Apparts : APT 02"));
                add_o_apparts->addAction (add_o_A2);

                add_o_A3 = new QAction(tr("Apparts : APT 101"));
                add_o_apparts->addAction (add_o_A3);

                add_o_A4 = new QAction(tr("Apparts : APT 102"));
                add_o_apparts->addAction (add_o_A4);

           add_o_studios = new QMenu(tr("Dans un Studio"));
           add_occupants->addMenu (add_o_studios);

                add_o_S1 = new QAction(tr("Studio : ST 01"));
                add_o_studios->addAction (add_o_S1);

                add_o_S2 = new QAction(tr("Studio : ST 02"));
                add_o_studios->addAction (add_o_S2);

                add_o_S3 = new QAction(tr("Studio : ST 03"));
                add_o_studios->addAction (add_o_S3);

                add_o_S4 = new QAction(tr("Studio : ST 04"));
                add_o_studios->addAction (add_o_S4);

                add_o_S5 = new QAction(tr("Studio : ST 101"));
                add_o_studios->addAction (add_o_S5);

                add_o_S6 = new QAction(tr("Studio : ST 102"));
                add_o_studios->addAction (add_o_S6);

                add_o_S7 = new QAction(tr("Studio : ST 103"));
                add_o_studios->addAction (add_o_S7);

                add_o_S8 = new QAction(tr("Studio : ST 104"));
                add_o_studios->addAction (add_o_S8);

           add_o_chambres = new QMenu(tr("Dans une Chambre"));
           add_occupants->addMenu (add_o_chambres);

                add_o_Ch1 = new QAction(tr("Chambre : CH 101"));
                add_o_chambres->addAction (add_o_Ch1);

                add_o_Ch2 = new QAction(tr("Chambre : CH 102"));
                add_o_chambres->addAction (add_o_Ch2);

                add_o_Ch3 = new QAction(tr("Chambre : CH 103"));
                add_o_chambres->addAction (add_o_Ch3);

                add_o_Ch4 = new QAction(tr("Chambre : CH 104"));
                add_o_chambres->addAction (add_o_Ch4);

           add_o_boutiques = new QMenu(tr("Dans une Boutique"));
           add_occupants->addMenu (add_o_boutiques);

                add_o_B1 = new QAction(tr("Boutique : B 01"));
                add_o_boutiques->addAction (add_o_B1);

                add_o_B2 = new QAction(tr("Boutique : B 02"));
                add_o_boutiques->addAction (add_o_B2);

                add_o_B3 = new QAction(tr("Boutique : B 03"));
                add_o_boutiques->addAction (add_o_B3);

        //Problemes
        add_problemes = new QMenu(tr("Problèmes survenus"));
        script_ajouter->addMenu (add_problemes);

           add_p_apparts = new QMenu(tr("Dans un Appartement"));
           add_problemes->addMenu (add_p_apparts);

                add_p_A1 = new QAction(tr("Appart : APT 01"));
                add_p_apparts->addAction (add_p_A1);

                add_p_A2 = new QAction(tr("Appart : APT 02"));
                add_p_apparts->addAction (add_p_A2);

                add_p_A3 = new QAction(tr("Appart : APT 101"));
                add_p_apparts->addAction (add_p_A3);

                add_p_A4 = new QAction(tr("Appart : APT 102"));
                add_p_apparts->addAction (add_p_A4);

           add_p_studios = new QMenu(tr("Dans un Studio"));
           add_problemes->addMenu (add_p_studios);

                add_p_S1 = new QAction(tr("Studio : ST 01"));
                add_p_studios->addAction (add_p_S1);

                add_p_S2 = new QAction(tr("Studio : ST 02"));
                add_p_studios->addAction (add_p_S2);

                add_p_S3 = new QAction(tr("Studio : ST 03"));
                add_p_studios->addAction (add_p_S3);

                add_p_S4 = new QAction(tr("Studio : ST 04"));
                add_p_studios->addAction (add_p_S4);

                add_p_S5 = new QAction(tr("Studio : ST 101"));
                add_p_studios->addAction (add_p_S5);

                add_p_S6 = new QAction(tr("Studio : ST 102"));
                add_p_studios->addAction (add_p_S6);

                add_p_S7 = new QAction(tr("Studio : ST 103"));
                add_p_studios->addAction (add_p_S7);

                add_p_S8 = new QAction(tr("Studio : ST 104"));
                add_p_studios->addAction (add_p_S8);

           add_p_chambres = new QMenu(tr("Dans une Chambre"));
           add_problemes->addMenu (add_p_chambres);

                add_p_Ch1 = new QAction(tr("Chambre : CH 101"));
                add_p_chambres->addAction (add_p_Ch1);

                add_p_Ch2 = new QAction(tr("Chambre : CH 102"));
                add_p_chambres->addAction (add_p_Ch2);

                add_p_Ch3 = new QAction(tr("Chambre : CH 103"));
                add_p_chambres->addAction (add_p_Ch3);

                add_p_Ch4 = new QAction(tr("Chambre : CH 104"));
                add_p_chambres->addAction (add_p_Ch4);

           add_p_boutiques = new QMenu(tr("Dans une Boutique"));
           add_problemes->addMenu (add_p_boutiques);

                add_p_B1 = new QAction(tr("Boutique : B 01"));
                add_p_boutiques->addAction (add_p_B1);

                add_p_B2 = new QAction(tr("Boutique : B 02"));
                add_p_boutiques->addAction (add_p_B2);

                add_p_B3 = new QAction(tr("Boutique : B 03"));
                add_p_boutiques->addAction (add_p_B3);

    //Scripts Enlever
    script_enlever = menuBar ()->addMenu (tr("Libérer"));
    //Occupants
    rmv_occupants = new QMenu(tr("Supprimer Occupant"));
    script_enlever->addMenu (rmv_occupants);
        rmv_o_apparts = new QMenu(tr("D'un Appartement"));
        rmv_occupants->addMenu (rmv_o_apparts);

            rmv_o_A1 = new QAction(tr("Apparts : APT 01"));
            rmv_o_apparts->addAction (rmv_o_A1);

            rmv_o_A2 = new QAction(tr("Apparts : APT 02"));
            rmv_o_apparts->addAction (rmv_o_A2);

            rmv_o_A3 = new QAction(tr("Apparts : APT 101"));
            rmv_o_apparts->addAction (rmv_o_A3);

            rmv_o_A4 = new QAction(tr("Apparts : APT 102"));
            rmv_o_apparts->addAction (rmv_o_A4);

       rmv_o_studios = new QMenu(tr("D'un Studio"));
       rmv_occupants->addMenu (rmv_o_studios);

            rmv_o_S1 = new QAction(tr("Studio : ST 01"));
            rmv_o_studios->addAction (rmv_o_S1);

            rmv_o_S2 = new QAction(tr("Studio : ST 02"));
            rmv_o_studios->addAction (rmv_o_S2);

            rmv_o_S3 = new QAction(tr("Studio : ST 03"));
            rmv_o_studios->addAction (rmv_o_S3);

            rmv_o_S4 = new QAction(tr("Studio : ST 04"));
            rmv_o_studios->addAction (rmv_o_S4);

            rmv_o_S5 = new QAction(tr("Studio : ST 101"));
            rmv_o_studios->addAction (rmv_o_S5);

            rmv_o_S6 = new QAction(tr("Studio : ST 102"));
            rmv_o_studios->addAction (rmv_o_S6);

            rmv_o_S7 = new QAction(tr("Studio : ST 103"));
            rmv_o_studios->addAction (rmv_o_S7);

            rmv_o_S8 = new QAction(tr("Studio : ST 104"));
            rmv_o_studios->addAction (rmv_o_S8);

       rmv_o_chambres = new QMenu(tr("D'une Chambre"));
       rmv_occupants->addMenu (rmv_o_chambres);

            rmv_o_Ch1 = new QAction(tr("Chambre : CH 101"));
            rmv_o_chambres->addAction (rmv_o_Ch1);

            rmv_o_Ch2 = new QAction(tr("Chambre : CH 102"));
            rmv_o_chambres->addAction (rmv_o_Ch2);

            rmv_o_Ch3 = new QAction(tr("Chambre : CH 103"));
            rmv_o_chambres->addAction (rmv_o_Ch3);

            rmv_o_Ch4 = new QAction(tr("Chambre : CH 104"));
            rmv_o_chambres->addAction (rmv_o_Ch4);

       rmv_o_boutiques = new QMenu(tr("D'une Boutique"));
       rmv_occupants->addMenu (rmv_o_boutiques);

            rmv_o_B1 = new QAction(tr("Boutique : B 01"));
            rmv_o_boutiques->addAction (rmv_o_B1);

            rmv_o_B2 = new QAction(tr("Boutique : B 02"));
            rmv_o_boutiques->addAction (rmv_o_B2);

            rmv_o_B3 = new QAction(tr("Boutique : B 03"));
            rmv_o_boutiques->addAction (rmv_o_B3);


      modifier = menuBar ()->addMenu (tr("Modifier"));
        modifier_personnes = new QAction(tr("Modifier informations personnes"));
        modifier_personnes->setShortcut (QKeySequence("Ctrl+P"));
        modifier->addAction (modifier_personnes);

        modifier_dates = new QAction(tr("Modifier des dates"));
        modifier_dates->setShortcut (QKeySequence("Ctrl+D"));
        modifier->addAction(modifier_dates);


}

void Fenetre::initialiser(){

    onglets = new QTabWidget(this);

    principale = new QVBoxLayout;

    w_apparts = new QWidget;
    w_studios = new QWidget;
    w_chambres = new QWidget;
    w_boutiques = new QWidget;

    grilleA = new QGridLayout;
    grilleS = new QGridLayout;
    grilleC = new QGridLayout;
    grilleB = new QGridLayout;

    titreA = new QLabel;
    titreA->setText (tr("Appartements"));
    titreA->setObjectName ("tA");

    titreS = new QLabel;
    titreS->setText (tr("Studios"));
    titreS->setObjectName ("tS");

    titreC = new QLabel;
    titreC->setText (tr("Chambres"));
    titreC->setObjectName ("tC");

    titreB = new QLabel;
    titreB->setText (tr("Boutiques"));
    titreB->setObjectName ("tB");

    //Initialisation Vue et Modele

    //Vues
    vueA1 = new QListView;
        vueA1->setObjectName ("vueA1");
        vueA1->setSpacing (5);
    vueA2 = new QListView;
        vueA2->setObjectName ("vueA2");
        vueA2->setSpacing (5);
    vueA3 = new QListView;
        vueA3->setObjectName ("vueA3");
        vueA3->setSpacing (5);
    vueA4 = new QListView;
        vueA4->setObjectName ("vueA4");
        vueA4->setSpacing (5);

    vueS1 = new QListView;
        vueS1->setObjectName ("vueS1");
        vueS1->setSpacing (1);
    vueS2 = new QListView;
        vueS2->setObjectName ("vueS2");
        vueS2->setSpacing (1);
    vueS3 = new QListView;
        vueS3->setObjectName ("vueS3");
        vueS3->setSpacing (1);
    vueS4 = new QListView;
        vueS4->setObjectName ("vueS4");
        vueS4->setSpacing (1);
    vueS5 = new QListView;
        vueS5->setObjectName ("vueS5");
        vueS5->setSpacing (1);
    vueS6 = new QListView;
        vueS6->setObjectName ("vueS6");
        vueS6->setSpacing (1);
    vueS7 = new QListView;
        vueS7->setObjectName ("vueS7");
        vueS7->setSpacing (1);
    vueS8 = new QListView;
        vueS8->setObjectName ("vueS8");
        vueS8->setSpacing (1);

    vueCH1 = new QListView;
        vueCH1->setSpacing (5);
        vueCH1->setObjectName ("vueCH1");
    vueCH2 = new QListView;
        vueCH2->setSpacing (5);
        vueCH2->setObjectName ("vueCH2");
    vueCH3 = new QListView;
        vueCH3->setSpacing (5);
        vueCH3->setObjectName ("vueCH3");
    vueCH4 = new QListView;
        vueCH4->setSpacing (5);
        vueCH4->setObjectName ("vueCH4");

    vueB1 = new QListView;
        vueB1->setSpacing (5);
        vueB1->setObjectName ("vueB1");
    vueB2 = new QListView;
        vueB2->setSpacing (5);
        vueB2->setObjectName ("vueB2");
    vueB3 = new QListView;
        vueB3->setSpacing (5);
        vueB3->setObjectName ("vueB3");

    //Modèles
    modele_A1 = new QStandardItemModel;
    modele_A2 = new QStandardItemModel;
    modele_A3 = new QStandardItemModel;
    modele_A4 = new QStandardItemModel;

    modele_S1 = new QStandardItemModel;
    modele_S2 = new QStandardItemModel;
    modele_S3 = new QStandardItemModel;
    modele_S4 = new QStandardItemModel;
    modele_S5 = new QStandardItemModel;
    modele_S6 = new QStandardItemModel;
    modele_S7 = new QStandardItemModel;
    modele_S8 = new QStandardItemModel;

    modele_CH1 = new QStandardItemModel;
    modele_CH2 = new QStandardItemModel;
    modele_CH3 = new QStandardItemModel;
    modele_CH4 = new QStandardItemModel;

    modele_B1 = new QStandardItemModel;
    modele_B2 = new QStandardItemModel;
    modele_B3 = new QStandardItemModel;

}

void Fenetre::connection(){
    //Nom utiliser pour l'ajout dans un appart
    add_o_A1->setObjectName ("A1");
    add_o_A2->setObjectName ("A2");
    add_o_A3->setObjectName ("A3");
    add_o_A4->setObjectName ("A4");

    //Nom utiliser pour l'ajout dans un studio
    add_o_S1->setObjectName ("S1");
    add_o_S2->setObjectName ("S2");
    add_o_S3->setObjectName ("S3");
    add_o_S4->setObjectName ("S4");
    add_o_S5->setObjectName ("S5");
    add_o_S6->setObjectName ("S6");
    add_o_S7->setObjectName ("S7");
    add_o_S8->setObjectName ("S8");

    //Nom pour l'ajout dans une Chambre (numero CHAR(3) CHECK (numero IN ('CH1'...'CH4'))
    add_o_Ch1->setObjectName ("CH1");
    add_o_Ch2->setObjectName ("CH2");
    add_o_Ch3->setObjectName ("CH3");
    add_o_Ch4->setObjectName ("CH4");

    //Nom utiliser pour l'ajout dans une boutique
    add_o_B1->setObjectName ("B1");
    add_o_B2->setObjectName ("B2");
    add_o_B3->setObjectName ("B3");

    connect(add_o_A1,SIGNAL(triggered()),this,SLOT(ajouterOccupantAp()));
    connect(add_o_A2,SIGNAL(triggered()),this,SLOT(ajouterOccupantAp()));
    connect(add_o_A3,SIGNAL(triggered()),this,SLOT(ajouterOccupantAp()));
    connect(add_o_A4,SIGNAL(triggered()),this,SLOT(ajouterOccupantAp()));

    connect(add_o_S1,SIGNAL(triggered()),this,SLOT(ajouterOccupantSt()));
    connect(add_o_S2,SIGNAL(triggered()),this,SLOT(ajouterOccupantSt()));
    connect(add_o_S3,SIGNAL(triggered()),this,SLOT(ajouterOccupantSt()));
    connect(add_o_S4,SIGNAL(triggered()),this,SLOT(ajouterOccupantSt()));
    connect(add_o_S5,SIGNAL(triggered()),this,SLOT(ajouterOccupantSt()));
    connect(add_o_S6,SIGNAL(triggered()),this,SLOT(ajouterOccupantSt()));
    connect(add_o_S7,SIGNAL(triggered()),this,SLOT(ajouterOccupantSt()));
    connect(add_o_S8,SIGNAL(triggered()),this,SLOT(ajouterOccupantSt()));

    connect (add_o_Ch1,SIGNAL (triggered()),this,SLOT(ajouterOccupantCh()));
    connect (add_o_Ch2,SIGNAL (triggered()),this,SLOT(ajouterOccupantCh()));
    connect (add_o_Ch3,SIGNAL (triggered()),this,SLOT(ajouterOccupantCh()));
    connect (add_o_Ch4,SIGNAL (triggered()),this,SLOT(ajouterOccupantCh()));

    connect (add_o_B1,SIGNAL(triggered()),this,SLOT (ajouterOccupantBt()));
    connect (add_o_B2,SIGNAL(triggered()),this,SLOT (ajouterOccupantBt()));
    connect (add_o_B3,SIGNAL(triggered()),this,SLOT (ajouterOccupantBt()));

    //Suppression occupant

    //Nom utiliser pour la suppression dans un appart
    rmv_o_A1->setObjectName ("A1");
    rmv_o_A2->setObjectName ("A2");
    rmv_o_A3->setObjectName ("A3");
    rmv_o_A4->setObjectName ("A4");

    //Nom utiliser pour l'ajout dans un studio
    rmv_o_S1->setObjectName ("S1");
    rmv_o_S2->setObjectName ("S2");
    rmv_o_S3->setObjectName ("S3");
    rmv_o_S4->setObjectName ("S4");
    rmv_o_S5->setObjectName ("S5");
    rmv_o_S6->setObjectName ("S6");
    rmv_o_S7->setObjectName ("S7");
    rmv_o_S8->setObjectName ("S8");

    //Nom pour l'ajout dans une Chambre (numero CHAR(3) CHECK (numero IN ('CH1'...'CH4'))
    rmv_o_Ch1->setObjectName ("CH1");
    rmv_o_Ch2->setObjectName ("CH2");
    rmv_o_Ch3->setObjectName ("CH3");
    rmv_o_Ch4->setObjectName ("CH4");

    //Nom utiliser pour l'ajout dans une boutique
    rmv_o_B1->setObjectName ("B1");
    rmv_o_B2->setObjectName ("B2");
    rmv_o_B3->setObjectName ("B3");

    connect(rmv_o_A1,SIGNAL(triggered()),this,SLOT(supprimerOccupantAp ()));
    connect(rmv_o_A2,SIGNAL(triggered()),this,SLOT(supprimerOccupantAp()));
    connect(rmv_o_A3,SIGNAL(triggered()),this,SLOT(supprimerOccupantAp()));
    connect(rmv_o_A4,SIGNAL(triggered()),this,SLOT(supprimerOccupantAp()));

    connect(rmv_o_S1,SIGNAL(triggered()),this,SLOT(supprimerOccupantSt()));
    connect(rmv_o_S2,SIGNAL(triggered()),this,SLOT(supprimerOccupantSt()));
    connect(rmv_o_S3,SIGNAL(triggered()),this,SLOT(supprimerOccupantSt()));
    connect(rmv_o_S4,SIGNAL(triggered()),this,SLOT(supprimerOccupantSt()));
    connect(rmv_o_S5,SIGNAL(triggered()),this,SLOT(supprimerOccupantSt()));
    connect(rmv_o_S6,SIGNAL(triggered()),this,SLOT(supprimerOccupantSt()));
    connect(rmv_o_S7,SIGNAL(triggered()),this,SLOT(supprimerOccupantSt()));
    connect(rmv_o_S8,SIGNAL(triggered()),this,SLOT(supprimerOccupantSt()));

    connect (rmv_o_Ch1,SIGNAL (triggered()),this,SLOT(supprimerOccupantCh()));
    connect (rmv_o_Ch2,SIGNAL (triggered()),this,SLOT(supprimerOccupantCh()));
    connect (rmv_o_Ch3,SIGNAL (triggered()),this,SLOT(supprimerOccupantCh()));
    connect (rmv_o_Ch4,SIGNAL (triggered()),this,SLOT(supprimerOccupantCh()));

    connect (rmv_o_B1,SIGNAL(triggered()),this,SLOT (supprimerOccupantBt()));
    connect (rmv_o_B2,SIGNAL(triggered()),this,SLOT (supprimerOccupantBt()));
    connect (rmv_o_B3,SIGNAL(triggered()),this,SLOT (supprimerOccupantBt()));

    //Ajout probleme
    //Nom utiliser pour l'ajout d'un probleme dans un appart
    add_p_A1->setObjectName ("A1");
    add_p_A2->setObjectName ("A2");
    add_p_A3->setObjectName ("A3");
    add_p_A4->setObjectName ("A4");

    //Nom utiliser pour l'ajout d'un probleme dans un studio
    add_p_S1->setObjectName ("S1");
    add_p_S2->setObjectName ("S2");
    add_p_S3->setObjectName ("S3");
    add_p_S4->setObjectName ("S4");
    add_p_S5->setObjectName ("S5");
    add_p_S6->setObjectName ("S6");
    add_p_S7->setObjectName ("S7");
    add_p_S8->setObjectName ("S8");

    //Nom pour l'ajout d'un probleme dans une Chambre ('CH1'...'CH4'))
    add_p_Ch1->setObjectName ("CH1");
    add_p_Ch2->setObjectName ("CH2");
    add_p_Ch3->setObjectName ("CH3");
    add_p_Ch4->setObjectName ("CH4");

    //Nom utiliser pour l'ajout d'un probleme dans une boutique
    add_p_B1->setObjectName ("B1");
    add_p_B2->setObjectName ("B2");
    add_p_B3->setObjectName ("B3");

    connect(add_p_A1,SIGNAL(triggered()),this,SLOT(ajoutProblemeAp()));
    connect(add_p_A2,SIGNAL(triggered()),this,SLOT(ajoutProblemeAp()));
    connect(add_p_A3,SIGNAL(triggered()),this,SLOT(ajoutProblemeAp()));
    connect(add_p_A4,SIGNAL(triggered()),this,SLOT(ajoutProblemeAp()));

    connect(add_p_S1,SIGNAL(triggered()),this,SLOT(ajoutProblemeSt()));
    connect(add_p_S2,SIGNAL(triggered()),this,SLOT(ajoutProblemeSt()));
    connect(add_p_S3,SIGNAL(triggered()),this,SLOT(ajoutProblemeSt()));
    connect(add_p_S4,SIGNAL(triggered()),this,SLOT(ajoutProblemeSt()));
    connect(add_p_S5,SIGNAL(triggered()),this,SLOT(ajoutProblemeSt()));
    connect(add_p_S6,SIGNAL(triggered()),this,SLOT(ajoutProblemeSt()));
    connect(add_p_S7,SIGNAL(triggered()),this,SLOT(ajoutProblemeSt()));
    connect(add_p_S8,SIGNAL(triggered()),this,SLOT(ajoutProblemeSt()));

    connect (add_p_Ch1,SIGNAL (triggered()),this,SLOT(ajoutProblemeCh ()));
    connect (add_p_Ch2,SIGNAL (triggered()),this,SLOT(ajoutProblemeCh ()));
    connect (add_p_Ch3,SIGNAL (triggered()),this,SLOT(ajoutProblemeCh()));
    connect (add_p_Ch4,SIGNAL (triggered()),this,SLOT(ajoutProblemeCh()));

    connect (add_p_B1,SIGNAL(triggered()),this,SLOT (ajoutProblemeBt ()));
    connect (add_p_B2,SIGNAL(triggered()),this,SLOT (ajoutProblemeBt ()));
    connect (add_p_B3,SIGNAL(triggered()),this,SLOT (ajoutProblemeBt ()));

    //Historique

    connect (h_o_apparts,SIGNAL (triggered()),this,SLOT(historiqueOccupantAp ()));
    connect (h_o_studios,SIGNAL (triggered()),this,SLOT(historiqueOccupantSt ()));
    connect (h_o_chambres,SIGNAL (triggered()),this,SLOT(historiqueOccupantCh ()));
    connect (h_o_boutiques,SIGNAL (triggered()),this,SLOT(historiqueOccupantBt ()));

    connect (p_apparts,SIGNAL (triggered()),this,SLOT(historiqueProblemeAp ()));
    connect (p_studios,SIGNAL (triggered()),this,SLOT(historiqueProblemeSt ()));
    connect (p_chambres,SIGNAL (triggered()),this,SLOT(historiqueProblemeCh ()));
    connect (p_boutiques,SIGNAL (triggered()),this,SLOT(historiqueProblemeBt ()));

    //Détails occupants
    details_o_A1->setObjectName ("A1");
    details_o_A2->setObjectName ("A2");
    details_o_A3->setObjectName ("A3");
    details_o_A4->setObjectName ("A4");

    details_o_S1->setObjectName ("S1");
    details_o_S2->setObjectName ("S2");
    details_o_S3->setObjectName ("S3");
    details_o_S4->setObjectName ("S4");
    details_o_S5->setObjectName ("S5");
    details_o_S6->setObjectName ("S6");
    details_o_S7->setObjectName ("S7");
    details_o_S8->setObjectName ("S8");

    details_o_CH1->setObjectName ("CH1");
    details_o_CH2->setObjectName ("CH2");
    details_o_CH3->setObjectName ("CH3");
    details_o_CH4->setObjectName ("CH4");

    details_o_B1->setObjectName ("B1");
    details_o_B2->setObjectName ("B2");
    details_o_B3->setObjectName ("B3");

    connect(details_o_A1,SIGNAL (triggered()),this,SLOT(detailsOccupantsAp()));
    connect(details_o_A2,SIGNAL (triggered()),this,SLOT(detailsOccupantsAp()));
    connect(details_o_A3,SIGNAL (triggered()),this,SLOT(detailsOccupantsAp()));
    connect(details_o_A4,SIGNAL (triggered()),this,SLOT(detailsOccupantsAp()));

    connect (details_o_S1,SIGNAL (triggered()),this,SLOT (detailsOccupantsSt()));
    connect (details_o_S2,SIGNAL (triggered()),this,SLOT (detailsOccupantsSt()));
    connect (details_o_S3,SIGNAL (triggered()),this,SLOT (detailsOccupantsSt()));
    connect (details_o_S4,SIGNAL (triggered()),this,SLOT (detailsOccupantsSt()));
    connect (details_o_S5,SIGNAL (triggered()),this,SLOT (detailsOccupantsSt()));
    connect (details_o_S6,SIGNAL (triggered()),this,SLOT (detailsOccupantsSt()));
    connect (details_o_S7,SIGNAL (triggered()),this,SLOT (detailsOccupantsSt()));
    connect (details_o_S8,SIGNAL (triggered()),this,SLOT (detailsOccupantsSt()));

    connect(details_o_CH1,SIGNAL (triggered()),this,SLOT(detailsOccupantsCh()));
    connect(details_o_CH2,SIGNAL (triggered()),this,SLOT(detailsOccupantsCh()));
    connect(details_o_CH3,SIGNAL (triggered()),this,SLOT(detailsOccupantsCh()));
    connect(details_o_CH4,SIGNAL (triggered()),this,SLOT(detailsOccupantsCh()));

    connect(details_o_B1,SIGNAL (triggered()),this,SLOT(detailsOccupantsBt()));
    connect(details_o_B2,SIGNAL (triggered()),this,SLOT(detailsOccupantsBt()));
    connect(details_o_B3,SIGNAL (triggered()),this,SLOT(detailsOccupantsBt()));

    //Modifier : syntaxe Qt5
    connect (modifier_personnes,&QAction::triggered,this,&Fenetre::modifierPersonnes);
    connect (modifier_dates,&QAction::triggered,this,&Fenetre::modifierDates);
    /*connect (actualise,&QAction::triggered , this , &Fenetre::actualiser); */
}

//...

void Fenetre::updateModele(QStandardItemModel* model,const QStringList& list ){
    model->clear(); //We make sure that nothing is inside
    foreach (QString item, list) {
        model->appendRow( new QStandardItem(item) );
    }
    QModelIndex vIndex = model->index(5,0);
    QMap<int, QVariant> vMap = model->itemData(vIndex);
    vMap.insert(Qt::BackgroundRole, QVariant(QBrush(Qt::red)));
    vMap.insert(Qt::TextColorRole, QVariant(QBrush(Qt::white)));
    model->setItemData(vIndex, vMap);
}

void Fenetre::chargerVue(){
    //Actualisation des vues

    //Apparts
    //Modifier liste_affiche_Ai
    requetes.liste_affiche_A1 (liste_affiche_A1);
    requetes.liste_affiche_A2 (liste_affiche_A2);
    requetes.liste_affiche_A3 (liste_affiche_A3);
    requetes.liste_affiche_A4 (liste_affiche_A4);
    //...


    vueA1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vueA1->setModel (modele_A1);

    //modele_A2->setStringList (liste_affiche_A2);
    vueA2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vueA2->setModel (modele_A2);

    //modele_A3->setStringList (liste_affiche_A3);
    vueA3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vueA3->setModel (modele_A3);

    //modele_A4->setStringList (liste_affiche_A4);
    vueA4->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vueA4->setModel (modele_A4);

    //Studios
    //Modifier liste_affiche_Si
    requetes.liste_affiche_S1 (liste_affiche_S1);
    requetes.liste_affiche_S2 (liste_affiche_S2);
    requetes.liste_affiche_S3 (liste_affiche_S3);
    requetes.liste_affiche_S4 (liste_affiche_S4);
    requetes.liste_affiche_S5 (liste_affiche_S5);
    requetes.liste_affiche_S6 (liste_affiche_S6);
    requetes.liste_affiche_S7 (liste_affiche_S7);
    requetes.liste_affiche_S8 (liste_affiche_S8);
    //...

    //modele_S1->setStringList (liste_affiche_S1);
    vueS1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vueS1->setModel (modele_S1);

    //modele_S2->setStringList (liste_affiche_S2);
    vueS2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vueS2->setModel (modele_S2);

    //modele_S3->setStringList (liste_affiche_S3);
    vueS3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vueS3->setModel (modele_S3);

    //modele_S4->setStringList (liste_affiche_S4);
    vueS4->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vueS4->setModel (modele_S4);

    //modele_S5->setStringList (liste_affiche_S5);
    vueS5->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vueS5->setModel (modele_S5);

    //modele_S6->setStringList (liste_affiche_S6);
    vueS6->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vueS6->setModel (modele_S6);

    //modele_S7->setStringList (liste_affiche_S7);
    vueS7->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vueS7->setModel (modele_S7);

    //modele_S8->setStringList (liste_affiche_S8);
    vueS8->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vueS8->setModel (modele_S8);

    //Chambres

    //initialisation requetes.liste_affiche_CHi(liste_affiche_Chi);
    requetes.liste_affiche_CH1(liste_affiche_Ch1);
    requetes.liste_affiche_CH2(liste_affiche_Ch2);
    requetes.liste_affiche_CH3(liste_affiche_Ch3);
    requetes.liste_affiche_CH4(liste_affiche_Ch4);

    //Initialisation modèle
    //modele_CH1->setStringList (liste_affiche_Ch1);
    //modele_CH2->setStringList (liste_affiche_Ch2);
    //modele_CH3->setStringList (liste_affiche_Ch3);
    //modele_CH4->setStringList (liste_affiche_Ch4);

    //Not checkable
    vueCH1 ->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vueCH2 ->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vueCH3 ->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vueCH4 ->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //Initialisation Vue
    vueCH1->setModel (modele_CH1);
    vueCH2->setModel (modele_CH2);
    vueCH3->setModel (modele_CH3);
    vueCH4->setModel (modele_CH4);

    //..

    //Boutiques
    requetes.liste_affiche_B1(liste_affiche_B1);
    requetes.liste_affiche_B2(liste_affiche_B2);
    requetes.liste_affiche_B3(liste_affiche_B3);

    //Modèles
    //modele_B1->setStringList (liste_affiche_B1);
    //modele_B2->setStringList (liste_affiche_B2);
    //modele_B3->setStringList (liste_affiche_B3);

    //Not checkable
    vueB1 ->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vueB2 ->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vueB3 ->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //Vues
    vueB1->setModel (modele_B1);
    vueB2->setModel (modele_B2);
    vueB3->setModel (modele_B3);

    //...
    //Add QStandardItem which contains string in liste_affiche...
    updateModele(modele_A1,liste_affiche_A1);
    updateModele(modele_A2,liste_affiche_A2);
    updateModele(modele_A3,liste_affiche_A3);
    updateModele(modele_A4,liste_affiche_A4);

    updateModele(modele_S1,liste_affiche_S1);
    updateModele(modele_S2,liste_affiche_S2);
    updateModele(modele_S3,liste_affiche_S3);
    updateModele(modele_S4,liste_affiche_S4);
    updateModele(modele_S5,liste_affiche_S5);
    updateModele(modele_S6,liste_affiche_S6);
    updateModele(modele_S7,liste_affiche_S7);
    updateModele(modele_S8,liste_affiche_S8);

    updateModele(modele_CH1,liste_affiche_Ch1);
    updateModele(modele_CH2,liste_affiche_Ch2);
    updateModele(modele_CH3,liste_affiche_Ch3);
    updateModele(modele_CH4,liste_affiche_Ch4);

    updateModele(modele_B1,liste_affiche_B1);
    updateModele(modele_B2,liste_affiche_B2);
    updateModele(modele_B3,liste_affiche_B3);
    //Actualisation couleur
    changementColoration ();
}

void Fenetre::grilleApparts(){

    //Good
    requetes.liste_affiche_A1 (liste_affiche_A1);
        //modele_A1->setStringList (liste_affiche_A1);
        vueA1->setModel (modele_A1);

    requetes.liste_affiche_A2 (liste_affiche_A2);
        //modele_A2->setStringList (liste_affiche_A2);
        vueA2->setModel (modele_A2);

    requetes.liste_affiche_A3 (liste_affiche_A3);
        //modele_A3->setStringList (liste_affiche_A3);
        vueA3->setModel (modele_A3);

    requetes.liste_affiche_A4 (liste_affiche_A4);
        //modele_A4->setStringList (liste_affiche_A4);
        vueA4->setModel (modele_A4);


    grilleA->addWidget (titreA);

    grilleA->addWidget (vueA1,2,1);

    grilleA->addWidget (vueA2,2,2);

    grilleA->addWidget (vueA3,3,1);

    grilleA->addWidget (vueA4,3,2);

    w_apparts->setLayout (grilleA);
    indexA = onglets->addTab (w_apparts,tr("Appartements"));

}

void Fenetre::grilleStudios(){
    //Vues ajouter requetes.liste_affiche_Si(liste_affiche_Si);
    requetes.liste_affiche_S1(liste_affiche_S1);
    requetes.liste_affiche_S2(liste_affiche_S2);
    requetes.liste_affiche_S3(liste_affiche_S3);
    requetes.liste_affiche_S4(liste_affiche_S4);
    requetes.liste_affiche_S5(liste_affiche_S5);
    requetes.liste_affiche_S6(liste_affiche_S6);
    requetes.liste_affiche_S7(liste_affiche_S7);
    requetes.liste_affiche_S8(liste_affiche_S8);

    //Studios
    //modele_S1->setStringList (liste_affiche_S1);
    vueS1->setModel (modele_S1);


    //modele_S2->setStringList (liste_affiche_S2);
    vueS2->setModel (modele_S2);


    //modele_S3->setStringList (liste_affiche_S3);
    vueS3->setModel (modele_S3);


    //modele_S4->setStringList (liste_affiche_S4);
    vueS4->setModel (modele_S4);


    //modele_S5->setStringList (liste_affiche_S5);
    vueS5->setModel (modele_S5);


    //modele_S6->setStringList (liste_affiche_S6);
    vueS6->setModel (modele_S6);


    //modele_S7->setStringList (liste_affiche_S7);
    vueS7->setModel (modele_S7);


    //modele_S8->setStringList (liste_affiche_S8);
    vueS8->setModel (modele_S8);

    //Layout
    grilleS->addWidget (titreS);

    grilleS->addWidget (vueS1,2,1);

    grilleS->addWidget (vueS2,2,2);

    grilleS->addWidget (vueS3,3,1);

    grilleS->addWidget (vueS4,3,2);

    grilleS->addWidget (vueS5,4,1);

    grilleS->addWidget (vueS6,4,2);

    grilleS->addWidget (vueS7,5,1);

    grilleS->addWidget (vueS8,5,2);

    //Initialisation onglet
    w_studios->setLayout (grilleS);
    indexS = onglets->addTab (w_studios,tr("Studios"));
}

void Fenetre::grilleChambres(){

    //initialisation requetes.liste_affiche_CHi(liste_affiche_Chi);
    requetes.liste_affiche_CH1(liste_affiche_Ch1);
    requetes.liste_affiche_CH2(liste_affiche_Ch2);
    requetes.liste_affiche_CH3(liste_affiche_Ch3);
    requetes.liste_affiche_CH4(liste_affiche_Ch4);

    //Initialisation modèle
    //modele_CH1->setStringList (liste_affiche_Ch1);
    //modele_CH2->setStringList (liste_affiche_Ch2);
    //modele_CH3->setStringList (liste_affiche_Ch3);
    //modele_CH4->setStringList (liste_affiche_Ch4);

    //Initialisation Vue
    vueCH1->setModel (modele_CH1);
    vueCH2->setModel (modele_CH2);
    vueCH3->setModel (modele_CH3);
    vueCH4->setModel (modele_CH4);

    grilleC->addWidget (titreC);

    grilleC->addWidget (vueCH1,2,1);

    grilleC->addWidget (vueCH2,2,2);

    grilleC->addWidget (vueCH3,3,1);

    grilleC->addWidget (vueCH4,3,2);

    w_chambres->setLayout (grilleC);
    indexC = onglets->addTab (w_chambres,tr("Chambres"));
}

void Fenetre::grilleBoutiques(){

    //requetes.liste_affiche_Bi(liste_affiche_Bi);
    requetes.liste_affiche_B1(liste_affiche_B1);
    requetes.liste_affiche_B2(liste_affiche_B2);
    requetes.liste_affiche_B3(liste_affiche_B3);

    //Modèles
    //modele_B1->setStringList (liste_affiche_B1);
    //modele_B2->setStringList (liste_affiche_B2);
    //modele_B3->setStringList (liste_affiche_B3);

    //Vues
    vueB1->setModel (modele_B1);
    vueB2->setModel (modele_B2);
    vueB3->setModel (modele_B3);

    grilleB->addWidget (titreB);

    grilleB->addWidget (vueB1,2,1);

    grilleB->addWidget (vueB2,2,2);

    grilleB->addWidget (vueB3,3,1);

    w_boutiques->setLayout (grilleB);
    indexB = onglets->addTab (w_boutiques,tr("Boutiques"));
}

void Fenetre::changementColoration(){
    qDebug("Changer de couleur");
    QString style = qApp->styleSheet ();

    if(liste_affiche_A1[1].contains ("Libre"))
        style += "QListView#vueA1{ background: rgb(62,201,36) }";
    else
        style += "QListView#vueA1{ background: rgb(231,122,122) }";

    if(liste_affiche_A2[1].contains ("Libre"))
        style += "QListView#vueA2{ background: rgb(62,201,36) }";
    else
        style += "QListView#vueA2{ background: rgb(231,122,122) }";

    if(liste_affiche_A3[1].contains ("Libre"))
        style += "QListView#vueA3{ background: rgb(62,201,36) }";
    else
        style += "QListView#vueA3{ background: rgb(231,122,122) }";

    if(liste_affiche_A4[1].contains ("Libre"))
        style += "QListView#vueA4{ background: rgb(62,201,36) }";
    else
        style += "QListView#vueA4{ background: rgb(231,122,122) }";


    if(liste_affiche_S1[1].contains ("Libre"))
        style += "QListView#vueS1{ background: rgb(62,201,36) }";
    else
        style += "QListView#vueS1{ background: rgb(231,122,122) }";

    if(liste_affiche_S2[1].contains ("Libre"))
        style += "QListView#vueS2{ background: rgb(62,201,36) }";
    else
        style += "QListView#vueS2{ background: rgb(231,122,122) }";

    if(liste_affiche_S3[1].contains ("Libre"))
        style += "QListView#vueS3{ background: rgb(62,201,36) }";
    else
        style += "QListView#vueS3{ background: rgb(231,122,122) }";

    if(liste_affiche_S4[1].contains ("Libre"))
        style += "QListView#vueS4{ background: rgb(62,201,36) }";
    else
        style += "QListView#vueS4{ background: rgb(231,122,122) }";

    if(liste_affiche_S5[1].contains ("Libre"))
        style += "QListView#vueS5{ background: rgb(62,201,36) }";
    else
        style += "QListView#vueS5{ background: rgb(231,122,122) }";

    if(liste_affiche_S6[1].contains ("Libre"))
        style += "QListView#vueS6{ background: rgb(62,201,36) }";
    else
        style += "QListView#vueS6{ background: rgb(231,122,122) }";

    if(liste_affiche_S7[1].contains ("Libre"))
        style += "QListView#vueS7{ background: rgb(62,201,36) }";
    else
        style += "QListView#vueS7{ background: rgb(231,122,122) }";

    if(liste_affiche_S8[1].contains ("Libre"))
        style += "QListView#vueS8{ background: rgb(62,201,36) }";
    else
        style += "QListView#vueS8{ background: rgb(231,122,122) }";


    if(liste_affiche_Ch1[1].contains ("Libre"))
        style += "QListView#vueCH1{ background: rgb(62,201,36) }";
    else
        style += "QListView#vueCH1{ background: rgb(231,122,122) }";

    if(liste_affiche_Ch2[1].contains ("Libre"))
        style += "QListView#vueCH2{ background: rgb(62,201,36) }";
    else
        style += "QListView#vueCH2{ background: rgb(231,122,122) }";

    if(liste_affiche_Ch3[1].contains ("Libre"))
        style += "QListView#vueCH3{ background: rgb(62,201,36) }";
    else
        style += "QListView#vueCH3{ background: rgb(231,122,122) }";

    if(liste_affiche_Ch4[1].contains ("Libre"))
        style += "QListView#vueCH4{ background: rgb(62,201,36) }";
    else
        style += "QListView#vueCH4{ background: rgb(231,122,122) }";


    if(liste_affiche_B1[1].contains ("Libre"))
        style += "QListView#vueB1{ background: rgb(62,201,36) }";
    else
        style += "QListView#vueB1{ background: rgb(231,122,122) }";

    if(liste_affiche_B2[1].contains ("Libre"))
        style += "QListView#vueB2{ background: rgb(62,201,36) }";
    else
        style += "QListView#vueB2{ background: rgb(231,122,122) }";

    if(liste_affiche_B3[1].contains ("Libre"))
        style += "QListView#vueB3{ background: rgb(62,201,36) }";
    else
        style += "QListView#vueB3{ background: rgb(231,122,122) }";


    setStyleSheet (style);
}
