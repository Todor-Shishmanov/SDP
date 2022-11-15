namespace sdp {
	template<typename Type>
	class Vector {
	public:
		// Element related
		void insert(const T&, size_t possition);
		void remove(size_t possition);
		void push_back(const T&);
		void push_front();
		void clear();

		// Size related
		size_t size() const noexcept;
		size_t capacity() const noexcept;
		void reserve(size_t new_cap);
		void shrink_to_fit();

	private:
		size_t capacity;
		size_t size;

	};
}
