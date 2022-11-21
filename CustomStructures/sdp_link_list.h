#ifndef CUSTOM_LINKED_LIST_HEADER_
#define CUSTOM_LINKED_LIST_HEADER_
namespace sdp {
	template<typename Type>
	class LinkedList {
	public:
		LinkedList();
		LinkedList(LinkedList&) = delete;
		LinkedList(LinkedList&&) noexcept;
		~LinkedList();
		LinkedList& operator=(const LinkedList& other) = delete;
		LinkedList& operator=(LinkedList&& other);
		
		// Size related
		inline bool empty() const noexcept { return size_ == 0; }
		size_t size() const noexcept { return size_; }

		// Manipulators
		void push_front(const Type&);
		void push_back(const Type&);
		//void insert();
		void pop_back();	// noexcept?
		void pop_front();	// noexcept?
		// void remove();
		void clear();		// noexcept?

	private:
		struct Node {
			Node(const Type& data, Node* next) : data(data), next(next) {}
			Node(Node&& other) = default;

			Type data;
			Node* next;
		};

		Node* start_;
		Node* end_;
		size_t size_; // slight optimization for empty() and size()
	};
}

#include <utility> // swap and move
#include <assert.h>
namespace sdp {
	template<typename Type>
	inline LinkedList<Type>::LinkedList():
		start_(nullptr),
		end_(nullptr),
		size_(0)
	{}

	template<typename Type>
	inline LinkedList<Type>::LinkedList(LinkedList&& other) noexcept:
		start_(std::move(other.start_)),
		end_(std::move(other.end_)),
		size_(other.size_)
	{
		other.start_ = nullptr;
		other.end_ = nullptr;
		other.size_ = 0;
	}

	template<typename Type>
	inline LinkedList<Type>::~LinkedList(){
		clear();
	}

	template<typename Type>
	inline LinkedList<Type>& LinkedList<Type>::operator=(LinkedList&& other){
		if (this == &other)
			return;

		LinkedList temp(std::move(other));
		
		std::swap(size_, other.size_);
		std::swap(start_, other.start_);
		std::swap(end_, other.end_);

		return *this;
		// temp deleted with destructor
	}
	
	template<typename Type>
	inline void LinkedList<Type>::push_front(const Type& value){
		Node* new_element = new Node(value, nullptr);
		if (start_ != nullptr)
			new_element->next = start_->next;
		else {
			assert(start_ == end_);
			end_ = new_element;
		}
		start_ = new_element;
		size_++;
	}
	
	template<typename Type>
	inline void LinkedList<Type>::push_back(const Type& value){
		Node* new_element = new Node(value, nullptr);
		if (end_ != nullptr)
			end_->next = new_element;
		else {
			assert(start_ == end_);
			start_ = new_element;
		}
		end_ = new_element;
		size_++;
	}
	
	template<typename Type>
	inline void LinkedList<Type>::pop_back()
	{
	}
	
	template<typename Type>
	inline void LinkedList<Type>::pop_front()
	{
	}
	
	template<typename Type>
	inline void LinkedList<Type>::clear(){
		while (size_ > 0)
			pop_front();
	}
}
#endif // CUSTOM_LINKED_LIST_HEADER_