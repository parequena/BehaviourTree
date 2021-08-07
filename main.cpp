#include <iostream>
#include <BTNodeChilds.hpp>
#include <BehaivourTree.hpp>

// ------------------------------------------------------------------
// -- Point2D
struct Point2D { uint32_t x{}, y{}; };

// ------------------------------------------------------------------
// -- Player
struct Player_t
{
    Point2D m_currentPosition;
    std::string m_name { "ApoCa" };
};

// ------------------------------------------------------------------
// -- BTActionMove_t
struct BTActionMove_t : BTNode
{
    BTActionMove_t(Point2D const& speed) : m_speed{speed} { }
    
    // run
    Status run(Player_t& player) noexcept final
    {
        player.m_currentPosition.x += m_speed.x;
        player.m_currentPosition.y += m_speed.y;

        return Status::SUCCESS;
    }

private:
    Point2D m_speed {};
};

// ------------------------------------------------------------------
// -- BTBoolean_t : Fails if false.
struct BTBoolean_t : BTNode
{
    BTBoolean_t(bool b) : m_b{b} { }
    
    // run
    Status run(Player_t& player) noexcept final
    {
        m_b = !m_b;

        if(m_b) return Status::SUCCESS;
        return Status::FAIL;
    }

private:
    bool m_b { false };
};

// ------------------------------------------------------------------
// -- BTSayName_t : Just says name and return success.
struct BTSayName_t : BTNode
{
    BTSayName_t() { }
    
    // run
    Status run(Player_t& player) noexcept final
    {
        std::cout << "\tName: " << player.m_name;
        return Status::SUCCESS;
    }
};


int main()
{
    BehaivourTree_t bt {};
    Player_t player;

    bt.createNode<BTNode_t<BTNode::Selector>>(           // 3. Then this one is going to look-up next branch. // 6. Then this is going to return SUCCESS.
            &bt.createNode<BTNode_t<BTNode::Sequence>> ( // 2. So, this is going to FAIL.
                    &bt.createNode<BTBoolean_t>( false ) // 1. First iteration will return FAIL. // 5. Then this is going to return SUCCESS.
                ,   &bt.createNode<BTSayName_t>( )
            )
        ,   &bt.createNode<BTNode_t<BTNode::Sequence>> ( // 4. This branch is going to return SUCCESS.
                    &bt.createNode<BTActionMove_t> ( Point2D { .x=1, .y=0 } )
                ,   &bt.createNode<BTActionMove_t> ( Point2D { .x=0, .y=2 } )
        )
    );
    
    do
    {
        std::cout << "Player (" << player.m_currentPosition.x << ", " << player.m_currentPosition.y << ")";
        bt.run(player);
    } while (std::cin.get());

    return 0;
}