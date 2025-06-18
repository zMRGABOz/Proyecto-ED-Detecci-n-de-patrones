#include "boyer_moore.h"

int main() {
    string txt = "ABAAABCDABAA";
    string pat = "ABAA";
    search(txt, pat);
    return 0;
}