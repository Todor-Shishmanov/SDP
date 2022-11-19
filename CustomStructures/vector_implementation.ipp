#ifndef CUSTOM_VECTOR_IMPLEMENTATION_
#define CUSTOM_VECTOR_IMPLEMENTATION_
//namespace sdp{
//	template<typename Type>
//	inline Vector<Type>::Vector():
//	size_(0),
//	capacity_(8)
//	{
//		data_ = new Type[capacity_];
//	}
//	
//	template<typename Type>
//	inline Vector<Type>::Vector(const Type * data_array, size_t size):
//		size_(size),
//		capacity_(size + 8)
//	{
//		data_ = new Type[capacity_];
//		for (size_t i = 0; i < size; ++i) {
//			data_[i] = data_array[i];
//		}
//	}
//
//	template<typename Type>
//	inline Vector<Type>::Vector(const Vector& other):
//		size_(other.size_),
//		capacity_(other.capacity_)
//	{
//		data_ = new Type[capacity_];
//		for (size_t i = 0; i < other.size_; ++i) {
//			data_[i] = other.data_[i];
//		}
//	}
//
//	template<typename Type>
//	inline Vector<Type>::Vector(Vector&& other) noexcept:
//		size_(std::move(other.size_)),
//		capacity_(std::move(other.capacity_)),
//		data_(std::move(other.data_))
//	{
//		other.size_ = 0;
//		other.capacity_ = 0;
//		other.data_ = nullptr;
//	}
//
//	template<typename Type>
//	inline Vector<Type>::~Vector(){
//		// Capacity only because we actually create objects with default constructor
//		for (size_t i = 0; i < capacity_; ++i) {
//			data_[i].~Type();
//		}
//
//		delete[] data_;
//	}
//
//	template<typename Type>
//	inline Vector& Vector<Type>::operator=(const Vector& other)
//	{
//		if (this == &other)
//			return *this;
//
//		size_t temp_size = other.size_;
//		size_t temp_capacity = other.capacity_;
//		Type temp_data = other.data_;
//
//		std::swap(temp_size, size_);
//		std::swap(temp_capacity, capacity_);
//		std::swap(temp_data, data_);
//
//		delete[] temp_data;
//		return *this
//	}
//
//	template<typename Type>
//	inline Vector& Vector<Type>::operator=(Vector&& other) noexcept
//	{
//		return *this;
//	}
//
//	//template<typename Type>
//	//inline Vector<Type>& Vector<Type>::operator=(Vector&& other) noexcept
//	//{
//	//	//// Guard self assignment
//	//	//if (this == &other)
//	//	//	return *this; // delete[]/size=0 would also be ok
//
//	//	//delete[] mArray;                               // release resource in *this
//	//	//mArray = std::exchange(other.mArray, nullptr); // leave other in valid state
//	//	//size = std::exchange(other.size, 0);
//	//	//return *this;
//	//	
//	//}
//
//	template<typename Type>
//	inline void Vector<Type>::insert(const Type&, size_t position)
//	{
//	}
//
//	template<typename Type>
//	inline void Vector<Type>::remove(size_t position)
//	{
//	}
//
//	template<typename Type>
//	inline void Vector<Type>::push_back(const Type&)
//	{
//	}
//
//	template<typename Type>
//	inline Type Vector<Type>::pop_back()
//	{
//		return Type();
//	}
//
//	template<typename Type>
//	inline void Vector<Type>::clear() noexcept
//	{
//	}
//
//	template<typename Type>
//	inline bool Vector<Type>::empty() const noexcept
//	{
//		return size_ == 0;
//	}
//
//	template<typename Type>
//	inline size_t Vector<Type>::size() const noexcept
//	{
//		return size_;
//	}
//
//	template<typename Type>
//	inline size_t Vector<Type>::capacity() const noexcept
//	{
//		return capacity_;
//	}
//
//	template<typename Type>
//	inline void Vector<Type>::resize(size_t new_size)
//	{
//	}
//
//	template<typename Type>
//	inline void Vector<Type>::reserve(size_t new_cap)
//	{
//	}
//
//	template<typename Type>
//	inline void Vector<Type>::shrink(size_t new_cap)
//	{
//	}
//
//	template<typename Type>
//	inline void Vector<Type>::shrink_to_fit()
//	{
//	}
//
//	template<typename Type>
//	inline Type& Vector<Type>::operator[](size_t idx)
//	{
//		return data_[idx];
//	}
//
//	template<typename Type>
//	inline const Type& Vector<Type>::operator[](size_t idx) const
//	{
//		return data_[idx];
//	}
//
//	template<typename Type>
//	inline Type Vector<Type>::at(size_t position)
//	{
//		return Type();
//	}
//
//	template<typename Type>
//	inline Type Vector<Type>::front()
//	{
//		return Type();
//	}
//
//	template<typename Type>
//	inline Type Vector<Type>::back()
//	{
//		return Type();
//	}
//
//	template<typename Type>
//	inline Type* Vector<Type>::data()
//	{
//		return nullptr;
//	}

//} // namespace sdp
#endif // CUSTOM_VECTOR_IMPLEMENTATION_