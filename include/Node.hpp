#ifndef BT_NODE_HPP
#define BT_NODE_HPP

#include <concepts>
#include <cstdint>

// ------------------------------------------------------------------
// -- Player_t
struct Player_t;
// For an easy testing this Behaivour tree it's directly working on the agent.
// This should be changed to be the agent to have an BTree and BTree maybe should
// modify the game context, or game world.

// ------------------------------------------------------------------
// -- Node
struct Node
{
    // Node child types.
    enum Childs {
            Sequence // Returns running or fail if one of childs does.
        ,   Selector // Returns success when finding first child that does.
    };

    // Status.
    enum class Status : std::uint8_t { SUCCESS, FAIL, RUNNING };

    constexpr explicit Node() noexcept = default;
    virtual ~Node()           noexcept = default;

    // Custom deleter of the node (because of storage).
    // This way because we are using a memory pool.
    struct Deleter { void operator()(Node* n) { n->~Node(); } };

    Node(Node const&)            = delete;
    Node(Node &&)                = delete;
    Node& operator=(Node const&) = delete;
    Node& operator=(Node &&)     = delete;

    // Virtual functions.
    // run
    virtual Status run(Player_t& player) noexcept = 0;
};

// ------------------------------------------------------------------
// -- Concept
struct Node;
template <typename T>
concept NodeType_t = std::derived_from<T, Node>;

#endif