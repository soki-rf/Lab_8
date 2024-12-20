#include <iostream>
#include <cstring>


char* CopyString(const char* str) {
    int cnt = 0;
    while (str[cnt] != '\0') {
        ++cnt;
    }

    char* buf = new char[cnt + 1];

    std::memcpy(buf, str, cnt);

    buf[cnt] = '\0';

    return buf;
}


char* ConcatinateStrings(const char* a, const char* b) {
    int l_a = 0, l_b = 0;

    while (a[l_a] != '\0') {
        ++l_a;
    }

    while (b[l_b] != '\0') {
        ++l_b;
    }

    char* result = new char[l_a + l_b + 1];
    
    std::memcpy(result, a, l_a);
    std::memcpy(result + l_a, b, l_b);

    result[l_a + l_b] = '\0';

    return result;
}


int main() {
    const char* str1 = "Biba";
    const char* str2 = "Boba";

    
    char* copy = CopyString(str1);
    std::cout << "Copied string: " << copy << std::endl;
    delete[] copy;
    
    char* concatenated = ConcatinateStrings(str1, str2);
    std::cout << "Concatenated string: " << concatenated << std::endl;
    delete[] concatenated;

    return 0;
}
