#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;

#define INF 987654321


int n,m,k,cnt,res;
vector<pii> player;
pii exits; // 출구
int maze[11][11];
int dy[4]={-1,1,0,0};
int dx[4]={0,0,-1,1};

int calcDist(int y1,int x1,int y2,int x2){
    return abs(y1-y2) + abs(x1-x2);
}

bool findPeople(int r1,int c1,int r2,int c2){
    for (int i = 0; i < player.size(); ++i) {
        if(player[i].first>=r1 && player[i].first<=r2 && player[i].second>=c1 && player[i].second<=c2) return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m >> k;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> maze[i][j];
        }
    }
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        player.push_back({a, b});

    }
    cin >> exits.first >> exits.second;
    cnt = player.size();
    while (k--) {

        // 한 칸 이동하기
        for (int i = 0; i < player.size(); ++i) {
            if (player[i].first == -1) continue;
            for (int j = 0; j < 4; ++j) {
                int ny = player[i].first + dy[j];
                int nx = player[i].second + dx[j];
                if (maze[ny][nx] != 0) continue;
                if (ny == exits.first && nx == exits.second) { // 출구에 도착
                    player[i].first = -1; // 탈출한 사람의 y좌표를 -1로 표시
                    cnt--;
                    res++;
                    break;
                }
                if (calcDist(exits.first, exits.second, player[i].first, player[i].second) >
                    calcDist(exits.first, exits.second, ny, nx)) { // 출구와 가까워지면 위치 갱신
                    player[i].first = ny;
                    player[i].second = nx;
                    res++;
                    break;
                }
            }
        }
        if (cnt == 0) break;

        int length = INF;

        // 정사각형 만들기
        for (int i = 0; i < player.size(); ++i) { // 가장 작은 정사각형 길이 찾기
            if (player[i].first == -1) continue;
            length = min(length, max(abs(exits.first - player[i].first),
                                     abs(exits.second - player[i].second))); // 정사각형의 한 변의 길이
        }


        // 정사각형의 왼쪽 위 죄표 찾기
        pii square;
        bool flag = false;
        for (int i = 1; i <= n - length; ++i) {
            if (flag) break;
            for (int j = 1; j <= n - length; ++j) {
                int r1 = i;
                int c1 = j;
                int r2 = i + length;
                int c2 = j + length;
                if (exits.first >= r1 && exits.first <= r2 && exits.second >= c1 && exits.second <= c2 &&
                    findPeople(r1, c1, r2, c2)) {
                    square = {i, j};
                    flag = true;
                    break;
                }
            }
        }


        // 정사각형 회전
        int newMaze[11][11];
        for (int i = square.first; i <= square.first + length; ++i) {
            for (int j = square.second; j <= square.second + length; ++j) {
                if (maze[i][j]) maze[i][j]--;
            }
        }
        for (int i = square.first; i <= square.first + length; ++i) {
            for (int j = square.second; j <= square.second + length; ++j) {
                int dy = i - square.first;
                int dx = j - square.second;
                int y = dx;
                int x = length - dy;
                newMaze[square.first + y][square.second + x] = maze[i][j];
            }
        }
        for (int i = square.first; i <= square.first + length; ++i) {
            for (int j = square.second; j <= square.second + length; ++j) {
                maze[i][j] = newMaze[i][j];
            }
        }
        // 참가자 회전
        for (int i = 0; i < player.size(); ++i) {
            if (player[i].first == -1) continue;
            if (player[i].first >= square.first && player[i].first <= square.first + length &&
                player[i].second >= square.second && player[i].second <= square.second + length) {
                int dy = player[i].first - square.first;
                int dx = player[i].second - square.second;
                int y = dx;
                int x = length - dy;
                player[i] = {square.first + y, square.second + x};
            }
        }

        // 출구 회전
        int dy = exits.first - square.first;
        int dx = exits.second - square.second;
        int y = dx;
        int x = length - dy;
        exits = {square.first + y, square.second + x};

        cout << res << '\n';
        cout << exits.first << ' ' << exits.second << '\n';
    }
}