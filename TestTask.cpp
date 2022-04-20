// Serialization and deserialization
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <map>
#include <sstream>
#include <vector>

class ListNode
{
public:
	ListNode* prev_;
	ListNode* next_;
	ListNode* rand_;
	std::string data_;
	ListNode(std::string data) : prev_{ nullptr }, next_{ nullptr }, rand_{ nullptr }, data_{ data }
	{
		// std::cout << "I was constructed!\n";
	}
	~ListNode()
	{
		// std::cout << "I was destroyed!\n";
	}
};

class ListRand
{
public:
	ListRand() : head_{ nullptr }, tail_{ nullptr }, count_{ 0 } {}
	ListNode* head_;
	ListNode* tail_;
	int count_;

	void serialize(std::ofstream& file)
	{
		std::map<ListNode*, int> listStructure;
		ListNode* current = head_;

		// fill map with pointer and its index
		for (int index = 0; current; current = current->next_, ++index)
		{
			listStructure.insert({ current, index });
		}

		current = head_;
		int index = 0;

		// store list size
		file << count_ << '\n';

		// foreach element in the list
		while (current)
		{
			// find random pointer if it is exists
			const auto it = listStructure.find(current->rand_);

			// if it is exists, store its index as reference for later converting
			const int randElemIndex = it == listStructure.end() ? -1 : it->second;
			// format output string for this template: index data randIndex
			file << std::string(std::to_string(index) + ' ' + current->data_ + ' ' + std::to_string(randElemIndex));
			// check for tail element
			if (current->next_) file << '\n';
			// iterate
			current = current->next_;
			++index;
		}
	}

	void deserialize(std::ifstream& file)
	{
		// clear previous nodes
		clear();

		// read amount of elements
		int count{};
		file >> count;

		// for random pointers indexes - index corresponds to the number of element, value - to the number of random element it is pointing
		std::vector<int> randomElements(count, 0);

		// map for matching the element and its number
		std::map<int, ListNode*> listElements;

		for (int i = 0; i < count; ++i)
		{
			int index{};
			std::string data;
			int randIndex{};

			file >> index >> data >> randIndex;

			randomElements[index] = randIndex;

			add(new ListNode(data));
			listElements.insert({ i, tail_ });
		}

		restoreRandomPointers(randomElements, listElements);
	}

	void restoreRandomPointers(std::vector<int>& randomElements, std::map<int, ListNode*>& listElements)
	{
		ListNode* current = head_;
		for (int i = 0; i < count_; ++i)
		{
			if (randomElements[i] != -1)
			{
				current->rand_ = listElements[randomElements[i]];
			}
			current = current->next_;
		}
	}

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


	}

	void fillRands()
	{
		for (ListNode* currentNode = head_; currentNode; currentNode = currentNode->next_)
		{
			// make random the event of even creating a pointer to the random list element
			bool needRand = rand() % 2;
			if (!needRand) continue;
			// make random pointer to the existing list element
			const auto index = rand() % count_;

			// iterate to this element
			ListNode* current = head_;
			for (int i = 0; i < index; ++i)
			{
				current = current->next_;
			}

			// assign it to the new element rand_ pointer
			currentNode->rand_ = current;
		}
	}

	void clear()
	{
		count_ = 0;
		ListNode* current = head_->next_;
		while (current)
		{
			delete current->prev_;
			current = current->next_;
		}
		delete tail_;
		tail_ = nullptr;
		head_ = nullptr;
	}

	void print()
	{
		std::cout << "\n===================== LIST CONTENT =====================\n";
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

	~ListRand()
	{
		clear();
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

	randomList->fillRands();

	randomList->print();

	std::ofstream outf("Serialized_list.txt");

	if (!outf)
	{
		std::cerr << "Could not open file for writing!\n" << std::endl;
		exit(1);
	}

	randomList->serialize(outf);

	outf.close();

	std::ifstream inf("Serialized_list.txt");
	if (!inf)
	{
		std::cerr << "Could not open file for reading!\n" << std::endl;
		exit(1);
	}


	randomList->deserialize(inf);

	randomList->print();

	delete randomList;
}