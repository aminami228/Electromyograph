//======================================================
// Star Finder
//======================================================
// File Name : syscalls.c
// Function  : Low level System Calls
//------------------------------------------------------
// Rev.01 2008.03.24 Takanaga Yamazaki
//------------------------------------------------------
// (C) Copyright 2008 Takanaga Yamazaki
//======================================================
// ---- License Information ----------------------------
// Anyone can FREELY use this code fully or partially
// under conditions shown below.
// 1. You should use this code under the GNU GPL.
// 2. You should remain this header text in your codes
//   including Copyright credit and License Information.
// 3. Your codes should inherit this license information.
//======================================================
// ---- Patent Notice ----------------------------------
// I have not cared whether this system (hw + sw) causes 
// infringement on the patent, copyright, trademark,
// or trade secret rights of others. You have all 
// responsibilities for determining if your designs
// and products infringe on the intellectual property
// rights of others, when you use technical information
// included in this system for your business.
//======================================================
// ---- Disclaimers ------------------------------------
// The function and reliability of this system are not 
// guaranteed. They may cause any damages to loss of
// properties, data, money, profits, life, or business.
// By adopting this sytem even partially, you assume
// all responsibility for its use.
//======================================================

#include <stdlib.h>
#include <unistd.h>

//========================================================
// Memory Management
//--------------------------------------------------------
// Belows are prepared to give user managable malloc().
//
// << Important Notice >>
// You can use following memory management utilities
// in your program.
//
//    malloc(), free(), realloc(), calloc()
//
// To enable this, you should add following options
// in linker command to make links to __wrap_*****()
// functions instead of default routines.
//
// -Wl,--wrap,malloc -Wl,--wrap,free
// -Wl,--wrap,realloc -Wl,--wrap,calloc
//========================================================

//-----------------------
// Heap Memory Definition
//-----------------------
#define HEAP_SIZE (4096) // total heap size is 4096KB

//--------------------------------
// "NULL" is defined in <stdlib.h>
//--------------------------------
#ifndef NULL
#define NULL 0
#endif

//------------------------------
// Memory Pool Related Resources
//------------------------------
#define NALLOC 32

typedef long Align;
union header
{
    struct
    {
        union header *ptr;
        unsigned size;
    } s;
    Align x;
};
typedef union header Header;

static Header base;
static Header *freep = NULL;

//--------------------
// Function Definition
//--------------------
void *i_malloc(unsigned);
void i_free(void*);
char *i_sbrk(unsigned int);

//==========================
// Allocate Memory from Heap
//==========================
void *__wrap_malloc(unsigned nbytes)
{
    void *ptr;
    ptr = (void *) i_malloc(nbytes);
    return ptr;
}

//=======================
// Release Memory to Heap
//=======================
void __wrap_free(void *ap)
{
    i_free(ap);
}

//========================================
// Allocate Memory from Heap, and Clear it
//========================================
void *__wrap_calloc(unsigned nmemb, unsigned nbytes)
{
    char *newPtr;
    char *clrPtr;
    int i;

    newPtr = __wrap_malloc(nmemb * nbytes);
    if (newPtr == NULL) return newPtr;

    clrPtr = newPtr;
    for (i = 0; i < (nmemb * nbytes); i++) *clrPtr++ = 0;

    return newPtr;
}

//============================
// Reallocate Memory from Heap
//============================
void *__wrap_realloc(void *p, unsigned nbytes)
{
    Header *ph;
    unsigned long copySize;
    char *oldPtr;
    char *newPtr;
    char *pReturn;
    int i;

    if (nbytes == 0)
    {
        i_free(p);
        return NULL;
    }

    if (p == NULL)
    {
        pReturn = __wrap_malloc(nbytes);
        return pReturn;
    }
    oldPtr = (char*) p;

    newPtr = __wrap_malloc(nbytes);
    if (newPtr == NULL) return NULL;
    pReturn = newPtr;

    ph = (Header*) p - 1;
    copySize = (ph->s.size - 1) * sizeof(Header);

    if (copySize > nbytes) copySize = nbytes;
    
    for (i = 0; i < copySize; i++) *newPtr++ = *oldPtr++;

    i_free(p);
    return pReturn;
}

//---------------------------------
// Internal Routine for Memory Heap
//---------------------------------
//
// core routine of memory allocation
//
void *i_malloc(unsigned nbytes)
{
    Header *p, *prevp;
    Header *morecore(unsigned);
    unsigned nunits;

    nunits = (nbytes + sizeof(Header) -1) / sizeof(Header) + 1;
    if ((prevp = freep) == NULL)
    {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr)
    {
        if (p->s.size >= nunits)
        {
            if (p->s.size == nunits)
                prevp->s.ptr = p->s.ptr;
            else
            {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p + 1);
        }
        if (p == freep)
            if ((p = morecore(nunits)) == NULL)
                return NULL;
    }
}
//
// request memory
//
Header *morecore(unsigned nu)
{
    char *cp;
    Header *up;

    if (nu < NALLOC)
        nu = NALLOC;
    cp = i_sbrk(nu * sizeof(Header));
    if (cp == NULL) return NULL;
    up = (Header *) cp;
    up->s.size = nu;
    i_free((void *)(up + 1));
    return freep;
}
//
// give requested memory
//
char *i_sbrk(unsigned int size)
{
	static char buf[HEAP_SIZE]; // keep RAM area as heap zone
	static unsigned int i = 0;
	char *ret;

        if (i + size > HEAP_SIZE) return NULL;
        ret = buf+i;
        i += size;
        return ret;
}
//
// core routine of free operation
//
void i_free(void *ap)
{
    Header *bp, *p;

    bp = (Header *) ap -1;
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr)) break;

    if (bp + bp->s.size == p->s.ptr)
    {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    }
    else
        bp->s.ptr = p->s.ptr;

    if (p + p->s.size == bp)
    {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    }
    else
        p->s.ptr = bp;

    freep = p;
}

//========================================================
// Low Level I/O
//--------------------------------------------------------
// Belows are prepared not to cause link error.
// Rewrite them if you need appropriate functionality,
//========================================================

//----------------
// isatty
//----------------
int isatty(int fd)
{
  return (1);
}

//----------------
// _sbrk
//----------------
void* _sbrk(unsigned int increment)
{
    return i_sbrk(increment);
}

//----------------
// read
//----------------
int _read(int fd, void *buffer, unsigned int count)
{
    return 0;
}

//----------------
// _write
//----------------
int _write(int fd, const void *buffer, unsigned int count)
{
    return 0;
}

//----------------
// _close
//----------------
int _close(int fd )
{
    return 0;
}

//----------------
// _fstat
//----------------
int _fstat( int fd, void* buffer)
{
    return 0;
}

//----------------
// _lseek
//----------------
long _lseek(int fd, long offset, int origin)
{
    return 0;
}

//----------------
// _exit
//----------------
void _exit(int status)
{
    while(1);
}

//----------------
// _getpid
//----------------
int _getpid(void)
{
    return 0;
}

//----------------
// _kill
//----------------
int _kill(int pid, int sig)
{
    return 0;
}

//======================================================
// End of Program
//======================================================
