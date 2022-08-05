#include <iostream>
#include <BTNode.hpp>
#include <BehaivourTree.hpp>

#include "helpers.hpp"

int main()
{
    BehaivourTree bt {};
    Player_t player;

    /*
    Steps:
        1 . BTBoolean = false, so return FAIL.
        2 . Sequence fails, so return FAIL.
        3 . Selector its gonna look next branch.
        4 . Sequence returns SUCCESS.
        5 . BTBoolean = true, return SUCCESS.
        6 . Return SUCCESS.

                      SELECTOR
                   /           \
              SEQUENCE         SEQUENCE
            /        \         /      \
        BOOLEAN   SAY_NAME   MOVE      MOVE
    */
    bt.createNode<BTNode<Node::Selector>>(           // 3. Then this one is going to look-up next branch. // 6. Then this is going to return SUCCESS.
            &bt.createNode<BTNode<Node::Sequence>> ( // 2. So, this is going to FAIL.
                    &bt.createNode<BTBoolean_t>( false ) // 1. First iteration will return FAIL. // 5. Then this is going to return SUCCESS.
                ,   &bt.createNode<BTSayName_t>( )
            )
        ,   &bt.createNode<BTNode<Node::Sequence>> ( // 4. This branch is going to return SUCCESS.
                    &bt.createNode<BTActionMove_t> ( Point2D { .x=1, .y=0 } )
                ,   &bt.createNode<BTActionMove_t> ( Point2D { .x=0, .y=2 } )
        )
    );
    
    do
    {
        std::cout << "Player (" << player.currPos_.x << ", " << player.currPos_.y << ")";
        bt.run(player);
    } while (std::cin.get());

    return 0;
}