#ifndef BT_NODE_CHILDS_HPP
#define BT_NODE_CHILDS_HPP

#include <Node.hpp>
#include <memory>
#include <vector>
#include <initializer_list>

// ------------------------------------------------------------------
// -- BTNode
template <Node::Childs type_t>
struct BTNode final : Node
{
    using value_type = Node*;
    using container_type = std::vector<value_type>;

    // Ctor.
    constexpr BTNode(std::initializer_list<value_type> l) noexcept
        : nodes_{l}
    { }

    // run
    Status run(Player_t& player) noexcept
    {
        if( currNodeIt_ == nodes_.end() )
            resetSeq();

        auto status = (*currNodeIt_)->run(player);
        if( status == Node::Status::SUCCESS )
            priv_succ();
        else if ( status == Node::Status::FAIL)
            priv_fail();

        return status;
    }

private:
    // moveIt
    constexpr void moveIt() noexcept
    {
        if(++currNodeIt_ == nodes_.end())
            resetSeq();
    }

    // resetSeq
    constexpr void resetSeq() noexcept { currNodeIt_ = nodes_.begin(); }

    constexpr void priv_succ() noexcept;
    constexpr void priv_fail() noexcept;

    container_type nodes_ {};
    container_type::iterator currNodeIt_ { nodes_.begin() };
};

#include "BTNodeSequence.tpp"
#include "BTNodeSelector.tpp"

#endif /* BT_NODE_CHILDS_HPP */
