
/*
인덱스 접근 연습에 좋은 스도쿠 문제이다. 
특정 칸을 선택했을 때 해당 칸이 속한 행/열/작은 상자에 대한 중복을 모두 체크해야 하기 때문에 배열 인덱스 접근 코드가 상당히 많다.

스도쿠 판에 들어가는 숫자가 1~9이기 때문에 이를 간편하게 활용하기 위해 실제 배열은 10x10으로 만들어 값을 저장한다. 
그리고 값을 저장해야 하는(0이 입력된) 칸의 목록을 배열로 관리하여 백트래킹에 사용하기 용이한 형태로 둔다.

접근해야 하는 빈 칸의 좌표와 몇 번째 작은 박스에 속하는지 정보를 구조체로 관리하여 연산량을 줄였다.

아래는 소스 코드 전문이다.
*/

#include <iostream>
#include <vector>
#define MAX_SIZE 9

struct holeCoor{
    int x;
    int y;
    int squareNum;
};

int sudoku[MAX_SIZE + 1][MAX_SIZE + 1];

bool row[MAX_SIZE + 1][MAX_SIZE + 1];
bool col[MAX_SIZE + 1][MAX_SIZE + 1];
bool square[MAX_SIZE + 1][MAX_SIZE + 1];

int holeNum = 0;
holeCoor hole[81];

int get_square_number(int x, int y){
    return ((x - 1)/ 3) + (((y - 1)/ 3) * 3) + 1;
}

bool back_tracking(int index){
    if(index == holeNum){
        for(int y = 1; y <= MAX_SIZE; y++){
            for(int x = 1; x <= MAX_SIZE; x++){
                std::cout << sudoku[y][x] << " ";
            }
            std::cout << "\n";
        }
        return true;
    }
    else{
        for(int num = 1; num <= MAX_SIZE; num++){
            int x = hole[index].x;
            int y = hole[index].y;
            int squareNum = hole[index].squareNum;

            if(!row[y][num] && !col[x][num] && !square[squareNum][num]){
                sudoku[y][x] = num;
                row[y][num] = true;
                col[x][num] = true;
                square[squareNum][num] = true;

                if(back_tracking(index + 1)){
                    return true;
                }

                sudoku[y][x] = 0;
                row[y][num] = false;
                col[x][num] = false;
                square[squareNum][num] = false;
            }
        }
    }
    return false;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    for(int y = 1; y <= MAX_SIZE; y++){
        for(int x = 1; x <= MAX_SIZE; x++){
            std::cin >> sudoku[y][x];
            int squareNum = get_square_number(x, y);

            row[y][sudoku[y][x]] = true;
            col[x][sudoku[y][x]] = true;
            square[squareNum][sudoku[y][x]] = true;
            if(sudoku[y][x] == 0){
                hole[holeNum++] = {x, y, squareNum};
            }
        }
    }
    back_tracking(0);
}