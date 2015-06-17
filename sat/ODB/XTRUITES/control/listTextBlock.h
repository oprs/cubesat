/**
 *  @file       listTextBlock.h
 *  @brief      Contrôle XTRUITES: listTextBlock (En-tête)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.5
 *  @date       20/05/2015
 */


#ifndef _QB50_LIST_TEXTBLOCK_H_
#define _QB50_LIST_TEXTBLOCK_H_


#include "../textualInterface.h"


namespace qb50
{


    class XTRUITES;

    class XTRUITESInputHandler;

    /// @class      XTRUITESListTextBlockItem
    /// @brief      Element de listTextBlock
    class XTRUITESListTextBlockItem
    {

        public:

            /// @brief  Nom de l'élément <br />
            ///         Il sera affiché après la touche cible de inputHandler de l'élément
            std::string             label;

            /// @brief  Hauteur en nombre d'élément <br/>
            ///         Hauteur de élément= rowSpan * XTRUITESListTextBlock->getHeightItem()
            uint8_t                 rowSpan;

            /// @brief  XTRUITESInputHandler associé à l'élément <br />
            ///         La touche touche cible sera affiché devant le label
            XTRUITESInputHandler*   inputHandler;

            /**
             *  @brief      Constructor
             *  @param[in]  labelVal : Nom de l'élément
             *  @param[in]  inputHandlerVal : XTRUITESInputHandler associé
             *  @param[in]  rowSpanVal : Hauteur en nombre d'élément
             */
            XTRUITESListTextBlockItem(std::string labelVal, XTRUITESInputHandler* inputHandlerVal, uint8_t rowSpanVal=1);

            /// @brief  Getter label
            std::string getLabel();

            /// @brief  Getter rowSpan
            uint8_t getRowSpan();

            /// @brief  Getter inputHandler
            XTRUITESInputHandler* getInputHandler();

            /// @brief  Setter label
            /// @return Reference XTRUITESListTextBlockItem courrante
            XTRUITESListTextBlockItem& setLabel(std::string labelVal);

            /// @brief  Setter rowSpan
            /// @return Reference XTRUITESListTextBlockItem courrante
            XTRUITESListTextBlockItem& setRowSpan(uint8_t rowSpanVal);

            /// @brief  Set inputHandler
            /// @return Reference XTRUITESListTextBlockItem courrante
            XTRUITESListTextBlockItem& setInputHandler(XTRUITESInputHandler* inputHandlerVal);

    };

    /// @class  XTRUITESListTextBlock
    /// @brief  Contrôle XTRUITES: listTextBlock
    class XTRUITESListTextBlock
    {
        public:

            /// @brief  Conteneur de XTRUITESListTextBlockItem
            std::vector<XTRUITESListTextBlockItem*>     items;

            /// @brief  Hauteur de la liste
            uint8_t     height;

            /// @brief  Longueur de la liste
            uint8_t     width;

            /// @brief  Hauteur standard de chaque élément de la liste
            uint8_t     heightItem;

            /// @brief  Longueur de chaque élément de la liste
            uint8_t     widthItem;

            /// @brief  Position en horizontal de 0 (à gauche) à 79 (à droite)
            uint8_t     locationX;

            /// @brief  Position en vertical de 0 (en haut) à 23 (en bas)
            uint8_t     locationY;

            /// @brief  Couleur de l'arrière plan
            uint8_t     background= XTRUITES_LIST_TEXTBLOCK_DEFAULT_BACKGROUND;

            /// @brief  Couleur des caractéres
            uint8_t     foreground= XTRUITES_LIST_TEXTBLOCK_DEFAULT_FOREGROUND;

            /**
             * @brief       Set position horizontal
             * @param[in]   locationXVal: Position horizontal de 0 (à gauche) à 79 (à droite)
             * @return      Référence XTRUITESListTextBlock courrante
             */
            XTRUITESListTextBlock&      setLocationX(uint8_t locationXVal);


            /// @brief  Get position horizontal
            /// @return Position horizontal
            uint8_t                     getLocationX();

            /**
             * @brief       Set position vertical
             * @param[in]   locationYVal: position vertical de 0 (en haut) à 23 (en bas)
             * @return      Référence XTRUITESListTextBlock courrante
             */
            XTRUITESListTextBlock&      setLocationY(uint8_t locationYVal);

            /// @brief  Get position vertical
            /// @return Position vertical
            uint8_t                     getLocationY();

            /**
             * @brief Set hauteur de la liste
             * @param[in] heightVal: Hauteur
             * @return Référence XTRUITESListTextBlock courrante
             */
            XTRUITESListTextBlock&      setHeight(uint8_t heightVal);

            /// @brief  Get hauteur de la liste
            /// @return Hauteur
            uint8_t                     getHeight();

            /**
             * @brief       Set hauteur des éléments
             * @param[in]   widthItemVal: Hauteur
             * @return      Référence XTRUITESListTextBlock courrante
             */
            XTRUITESListTextBlock&      setWidthItem(uint8_t widthItemVal);

            /// @brief   Get hauteur des éléments
            /// @return  hauteur
            uint8_t                     getWidthItem();

            /**
             * @brief       Set longueur de la liste
             * @param[in]   widthVal: Longueur
             * @return      Référence XTRUITESListTextBlock courrante
             */
            XTRUITESListTextBlock&      setWidth(uint8_t widthVal);

            /// @brief  Get longueur de la liste
            /// @return Longueur
            uint8_t                     getWidth();

            /**
             *  @brief      Set hauteur des éléments
             *  @param[in]  heightItemVal: Hauteur
             *  @return     Référence XTRUITESListTextBlock courrante
             */
            XTRUITESListTextBlock&      setHeightItem(uint8_t heightItemVal);

            /**
             * @brief       Get hauteur des éléments
             * @return      Référence XTRUITESListTextBlock courrante
             */
            uint8_t                     getHeightItem();

            /**
             *  @brief      Ajouter un élément à la liste
             *  @param[in]  listTextBlockItem: Elément
             *  @return     Référence XTRUITESListTextBlock courrante
             */
            XTRUITESListTextBlock&      addItem(XTRUITESListTextBlockItem* listTextBlockItem);

            /// @brief  Affiche la liste
            /// @return Référence XTRUITESListTextBlock courrante
            XTRUITESListTextBlock&      display();

            /**
             *  @brief      Scrute chacun des XTRUITESInputHandler puis déchanche ceux correspondant au caractére reçu
             *  @param[in]  key: Caractére reçu
             *  @return     Nombre d'événement déclanché
             */
            uint8_t                     keyPress(uint8_t key);

    };


} /* namespace: qb50 */


#endif /* _QB50_LIST_TEXTBLOCK_H_ */


/*EoF*/
