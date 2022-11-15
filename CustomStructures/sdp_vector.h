#ifndef CUSTOM_VECTOR_HEADER_
#define CUSTOM_VECTOR_HEADER_
	/*
		Notes on implementation/ areas for improvement:
			- Requires default constructor for the stored class. Can be changed by using a void pointer for data_.
			- Doesn't use iterators.
	*/
namespace sdp {
	
	template<typename Type>
	class Vector {
	public:
		// Big 3/5/many
		Vector();										// Default
		Vector(Type* data_array, size_t size);			// Sorta kinda copy
		Vector(const vector& other);					// Copy
		// Std vector has one without???
		Vector(vector&& other) noexcept;				// Move
		~Vector();										// Destructor
		Type& operator=(const Type& other);				// Assign operator
		Type& operator=(Type&& other) noexcept;			// Move assign operator

		// Element related
		void insert(const Type&, size_t possition);
		void remove(size_t possition);
		void push_back(const Type&);
		void push_front();
		Type pop_back();
		Type pop_front();
		void clear() noexcept;

		// Size related
		bool empty() const noexcept;
		size_t size() const noexcept;
		size_t capacity() const noexcept;
		void resize(size_t new_size); // can be used to delete elements
		void reserve(size_t new_cap); // new_cap > capacity_
		void shrink(size_t new_cap);  // new_cap < capacity_, but new_cap > size_
		void shrink_to_fit();

		// Access related
		Type& operator[](size_t idx);// { return data_[idx]; }
		const Type& operator[](size_t idx) const;// { return data_[idx]; }
		Type at(size_t possition);
		Type front();
		Type back();
		Type* data();

	private:
		size_t capacity_;
		size_t size_;
		Type* data_;
	};
}
#endif // CUSTOM_VECTOR_HEADER_