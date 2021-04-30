# Problem: disjoint regions
Given an n by m map with r regions on it, build a program that outputs which regions
are disjoint. A region is said to be disjoint if there exists some a and b in r
such that no path in r connect them.

ie.
n = 5, m = 3, r = {1, 2}
map:
```
1 1 - 2 2
2 1 1 1 1
2 1 1 - -
```
2 is the only disjoint regions.

# My solution:
Count the number of regions, for each region pick a random member and count how many
neighbors it has, if that count is less than the total regions, then is must be disjoint.

## Notes:
1. I did not check for every possible error for the sake of the program length.

