// Наивная проверка для задачи 14.10 "Распил бруса 2"
// Симулирует Huffman: N единичек + 1 отрезок (L-N), min-heap, всегда сливаем два наименьших.
// Только для малых N (примерно N <= 20) - иначе медленно.
// Читает input.txt, пишет ответ в output.txt и сверяет с f(N)+L.

#include <fstream>
#include <vector>
#include <queue>
#include <iostream>

long long naiveHuffmanCost(long long n, long long bigPiece) {
    std::priority_queue<long long, std::vector<long long>, std::greater<long long>> pq;
    for (long long i = 0; i < n; ++i)
        pq.push(1);
    pq.push(bigPiece);

    long long totalCost = 0;
    while (pq.size() > 1) {
        long long a = pq.top(); pq.pop();
        long long b = pq.top(); pq.pop();
        long long sum = a + b;
        totalCost += sum;
        pq.push(sum);
    }
    return totalCost;
}

long long formulaCost(long long n) {
    if (n <= 1) return 0;
    unsigned long long pow2 = 1;
    int k = 0;
    while (pow2 < (unsigned long long)n) {
        pow2 *= 2;
        ++k;
    }
    return n * (1LL + k) - (long long)pow2;
}

int main() {
    std::ifstream in("input.txt");
    long long L, N;
    in >> L >> N;
    in.close();

    if (N > 25) {
        std::cerr << "naive: N too large, use main.exe for N > 25\n";
        return 1;
    }

    long long bigPiece = L - N;
    long long naiveResult = naiveHuffmanCost(N, bigPiece);
    long long formulaResult = L + formulaCost(N);

    std::ofstream out("output.txt");
    out << naiveResult << "\n";
    out.close();

    if (naiveResult != formulaResult) {
        std::cerr << "MISMATCH: naive=" << naiveResult << " formula=" << formulaResult << "\n";
        return 1;
    }
    return 0;
}
