#ifndef BT_NODE_SEQ
#define BT_NODE_SEQ

// ------------------------------------------------------------------
// -- Sequence
// --   Returns running or fail if one of childs does.
template <>
constexpr void BTNode<Node::Sequence>::priv_succ() noexcept
{
    ++currNodeIt_;
    if(currNodeIt_ == nodes_.end())
        resetSeq();
}

template <>
constexpr void BTNode<Node::Sequence>::priv_fail() noexcept { resetSeq(); }

#endif /* BT_NODE_SEQ */
