
#include "FenetrePrincipale.h"

FenetrePrincipale::FenetrePrincipale()
{
    QMenu *menuFichier = menuBar()->addMenu( "&File" );

    _actionOuvrir = new QAction( "&Open", this );
    menuFichier->addAction( _actionOuvrir );

    _actionQuitter = new QAction( "E&xit", this );
    menuFichier->addAction( _actionQuitter );

    _zoneCentrale = new QWidget;
    setCentralWidget( _zoneCentrale );

    //creation de QTabWidget
    _onglets = new QTabWidget( _zoneCentrale );
    //_onglets->setGeometry(20, 20, 400, 300);

    //creation des pages onglets
    _adc            = new QWidget;
    _gps            = new QWidget;
    _attitude       = new QWidget;
    _fipex          = new QWidget;
    _housekeeping   = new QWidget;
    _etatRegistreSU = new QWidget;

    //creation de contenu pages widgets

        // page ADCs

            //groupe ADC_1
            _adc1cn0 = new QCheckBox( "ADC_1_CN_0" );
            _adc1cn1 = new QCheckBox( "ADC_1_CN_1" );
            _adc1cn2 = new QCheckBox( "ADC_1_CN_2" );
            _adc1cn3 = new QCheckBox( "ADC_1_CN_3" );
            _adc1cn4 = new QCheckBox( "ADC_1_CN_4" );
            _adc1cn5 = new QCheckBox( "ADC_1_CN_5" );
            _adc1cn6 = new QCheckBox( "ADC_1_CN_6" );
            _adc1cn7 = new QCheckBox( "ADC_1_CN_7" );

            QVBoxLayout *adc1Layout = new QVBoxLayout;
            adc1Layout->addWidget( _adc1cn0 );
            adc1Layout->addWidget( _adc1cn1 );
            adc1Layout->addWidget( _adc1cn2 );
            adc1Layout->addWidget( _adc1cn3 );
            adc1Layout->addWidget( _adc1cn4 );
            adc1Layout->addWidget( _adc1cn5 );
            adc1Layout->addWidget( _adc1cn6 );
            adc1Layout->addWidget( _adc1cn7 );

            QGroupBox *groupAdc1 = new QGroupBox( "ADC_1" );
            groupAdc1->setLayout( adc1Layout );

            //groupe ADC_2
            _adc2cn0 = new QCheckBox( "ADC_2_CN_0" );
            _adc2cn1 = new QCheckBox( "ADC_2_CN_1" );
            _adc2cn2 = new QCheckBox( "ADC_2_CN_2" );
            _adc2cn3 = new QCheckBox( "ADC_2_CN_3" );
            _adc2cn4 = new QCheckBox( "ADC_2_CN_4" );
            _adc2cn5 = new QCheckBox( "ADC_2_CN_5" );
            _adc2cn6 = new QCheckBox( "ADC_2_CN_6" );
            _adc2cn7 = new QCheckBox( "ADC_2_CN_7" );

            QVBoxLayout *adc2Layout = new QVBoxLayout;
            adc2Layout->addWidget( _adc2cn0 );
            adc2Layout->addWidget( _adc2cn1 );
            adc2Layout->addWidget( _adc2cn2 );
            adc2Layout->addWidget( _adc2cn3 );
            adc2Layout->addWidget( _adc2cn4 );
            adc2Layout->addWidget( _adc2cn5 );
            adc2Layout->addWidget( _adc2cn6 );
            adc2Layout->addWidget( _adc2cn7 );

            QGroupBox *groupAdc2 = new QGroupBox( "ADC_2" );
            groupAdc2->setLayout( adc2Layout );

            //groupe ADC_3
            _adc3cn0 = new QCheckBox( "ADC_3_CN_0" );
            _adc3cn1 = new QCheckBox( "ADC_3_CN_1" );
            _adc3cn2 = new QCheckBox( "ADC_3_CN_2" );
            _adc3cn3 = new QCheckBox( "ADC_3_CN_3" );
            _adc3cn4 = new QCheckBox( "ADC_3_CN_4" );
            _adc3cn5 = new QCheckBox( "ADC_3_CN_5" );
            _adc3cn6 = new QCheckBox( "ADC_3_CN_6" );
            _adc3cn7 = new QCheckBox( "ADC_3_CN_7" );

            QVBoxLayout *adc3Layout = new QVBoxLayout;
            adc3Layout->addWidget( _adc3cn0 );
            adc3Layout->addWidget( _adc3cn1 );
            adc3Layout->addWidget( _adc3cn2 );
            adc3Layout->addWidget( _adc3cn3 );
            adc3Layout->addWidget( _adc3cn4 );
            adc3Layout->addWidget( _adc3cn5 );
            adc3Layout->addWidget( _adc3cn6 );
            adc3Layout->addWidget( _adc3cn7 );

            QGroupBox *groupAdc3 = new QGroupBox( "ADC_3" );
            groupAdc3->setLayout( adc3Layout );

            //groupe ADC_4
            _adc4cn0 = new QCheckBox( "ADC_4_CN_0" );
            _adc4cn1 = new QCheckBox( "ADC_4_CN_1" );
            _adc4cn2 = new QCheckBox( "ADC_4_CN_2" );
            _adc4cn3 = new QCheckBox( "ADC_4_CN_3" );
            _adc4cn4 = new QCheckBox( "ADC_4_CN_4" );
            _adc4cn5 = new QCheckBox( "ADC_4_CN_5" );
            _adc4cn6 = new QCheckBox( "ADC_4_CN_6" );
            _adc4cn7 = new QCheckBox( "ADC_4_CN_7" );

            QVBoxLayout *adc4Layout = new QVBoxLayout;
            adc4Layout->addWidget( _adc4cn0 );
            adc4Layout->addWidget( _adc4cn1 );
            adc4Layout->addWidget( _adc4cn2 );
            adc4Layout->addWidget( _adc4cn3 );
            adc4Layout->addWidget( _adc4cn4 );
            adc4Layout->addWidget( _adc4cn5 );
            adc4Layout->addWidget( _adc4cn6 );
            adc4Layout->addWidget( _adc4cn7 );

            QGroupBox *groupAdc4 = new QGroupBox( "ADC_4" );
            groupAdc4->setLayout( adc4Layout );

        //layout Contenant les ADCs
        QVBoxLayout *layoutContenantAdcs = new QVBoxLayout;
        layoutContenantAdcs->addWidget( groupAdc1 );
        layoutContenantAdcs->addWidget( groupAdc2 );
        layoutContenantAdcs->addWidget( groupAdc3 );
        layoutContenantAdcs->addWidget( groupAdc4 );

        _adc->setLayout( layoutContenantAdcs );

        // page GPS

            //groupe format
            _gpgga = new QCheckBox( "GPGGA" );
            _gpzda = new QCheckBox( "GPZDA" );

            QVBoxLayout *formatGpsLayout = new QVBoxLayout;
            formatGpsLayout->addWidget( _gpgga );
            formatGpsLayout->addWidget( _gpzda );

            QGroupBox *groupFormatTrameGps = new QGroupBox( "FORMAT TRAME" );
            groupFormatTrameGps->setLayout( formatGpsLayout );

            _trameUtileGps = new QCheckBox( "TRAME UTILE (GGA + ZDA)" );

        //layout Contenant les trames GPS
        QVBoxLayout *layoutContenantTrameGps = new QVBoxLayout;
        layoutContenantTrameGps->addWidget( groupFormatTrameGps );
        layoutContenantTrameGps->addWidget( _trameUtileGps );

        _gps->setLayout( layoutContenantTrameGps );

        // page ATTITUDE

            //groupe format
            _quaternion = new QCheckBox( "Quaternion" );
            _cartesien  = new QCheckBox( "Cartesien" );

            QVBoxLayout *formatAttitudeLayout = new QVBoxLayout;
            formatAttitudeLayout->addWidget( _quaternion );
            formatAttitudeLayout->addWidget( _cartesien );

            QGroupBox *groupFormatTrameAttitude = new QGroupBox("FORMAT TRAME");
            groupFormatTrameAttitude->setLayout( formatAttitudeLayout );

        //layout Contenant les trames Attitude
        QVBoxLayout *layoutContenantTrameAttitude = new QVBoxLayout;
        layoutContenantTrameAttitude->addWidget( groupFormatTrameAttitude );

        _attitude->setLayout( layoutContenantTrameAttitude );

        // page FIPEX

            //groupe format
            _choix1 = new QCheckBox( "Choix1 ???" );
            _choix2 = new QCheckBox( "Choix2 ???" );

            QVBoxLayout *formatFipexLayout = new QVBoxLayout;
            formatFipexLayout->addWidget( _choix1 );
            formatFipexLayout->addWidget( _choix2 );

            QGroupBox *groupFormatTrameFipex = new QGroupBox("FORMAT TRAME");
            groupFormatTrameFipex->setLayout( formatFipexLayout );

        //layout Contenant les trames Fipex
        QVBoxLayout *layoutContenantTrameFipex = new QVBoxLayout;
        layoutContenantTrameFipex->addWidget( groupFormatTrameFipex );

        _fipex->setLayout( layoutContenantTrameFipex );

        // page HOUSEKEEPING

            //groupe format
            _choixA = new QCheckBox( "ChoixA ???" );
            _choixB = new QCheckBox( "ChoixB ???" );

            QVBoxLayout *formatHousekeepingLayout = new QVBoxLayout;
            formatHousekeepingLayout->addWidget( _choixA );
            formatHousekeepingLayout->addWidget( _choixB );

            QGroupBox *groupFormatTrameHousekeeping = new QGroupBox( "FORMAT TRAME" );
            groupFormatTrameHousekeeping->setLayout( formatHousekeepingLayout );

        //layout Contenant les trames Housekeeping
        QVBoxLayout *layoutContenantTrameHousekeeping = new QVBoxLayout;
        layoutContenantTrameHousekeeping->addWidget( groupFormatTrameHousekeeping );

        _housekeeping->setLayout( layoutContenantTrameHousekeeping );

        // page ETAT REGISTRE SU

            //groupe format
            _aDefinir1 = new QCheckBox( "A Definir1 ???" );
            _aDefinir2 = new QCheckBox( "A Definir2 ???" );

            QVBoxLayout *formatEtatRegistreSuLayout = new QVBoxLayout;
            formatEtatRegistreSuLayout->addWidget( _aDefinir1 );
            formatEtatRegistreSuLayout->addWidget( _aDefinir2 );

            QGroupBox *groupFormatTrameEtatRegistreSu = new QGroupBox("FORMAT TRAME");
            groupFormatTrameEtatRegistreSu->setLayout( formatEtatRegistreSuLayout );

        //layout Contenant les trames Housekeeping
        QVBoxLayout *layoutContenantTrameEtatRegistreSu = new QVBoxLayout;
        layoutContenantTrameEtatRegistreSu->addWidget( groupFormatTrameEtatRegistreSu );

        _etatRegistreSU->setLayout( layoutContenantTrameEtatRegistreSu );


    _onglets->addTab( _adc, "ADCs" );
    _onglets->addTab( _gps, "GPS"  );
    _onglets->addTab( _attitude, "ATTITUDE" );
    _onglets->addTab( _fipex, "FIPEX" );
    _onglets->addTab( _housekeeping, "HOUSEKEEPING" );
    _onglets->addTab( _etatRegistreSU, "ETAT REGISTRE SU" );

}
