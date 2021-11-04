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
        super.resetItr();
        copy.resetItr();
        superP->resetItr();
        copyP->resetItr();
        while (super.getItr() != nullptr && copy.getItr() != nullptr && superP->getItr() != nullptr && copyP->getItr() != nullptr) {
            REQUIRE(copy.getItr()->data == super.getItr()->data);
            REQUIRE(copyP->getItr()->data == superP->getItr()->data);
            super.moveItr();
            superP->moveItr();
            copy.moveItr();
            copyP->moveItr();
        }
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
        super.resetItr();
        superP->resetItr();
        copy.resetItr();
        copyP->resetItr();
        while (super.getItr() != nullptr && copy.getItr() != nullptr && superP->getItr() != nullptr && copyP->getItr() != nullptr) {
            REQUIRE(copy.getItr()->data == super.getItr()->data);
            REQUIRE(copyP->getItr()->data == superP->getItr()->data);
            super.moveItr();
            superP->moveItr();
            copy.moveItr();
            copyP->moveItr();
        }
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

    SECTION("Destructor") {
        delete superP;
        REQUIRE(superP->isEmpty());
        REQUIRE(superP->getItr() == nullptr);
        REQUIRE(superP->getTail() == nullptr);
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

    SECTION("Remove method") {
        super.remove(nums[0]);
        REQUIRE(super.getHead()->data == nums[1]);
        REQUIRE(super.getItr() == super.getHead());

        super.remove(nums[9]);
        REQUIRE(super.getTail()->data == nums[8]);

        super.remove(nums[5]);
        REQUIRE(!super.contains(nums[5]));
    }

    SECTION("IsEmpty method") {
        REQUIRE(!super.isEmpty());
    }
}

TEST_CASE("DSStack", "[DSStack]") {
    DSStack<int> super;
    int* nums = new int[12]{0,1,2,3,4,5,6,7,8,9,10,11};
    for (int i = 0; i < 10; i++)
        super.push(nums[i]);

    SECTION("Constructor") {
        REQUIRE(!super.isEmpty());
        REQUIRE(super.peek() == nums[9]);
    }

    SECTION("push method") {
        super.push(nums[10]);
        REQUIRE(super.peek() == nums[10]);
    }

    SECTION("pop method") {
        super.pop();
        REQUIRE(super.peek() == nums[8]);
        super.pop();
        REQUIRE(super.peek() == nums[7]);
    }
}