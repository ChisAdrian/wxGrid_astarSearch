#ifndef ASTARSEARCH_H_INCLUDED
#define ASTARSEARCH_H_INCLUDED

#include<bits/stdc++.h>
#include <vector>
typedef std::pair<int, int> Pair;
// Creating a shortcut for pair<int, pair<int, int>> type
typedef std::pair<double, std::pair<int, int>> pPair;
typedef std::vector<std::vector<int>> mPath;
// A structure to hold the neccesary parameters
struct cell
{
	// Row and Column index of its parent
	// Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
	int parent_i, parent_j;
	// f = g + h
	double f, g, h;
};
std::vector<std::vector<int>> aStarSearch(std::vector<std::vector<int>> walk_table, Pair src, Pair dest);

#endif // ASTARSEARCH_H_INCLUDED
