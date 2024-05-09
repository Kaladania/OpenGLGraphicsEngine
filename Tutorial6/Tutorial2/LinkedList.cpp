#include "LinkedList.h"
#include "Polygon3D.h"
#include <iostream>
#include <iomanip>

LinkedList::LinkedList()
{

}

LinkedList::~LinkedList()
{

}

/// <summary>
/// Creates a new node and adds it to the linked list
/// </summary>
/// <param name="head">new node to add</param>
/// <param name="data">data to store in node</param>
/// <returns>the newly created node</returns>
ListNode* LinkedList::MakeNode(ListNode** head, Polygon3D* data)
{
	//creates a new node from the data provided
	ListNode* newNode = new ListNode;
	ListNode* last = *head;

	//populates the new node and sets the node its connected to to NULL
	newNode->data = data;
	newNode->nextNode = nullptr;

	//assigns the new node to be the head of the list is there is currently no head (list is empty)
	if (*head == nullptr)
	{
		*head = newNode;
		return newNode;
	}

	//cycles through the list to find the last node in said list (the one node with an empty next pointer)
	while (last->nextNode != nullptr)
	{
		last = last->nextNode;
	}

	//adds the newly created node to the last node's next pointer - making the newly created node the new last node in the list
	last->nextNode = newNode;

	return newNode;
}

/// <summary>
/// Inserts a new node at the start of the lead
/// </summary>
/// <param name="head">the old head node to be replaced</param>
/// <param name="data">the data being assigned to the new node</param>
/// <returns>the new head node</returns>
ListNode* LinkedList::InsertFirst(ListNode** head, Polygon3D* data)
{
	//creates a new node and sets the current head to be it's next node
	ListNode* newNode = new ListNode;
	newNode->data = data;
	newNode->nextNode = *head;

	//replaces the old head as the new head of the list
	*head = newNode;

	return newNode;
}

void LinkedList::InsertAfter(ListNode* lastNode, Polygon3D* data)
{
	//creates a new node and populates it with the given data
	ListNode* newNode = new ListNode;
	newNode->data = data;

	//sets the newly create node's nextNode to be the previous node's next node (is placed right after the currently passed in node
	newNode->nextNode = lastNode->nextNode;
	lastNode->nextNode = newNode;
}

/// <summary>
/// Deletes all elements after the passed in node
/// </summary>
/// <param name="node">the node respresting the start of the list of nodes to delete</param>
void LinkedList::DeleteList(ListNode** node)
{
	//creates a new temp node to act as an iterator to check if there are still nodes to delete
	ListNode* pTemp = *node;

	//creates a new temp node to store the next node for pTemp to delete
	ListNode* next = nullptr;

	//iterates through entire list until pTemp takes on the last node's nextNode pointer and becomes null
	while (pTemp != nullptr)
	{
		next = pTemp->nextNode; //stores a reference to the next node in the list
		delete pTemp; //deletes the current node
		pTemp = next; //moves on to the next node
	}

	*node = nullptr; //sets the pointer of the passed in node to NULL

	//cleans up by deleting the temp pointers
	delete pTemp;
	delete next;
}

/// <summary>
/// Deletes the node being pointed to by the passed in node
/// </summary>
/// <param name="node">node to reference</param>
void LinkedList::DeleteAfter(ListNode* node)
{
	//creates a new temp node to store the next node being pointed to from the current node
	ListNode* pTemp = node;

	//if the current node is not null and is pointing to second node
	if (node != nullptr && node->nextNode != nullptr)
	{
		pTemp = node->nextNode; //stores a reference to the next node in the list
		node->nextNode = pTemp->nextNode; //assignes the nextNode pointer of the current node to the node originally being pointed to by the passed in node
		delete pTemp; //deletes the current node
	}

}

/// <summary>
/// Returns the node at the current position
/// </summary>
/// <param name="node">the head node</param>
/// <param name="position">the position to access</param>
/// <returns>the found node. NULLPTR is position given is out of scope</returns>
ListNode* LinkedList::GetNode(ListNode* node, int position)
{
	int count = 0; //loop iterator

	//while there is still a node to traverse
	while (node != nullptr)
	{
		//returns the node at the passed in position
		if (count == position)
		{
			std::cout << "Data stored at Position: " << position << " is: " << node->data->GetPolygonName() << std::endl;
			return node;
		}

		//increments count and sets node to the next node
		count++;
		node = node->nextNode;
	}

	//returns an error mode for out of scope positions and returns a null value
	std::cout << "Position: " << position << " holds no data as it is outside the scope of the list." << std::endl;
	return nullptr;
}

/// <summary>
/// Finds the position of the given node
/// </summary>
/// <param name="node">the head node</param>
/// <param name="index">data of the node to find</param>
/// <returns>The position of the node holding the requested data. Returns -1 if the data cannot be found</returns>
int LinkedList::Find(ListNode* node, Polygon3D* index)
{
	int count = 0; //loop iterator

	//while there is still a node to traverse
	while (node != nullptr)
	{
		//returns the node at the passed in position
		if (node->data == index)
		{
			std::cout << "Node has been found at Position: " << count << std::endl;
			return count;
		}

		//increments count and sets node to the next node
		count++;
		node = node->nextNode;
	}

	//returns an error mode for out of scope positions and returns a null value
	std::cout << "The requested data cannot be found in the linked list." << std::endl;
	return -1;
}


void LinkedList::PrintList(ListNode* node)
{
	while (node != nullptr)
	{
		std::cout << std::setw(5) << " | " << node->data->GetPolygonName() << " |-->";
		node = node->nextNode;
	}

	if (node == nullptr)
	{
		std::cout << " | NULL |" << std::endl;
	}

	std::cout << std::endl;
}

/// <summary>
/// Returns the node at the current position
/// </summary>
/// <param name="node">the head node</param>
/// <param name="position">the position to access</param>
/// <returns>the found node. NULLPTR is position given is out of scope</returns>
void LinkedList::DeleteAt(ListNode* node, int position)
{
	int count = 0; //loop iterator

	ListNode* startingNode = node; //store a reference to the original head node
	ListNode* previousNode = node; //stores a reference to the previous node linking to the current node
	//ListNode* nextNode = nullptr;


	//while there is still a node to traverse
	while (node != nullptr)
	{
		//deletes the node at the requested position
		if (count == position)
		{
			//if the node is not the head, gets it's previous pointer as uses it as a reference to properly delete the node
			if (position > 0)
			{
				previousNode = GetNode(startingNode, position - 1);
				DeleteAfter(previousNode);
				break;

			}
			else
			{
				ListNode* nextNode = node->nextNode;
				node = nextNode; //stores a reference to the previous node linking to the current node

				//node = InsertFirst(&startingNode, node->nextNode->data);
				Find(startingNode, node->data);
				Find(startingNode, previousNode->data);
				//ListNode* pTemp = node;
				//node = nextNode;

				PrintList(node);

				Find(node, node->data);

				delete previousNode;
				

				//previousNode = node; //stores a reference to the next node in the list
				//node->nextNode = pTemp->nextNode; //assignes the nextNode pointer of the current node to the node originally being pointed to by the passed in node
				//delete pTemp; //deletes the current node
				break;
			}
		}

		//increments count and sets node to the next node
		count++;

		//creates a new temp node to store the next node being pointed to from the current node

		node = node->nextNode;
	}

}