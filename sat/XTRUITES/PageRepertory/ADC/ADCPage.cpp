/**
 *  @file
 *  @brief
 *  @author
 *  @version
 *  @date
 */

#include "ADCPage.h"
#include "ConvFormula.h"
#include "TestADCChip.h"
#include "TestADCChannel.h"
#include "ADCWatch.h"
#include "config.h"
#include <vector>


using namespace std;
using namespace qb50::XTRUITES;

ADCPage::ADCPage()
{

}

void ADCPage::onLoad( void )
{

  test_ADC_Config= new Test_ADC_Config();

  for(unsigned char i=0; i<XTRUITES_TEST_ADC_NUMBER; i++)
  {
    ADCWatchComponent[i]= new ADCWatch(test_ADC_Config->ADC[i]);
    addComponent(ADCWatchComponent[i]);
  }

  ADCWatchComponent[0]->setLocation(Point( 1, 4));
  ADCWatchComponent[1]->setLocation(Point(67, 4));
  ADCWatchComponent[2]->setLocation(Point( 1,20));
  ADCWatchComponent[3]->setLocation(Point(67,20));

  getCollection().loadAllComponents();
}


void ADCPage::onUnload( void )
{
  getCollection().unloadAllComponents();

  for(unsigned char i=0; i<XTRUITES_TEST_ADC_NUMBER; i++)
  {
    getCollection().eraseComponent( ADCWatchComponent[i] );
    delete ADCWatchComponent[i];
  }

  delete test_ADC_Config;
}




/*EoF*/
