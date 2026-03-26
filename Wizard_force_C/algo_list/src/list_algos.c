#include <./list_algos.h>
#include <./dbg.h>

inline void ListNode_swap(ListNode *a, ListNode *b)
{
    void *temp = a->value;
    a->value = b->value;
    b->value = temp;
}

int List_bubble_sort(List *list, List_compare cmp)
{
    int sorted = 1;

    if(List_count(list) <= 1) {
        return 0;  // already sorted
    }

    do {
        sorted = 1;
        LIST_FOREACH(list, first, next, cur) {
            if(cur->next) {
                if(cmp(cur->value, cur->next->value) > 0) {
                    ListNode_swap(cur, cur->next);
                    sorted = 0;
                }
            }
        }
    } while(!sorted);

    return 0;
}

inline List *List_merge(List *left, List *right, List_compare cmp)
{
    List *result = List_create();
    void *val = NULL;

    while(List_count(left) > 0 || List_count(right) > 0) {
        if(List_count(left) > 0 && List_count(right) > 0) {
            if(cmp(List_first(left), List_first(right)) <= 0) {
                val = List_shift(left);
            } else {
                val = List_shift(right);
            }

            List_push(result, val);
        } else if(List_count(left) > 0) {
            val = List_shift(left);
            List_push(result, val);
        } else if(List_count(right) > 0) {
            val = List_shift(right);
            List_push(result, val);
        }
    }

    return result;
}


// !!! optimize:
// create and copy much list:
// left & right
List *List_merge_sort(List *list, List_compare cmp)
{
    if(List_count(list) <= 1) {  // bottom check-----
        return list;
    }
    // build two new pointers: left, right
    List *left = List_create();
    List *right = List_create();

    // middle of input list ----
    int middle = List_count(list) / 2;

    // split equally to two parts  -----  // cubersome
    LIST_FOREACH(list, first, next, cur) {
        if(middle > 0) {
            List_push(left, cur->value);   // half to left
        } else {
            List_push(right, cur->value);  // half to right
        }

        middle--;
    }

    List *sort_left = List_merge_sort(left, cmp);
    List *sort_right = List_merge_sort(right, cmp);

    if(sort_left != left) List_destroy(left);
    if(sort_right != right) List_destroy(right);

    return List_merge(sort_left, sort_right, cmp);  // just merge
}

/*
void List_insert_sorted(List* list, List_compare cmp, void* value){
    Assert(list != NULL, "Input list is empty");
    ListNode* new;
    new->value = value;
    int n = 1;
    int insert = 0;
    LIST_FOREACH(list, first, next, cur){
        if(cmp(cur->value, value) > 0){
            if(n == 1){
                list->first = new;
                new->next = cur;
                cur->prev = new;
            }
            else{
                ListNode* temp = cur->prev;
                cur->prev = new;
                new->next = cur;
                temp->next = new;
                new->prev = temp;
            }
            list->count++;
            insert = 1;
        }
        n++;
    }
    if(!insert){
        List_push(list, value);
    }
}
*/
/*
List* List_merge_sort(List* list, List_compare cmp){
    Assert(list != NULL, "Input list is empty");
    if(List_count(list) <= 1) {  // bottom check-----
        return list;
    }
    List *left = List_create();
    List *right = List_create();

    size_t half = list_count(list) / 2;
    left->count = right->count = half / 2;

    int i = 0;
    LIST_FOREACH(list, first, next, cur){
        if(i = half - 1) left->last = cur;
        if(i = half) right->first = cur;
        if(i = list_count(list) - 1) right->last = cur;
        i++;
    }
    List* sorted_left = List_merge_sort(left, cmp);
    List* sorted_right = List_merge_sort(right, cmp);

    return List_merge(sorted_left, sorted_right, cmp);
}
*/


