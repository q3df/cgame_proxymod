#ifndef __VM_H__
#define __VM_H__



//magic number is stored in file as 44 14 72 12
#define	VM_MAGIC	0x12721444
#define VM_MAGIC_BIG	0x44147212

#define  MAX_QPATH	64

typedef enum {
	OP_UNDEF,
	OP_NOP,
	OP_BREAK,
	OP_ENTER,
	OP_LEAVE,
	OP_CALL,
	OP_PUSH,
	OP_POP,
	OP_CONST,
	OP_LOCAL,
	OP_JUMP,
	OP_EQ,
	OP_NE,
	OP_LTI,
	OP_LEI,
	OP_GTI,
	OP_GEI,
	OP_LTU,
	OP_LEU,
	OP_GTU,
	OP_GEU,
	OP_EQF,
	OP_NEF,
	OP_LTF,
	OP_LEF,
	OP_GTF,
	OP_GEF,
	OP_LOAD1,
	OP_LOAD2,
	OP_LOAD4,
	OP_STORE1,
	OP_STORE2,
	OP_STORE4,
	OP_ARG,
	OP_BLOCK_COPY,
	OP_SEX8,
	OP_SEX16,
	OP_NEGI,
	OP_ADD,
	OP_SUB,
	OP_DIVI,
	OP_DIVU,
	OP_MODI,
	OP_MODU,
	OP_MULI,
	OP_MULU,
	OP_BAND,
	OP_BOR,
	OP_BXOR,
	OP_BCOM,
	OP_LSH,
	OP_RSHI,
	OP_RSHU,
	OP_NEGF,
	OP_ADDF,
	OP_SUBF,
	OP_DIVF,
	OP_MULF,
	OP_CVIF,
	OP_CVFI
} vmOps_t;














#endif //__VM_H__
typedef struct {
  int   vmMagic;
  int   instructionCount;
  int   codeOffset;
  int   codeLength;
  int   dataOffset;
  int   dataLength;
  int   litLength;      /* ( dataLength - litLength ) should be byteswapped on load */
  int   bssLength;      /* zero filled memory appended to datalength */
} vmHeader_t;



typedef struct vm_s {
	/* public interface */
	char name[MAX_QPATH];

	/* segments */
	int* codeSegment; /* code segment, each instruction is 2 ints */
	byte* dataSegment;  /* data segment, partially filled on load */
	byte* stackSegment; /* stack segment */

	/* status*/
	int codeSegmentLen; /* size of codeSegment */
	int dataSegmentLen; /* size of dataSegment */
	int dataSegmentMask;

	/* registers */
	int* opPointer;
	int* opStack;
	int opBase;

	/* memory */
	int memorySize;
	byte* memory;

	qboolean swapped; /* was this file byteswapped? (is the server big-endian) */
	int fileSize;   /* .qvm file size (for qmmvm_status) */
	vmHeader_t header;  /* store header information (useful later on) */

	/* non-API function hooking */
	int hook_realfunc;  /* address for a VM function to call after a hook completes (0 = don't call) */
} vm_t;



extern vm_t g_VM;
extern char vmpath[MAX_QPATH];
extern char vmbase[16];
extern int stacksize;
extern int vm_stacksize;


int QDECL VM_Exec(vm_t *vm, int command, int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10, int arg11);
qboolean VM_Create(vm_t* vm, const char* path, byte* oldmem);
void VM_Destroy(vm_t *vm);
qboolean VM_Restart(vm_t *vm, qboolean savemem);
void *VM_ExplicitArgPtr( vm_t *vm, int intValue );
int QDECL VM_SysCalls(byte *memoryBase, int cmd, int *args);
int int_byteswap(int i);
short short_byteswap(short s);
