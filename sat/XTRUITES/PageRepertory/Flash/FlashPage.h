/**
 *  @file     FlashPage.h
 *  @brief    Page testant les méthode d'écriture, de lecture et d'effacement sur la RAM (En-tête)
 *  @author   Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version  1.0
 *  @date     08/07/2015
 */

#ifndef _QB50_XTRUITES_SECTOR_PAGE_H_
#define _QB50_XTRUITES_SECTOR_PAGE_H_

/// Composition de la RAM: Nombre de block
#define XTRUITES_RAM_TEST_BLOCK_SIZE    64
/// Composition de la RAM: Nombre de secteur par block
#define XTRUITES_RAM_TEST_SECTOR_SIZE   16

/// Couleur du titre des blocks
#define XTRUITES_RAM_TEST_BACKGROUND_BLOCK_TITLE  27
#define XTRUITES_RAM_TEST_FOREGROUND_BLOCK_TITLE  255

/// Couleur des label des blocks
#define XTRUITES_RAM_TEST_BACKGROUND_BLOCK_LABEL  25
#define XTRUITES_RAM_TEST_FOREGROUND_BLOCK_LABEL  255

/// Couleur de titre des secteurs
#define XTRUITES_RAM_TEST_BACKGROUND_SECTOR_TITLE 202
#define XTRUITES_RAM_TEST_FOREGROUND_SECTOR_TITLE 255

/// Couleur des label des secteurs
#define XTRUITES_RAM_TEST_BACKGROUND_SECTOR_LABEL 130
#define XTRUITES_RAM_TEST_FOREGROUND_SECTOR_LABEL 255


#include "../Page.h"
#include "../PageRepertory.h"

namespace qb50
{

  namespace XTRUITES
  {

    /**
    *  @class      FlashPage
    *  @brief      Page testant les méthode d'écriture, de lecture et d'effacement sur la RAM
    */
    class FlashPage : public Page
    {

      public:
        /// @brief      Constructeur: construit 2 RAM watch et les lies à cette page
        /// @param[in]  pageRepertoryVal: Répertoire référençant cette page
        FlashPage();

//        void onLoad( void );
//        void onUpdate( void );
//        void onUnload( void );
//        void onKeyPress( uint8_t key );

    };

  } /* namespace: XTRUITES */

} /* namespace: qb50 */

#endif /* _QB50_XTRUITES_SECTOR_PAGE_H_ */

/*EoF*/
