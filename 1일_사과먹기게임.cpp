#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

struct goal_info
{
	int idx;
	int goal_y;
	int goal_x;
};

int N;
vector<vector<int>> map;
vector<vector<int>> visited;
vector<goal_info> axis;

vector<int> dy = { 0, 1, 0, -1 };
vector<int> dx = { 1, 0, -1, 0 };

int answer; // 최종 결과
int result; // 각 턴의 결과
int dir_cnt;
int move_cnt;
int last_dir;

bool cmp(goal_info a, goal_info b)
{
	return a.idx < b.idx;
}

void init()
{
	dir_cnt = 0;
	move_cnt = 0;
	result = INT_MAX;
	answer = 0;
	last_dir = 0;

	visited.clear();
	axis.clear();
	map.clear();
}

void input()
{
	cin >> N;
	map.resize(N, vector<int>(N));
	visited.resize(N, vector<int>(N, 0));

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			cin >> map[i][j];
			if (map[i][j] > 0)
			{
				struct goal_info g;
				g = { map[i][j], i, j };
				axis.push_back(g);
			}
		}

	sort(axis.begin(), axis.end(), cmp);
}

void dfs(int dir, int goal_y, int goal_x, int curr_y, int curr_x)
{
	if (goal_y == curr_y && goal_x == curr_x)
	{
		if (result > dir_cnt)
		{
			result = dir_cnt;
			last_dir = dir;
		}

		return;
	}

	//if (move_cnt >= N)
	//	return;

	int orig_dir = dir;

	for (int ndir = dir; ndir <= dir + 1; ndir++)
	{
		int next_dir =  ndir % 4;
		int next_y = curr_y + dy[next_dir];
		int next_x = curr_x + dx[next_dir];

		if (next_y < 0 || next_y >= N || next_x < 0 || next_x >= N) continue;
		if (visited[next_y][next_x] >= 2) continue;
		if (result <= dir_cnt) continue;
		if (orig_dir != ndir) dir_cnt++;
		move_cnt++;
		visited[next_y][next_x]++;
		dfs(next_dir, goal_y, goal_x, next_y, next_x);
		if (orig_dir != ndir) dir_cnt--;
		visited[next_y][next_x]--;
		move_cnt--;
	}
}

void solution()
{
	int c_y = 0, c_x = 0;

	for (auto ax : axis)
	{
		int g_y = ax.goal_y;
		int g_x = ax.goal_x;
		result = INT_MAX;
		move_cnt = 0;

		dfs(last_dir, g_y, g_x, c_y, c_x);
		c_y = g_y;
		c_x = g_x;
		
		answer += result;
		//cout << answer << '\n';

		for (int i = 0; i < visited.size(); i++)
			for (int j = 0; j < visited[i].size(); j++)
				visited[i][j] = 0;
	}
}

int main()
{
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++)
	{
		init();
		input();
		solution();

		cout << '#' << tc << ' ' << answer << '\n';
	}
	return 0;
}