#include <iostream>
#define NUM 5



int main() {

    int test[NUM] = {80,60,22,50,75};
    int i;

    for (i = 0; i < NUM; i++) {
        
        std::cout << i + 1 << "番目の人の点数は" << test[i] << "です。" << std::endl;
    }

    return 0;
}
