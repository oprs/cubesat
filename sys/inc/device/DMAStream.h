
#ifndef _QB50_SYS_DEVICE_DMA_STREAM_H
#define _QB50_SYS_DEVICE_DMA_STREAM_H

#include "Device.h"

#include <stdint.h>


namespace qb50 {

   class DMA;

   class DMAStream : public Device
   {
      public:

         DMAStream( DMA& dma, const uint32_t iobase, const uint32_t shl );
         ~DMAStream();

         DMAStream& reset   ( void );
         DMAStream& enable  ( void );
         DMAStream& disable ( void );

         /* channel selection */

         enum Chan {
            CH0      = 0, /*!< channel 0 */
            CH1      = 1, /*!< channel 1 */
            CH2      = 2, /*!< channel 2 */
            CH3      = 3, /*!< channel 3 */
            CH4      = 4, /*!< channel 4 */
            CH5      = 2, /*!< channel 5 */
            CH6      = 6, /*!< channel 6 */
            CH7      = 7  /*!< channel 7 */
         };

         inline DMAStream& channel( Chan sel )
         { return _updateCR( sel, 0x07, 25 ); }

         /* burst transfer configuration */

         enum Burst {
            SINGLE   = 0, /*!< single transfer               */
            INCR4    = 1, /*!< incremental burst of  4 beats */
            INCR8    = 2, /*!< incremental burst of  8 beats */
            INCR16   = 3  /*!< incremental burst of 16 beats */
         };

         inline DMAStream& mBurst( Burst sel )
         { return _updateCR( sel, 0x03, 23 ); }

         inline DMAStream& pBurst( Burst sel )
         { return _updateCR( sel, 0x03, 21 ); }

         /* current target */

         enum Target {
            MEM0     = 0, /*!< target memory is memory 0 */
            MEM1     = 1  /*!< target memory is memory 1 */
         };

         inline DMAStream& target( Target sel )
         { return _updateCR( sel, 0x01, 19 ); }

         /* priority level */

         enum Priority {
            LOW      = 0, /*!< low priority       */
            MEDIUM   = 1, /*!< medium priority    */
            HIGH     = 2, /*!< high priority      */
            VERYHIGH = 3  /*!< very high priority */
         };

         inline DMAStream& priority( Priority sel )
         { return _updateCR( sel, 0x03, 16 ); }

         /* memory/peripheral data size */

         enum DataSize {
            BYTE     = 0, /*!< byte (8-bit)   */
            SHORT    = 1, /*!< short (16-bit) */
            WORD     = 2  /*!< word (32-bit)  */
         };

         inline DMAStream& mDataSize( DataSize sel )
         { return _updateCR( sel, 0x03, 13 ); }

         inline DMAStream& pDataSize( DataSize sel )
         { return _updateCR( sel, 0x03, 11 ); }

         /* address increment mode */

         enum IncMode {
            FIXED    = 0, /*!< address pointer is fixed */
            INCR     = 1  /*!< address pointer is incremented after each transfer */
         };

         inline DMAStream& mIncMode( IncMode sel )
         { return _updateCR( sel, 0x01, 10 ); }

         inline DMAStream& pIncMode( IncMode sel )
         { return _updateCR( sel, 0x01, 9 ); }

         /* normal/circular mode */

         enum Mode {
            NORMAL   = 0, /*!< circular mode disabled */
            CIRCULAR = 1  /*!< circular mode enabled  */
         };

         inline DMAStream& mode( Mode sel )
         { return _updateCR( sel, 0x01, 8 ); }

         /* transfer direction */

         enum Direction {
            P2M      = 0, /*!< peripheral to memory */
            M2P      = 1, /*!< memory to peripheral */
            M2M      = 2  /*!< memory to memory     */
         };

         inline DMAStream& direction( Direction sel )
         { return _updateCR( sel, 0x03, 6 ); }

         /* data counter */

         DMAStream& counter   ( uint16_t cnt );

         /* peripheral/memory addresses */

         DMAStream& pAddr     ( uint32_t addr );
         DMAStream& m0Addr    ( uint32_t addr );
         DMAStream& m1Addr    ( uint32_t addr );

         void isr( void );

      private:

         DMAStream& _updateCR ( uint32_t val, uint32_t mask, int shift );

         DMA&           _dma;
         const uint32_t _iobase;
         const uint32_t _shl;
   };

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
