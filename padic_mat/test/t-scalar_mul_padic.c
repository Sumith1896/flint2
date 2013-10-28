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

    Copyright (C) 2011 Sebastian Pancratz

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "flint.h"
#include "ulong_extras.h"
#include "long_extras.h"
#include "padic.h"
#include "padic_mat.h"

int
main(void)
{
    int i, result;
    flint_rand_t state;

    fmpz_t p;
    slong N;
    padic_ctx_t ctx;
    slong m, n;

    flint_printf("scalar_mul_padic... ");
    fflush(stdout);

    flint_randinit(state);

    /* Check aliasing */
    for (i = 0; i < 10000; i++)
    {
        padic_mat_t a, b;
        padic_t x;

        fmpz_init_set_ui(p, n_randtest_prime(state, 0));
        N = n_randint(state, PADIC_TEST_PREC_MAX - PADIC_TEST_PREC_MIN) 
            + PADIC_TEST_PREC_MIN;
        padic_ctx_init(ctx, p, FLINT_MAX(0, N-10), FLINT_MAX(0, N+10), PADIC_SERIES);

        m = n_randint(state, 20);
        n = n_randint(state, 20);

        padic_mat_init2(a, m, n, N);
        padic_mat_init2(b, m, n, N);
        padic_init2(x, N);

        padic_mat_randtest(a, state, ctx);
        padic_randtest(x, state, ctx);

        padic_mat_scalar_mul_padic(b, a, x, ctx);
        padic_mat_scalar_mul_padic(a, a, x, ctx);

        result = (padic_mat_equal(a, b) && padic_mat_is_reduced(a, ctx));
        if (!result)
        {
            flint_printf("FAIL:\n\n");
            flint_printf("a = "), padic_mat_print(a, ctx), flint_printf("\n");
            flint_printf("b = "), padic_mat_print(b, ctx), flint_printf("\n");
            flint_printf("x = "), padic_print(x, ctx), flint_printf("\n");
            abort();
        }

        padic_mat_clear(a);
        padic_mat_clear(b);
        padic_clear(x);

        fmpz_clear(p);
        padic_ctx_clear(ctx);
    }

    flint_randclear(state);
    flint_cleanup();
    flint_printf("PASS\n");
    return EXIT_SUCCESS;
}

