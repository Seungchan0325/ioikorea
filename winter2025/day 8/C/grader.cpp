#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <algorithm>
#include <tuple>
#include <cassert>
#define M_PI 3.1415926535897932384626

std::vector<double> classify(std::vector<int> x1, std::vector<int> y1, std::vector<int> x2, std::vector<int> y2);

unsigned int c = (unsigned)std::chrono::steady_clock::now().time_since_epoch().count();
std::mt19937 rng(c);
// std::mt19937 rng(1242048561);

static int evaluate(std::vector<int> x1, std::vector<int> y1, std::vector<int> x2, std::vector<int> y2,
               double x0, double y0, double a, double b) {
  assert(x1.size() == y1.size());
  assert(x2.size() == y2.size());

  int cnt = 0;

  for(unsigned i = 0; i < x1.size(); i++) {
    int x = x1[i], y = y1[i];
    long double by = ((long double)(x <= x0 ? a : b) * (x - x0) + y0);
    if(y < by && fabs(y - by) > 1e-8) {
      cnt += 1;
    }  
  }
  
  for(unsigned i = 0; i < x2.size(); i++) {
    int x = x2[i], y = y2[i];
    long double by = ((long double)(x <= x0 ? a : b) * (x - x0) + y0);
    if(y > by && fabs(y - by) > 1e-8) {
      cnt += 1;
    }
  }
  
  return cnt;
}

int main() {
  const int NUM_POINTS = 10000;
  const int MAX_COORDINATE = 100000;

  std::uniform_int_distribution<int> pos_rng(0, MAX_COORDINATE);

  while(true) {
    int x0 = pos_rng(rng);
    int y0 = pos_rng(rng);

    auto get_slope = [&]() {
      std::uniform_real_distribution<double> ang_rng(0, M_PI / 2 - 1e-4);
      double ang = ang_rng(rng);
      std::uniform_int_distribution<int> slope_sign_rng(0, 1);
      if(slope_sign_rng(rng)) ang += M_PI / 2;
      return std::make_pair(floor(cos(ang) * 1e3), floor(sin(ang) * 1e3));
    };

    int ax, ay; std::tie(ax, ay) = get_slope();
    int bx, by; std::tie(bx, by) = get_slope();

    auto boundary = [&x0, &y0, &ax, &ay, &bx, &by](int x) {
      if(x <= x0) {
        return ay * (x - x0) / ax + y0;
      }else {
        return by * (x - x0) / bx + y0;
      }
    };

    std::vector< std::pair<long long, int> > up_x_cand, down_x_cand;
    for(int x = 0; x <= MAX_COORDINATE; x += 1) {
      int y = boundary(x);
      if(y + 1 < MAX_COORDINATE) {
        up_x_cand.emplace_back(MAX_COORDINATE - std::max(0, y) - 1, x);
      }
      if(y > 0) {
        down_x_cand.emplace_back(std::min(MAX_COORDINATE, y), x);
      }
    }

    for(unsigned i = 1; i < up_x_cand.size(); i++) {
      up_x_cand[i].first += up_x_cand[i-1].first;
    }
    for(unsigned i = 1; i < down_x_cand.size(); i++) {
      down_x_cand[i].first += down_x_cand[i-1].first;
    }

    if(up_x_cand.empty() || down_x_cand.empty()) {
      continue;
    }

    auto add_up = [&up_x_cand, &boundary](std::vector<int> &xs, std::vector<int> &ys) {
      std::uniform_int_distribution<long long> up_x_idx_rng(1, up_x_cand.back().first);
      long long idx = up_x_idx_rng(rng);

      int i = std::distance(
        up_x_cand.begin(),
        std::lower_bound(up_x_cand.begin(), up_x_cand.end(), std::make_pair(idx, -1))
      );

      int x = up_x_cand[i].second;
      int y = std::max(boundary(x), 0) + 1 + (idx - (i == 0 ? 0 : up_x_cand[i-1].first));

      xs.push_back(x);
      ys.push_back(y);
      assert(0 <= x && x <= MAX_COORDINATE);
      assert(0 <= y && y <= MAX_COORDINATE);
    };

    auto add_down = [&down_x_cand, &boundary, &MAX_COORDINATE](std::vector<int> &xs, std::vector<int> &ys) {
      std::uniform_int_distribution<long long> down_x_idx_rng(1, down_x_cand.back().first);
      long long idx = down_x_idx_rng(rng);

      int i = std::distance(
        down_x_cand.begin(),
        std::lower_bound(down_x_cand.begin(), down_x_cand.end(), std::make_pair(idx, -1))
      );

      int x = down_x_cand[i].second;
      int y = std::min(boundary(x), MAX_COORDINATE) - (idx - (i == 0 ? 0 : down_x_cand[i-1].first));
      
      xs.push_back(x);
      ys.push_back(y);
      assert(0 <= x && x <= MAX_COORDINATE);
      assert(0 <= y && y <= MAX_COORDINATE);
    };

    // upwards
    std::vector<int> x1, y1;
    std::vector<int> x2, y2;

    std::uniform_int_distribution<int> number_rng(1, NUM_POINTS);
    int N = number_rng(rng);
    int M = NUM_POINTS - N;
    for(int i = 0; i < N; i++) {
      add_up(x1, y1);
    }
    for(int i = 0; i < M; i++) {
      add_down(x2, y2);
    }

    FILE *in = fopen("example.in", "w");
    fprintf(in, "%ld\n", x1.size());
    for(unsigned i = 0; i < x1.size(); i++) fprintf(in, "%d %d\n", x1[i], y1[i]);
    fprintf(in, "%ld\n", x2.size());
    for(unsigned i = 0; i < x2.size(); i++) fprintf(in, "%d %d\n", x2[i], y2[i]);

    assert(evaluate(x1, y1, x2, y2, x0, y0, (double)ay / ax, (double)by / bx) == 0);
    // if you spot an assertion error in this line, please contact jogyo

    std::vector<double> result = classify(x1, y1, x2, y2);
    assert(result.size() == 4);

    printf("Your score: %.4f\n", std::max(0.0, 1 - (double)3 * evaluate(x1, y1, x2, y2, result[0], result[1], result[2], result[3]) / NUM_POINTS));
    printf("%u", c);
    break;
  }
 
  return 0;
}
