#include "BPlusTree.h"

using namespace std;

void keep_window_open()
{
    char c;
    printf("enter a character to exit\n");
    cin >> c;
}

/*
void test_page()
{
    Page<string> p1(3);
    cout << p1.get_m() << endl;
}
*/

void test_tree()
{
    BPlusTree<int, int> tree(3);
    tree.create_tree();
    tree.init_tree();
    tree.show_tree();
    cout << tree.contains_key(37) << endl;
    cout << tree.contains_key(59) << endl;
    cout << tree.contains_key(91) << endl;
    cout << tree.contains_key(51) << endl;
    cout << tree.contains_key(100) << endl;
    cout << tree.contains_key(30) << endl;
    cout << tree.contains_key(76) << endl;
}

int main()
{
    int i = 15;
    i = i / 7 * 7;
    cout << i << endl;
    //test_page();
    test_tree();
    printf("hello world!\n");
    //keep_window_open();
}
