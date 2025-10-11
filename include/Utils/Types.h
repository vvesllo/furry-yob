#pragma once

#include <vector>
#include <memory>
#include <optional>

namespace Types
{
    template<typename T>
    using uptr_vec = std::vector<std::unique_ptr<T>>;

    template<typename T>
    using uptr_ref_opt = std::optional<std::reference_wrapper<std::unique_ptr<T>>>;
}




