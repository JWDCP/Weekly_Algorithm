/*
어렵게 생각하면 어렵지만 쉽게 생각하면 쉬운 문제다.

문제에서 두 팀으로 사람을 나누는 작업에서 첫 번째 조합, 그리고 나뉜 팀에서 능력치를 더하기 위해 두 명씩 나누는 두 번째 조합, 
이렇게 두 번의 dfs를 돌려야 할 것으로 생각했다. 그렇게 된다면 스택의 크기가 너무 커진다.

하지만 다행히도 이번 문제는 팀을 나누는 것만 dfs로 해주고 능력치 합은 완전탐색으로 해주어도 시간 초과가 나지 않는다.

필자는 팀을 나누는 용도로 joined라는 배열을 만들고 true라면 A팀, false라면 B팀에 분류하는 식으로 구분하였다. 
따라서 joined의 n개의 원소 중 n / 2개를 선별하였다면 완전탐색을 통해 같은 팀원일 때의 능력치만 합산해주는 식으로 처리하여 정답을 받았다.
*/

#include <iostream>
#include <math.h>
int n;
int ability[20][20];

bool joined[20];
int min = 1000000000;

void member_list_up(int memberNum, int pos){
    if(memberNum == n / 2){
        int start = 0, link = 0;
        for(int mem1 = 0; mem1 < n; mem1++){
            for(int mem2 = 0; mem2 < n; mem2++){
                if(joined[mem1] && joined[mem2]){
                    start += ability[mem1][mem2];
                }
                if(!joined[mem1] && !joined[mem2]){
                    link += ability[mem1][mem2];
                }
            }
        }
        int result = std::abs(start - link);
        if(result < min){
            min = result;
        }
    }
    else{
        for(int count = pos; count < n; count++){
            joined[count] = true;

            member_list_up(memberNum + 1, count + 1);

            joined[count] = false;
        }
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> n;

    for(int row = 0; row < n; row++){
        for(int col = 0; col < n; col++){
            std::cin >> ability[row][col];
        }
    }

    member_list_up(0, 0);
    std::cout << min;
}