#ifndef BEHAIVOUR_TREE_HPP
#define BEHAIVOUR_TREE_HPP

#include <Node.hpp>
#include <memory>
#include <vector>

// ------------------------------------------------------------------
// -- BehaivourTree
struct BehaivourTree
{
    using value_type = std::unique_ptr<Node, Node::Deleter>;
    using NodeStrge   = std::vector<value_type>;
    using MemoryStrge = std::unique_ptr<std::byte[]>;

    constexpr explicit BehaivourTree() noexcept = default;

    constexpr void run(Player_t& player) noexcept
    {
        if( nodes_.size() == 0) return;
        nodes_.back()->run(player); // Storing tree backwards (last = root).
    };

    template <NodeType_t BTNode, typename... param_t>
    constexpr BTNode& createNode(param_t&&... params)
    {
        // Reserve memory.
        pMem_ -= sizeof(BTNode);
        if( pMem_ < memory_.get())
        {
            pMem_ += sizeof(BTNode);
            throw std::bad_alloc{};
        }

        auto* pnode = new (pMem_) BTNode{ std::forward<param_t>(params)... };
        nodes_.emplace_back( pnode );
        return *pnode;
    }
    
private:
    std::size_t memSize_ { 1024 };
    MemoryStrge memory_  { std::make_unique<std::byte[]>(memSize_) };
    std::byte*  pMem_    { memory_.get() + memSize_ };
    NodeStrge   nodes_   {};
};

#endif /* BEHAIVOUR_TREE_HPP */
