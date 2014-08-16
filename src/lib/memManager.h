#ifndef MEMMANAGER_H_
#define MEMMANAGER_H_

#include "timer.h"

typedef unsigned char byte;
typedef enum bool {false, true} bool;

typedef int   (*JittedFunc)(void);
typedef float (*FloatJittedFunc)(void);

struct memManagerVars
{
	byte asmCode [255];
	void* memSpace;
};

extern void dump(void);
extern bool allocMem(void);
extern bool copyExecutableCode(void);
extern bool makeMemoryExecutable(void);
extern bool freeMem(void);
extern inline int executeMem(void);
extern inline float executeMemFloat(void);

//void outputToFile(char* filename);

#endif /* MEMMANAGER_H_ */
