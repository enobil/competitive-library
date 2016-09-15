#define SEGMENTTREEMAX_H

#ifndef BITMANIPULATION_H
#include "Bit Manipulation\BitManipulation.hpp"
#endif

#define mid(x, y) ((x) + (((y) - (x)) / 2))
#define left(x) (((x) * 2) + 1)
#define right(x) (((x) * 2) + 2)
#define max(x, y) ((x) > (y) ? (x) : (y))

template <class T>
class SegmentTreeMax {
	T *_tree;
	T *_lazy;
	int _capacity;
	int _size;
	void fill(T *arr, int ix, int s, int e);
	//static inline int mid(int x, int y) { return x + ((y - x) / 2); };
	//static inline int left(int x) { return (x * 2) + 1; }
	//static inline int right(int x) { return (x * 2) + 2; }
	//static inline int max(int x, int y) { return x > y ? x : y; }
	static inline int capacityCalc(int size);
	T queryMax(int s, int e, int treeIx, int treeS, int treeE);
	void updateAdd(int s, int e, T valToAdd, int treeIx, int treeS, int treeE);
public:
	//TODO: Use operator overloading [a][b]
	T Query_Max(int s, int e);
	void Update_Add(int s, int e, T valToAdd);
	SegmentTreeMax(int size, T *arr);
	~SegmentTreeMax();
};

template <class T>
T SegmentTreeMax<T>::queryMax (int s, int e, int treeIx, int treeS, int treeE) {
	if (_lazy[treeIx] != 0) {
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
		return _tree[treeIx];
	}

	int md = mid(treeS, treeE);
	return max(
		queryMax(s, e, left(treeIx), treeS, md),
		queryMax(s, e, right(treeIx), md + 1, treeE));
}

template <class T>
void SegmentTreeMax<T>::updateAdd(int s, int e, T valToAdd, int treeIx, int treeS, int treeE) {
	if (_lazy[treeIx] != 0) {
		_tree[treeIx] += _lazy[treeIx];

		if (treeS != treeE) {
			_lazy[left(treeIx)] += _lazy[treeIx];
			_lazy[right(treeIx)] += _lazy[treeIx];
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

	_tree[treeIx] = max(_tree[left(treeIx)], _tree[right(treeIx)]);
}

template <class T>
void SegmentTreeMax<T>::Update_Add(int s, int e, T valToAdd) {
	updateAdd(s, e, valToAdd, 0, 0, _size - 1);
}

template <class T>
T SegmentTreeMax<T>::Query_Max(int s, int e) {
	T result = queryMax(s, e, 0, 0, _size - 1);
	return result;
}

template <class T>
SegmentTreeMax<T>::SegmentTreeMax(int size, T *arr) {
	_capacity = capacityCalc(size);
	_size = size;
	_tree = (T*)malloc(sizeof(T)*(_capacity + 1));
	_lazy = (T*)malloc(sizeof(T)*(_capacity + 1));
	memset(_lazy, 0, sizeof(T)*(_capacity + 1));
	if (sizeof(T) == sizeof(long long))
		for (int i = 0; i < _capacity; i++)
			_tree[i] = LLONG_MIN;
	else if (sizeof(T) == sizeof(long))
		for (int i = 0; i < _capacity; i++)
			_tree[i] = LONG_MIN;
	else if(sizeof(T) == sizeof(int))
		for (int i = 0; i < _capacity; i++)
			_tree[i] = INT_MIN;
	this->fill(arr, 0, 0, size - 1);
}

template <class T>
void SegmentTreeMax<T>::fill(T *arr, int ix, int s, int e) {
	assert(ix >= 0 && ix < _capacity);
	if (s > e)
		return;
	if (s == e) { //leaf
		_tree[ix] = arr[s];
		return;
	}
	//nonleaf
	int md = mid(s, e);
	fill(arr, left(ix), s, md);
	fill(arr, right(ix), md + 1, e);
	_tree[ix] = max(_tree[left(ix)], _tree[right(ix)]);
}

template <class T>
int SegmentTreeMax<T>::capacityCalc(int size) {
	if (count1s(size) == 1)
		return size << 1;
	return 1 << (2 + lg2(size));
}

template <class T>
SegmentTreeMax<T>::~SegmentTreeMax() {
	free(_tree);
	free(_lazy);
}