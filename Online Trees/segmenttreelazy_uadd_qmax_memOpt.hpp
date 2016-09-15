#define SEGMENTTREEMAX_H

#ifndef BITMANIPULATION_H
#include "Bit Manipulation\BitManipulation.hpp"
#endif

#define mid(x, y) ((x) + (((y) - (x)) / 2))
#define left(x) (((x) * 2) + 1)
#define right(x) (((x) * 2) + 2)

#include <unordered_map>

class SegmentTreeMax {
	std::unordered_map<int, long long> _tree;
	std::unordered_map<int, long long> _lazy;
	int _size;
	//static inline int mid(int x, int y) { return x + ((y - x) / 2); };
	//static inline int left(int x) { return (x * 2) + 1; }
	//static inline int right(int x) { return (x * 2) + 2; }
	static inline int max(int x, int y) { return x > y ? x : y; }
	long long queryMax(int s, int e, int treeIx, int treeS, int treeE);
	void updateAdd(int s, int e, long long valToAdd, int treeIx, int treeS, int treeE);
public:
	//TODO: Use operator overloading [a][b]
	long long Query_Max(int s, int e);
	void Update_Add(int s, int e, long long valToAdd);
	SegmentTreeMax(int size, long long *arr);
};

long long SegmentTreeMax::queryMax (int s, int e, int treeIx, int treeS, int treeE) {
	if (_lazy.find(treeIx) != _lazy.end() && _lazy[treeIx] != 0) {
		_tree[treeIx] = _lazy[treeIx];

		if (treeS != treeE) {
			_lazy[left(treeIx)] = _lazy[treeIx];
			_lazy[right(treeIx)] = _lazy[treeIx];
		}

		_lazy[treeIx] = 0;
	}

	if (treeS > treeE || treeS > e || treeE < s)
		return INT_MIN;

	if (treeS >= s && treeE <= e) {
		return _tree.find(treeIx) == _tree.end() ? 0 : _tree[treeIx];
	}

	int md = mid(treeS, treeE);
	return max(
		queryMax(s, e, left(treeIx), treeS, md),
		queryMax(s, e, right(treeIx), md + 1, treeE));
}

void SegmentTreeMax::updateAdd(int s, int e, long long valToAdd, int treeIx, int treeS, int treeE) {
	if (_lazy.find(treeIx) != _lazy.end() &&  _lazy[treeIx] != 0) {
		if (_tree.find(treeIx) == _tree.end()) {
			_tree[treeIx] = _lazy[treeIx];
		}
		else {
			_tree[treeIx] += _lazy[treeIx];
		}

		if (treeS != treeE) {
			if (_lazy.find(left(treeIx)) == _lazy.end()) {
				_lazy[left(treeIx)] = _lazy[treeIx];
			}
			else {
				_lazy[left(treeIx)] += _lazy[treeIx];
			}
			if (_lazy.find(right(treeIx)) == _lazy.end()) {
				_lazy[right(treeIx)] = _lazy[treeIx];
			}
			else {
				_lazy[right(treeIx)] += _lazy[treeIx];
			}
		}
		_lazy[treeIx] = 0;
	}

	if (treeS > treeE || treeS > e || treeE < s)
		return;

	if (treeS >= s && treeE <= e) {
		_tree[treeIx] += valToAdd;

		if (treeS != treeE) {
			_lazy[left(treeIx)] += valToAdd;
			_lazy[right(treeIx)] += valToAdd;
		}
		return;
	}

	int md = mid(treeS, treeE);
	updateAdd(s, e, valToAdd, left(treeIx), treeS, md);
	updateAdd(s, e, valToAdd, right(treeIx), md + 1, treeE);

	_tree[treeIx] = max(
		_tree[left(treeIx)],
		_tree[right(treeIx)]);
}

void SegmentTreeMax::Update_Add(int s, int e, long long valToAdd) {
	updateAdd(s, e, valToAdd, 0, 0, _size - 1);
}

long long SegmentTreeMax::Query_Max(int s, int e) {
	long long result = queryMax(s, e, 0, 0, _size - 1);
	return result;
}

SegmentTreeMax::SegmentTreeMax(int size, long long *arr) {
	_size = size;
}