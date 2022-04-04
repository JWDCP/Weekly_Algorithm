/*
해당 문제는 bfs를 이용해 해결하였다. 경로에 가중치가 설정된 최단 경로 찾기는 dfs로 푸는 것이 적절하지만, 
가중치가 없는 최단 경로는 bfs로 풀어야 한다. 일정 경로를 거쳐 특정 칸에 처음 도달했을 때 경로의 길이가 최소라는 보장이 없기 때문이다.

· 메인 아이디어
    이 문제는 일반적인 bfs 문제들과 크게 다르지 않은 형태로 보이지만 "필요하다면 한 개의 벽을 제거할 수 있다"는 조건이 포함되어 있다. 
    이것이 로직에 큰 영향을 준다.

    즉,

    - 벽을 파괴하지 않으면서 이동한 방문 정보
    - 벽을 파괴한 상태로 이동한 방문 정보
    
    를 함께 관리해야 한다. 시작점에서부터 도착점이 아닌 특정 지점에 도달할 때까지 벽을 부수고 이동한 경로의 길이와 
    벽을 부수지 않고 이동한 경로의 길이가 같다면 굳이 부수지 않는 것이 낫다(벽을 제거한다 파괴한다 부순다 아주 표현이 뒤죽박죽 난리가 났다). 
    그 이유는 당연하게도 앞으로 갈 길에 '반드시 부숴야 하는' 벽이 존재할 수도 있기 때문이다.

    따라서 벽을 부수고 이동하는 거리와 벽을 부수지 않고 이동하는 거리가 같다면 당연히 벽을 부수지 않고 이동하는 방법을 택할 것이다. 
    또는 벽을 부수면 훨씬 거리가 단축되지만 벽을 부수지 않고 우회하여도 조금 더 오래 걸릴 뿐 도달을 할 수 있다면 그 경로도 유의미한 경로가 될 것이다.

    이러한 이유로 '벽을 파괴하지 않으면서 이동한 방문 정보'와 '벽을 파괴한 상태로 이동한 방문 정보'를 함께 관리하는 것이다.

· 알고리즘
    bfs로 길찾기 알고리즘에서 '해당 지점이 이동 가능한 지점인지', '해당 지점에 방문한 기록이 있는지'를 판단하고 
    두 조건을 모두 만족하면 다음 방문 지점에 추가한다. 이를 cpp 코드로 작성하면 아래와 같은 형태로 표현할 수 있다.

    if(!map[nextY][nextX] && !visit[nextY][nextX]) { ... } // map 변수는 길이 1, 벽이 0
    
    하지만 이번 문제는 케이스가 다르다. '벽을 파괴한 적 있는지'에 대한 정보에 따라 특정 지점에 방문할 수 있는지 없는지가 나뉘기 때문이다. 
    이번 문제에서 다음 지점으로 이동하기 위해 확인해야 하는 경우는 두 가지로 나뉠 수 있다.

    - 다음 지점이 '길'이고, 방문한 적이 없다.
    - 다음 지점이 '벽'이고, 여태까지 벽을 파괴한 적이 없다.
    
    다음 지점이 벽일 때, 해당 지점을 방문한 적이 없더라도 벽을 파괴한 기록이 있다면 어차피 갈 수 없기 때문에 방문 여부를 확인할 필요가 없다. 
    이후의 내용에선 벽 파괴 여부를 breaking이라는 변수로 표현하겠다. 또한 위 조건들을 만족하여 다음 지점으로 이동하면서 다음과 같은 처리가 필요하다.

    - 다음 지점이 '길'이고, 방문한 적이 없다.
        : breaking의 변화 없이 다음 지점을 큐에 넣는다.
    - 다음 지점이 '벽'이고, 여태까지 벽을 파괴한 적이 없다.
        : breaking을 true로 만들고 다음 지점을 큐에 넣는다.
    
    위 경우에서 breaking이 false에서 true가 될 수는 있지만 true에서 false가 될 순 없다. 
    즉, 벽을 부수지 않은 상태에서 부순 상태가 될 수는 있지만 부순 사실을 무를 수는 없는 것이다.

이러한 내용을 정리하여 만들어진 전체 소스코드는 다음과 같다.
*/

#include <iostream>
#include <queue>
#include <vector>

struct state{
    int x;
    int y;
    int breaking;
};

std::pair<int, int> direction[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int rowSize, colSize;
int map[1000][1000];

int visit[1000][1000][2]; // 벽을 부수지 않은 상태 = 0, 벽을 부순 상태 = 1
std::queue<state> q;

int bfs(){
    while(!q.empty()){
        state cur = q.front();
        q.pop();
        if(cur.x == colSize - 1 && cur.y == rowSize - 1){ 	// 큐의 원소들을 따라 도착 지점에 도달한
            return visit[cur.y][cur.x][cur.breaking];		// 첫 번째 경로가 최단 경로임이 보장되기 때문에 
        }													// 도착 지점에 도달하자마자 bfs 중단

        for(auto dir : direction){
            int nextX = cur.x + dir.second;
            int nextY = cur.y + dir.first;

            if(nextX < 0 || nextX >= colSize || nextY < 0 || nextY >= rowSize){
                continue;
            }
            if(map[nextY][nextX] == 1 && !cur.breaking){
                q.push({nextX, nextY, 1});
                visit[nextY][nextX][1] = visit[cur.y][cur.x][cur.breaking] + 1;
            }
            else if(map[nextY][nextX] == 0 && !visit[nextY][nextX][cur.breaking]){
                q.push({nextX, nextY, cur.breaking});
                visit[nextY][nextX][cur.breaking] = visit[cur.y][cur.x][cur.breaking] + 1;
            }
        }
    }

    return -1;	// 도착 지점에 도달하지 못한 채로 bfs가 종료되면 -1을 반환
}

int main(){
    scanf("%d %d", &rowSize, &colSize);
    for(int row = 0; row < rowSize; row++){
        std::string line;
        std::cin >> line;

        for(int index = 0; index < colSize; index++){
            map[row][index] = line[index] - '0';
        }
    }

    q.push({0, 0, 0});
    visit[0][0][0] = 1;

    printf("%d", bfs());
}