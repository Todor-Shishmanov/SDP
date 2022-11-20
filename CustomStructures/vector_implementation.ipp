#ifndef CUSTOM_VECTOR_IMPLEMENTATION_
#define CUSTOM_VECTOR_IMPLEMENTATION_
namespace sdp {
	template<typename Type>
	inline Vector<Type>::Vector() :
		size_(0),
		capacity_(8)
	{
		data_ = static_cast<Type*>(::operator new(sizeof(Type) * capacity_));// new operator and operator new are fucking with my brain rn
	}

	template<typename Type>
	inline Vector<Type>::Vector(const Vector<Type>& other) :
		size_(other.size_),
		capacity_(other.capacity_)
	{
		data_ = static_cast<Type*>(::operator new(sizeof(Type) * capacity_));
		for (size_t i = 0; i < size_; ++i) {
			//static_cast<Type*>(data_)[i] = static_cast<Type*>(other.data_)[i]; -> invalid, because the underlying memoty is not initialized yet so operator= wont work.
			new (data_ + i) Type(other.data_[i]);
		}
	}

	template<typename Type>
	inline Vector<Type>::Vector(const Type* arr, const size_t size) :
		size_(size),
		capacity_(size + 8)
	{
		data_ = static_cast<Type*>(::operator new(sizeof(Type) * capacity_));
		for (size_t i = 0; i < size_; ++i) {
			new (data_ + i) Type(arr[i]);
		}
	}

	template<typename Type>
	inline Vector<Type>::Vector(Vector<Type>&& other) noexcept :
		size_(std::move(other.size_)), // Needed std::move?
		capacity_(std::move(other.capacity_)), // Needed std::move?
		data_(std::move(other.data_)) // Needed std::move?
	{
		other.data_ = nullptr;
		other.size_ = 0;
		other.capacity_ = 8;
	}

	template<typename Type>
	inline Vector<Type>::~Vector() noexcept {
		for (size_t i = 0; i < size_; ++i)
			data_[i].~Type();

		operator delete[](data_);
	}

	template<typename Type>
	inline Vector<Type>& Vector<Type>::operator=(const Vector<Type>& other) {
		//Copy&Swap idiom
		Vector<Type> temp(other);
		std::swap(data_, temp.data_);
		std::swap(size_, temp.size_);
		std::swap(capacity_, temp.capacity_);

		return *this;
		// Destructor called for temp
	}

	template<typename Type>
	inline Vector<Type>& Vector<Type>::operator=(Vector<Type>&& other) noexcept {
		size_ = std::move(other.size_);
		capacity_ = std::move(other.capacity_);
		data_ = std::move(other.data_);

		//Other is left in a valid state and other.empty == true
		other.data_ = nullptr;
		other.size_ = 0;
		other.capacity_ = 8;
		return *this;
	}
	
	template<typename Type>
	inline void Vector<Type>::insert(const Type& value, const size_t idx) {
		assert(idx < size_);
		push_back(value);
		for (size_t i = size_ - 1; i > idx; --i)
			std::swap(data_[i - 1], data_[i]);
	}

	template<typename Type>
	inline void Vector<Type>::remove(const size_t idx) {
		assert(idx < size_);
		for (size_t i = idx + 1; i < size_; ++i)
			std::swap(data_[i - 1], data_[i]); // Is manual shifting better?
		data_[size_-- - 1].~Type();
	}

	template<typename Type>
	inline void Vector<Type>::push_back(const Type& value) {
		assert(size_ <= capacity_);
		if (size_ == capacity_)
			reallocate(static_cast<size_t>(capacity_ * 1.5));
		new(data_ + size_++) Type(value);
	}

	template<typename Type>
	inline void Vector<Type>::pop_back() {
		assert(size_ > 0);
		data_[size_-- - 1].~Type();
	}

	template<typename Type>
	inline Type Vector<Type>::pop_back_get() {
		assert(size_ > 0);
		Type temp = data_[size_ - 1];
		data_[size_-- - 1].~Type();
		return temp;
	}

	template<typename Type>
	inline void Vector<Type>::clear() noexcept {
		for (size_t i = 0; i < size_; ++i)
			data_[i].~Type();
		size_ = 0;
	}

	template<typename Type>
	inline void Vector<Type>::resize_up(const size_t new_size) {
		assert(new_size > size_);
		if (new_size > capacity_)
			reallocate(new_size);
		for (size_t i = size_; i < new_size; ++i)
			new(data_ + i) Type();
		size_ = new_size;
	}

	template<typename Type>
	inline void Vector<Type>::resize_down(const size_t new_size) {
		assert(new_size < size_);
		for (size_t i = new_size; i < size_; ++i)
			data_[i].~Type();
		size_ = new_size;
	}

	template<typename Type>
	inline void Vector<Type>::resize(const size_t new_size) {
		if (new_size < size_)
			resize_down(new_size);
		else if (new_size > size_)
			resize_up(new_size);
	}

	template<typename Type>
	inline void Vector<Type>::reserve(const size_t new_cap) {
		if (new_cap <= capacity_)
			return;
		reallocate(new_cap);
	}

	template<typename Type>
	inline void Vector<Type>::shrink(const size_t new_cap) {
		if (new_cap >= capacity_)
			return;
		if (new_cap < size_)
			resize_down(new_cap);
		reallocate(new_cap);
	}

	template<typename Type>
	inline void Vector<Type>::shrink_to_fit() {
		shrink(size_);
	}

	template<typename Type>
	inline void Vector<Type>::reallocate(const size_t new_cap) {
		assert(new_cap >= size_);
		if (new_cap == capacity_)
			return;
		Type* temp = data_;
		data_ = static_cast<Type*>(::operator new(sizeof(Type) * new_cap));

		for (size_t i = 0; i < size_; ++i) {
			new(data_ + i) Type(temp[i]);
			temp[i].~Type();
		}

		capacity_ = new_cap;
	}

	template<typename Type>
	inline Type& Vector<Type>::operator[](const size_t idx) {
		assert(idx < size_);
		return data_[idx];
	}

	template<typename Type>
	inline const Type& Vector<Type>::operator[](const size_t idx) const {
		assert(idx < size_);
		return data_[idx];
	}

	template<typename Type>
	inline Type& Vector<Type>::at(const size_t idx) {
		if (idx >= size_)
			throw std::out_of_range("Trying to access data out of range");
		return data_[idx];
	}

	template<typename Type>
	inline const Type& Vector<Type>::at(const size_t idx) const {
		if (idx >= size_)
			throw std::out_of_range("Trying to access data out of range");
		return data_[idx];
	}

	template<typename Type>
	inline Type& Vector<Type>::front() {
		return operator[](0);
	}

	template<typename Type>
	inline const Type& Vector<Type>::front() const {
		return operator[](0);
	}

	template<typename Type>
	inline Type& Vector<Type>::back() {
		return operator[](size_ - 1);
	}

	template<typename Type>
	inline const Type& Vector<Type>::back() const {
		return operator[](size_ - 1);
	}

} // namespace sdp
#endif // CUSTOM_VECTOR_IMPLEMENTATION_