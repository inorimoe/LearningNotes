/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
/*
 * 我菜，我渣，简直是人间之屑 
 */
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode *start=NULL,*node=NULL;
    if(l1!=NULL&&l2==NULL)
    {
            start=l1;
            node=start;
            l1=l1->next;
    }
    else if(l1==NULL&&l2!=NULL)
    {
            start=l2;
            node=start;
            l2=l2->next;
    }
    else if(l1==NULL&&l2==NULL)
    {
        return NULL;
    }
    else
    {
            if(l1->val<=l2->val)
            {
                start=l1;
                node=start;
                l1=l1->next;
            }
            else
            {
                start=l2;
                node=start;
                l2=l2->next;
            }
    }
    while(node!=NULL)
    {
        if(l1!=NULL&&l2!=NULL)
        {
            if(l1->val<=l2->val)
            {
                node->next=l1;
                l1=l1->next;
                node=node->next;
            }
            else
            {
                node->next=l2;
                l2=l2->next;
                node=node->next;
            }
        }
        else if(l1==NULL&&l2!=NULL)
        {
            node->next=l2;
            break;
        }
        else if(l1!=NULL&&l2==NULL)
        {
            node->next=l1;
            break;
        }
        else
            node=node->next;
    }
    return start;
}