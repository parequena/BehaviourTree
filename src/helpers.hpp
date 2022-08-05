#include <Node.hpp>

// ------------------------------------------------------------------
// -- Point2D
struct Point2D { uint32_t x{}, y{}; };

// ------------------------------------------------------------------
// -- Player
struct Player_t
{
    Point2D currPos_ {};
    std::string name_ { "Pablo" };
};

// ------------------------------------------------------------------
// -- BTActionMove_t
struct BTActionMove_t final : Node
{
    constexpr BTActionMove_t(Point2D const& speed) noexcept
        : speed_{speed} { }
    
    // run
    constexpr Status run(Player_t& player) noexcept
    {
        player.currPos_.x += speed_.x;
        player.currPos_.y += speed_.y;

        return Status::SUCCESS;
    }

private:
    Point2D speed_ {};
};

// ------------------------------------------------------------------
// -- BTBoolean_t : Fails if false.
struct BTBoolean_t final : Node
{
    constexpr BTBoolean_t(bool b) noexcept
        : b_{b} { }
    
    // run
    constexpr Status run(Player_t& player) noexcept
    {
        (void)player; // Unused, because this Node doesn't has any sense.
        b_ = !b_;

        return b_ ? Status::SUCCESS : Status::FAIL;
    }

private:
    bool b_ { false };
};

// ------------------------------------------------------------------
// -- BTSayName_t : Just says name and return success.
struct BTSayName_t final : Node
{
    constexpr BTSayName_t() noexcept = default;
    
    // run
    Status run(Player_t& player) noexcept
    {
        std::cout << "\tName: " << player.name_;
        return Status::SUCCESS;
    }
};
