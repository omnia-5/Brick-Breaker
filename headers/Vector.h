#ifndef Vector_H
#define Vector_H

namespace sp {
	template <typename Type>
	struct Vector {
	private:
		Type* buffer; // Dynamic array of Type witch we spicify when we intialze the array
		unsigned int _maxSize; // _maxSize is the total storage
		unsigned int _size; // _size is the number of elements currently present in the buffer
		typedef Type* iterator;
	public:
		// Default constructor to initialise an initial _maxSize of 1 element and allocating storage using dynamic allocation
		Vector();

		// constructor with intinal size
		Vector(unsigned int size);

		// constructor with intinal size and default value
		Vector(unsigned int size, const Type& initial);

		// constructor that copies another Vector
		Vector(const Vector<Type>& v);

		// Default destructor to clear the buffer after we stop using it 
		~Vector();

		// function to add element at last index
		void push_back(Type data);

		// function to add element at any index
		void push_back(Type data, int index);

		// function to delete last element
		void pop_back();

		// function to delete element by Index
		void erase(int index);

		// function to clear the array
		void clear();

		// function to get the first element in the Vector 
		Type& front();

		// function to get the last element in the Vector 
		Type& back();

		iterator begin();
		iterator end();

		// function to get size of the array
		unsigned int size();

		// function to get Max Size of the array
		unsigned int maxSize();

		// Subscripting [] Operator Overloading to be able to to call Vector[index]
		Type& operator[](int index);

		// Equal = Operator Overloading to be able to to call Vector1=Vector2
		Vector<Type>& operator=(const Vector<Type>& v);

	};

	template <class Type>
	sp::Vector<Type>::Vector() :_maxSize(1), _size(0) {
		this->buffer = new Type[1];
	};

	template <class Type>
	sp::Vector<Type>::Vector(unsigned int size) :_maxSize(size), _size(size) {
		this->buffer = new Type[size];
	};

	template <class Type>
	sp::Vector<Type>::Vector(unsigned int size, const Type& initial) :_maxSize(size), _size(size) {
		this->buffer = new Type[size];
		for (unsigned int i = 0; i < size; i++)
			this->buffer[i] = initial;
	};

	template <class Type>
	sp::Vector<Type>::Vector(const sp::Vector<Type>& v) {
		this->_size = v._size;
		this->_maxSize = v._maxSize;
		this->buffer = new Type[this->_size];
		for (unsigned int i = 0; i < this->_size; i++)
			this->buffer[i] = v.buffer[i];
	};

	template <class Type>
	sp::Vector<Type>::~Vector() {
		delete[] this->buffer;
	};

	template <class Type>
	void sp::Vector<Type>::push_back(Type data) {
		/* if the number of elements is equal to the _maxSize, that means we don't have space to
		allocate more elements. so that means We need to increase the capacity
		*/
		if (this->_size == this->_maxSize) {
			Type* temp = new Type[(unsigned int)2 * this->_maxSize];

			// copying old array elements to new array
			for (unsigned int i = 0; i < this->_maxSize; i++)
				temp[i] = this->buffer[i];

			// deleting previous buffer
			delete[] this->buffer;
			this->_maxSize *= (unsigned int)2;
			this->buffer = temp;
		}
		// Inserting data
		this->buffer[_size] = data;
		this->_size++;
	};

	template <class Type>
	void sp::Vector<Type>::push_back(Type data, int index) {
		// if index is equal to _maxSize then we have to do the process in the function above
		if (index == this->_maxSize)
			this->push_back(data);
		else
			this->buffer[index] = data;
	};

	template <class Type>
	void sp::Vector<Type>::pop_back() {
		this->_size--;
	};

	template <class Type>
	void sp::Vector<Type>::erase(int index) {
		for (unsigned int i = 0; i < this->_size; i++) {
			if (i == index) {
				for (; i < this->_size - 1; i++)
					this->buffer[i] = this->buffer[i + 1]; // Assign the next element to current location. 
				this->buffer[this->_size - 1] = 0; // Remove the last element as it has been moved to previous index.
				this->_size--;
			}
		}
	};

	template <class Type>
	void sp::Vector<Type>::clear() {
		this->_maxSize = 1;
		this->_size = 0;
		delete[] this->buffer;
		this->buffer = new Type[this->_maxSize];
	};

	template <class Type>
	Type& sp::Vector<Type>::front() {
		return this->buffer[0];
	}

	template <class Type>
	Type& sp::Vector<Type>::back() {
		return this->buffer[this->_size - 1];
	}

	template <class Type>
	typename sp::Vector<Type>::iterator sp::Vector<Type>::begin() {
		return this->buffer;
	}

	template <class Type>
	typename sp::Vector<Type>::iterator Vector<Type>::end() {
		return this->buffer + this->size();
	}

	template <class Type>
	unsigned int sp::Vector<Type>::size() {
		return this->_size;
	};

	template <class Type>
	unsigned int sp::Vector<Type>::maxSize() {
		return this->_maxSize;
	};

	template <class Type>
	Type& sp::Vector<Type>::operator[](int index) {
		return this->buffer[index];
	};

	template <class Type>
	sp::Vector<Type>& sp::Vector<Type>::operator=(const sp::Vector<Type>& v) {
		delete[] this->buffer;
		this->_size = v._size;
		this->_maxSize = v._maxSize;
		this->buffer = new Type[this->_size];
		for (unsigned int i = 0; i < this->_size; i++)
			this->buffer[i] = v.buffer[i];
		return *this;
	};
}

#endif // !Vector_H