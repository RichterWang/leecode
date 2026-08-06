// LeetCode 3345. Smallest Divisible Digit Product I

class Solution {
public:
    int smallestNumber(int n, int t) {
        const int index_max = 1000;

        for (int i = n; i < index_max; ++i) {
            int product;

            if (i < 10) {
                product = i;
            } else if (i < 100) {
                product = (i % 10) * (i / 10);
            } else {
                product = (i % 10)
                        * ((i / 10) % 10)
                        * ((i / 100) % 10);
            }

            if (product % t == 0) {
                return i;
            }
        }

        return -1;
    }
};
