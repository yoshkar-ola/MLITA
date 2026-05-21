//VASILIEV ALEXEY PC-21
//12.6.Жизнь на Марсе(7)
//При высадке на Марс было основано N поселений.Каждое из них равномерно расширялось во все стороны на L марсианских миль в месяц.Постепенно поселения начали сливаться друг с другом, получая общее название.Какое минимальное время с момента высадки потребуется для того, чтобы на Марсе осталось не более K поселений ?
//Ввод из файла INPUT.TXT.В первой строке задаются через пробел  три целых положительных значения : начальное количество поселений N(1 ≤ N ≤ 1000), число K(1 ≤ K ≤ 10, K < N) и скорость роста поселений L(1 ≤ L ≤ 100).Далее в следующих N строках содержатся через пробел целые координаты поселений Xi, Yi(-1000 ≤ Xi, Yi ≤ 1000) в марсианских милях.
//    Вывод в файл OUTPUT.TXT.В единственной строке вывести с точностью до 3 знаков минимальное время в месяцах с момента высадки, необходимое для того, чтобы в результате слияния осталось не более K поселений.
//    Пример
//    Ввод
//    3 2 1
//    - 1 1
//    2 1
//    2 5
//    Вывод
//    1.50
//VS2019
//https://docs.google.com/presentation/d/1rBfFXjaH-UM78TcRSNFeSASAGkuxujGl/edit?slide=id.p8#slide=id.p8
// https://ru.wikipedia.org/wiki/%D0%A1%D0%B8%D1%81%D1%82%D0%B5%D0%BC%D0%B0_%D0%BD%D0%B5%D0%BF%D0%B5%D1%80%D0%B5%D1%81%D0%B5%D0%BA%D0%B0%D1%8E%D1%89%D0%B8%D1%85%D1%81%D1%8F_%D0%BC%D0%BD%D0%BE%D0%B6%D0%B5%D1%81%D1%82%D0%B2
// lesson 10 slide 8
#include <cmath>
#include <fstream>
#include <iomanip>
#include <numeric>
#include <vector>
#include <algorithm>

struct Edge {
    int u;
    int v;
    long long dist2;
};

class DSU {
public:
    explicit DSU(int n) : parent(n), size(n, 1) {
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return false;
        }
        if (size[a] < size[b]) {
            std::swap(a, b);
        }
        parent[b] = a;
        size[a] += size[b];
        return true;
    }

private:
    std::vector<int> parent;
    std::vector<int> size;
};

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int n = 0; // к-во поселений
    int k = 0; // к-во групп
    int l = 0; // скорость роста радиуса в милях за месяц
    in >> n >> k >> l;

    std::vector<int> x(n), y(n);
    for (int i = 0; i < n; ++i) {
        in >> x[i] >> y[i];
    }

    std::vector<Edge> edges;
    edges.reserve(n * (n - 1) / 2);

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            long long dx = static_cast<long long>(x[i]) - x[j];
            long long dy = static_cast<long long>(y[i]) - y[j];
            long long dist2 = dx * dx + dy * dy;
            edges.push_back({i, j, dist2});
        }
    }

    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.dist2 < b.dist2;
    });

    DSU dsu(n);
    int components = n;
    long long criticalDist2 = 0;

    for (const Edge& e : edges) {
        if (!dsu.unite(e.u, e.v)) {
            continue;
        }
        --components;
        if (components <= k) {
            criticalDist2 = e.dist2;
            break;
        }
    }

    double criticalDistance = std::sqrt(static_cast<double>(criticalDist2));
    double answer = criticalDistance / (2.0 * static_cast<double>(l));

    out << std::fixed << std::setprecision(3) << answer;
    return 0;
}
