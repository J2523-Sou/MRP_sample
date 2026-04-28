#include <stdio.h>

//関数の定義
void buy(int x) {
	printf("%d万円の車を買いました。¥n", x);
}

int main (void)	{
int NUM;

    printf("一台目の車はいくらですか。¥n");
    scanf("%d", &NUM);

    buy(20);

    printf("2台目の車はいくらですか。¥n");
    scanf("%d", &NUM);
    
    buy(50);

}