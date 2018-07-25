#include <iostream>
#include <vector>


std::vector<int> merge0(const std::vector<int>& v1, const std::vector<int>& v2) {
    std::vector<int> res;
    unsigned int i1 = 0;
    unsigned int i2 = 0;
    const unsigned int size1 = v1.size();
    const unsigned int size2 = v2.size();

    while (true) {
        if (i1 < size1) {
            if (i2 < size2) {
                res.push_back(v1[i1] <= v2[i2] ? v1[i1++] : v2[i2++]);
            } else {
                res.push_back(v1[i1++]);
            }
        } else {
            if (i2 < size2) {
                res.push_back(v2[i2++]);
            } else {
                break;
            }
        }
    }

    return res;
}


std::vector<int> merge1(const std::vector<int>& v1, const std::vector<int>& v2) {
    std::vector<int> res;
    unsigned int i1 = 0;
    unsigned int i2 = 0;
    const unsigned int size1 = v1.size();
    const unsigned int size2 = v2.size();

    while (true) {
        if (i1 < size1) {
            if (i2 < size2) {
                res.push_back(v1[i1] <= v2[i2] ? v1[i1++] : v2[i2++]);
            } else {
                do { res.push_back(v2[i2++]); } while (i1 < size1);
                break;
            }
        } else {
            while (i2 < size2) res.push_back(v2[i2++]);
            break;
        }
    }

    return res;
}


std::vector<int> merge2(const std::vector<int>& v1, const std::vector<int>& v2) {
    std::vector<int> res;
    unsigned int i1 = 0;
    unsigned int i2 = 0;
    const unsigned int size1 = v1.size();
    const unsigned int size2 = v2.size();

    while (true) {
        if (i1 >= size1) {
            while (i2 < size2) res.push_back(v2[i2++]);
            break;
        }

        if (i2 >= size2) {
            do { res.push_back(v2[i2++]); } while (i1 < size1);
            break;
        }

        res.push_back( (v1[i1] <= v2[i2]) ? v1[i1++] : v2[i2++] );
    }

    return res;
}


int main() {
    std::vector<int> a {1,2,6,7};
    std::vector<int> b {1,4,5,6,9};

    for (const int el : merge1(a, b)) {
        std::cout << el << " ";
    }
    std::cout << std::endl;

    return 0;
}
