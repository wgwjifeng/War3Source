#ifndef __INCLUDED_SHARED
#define __INCLUDED_SHARED


class Semaphore;

typedef void (*funcpointer)(void); //of void return and no args
///use funcpointer variable= blah
class IMyTimer
{
public:
	virtual void AddTimer(funcpointer func,int milisecondInterval)=0;
};
class War3Ext; //forward declaration...
struct myglobalstruct
{
	War3Ext *pwar3_ext;
	IWebternet *sminterfaceIWebternet; //SMInterface
	ITimerSystem *sminterfacetimersys;
	IWebTransfer *IWebTransferxfer; //single object for transfer handling
	IPluginFunction *helpergetfunc;
	IPlayerManager *playermanager;

	IEventSignal *sem_callfin; //signal when OnTimer sychronous thread finished
	IMutex *docallmutex;
	IPluginContext *plugincontext; //context to call natives
	INativeInterface *nativeinterf;
	INativeInvoker *invoker;

	Semaphore *threadticketrequest;
	Semaphore *threadticket;
	Semaphore *threadticketdone;

	IMyTimer *imytimer;

	int war3revision;
	bool needsWar3Update;
	bool minversionexceeded;
	std::string teststr;

};
extern myglobalstruct *g;

#define SMCALLBEGIN g->threadticketrequest->Signal(); g->threadticket->Wait()
#define SMCALLEND g->threadticketdone->Signal()
//you add the semicolon

//extension helper
enum EXTH {
EXTH_HOSTNAME,
EXTH_W3VERSION_STR,
EXTH_W3VERSION_NUM,
EXTH_GAME ,
EXTH_W3_SH_MODE,
EXTH_IP ,
EXTH_PORT
};




class CWar3DLLInterface
{
public:
    virtual ~CWar3DLLInterface()=0; // <= important!?

	//put all wrapped functions here, and in actual class
    virtual const char *DLLVersion() = 0; //rememer = 0;
	virtual void PassStuff(ISourceMod*,IVEngineServer*,IForwardManager*,IShareSys*,IExtension*,void*,IThreader *,myglobalstruct**)=0;
	virtual void DoStuff()=0;

};

#endif
