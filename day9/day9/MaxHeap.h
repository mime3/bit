#pragma once
constexpr auto MAXHEAP_SIZE = 100;

template <typename T>
class MaxHeap
{
	T _heap[MAXHEAP_SIZE];
	int _size = 0;

	void Swap(int index1, int index2);
	void UpHeap(int index);
	void DownHeap(int index);
public:
	bool Insert(T data);
	bool Delete(T * data);
};

template<typename T>
inline void MaxHeap<T>::UpHeap(int index)
{
}

template<typename T>
inline void MaxHeap<T>::DownHeap(int index)
{
}

template<typename T>
inline bool MaxHeap<T>::Insert(T data)
{
	if(_size + 1 == MAXHEAP_SIZE)
		return false;

}
