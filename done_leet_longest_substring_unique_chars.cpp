// Given a string, find the length of the longest substring with unique chars.
#include <iostream>
#include <cstring> // memset


int lengthOfLongestSubstring(std::string s) {
    if (s.size() == 0) {
        return 0;
    }

    int begin = 0;
    int end = 0;
    int maxLength = 0;
    bool map[256];
    memset(map, 0, 256 * sizeof(bool));

    while (end < s.size()) {
        const char c = s[end];
        if (map[c]) { // exists in current substring => cut the substring tail
            do {
                map[s[begin]] = false;
                begin++;
            } while (s[begin - 1] != c);
            // If (s[begin - 1] == c) that means that we've just erased
            // the problematic char from the tail => stop erasing.
            map[c] = true; // we've just found it => restore what we've erased
        } else { // a new (unique) char
            map[c] = true;
            // Recalculate the length
            const unsigned int newLength = end - begin;
            if (newLength > maxLength) {
                maxLength = newLength;
            }
        }

        end++;
    }

    return maxLength + 1; // actual length is +1'ed
}

int main() {
    std::cout << lengthOfLongestSubstring("abcd") << std::endl;

    return 0;
}
