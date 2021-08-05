#ifndef BT_NODE_CHILDS_HPP
#define BT_NODE_CHILDS_HPP

#include <BTNode.hpp>
#include <memory>
#include <vector>
#include <initializer_list>

// ------------------------------------------------------------------
// -- BTNode_t
template <BTNode::Childs type_t>
struct BTNode_t : BTNode
{
    using value_type = BTNode*;
    using container_type = std::vector<value_type>;

    BTNode_t(std::initializer_list<value_type> l)
        : m_nodes{l}
    {

    }

    // run
    Status run() noexcept final
    {
        if( currNodeIt == m_nodes.end() )
            resetSeq();

        auto status = (*currNodeIt)->run();
        if( status == BTNode::Status::SUCCESS )
            priv_succ();
        else if ( status == BTNode::Status::FAIL)
            priv_fail();

        return status;
    }

private:
    // moveIt
    void moveIt()
    {
        if(++currNodeIt == m_nodes.end())
            resetSeq();
    }

    // resetSeq
    void resetSeq() { currNodeIt = m_nodes.begin(); }

    void priv_succ();
    void priv_fail();

    container_type m_nodes {};
    container_type::iterator currNodeIt { m_nodes.begin() };
};

// ------------------------------------------------------------------
// -- Sequence
template <>
void BTNode_t<BTNode::Sequence>::priv_succ()
{
    ++currNodeIt;
    if(currNodeIt == m_nodes.end())
        resetSeq();
}

template <>
void BTNode_t<BTNode::Sequence>::priv_fail()
{
    resetSeq();
}

// ------------------------------------------------------------------
// -- Selector
template <>
void BTNode_t<BTNode::Selector>::priv_succ()
{
    resetSeq();
}

template <>
void BTNode_t<BTNode::Selector>::priv_fail()
{
    ++currNodeIt;
    if(currNodeIt == m_nodes.end())
        resetSeq();
}

#endif /* BT_NODE_CHILDS_HPP */
