#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QApplication>
#include <QtWidgets>


class FenetrePrincipale: public QMainWindow
{
    public:
        FenetrePrincipale();

    private:
        QAction *_actionOuvrir;
        QAction *_actionQuitter;

        QTabWidget *_onglets;

        QWidget *_zoneCentrale;

        QWidget *_adc;
        QWidget *_gps;
        QWidget *_attitude;
        QWidget *_fipex;
        QWidget *_housekeeping;
        QWidget *_etatRegistreSU;


        //ADCs
        QCheckBox *_adc1cn0;
        QCheckBox *_adc1cn1;
        QCheckBox *_adc1cn2;
        QCheckBox *_adc1cn3;
        QCheckBox *_adc1cn4;
        QCheckBox *_adc1cn5;
        QCheckBox *_adc1cn6;
        QCheckBox *_adc1cn7;

        QCheckBox *_adc2cn0;
        QCheckBox *_adc2cn1;
        QCheckBox *_adc2cn2;
        QCheckBox *_adc2cn3;
        QCheckBox *_adc2cn4;
        QCheckBox *_adc2cn5;
        QCheckBox *_adc2cn6;
        QCheckBox *_adc2cn7;

        QCheckBox *_adc3cn0;
        QCheckBox *_adc3cn1;
        QCheckBox *_adc3cn2;
        QCheckBox *_adc3cn3;
        QCheckBox *_adc3cn4;
        QCheckBox *_adc3cn5;
        QCheckBox *_adc3cn6;
        QCheckBox *_adc3cn7;

        QCheckBox *_adc4cn0;
        QCheckBox *_adc4cn1;
        QCheckBox *_adc4cn2;
        QCheckBox *_adc4cn3;
        QCheckBox *_adc4cn4;
        QCheckBox *_adc4cn5;
        QCheckBox *_adc4cn6;
        QCheckBox *_adc4cn7;

        //GPS
        QCheckBox *_gpgga;
        QCheckBox *_gpzda;
        QCheckBox *_trameUtileGps;

        //ATTITUDE
        QCheckBox *_quaternion;
        QCheckBox *_cartesien;

        //FIPEX
        QCheckBox *_choix1;
        QCheckBox *_choix2;

        //HOUSEKEEPING
        QCheckBox *_choixA;
        QCheckBox *_choixB;

        //ETAT REGISTRE SU
        QCheckBox *_aDefinir1;
        QCheckBox *_aDefinir2;

};


#endif // FENETREPRINCIPALE_H
