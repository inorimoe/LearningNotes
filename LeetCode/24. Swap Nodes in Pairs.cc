/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(head == nullptr) return head;
        if(head->next == nullptr)return head;
        //构建头结点，链表题的经典解法之一
        ListNode pre(123, head);
        ListNode* llo = &pre;
        ListNode* lo = head;
        ListNode* hi;
        while(lo && lo->next){
            hi = lo->next;
            lo->next = hi->next;
            llo->next = hi;
            hi->next = lo;

            llo = lo;
            lo = lo->next;
        }
        return pre.next;
    }
};