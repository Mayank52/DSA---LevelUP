#include <iostream>
#include <vector>

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 876. Middle of the Linked List
//gets second mid in case of even length
ListNode *middleNode(ListNode *head)
{
    ListNode *slow = head;
    ListNode *fast = head;

    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

//gets first mid in case of even length
ListNode *middleNode_02(ListNode *head)
{
    ListNode *slow = head;
    ListNode *fast = head;

    while (fast->next != nullptr && fast->next->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

// 206. Reverse Linked List
ListNode *reverseList(ListNode *head)
{
    ListNode *prev = nullptr;
    ListNode *curr = head;

    while (curr != nullptr)
    {
        ListNode *forw = curr->next;
        curr->next = prev;
        prev = curr;
        curr = forw;
    }

    return prev;
}

// 234. Palindrome Linked List
ListNode *middleNode_02(ListNode *head)
{
    ListNode *slow = head;
    ListNode *fast = head;

    while (fast->next != nullptr && fast->next->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}
ListNode *reverseList(ListNode *head)
{
    ListNode *prev = nullptr;
    ListNode *curr = head;

    while (curr != nullptr)
    {
        ListNode *forw = curr->next;
        curr->next = prev;
        prev = curr;
        curr = forw;
    }

    return prev;
}
bool isPalindrome(ListNode *head)
{
    if (head == nullptr)
        return true;

    ListNode *curr = head;
    ListNode *midNode = middleNode_02(curr);
    ListNode *newHead = reverseList(midNode->next);
    midNode->next = nullptr;

    while (curr != nullptr && newHead != nullptr)
    {
        if (curr->val != newHead->val)
            return false;
        curr = curr->next;
        newHead = newHead->next;
    }

    return true;
}

// 19. Remove Nth Node From End of List (n is always valid)
ListNode *removeNthFromEnd(ListNode *head, int n)
{
    if (n == 0 || head == nullptr)
        return head;
    if (n == 1 && head->next == nullptr)
        return nullptr;

    ListNode *slow = head;
    ListNode *fast = head;

    //move fast pointer n times
    while (n-- > 0)
        fast = fast->next;

    //if first node was to be removed
    if (fast == nullptr)
        return slow->next;

    //move both until fast is at the end of list
    while (fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next;
    }

    ListNode *forw = slow->next;
    slow->next = slow->next->next;
    forw->next = nullptr;

    return head;
}

// 143. Reorder List
ListNode *middleNode(ListNode *head)
{
    ListNode *slow = head;
    ListNode *fast = head;

    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}
ListNode *reverseList(ListNode *head)
{
    ListNode *prev = nullptr;
    ListNode *curr = head;

    while (curr != nullptr)
    {
        ListNode *forw = curr->next;
        curr->next = prev;
        prev = curr;
        curr = forw;
    }

    return prev;
}
void reorderList(ListNode *head)
{
    if (head == nullptr || head->next == nullptr)
        return;

    ListNode *curr = head;
    ListNode *midNode = middleNode(curr);
    ListNode *nhead = reverseList(midNode->next);
    midNode->next = nullptr;

    while (curr != nullptr && nhead != nullptr)
    {
        ListNode *forw1 = curr->next;
        ListNode *forw2 = nhead->next;

        curr->next = nhead;
        nhead->next = forw1;

        nhead = forw2;
        curr = forw1;
    }
}

// 21. Merge Two Sorted Lists
ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
{
    if (l1 == nullptr || l2 == nullptr)
        return l1 == nullptr ? l2 : l1;

    ListNode *curr1 = l1;
    ListNode *curr2 = l2;
    ListNode *head = new ListNode(-1);
    ListNode *prev = head;

    while (curr1 != nullptr && curr2 != nullptr)
    {
        if (curr1->val < curr2->val)
        {
            prev->next = curr1;
            curr1 = curr1->next;
        }
        else
        {
            prev->next = curr2;
            curr2 = curr2->next;
        }
        prev = prev->next;
    }

    while (curr1 != nullptr)
    {
        prev->next = curr1;
        curr1 = curr1->next;
        prev = prev->next;
    }
    while (curr2 != nullptr)
    {
        prev->next = curr2;
        curr2 = curr2->next;
        prev = prev->next;
    }

    return head->next;
}

// 328. Odd Even Linked List
ListNode *oddEvenList(ListNode *head)
{
    
}

void solve()
{
}
int main()
{
    solve();
    return 0;
}