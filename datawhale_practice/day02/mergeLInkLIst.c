/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2){
    if(!l1 && !l2)
            return NULL;
        if(!l1 && l2)
            return l2;
        if(l1 && !l2)
            return l1;
    //  l1 = l1->next;
    //  l2 = l2->next;
    struct ListNode* tmp = (struct ListNode *)malloc(sizeof(struct ListNode));
    struct ListNode*  res = tmp;
    tmp->next = NULL;
    while(l1 != NULL && l2 != NULL )
    {
        if(l1->val<=l2->val)
        {
            tmp->next= l1;
            tmp=l1;
            l1=l1->next;
        } else{
            tmp->next = l2;
            tmp = l2;
            l2=l2->next;
        }
    }
    tmp->next = l1?l1:l2;
    l1 = NULL;
    l2 =NULL;
    return res->next;
}