
#ifndef _QB50_SYSTEM_THREAD_H
#define _QB50_SYSTEM_THREAD_H


namespace qb50 {

	class Thread;
	typedef void (*ThreadWorker)( Thread *self );

	class Thread
	{
		public:

			Thread( const char *name, ThreadWorker worker );
			~Thread();

			void suspend ( void );
			void resume  ( void );

			const char   *name;
			ThreadWorker  worker;
			void         *handle;
			unsigned      priority;
			unsigned      stackDepth;
	};

} /* qb50 */


#endif /*_QB50_SYSTEM_THREAD_H*/

/*EoF*/
