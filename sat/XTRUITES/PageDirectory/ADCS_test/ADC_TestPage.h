/**
 *  @file       ADC_TestPage.h
 *  @brief      Page de test pour afficher toutes les valeurs des canaux ADC (MAX111x) (En-tête).
 *  @author     Jérôme skoda <jerome.skoda@hotmail.fr>
 *  @version    1.4
 *  @date       28/05/2015 - 12/06/2015
 */


#ifndef _QB50_XTRUITES_ADCS_ADC_TEST_PAGE_PAGE_H_
#define _QB50_XTRUITES_ADCS_ADC_TEST_PAGE_PAGE_H_


/// Raccourci pour sélectionner le canal courrant
#define   FIELD_CURRENT_ADC     converterADC[XTRUITESADC_TestPage::currentADC_read][channel]


#include "../../textualInterface.h"


namespace qb50
{
    /**
     *  @class      XTRUITESADC_TestPage
     *  @brief      Page de test pour afficher toutes les valeurs des canaux ADC (MAX111x)
     *  @author     Jérôme skoda <jerome.skoda@hotmail.fr>
     *  @version    1.4
     *  @date       28/05/2015 - 12/06/2015
     */
    class XTRUITESADC_TestPage : public XTRUITESPage
    {


        public:

            XTRUITESADC_TestPage(XTRUITES& _XTRUITESInterfaceVal);

            void load(void);
            void unload(void);
            uint8_t  keypress(uint8_t key);

            Thread *updateADCSVal;
            static uint8_t currentADC_read;
    };

    /**
     *  @class      fieldADC
     *  @brief      Liaison entre un canal et une fonction de conversion
     *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
     *  @version    1.4
     *  @date       28/05/2015 - 12/06/2015
     */
    class fieldADC
    {

        public:

            /// Nom du canal
            std::string name;

            /**
             * @brief   Unité
             * @warning '°' utilise deux caractéres lors de l'envoie
             */
            std::string unit;

            /// Fonction de conversion (lambda)
            std::function<float(uint16_t)> converter;

            /**
             *  @brief      Constructeur
             *  @param[in]  nameVal:        Nom associé au canal.
             *  @param[in]  converterVal:   Fonction de conversion.
             *  @param[in]  unitVal:        Unité du canal.
             */
            fieldADC(std::string nameVal, std::function<float(uint16_t)> converterVal, std::string unitVal);

            /**
             *  @brief      Convertie une valeur numerique en valeur réel avec l'unité
             *  @param[in]  value: Valeur numerique
             *  @return     Valeur convertie (chaîne de caractère)
             */
            std::string convertValue(uint16_t value);
    };


    extern void ADCPageThreadUpdate(Thread *self );


} /* namespace: qb50 */


#endif /* _QB50_XTRUITES_ADCS_ADC_TEST_PAGE_PAGE_H_ */


/*EoF*/
