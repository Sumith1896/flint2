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

    Copyright (C) 2011 Andy Novocin
    Copyright (C) 2011 Sebastian Pancratz

******************************************************************************/

/*
    Example program demonstrating the Zassenhaus factoring algorithm.
*/

#include <cstdio>
#include "fmpz_polyxx.h"
#include "fmpz_poly_factorxx.h"

using namespace flint;
using namespace std;

int main()
{
    fmpz_polyxx f;

    if (0)
    {
        // NB: this does not seem to work in the C version

        FILE *polyfile;
        polyfile = fopen("examples/fmpz_poly_hensel_P1", "r");

        if (!polyfile)
        {
            printf("Error.  Could not read P1 from file.\n");
            abort();
        }
        read(polyfile, f);
    }
    else
        f =  "63  1 1 1 -4 -7 -2 -6 -3 -7 18 7 25 -11 95 36 21 16 69 56 35 36 32 33 26 -26 -15 -14 -53 -96 67 72 -67 40 -79 -116 -452 -312 -260 -29 -1393 327 69 -28 -241 230 -54 -309 -125 -74 -450 -69 -3 66 -27 73 68 50 -63 -1290 372 31 -16 2";

    printf("Polynomial:\n");print(f);
    printf("\nFactorisation:\n");print(factor_zassenhaus(f));

    return 0;
}
