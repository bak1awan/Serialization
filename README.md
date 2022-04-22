# List serialization/deserialization
## Description

This program written on C++ is designed to serialize/deserialize a list. 

Sctructures of `ListNode` and `ListRand` are specified below:

	class ListNode
	{
		public ListNode Prev;
		public ListNode Next;
		public ListNode Rand; // random element of the list
		public string Data;
	}


	class ListRand
	{
		public ListNode Head;
		public ListNode Tail;
		public int Count;

		public void Serialize(FileStream s)
		{
		}

		public void Deserialize(FileStream s)
		{
		}
	}


Each element is serialized in the format: `data/spacebar/pointerToListNodeRand`. 

The functionallity is divided into header (`List.h`) and cpp (`List.cpp`) files. You cant test serialization and deserialization in the `SerializeAndDeserializeList.cpp` file.
