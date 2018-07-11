#ifndef _SKEIN_H_
#define _SKEIN_H_     1
#include "skein_port.h"                      /* get platform-specific definitions */

typedef enum
{
  SKEIN_SUCCESS         =      0,          /* return codes from Skein calls */
  SKEIN_FAIL            =      1,
  SKEIN_BAD_HASHLEN     =      2
}
HashReturn;

typedef size_t   DataLength;                /* bit count  type */
typedef u08b_t   BitSequence;               /* bit stream type */

/* "all-in-one" call */
HashReturn skein_hash(int hashbitlen,   const BitSequence *data, 
                      DataLength databitlen,  BitSequence *hashval);

#endif  /* ifndef _SKEIN_H_ */
