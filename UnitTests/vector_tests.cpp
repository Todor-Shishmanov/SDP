#include "CppUnitTest.h"
#include "../CustomStructures/sdp_vector.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace sdp;

namespace CustomVector
{
	struct Person {
		Person() : name("Smith"), age(30) {}
		Person(std::string name_arg, int age_arg) : name(name_arg), age(age_arg) {}
		std::string name;
		int age;
	};

	TEST_CLASS(Big5)
	{
	public:

		TEST_METHOD(DefaultConstructorInt)
		{
			//Arrange + Act
			Vector<int> v_int;

			// Assert
			Assert::IsTrue(v_int.empty(), L"Vector with integer not empty after default constructor");
			Assert::AreEqual(static_cast<size_t>(0), v_int.size(), L"Vector with integer has size different than 0 after default constructor");
			Assert::AreEqual(static_cast<size_t>(8), v_int.capacity(), L"Vector with integer has capacity different than 8 after default constructor");
		}

		TEST_METHOD(DefaultConstructorChar)
		{
			//Arrange + Act
			Vector<char> v_char;

			// Assert
			Assert::IsTrue(v_char.empty(), L"Vector with character not empty after default constructor");
			Assert::AreEqual(static_cast<size_t>(0), v_char.size(), L"Vector with character has size different than 0 after default constructor");
			Assert::AreEqual(static_cast<size_t>(8), v_char.capacity(), L"Vector with character has capacity different than 8 after default constructor");
		}

		TEST_METHOD(DefaultConstructorPerson)
		{
			//Arrange + Act
			Vector<Person> v_person;

			// Assert
			Assert::IsTrue(v_person.empty(), L"Vector with Person not empty after default constructor");
			Assert::AreEqual(static_cast<size_t>(0), v_person.size(), L"Vector with Person struct has size different than 0 after default constructor");
			Assert::AreEqual(static_cast<size_t>(8), v_person.capacity(), L"Vector with Person struct has capacity different than 8 after default constructor");
		}

		TEST_METHOD(ArrayConstructorInt)
		{
			// Arrange
			int arr[1000];
			for (unsigned i = 0; i < 1000; ++i)
				arr[i] = i;
			
			// Act
			Vector<int> v(arr, 1000);
			int* v_data = v.data();

			// Assert
			Assert::AreEqual(static_cast<size_t>(1000), v.size(), L"Vector's size doesn't match");
			Assert::AreEqual(static_cast<size_t>(1008), v.capacity(), L"Vector's capacity doesn't match");
			for (unsigned i = 0; i < 1000; ++i)
				Assert::AreEqual(arr[i], v_data[i], L"Vector's elements don't match");
		}

		TEST_METHOD(ArrayConstructorChar)
		{
			// Arrange
			char arr[1000];
			for (unsigned i = 0; i < 1000; ++i)
				arr[i] = i % 100; // 0...99
				
			// Act
			Vector<char> v(arr, 1000);
			char* v_data = v.data();

			// Assert
			Assert::AreEqual(static_cast<size_t>(1000), v.size(), L"Vector's size doesn't match");
			Assert::AreEqual(static_cast<size_t>(1008), v.capacity(), L"Vector's capacity doesn't match");
			for (unsigned i = 0; i < 1000; ++i)
				Assert::AreEqual(arr[i], v_data[i], L"Vector's elements don't match");
		}

		TEST_METHOD(ArrayConstructorPerson)
		{
			// Arrange
			Person arr[100];
			for (unsigned i = 0; i < 100; ++i) {
				arr[i].name = "smth" + std::to_string(i);
				arr[i].age = i;
			}

			// Act
			Vector<Person> v(arr, 100);
			Person* v_data = v.data();

			// Assert
			Assert::AreEqual(static_cast<size_t>(100), v.size(), L"Vector's size doesn't match");
			Assert::AreEqual(static_cast<size_t>(108), v.capacity(), L"Vector's capacity doesn't match");
			for (unsigned i = 0; i < 100; ++i) {
				Assert::AreEqual(arr[i].name, v_data[i].name, L"Vector's elements name don't match");
				Assert::AreEqual(arr[i].age, v_data[i].age, L"Vector's elements age don't match");
			}
				
		}

		TEST_METHOD(CopyConstructorInt)
		{
			// Arrange
			Vector<int> v_int;
			for (unsigned i = 0; i < 100; ++i)
				v_int.push_back(i);

			// Act
			Vector<int> v_copy_int(v_int);
			int* int_data = v_int.data();
			int* copy_int_data = v_copy_int.data();

			// Assert
			Assert::AreEqual(v_int.capacity(), v_copy_int.capacity(), L"Capacity of v_int and v_copy_int are different");
			Assert::AreEqual(v_int.size(), v_copy_int.size(), L"Sizes of v_int and v_copy_int are different");
			for (unsigned i = 0; i < 100; ++i)
				Assert::AreEqual(int_data[i], copy_int_data[i], L"Values of v_int and v_copy_int are different");
		}

		TEST_METHOD(CopyConstructorChar)
		{
			// Arrange
			Vector<char> v_char;
			for (unsigned char i = 0; i < 255; ++i)
				v_char.push_back(i);

			// Act
			Vector<char> v_copy_char(v_char);
			char* copy_char_data = v_copy_char.data();
			char* char_data = v_char.data();

			// Assert
			Assert::AreEqual(v_char.capacity(), v_copy_char.capacity(), L"Capacity of v_char and v_copy_char are different");
			Assert::AreEqual(v_char.size(), v_copy_char.size(), L"Sizes of v_char and v_copy_char are different");
			for (unsigned char i = 0; i < 255; ++i)
				Assert::AreEqual(v_char[i], v_copy_char[i], L"Values of v_char and v_copy_char are different");
		}

		TEST_METHOD(CopyConstructorPerson)
		{
			// Arrange
			Vector<Person> v_person;
			for (int i = 0; i < 100; ++i)
				v_person.push_back(Person("someone", i));

			// Act
			Vector<Person> v_copy_person(v_person);
			Person* copy_person_data = v_copy_person.data();
			Person* person_data = v_person.data();

			// Assert
			Assert::AreEqual(v_person.capacity(), v_copy_person.capacity(), L"Capacity of v_person and v_copy_person are different");
			Assert::AreEqual(v_person.size(), v_copy_person.size(), L"Sizes of v_person and v_copy_person are different");
			for (unsigned i = 0; i < 100; ++i) {
				Assert::AreEqual(v_person[i].name, v_copy_person[i].name, L"Values of v_person.name and v_copy_person.name are different");
				Assert::AreEqual(v_person[i].age, v_copy_person[i].age, L"Values of v_person.age and v_copy_person.age are different");
			}
		}

		TEST_METHOD(MoveConstructorInt)
		{
			// Arrange
			int arr[3] = { 3, 5, 2 };

			//Act
			Vector<int> vec(Vector<int>(arr, 3));
			int* vec_data = vec.data();

			//Assert
			for (size_t i = 0; i < vec.size(); ++i)
				Assert::AreEqual(arr[i], vec_data[i]);
		}

		TEST_METHOD(MoveConstructorChar)
		{
			// Arrange
			char arr[3] = { 'a', 'b', 'c' };

			//Act
			Vector<char> vec(Vector<char>(arr, 3));
			char* vec_data = vec.data();

			//Assert
			for (size_t i = 0; i < vec.size(); ++i)
				Assert::AreEqual(arr[i], vec_data[i]);
		}

		TEST_METHOD(MoveConstructorPerson)
		{
			// Arrange
			Person alice("alice", 15);
			Person lilia("lilia", 140);
			Person michael("michael", 4);

			Person arr[3] = { alice, lilia, michael };

			//Act
			Vector<Person> vec(Vector<Person>(arr, 3));
			Person* vec_data = vec.data();

			//Assert
			for (size_t i = 0; i < vec.size(); ++i) {
				Assert::AreEqual(arr[i].name, vec_data[i].name);
				Assert::AreEqual(arr[i].age, vec_data[i].age);
			}
		}

		TEST_METHOD(CopyAssignOperatorsInt)
		{
			// Arrange
			Vector<int> vec;
			Vector<int> vec_other;
			vec_other.push_back(6);
			vec_other.push_back(5);
			vec_other.push_back(8);

			// Act
			vec = vec_other; // Copy assign

			// Assert
			Assert::AreEqual(static_cast<size_t>(3), vec.size(), L"Vector not empty");
			Assert::AreEqual(6, vec[0]);
			Assert::AreEqual(5, vec[1]);
			Assert::AreEqual(8, vec[2]);
		}

		TEST_METHOD(MoveAssignOperatorsInt)
		{
			// Arrange
			int data[3] = { 5, 2, 10 };
			Vector<int> vec;

			// Act
			vec = Vector<int>(data, 3); // Move assign

			// Assert
			Assert::AreEqual(static_cast<size_t>(3), vec.size(), L"Vector not empty");
			Assert::AreEqual(5, vec[0]);
			Assert::AreEqual(2, vec[1]);
			Assert::AreEqual(10, vec[2]);
		}

		TEST_METHOD(CopyAssignOperatorChar)
		{
			// Arrange
			Vector<char> vec;
			Vector<char> vec_other;
			vec_other.push_back('a');
			vec_other.push_back('a');
			vec_other.push_back('c');

			// Act
			vec = vec_other; // Copy assign

			// Assert
			Assert::AreEqual(static_cast<size_t>(3), vec.size(), L"Vector not empty");
			Assert::AreEqual('a', vec[0]);
			Assert::AreEqual('a', vec[1]);
			Assert::AreEqual('c', vec[2]);
		}

		TEST_METHOD(MoveAssignOperatorChar)
		{
			// Arrange
			char data[3] = { 'a', 'b', 'c' };
			Vector<char> vec;

			// Act
			vec = Vector<char>(data, 3); // Move assign

			// Assert
			Assert::AreEqual(static_cast<size_t>(3), vec.size(), L"Vector not empty");
			Assert::AreEqual('a', vec[0]);
			Assert::AreEqual('b', vec[1]);
			Assert::AreEqual('c', vec[2]);
		}

		TEST_METHOD(CopyAssignOperatorPerson)
		{
			// Arrange
			Vector<Person> vec;
			Vector<Person> vec_other;
			Person linda("Linda", 5);
			Person max("Max", 10);
			Person jojo("jojo", 1);
			vec_other.push_back(linda);
			vec_other.push_back(max);
			vec_other.push_back(jojo);

			// Act
			vec = vec_other; // Copy assign

			// Assert
			Assert::AreEqual(static_cast<size_t>(3), vec.size(), L"Vector not empty");
			Assert::AreEqual(linda.name, vec[0].name);
			Assert::AreEqual(linda.age, vec[0].age);
			Assert::AreEqual(max.name, vec[1].name);
			Assert::AreEqual(max.age, vec[1].age);
			Assert::AreEqual(jojo.name, vec[2].name);
			Assert::AreEqual(jojo.age, vec[2].age);
		}

		TEST_METHOD(MoveAssignOperatorPerson)
		{
			// Arrange
			Person mimi("Mimi", 12);
			Person han("Han", 1234);
			Person mini("Mini", 0);
			Person data[3] = { mimi, han, mini };
			Vector<Person> vec;

			// Act
			vec = Vector<Person>(data, 3); // Move assign

			// Assert
			Assert::AreEqual(static_cast<size_t>(3), vec.size(), L"Vector not empty");
			Assert::AreEqual(mimi.name, vec[0].name);
			Assert::AreEqual(mimi.age, vec[0].age);
			Assert::AreEqual(han.name, vec[1].name);
			Assert::AreEqual(han.age, vec[1].age);
			Assert::AreEqual(mini.name, vec[2].name);
			Assert::AreEqual(mini.age, vec[2].age);
		}
	};

	TEST_CLASS(AccessRelatedFunctions) {
	public:
		TEST_METHOD(DataGetterInt)
		{
			// Arrange
			int data[1000];
			for (unsigned i = 0; i < 1000; ++i)
				data[i] = i;
			const Vector<int> v(data, 1000);

			// Act + Assert
			for (unsigned i = 0; i < 1000; ++i)
				Assert::AreEqual(data[i], v.data()[i]);
		}

		TEST_METHOD(DataGetterChar)
		{
			// Arrange
			char data[1000];
			for (unsigned i = 0; i < 1000; ++i)
				data[i] = i % 120;
			Vector<char> v(data, 1000);

			// Act + Assert
			for (unsigned i = 0; i < 1000; ++i)
				Assert::AreEqual(data[i], v.data()[i]);
		}

		TEST_METHOD(DataGetterPerson)
		{
			// Arrange
			Person data[100];
			for (unsigned i = 0; i < 100; ++i) {
				data[i].name = std::to_string(i);
				data[i].age = i + 1;
			}

			Vector<Person> v(data, 100);

			// Act + Assert
			for (unsigned i = 0; i < 100; ++i) {
				Assert::AreEqual(data[i].name, v.data()[i].name);
				Assert::AreEqual(data[i].age, v.data()[i].age);
			}
		}

		TEST_METHOD(DataGetterEmpty)
		{
			Vector<Person> v;
			Assert::IsTrue(v.data()); // v.data() != nullptr
		}

		TEST_METHOD(RandomAccessOperatorInt)
		{
			// Arrange
			int data[1000];
			for (unsigned i = 0; i < 1000; ++i)
				data[i] = i;
			Vector<int> v(data, 1000);

			// Act + Assert
			for (unsigned i = 0; i < 1000; ++i)
				Assert::AreEqual(data[i], v[i]);
		}

		TEST_METHOD(RandomAccessOperatorChar)
		{
			// Arrange
			char data[1000];
			for (unsigned i = 0; i < 1000; ++i)
				data[i] = i%120;
			Vector<char> v(data, 1000);

			// Act + Assert
			for (unsigned i = 0; i < 1000; ++i)
				Assert::AreEqual(data[i], v[i]);
		}

		TEST_METHOD(RandomAccessOperatorPerson)
		{
			// Arrange
			Person data[100];
			for (unsigned i = 0; i < 100; ++i) {
				data[i].name = std::to_string(i);
				data[i].age = i + 1;
			}
				
			Vector<Person> v(data, 100);

			// Act + Assert
			for (unsigned i = 0; i < 100; ++i) {
				Assert::AreEqual(data[i].name, v[i].name);
				Assert::AreEqual(data[i].age, v[i].age);
			}
		}
		
		TEST_METHOD(ConstRandomAccessOperatorInt)
		{
			// Arrange
			int data[1000];
			for (unsigned i = 0; i < 1000; ++i)
				data[i] = i;
			const Vector<int> v(data, 1000);

			// Act + Assert
			for (unsigned i = 0; i < 1000; ++i)
				Assert::AreEqual(data[i], v[i]);
		}

		TEST_METHOD(ConstRandomAccessOperatorChar)
		{
			// Arrange
			char data[1000];
			for (unsigned i = 0; i < 1000; ++i)
				data[i] = i % 120;
			const Vector<char> v(data, 1000);

			// Act + Assert
			for (unsigned i = 0; i < 1000; ++i)
				Assert::AreEqual(data[i], v[i]);
		}

		TEST_METHOD(ConstRandomAccessOperatorPerson)
		{
			// Arrange
			Person data[100];
			for (unsigned i = 0; i < 100; ++i) {
				data[i].name = std::to_string(i);
				data[i].age = i + 1;
			}

			const Vector<Person> v(data, 100);

			// Act + Assert
			for (unsigned i = 0; i < 100; ++i) {
				Assert::AreEqual(data[i].name, v[i].name);
				Assert::AreEqual(data[i].age, v[i].age);
			}
		}
		
		TEST_METHOD(AtNoThrowInt)
		{
			// Arrange
			int data[1000];
			for (unsigned i = 0; i < 1000; ++i)
				data[i] = i;
			Vector<int> v(data, 1000);

			// Act + Assert
			for (unsigned i = 0; i < 1000; ++i)
				Assert::AreEqual(data[i], v.at(i));
		}

		TEST_METHOD(AtNoThrowChar)
		{
			// Arrange
			char data[1000];
			for (unsigned i = 0; i < 1000; ++i)
				data[i] = i % 120;
			Vector<char> v(data, 1000);

			// Act + Assert
			for (unsigned i = 0; i < 1000; ++i)
				Assert::AreEqual(data[i], v.at(i));
		}

		TEST_METHOD(AtNoThrowPerson)
		{
			// Arrange
			Person data[100];
			for (unsigned i = 0; i < 100; ++i) {
				data[i].name = std::to_string(i);
				data[i].age = i + 1;
			}

			Vector<Person> v(data, 100);

			// Act + Assert
			for (unsigned i = 0; i < 100; ++i) {
				Assert::AreEqual(data[i].name, v.at(i).name);
				Assert::AreEqual(data[i].age, v.at(i).age);
			}
		}

		TEST_METHOD(ConstAtNoThrowInt)
		{
			// Arrange
			int data[1000];
			for (unsigned i = 0; i < 1000; ++i)
				data[i] = i;
			const Vector<int> v(data, 1000);

			// Act + Assert
			for (unsigned i = 0; i < 1000; ++i)
				Assert::AreEqual(data[i], v.at(i));
		}

		TEST_METHOD(ConstAtNoThrowChar)
		{
			// Arrange
			char data[1000];
			for (unsigned i = 0; i < 1000; ++i)
				data[i] = i % 120;
			const Vector<char> v(data, 1000);

			// Act + Assert
			for (unsigned i = 0; i < 1000; ++i)
				Assert::AreEqual(data[i], v.at(i));
		}

		TEST_METHOD(ConstAtNoThrowPerson)
		{
			// Arrange
			Person data[100];
			for (unsigned i = 0; i < 100; ++i) {
				data[i].name = std::to_string(i);
				data[i].age = i + 1;
			}

			const Vector<Person> v(data, 100);

			// Act + Assert
			for (unsigned i = 0; i < 100; ++i) {
				Assert::AreEqual(data[i].name, v.at(i).name);
				Assert::AreEqual(data[i].age, v.at(i).age);
			}
		}

		TEST_METHOD(AtThrow)
		{
			// Arrange
			int data[10];
			Vector<int> v(data, 10);

			// Act + Assert
			try {
				v.at(100);
			}
			catch (std::out_of_range&) {
				return;
			}	
			catch (...) {
				Assert::Fail(L"Wrong exception thrown");
			}

			Assert::Fail(L"No exception thrown");
		}

		TEST_METHOD(AtThrowEmpty)
		{
			// Arrange
			Vector<Person> v;

			// Act + Assert
			try {
				v.at(0);
			}
			catch (std::out_of_range&) {
				return;
			}
			catch (...) {
				Assert::Fail(L"Wrong exception thrown");
			}

			Assert::Fail(L"No exception thrown");
		}
		
		TEST_METHOD(FrontInt)
		{
			// Arrange
			int data[10];
			for (unsigned i = 0; i < 10; ++i)
				data[i] = i;
			Vector<int> v(data, 10);

			// Act
			v.front() = 5;

			// Assert
			Assert::AreEqual(5, v.front());
			Assert::AreEqual(v.data()[0], v.front());
		}

		TEST_METHOD(FrontChar)
		{
			// Arrange
			char data[10];
			for (unsigned i = 0; i < 10; ++i)
				data[i] = i;
			Vector<char> v(data, 10);

			// Act
			v.front() = 'b';

			// Assert
			Assert::AreEqual('b', v.front());
			Assert::AreEqual(v.data()[0], v.front());
		}

		TEST_METHOD(FrontPerson)
		{
			// Arrange
			Person data[10];
			for (unsigned i = 0; i < 10; ++i) {
				data[i].name = std::to_string(i);
				data[i].age = i + 1;
			}
			Vector<Person> v(data, 10);

			// Act
			v.front().name = "b";
			v.front().age = 51;

			// Assert
			std::string name = "b";
			Assert::AreEqual(name, v.front().name);
			Assert::AreEqual(51, v.front().age);
			Assert::AreEqual(v.data()[0].name, v.front().name);
			Assert::AreEqual(v.data()[0].age, v.front().age);
		}

		TEST_METHOD(ConstFrontInt)
		{
			// Arrange
			int data[10];
			for (unsigned i = 0; i < 10; ++i)
				data[i] = i;
			const Vector<int> v(data, 10);

			// Act + Assert
			Assert::AreEqual(data[0], v.front());
			Assert::AreEqual(v.data()[0], v.front());
		}

		TEST_METHOD(ConstFrontChar)
		{
			// Arrange
			char data[10];
			for (unsigned i = 0; i < 10; ++i)
				data[i] = i;
			const Vector<char> v(data, 10);

			// Act + Assert
			Assert::AreEqual(data[0], v.front());
			Assert::AreEqual(v.data()[0], v.front());
		}

		TEST_METHOD(ConstFrontPerson)
		{
			// Arrange
			Person data[10];
			for (unsigned i = 0; i < 10; ++i) {
				data[i].name = std::to_string(i);
				data[i].age = i + 1;
			}
			const Vector<Person> v(data, 10);

			// Act + Assert
			Assert::AreEqual(data[0].name, v.front().name);
			Assert::AreEqual(data[0].age, v.front().age);
			Assert::AreEqual(v.data()[0].name, v.front().name);
			Assert::AreEqual(v.data()[0].age, v.front().age);
		}

		TEST_METHOD(BackInt)
		{
			// Arrange
			int data[10];
			for (unsigned i = 0; i < 10; ++i)
				data[i] = i;
			Vector<int> v(data, 10);

			// Act
			v.back() = 15;

			// Assert
			Assert::AreEqual(15, v.back());
			Assert::AreEqual(v.data()[9], v.back());
		}

		TEST_METHOD(BackChar)
		{
			// Arrange
			char data[10];
			for (unsigned i = 0; i < 10; ++i)
				data[i] = i;
			Vector<char> v(data, 10);

			// Act
			v.back() = 'v';

			// Assert
			Assert::AreEqual('v', v.back());
			Assert::AreEqual(v.data()[9], v.back());
		}

		TEST_METHOD(BackPerson)
		{
			// Arrange
			Person data[10];
			for (unsigned i = 0; i < 10; ++i) {
				data[i].name = std::to_string(i);
				data[i].age = i + 1;
			}
			Vector<Person> v(data, 10);

			// Act
			v.back().name = "asd";
			v.back().age = 51;

			// Assert
			std::string name = "asd";
			Assert::AreEqual(name, v.back().name);
			Assert::AreEqual(51, v.back().age);
			Assert::AreEqual(v.data()[9].name, v.back().name);
			Assert::AreEqual(v.data()[9].age, v.back().age);
		}

		TEST_METHOD(ConstBackInt)
		{
			// Arrange
			int data[10];
			for (unsigned i = 0; i < 10; ++i)
				data[i] = i;
			const Vector<int> v(data, 10);

			// Act + Assert
			Assert::AreEqual(data[9], v.back());
			Assert::AreEqual(v.data()[9], v.back());
		}

		TEST_METHOD(ConstBackChar)
		{
			// Arrange
			char data[10];
			for (unsigned i = 0; i < 10; ++i)
				data[i] = i;
			const Vector<char> v(data, 10);

			// Act + Assert
			Assert::AreEqual(data[9], v.back());
			Assert::AreEqual(v.data()[9], v.back());
		}

		TEST_METHOD(ConstBackPerson)
		{
			// Arrange
			Person data[10];
			for (unsigned i = 0; i < 10; ++i) {
				data[i].name = std::to_string(i);
				data[i].age = i + 1;
			}
			const Vector<Person> v(data, 10);

			// Act + Assert
			Assert::AreEqual(data[9].name, v.back().name);
			Assert::AreEqual(data[9].age, v.back().age);
			Assert::AreEqual(v.data()[9].name, v.back().name);
			Assert::AreEqual(v.data()[9].age, v.back().age);
		}
	};

	TEST_CLASS(ElementRelatedFunctions) {
	public:
		TEST_METHOD(PushBackInt) {
			// Arrange
			Vector<int> v_int;

			// Act
			for (int i = 0; i < 100; i++)
				v_int.push_back(i);
			int* int_data = v_int.data();

			// Assert
			for (size_t i = 0; i < v_int.size(); ++i)
				Assert::AreEqual(static_cast<int>(i), int_data[i], L"After push_back in the integer vector the values aren't equal to the expected.");
		}

		TEST_METHOD(PushBackChar) {
			// Arrange
			Vector<char> v_char;

			// Act
			for (unsigned char c = 0; c < 255; ++c)
				v_char.push_back(c);
			char* char_data = v_char.data();

			// Assert
			for (size_t i = 0; i < v_char.size(); ++i)
				Assert::AreEqual(static_cast<char>(i), char_data[i], L"After push_back in the char vector the values aren't equal to the expected.");
		}

		TEST_METHOD(PushBackPerson) {
			// Arrange
			Vector<Person> v_person;
			Person adam("adam", 4);
			Person nini("nini", 15);
			Person haskel("haskel", 402);
			Person humini("humini", 53);

			// Act
			v_person.push_back(adam);
			v_person.push_back(nini);
			v_person.push_back(haskel);
			v_person.push_back(humini);
			Person* person_data = v_person.data();

			// Assert
			Assert::AreEqual(static_cast<size_t>(4), v_person.size(), L"Vector not empty");
			Assert::AreEqual(adam.name, person_data[0].name, L"After push_back in the person vector the name of element 0 doesn't match.");
			Assert::AreEqual(adam.age, person_data[0].age, L"After push_back in the person vector the age of element 0 doesn't match.");
			Assert::AreEqual(nini.name, person_data[1].name, L"After push_back in the person vector the name of element 1 doesn't match.");
			Assert::AreEqual(nini.age, person_data[1].age, L"After push_back in the person vector the age of element 1 doesn't match.");
			Assert::AreEqual(haskel.name, person_data[2].name, L"After push_back in the person vector the name of element 2 doesn't match.");
			Assert::AreEqual(haskel.age, person_data[2].age, L"After push_back in the person vector the age of element 2 doesn't match.");
			Assert::AreEqual(humini.name, person_data[3].name, L"After push_back in the person vector the name of element 3 doesn't match.");
			Assert::AreEqual(humini.age, person_data[3].age, L"After push_back in the person vector the age of element 3 doesn't match.");
		}

		TEST_METHOD(InsertInt)
		{
			// Arrange
			Vector<int> v_int;
			v_int.push_back(5); // 5
			v_int.push_back(4); // 54
			v_int.push_back(3); // 543

			// Act
			v_int.insert(2, 1); // 5243

			// Assert
			Assert::AreEqual(static_cast<size_t>(4), v_int.size(), L"Vector not empty");
			Assert::AreEqual(5, v_int[0]);
			Assert::AreEqual(2, v_int[1]);
			Assert::AreEqual(4, v_int[2]);
			Assert::AreEqual(3, v_int[3]);
		}

		TEST_METHOD(InsertChar)
		{
			// Arrange
			Vector<char> v_char;
			v_char.push_back('a'); // a
			v_char.push_back('b'); // ab
			v_char.push_back('c'); // abc

			// Act
			v_char.insert('d', 1); // adbc

			// Assert
			Assert::AreEqual(static_cast<size_t>(4), v_char.size(), L"Vector not empty");
			Assert::AreEqual('a', v_char[0]);
			Assert::AreEqual('d', v_char[1]);
			Assert::AreEqual('b', v_char[2]);
			Assert::AreEqual('c', v_char[3]);
		}

		TEST_METHOD(InsertPerson)
		{
			// Arrange
			Vector<Person> v_person;
			Person one("one", 1);
			Person two("two", 2);
			Person three("three", 3);
			Person four("four", 4);

			v_person.push_back(one); // one
			v_person.push_back(two); // one two
			v_person.push_back(three); // one two three

			// Act
			v_person.insert(four, 1); // one four two three

			// Assert
			Assert::AreEqual(static_cast<size_t>(4), v_person.size(), L"Vector not empty");
			Assert::AreEqual(one.name, v_person[0].name);
			Assert::AreEqual(one.age, v_person[0].age);
			Assert::AreEqual(four.name, v_person[1].name);
			Assert::AreEqual(four.age, v_person[1].age);
			Assert::AreEqual(two.name, v_person[2].name);
			Assert::AreEqual(two.age, v_person[2].age);
			Assert::AreEqual(three.name, v_person[3].name);
			Assert::AreEqual(three.age, v_person[3].age);
		}

		TEST_METHOD(RemoveInt)
		{
			// Arrange
			Vector<int> v_int;
			v_int.push_back(5);
			v_int.push_back(2);
			v_int.push_back(4);
			v_int.push_back(3); // 5243

			v_int.remove(0);

			Assert::AreEqual(static_cast<size_t>(3), v_int.size(), L"Vector not empty");
			Assert::AreEqual(2, v_int[0]);
			Assert::AreEqual(4, v_int[1]);
			Assert::AreEqual(3, v_int[2]);
		}

		TEST_METHOD(RemoveChar)
		{
			// Arrange
			Vector<char> v_char;
			v_char.push_back('a');
			v_char.push_back('d');
			v_char.push_back('b');
			v_char.push_back('c'); // adbc

			// Act
			v_char.remove(1);

			// Assert
			Assert::AreEqual(static_cast<size_t>(3), v_char.size(), L"Vector not empty");
			Assert::AreEqual('a', v_char[0]);
			Assert::AreEqual('b', v_char[1]);
			Assert::AreEqual('c', v_char[2]);
		}

		TEST_METHOD(RemovePerson)
		{
			// Arrange
			Vector<Person> v_person;
			Person one("one", 1);
			Person two("two", 2);
			Person three("three", 3);
			Person four("four", 4);

			v_person.push_back(one);
			v_person.push_back(four);
			v_person.push_back(two);
			v_person.push_back(three); // one four two three

			// Act
			v_person.remove(2);

			// Assert
			Assert::AreEqual(static_cast<size_t>(3), v_person.size(), L"Vector not empty");
			Assert::AreEqual(one.name, v_person[0].name);
			Assert::AreEqual(one.age, v_person[0].age);
			Assert::AreEqual(four.name, v_person[1].name);
			Assert::AreEqual(four.age, v_person[1].age);
			Assert::AreEqual(three.name, v_person[2].name);
			Assert::AreEqual(three.age, v_person[2].age);
		}

		TEST_METHOD(PopBackInt) 
		{
			// Arrange
			int data[1000];
			for (unsigned i = 0; i < 1000; i++)
				data[i] = i;
			Vector<int> v(data, 1000);

			// Act
			size_t size = v.size();
			for (size_t i = 0; i < size; ++i)
				v.pop_back();

			// Assert
			Assert::AreEqual(static_cast<size_t>(0), v.size(), L"Vector not empty");
		}

		TEST_METHOD(PopBackChar)
		{
			// Arrange
			char data[1000];
			for (unsigned i = 0; i < 1000; ++i)
				data[i] = i%100;
			Vector<char> v(data, 1000);

			// Act
			size_t size = v.size();
			for (size_t i = 0; i < size; ++i)
				v.pop_back();

			// Assert
			Assert::AreEqual(static_cast<size_t>(0), v.size(), L"Vector not empty");
		}

		TEST_METHOD(PopBackPerson)
		{
			// Arrange
			Person data[100];
			for (unsigned i = 0; i < 100; ++i) {
				data[i].name = "smth" + std::to_string(i);
				data[i].age = i;
			}
			Vector<Person> v(data, 100);

			// Act
			size_t size = v.size();
			for (size_t i = 0; i < size; ++i)
				v.pop_back();

			// Assert
			Assert::AreEqual(static_cast<size_t>(0), v.size(), L"Vector not empty");
		}

		TEST_METHOD(PopBackGetInt)
		{
			// Arrange
			int data[1000];
			int data_get[1000];
			for (unsigned i = 0; i < 1000; i++)
				data[i] = i;
			Vector<int> v(data, 1000);

			// Act
			size_t size = v.size();
			for (size_t i = 0; i < size; ++i)
				data_get[i] = v.pop_back_get();

			// Assert
			Assert::AreEqual(static_cast<size_t>(0), v.size(), L"Vector not empty");
			for (unsigned i = 0; i < size; ++i)
				Assert::AreEqual(data[i], data_get[size - i - 1], L"Vector elemets that were poped don't match the original");
		}

		TEST_METHOD(PopBackGetChar)
		{
			// Arrange
			char data[1000];
			char data_get[1000];
			for (unsigned i = 0; i < 1000; ++i)
				data[i] = i % 100;
			Vector<char> v(data, 1000);

			// Act
			size_t size = v.size();
			for (size_t i = 0; i < size; ++i)
				data_get[i] = v.pop_back_get();

			// Assert
			Assert::AreEqual(static_cast<size_t>(0), v.size(), L"Vector not empty");
			for (unsigned i = 0; i < size; ++i)
				Assert::AreEqual(data[i], data_get[size - i - 1], L"Vector elemets that were poped don't match the original");
		}

		TEST_METHOD(PopBackGetPerson)
		{
			// Arrange
			Person data[100];
			Person data_get[100];
			for (unsigned i = 0; i < 100; ++i) {
				data[i].name = "smth" + std::to_string(i);
				data[i].age = i;
			}
			Vector<Person> v(data, 100);

			// Act
			size_t size = v.size();
			for (size_t i = 0; i < size; ++i)
				data_get[i] = v.pop_back_get();

			// Assert
			Assert::AreEqual(static_cast<size_t>(0), v.size(), L"Vector not empty");
			for (unsigned i = 0; i < size; ++i) {
				Assert::AreEqual(data[i].name, data_get[size - i - 1].name, L"Vector elemets that were poped don't match the original");
				Assert::AreEqual(data[i].age, data_get[size - i - 1].age, L"Vector elemets that were poped don't match the original");
			}
				
		}

		TEST_METHOD(ClearInt)
		{
			// Arrange
			int data[1000];
			for (unsigned i = 0; i < 1000; i++)
				data[i] = i;
			Vector<int> v(data, 1000);

			// Act
			v.clear();

			// Assert
			Assert::AreEqual(static_cast<size_t>(0), v.size());
		}

		TEST_METHOD(ClearChar)
		{
			// Arrange
			char data[1000];
			for (unsigned i = 0; i < 1000; ++i)
				data[i] = i % 100;
			Vector<char> v(data, 1000);

			// Act
			v.clear();

			// Assert
			Assert::AreEqual(static_cast<size_t>(0), v.size());
		}

		TEST_METHOD(ClearPerson)
		{
			// Arrange
			Person data[100];
			for (unsigned i = 0; i < 100; ++i) {
				data[i].name = "smth" + std::to_string(i);
				data[i].age = i;
			}
			Vector<Person> v(data, 100);

			// Act
			v.clear();

			// Assert
			Assert::AreEqual(static_cast<size_t>(0), v.size());
		}
		
		// Old test, but no reason to remove it
		TEST_METHOD(PushAndPopBackGetInt) {
			// Arrange
			Vector<int> v_int;

			// Act
			v_int.push_back(5);
			int int_poped = v_int.pop_back_get();

			// Assert
			Assert::AreEqual(5, int_poped);
			Assert::IsTrue(v_int.empty());
			Assert::AreEqual(static_cast<size_t>(8), v_int.capacity());
		}

		// Old test, but no reason to remove it
		TEST_METHOD(PushAndPopBackGetChar) {
			// Arrange
			Vector<char> v_char;

			// Act
			v_char.push_back('a');
			char char_poped = v_char.pop_back_get();

			//Assert
			Assert::AreEqual('a', char_poped);
			Assert::IsTrue(v_char.empty());
			Assert::AreEqual(static_cast<size_t>(8), v_char.capacity());
		}

		// Old test, but no reason to remove it
		TEST_METHOD(PushAndPopBackGetPerson)
		{
			// Arrange
			Vector<Person> v_person;
			Person luci("luci", 5);

			// Act
			v_person.push_back(luci);
			Person person_poped = v_person.pop_back_get();

			// Assert
			Assert::AreEqual(luci.name, person_poped.name);
			Assert::AreEqual(luci.age, person_poped.age);
			Assert::IsTrue(v_person.empty());
			Assert::AreEqual(static_cast<size_t>(8), v_person.capacity());
		}
	};

	TEST_CLASS(SizeRelatedFunctions) {
	public:
		// This method isn't template related
		TEST_METHOD(Empty)
		{
			// Arrange
			Vector<Person> v;
			Person data[1] = { Person("Linda", 3) };
			Vector<Person> v2(data, 1);

			// Act + Assert
			Assert::IsTrue(v.empty());
			Assert::IsFalse(v2.empty());
		}
		
		TEST_METHOD(ResizeUpInt)
		{
			// Arrange
			int data[3] = { 1, 3, 2 };
			Vector<int> v(data, 3);

			// Act
			v.resize(10);
			int* v_data = v.data();

			// Assert
			Assert::AreEqual(static_cast<size_t>(10), v.size(), L"Size doesn't match");
			Assert::AreEqual(1, v_data[0], L"First old element changed");
			Assert::AreEqual(3, v_data[1], L"Second old element changed");
			Assert::AreEqual(2, v_data[2], L"Third old element changed");
			for (unsigned i = 3; i < 10; ++i)
				Assert::AreEqual(0, v_data[i], L"Not filled with default elements");
		}

		TEST_METHOD(ResizeUpChar)
		{
			// Arrange
			char data[3] = { 'a', 'd', 'h'};
			Vector<char> v(data, 3);

			// Act
			v.resize(10);
			char* v_data = v.data();

			// Assert
			Assert::AreEqual(static_cast<size_t>(10), v.size(), L"Size doesn't match");
			Assert::AreEqual('a', v_data[0], L"First old element changed");
			Assert::AreEqual('d', v_data[1], L"Second old element changed");
			Assert::AreEqual('h', v_data[2], L"Third old element changed");
			for (unsigned i = 3; i < 10; ++i)
				Assert::AreEqual(static_cast<char>(0), v_data[i], L"Not filled with default elements");
		}

		TEST_METHOD(ResizeUpPerson)
		{
			// Arrange
			Person data[3] = { Person("a", 5), Person("h", 2), Person("asd", 531) };
			Vector<Person> v(data, 3);

			// Act
			v.resize(10);
			Person* v_data = v.data();

			// Assert
			Assert::AreEqual(static_cast<size_t>(10), v.size(), L"Size doesn't match");
			Assert::AreEqual(data[0].name, v_data[0].name, L"First old element changed");
			Assert::AreEqual(data[0].age, v_data[0].age, L"First old element changed");
			Assert::AreEqual(data[1].name, v_data[1].name, L"Second old element changed");
			Assert::AreEqual(data[1].age, v_data[1].age, L"Second old element changed");
			Assert::AreEqual(data[2].name, v_data[2].name, L"Third old element changed");
			Assert::AreEqual(data[2].age, v_data[2].age, L"Third old element changed");
			Person normal;
			for (unsigned i = 3; i < 10; ++i) {
				Assert::AreEqual(normal.name, v_data[i].name, L"Not filled with default elements");
				Assert::AreEqual(normal.age, v_data[i].age, L"Not filled with default elements");
			}
				
		}
		
		TEST_METHOD(ResizeDownInt)
		{
			// Arrange
			const int data[10] = { 123, 33, 245, 2, 1, 4, 2 };
			Vector<int> v(data, 10);

			// Act
			v.resize(4);
			int* v_data = v.data();

			// Assert
			Assert::AreEqual(static_cast<size_t>(4), v.size(), L"Size doesn't match");
			Assert::AreEqual(data[0], v_data[0], L"First old element changed");
			Assert::AreEqual(data[1], v_data[1], L"Second old element changed");
			Assert::AreEqual(data[2], v_data[2], L"Third old element changed");
			Assert::AreEqual(data[3], v_data[3], L"Forth old element changed");
		}

		TEST_METHOD(ResizeDownChar)
		{
			// Arrange
			const char data[10] = { 'a', '2', '4', '/', '%', 'a', '2' };
			Vector<char> v(data, 10);

			// Act
			v.resize(4);
			char* v_data = v.data();

			// Assert
			Assert::AreEqual(static_cast<size_t>(4), v.size(), L"Size doesn't match");
			Assert::AreEqual(data[0], v_data[0], L"First old element changed");
			Assert::AreEqual(data[1], v_data[1], L"Second old element changed");
			Assert::AreEqual(data[2], v_data[2], L"Third old element changed");
			Assert::AreEqual(data[3], v_data[3], L"Forth old element changed");
		}

		TEST_METHOD(ResizeDownPerson)
		{
			// Arrange
			const Person data[10] = { Person("a", 5), Person("h", 2), Person("asd", 531), Person("hhaha", 5) };
			Vector<Person> v(data, 10);

			// Act
			v.resize(4);
			Person* v_data = v.data();

			// Assert
			Assert::AreEqual(static_cast<size_t>(4), v.size(), L"Size doesn't match");
			Assert::AreEqual(data[0].name, v_data[0].name, L"First old element changed");
			Assert::AreEqual(data[0].age, v_data[0].age, L"First old element changed");
			Assert::AreEqual(data[1].name, v_data[1].name, L"Second old element changed");
			Assert::AreEqual(data[1].age, v_data[1].age, L"Second old element changed");
			Assert::AreEqual(data[2].name, v_data[2].name, L"Third old element changed");
			Assert::AreEqual(data[2].age, v_data[2].age, L"Third old element changed");
			Assert::AreEqual(data[3].name, v_data[3].name, L"Forth old element changed");
			Assert::AreEqual(data[3].age, v_data[3].age, L"Forth old element changed");
		}

		// Shouldn't reach a templated call
		TEST_METHOD(ReserveDown)
		{
			// Arrange
			const int data[10] = { 123, 33, 245, 2, 1, 4, 2 };
			Vector<int> v(data, 10);
			size_t old_cap = v.capacity();

			// Act
			v.reserve(2);
			size_t new_cap = v.capacity();
			int* v_data = v.data();

			// Assert
			Assert::AreEqual(old_cap, new_cap, L"Capacity changed");
			for (unsigned i = 0; i < 10; ++i)
				Assert::AreEqual(data[i], v_data[i], L"Elements changed");
		}

		TEST_METHOD(ReserveUpInt)
		{
			// Arrange
			const int data[10] = { 123, 33, 245, 2, 1, 4, 2 };
			Vector<int> v(data, 10);

			// Act
			v.reserve(100);
			size_t new_cap = v.capacity();
			int* v_data = v.data();

			// Assert
			Assert::AreEqual(static_cast<size_t>(100), new_cap, L"Capacity not changed");
			for (unsigned i = 0; i < 10; ++i)
				Assert::AreEqual(data[i], v_data[i], L"Elements changed");
		}

		TEST_METHOD(ReserveUpChar)
		{
			// Arrange
			const char data[10] = { 'a', 'b', 'c', 'd', 'e'};
			Vector<char> v(data, 10);

			// Act
			v.reserve(100);
			size_t new_cap = v.capacity();
			char* v_data = v.data();

			// Assert
			Assert::AreEqual(static_cast<size_t>(100), new_cap, L"Capacity not changed");
			for (unsigned i = 0; i < 10; ++i)
				Assert::AreEqual(data[i], v_data[i], L"Elements changed");
		}

		TEST_METHOD(ReserveUpPerson)
		{
			// Arrange
			const Person data[10] = { Person("a", 5), Person("h", 2), Person("ad", 531), Person("lmao", 5) };
			Vector<Person> v(data, 10);

			// Act
			v.reserve(100);
			size_t new_cap = v.capacity();
			Person* v_data = v.data();

			// Assert
			Assert::AreEqual(static_cast<size_t>(100), new_cap, L"Capacity not changed");
			for (unsigned i = 0; i < 10; ++i) {
				Assert::AreEqual(data[i].name, v_data[i].name, L"Elements changed");
				Assert::AreEqual(data[i].age, v_data[i].age, L"Elements changed");
			}		
		}
		
		TEST_METHOD(ShrinkUpInt)
		{
			// Arrange
			const int data[10] = { 123, 33, 245, 2, 1, 4, 2 };
			Vector<int> v(data, 10);
			size_t old_cap = v.capacity();

			// Act
			v.shrink(100);
			size_t new_cap = v.capacity();
			int* v_data = v.data();

			// Assert
			Assert::AreEqual(old_cap, new_cap, L"Capacity changed");
			for (unsigned i = 0; i < 10; ++i)
				Assert::AreEqual(data[i], v_data[i], L"Elements changed");
		}

		TEST_METHOD(ShrinkDownInt)
		{
			// Arrange
			const int data[10] = { 123, 33, 245, 2, 1, 4, 2 };
			Vector<int> v(data, 10);

			// Act
			v.shrink(5);
			size_t new_cap = v.capacity();
			int* v_data = v.data();

			// Assert
			Assert::AreEqual(static_cast<size_t>(5), new_cap, L"Capacity not changed");
			for (unsigned i = 0; i < 5; ++i)
				Assert::AreEqual(data[i], v_data[i], L"Elements changed");
		}

		TEST_METHOD(ShrinkDownChar)
		{
			// Arrange
			const char data[10] = { 'a', 'b', 'c', 'd', 'e' };
			Vector<char> v(data, 10);

			// Act
			v.shrink(5);
			size_t new_cap = v.capacity();
			char* v_data = v.data();

			// Assert
			Assert::AreEqual(static_cast<size_t>(5), new_cap, L"Capacity not changed");
			for (unsigned i = 0; i < 5; ++i)
				Assert::AreEqual(data[i], v_data[i], L"Elements changed");
		}

		TEST_METHOD(ShrinkDownPerson)
		{
			// Arrange
			const Person data[10] = { Person("a", 5), Person("h", 2), Person("asd", 531), Person("hhaha", 5), Person("ha", 52), Person("aha", 51) };
			Vector<Person> v(data, 10);

			// Act
			v.shrink(5);
			size_t new_cap = v.capacity();
			Person* v_data = v.data();

			// Assert
			Assert::AreEqual(static_cast<size_t>(5), new_cap, L"Capacity not changed");
			for (unsigned i = 0; i < 5; ++i) {
				Assert::AreEqual(data[i].name, v_data[i].name, L"Elements changed");
				Assert::AreEqual(data[i].age, v_data[i].age, L"Elements changed");
			}
		}
		
		TEST_METHOD(ShrinkToFitInt)
		{
			// Arrange
			const int data[10] = { 123, 33, 245, 2, 1, 4, 2 };
			Vector<int> v(data, 10);

			// Act
			v.shrink_to_fit();
			int* v_data = v.data();

			// Assert
			Assert::AreEqual(v.size(), v.capacity(), L"Capacity not equal to size");
			for (unsigned i = 0; i < 10; ++i)
				Assert::AreEqual(data[i], v_data[i], L"Elements changed");
		}

		TEST_METHOD(ShrinkToFitChar)
		{
			// Arrange
			const char data[10] = { '/', 'g', 'c', 'h', '4' };
			Vector<char> v(data, 10);

			// Act
			v.shrink_to_fit();
			char* v_data = v.data();

			// Assert
			Assert::AreEqual(v.size(), v.capacity(), L"Capacity not equal to size");
			for (unsigned i = 0; i < 10; ++i)
				Assert::AreEqual(data[i], v_data[i], L"Elements changed");
		}

		TEST_METHOD(ShrinkToFitPerson)
		{
			// Arrange
			const Person data[10] = { Person("a", 5), Person("h", 2), Person("asd", 531), Person("hhaha", 5), Person("ha", 52), Person("aha", 51) };
			Vector<Person> v(data, 10);

			// Act
			v.shrink_to_fit();
			Person* v_data = v.data();

			// Assert
			Assert::AreEqual(v.size(), v.capacity(), L"Capacity not equal to size");
			for (unsigned i = 0; i < 10; ++i) {
				Assert::AreEqual(data[i].name, v_data[i].name, L"Elements changed");
				Assert::AreEqual(data[i].age, v_data[i].age, L"Elements changed");
			}
		}
	};
}