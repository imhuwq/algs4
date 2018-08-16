#include <iostream>

#include "search/rbt.h"

int main() {
    RBT<int, int> rbt;
    rbt.Put(0, 0);
    rbt.Put(-10, -10);
    rbt.Put(10, 10);
    rbt.Put(-20, -20);
    rbt.Put(-5, -5);
    rbt.Delete(0);
    rbt.Delete(-10);
    rbt.Delete(-20);
    rbt.CheckTree();
    DEBUG(rbt.GetSize());
}