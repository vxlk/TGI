#pragma once

/*
Alphabetically sorted vector

Since the typed command list will be searched (potentially) many times a second 
(every chat message starting with !), need an efficient way to look up whether a 
term is in the list or not, hence binary search with an automatically updated alphabetically 
sorted vector
*/
///NEEDS TESTING

template <class T>
class tgiVector
{
public:
	tgiVector(int _size = 4)
	{
		size = _size;
		minimumSize = _size;
		contents = new T[_size];
	}

	~tgiVector()
	{
		size = 0;
		delete[] contents;
	}

	void push_back(T toBeAdded)
	{
		++currentPos;
		if (currentPos == size / 2)
			resize();
	}

	void pop(T toBeSubtracted)
	{
		--currentPos;
		if (currentPos == size / 3)
			resizeSubtract();

		int index = containsAtIndex(toBeSubtracted);
		if (index == -1) return;
		else
			while (++index < size)
				contents[index - 1] = contents[index];
	}

	bool contains(T toBeSearchedFor)
	{
		int l = 0;
		int r = size - 1;
		int m = 0;

		while (l <= r)
		{
			m = ((l + r) / 2);
			if (contents[m] < toBeSearchedFor)
				l = m + 1;
			else if (contents[m] > toBeSearchedFor)
				r = m - 1;
			else return true;
		}
		return false;
	}

	int containsAtIndex(T toBeSearchedFor)
	{
		int l = 0;
		int r = size - 1;
		int m = 0;

		while (l <= r)
		{
			m = ((l + r) / 2);
			if (contents[m] < toBeSearchedFor)
				l = m + 1;
			else if (contents[m] > toBeSearchedFor)
				r = m - 1;
			else return m;
		}
		return -1;
	}

	/* Does not exist in the array */
	const static int npos = -1;
private:

	/* Comparator for sort function */
	int cmpr(T* a, T* b)
	{
		if (*b > *a)
			return -1;
		if (*b < *a)
			return 1;
		return 0;
	}

	void resizeSubtract()
	{
		int newSize = (size / 2);
		T* temp = new T[newSize];

		for (int i = currentPos; i >= 0; --i)
			temp[i] = contents[i];

		contents = temp;
		delete[] contents;
	}

	void resizeAdd()
	{
		int newSize = (size * 2);
		T* temp = new T[newSize];

		for (int i = 0; i < size; ++i)
			temp[i] = contents[i];

		contents = temp;
		delete[] contents;
	}

	void sort()
	{
		std::qsort(contents, size, sizeof(T), cmpr);
	}

	T* contents;
	int size;
	int minimumSize;
	int currentPos;
};
