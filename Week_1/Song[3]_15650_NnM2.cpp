
/*
· 백트래킹(Back-tracking)
    백트래킹은 쉽게 말하자면 "조건이 포함된 dfs"이다. 엄밀히 보자면 bfs나 dfs 탐색 중 특정 조건을 만족할 때 현재 탐색을 중단하고 
    다음 탐색을 이어가는 것인데, bfs에 백트래킹을 적용하는 것은 성능 향상에 크게 도움이 되지 않기 때문에 
    일반적으로 dfs를 사용할 때 같이 사용하는 기법이라고 보면 된다.

· 메인 아이디어
    이번 문제의 핵심은 '중복 없이 고른 순열'이라는 것이다. 즉, {1, 2}와 {2, 1}은 순열을 이루는 숫자가 순서에 상관 없이 중복되므로 같은 순열이다. 
    이러한 순열의 특징은 간단하다. 앞의 숫자가 뒤의 숫자보다 반드시 작다.

    즉, 뒤에 위치할 숫자가 앞에 위치할 숫자보다 클 때만 순열을 이룰 수 있다는 조건을 추가하면 쉽게 걸러낼 수 있다.
*/

#include <iostream>
#include <vector>

std::vector<std::string> perms;
char nums[20];
bool visit[20];
int n, m;

void permutation(int count){
    if(count == m){
        std::cout << nums << "\n";
    }
    else {
        for(int num = 1; num <= n; num++){
            if(!visit[num]){
                if(count > 0){	// 0 미만의 인덱스를 접근하지 않게 하기 위한 조건
                    if(nums[(count - 1) * 2] > num + '0'){ 	// 직전 원소가 현재 원소보다
                        continue;							// 크면 탐색 종료
                    }
                }
                nums[count * 2] = num + '0';
                visit[num] = 1;
                permutation(count + 1);
                visit[num] = 0;
            }
        }
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    std::cin >> n >> m;

    for(int index = 0; index < m * 2; index++){
        nums[index] = ' ';
    }

    permutation(0);
}
/*

직전의 N과 M (1) 문제에서와 마찬가지로 문자열 형태로 배열을 출력하기 위해 특정 인덱스에 접근할 때 
index * 2를 해준 것 때문에 코드의 배열 인덱스에 포함된 * 2를 혼란스러워 말자.

*/