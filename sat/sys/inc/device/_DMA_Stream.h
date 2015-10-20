
#ifndef _QB50_SYS_DEVICE_DMA_STREAM_H
#define _QB50_SYS_DEVICE_DMA_STREAM_H

#include "Device.h"

#include <stdint.h>


class Stream : public Device
{

   public:

      Stream( DMA& dma, const uint32_t iobase, const uint32_t IRQn, const char *name, const uint32_t shl );
      ~Stream();

      Stream& init    ( void );
      Stream& enable  ( bool silent = false );
      Stream& disable ( bool silent = false );

      /* start/stop */

      Stream& start   ( void );
      Stream& stop    ( void );
      Stream& wait    ( void );

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

      inline Stream& channel( Channel sel )
      { return _updateCR( sel, 0x07, 25 ); }

      /* burst transfer configuration */

      enum Burst {
         SINGLE   = 0, /*!< single transfer               */
         INCR4    = 1, /*!< incremental burst of  4 beats */
         INCR8    = 2, /*!< incremental burst of  8 beats */
         INCR16   = 3  /*!< incremental burst of 16 beats */
      };

      inline Stream& mBurst( Burst sel )
      { return _updateCR( sel, 0x03, 23 ); }

      /**
       * Sélectionne le mode burst utilisé pour les transferts mémoire/périphérique
       *
       * @param sel Mode à utiliser
       *
       * @return Une self-reference sur cette instance.
       */

      inline Stream& pBurst( Burst sel )
      { return _updateCR( sel, 0x03, 21 ); }

      /* current target */

      enum Target {
         MEM0 = 0, /*!< target memory is memory 0 */
         MEM1 = 1  /*!< target memory is memory 1 */
      };

      inline Stream& target( Target sel )
      { return _updateCR( sel, 0x01, 19 ); }

      /* priority level */

      enum Priority {
         LOW      = 0, /*!< low priority       */
         MEDIUM   = 1, /*!< medium priority    */
         HIGH     = 2, /*!< high priority      */
         VERYHIGH = 3  /*!< very high priority */
      };

      inline Stream& priority( Priority sel )
      { return _updateCR( sel, 0x03, 16 ); }

      /* memory/peripheral data size */

      enum DataSize {
         BYTE     = 0, /*!< byte (8-bit)   */
         SHORT    = 1, /*!< short (16-bit) */
         WORD     = 2  /*!< word (32-bit)  */
      };

      inline Stream& mDataSize( DataSize sel )
      { return _updateCR( sel, 0x03, 13 ); }

      inline Stream& pDataSize( DataSize sel )
      { return _updateCR( sel, 0x03, 11 ); }

      /* address increment mode */

      enum IncMode {
         FIXED    = 0, /*!< address pointer is fixed */
         INCR     = 1  /*!< address pointer is incremented after each transfer */
      };

      inline Stream& mIncMode( IncMode sel )
      { return _updateCR( sel, 0x01, 10 ); }

      inline Stream& pIncMode( IncMode sel )
      { return _updateCR( sel, 0x01, 9 ); }

      /* circular mode */

      enum Mode {
         NORMAL   = 0, /*!< circular mode disabled */
         CIRCULAR = 1  /*!< circular mode enabled  */
      };

      inline Stream& mode( Mode sel )
      { return _updateCR( sel, 0x01, 8 ); }

      /* transfer direction */

      enum Direction {
         P2M      = 0, /*!< peripheral to memory */
         M2P      = 1, /*!< memory to peripheral */
         M2M      = 2  /*!< memory to memory     */
      };

      inline Stream& direction( Direction sel )
      { return _updateCR( sel, 0x03, 6 ); }

      Stream& counter ( uint16_t cnt  );
      Stream& pAddr   ( uint32_t addr );
      Stream& m0Addr  ( uint32_t addr );
      Stream& m1Addr  ( uint32_t addr );

      void isr( void );

   private:

      Stream& _updateCR ( uint32_t val, uint32_t mask, int shift );
      Stream& _clearIFR ( uint32_t flags );

      xSemaphoreHandle _isrTxIE;  /**< ISR semaphore bound to TCIE and TEIE */

      DMA&           _dma;
      const uint32_t _iobase;
      const uint32_t _IRQn;
      const uint32_t _shl;

};


#endif /*_QB50_SYS_DEVICE_DMA_STREAM_H*/

/*EoF*/
