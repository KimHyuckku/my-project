#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int main()
{
    double roof_length, ground_length, angle, ans, r, answer;
    double pi = 3.141592;

    printf("비닐의 길이(m) : ");
    scanf("%lf", &roof_length);
    printf("땅 길이(m) : ");
    scanf("%lf", &ground_length);
    
    for (angle = 0; angle < 90; angle=angle+0.01)
    {
        ans = angle / (sin(angle * pi / 180));

        if (ans < roof_length * 180 / pi / ground_length + 0.01 && ans > roof_length * 180 / pi / ground_length - 0.01)
            break;
    }

    r = ground_length / 2 / (sin(angle * pi / 180));

    answer = r - r * (cos(angle * pi / 180));
    printf("각도 : %.2lf m \n", angle);
    printf("필요한 기둥의 높이 : %.2lf m \n", answer);
}
