#ifndef BT_NODE_HPP
#define BT_NODE_HPP

#include <concepts>
#include <cstdint>

// ------------------------------------------------------------------
// -- BTNode
struct BTNode
{
    // BTNode child types.
    enum Childs { Sequence, Selector };

    // Status.
    enum class Status : std::uint8_t { SUCCESS, FAIL, RUNNING };

    // Ctor.
    BTNode()          = default;
    // Dtor.
    virtual ~BTNode() = default;

    // Custom deleter of the node (because of storage).
    // This way because we are using a memory pool.
    struct Deleter { void operator()(BTNode* n) { n->~BTNode(); } };

    BTNode(BTNode const&)            = delete;
    BTNode(BTNode &&)                = delete;
    BTNode& operator=(BTNode const&) = delete;
    BTNode& operator=(BTNode &&)     = delete;

    // Virtual functions.
    // run
    virtual Status run() noexcept = 0;
};

// ------------------------------------------------------------------
// -- Concept
struct BTNode;
template <typename type_t>
concept BTNodeType_t = std::derived_from<type_t, BTNode>;

#endif