// Serialization and deserialization
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <map>
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

	void serialize(std::ofstream& file) 
	{
		std::map<ListNode*, int> listStructure;
		ListNode* current = head_;
		
		for (int index = 0; current; current = current->next_, ++index) 
		{
			listStructure.insert({ current, index });
		}

		file << "{\n";
		current = head_;
		int index = 0;
		while (current)
		{
			const auto it = listStructure.find(current->rand_);
			const int randElemIndex = it == listStructure.end() ? -1 : it->second;
			file << getFormattedString(index, current->data_, randElemIndex);
			// file << "\t\"" << index << "\":{\"data\":\"" << current->data_ << "\", \"randIndex\":" << randElemIndex << '}';
			if (current->next_) file << ",\n";
			current = current->next_;
			++index;
		}
		file << "\n}";
	}

	std::string getFormattedString(const int index, std::string data, const int randElemIndex) {
		return std::string("\t\"" + std::to_string(index) + "\":{\"data\":\"" + data + "\", \"randIndex\":" + std::to_string(randElemIndex) + '}');
	}

	void deserialize(std::ifstream& file)
	{

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

	~ListRand() 
	{
		ListNode* current = head_->next_;
		while (current)
		{
			delete current->prev_;
			current = current->next_;
		}
		delete tail_;
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
	randomList->serialize(outf);

	// std::ifstream inf("Serialized_list.txt");
	// randomList->deserialize(inf);

	delete randomList;


}
