#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

const int MAXN = 501;
const int MAXK = 101;
const int INF = INT_MAX / 2;

int N, K;
int a[MAXN];
int A[MAXN];
int F[MAXN][MAXK];
int MinFull[MAXN][MAXK];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> K;
    for (int i = 1; i <= N; ++i) cin >> a[i];

    A[N] = 0;
    for (int i = N - 1; i >= 1; --i)
        A[i] = A[i + 1] + a[i + 1];

    int total_sz = 0;
    for (int i = 1; i <= N; ++i) total_sz += a[i] + 1;
    vector<int> P_data(total_sz);
    vector<int> offset(N + 2);
    int cur = 0;
    for (int i = 1; i <= N; ++i) {
        offset[i] = cur;
        cur += a[i] + 1;
    }

    for (int i = N; i >= 1; --i) {
        if (a[i] == 0) {
            F[i][1] = (i < N) ? F[i + 1][1] : 0;
            MinFull[i][1] = F[i][1];
            int* P_i = &P_data[offset[i]];
            P_i[0] = F[i][1];
            continue;
        }
        int* P_i = &P_data[offset[i]];
        int min_so_far = (i < N) ? F[i + 1][1] : 0;
        P_i[0] = min_so_far;
        int min_f = INF;
        int A_i = A[i];
        for (int r = 1; r < a[i]; ++r) {
            int val = r + A_i - min_so_far;
            if (val < min_so_far) min_so_far = val;
            P_i[r] = min_so_far;
            if (val < min_f) min_f = val;
        }

        int r = a[i];
        int val = r + A_i - min_so_far;
        if (val < min_so_far) min_so_far = val;
        P_i[r] = min_so_far;
        F[i][1] = val;

        int f0 = (i < N) ? F[i + 1][1] : 0;
        MinFull[i][1] = f0;
        if (min_f < MinFull[i][1]) MinFull[i][1] = min_f;
    }

    for (int L = 2; L <= K; ++L) {
        for (int i = N; i >= 1; --i) {
            if (a[i] == 0) {
                F[i][L] = (i < N) ? F[i + 1][L] : 0;
                MinFull[i][L] = F[i][L];
                continue;
            }
            int q_max = min(L, N - i + 1);
            int M2 = INF;
            for (int q = 2; q <= q_max; ++q) {
                int mf = MinFull[i + q - 1][q];
                if (mf < M2) M2 = mf;
            }
            int A_i = A[i];
            const int* P_i = &P_data[offset[i]];
            int min_f = INF;
            for (int r = 1; r < a[i]; ++r) {
                int best = P_i[r - 1];
                if (M2 < best) best = M2;
                int val = r + A_i - best;
                if (val < min_f) min_f = val;
            }
            int r = a[i];
            int best = P_i[r - 1];
            if (M2 < best) best = M2;
            F[i][L] = r + A_i - best;

            int f0 = (i < N) ? F[i + 1][L] : 0;
            MinFull[i][L] = f0;
            if (min_f < MinFull[i][L]) MinFull[i][L] = min_f;
        }
    }

    cout << F[1][K] << "\n";
    return 0;
}