/*
  LIST MERGE SORT
  input: (singly linked) list L
  output: list with L's keys, sorted increasingly.
  algorithm: adaptation of the usual merge sort for arrays.
  complexity: O(nlogn) time, O(1) space, n=length of list. //unlike array merge sort with O(n) space
  comments: presumably bad software.
*/

#include <stdlib.h>
#include <stdio.h>

typedef int key;

struct node{
    key key;
    struct node* arrow;
};

typedef struct node node;
typedef struct node* list;

uint list_length(list list)
{
    uint cur_len=0;
    while(list)
    {
        cur_len++;
        list=list->arrow;
    }
    return cur_len;
}

//input: current to node, num steps to advance.
static list advance(list list, uint num_steps)
{  
    while(list && num_steps>0)
    {
        num_steps--;
        list=list->arrow;
    }
    return list;
}

//input: two increasingly sorted lists
//output: merged sorted list
static list merge(list dummy_node_ptr_list, list second_list)
{
    list ret;//the value merge returns
    list last_merged;//the last pointer in merged list
    list temp;

    //edge cases
    if(dummy_node_ptr_list==NULL)
        return second_list;
    if(second_list==NULL)
        return dummy_node_ptr_list;
    
    //may assume both lists are non empty. 
    //getting return key and start of merged list
    if(dummy_node_ptr_list->key < second_list->key)
    {
        ret=dummy_node_ptr_list;
        last_merged=dummy_node_ptr_list;
        dummy_node_ptr_list=dummy_node_ptr_list->arrow;
    }
    else
    {
        ret=second_list;
        last_merged=second_list;
        second_list=second_list->arrow;
    }

    //moving the elements from a and b to the merged list
    while(dummy_node_ptr_list && second_list)
    {
        if(dummy_node_ptr_list->key < second_list->key)
        {
            temp=dummy_node_ptr_list;
            dummy_node_ptr_list=dummy_node_ptr_list->arrow;
        }
        else
        {
            temp=second_list;
            second_list=second_list->arrow;
        }
        last_merged->arrow=temp;
        last_merged=temp;
    }

    //(at this point) one of the lists terminated
    if(dummy_node_ptr_list)
        last_merged->arrow=dummy_node_ptr_list;
    else
        last_merged->arrow=second_list;
        
    return ret;
}

//input: unsorted list
//output: input list, only sorted from min key to max key
list merge_sort(list input_list)
{
    uint N=list_length(input_list);
    if(N<2)
        return input_list;

    node* dummy_node_ptr = malloc(sizeof(node));
    dummy_node_ptr->arrow=input_list;

    //       [dummy] -> [***] -> [***] -> [***] ... [last] -> [ptr] ... [ptrA] -> [ptr B] ... [ptrC]  ->  [ptrD] ...
    // index   -1         0        1        2        x-1        x        x+k-1     x+k        x+2k-1       x+2k
    node *current, *adv_one, *adv_block, *adv_block_plus_one, *adv_two_blocks, *adv_two_blocks_plus_one;
    uint index;
    
    
for(uint sorted_block_size=1; sorted_block_size<N; sorted_block_size*=2)
    {
        current=dummy_node_ptr;
        adv_one=current->arrow;
        index=0;
        
        //check if only one merge is required
        if(2*sorted_block_size>=N)
        {
            adv_block=advance(adv_one,sorted_block_size-1);
            adv_block_plus_one=advance(adv_block,1);
            adv_block->arrow=NULL;
            free(dummy_node_ptr);
            return merge(adv_one,adv_block_plus_one);
        }

        //main loop
        while(index+2*sorted_block_size<N)
        {
            adv_block=advance(adv_one,sorted_block_size-1);
            adv_block_plus_one=advance(adv_block,1);
            adv_two_blocks=advance(adv_block_plus_one,sorted_block_size-1);
            adv_two_blocks_plus_one=advance(adv_two_blocks,1);//is not null

            adv_block->arrow=NULL;
            adv_two_blocks->arrow=NULL;

            current->arrow=merge(adv_one, adv_block_plus_one);

            //arange for next loop
            if(adv_block->key > adv_two_blocks->key)
                current=adv_block;
            else
                current=adv_two_blocks;
            index+=2*sorted_block_size;
            adv_one=adv_two_blocks_plus_one;
        }

        //ptr has reached the final block of size 2*sorted_block_size.
        //check if more than one block of size sorted_block_size remain
        if(index+sorted_block_size<N)
        {
            adv_block=advance(adv_one,sorted_block_size-1);
            adv_block_plus_one=advance(adv_block,1);
            adv_block->arrow=NULL;
            current->arrow=merge(adv_one, adv_block_plus_one);
        }
        //otherwise there remains at most one complete block of size sorted_block_size
        else
            current->arrow=adv_one;
    }
}
