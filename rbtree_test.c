/******************************************************************************
 * @file    : rbtree_test.c
 * @author  : wangyubin
 * @date    : Tue Jun 24 16:58:24 2014
 * 
 * @brief   : test rbtree use cpputest
 * history  : init
 ******************************************************************************/

#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>

extern "C"
{
#include "rbtree.h"
}

void print_tree(int, struct rb_root);           /* 0: 前序，1：中序，2：后序 */

struct test_struct 
{
    int num;
    struct rb_node node;
};

TEST_GROUP(test_rbtree)
{
    void setup()
    {
        printf ("\n=========================================\n");
    }
    void teardown()
    {
        printf ("=========================================\n\n\n");
    }
};

/*
 * 构造测试用红黑树如下:
 *                    root
 *                     0
 *                   /   \
 *                  1     4
 *                 / \   / \
 *                2   3 5   6
 */
TEST(test_rbtree, test_rb_func)
{
    struct rb_root root = RB_ROOT;
    struct test_struct *l, *ll, *lr, *r, *rl, *rr, *m;
    struct test_struct *node_in, *node_in2, *node_replace;

    m = (struct test_struct*)malloc(sizeof(struct test_struct));
    m->num = 0;
    rb_init_node(&m->node);
    rb_set_black(&m->node);

    l = (struct test_struct*)malloc(sizeof(struct test_struct));
    l->num = 1;
    rb_init_node(&l->node);
    rb_set_red(&l->node);

    ll = (struct test_struct*)malloc(sizeof(struct test_struct));
    ll->num = 2;
    rb_init_node(&ll->node);
    rb_set_black(&ll->node);

    lr = (struct test_struct*)malloc(sizeof(struct test_struct));
    lr->num = 3;
    rb_init_node(&lr->node);
    rb_set_black(&lr->node);

    r = (struct test_struct*)malloc(sizeof(struct test_struct));
    r->num = 4;
    rb_init_node(&r->node);
    rb_set_red(&r->node);

    rl = (struct test_struct*)malloc(sizeof(struct test_struct));
    rl->num = 5;
    rb_init_node(&rl->node);
    rb_set_black(&rl->node);

    rr = (struct test_struct*)malloc(sizeof(struct test_struct));
    rr->num = 6;
    rb_init_node(&rr->node);
    rb_set_black(&rr->node);

    /* root 节点 */
    root.rb_node = &m->node;
    rb_init_node(root.rb_node);
    root.rb_node->rb_left = &l->node;
    root.rb_node->rb_right = &r->node;
    rb_set_parent(&l->node, root.rb_node);
    rb_set_parent(&r->node, root.rb_node);
    rb_set_black(root.rb_node);

    /* root 左节点 */
    (&l->node)->rb_left = &ll->node;
    (&l->node)->rb_right = &lr->node;
    rb_set_parent(&ll->node, &l->node);
    rb_set_parent(&lr->node, &l->node);

    /* root 右节点 */
    (&r->node)->rb_left = &rl->node;
    (&r->node)->rb_right = &rr->node;
    rb_set_parent(&rl->node, &r->node);
    rb_set_parent(&rr->node, &r->node);

    /* test rb_set_parent */
    POINTERS_EQUAL(rb_parent(&l->node), root.rb_node);
    POINTERS_EQUAL(rb_parent(&r->node), root.rb_node);

    /* test rb_set_color */
    CHECK(rb_color(&l->node) == RB_RED);
    CHECK(rb_color(&lr->node) == RB_BLACK);

    /* test rb_first rb_last rb_prev rb_next */
    POINTERS_EQUAL(rb_first(&root), &ll->node);
    POINTERS_EQUAL(rb_last(&root), &rr->node);
    POINTERS_EQUAL(rb_prev(&l->node), &ll->node);
    POINTERS_EQUAL(rb_next(&l->node), &lr->node);
    
    /*
     * test rb_insert_color
     * 1. 先插入节点 node_in 红色
     * 2. 再插入节点 node_in2 到 node_in 之下
     * */
    node_in = (struct test_struct*)malloc(sizeof(struct test_struct)); /* 待插入的node */
    node_in->num = 7;
    rb_init_node(&node_in->node);

    (&ll->node)->rb_left = &node_in->node;
    rb_set_parent(&node_in->node, &ll->node);
    printf ("before insert color node_in->node color: %s\n", rb_color(&node_in->node) ? "BLACK" : "RED");
    rb_insert_color(&node_in->node, &root);
    printf ("after  insert color node_in->node color: %s\n", rb_color(&node_in->node) ? "BLACK" : "RED");

    node_in2 = (struct test_struct*)malloc(sizeof(struct test_struct)); /* 待插入的node */
    node_in2->num = 8;
    rb_init_node(&node_in2->node);

    (&node_in->node)->rb_left = &node_in2->node;
    rb_set_parent(&node_in2->node, &node_in->node);
    printf ("before insert color node_in2->node color: %s\n", rb_color(&node_in2->node) ? "BLACK" : "RED");
    rb_insert_color(&node_in2->node, &root);
    printf ("after  insert color node_in2->node color: %s\n", rb_color(&node_in2->node) ? "BLACK" : "RED");

    printf ("前序遍历: \n");
    print_tree(0, root);        /* 前序 */
    printf ("中序遍历: \n");
    print_tree(1, root);        /* 中序 */
    printf ("后序遍历: \n");
    print_tree(2, root);        /* 后序 */

    /* test rb_erase */
    rb_erase(&ll->node, &root);

    /* test rb_replace_node */
    node_replace = (struct test_struct*)malloc(sizeof(struct test_struct)); /* 待插入的node */
    node_replace->num = 9;
    rb_init_node(&node_replace->node);

    rb_replace_node(&node_in->node, &node_replace->node, &root);
    
    printf ("前序遍历: \n");
    print_tree(0, root);        /* 前序 */
    printf ("中序遍历: \n");
    print_tree(1, root);        /* 中序 */
    printf ("后序遍历: \n");
    print_tree(2, root);        /* 后序 */

    free(ll);
    free(lr);
    free(l);
    free(rr);
    free(rl);
    free(r);
    free(m);
}

/* 前序 */
void __print_DLR(struct rb_node* node)
{
    struct test_struct *p = NULL;
    if (node == NULL)
        return;
    
    p = rb_entry(node, struct test_struct, node);
    printf ("node num: %d\n", p->num);
    __print_DLR(node->rb_left);
    __print_DLR(node->rb_right);
}

/* 中序 */
void __print_LDR(struct rb_node* node)
{
    struct test_struct *p = NULL;
    if (node == NULL)
        return;

    __print_LDR(node->rb_left);
    p = rb_entry(node, struct test_struct, node);
    printf ("node num: %d\n", p->num);
    __print_LDR(node->rb_right);
}

/* 后序 */
void __print_LRD(struct rb_node* node)
{
    struct test_struct *p = NULL;
    if (node == NULL)
        return;

    __print_LRD(node->rb_left);
    __print_LRD(node->rb_right);
    p = rb_entry(node, struct test_struct, node);
    printf ("node num: %d\n", p->num);
}

/*
 * 按照指定顺序打印整个树 
 * sort: 0 - 前序, 1 - 中序, 2 - 后序
 */
void print_tree(int sort, struct rb_root root)
{
    if (root.rb_node == NULL)
        return;

    if (sort == 0) {
        __print_DLR(root.rb_node);
    }
    else if (sort == 1) {
        __print_LDR(root.rb_node);
    }
    else if (sort == 2) {
        __print_LRD(root.rb_node);
    }
    
}


int main(int argc, char *argv[])
{
    return RUN_ALL_TESTS(argc, argv);
}
