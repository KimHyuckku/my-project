#if 1
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int maze[19][19] = {                                                             // 19 * 19
                        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
                        {1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
                        {1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
                        {1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
                        {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
                        {1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                        {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                        {1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                        {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                        {1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                        {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1},
                        {1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1},
                        {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1},
                        {1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
                        {1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
                        {1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1},
                        {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };

int main()
{
    int cur_x = 1, cur_y = 1;
    int past_x = 1, past_y = 0;
    int i = 0;

    while (1)
    {

        if (cur_x == past_x && cur_y == past_y + 1)      // 현재 방향➡           ⬆⬅⬇➡
        {
            if (maze[cur_x - 1][cur_y] == 0)    // ⬆방향이 뚫려있으면
            {
                past_x = cur_x;
                cur_x = cur_x - 1;
            }
            else if (maze[cur_x][cur_y+1] == 0)      // ➡방향이 뚫려있으면
            {
                past_y = cur_y;
                cur_y = cur_y + 1;
            }
            else if (maze[cur_x + 1][cur_y] == 0)    // ⬇방향이 뚫려있으면
            {
                past_x = cur_x;
                cur_x = cur_x + 1;
            }
            else if (maze[cur_x][cur_y - 1] == 0)      // ⬅방향이 뚫려있으면
            {
                past_y = cur_y;
                cur_y = cur_y - 1;
            }
        }
        else if (cur_x == past_x && cur_y == past_y - 1)      // 현재 방향⬅           ⬆⬅⬇➡
        {
            if (maze[cur_x + 1][cur_y] == 0)    // ⬇방향이 뚫려있으면
            {
                past_x = cur_x;
                cur_x = cur_x + 1;
            }
            else if (maze[cur_x][cur_y - 1] == 0)      // ⬅방향이 뚫려있으면
            {
                past_y = cur_y;
                cur_y = cur_y - 1;
            }
            else if (maze[cur_x - 1][cur_y] == 0)    // ⬆방향이 뚫려있으면
            {
                past_x = cur_x;
                cur_x = cur_x - 1;
            }
            else if (maze[cur_x][cur_y + 1] == 0)      // ➡방향이 뚫려있으면
            {
                past_y = cur_y;
                cur_y = cur_y + 1;
            }
        }
        else if (cur_x == past_x-1 && cur_y == past_y)      // 현재 방향⬆           ⬆⬅⬇➡
        {
            if (maze[cur_x][cur_y-1] == 0)    // ⬅방향이 뚫려있으면
            {
                past_y = cur_y;
                cur_y = cur_y - 1;
            }
            else if (maze[cur_x-1][cur_y] == 0)      // ⬆방향이 뚫려있으면
            {
                past_x = cur_x;
                cur_x = cur_x - 1;
            }
            else if (maze[cur_x][cur_y+1] == 0)    // ➡방향이 뚫려있으면
            {
                past_y = cur_y;
                cur_y = cur_y + 1;
            }
            else if (maze[cur_x+1][cur_y] == 0)      // ⬇방향이 뚫려있으면
            {
                past_x = cur_x;
                cur_x = cur_x + 1;
            }
        }
        else if (cur_x == past_x + 1 && cur_y == past_y)      // 현재 방향⬇          ⬆⬅⬇➡
        {
            if (maze[cur_x][cur_y + 1] == 0)    // ➡방향이 뚫려있으면
            {
                past_y = cur_y;
                cur_y = cur_y + 1;
            }
            else if (maze[cur_x + 1][cur_y] == 0)      // ⬇방향이 뚫려있으면
            {
                past_x = cur_x;
                cur_x = cur_x + 1;
            }
            else if (maze[cur_x][cur_y-1] == 0)    // ⬅방향이 뚫려있으면
            {
                past_y = cur_y;
                cur_y = cur_y - 1;
            }
            else if (maze[cur_x-1][cur_y] == 0)      // ⬆방향이 뚫려있으면
            {
                past_x = cur_x;
                cur_x = cur_x - 1;
            }
        }


        printf("현재위치 [%d, %d] \n", cur_x, cur_y);

        if (cur_x == 1 && cur_y == 0) //< 0 || cur_x > 18 || cur_y < 0 || cur_y > 18)
        {
            break;
        }
    }

    printf("탈출 완료! (%d, %d)", cur_x, cur_y);
}


#endif





#if 0   //left_hand_maze
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int maze[19][19] = {                                                             // 19 * 19
                        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
                        {1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
                        {1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
                        {1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
                        {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
                        {1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                        {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                        {1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                        {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                        {1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                        {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1},
                        {1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1},
                        {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1},
                        {1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
                        {1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
                        {1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1},
                        {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };

int main()
{
    int cur_x=1, cur_y=1;
    int past_x=1, past_y=0;
    int i = 0;


    while (1)
    {
        if (cur_x == past_x - 1 && cur_y == past_y)     // 현재 방향⬆
        {
            if (maze[cur_x][cur_y - 1] == 0)    // ⬅방향이 뚫려있으면// 왼쪽
            {
                past_y = cur_y;
                cur_y = cur_y - 1;
            }
            else if (maze[cur_x - 1][cur_y] == 0)   // ⬆방향이 뚫려있으면// 정면
            {
                past_x = cur_x;
                cur_x = cur_x - 1;
            }
            else if (maze[cur_x][cur_y + 1] == 0)   // ➡방향이 뚫려있으면// 오른쪽
            {
                past_y = cur_y;
                cur_y = cur_y + 1;
            }
            else if (maze[cur_x + 1][cur_y] == 0)            // ⬇ //왔던방향으로 되돌아감
            {
                past_x = past_x - 1;
                cur_x = cur_x + 1;
            }
        }
        else if (cur_x == past_x && cur_y == past_y + 1)     // 현재 방향➡
        {
            if (maze[cur_x-1][cur_y] == 0)    // ⬆방향이 뚫려있으면// 왼쪽
            {
                past_x = cur_x;
                cur_x = cur_x - 1;
            }
            else if (maze[cur_x][cur_y + 1] == 0)   // ➡방향이 뚫려있으면// 정면
            {
                past_y = cur_y;
                cur_y = cur_y + 1;
            }
            else if (maze[cur_x + 1][cur_y] == 0)   // ⬇방향이 뚫려있으면// 오른쪽
            {
                past_x = cur_x;
                cur_x = cur_x + 1;
            }
            else if (maze[cur_x][cur_y - 1] == 0)           // ⬅ //왔던방향으로 되돌아감
            {
                past_y = past_y + 1;
                cur_y = cur_y - 1;
            }
        }
        else if (cur_x == past_x + 1 && cur_y == past_y)     // 현재 방향⬇
        {
            if (maze[cur_x][cur_y + 1] == 0)    // ➡방향이 뚫려있으면// 왼쪽
            {
                past_y = cur_y;
                cur_y = cur_y + 1;
            }
            else if (maze[cur_x + 1][cur_y] == 0)   // ⬇방향이 뚫려있으면// 정면
            {
                past_x = cur_x;
                cur_x = cur_x + 1;
            }
            else if (maze[cur_x][cur_y - 1] == 0)   // ⬅방향이 뚫려있으면// 오른쪽
            {
                past_y = cur_y;
                cur_y = cur_y - 1;
            }
            else if (maze[cur_x - 1][cur_y] == 0)           // ⬆ //왔던방향으로 되돌아감
            {
                past_x = past_x + 1;
                cur_x = cur_x - 1;
            }
        }
        else if (cur_x == past_x && cur_y == past_y - 1)     // 현재 방향⬅
        {
            if (maze[cur_x + 1][cur_y] == 0)    // ⬇방향이 뚫려있으면// 왼쪽
            {
                past_x = cur_x;
                cur_x = cur_x + 1;
            }
            else if (maze[cur_x][cur_y - 1] == 0)   // ⬅방향이 뚫려있으면// 정면
            {
                past_y = cur_y;
                cur_y = cur_y - 1;
            }
            else if (maze[cur_x - 1][cur_y] == 0)   // ⬆방향이 뚫려있으면// 오른쪽
            {
                past_x = cur_x;
                cur_x = cur_x - 1;
            }
            else if (maze[cur_x][cur_y + 1] == 0)           // ➡ //왔던방향으로 되돌아감
            {
                past_y = past_y - 1;
                cur_y = cur_y + 1;
            }
        }

        //if (cur_x == past_x + 1)     // 현재 방향⬇
        //{
        //    if (maze[cur_x][cur_y + 1] == 0)    // ➡방향이 뚫려있으면// 왼쪽
        //    {
        //        past_y = cur_y;
        //        cur_y = cur_y + 1;
        //    }
        //    else if (maze[cur_x + 1][cur_y] == 0)   // ⬇방향이 뚫려있으면// 정면
        //    {
        //        past_x = cur_x;
        //        cur_x = cur_x + 1;
        //    }
        //    else if (maze[cur_x][cur_y-1] == 0)   // ⬅방향이 뚫려있으면// 오른쪽
        //    {
        //        past_y = cur_y;
        //        cur_y = cur_y - 1;
        //    }
        //    else if (maze[cur_x - 1][cur_y] == 0)           // ⬆ //왔던방향으로 되돌아감
        //    {
        //        past_x = cur_x;
        //        cur_x = cur_x - 1;
        //    }
        //}


        i++;
        printf("현재위치 [%d, %d] \n", cur_x, cur_y);

        if (cur_x ==1 && cur_y==0) //< 0 || cur_x > 18 || cur_y < 0 || cur_y > 18)
        {
            break;
        }

    }

    printf("탈출 완료! (%d, %d)", cur_x, cur_y);
}

#endif



#if 0
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main()
{
    int i=0;
    double distance, wheel_diameter, round_size, rest_distance, left_count, left_angle;
    double pi = 3.141592;

    printf("이동할 거리(m) : ");
    scanf("%lf", &distance);
    printf("바퀴의 지름(m) : ");
    scanf("%lf", &wheel_diameter);
    
    while (1)
    {
        round_size = wheel_diameter * pi;

        if (round_size *i < distance)
        {
            i++;
        }

        if (round_size *i > distance)
        {
            i--;
            rest_distance = distance - round_size *i;
            left_count = rest_distance / round_size;
            left_angle = left_count * 360;
            break;
        }        
    }
    printf("회전해야할 바퀴의 회전 수, 각도: %.2lf바퀴 , %.2lf도", i+left_count, i*360+left_angle);

}
#endif