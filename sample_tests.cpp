//
// Created by MARK FONTENOT on 9/14/21.
//

/**
 * This file contains some simple tests.
 *
 * DO NOT add the #define CATCH_CONFIG_RUNNER to this file.
 * It is already in catch_setup.cpp
 *
 * Note that you can have more than one cpp file with tests in them.
 * For example, you could have a test file for your DSString and a
 * separate one for your DSVector.
 */

#include "catch.hpp"
#include "DSLinkedList.h"
#include "DSStack.h"

TEST_CASE("Testing", "[Example]") {
    REQUIRE(4 == 4);
}

TEST_CASE("DSLinkedList", "[DSLinkedList]") {
    DSLinkedList<int> super;
    DSLinkedList<int>* superP = new DSLinkedList<int>();
    int* nums = new int[12]{0,1,2,3,4,5,6,7,8,9,10,11};
    for (int i = 0; i < 10; i++) {
        super.push_back(nums[i]);
        superP->push_back(nums[i]);
    }

    SECTION("Constructor") {
        // Constructor
        REQUIRE(!super.isEmpty());
        REQUIRE(super.getHead()->data == nums[0]);
        REQUIRE(super.getTail()->data == nums[9]);
        REQUIRE(super.getHead()->next != nullptr);
        REQUIRE(super.getHead()->prev == nullptr);
        REQUIRE(super.getTail()->prev != nullptr);
        REQUIRE(super.getTail()->next == nullptr);
    }

    SECTION("Copy Constructor") {
        DSLinkedList<int> copy(super);
        DSLinkedList<int>* copyP = new DSLinkedList<int>(*superP);

        REQUIRE(copy == super);
        REQUIRE(*copyP == *superP);

        REQUIRE(copy.getHead() != super.getHead());
        REQUIRE(copy.getTail() != super.getTail());
        REQUIRE(copy.getHead()->next != nullptr);
        REQUIRE(copy.getHead()->prev == nullptr);
        REQUIRE(copy.getTail()->prev != nullptr);
        REQUIRE(copy.getTail()->next == nullptr);

        REQUIRE(copyP->getHead() != superP->getHead());
        REQUIRE(copyP->getTail() != superP->getTail());
        REQUIRE(copyP->getHead()->next != nullptr);
        REQUIRE(copyP->getHead()->prev == nullptr);
        REQUIRE(copyP->getTail()->prev != nullptr);
        REQUIRE(copyP->getTail()->next == nullptr);
    }

    SECTION("Assignment Operator") {
        DSLinkedList<int> copy;
        DSLinkedList<int>* copyP = new DSLinkedList<int>();
        REQUIRE(copy.isEmpty());
        REQUIRE(copyP->isEmpty());
        copy = super;
        *copyP = *superP;

        REQUIRE(copy == super);
        REQUIRE(*copyP == *superP);

        REQUIRE(copy.getHead() != super.getHead());
        REQUIRE(copy.getTail() != super.getTail());
        REQUIRE(copy.getHead()->next != nullptr);
        REQUIRE(copy.getHead()->prev == nullptr);
        REQUIRE(copy.getTail()->prev != nullptr);
        REQUIRE(copy.getTail()->next == nullptr);

        REQUIRE(copyP->getHead() != superP->getHead());
        REQUIRE(copyP->getTail() != superP->getTail());
        REQUIRE(copyP->getHead()->next != nullptr);
        REQUIRE(copyP->getHead()->prev == nullptr);
        REQUIRE(copyP->getTail()->prev != nullptr);
        REQUIRE(copyP->getTail()->next == nullptr);
    }

    SECTION("Get methods") {
        REQUIRE(super.getHead()->data == nums[0]);
        REQUIRE(super.getHead()->next->data == nums[1]);
        REQUIRE(super.getTail()->data == nums[9]);
        REQUIRE(super.getTail()->prev->data == nums[8]);
    }

    SECTION("Itr methods") {
        REQUIRE(super.getItr() == super.getHead());

        super.moveItr();
        REQUIRE(super.getItr() == super.getHead()->next);

        super.resetItr();
        REQUIRE(super.getItr() == super.getHead());
    }

    SECTION("Push methods") {
        super.push_back(nums[10]);
        REQUIRE(super.getTail()->data == nums[10]);

        super.push_front(nums[11]);
        REQUIRE(super.getHead()->data == nums[11]);
        REQUIRE(super.getItr()->data == nums[11]);
    }

    SECTION("Pop methods") {
        super.pop_front();
        REQUIRE(super.getHead()->data == nums[1]);
        REQUIRE(super.getHead()->prev == nullptr);

        super.pop_back();
        REQUIRE(super.getTail()->data == nums[8]);
        REQUIRE(super.getTail()->next == nullptr);
    }

    SECTION("Insert methods") {
        super.insertAfter(nums[0], nums[10]);
        REQUIRE(super.getHead()->data == nums[0]);
        REQUIRE(super.getHead()->next->data == nums[10]);
        REQUIRE(super.getHead()->next->prev == super.getHead());

        super.insertBefore(nums[9], nums[11]);
        REQUIRE(super.getTail()->data == nums[9]);
        REQUIRE(super.getTail()->prev->data == nums[11]);
        REQUIRE(super.getTail()->prev->next == super.getTail());

        super.insertBefore(nums[0], nums[11]);
        REQUIRE(super.getHead()->data == nums[11]);
        REQUIRE(super.getItr() == super.getHead());

        super.insertAfter(nums[9], nums[10]);
        REQUIRE(super.getTail()->data == nums[10]);
    }

    SECTION("Contains method") {
        REQUIRE(super.contains(nums[0]));
        REQUIRE(super.contains(nums[9]));
        REQUIRE(super.contains(nums[5]));
        REQUIRE(!super.contains(nums[10]));
    }

    SECTION("Find method") {
        REQUIRE(super.find(nums[0])->data == nums[0]);
        REQUIRE(super.find(nums[9])->data == nums[9]);
        REQUIRE(super.find(nums[5])->data == nums[5]);
        REQUIRE(super.find(nums[10]) == nullptr);
    }

    SECTION("Remove method") {
        super.remove(nums[0]);
        REQUIRE(super.getHead()->data == nums[1]);
        REQUIRE(super.getItr() == super.getHead());

        super.remove(nums[9]);
        REQUIRE(super.getTail()->data == nums[8]);

        super.remove(nums[5]);
        REQUIRE(!super.contains(nums[5]));
    }

    SECTION("toString method") {
        DSLinkedList<int> temp;
        REQUIRE(temp.toString() == "");
        temp.push_back(nums[0]);
        REQUIRE(temp.toString() == "0");
        temp.push_back(nums[2]);
        REQUIRE(temp.toString() == "0 -> 2");
    }
}

TEST_CASE("DSStack", "[DSStack]") {
    DSStack<int> super;
    DSStack<int>* superP = new DSStack<int>();
    int* nums = new int[12]{0,1,2,3,4,5,6,7,8,9,10,11};
    for (int i = 0; i < 10; i++) {
        super.push(nums[i]);
        superP->push(nums[i]);
    }

    SECTION("Constructor") {
        REQUIRE(!super.isEmpty());
        REQUIRE(super.peek() == nums[9]);
        REQUIRE(!superP->isEmpty());
        REQUIRE(superP->peek() == nums[9]);
    }

    SECTION("Copy Constructor") {
        DSStack<int> copy(super);
        DSStack<int>* copyP = new DSStack<int>(*superP);

        REQUIRE(copy == super);
        REQUIRE(*copyP == *superP);
    }

    SECTION("assignment operator") {
        DSStack<int> copy;
        DSStack<int>* copyP = new DSStack<int>();

        REQUIRE(copy.isEmpty());
        REQUIRE(copyP->isEmpty());

        copy = super;
        *copyP = *superP;

        REQUIRE(copy == super);
        REQUIRE(*copyP == *superP);
    }

    SECTION("push method") {
        super.push(nums[10]);
        REQUIRE(super.peek() == nums[10]);
    }

    SECTION("pop and peek methods") {
        super.pop();
        REQUIRE(super.peek() == nums[8]);
        super.pop();
        REQUIRE(super.peek() == nums[7]);
        super.pop();
        REQUIRE(super.peek() == nums[6]);
    }

    SECTION("toString method") {
        DSStack<int> temp;
        REQUIRE(temp.toString() == "");
        temp.push(nums[0]);
        REQUIRE(temp.toString() == "0");
        temp.push(nums[2]);
        REQUIRE(temp.toString() == "0 -> 2");
    }
}