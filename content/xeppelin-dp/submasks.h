/**
 * Author: kik0s
 * Description: $O(3^n)$
 */
#pragma once

for (int mask = 0; mask < (1 << n); mask++)
	for (int sub = mask; sub > 0; sub = (sub - 1) & mask)
		// do something, if needed add 0-mask
