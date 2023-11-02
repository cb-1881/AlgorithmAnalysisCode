/*
Cole Brausen
CSC-510 Algorithm Analysis

Problem #4 HW-3

My favorite programming language lol
*/



#include <cassert>
#include <climits>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

struct Solution {
  vector<pair<int, int>> path;
  int sum;
};

bool isValidSolution(vector<pair<int, int>> &path, int N) {
  set<pair<int, int>> visited;
  for (int i = 0; i < N - 1; i++) {
    if (visited.find(path[i]) != visited.end() ||
        path[i].second != path[i + 1].first) {
      return false;
    }
    visited.insert(path[i]);
  }
  return true;
}

void findSumsHelper(int row, int col, int N, vector<vector<int>> &M,
                    vector<pair<int, int>> &currentPath, int currentSum,
                    set<pair<int, int>> &visitedCells,
                    vector<Solution> &allSolutions) {
  if (row >= N) {
    if (isValidSolution(currentPath, N)) {
      allSolutions.push_back({currentPath, currentSum});
    }
    return;
  }

  for (int i = 0; i < N; i++) {
    if (M[row][i] != 0 && visitedCells.find({row, i}) == visitedCells.end()) {
      currentSum += M[row][i];
      currentPath.push_back({row, i});
      visitedCells.insert({row, i});

      findSumsHelper(row + 1, 0, N, M, currentPath, currentSum, visitedCells,
                     allSolutions);

      currentSum -= M[row][i];
      currentPath.pop_back();
      visitedCells.erase({row, i});
    }
  }
}

void printMaxAndMinSolutions(const vector<Solution> &maxSolutions,
                             const vector<Solution> &minSolutions) {
  cout << "Maximized Solutions: " << endl;
  for (auto solution : maxSolutions) {
    cout << "Path: ";
    for (auto p : solution.path) {
      cout << "(" << p.first << "," << p.second << ") ";
    }
    cout << "Sum: " << solution.sum << endl;
  }

  cout << "Minimized Solutions: " << endl;
  for (auto solution : minSolutions) {
    cout << "Path: ";
    for (auto p : solution.path) {
      cout << "(" << p.first << "," << p.second << ") ";
    }
    cout << "Sum: " << solution.sum << endl;
  }
}

vector<Solution> findAllSums(vector<vector<int>> &M) {
  int N = M.size();
  vector<Solution> allSolutions;
  vector<pair<int, int>> currentPath;
  set<pair<int, int>> visitedCells;
  int currentSum = 0;
  findSumsHelper(0, 0, N, M, currentPath, currentSum, visitedCells,
                 allSolutions);
  return allSolutions;
}

// Function to find the maximized solutions
vector<Solution> findMaxSolutions(const vector<Solution> &allSolutions) {
  int maxSum = INT_MIN;
  vector<Solution> maxSolutions;

  for (const auto &solution : allSolutions) {
    if (solution.sum > maxSum) {
      maxSolutions.clear();
      maxSolutions.push_back(solution);
      maxSum = solution.sum;
    } else if (solution.sum == maxSum) {
      maxSolutions.push_back(solution);
    }
  }

  return maxSolutions;
}

// Function to find the minimized solutions
vector<Solution> findMinSolutions(const vector<Solution> &allSolutions) {
  int minSum = INT_MAX;
  vector<Solution> minSolutions;

  for (const auto &solution : allSolutions) {
    if (solution.sum < minSum) {
      minSolutions.clear();
      minSolutions.push_back(solution);
      minSum = solution.sum;
    } else if (solution.sum == minSum) {
      minSolutions.push_back(solution);
    }
  }

  return minSolutions;
}

void testBacktrackingAlgorithm() {
  vector<vector<int>> testMatrix = {{0, 1, 2}, {1, 0, 3}, {2, 3, 0}};

  auto solutions = findAllSums(testMatrix);

  // Test for valid solutions
  for (auto solution : solutions) {
    assert(isValidSolution(solution.path, testMatrix.size()));
    // Test other conditions if required
  }

  // test 2 for
  auto solutions2 = findAllSums(testMatrix);

  for (auto solution : solutions) {
    for (int i = 0; i < solution.path.size() - 1; i++) {
      assert(solution.path[i].second == solution.path[i + 1].first);
    }
  }

  // Add more test cases if needed
}

int main() {
  vector<vector<int>> M = {{0, 7, 1, 0, 0, 8}, {7, 0, 5, 0, 9, 6},
                           {1, 5, 0, 4, 0, 0}, {0, 0, 4, 0, 2, 0},
                           {0, 9, 0, 2, 0, 3}, {8, 6, 0, 0, 3, 0}};

  auto allSolutions = findAllSums(M);

  cout << "All Solutions: " << endl;
  for (auto solution : allSolutions) {
    cout << "Path: ";
    for (auto p : solution.path) {
      cout << "(" << p.first << "," << p.second << ") ";
    }
    cout << "Sum: " << solution.sum << endl;
  }

  auto maxSolutions = findMaxSolutions(allSolutions);
  auto minSolutions = findMinSolutions(allSolutions);
  printMaxAndMinSolutions(maxSolutions, minSolutions);

  try {
    testBacktrackingAlgorithm();
    cout << "tests passed!" << endl;
  } catch (...) {
    cout << "tests failed!" << endl;
  }
  return 0;
}
