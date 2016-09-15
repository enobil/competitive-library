#include <cassert>

class KeyedMinHeap
{
private:
	long long *_heapKey;
	long long *_heapValue;
	int *_lookupKey;
	int _capacity;
	int _size = 0;

	void BubbleDown(int internalIndex);
	void BubbleUp(int internalIndex);

	inline static int left(int x) { return x * 2 + 1; }
	inline static int right(int x) { return x * 2 + 2; }
	inline static int parent(int x) { return (x - 1) / 2; }

public:
	KeyedMinHeap(int capacity);

	void Insert(int key, long long value);
	long long PeekMinValue();
	int PeekMinKey();
	void PopMin();
	void DecreaseKey(int key, long long value);
	void DecreaseOrInsertKey(int key, long long value);
	bool IsEmpty() { return _size == 0; }
	int Size() { return _size; }
};

void KeyedMinHeap::DecreaseOrInsertKey(int key, long long value) {
	if (_lookupKey[key] != -1) {
		DecreaseKey(key, value);
	}
	else {
		Insert(key, value);
	}
}

void KeyedMinHeap::DecreaseKey(int key, long long value) {
	assert(key <= _capacity + 1);
	int index = _lookupKey[key];
	_heapValue[index] = value;

	BubbleUp(index);
}

KeyedMinHeap::KeyedMinHeap(int capacity)
{
	_capacity = capacity;
	_heapKey = (long long *)malloc(sizeof(long long) * (_capacity + 2));
	_heapValue = (long long *)malloc(sizeof(long long) * (_capacity + 2));
	_lookupKey = (int *)malloc(sizeof(int) * (_capacity + 2));
	for (int i = 0; i <= _capacity + 1; i++) {
		_lookupKey[i] = -1;
	}
}

void KeyedMinHeap::BubbleDown(int internalIndex)
{
	int leftChildIndex = left(internalIndex);
	int rightChildIndex = right(internalIndex);

	if (leftChildIndex >= _size)
		return; //index is a leaf

	int minIndex = internalIndex;

	if (_heapValue[internalIndex] > _heapValue[leftChildIndex])
	{
		minIndex = leftChildIndex;
	}

	if ((rightChildIndex < _size) && (_heapValue[minIndex] > _heapValue[rightChildIndex]))
	{
		minIndex = rightChildIndex;
	}

	if (minIndex != internalIndex)
	{
		//TODO: Try using swap() built-in function
		//need to swap
		long long tempValue = _heapValue[internalIndex];
		_heapValue[internalIndex] = _heapValue[minIndex];
		_heapValue[minIndex] = tempValue;

		int tempKey = _heapKey[internalIndex];
		_heapKey[internalIndex] = _heapKey[minIndex];
		_heapKey[minIndex] = tempKey;

		int oldKey = _heapKey[internalIndex];
		int newKey = _heapKey[minIndex];
		int tempIndex = _lookupKey[oldKey];
		_lookupKey[oldKey] = _lookupKey[newKey];
		_lookupKey[newKey] = tempIndex;

		BubbleDown(minIndex);
	}
}

void KeyedMinHeap::BubbleUp(int internalIndex)
{
	if (internalIndex == 0)
		return; //reached to top

	int parentIndex = parent(internalIndex);

	if (_heapValue[parentIndex] > _heapValue[internalIndex])
	{
		long long tempValue = _heapValue[internalIndex];
		_heapValue[internalIndex] = _heapValue[parentIndex];
		_heapValue[parentIndex] = tempValue;

		int tempKey = _heapKey[internalIndex];
		_heapKey[internalIndex] = _heapKey[parentIndex];
		_heapKey[parentIndex] = tempKey;

		int oldKey = _heapKey[internalIndex];
		int newKey = _heapKey[parentIndex];
		int tempIndex = _lookupKey[oldKey];
		_lookupKey[oldKey] = _lookupKey[newKey];
		_lookupKey[newKey] = tempIndex;

		BubbleUp(parentIndex);
	}
}

void KeyedMinHeap::Insert(int key, long long value)
{
	assert(_size <= _capacity);
	
	_heapKey[_size] = key;
	_heapValue[_size] = value;
	_lookupKey[key] = _size;
	_size++; // NOT SURE

	BubbleUp(_size - 1);
}

long long KeyedMinHeap::PeekMinValue()
{
	assert(_size > 0);
	return _heapValue[0];
}

int KeyedMinHeap::PeekMinKey()
{
	assert(_size > 0);
	return _heapKey[0];
}

void KeyedMinHeap::PopMin()
{
	assert(_size > 0);

	_lookupKey[_heapKey[0]] = -1;
	_heapKey[0] = _heapKey[_size - 1];
	_heapValue[0] = _heapValue[_size - 1];	
	_lookupKey[_heapKey[0]] = 0;

	_size--;

	BubbleDown(0);
}
