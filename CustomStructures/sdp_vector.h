#ifndef CUSTOM_VECTOR_HEADER_
#define CUSTOM_VECTOR_HEADER_
#include <assert.h>
#include <stdexcept>
	/*
		Notes on implementation/areas for improvement:
			- Requires default constructor for the stored class if resize is used
			- Requires operator= for the stored class.
			- Doesn't use iterators.
	*/
namespace sdp {
	
	template<typename Type>
	class Vector {
		// Big 3/5/many
	public:
		Vector();										// Default
		Vector(const Vector& other);					// Copy
		Vector(const Type* arr, const size_t size);		// Array constructor - Sorta kinda close to copy
		Vector(Vector&& other) noexcept;				// Move, std::vector has one without noexcept???
		~Vector() noexcept;								// Destructor
		Vector& operator=(const Vector& other);			// Assign operator
		Vector& operator=(Vector&& other) noexcept;		// Move assign operator
		
		// Element related
	public:
		void insert(const Type& value, const size_t idx);
		void remove(const size_t idx);					// noexcept ? Technically if it asserts its not exception
		void push_back(const Type& value);				// noexcept ?
		void pop_back();								// noexcept ?
		Type pop_back_get();							// noexcept ?
		void clear() noexcept;

		// Size related
	public:
		inline bool empty() const noexcept { return size_ == 0; }
		inline size_t size() const noexcept { return size_; }
		inline size_t capacity() const noexcept { return capacity_; }
	private:
		void resize_up(const size_t new_size);
		void resize_down(const size_t new_size);
	public:
		void resize(const size_t new_size);
		void reserve(const size_t new_cap);				// new_cap > capacity_
		void shrink(const size_t new_cap);				// new_cap < capacity_
		void shrink_to_fit();
	private:
		void reallocate(size_t new_cap);				// new_cap >= size_

		// Access related
	public:
		inline Type* data() const noexcept { return data_; }
		Type& operator[](const size_t idx);
		const Type& operator[](const size_t idx) const;	// noexcept ?
		Type& at(const size_t idx);
		const Type& at(const size_t idx) const;
		Type& front();									//should we allow vec.front() = x?
		const Type& front() const;
		Type& back();									// same question as with front()
		const Type& back() const;

	private:
		size_t capacity_;
		size_t size_;
		Type* data_;
	};
} // namespace sdp
#include "vector_implementation.ipp"
#endif // CUSTOM_VECTOR_HEADER_