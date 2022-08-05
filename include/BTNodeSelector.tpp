#ifndef BT_NODE_SEL
#define BT_NODE_SEL

// ------------------------------------------------------------------
// -- Selector
// --   Returns success when finding first child that does.
template <>
constexpr void BTNode<Node::Selector>::priv_succ() noexcept { resetSeq(); }

template <>
constexpr void BTNode<Node::Selector>::priv_fail() noexcept
{
    ++currNodeIt_;
    if(currNodeIt_ == nodes_.end())
        resetSeq();
}

#endif /* BT_NODE_SEL */
