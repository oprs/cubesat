/**
 *  ADC_TestPage.h
 *  28/25/2015
 */


#ifndef _QB50_XTRUITES_ADCS_ADC_TEST_PAGE_PAGE_H_
#define _QB50_XTRUITES_ADCS_ADC_TEST_PAGE_PAGE_H_

#define   FIELD_CURRENT_ADC     converterADC[XTRUITESADC_TestPage::currentADC_read][channel]
#include "../../textualInterface.h"


namespace qb50
{


    class XTRUITESTextBlock;

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


    class fieldADC
    {

        public:

        std::string name;
        std::string unit;
        std::function<float(uint16_t)>   converter;

        fieldADC(std::string nameVal, std::function<float(uint16_t)> converterVal, std::string unitVal);
        std::string convertValue(uint16_t value);
    };


    extern void ADCPageThreadUpdate(Thread *self );


} /* namespace: qb50 */


#endif /* _QB50_XTRUITES_ADCS_ADC_TEST_PAGE_PAGE_H_ */


/*EoF*/
