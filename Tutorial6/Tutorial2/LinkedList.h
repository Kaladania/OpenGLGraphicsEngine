#pragma once

class Polygon3D;

struct ListNode
{
	Polygon3D* data = nullptr;
	ListNode* nextNode = nullptr;
};


/// <summary>
/// Class Structure for a Linked List
/// </summary>
class LinkedList
{
private:

	
public:
	LinkedList();
	~LinkedList();

	ListNode* MakeNode(ListNode** head, Polygon3D* data);
	ListNode* InsertFirst(ListNode** head, Polygon3D* data);
	void InsertAfter(ListNode* lastNode, Polygon3D* data);
	void DeleteList(ListNode** node);
	void DeleteAfter(ListNode* node);
	void DeleteAt(ListNode* node, int position);
	ListNode* GetNode(ListNode* node, int position);
	int Find(ListNode* node, Polygon3D* data);
	void PrintList(ListNode* node);

};

