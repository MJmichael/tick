/******************************************************************************
 * @file    : list_test.c
 * @author  : wangyubin
 * @date    : Sun Jun 22 19:00:58 2014
 * 
 * @brief   : list test use CppUTest
 * history  : init
 ******************************************************************************/
#include <stdlib.h>
#include <stdio.h>

#include "list.h"
#define NODE 5

struct test_struct 
{
    int num;
    struct list_head list;
};

void print_list(struct list_head *h);
void init_test_struct(int n, struct test_struct* ts);

/* 追加2个节点，然后和head.next head.prev 比较地址 */
//TEST(test_list, list_add)
void test1()
{
	struct test_struct* ts = NULL;
	int i;

	ts = (struct test_struct*)malloc(NODE * sizeof(struct test_struct));
	init_test_struct(NODE, ts);

	LIST_HEAD(head);
	printf ("Before add node:\n");
	print_list(&head);

	printf ("After add node:\n");
	//for(i=0;i<NODE;++i)
	//   list_add(&(ts+i)->list, &head);

	for(i=0;i<NODE;++i)
		list_add_tail(&(ts+i)->list, &head);

	//    print_list(&head);
	struct test_struct* pos;

	list_for_each_entry_reverse(pos, &head, list)
		printf("%d\n", pos->num);
#if 0
	struct list_head *hd;

	// 1: list point, 2:head
	list_for_each(hd, &head)
	{
		struct test_struct* p;
		int *n;

		p = container_of(hd, struct test_struct, list);
		printf("%d\n", p->num);

		n = &p->num;
		p = container_of(n, struct test_struct, num);
		printf("%d\n", p->num);
	}
#endif

	free(ts);
	
	unsigned int k, j;
	
	k=0;j=0xfffffffe;
	printf("%u\n", (k-j));
}

//TEST(test_list, list_del)
void test3()
{
    struct test_struct* ts = NULL;
    ts = (struct test_struct*)malloc(2 * sizeof(struct test_struct));
    init_test_struct(2, ts);
    
    LIST_HEAD(head);
    printf ("Before del node:\n");
    list_add_tail(&(ts+0)->list, &head);
    list_add_tail(&(ts+1)->list, &head);
    print_list(&head);

    printf ("After del node:\n");
    list_del(&(ts+0)->list);
    print_list(&head);
    
    free(ts);
}

//TEST(test_list, list_del_init)
void test4()
{
    struct test_struct* ts = NULL;
    ts = (struct test_struct*)malloc(2 * sizeof(struct test_struct));
    init_test_struct(2, ts);
    
    LIST_HEAD(head);
    printf ("Before del node:\n");
    list_add_tail(&(ts+0)->list, &head);
    list_add_tail(&(ts+1)->list, &head);
    print_list(&head);

    printf ("After del node:\n");
    list_del_init(&(ts+0)->list);
    print_list(&head);
    
    free(ts);
}

//TEST(test_list, list_replace)
void test5()
{
    struct test_struct* ts = NULL;
    ts = (struct test_struct*)malloc(3 * sizeof(struct test_struct));
    init_test_struct(3, ts);
    
    LIST_HEAD(head);
    printf ("Before replace node:\n");
    list_add_tail(&(ts+0)->list, &head);
    list_add_tail(&(ts+1)->list, &head);
    print_list(&head);

    printf ("After replace node:\n");
    list_replace(&(ts+0)->list, &(ts+2)->list);
    print_list(&head);
    
    free(ts);
}

//TEST(test_list, list_replace_init)
void test6()
{
    struct test_struct* ts = NULL;
    ts = (struct test_struct*)malloc(3 * sizeof(struct test_struct));
    init_test_struct(3, ts);
    
    LIST_HEAD(head);
    printf ("Before replace node:\n");
    list_add_tail(&(ts+0)->list, &head);
    list_add_tail(&(ts+1)->list, &head);
    print_list(&head);

    printf ("After replace node:\n");
    list_replace(&(ts+0)->list, &(ts+2)->list);
    print_list(&head);
    
    free(ts);
}

//TEST(test_list, list_move)
void test7()
{
    struct test_struct* ts = NULL;
    ts = (struct test_struct*)malloc(3 * sizeof(struct test_struct));
    init_test_struct(3, ts);
    
    LIST_HEAD(head1);
    LIST_HEAD(head2);
    printf ("Before move node:\n");
    printf ("Head1:\n");
    list_add_tail(&(ts+0)->list, &head1);
    list_add_tail(&(ts+1)->list, &head1);
    print_list(&head1);
    printf ("Head2:\n");
    list_add_tail(&(ts+2)->list, &head2);
    print_list(&head2);

    printf ("After remove node:\n");
    list_move(&(ts+0)->list, &head2);
    
    printf ("Head1:\n");
    print_list(&head1);
    printf ("Head2:\n");
    print_list(&head2);
    
    free(ts);
}

//TEST(test_list, list_move_tail)
void test8()
{
    struct test_struct* ts = NULL;
    ts = (struct test_struct*)malloc(3 * sizeof(struct test_struct));
    init_test_struct(3, ts);
    
    LIST_HEAD(head1);
    LIST_HEAD(head2);
    printf ("Before move node:\n");
    printf ("Head1:\n");
    list_add_tail(&(ts+0)->list, &head1);
    list_add_tail(&(ts+1)->list, &head1);
    print_list(&head1);
    printf ("Head2:\n");
    list_add_tail(&(ts+2)->list, &head2);
    print_list(&head2);

    printf ("After remove node:\n");
    list_move_tail(&(ts+0)->list, &head2);
    
    printf ("Head1:\n");
    print_list(&head1);
    printf ("Head2:\n");
    print_list(&head2);
    
    free(ts);
}

//TEST(test_list, list_is_last)
void test9()
{
    struct test_struct* ts = NULL;
    ts = (struct test_struct*)malloc(3 * sizeof(struct test_struct));
    init_test_struct(3, ts);
    
    LIST_HEAD(head);
    printf ("init node:\n");
    list_add_tail(&(ts+0)->list, &head);
    list_add_tail(&(ts+1)->list, &head);
    list_add_tail(&(ts+2)->list, &head);
    print_list(&head);

    if (list_is_last(&(ts+0)->list, &head))
        printf ("(ts+0) is last!\n");
    else
        printf ("(ts+0) is not last!\n");
    
    if (list_is_last(&(ts+2)->list, &head))
        printf ("(ts+2) is last!\n");
    else
        printf ("(ts+2) is not last!\n");
    
    free(ts);
}

//TEST(test_list, list_empty)
void test10()
{
    struct test_struct* ts = NULL;
    ts = (struct test_struct*)malloc(3 * sizeof(struct test_struct));
    init_test_struct(3, ts);
    
    LIST_HEAD(head);
    printf ("init node:\n");
    list_add_tail(&(ts+0)->list, &head);
    list_add_tail(&(ts+1)->list, &head);
    list_add_tail(&(ts+2)->list, &head);
    print_list(&head);

    if (list_empty(&head))
        printf ("head is empty!\n");
    else
        printf ("head is not empty!\n");
    
    free(ts);
}

//TEST(test_list, list_is_singular)
void test11()
{
    struct test_struct* ts = NULL;
    ts = (struct test_struct*)malloc(3 * sizeof(struct test_struct));
    init_test_struct(3, ts);
    
    LIST_HEAD(head);
    printf ("after init node:\n");
    if (list_is_singular(&head))
        printf ("head is singular!\n");
    else
        printf ("head is not sungular!\n");
    
    printf ("add first node:\n");
    list_add_tail(&(ts+0)->list, &head);
    print_list(&head);

    if (list_is_singular(&head))
        printf ("head is singular!\n");
    else
        printf ("head is not sungular!\n");
    
    printf ("add second node:\n");
    list_add_tail(&(ts+1)->list, &head);
    print_list(&head);

    if (list_is_singular(&head))
        printf ("head is singular!\n");
    else
        printf ("head is not sungular!\n");
    
    free(ts);
}

//TEST(test_list, list_cut_position)
void test12()
{
    struct test_struct* ts = NULL;
    ts = (struct test_struct*)malloc(3 * sizeof(struct test_struct));
    init_test_struct(3, ts);
    
    LIST_HEAD(head1);
    LIST_HEAD(head2);
    printf ("init node:\n");
    list_add_tail(&(ts+0)->list, &head1);
    list_add_tail(&(ts+1)->list, &head1);
    list_add_tail(&(ts+2)->list, &head1);
    printf ("Head1:\n");
    print_list(&head1);
    printf ("Head2:\n");
    print_list(&head2);

    list_cut_position(&head2, &head1, &(ts+1)->list);
    printf ("Head1:\n");
    print_list(&head1);
    printf ("Head2:\n");
    print_list(&head2);

    free(ts);
}

//TEST(test_list, list_splice)
void test13()
{
    struct test_struct* ts = NULL;
    ts = (struct test_struct*)malloc(3 * sizeof(struct test_struct));
    init_test_struct(3, ts);
    
    LIST_HEAD(head1);
    LIST_HEAD(head2);
    printf ("init node:\n");
    list_add_tail(&(ts+0)->list, &head1);
    list_add_tail(&(ts+1)->list, &head1);
    printf ("Head1:\n");
    print_list(&head1);
    
    list_add_tail(&(ts+2)->list, &head2);
    printf ("Head2:\n");
    print_list(&head2);

    list_splice(&head2, &head1);
    printf ("Head1:\n");
    print_list(&head1);
    printf ("Head2:\n");
    /* print_list(&head2);  head2 是未知情况 */

    free(ts);
}

//TEST(test_list, list_splice_tail)
void test14()
{
    struct test_struct* ts = NULL;
    ts = (struct test_struct*)malloc(3 * sizeof(struct test_struct));
    init_test_struct(3, ts);
    
    LIST_HEAD(head1);
    LIST_HEAD(head2);
    printf ("init node:\n");
    list_add_tail(&(ts+0)->list, &head1);
    list_add_tail(&(ts+1)->list, &head1);
    printf ("Head1:\n");
    print_list(&head1);
    
    list_add_tail(&(ts+2)->list, &head2);
    printf ("Head2:\n");
    print_list(&head2);

    list_splice_tail(&head2, &head1);
    printf ("Head1:\n");
    print_list(&head1);
    printf ("Head2:\n");
    /* print_list(&head2);  head2 是未知情况 */

    free(ts);
}

//TEST(test_list, list_splice_init)
void test15()
{
    struct test_struct* ts = NULL;
    ts = (struct test_struct*)malloc(3 * sizeof(struct test_struct));
    init_test_struct(3, ts);
    
    LIST_HEAD(head1);
    LIST_HEAD(head2);
    printf ("init node:\n");
    list_add_tail(&(ts+0)->list, &head1);
    list_add_tail(&(ts+1)->list, &head1);
    printf ("Head1:\n");
    print_list(&head1);
    
    list_add_tail(&(ts+2)->list, &head2);
    printf ("Head2:\n");
    print_list(&head2);

    list_splice_init(&head2, &head1);
    printf ("Head1:\n");
    print_list(&head1);
    printf ("Head2:\n");
    print_list(&head2);         /* list_splice_init 的情况下, head2被初始化 */

    free(ts);
}

//TEST(test_list, list_splice_tail_init)
void test16()
{
    struct test_struct* ts = NULL;
    ts = (struct test_struct*)malloc(3 * sizeof(struct test_struct));
    init_test_struct(3, ts);
    
    LIST_HEAD(head1);
    LIST_HEAD(head2);
    printf ("init node:\n");
    list_add_tail(&(ts+0)->list, &head1);
    list_add_tail(&(ts+1)->list, &head1);
    printf ("Head1:\n");
    print_list(&head1);
    
    list_add_tail(&(ts+2)->list, &head2);
    printf ("Head2:\n");
    print_list(&head2);

    list_splice_tail_init(&head2, &head1);
    printf ("Head1:\n");
    print_list(&head1);
    printf ("Head2:\n");
    print_list(&head2);         /* list_splice_tail_init 的情况下, head2被初始化 */

    free(ts);
}

void print_list(struct list_head *h)
{
    struct test_struct *pos = NULL;
    
    list_for_each_entry(pos, h, list) {
        printf ("%d\n", pos->num);
    }
}

void init_test_struct(int n, struct test_struct* ts)
{
    int i;

    for(i = 0; i < n; i++){
        (ts+i)->num = i+1;
        INIT_LIST_HEAD(&(ts+i)->list);
    }
}

void main(int argc, char *argv[])
{
    //return RUN_ALL_TESTS(argc, argv);
	test1();
#if 0
	test3();
	test4();
	test5();
	test6();
	test7();
	test8();
	test9();
	test10();
	test11();
	test12();
	test13();
	test14();
	test15();
	test16();
#endif
}
