CREATE TABLE Appartements(numero CHAR(2) NOT NULL,etat CHAR(1) NOT NULL CHECK (etat='L' OR etat='O'),prix INTEGER NOT NULL,PRIMARY KEY(numero));

CREATE TABLE Boutiques(numero CHAR(2) NOT NULL,etat CHAR(1) NOT NULL CHECK (etat IN ('L','O')),prix INTEGER NOT NULL,PRIMARY KEY(numero));

CREATE TABLE Chambres (numero CHAR(3) NOT NULL,etat CHAR(1) NOT NULL CHECK (etat IN ('L','O')),prix INTEGER NOT NULL,PRIMARY KEY(numero));

CREATE TABLE Studios(numero CHAR(2) NOT NULL,etat CHAR(1) NOT NULL CHECK (etat IN ('L','O')),prix INTEGER NOT NULL,PRIMARY KEY(numero));

CREATE TABLE Observations ( idOP INTEGER,observation TEXT, date DATE,FOREIGN KEY(idOP) REFERENCES Personnes ON DELETE CASCADE);

CREATE TABLE Occupants( idPO INTEGER NOT NULL,date_entree DATE NOT NULL,date_sortie DATE NULL, date_fin_sejour DATE,date_butoire DATE,FOREIGN KEY(idPO) REFERENCES Personnes ON DELETE CASCADE ON UPDATE CASCADE,PRIMARY KEY(idPO));

CREATE TABLE OccupeAP(idAO INTEGER,numeroAO CHAR(2),FOREIGN KEY(idAO) REFERENCES Occupants(idPO) ON DELETE CASCADE,FOREIGN KEY(numeroAO) REFERENCES Appartements(numero),PRIMARY KEY(idAO,numeroAO) );

CREATE TABLE OccupeBt(idBtO INTEGER,numeroBtO CHAR(2),FOREIGN KEY(idBtO) REFERENCES Occupants(idPO) ON DELETE CASCADE,FOREIGN KEY(numeroBtO) REFERENCES Boutiques(numero),PRIMARY KEY(idBtO,numeroBtO) );

CREATE TABLE OccupeCh(idChO INTEGER,numeroChO CHAR(2),FOREIGN KEY(idChO) REFERENCES Occupants(idPO) ON DELETE CASCADE,FOREIGN KEY(numeroChO) REFERENCES Chambres(numero),PRIMARY KEY(idChO,numeroChO) );

CREATE TABLE OccupeSt(idStO INTEGER,numeroStO CHAR(2),FOREIGN KEY(idStO) REFERENCES Occupants(idPO) ON DELETE CASCADE,FOREIGN KEY(numeroStO) REFERENCES Studios(numero),PRIMARY KEY(idStO,numeroStO) );

CREATE TABLE Personnes (idP INTEGER PRIMARY KEY,cni VARCHAR(30) NOT NULL UNIQUE,nom VARCHAR(30) NOT NULL,prenom VARCHAR(30) NULL,age INTEGER CHECK(age >= 20 AND age <= 100),profession VARCHAR(30),contact VARCHAR(70), pays VARCHAR(30), ville VARCHAR(30), adresse VARCHAR(30),email VARCHAR(30), cni_le DATE, cni_a VARCHAR(20),commentaires VARCHAR(50));

CREATE TABLE ProblemeAp ( numeroA CHAR(2) NOT NULL,probleme TEXT, date DATE, FOREIGN KEY(numeroA) REFERENCES Appartements );

CREATE TABLE ProblemeBt ( numeroB CHAR(2) NOT NULL,probleme TEXT, date DATE, FOREIGN KEY(numeroB) REFERENCES Boutiques );

CREATE TABLE ProblemeCh ( numeroC CHAR(3) NOT NULL,probleme TEXT, date DATE, FOREIGN KEY(numeroC) REFERENCES Chambres );

CREATE TABLE ProblemeSt ( numeroS CHAR(2) NOT NULL,probleme TEXT, date DATE, FOREIGN KEY(numeroS) REFERENCES Studios );

INSERT INTO "Boutiques" VALUES('B1','L',30000);
INSERT INTO "Boutiques" VALUES('B2','L',30000);
INSERT INTO "Boutiques" VALUES('B3','L',30000);

INSERT INTO "Chambres" VALUES('CH1','L',15000);
INSERT INTO "Chambres" VALUES('CH2','L',15000);
INSERT INTO "Chambres" VALUES('CH3','L',15000);
INSERT INTO "Chambres" VALUES('CH4','L',15000);

INSERT INTO "Studios" VALUES('S1','L',30000);
INSERT INTO "Studios" VALUES('S2','L',30000);
INSERT INTO "Studios" VALUES('S3','L',30000);
INSERT INTO "Studios" VALUES('S4','L',30000);
INSERT INTO "Studios" VALUES('S5','L',30000);
INSERT INTO "Studios" VALUES('S6','L',30000);
INSERT INTO "Studios" VALUES('S7','L',30000);
INSERT INTO "Studios" VALUES('S8','L',30000);

INSERT INTO "Appartements" VALUES('A1','L',50000);
INSERT INTO "Appartements" VALUES('A2','L',50000);
INSERT INTO "Appartements" VALUES('A3','L',50000);
INSERT INTO "Appartements" VALUES('A4','L',50000);                                                                                                                                                                                   