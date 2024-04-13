#include <iostream>
#include <vector>
using namespace std;

struct Knight {
	int y, x, h, w, hp;
	int damage = 0;
	bool dead = false;
};
int l, n, q,res;
bool can_move = true;
int board[51][51];
int knight_space[51][51];
int copy_space[51][51];
Knight knight[31];
bool visited[31];
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

void move(int id, int d) { // 이동이 가능한지 확인
	//cout << id << '\n';
	visited[id] = true;
	int y = knight[id].y;
	int x = knight[id].x;
	int h = knight[id].h;
	int w = knight[id].w;
	for (int i = y; i < y + h; i++) {
		for (int j = x; j < x+w; j++) {
			int ny = i + dy[d];
			int nx = j + dx[d];
			if (knight_space[ny][nx] == id) continue;
			
			if (ny > l || ny <= 0 || nx > l || nx <= 0 || board[ny][nx]==2) {
				can_move = false;
				return;
			}
			
			int next = knight_space[ny][nx];
			if (knight[next].dead) continue;
			if (next != 0) {
				move(next, d);
			}
		}
	}
}
int main() {
	cin >> l >> n >> q;
	for (int i = 1; i <= l; i++) {
		for (int j = 1; j <= l; j++)
		{
			cin >> board[i][j];
		}
	}
	for (int i = 1; i <= n; i++) {
		int y, x, h, w, k; cin >> y >> x >> h >> w >> k;

		knight[i] = { y,x,h,w,k };
		for (int j = y; j < y+h; j++)
		{
			for (int k = x; k < x + w; k++) {
				knight_space[j][k] = i;
			}
		}
	}
	//for (int i = 1; i <= l; i++) {
	//	for (int j = 1; j <= l; j++)
	//	{
	//		cout << knight_space[i][j] << ' ';
	//	}
	//	cout << '\n';
	//}
	while (q--)
	{
		int id, d; cin >> id >> d;
		if (knight[id].dead) continue;
		can_move = true;
		for (int i = 1; i <= n; i++) {
			visited[i] = false;
		}
		move(id, d);

		//cout << can_move << '\n';
	/*	for (int i = 1; i <= l; i++) {
			cout << knight[i].y << ' ' << knight[i].x << '\n';
		}*/
		if (can_move) {
			if (d == 0) { // 위
				for (int i = 1; i <= l; i++) { // x축 이동
					for (int j = 1; j < l; j++) { // y축 이동
						int next = knight_space[j+1][i];
						if (next == 0 || !visited[next] || knight[next].dead) continue;
						knight_space[j][i] = next;
						knight_space[j+1][i] = 0;
					}
				}
			}
			if (d == 1) { // 오른쪽
				for (int i = 1; i <= l; i++) { // y축 이동
					for (int j = l; j > 1; j--) { // x축 이동
						int next = knight_space[i][j-1];
						if (next == 0 || !visited[next] || knight[next].dead) continue;
						knight_space[i][j] = next;
						knight_space[i][j-1] = 0;
					}
				}
			}
			if (d == 2) { // 아래
				for (int i = 1; i <= l; i++) { // x축 이동
					for (int j = l; j > 1; j--) { // y축 이동
						int next = knight_space[j - 1][i];
						if (next == 0 || !visited[next] || knight[next].dead) continue;
						knight_space[j][i] = next;
						knight_space[j-1][i] = 0;
					}
				}
			}
			if (d == 3) { // 왼쪽
				for (int i = 1; i <= l; i++) { // y축 이동
					for (int j = 1; j < l; j++) { // x축 이동
						int next = knight_space[i][j + 1];
						if (next == 0 || !visited[next] || knight[next].dead ) continue;
						knight_space[i][j] = next;
						knight_space[i][j+1] = 0;
					}
				}
			}
			for (int idx = 1; idx <= n; idx++) {
				if (visited[idx] && !knight[idx].dead) {
					knight[idx].y += dy[d];
					knight[idx].x += dx[d];
					if (idx == id) continue; // 공격자는 옮기기만
					int y = knight[idx].y;
					int x = knight[idx].x;
					int h = knight[idx].h;
					int w = knight[idx].w;
					int damage = 0;
					for (int i = y; i < y + h; i++) {
						for (int j = x; j < x + w; j++) {
							if (board[i][j] == 1) damage++;
						}
					}
					knight[idx].hp -= damage;
					knight[idx].damage += damage;
					//cout << idx << ' ' << knight[idx].damage << '\n';
					if (knight[idx].hp <= 0) {	
						knight[idx].dead = true;
						for (int i = y; i < y + h; i++) {
							for (int j = x; j < x + w; j++) {
								knight_space[i][j]=0;
							}
						}
					}
				}
			}
		}
		//for (int i = 1; i <= l; i++) {
		//	for (int j = 1; j <= l; j++) {
		//		cout << knight_space[i][j] << ' ';
		//	}
		//	cout << '\n';
		//}
		
		//else { // 벽 때문에 이동이 불가하면 원래 판으로 복구
		//	for (int i = 1; i <= l; i++) {
		//		for (int j = 1; j <= l; j++) {
		//			knight_space[i][j] = copy_space[i][j];
		//		}
		//	}
		//}
		
		
	}
	for (int i = 1; i <= l; i++) {
		if (!knight[i].dead) res+= knight[i].damage;
	}
	cout << res << '\n';
}