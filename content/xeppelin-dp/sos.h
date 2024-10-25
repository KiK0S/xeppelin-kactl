/**
 * Author: kik0s
 * Description: sum over subsets, $O(2^n \cdot n)$
 */

int a[1 << MAXLOG];
ll sos() { // takes 1 << n elements
    for (int i = 0; i < n; i++)
        for (int mask = 0; mask < (1 << n); mask++)
            if (mask & (1 << i))
                a[mask] += a[mask ^ (1 << i)];
}

