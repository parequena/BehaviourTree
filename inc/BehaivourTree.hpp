#ifndef BEHAIVOUR_TREE_HPP
#define BEHAIVOUR_TREE_HPP

#include <BTNode.hpp>
#include <memory>
#include <vector>

// ------------------------------------------------------------------
// -- BehaivourTree_t
struct BehaivourTree_t
{
    using value_type = std::unique_ptr<BTNode>;
    using NodeStrge_t = std::vector<value_type>;
    using MemoryStrge_t = std::unique_ptr<std::byte[]>;

    explicit BehaivourTree_t() noexcept
    {

    }

    void run() noexcept
    {
        if( m_nodes.size() == 0) return;
        m_nodes.back()->run(); // Storing tree backwards (last = root).
    };

    template <BTNodeType_t Node_t, typename... param_t>
    Node_t& createNode(param_t&&... params)
    {
        // Reserve memory.
        m_ptr_res -= sizeof(Node_t);
        if( m_ptr_res < m_mem.get())
        {
            m_ptr_res += sizeof(Node_t);
            throw std::bad_alloc{};
        }

        auto* pnode = new (m_ptr_res) Node_t{std::forward<param_t>(params)...};
        return m_nodes.emplace_back( pnode );
    }
    
private:
    std::size_t   m_memSize { 1024 };
    MemoryStrge_t m_mem     { std::make_unique<std::byte[]>(m_memSize) };
    std::byte*    m_ptr_res { m_mem.get() + m_memSize };
    NodeStrge_t   m_nodes   {};
};

#endif /* BEHAIVOUR_TREE_HPP */
