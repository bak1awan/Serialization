// Serialization and deserialization
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
// #define PRINT(x) #x << ": " << x

class ListNode
{
public:
	ListNode* prev_;
	ListNode* next_;
	ListNode* rand_;
	std::string data_;

	ListNode(std::string data) : prev_{ nullptr }, next_{ nullptr }, rand_{ nullptr }, data_{ data } {}
};

class ListRand
{
public:
	ListRand() : head_{ nullptr }, tail_{ nullptr }, count_{ 0 } {}
	ListNode* head_;
	ListNode* tail_;
	int count_;

	void serialize(std::ofstream& s) {}

	void deserialize(std::ifstream& s) {}

	void add(ListNode* listNode)
	{
		++count_; // increment list element counter

		if (!head_) // if it is the first element in the list
		{
			head_ = listNode;
			tail_ = listNode;
		}
		else // add new element to the end of the list
		{
			tail_->next_ = listNode;
			listNode->prev_ = tail_;
			tail_ = listNode;
		}

		// if it is the first element - we won't generate pointer to the random list element
		if (count_ == 1)
		{
			return;
		}

		// make random the event of even creating a pointer to the random list element
		bool fillRand = rand() % 2;
		if (!fillRand) return;

		// make random pointer to the existing list element
		const auto index = rand() % count_;

		// iterate to this element
		ListNode* current = head_;
		for (int i = 0; i < index; ++i)
		{
			current = current->next_;
		}

		// assign it to the new element rand_ pointer
		tail_->rand_ = current;
	}

	// for debugging
	void print()
	{
		ListNode* current = head_;
		int counter = 0;
		while (current)
		{
			printf("Element #%i: data - %s, prev_ - %p, next_ - %p, rand_ %p.\n\n", //
				counter, current->data_.c_str(), current->prev_, current->next_, current->rand_);
			current = current->next_;
			++counter;
		}
	}
};




int main()
{
	srand(static_cast<unsigned int>(time(0)));

	ListRand* randomList = new ListRand();

	randomList->add(new ListNode("first"));
	randomList->add(new ListNode("second"));
	randomList->add(new ListNode("third"));
	randomList->add(new ListNode("fourth"));
	randomList->add(new ListNode("fifth"));
	randomList->add(new ListNode("sixth"));
	randomList->add(new ListNode("seventh"));
	randomList->add(new ListNode("eighth"));
	randomList->add(new ListNode("ninth"));
	randomList->add(new ListNode("tenth"));
	randomList->add(new ListNode("eleventh"));

	randomList->print();

	// std::ofstream outf("Serialized_list.txt");
	// std::ifstream inf("Deserialized_list.txt");
}
