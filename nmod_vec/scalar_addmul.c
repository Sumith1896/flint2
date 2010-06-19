/*============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

===============================================================================*/
/****************************************************************************

   Copyright (C) 2010 William Hart
   
*****************************************************************************/

#include <mpir.h>
#include <stdlib.h>
#include "flint.h"
#include "ulong_extras.h"
#include "nmod_vec.h"

void _nmod_vec_scalar_addmul(mp_ptr res, mp_srcptr vec, 
				                  long len, nmod_t mod, mp_limb_t c)
{
   long i;
   
   if (mod.norm >= FLINT_BITS/2) // addmul will fit in a limb
   {
      mpn_addmul_1(res, vec, len, c);
	  _nmod_vec_reduce(res, res, len, mod);
   } else // products may take two limbs
   {
      mp_limb_t hi, lo;
	  
	  for (i = 0; i < len; i++)
	     NMOD_ADDMUL(res[i], vec[i], c, mod); // hi already reduced mod n
   }
}
