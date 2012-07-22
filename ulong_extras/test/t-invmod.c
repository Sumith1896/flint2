/*=============================================================================

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

=============================================================================*/
/******************************************************************************

    Copyright (C) 2009 William Hart

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <mpir.h>
#include "flint.h"
#include "ulong_extras.h"

int main(void)
{
   int i, result;
   flint_rand_t state;
   flint_randinit(state);

   printf("invmod....");
   fflush(stdout);
   
   for (i = 0; i < 10000 * flint_test_multiplier(); i++) 
   {
      mp_limb_t a, b, t, r, binv, ph, pl;
      
      do
      {
         a = n_randtest(state);
         b = n_randtest(state);
      } while ((a >= b) || (n_gcd(b, a) != 1UL));

      t = n_invmod(a, b);
      
      binv = n_preinvert_limb(b);
      umul_ppmm(ph, pl, t, a);
      r = n_ll_mod_preinv(ph, pl, b, binv);

      result = (((r == 0UL) && (b == 1UL)) || (r == 1UL));
      if (!result)
      {
         printf("FAIL:\n");
         printf("a = %lu, b = %lu, r = %ld\n", a, b, r); 
         abort();
      }
   }

   flint_randclear(state);

   printf("PASS\n");
   return 0;
}
