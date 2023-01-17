#ifndef _LOCK_H
#define _LOCK_H

// should include files/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    uint32_t waiting_refcount;
    uint32_t bits;
} lock_t;

// (this may or maynot be used)
#define CAS(AR0, AR2, AR3) ({ \
    bool ret;                           \
    typeof(AR2) ar2 = AR2;     \
    asm volatile (                      \
        "lock cmpxchg %0, %3"           \
        : "+m"(AR0), "+a"(ar2),     \
          "=@ccz" (ret)                 \
        : "r"(AR3)                \
        : "memory"                      \
    );                                  \
    ret;                                \
})

#define LOCKED_READ(VAR) ({    \
    typeof(VAR) ret = 0;       \
    asm volatile (             \
        "lock xadd %1, %0"     \
        : "+r"(ret), "+m"(VAR) \
        :                      \
        : "memory"             \
    );                         \
    ret;                       \
})

#define LOCKED_WRITE(VAR, VAL) ({ \
    typeof(VAR) ret = VAL;        \
    asm volatile (                \
        "lock xchg %1, %0"        \
        : "+r"(ret), "+m"(VAR)    \
        :                         \
        : "memory"                \
    );                            \
    ret;                          \
})

#define LOCKED_INC(VAR) ({ \
    bool ret;              \
    asm volatile (         \
        "lock inc %1"      \
        : "=@ccnz" (ret)   \
        : "m" (VAR)        \
        : "memory"         \
    );                     \
    ret;                   \
})

#define LOCKED_DEC(VAR) ({ \
    bool ret;              \
    asm volatile (         \
        "lock dec %1"      \
        : "=@ccnz" (ret)   \
        : "m" (VAR)        \
        : "memory"         \
    );                     \
    ret;                   \
})

#define SPINLOCK_ACQUIRE(LOCK) ({        \
    bool ret;                            \
    LOCKED_INC((LOCK).waiting_refcount); \
    asm volatile (                       \
        "1: lock bts %0, 0\n\t"          \
        "jnc 1f\n\t"                     \
        "bt %0, 1\n\t"                   \
        "jc 1f\n\t"                      \
        "pause\n\t"                      \
        "jmp 1b\n\t"                     \
        "1:"                             \
        : "+m" ((LOCK).bits),            \
          "=@ccc" (ret)                  \
        :                                \
        : "memory"                       \
    );                                   \
    LOCKED_DEC((LOCK).waiting_refcount); \
    !ret;                                \
})

#define LOCK_ACQUIRE(LOCK) ({        \
    bool ret;                        \
    asm volatile (                   \
        "lock bts %0, 0"             \
        : "+m" ((LOCK).bits),        \
          "=@ccc" (ret)              \
        :                            \
        : "memory"                   \
    );                               \
    !ret;                            \
})

#define LOCK_RELEASE(LOCK) ({       \
    asm volatile (                  \
        "lock btr %0, 0"            \
        : "+m" ((LOCK).bits)        \
        :                           \
        : "memory"                  \
    );                              \
})

// Use this JUST on AQUIRED LOCKS
#define LOCK_DESTROY(LOCK) ({                     \
    asm volatile (                                \
        "lock bts %0, 1"                          \
        : "+m" ((LOCK).bits)                      \
        :                                         \
        : "memory"                                \
    );                                            \
    while (LOCKED_READ((LOCK).waiting_refcount)); \
})


#endif