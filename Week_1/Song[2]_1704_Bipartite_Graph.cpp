/*
· 메인 아이디어
    이분 그래프는 인접한 노드끼리 서로 다른 그룹으로 분류할 수 있는 그래프이다. 
    따라서 자신과 인접한 노드가 서로 다른 그룹인지만 체크하면 된다.

    자신과 인접한 노드가 이전에 방문한 적 없는 노드라면 특정 그룹에 분류돼있지 않은 상태이니 방문체크를 해주고 그룹을 지정해주면 되고, 
    방문한 적 있는 노드라면 자신과 같은 그룹인지 체크하면 된다. 따라서 일반적인 bfs와 큰 차이가 없는 코드를 가진다.

· 내가 틀린 이유
    두 가지 요소를 간과하였다.

    첫째는 여러 개의 테스트케이스를 가지는 만큼 변수들의 초기화에 신경써야 한다는 것. 필자는 bfs를 함수로 분리하였고, 
    사용되는 큐나 배열 등을 매개변수로 전달하지 않고 전역변수로 두었기 때문에 각 케이스에 대한 처리가 끝나고 전역변수들의 초기화가 매우 중요했으나, 
    일부 변수의 초기화를 정상적으로 처리하지 않았다.

    둘째, 불완전 그래프에 대한 것을 간과하였다. 이것이 헤맨 주 원인인데, 애꿎은 로직만 들여다보고 그룹 넘버 바꿔보고 이상한 짓을 다 하였지만 
    반례를 찾는 것이 더 중요하였다. 문제에서 주어지는 모든 정점이 이어진 완전 그래프라는 조건이 없었는데 필자는 완전 그래프일 것이라고 믿은 것이다.

    첫 번째 정점에 대해서만 bfs를 실행했기 때문에 첫 번째 정점에 이어지지 않은 정점들에 대한 이분 그래프 탐색이 이루어지지 않아 
    자꾸 문제를 틀린 것이다. 따라서 그래프 내 모든 정점에 대해 방문 처리가 된 정점인지 확인하고 방문 처리가 안 된 정점이라면 해당 정점에 대해 
    추가적인 이분 그래프 판별을 해주어 정답 처리가 될 수 있었다.

이 모든 내용을 바탕으로 작성된 최종 코드는 아래와 같다.
*/

#include <iostream>
#include <vector>
#include <queue>

int v, e;
std::queue<int> q;
std::vector<int> graph[20001];
int visit[20001];
int group[20001];

bool bfs(){
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        for(auto adj : graph[cur]){
            if(!visit[adj]){
                q.push(adj);
                visit[adj] = 1;
                group[adj] = group[cur] * -1;
            }
            else if(group[cur] == group[adj]){
                return false;
            }
        }
    }
    return true;
}

void reset(){
    for(int index = 0; index <= v; index++){
        visit[index] = 0;
        group[index] = 0;
        graph[index].clear();
    }
    while(!q.empty()){
        q.pop();
    }
}

int main(){
    int cases;
    scanf("%d", &cases);

    for(int count = 0; count < cases; count++){
        scanf("%d %d", &v, &e);
        int vert1, vert2;
        for(int edgeCount = 0; edgeCount < e; edgeCount++){
            scanf("%d %d", &vert1, &vert2);
            graph[vert1].push_back(vert2);
            graph[vert2].push_back(vert1);
        }

        bool bipartite = true;
        for(int index = 1; index <= v; index++){    // 불완전 그래프를 위한 모든 정점 탐색
            if(!visit[index]){
                q.push(index);
                visit[index] = 1;
                group[index] = 1;
            }
            if(!bfs()){
                bipartite = false;
                break;
            }
        }
        (bipartite) ? printf("YES\n") : printf("NO\n");
        reset();
    }
}