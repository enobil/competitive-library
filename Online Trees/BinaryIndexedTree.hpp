#include <cassert>
#include <cstdlib>
#include <cstring>

class BinaryIndexedTree {
	int *_array;
	int _capacity;
public:
	BinaryIndexedTree(int);
	~BinaryIndexedTree();
	int querySum(int);
	int querySumRange(int, int);
	void update(int, int);
};

BinaryIndexedTree::BinaryIndexedTree(int capacity) {
	_capacity = capacity + 2;
	_array = (int*)malloc(sizeof(int) * (_capacity));
	memset(_array, 0, _capacity * sizeof(int));
}

BinaryIndexedTree::~BinaryIndexedTree() {
	free(_array);
}

int BinaryIndexedTree::querySumRange(int l, int r) {
	if (l > 0) {
		return querySum(r) - querySum(l - 1);
	}
	else {
		return querySum(r);
	}
}

int BinaryIndexedTree::querySum(int index)
{
	int sum = 0;

	// index in BITree[] is 1 more than the index in arr[]
	index = index + 1;

	// Traverse ancestors of BITree[index]
	while (index>0){
		// Add current element of BITree to sum
		sum += _array[index];

		// Move index to parent node in getSum View
		index -= index & (-index);
	}
	return sum;
}

void BinaryIndexedTree::update(int index, int val)
{
	// index in BITree[] is 1 more than the index in arr[]
	index = index + 1;

	// Traverse all ancestors and add 'val'
	while (index <= _capacity){
		// Add 'val' to current node of BI Tree
		_array[index] += val;

		// Update index to that of parent in update View
		index += index & (-index);
	}
}

//int *constructBITree(int arr[], int n)
//{
//	// Create and initialize BITree[] as 0
//	int *BITree = new int[n + 1];
//	for (int i = 1; i <= n; i++)
//		BITree[i] = 0;
//
//	// Store the actual values in BITree[] using update()
//	for (int i = 0; i<n; i++)
//		updateBIT(BITree, n, i, arr[i]);
//
//	// Uncomment below lines to see contents of BITree[]
//	//for (int i=1; i<=n; i++)
//	//      cout << BITree[i] << " ";
//
//	return BITree;
//}