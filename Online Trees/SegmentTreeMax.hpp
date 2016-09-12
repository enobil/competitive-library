#define SEGMENTTREEMAX_H

#ifndef BITMANIPULATION_H
#include "Bit Manipulation\BitManipulation.hpp"
#endif

class SegmentTreeMax {
	//int _reccnt = 0;
	int *_tree;
	int _capacity;
	int _size;
	void fill(int *arr, int ix, int s, int e);
	static inline int mid(int x, int y) { return x + ((y - x) / 2 ); };
	static inline int left(int x) { return (x * 2) + 1; }
	static inline int right(int x) { return (x * 2) + 2; }
	static inline int max(int x, int y) { return x > y ? x : y; }
	static inline int capacityCalc(int size);
	int search(int s, int e, int treeIx, int treeS, int treeE);
	int update(int pos, int val, int treeIx, int treeS, int treeE);
public:
	//TODO: Use operator overloading [a][b]
	int Get(int s, int e);
	void Update(int pos, int val);
	SegmentTreeMax(int size, int *arr);
	~SegmentTreeMax();
};

int SegmentTreeMax::search(int s, int e, int treeIx, int treeS, int treeE) {
	//_reccnt++;
	//query interval totally includes current recurrence interval
	if (s <= treeS && treeE <= e)
		return _tree[treeIx];
	//query interval and recurrence interval don't intersect
	if (treeS > e || treeE < s)
		return INT_MIN;
	//query interval intersects with current recurrence interval
	return max(
		search(s, e, left(treeIx), treeS, mid(treeS, treeE)),
		search(s, e, right(treeIx), mid(treeS, treeE) + 1, treeE));
}

int SegmentTreeMax::update(int pos, int val, int treeIx, int treeS, int treeE) {
	if (treeS == pos && treeE == pos) {
		_tree[treeIx] = val;
	}
	else if (treeS <= pos && pos <= treeE) {
		update(pos, val, left(treeIx), treeS, mid(treeS, treeE));
		update(pos, val, right(treeIx), mid(treeS, treeE) + 1, treeE);
		_tree[treeIx] = max(_tree[left(treeIx)], _tree[right(treeIx)]);
	}
	return _tree[treeIx];
}

void SegmentTreeMax::Update(int pos, int val) {
	update(pos, val, 0, 0, _size - 1);
}

int SegmentTreeMax::Get(int s, int e) {
	assert(s >= 0 && e < _size);
	//_reccnt = 0;
	int result = search(s, e, 0, 0, _size - 1);
	//std::cout << "reccnt: " << _reccnt << std::endl;
	return result;
}

//void SegmentTreeMax::Print() {
//	for (int i = 0; i < _capacity; i++) {
//		std::cout << _tree[i] << " ";
//	}
//	std::cout << std::endl;
//}

SegmentTreeMax::SegmentTreeMax(int size, int *arr) {
	_capacity = capacityCalc(size);
	_size = size;
	_tree = (int*)malloc(sizeof(int)*(_capacity+1));
	for (int i = 0; i < _capacity; i++)
		_tree[i] = INT_MIN;
	fill(arr, 0, 0, size - 1);
}

void SegmentTreeMax::fill(int *arr, int ix, int s, int e) {
	assert(ix >= 0 && ix < _capacity);
	if (s > e)
		return;
	if (s == e) { //leaf
		_tree[ix] = arr[s];
		return;
	}
	//nonleaf
	fill(arr, left(ix), s, mid(s, e));
	fill(arr, right(ix), mid(s, e) + 1, e);
	_tree[ix] = max(_tree[left(ix)], _tree[right(ix)]);
}

int SegmentTreeMax::capacityCalc(int size) {
	if (count1s(size) == 1)
		return size << 1;
	return 1 << (2 + lg2(size));
}

SegmentTreeMax::~SegmentTreeMax() {
	delete _tree;
}