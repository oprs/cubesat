
#ifndef _QB50_SYS_DEVICE_DMA_STREAM_H
#define _QB50_SYS_DEVICE_DMA_STREAM_H

#include <FreeRTOS.h>
#include <semphr.h>
#include <stdint.h>

#include "Device.h"


namespace qb50 {

   class DMA;

   class DMAStream : public Device
   {

      public:

         /**
          * Construit un stream DMA
          *
          * @param dma    Référence sur l'instance du DMA parent
          * @param iobase Adresse de base dans la mémoire des I/O pour ce stream
          * @param shl    Offset du permier bit dans le Interrupt Status Register
          *
          * Les streams par défaut de l'ODB sont instanciés au démarrage
          * dans `system/odb.cpp`.  Il est peu probable que la création de
          * nouveaux streams par l'application soit nécessaire.
          */

         DMAStream( DMA& dma, const uint32_t iobase, const uint32_t IRQn, const char *name, const uint32_t shl );
         ~DMAStream();

         DMAStream& init( void );

         /**
          * Active le stream DMA
          *
          * Incrémente le compteur de référence sur le le DMA parent,
          * puis active le stream.
          *
          * @return Une self-reference sur cette instance.
          */

         DMAStream& enable( bool silent = false );

         /**
          * Désactive le stream DMA
          *
          * Désactive le stream, puis décrémente le compteur de référence
          * sur le DMA parent.
          *
          * @return Une self-reference sur cette instance.
          */

         DMAStream& disable( bool silent = false );

      /* channel selection */

         enum Channel {
            CH0      = 0, /*!< channel 0 */
            CH1      = 1, /*!< channel 1 */
            CH2      = 2, /*!< channel 2 */
            CH3      = 3, /*!< channel 3 */
            CH4      = 4, /*!< channel 4 */
            CH5      = 5, /*!< channel 5 */
            CH6      = 6, /*!< channel 6 */
            CH7      = 7  /*!< channel 7 */
         };

      /* start/stop */

         DMAStream& start   ( void );
         DMAStream& stop    ( void );
         DMAStream& wait    ( void );

         /**
          * Sélectionne le channel DMA utilisé par ce stream
          *
          * @param sel Channel à utiliser
          *
          * @return Une self-reference sur cette instance.
          */

         inline DMAStream& channel( Channel sel )
         { return _updateCR( sel, 0x07, 25 ); }

      /* burst transfer configuration */

         enum Burst {
            SINGLE   = 0, /*!< single transfer               */
            INCR4    = 1, /*!< incremental burst of  4 beats */
            INCR8    = 2, /*!< incremental burst of  8 beats */
            INCR16   = 3  /*!< incremental burst of 16 beats */
         };

         /**
          * Sélectionne le mode burst utilisé pour les transferts mémoire/mémoire
          *
          * @param sel Mode à utiliser
          *
          * @return Une self-reference sur cette instance.
          */

         inline DMAStream& mBurst( Burst sel )
         { return _updateCR( sel, 0x03, 23 ); }

         /**
          * Sélectionne le mode burst utilisé pour les transferts mémoire/périphérique
          *
          * @param sel Mode à utiliser
          *
          * @return Une self-reference sur cette instance.
          */

         inline DMAStream& pBurst( Burst sel )
         { return _updateCR( sel, 0x03, 21 ); }

      /* current target */

         enum Target {
            MEM0     = 0, /*!< target memory is memory 0 */
            MEM1     = 1  /*!< target memory is memory 1 */
         };

         /**
          * Sélectionne la zone mémoire cible pour le transfert
          *
          * @param sel Zone mémoire cible
          *
          * @return Une self-reference sur cette instance.
          */

         inline DMAStream& target( Target sel )
         { return _updateCR( sel, 0x01, 19 ); }

      /* priority level */

         enum Priority {
            LOW      = 0, /*!< low priority       */
            MEDIUM   = 1, /*!< medium priority    */
            HIGH     = 2, /*!< high priority      */
            VERYHIGH = 3  /*!< very high priority */
         };

         /**
          * Sélectionne la priorité du transfert
          *
          * @param sel Priorité à utiliser
          *
          * @return Une self-reference sur cette instance.
          */

         inline DMAStream& priority( Priority sel )
         { return _updateCR( sel, 0x03, 16 ); }

      /* memory/peripheral data size */

         enum DataSize {
            BYTE     = 0, /*!< byte (8-bit)   */
            SHORT    = 1, /*!< short (16-bit) */
            WORD     = 2  /*!< word (32-bit)  */
         };

         /**
          * Sélectionne la taille des objets à transférer
          * pour les transferts mémoire/mémoire.
          *
          * @param sel Taille
          *
          * @return Une self-reference sur cette instance.
          */

         inline DMAStream& mDataSize( DataSize sel )
         { return _updateCR( sel, 0x03, 13 ); }

         /**
          * Sélectionne la taille des objets à transférer
          * pour les transferts mémoire/périphérique.
          *
          * @param sel Taille
          *
          * @return Une self-reference sur cette instance.
          */

         inline DMAStream& pDataSize( DataSize sel )
         { return _updateCR( sel, 0x03, 11 ); }

      /* address increment mode */

         enum IncMode {
            FIXED    = 0, /*!< address pointer is fixed */
            INCR     = 1  /*!< address pointer is incremented after each transfer */
         };

         /**
          * Sélectionne le mode d'incrémentation utilisé côté mémoire
          *
          * @param sel Mode d'incrémentation
          *
          * @return Une self-reference sur cette instance.
          */

         inline DMAStream& mIncMode( IncMode sel )
         { return _updateCR( sel, 0x01, 10 ); }

         /**
          * Sélectionne le mode d'incrémentation utilisé côté périphérique
          *
          * @param sel Mode d'incrémentation
          *
          * @return Une self-reference sur cette instance.
          */

         inline DMAStream& pIncMode( IncMode sel )
         { return _updateCR( sel, 0x01, 9 ); }

      /* normal/circular mode */

         enum Mode {
            NORMAL   = 0, /*!< circular mode disabled */
            CIRCULAR = 1  /*!< circular mode enabled  */
         };

         /**
          * Sélectionne le mode de transfert (normal ou circulaire)
          *
          * @param sel Mode
          *
          * @return Une self-reference sur cette instance.
          */

         inline DMAStream& mode( Mode sel )
         { return _updateCR( sel, 0x01, 8 ); }

      /* transfer direction */

         enum Direction {
            P2M      = 0, /*!< peripheral to memory */
            M2P      = 1, /*!< memory to peripheral */
            M2M      = 2  /*!< memory to memory     */
         };

         /**
          * Sélectionne le type de transfert à effectuer:
          *  - périphérique vers mémoire
          *  - mémoire vers périphérique
          *  - mémoire vers mémoire
          *
          * @param sel Mode
          *
          * @return Une self-reference sur cette instance.
          */

         inline DMAStream& direction( Direction sel )
         { return _updateCR( sel, 0x03, 6 ); }

         /**
          * Initialise le compteur d'objets mémoire à copier
          *
          * @param cnt Nombre d'objets mémoire à copier
          *
          * @return Une self-reference sur cette instance.
          */

         DMAStream& counter( uint16_t cnt );

         /**
          * Initialise l'adresse du périphérique impliqué dans le transfert
          *
          * @param addr Adresse dans la mémoire des I/O
          *
          * @return Une self-reference sur cette instance.
          */

         DMAStream& pAddr( uint32_t addr );

         /**
          * Initialise l'adresse mémoire #0
          *
          * @param addr Adresse mémoire #0
          *
          * @return Une self-reference sur cette instance.
          */

         DMAStream& m0Addr( uint32_t addr );

         /**
          * Initialise l'adresse mémoire #1
          *
          * @param addr Adresse mémoire #1
          *
          * @return Une self-reference sur cette instance.
          */

         DMAStream& m1Addr( uint32_t addr );

         /**
          * "Interrupt Service Routine": traitement des interruptions DMA
          *
          * Cette méthode est appelée depuis les "trampolines"
          * `DMA_StreamX_IRQHandler()` (passerelles entre les fonctions
          * C des ISR et les instances de classes C++ correspondantes).
          */

         void isr( void );

      private:

         DMAStream& _updateCR ( uint32_t val, uint32_t mask, int shift );
         DMAStream& _clearIFR ( uint32_t flags );

         xSemaphoreHandle _isrTxIE;  /**< ISR semaphore bound to TCIE and TEIE */

         DMA&           _dma;
         const uint32_t _iobase;
         const uint32_t _IRQn;
         const uint32_t _shl;

   };

   extern qb50::DMAStream DMA1ST0;
   extern qb50::DMAStream DMA1ST1;
   extern qb50::DMAStream DMA1ST2;
   extern qb50::DMAStream DMA1ST3;
   extern qb50::DMAStream DMA1ST4;
   extern qb50::DMAStream DMA1ST5;
   extern qb50::DMAStream DMA1ST6;
   extern qb50::DMAStream DMA1ST7;

   extern qb50::DMAStream DMA2ST0;
   extern qb50::DMAStream DMA2ST1;
   extern qb50::DMAStream DMA2ST2;
   extern qb50::DMAStream DMA2ST3;
   extern qb50::DMAStream DMA2ST4;
   extern qb50::DMAStream DMA2ST5;
   extern qb50::DMAStream DMA2ST6;
   extern qb50::DMAStream DMA2ST7;

} /* qb50 */


extern "C" {
   void DMA1_Stream0_IRQHandler( void );
   void DMA1_Stream1_IRQHandler( void );
   void DMA1_Stream2_IRQHandler( void );
   void DMA1_Stream3_IRQHandler( void );
   void DMA1_Stream4_IRQHandler( void );
   void DMA1_Stream5_IRQHandler( void );
   void DMA1_Stream6_IRQHandler( void );
   void DMA1_Stream7_IRQHandler( void );

   void DMA2_Stream0_IRQHandler( void );
   void DMA2_Stream1_IRQHandler( void );
   void DMA2_Stream2_IRQHandler( void );
   void DMA2_Stream3_IRQHandler( void );
   void DMA2_Stream4_IRQHandler( void );
   void DMA2_Stream5_IRQHandler( void );
   void DMA2_Stream6_IRQHandler( void );
   void DMA2_Stream7_IRQHandler( void );
}


#endif /*_QB50_SYS_DEVICE_DMA_STREAM_H*/

/*EoF*/
