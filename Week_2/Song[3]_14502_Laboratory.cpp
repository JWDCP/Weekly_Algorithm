/*
· 메인 아이디어
    브루트포스와 bfs를 함께 활용하는 문제다. 반드시 세워야 하는 3개의 벽을 브루트포스로 지정해주고 바이러스의 번식을 bfs로 설계해준다.

    이때 일반적으로 많이 쓰는 큐를 활용한 bfs를 적용했는데 다른 사람들의 코드에 비해 많이 느린 것을 확인하였다. 
    때문에 어떻게 시간을 줄였는지 확인했는데 큐 대신 단순 배열에서 인덱스를 효과적으로 다루고, 
    맵에서 다음 방향을 배열로 관리하는 대신 일일이 특정 방향에 대한 처리를 해주는 것으로 연산을 줄일 수 있었다.

먼저 올리는 코드는 처음 정답으로 처리된 코드44ms, 뒤에 올리는 코드가 최종적으로 수정된 코드16ms이다.
*/

/*
// 초기 코드. 44ms
#include <iostream>
#include <queue>
#include <vector>

std::pair<int, int> direction[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int n, m;
int map[8][8];
bool visit[8][8];

std::queue<std::pair<int, int>> q;
std::pair<int, int> ways[64];
std::vector<std::pair<int, int>> motherVirus;
std::vector<std::pair<int, int>> viruses;

int waysNum = 0;

int maxSafeZone = 0;

void bfs(){
    while(!q.empty()){
        std::pair<int, int> cur = q.front();
        q.pop();

        for(auto dir : direction){
            int nextX = cur.first + dir.first;
            int nextY = cur.second + dir.second;

            if(nextX < 0 || nextX >= m || nextY < 0 || nextY >= n){
                continue;
            }
            else{
                if(!visit[nextY][nextX] && map[nextY][nextX] == 0){
                    q.push({nextX, nextY});
                    visit[nextY][nextX] = true;
                    map[nextY][nextX] = 2;
                    viruses.push_back({nextX, nextY});
                }
            }
        }
    }
    int safeZone = waysNum - 3 - viruses.size() + motherVirus.size();
    if(maxSafeZone < safeZone){
        maxSafeZone = safeZone;
    }
    for(auto virus : viruses){
        map[virus.second][virus.first] = 0;
        visit[virus.second][virus.first] = false;
    }
    viruses.clear();
}

void make_wall(){
    for(int firstWall = 0; firstWall < waysNum - 2; firstWall++){
        map[ways[firstWall].second][ways[firstWall].first] = 1;
        for(int secondWall = firstWall + 1; secondWall < waysNum - 1; secondWall++){
            map[ways[secondWall].second][ways[secondWall].first] = 1;
            for(int thirdWall = secondWall + 1; thirdWall < waysNum; thirdWall++){
                map[ways[thirdWall].second][ways[thirdWall].first] = 1;

                for(auto mother : motherVirus){
                    q.push(mother);
                    viruses.push_back(mother);
                    map[mother.second][mother.first] = 2;
                    visit[mother.second][mother.first] = true;
                }
                bfs();

                map[ways[thirdWall].second][ways[thirdWall].first] = 0;
            }
            map[ways[secondWall].second][ways[secondWall].first] = 0;
        }
        map[ways[firstWall].second][ways[firstWall].first] = 0;
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> n >> m;
    for(int y = 0; y < n; y++){
        for(int x = 0; x < m; x++){
            std::cin >> map[y][x];
            if(map[y][x] == 2){
                motherVirus.push_back({x, y});
            }
            else if(map[y][x] == 0){
                ways[waysNum++] = {x, y};
            }
        }
    }

    make_wall();
    std::cout << maxSafeZone << std::endl;
}
*/

// 최종 코드. 16ms
#include <iostream>

int n, m;
int map[10][10];
int tempMap[10][10];

std::pair<int, int> ways[64];
std::pair<int, int> viruses[64];

int virusNum = 0;
int tempVirusNum = 0;
int waysNum = 0;

int maxSafeZone = 0;

void bfs(){
    for(int firstWall = 0; firstWall < waysNum - 2; firstWall++){
        for(int secondWall = firstWall + 1; secondWall < waysNum - 1; secondWall++){
            for(int thirdWall = secondWall + 1; thirdWall < waysNum; thirdWall++){

                for(int y = 1; y <= n; y++){
                    for(int x = 1; x <= m; x++){
                        tempMap[y][x] = map[y][x];
                    }
                }

                tempMap[ways[firstWall].first][ways[firstWall].second] = 1;
                tempMap[ways[secondWall].first][ways[secondWall].second] = 1;
                tempMap[ways[thirdWall].first][ways[thirdWall].second] = 1;

                tempVirusNum = virusNum;

                for(int spreadCnt = 0; spreadCnt < tempVirusNum; spreadCnt++){
                    if(tempMap[viruses[spreadCnt].first + 1][viruses[spreadCnt].second] == 0){
                        tempMap[viruses[spreadCnt].first + 1][viruses[spreadCnt].second] = 2;
                        viruses[tempVirusNum++] = {viruses[spreadCnt].first + 1, viruses[spreadCnt].second};
                    }
                    if(tempMap[viruses[spreadCnt].first - 1][viruses[spreadCnt].second] == 0){
                        tempMap[viruses[spreadCnt].first - 1][viruses[spreadCnt].second] = 2;
                        viruses[tempVirusNum++] = {viruses[spreadCnt].first - 1, viruses[spreadCnt].second};
                    }
                    if(tempMap[viruses[spreadCnt].first][viruses[spreadCnt].second + 1] == 0){
                        tempMap[viruses[spreadCnt].first][viruses[spreadCnt].second + 1] = 2;
                        viruses[tempVirusNum++] = {viruses[spreadCnt].first, viruses[spreadCnt].second + 1};
                    }
                    if(tempMap[viruses[spreadCnt].first][viruses[spreadCnt].second - 1] == 0){
                        tempMap[viruses[spreadCnt].first][viruses[spreadCnt].second - 1] = 2;
                        viruses[tempVirusNum++] = {viruses[spreadCnt].first, viruses[spreadCnt].second - 1};
                    }
                }

                int safeZone = waysNum - 3 - tempVirusNum + virusNum;
                if(maxSafeZone < safeZone){
                    maxSafeZone = safeZone;
                }
            }
        }
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    std::cin >> n >> m;
    for(int y = 1; y <= n; y++){
        for(int x = 1; x <= m; x++){
            std::cin >> map[y][x];
            if(map[y][x] == 2){
                viruses[virusNum++] = {y, x};
            }
            else if(map[y][x] == 0){
                ways[waysNum++] = {y, x};
            }
        }
    }

    for(int y = 0; y < 10; y++){
        for(int x = 0; x < 10; x++){
            tempMap[y][x] = -1;
        }
    }
    bfs();
    std::cout << maxSafeZone;
}