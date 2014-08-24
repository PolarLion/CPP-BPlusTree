/*
*/

#include <iostream>
#include <vector>
#include <stdarg.h>

const int INIT_SIZE = 1000;
const int NULL_INDEX = -2;
const int STOP_TAG = -1;
const int LEAF_TAG = -2;
const int KEY_TAG = -3;



template<typename KeyType, typename ValueType>
class BPlusTree {
private:
    const short m;
    int buffer_size;
    int count_page;
    KeyType *keys;
    int *index;

    void depth_first_traversal(int i, int depth) const;

    bool search_in_page(const KeyType& key, int& i, bool& in_keys) const;

    bool is_leaf_index(int i) const {
	return  LEAF_TAG == index[i]; 
    }

    bool is_stop_index(int i) const {
	return  STOP_TAG == index[i];
    }

public:
    BPlusTree(int mm)
	: m(mm)
	, count_page(0)
	, keys(nullptr)
	, index(nullptr)
    {	printf("in BPlusTree()\n"); }
    ~BPlusTree() {
	if ( nullptr != keys ) {
	    delete keys;
	    keys = nullptr;
	}
	if ( nullptr != index ) {
	    delete index;
	    index = nullptr;
	}
	printf("in ~BPlusTree()\n");
    }

    bool create_tree();

    void init_tree();

    void show_tree() const;
    
    bool contains_key(const KeyType& key) const; 

    int insert(const KeyType& key, const ValueType& value);
};

template<typename KeyType, typename ValueType>
int BPlusTree<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value)
{
    int i = 0;
    bool found = false;
    while ( !is_leaf_index(i) ) {
	found = search_in_page(key, i);
    }
     
    return 0;
}

template<typename KeyType, typename ValueType>
bool BPlusTree<KeyType, ValueType>::search_in_page(const KeyType& key, int& i, bool& in_keys) const 
{
    if ( KEY_TAG == index[i] )
	++i;
    int count_step = 0;
    while ( !is_stop_index(i) && count_step++ < m ) {
	//std::cout << keys[index[i]] << std::endl;
	if ( key < keys[index[i]] ) {
	    i = index[i+1];
	    return true;
	}
	else if ( key == keys[index[i]] ) {
	    i = index[i+1];
	    in_keys = true;
	    return true;
	}
	else 
	    i += 2;
    }
    i = index[i-1];
    return false;
}

template<typename KeyType, typename ValueType>
bool BPlusTree<KeyType, ValueType>::contains_key(const KeyType& key) const
{
    int i = 0;
    int count_depth = 0;
    bool found = true;
    bool b;
    while ( !is_leaf_index(i) && found ) {
	found = search_in_page(key, i, b);
	count_depth++;
    }
    int count_step = 1;
    KeyType temp_key;
    if (is_leaf_index(i)) {
	i++;
	count_depth++;
    }
    while ( found && !is_stop_index(i) && count_step < m) {
	temp_key = keys[index[i]];
	if ( key < temp_key ) {
	    std::cout << "finding0 " << key << " uses " << count_depth << " steps to get " << i << std::endl;
	    return false;
	}
	else if ( key == temp_key ) {
	    std::cout << "finding1 " << key << " uses " << count_depth << " steps to get " << i << std::endl;
	    return true;
	}
	else {
	    i += 2;
	}
	count_step++;
	//std::cout << temp_key << " ";
    }
    std::cout << "finding2 " << key << " uses " << count_depth << " steps to get " << i << std::endl;
    return false;
}

template<typename KeyType, typename ValueType>
bool BPlusTree<KeyType, ValueType>::create_tree() 
{
    keys = new KeyType[INIT_SIZE];
    if ( nullptr == keys ) {
	printf("create_tree error\n");
	return false;
    }
    buffer_size = (2 * m + 1) * INIT_SIZE;
    index = new int[buffer_size + 1];
    if ( nullptr == index ) {
	printf("create_tree error\n");
	return false;
    }
    index[buffer_size] = STOP_TAG;
    return true;
}

template<typename KeyType, typename ValueType>
void BPlusTree<KeyType, ValueType>::init_tree()
{
    count_page = 7;
    int i = 0, j = 0;
    keys[i++] = 59;
    keys[i++] = 97;
    keys[i++] = 15;
    keys[i++] = 44;
    keys[i++] = 72;
    keys[i++] = 10;
    keys[i++] = 21;
    keys[i++] = 37;
    keys[i++] = 51;
    keys[i++] = 63;
    keys[i++] = 85;
    keys[i++] = 91;

    index[0] = KEY_TAG;
    index[1] = 0;
    index[2] = 7;
    index[3] = 1;
    index[4] = 14;
    index[5] = STOP_TAG;
    index[6] = STOP_TAG;

    index[7] = KEY_TAG;
    index[8] = 2;
    index[9] = 21;
    index[10] = 3;
    index[11] = 28;
    index[12] = 0;
    index[13] = 35;

    index[14] = KEY_TAG;
    index[15] = 4;
    index[16] = 42;
    index[17] = 1;
    index[18] = 49;
    index[19] = STOP_TAG;
    index[20] = STOP_TAG;

    index[21] = LEAF_TAG;
    index[22] = 5;
    index[23] = -2;
    index[24] = 2;
    index[25] = -2;
    index[26] = STOP_TAG;
    index[27] = STOP_TAG;

    index[28] = LEAF_TAG;
    index[29] = 6;
    index[30] = -3;
    index[31] = 7;
    index[32] = -4;
    index[33] = 3;
    index[34] = -5;

    index[35] = LEAF_TAG;
    index[36] = 8;
    index[37] = -6;
    index[38] = 0;
    index[39] = -7;
    index[40] = STOP_TAG;
    index[41] = STOP_TAG;

    index[42] = LEAF_TAG;
    index[43] = 9;
    index[44] = -8;
    index[45] = 4;
    index[46] = -9;
    index[47] = STOP_TAG;
    index[48] = STOP_TAG;

    index[49] = LEAF_TAG;
    index[50] = 10;
    index[51] = -10;
    index[52] = 11;
    index[53] = -11;
    index[54] = 1;
    index[55] = -12;
}

template<typename KeyType, typename ValueType>
void BPlusTree<KeyType, ValueType>::depth_first_traversal(int i, int depth) const
{
    if ( i < 0 )
	return;
    depth++;
    int count_step = 0;
    i++;
    while ( !is_stop_index(i) && count_step++ < m) {
	std::cout << keys[index[i]] << "-";
	depth_first_traversal(index[i+1], depth);
	std::cout << std::endl;
	for (int j = 0; j < depth && depth > 1; ++j)
	    std::cout << "  ";
	i += 2;
    }
}

template<typename KeyType, typename ValueType>
void BPlusTree<KeyType, ValueType>::show_tree() const
{
    int i = 0;
    int count_nullindex = 0;
    depth_first_traversal(0, 0);
}

