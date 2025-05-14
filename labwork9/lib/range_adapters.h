#pragma once

#include <iterator>
#include <type_traits>
#include <utility>

namespace ra {

template<typename T>
using iter_t = decltype(std::begin(std::declval<T&>()));

template<typename Range, typename Predicate>
class filter_view {
    Range range_;
    Predicate pred_;
public:
    filter_view(Range range, Predicate pred)
        : range_(std::move(range)), pred_(std::move(pred)) {}

    class iterator {
        iter_t<Range> curr_, end_;
        Predicate* pred_;
        void skip_to_valid() {
            while (curr_ != end_ && !(*pred_)(*curr_)) ++curr_;
        }
    public:
        iterator(iter_t<Range> curr, iter_t<Range> end, Predicate* pred)
            : curr_(curr), end_(end), pred_(pred) { skip_to_valid(); }
        auto operator*() const { return *curr_; }
        iterator& operator++() { ++curr_; skip_to_valid(); return *this; }
        bool operator!=(const iterator& o) const { return curr_ != o.curr_; }
    };

    iterator begin() { return {std::begin(range_), std::end(range_), &pred_}; }
    iterator end()   { return {std::end(range_),   std::end(range_),   &pred_}; }
};

template<typename Predicate>
inline auto filter(Predicate pred) {
    return [pred](auto&& rng) {
        using R = std::remove_cvref_t<decltype(rng)>;
        return filter_view<R, Predicate>(std::forward<decltype(rng)>(rng), pred);
    };
}

template<typename Range, typename Func>
class transform_view {
    Range range_;
    Func func_;
public:
    transform_view(Range range, Func func)
        : range_(std::move(range)), func_(std::move(func)) {}

    class iterator {
        iter_t<Range> curr_;
        Func* func_;
    public:
        iterator(iter_t<Range> curr, Func* func)
            : curr_(curr), func_(func) {}
        auto operator*() const { return (*func_)(*curr_); }
        iterator& operator++() { ++curr_; return *this; }
        bool operator!=(const iterator& o) const { return curr_ != o.curr_; }
    };

    iterator begin() { return {std::begin(range_), &func_}; }
    iterator end()   { return {std::end(range_),   &func_}; }
};

template<typename Func>
inline auto transform(Func func) {
    return [func](auto&& rng) {
        using R = std::remove_cvref_t<decltype(rng)>;
        return transform_view<R, Func>(std::forward<decltype(rng)>(rng), func);
    };
}

template<typename Range, typename Size>
class take_view {
    Range range_;
    Size count_;
public:
    take_view(Range range, Size count)
        : range_(std::move(range)), count_(count) {}

    class iterator {
        iter_t<Range> curr_;
        Size rem_;
    public:
        iterator(iter_t<Range> curr, Size rem)
            : curr_(curr), rem_(rem) {}
        auto operator*() const { return *curr_; }
        iterator& operator++() { ++curr_; if (rem_>0) --rem_; return *this; }
        bool operator!=(const iterator& o) const { return rem_>0 && curr_ != o.curr_; }
    };

    iterator begin() { return {std::begin(range_), count_}; }
    iterator end()   { return {std::end(range_),   0}; }
};

template<typename Size>
inline auto take(Size count) {
    return [count](auto&& rng) {
        using R = std::remove_cvref_t<decltype(rng)>;
        return take_view<R, Size>(std::forward<decltype(rng)>(rng), count);
    };
}

template<typename Range, typename Size>
class drop_view {
    Range range_;
    Size count_;
public:
    drop_view(Range range, Size count)
        : range_(std::move(range)), count_(count) {}

    class iterator {
        iter_t<Range> curr_, end_;
    public:
        iterator(iter_t<Range> curr, iter_t<Range> end, Size to_skip)
            : curr_(curr), end_(end) {
            for(Size i=0;i<to_skip&&curr_!=end_;++i) ++curr_;
        }
        auto operator*() const { return *curr_; }
        iterator& operator++() { ++curr_; return *this; }
        bool operator!=(const iterator& o) const { return curr_ != o.curr_; }
    };

    iterator begin() { return {std::begin(range_), std::end(range_), count_}; }
    iterator end()   { return {std::end(range_),   std::end(range_),   0}; }
};

template<typename Size>
inline auto drop(Size count) {
    return [count](auto&& rng) {
        using R = std::remove_cvref_t<decltype(rng)>;
        return drop_view<R, Size>(std::forward<decltype(rng)>(rng), count);
    };
}

template<typename Range>
class reverse_view {
    Range range_;
public:
    reverse_view(Range range) : range_(std::move(range)) {}

    class iterator {
        iter_t<Range> curr_;
    public:
        iterator(iter_t<Range> curr) : curr_(curr) {}
        auto operator*() const { auto tmp=curr_; return *--tmp; }
        iterator& operator++() { --curr_; return *this; }
        bool operator!=(const iterator& o) const { return curr_!=o.curr_; }
    };

    iterator begin() { return {std::end(range_)}; }
    iterator end()   { return {std::begin(range_)}; }
};

inline auto reverse = [](auto&& rng) {
    using R = std::remove_cvref_t<decltype(rng)>;
    return reverse_view<R>(std::forward<decltype(rng)>(rng));
};

template<typename Range>
class keys_view {
    Range range_;
public:
    keys_view(Range range) : range_(std::move(range)) {}

    class iterator {
        iter_t<Range> curr_;
    public:
        iterator(iter_t<Range> curr) : curr_(curr) {}
        auto operator*() const { return curr_->first; }
        iterator& operator++() { ++curr_; return *this; }
        bool operator!=(const iterator& o) const { return curr_!=o.curr_; }
    };

    iterator begin() { return {std::begin(range_)}; }
    iterator end()   { return {std::end(range_)}; }
};

inline auto keys = [](auto&& rng) {
    using R = std::remove_cvref_t<decltype(rng)>;
    return keys_view<R>(std::forward<decltype(rng)>(rng));
};

template<typename Range>
class values_view {
    Range range_;
public:
    values_view(Range range) : range_(std::move(range)) {}

    class iterator {
        iter_t<Range> curr_;
    public:
        iterator(iter_t<Range> curr) : curr_(curr) {}
        auto operator*() const { return curr_->second; }
        iterator& operator++() { ++curr_; return *this; }
        bool operator!=(const iterator& o) const { return curr_!=o.curr_; }
    };

    iterator begin() { return {std::begin(range_)}; }
    iterator end()   { return {std::end(range_)}; }
};

inline auto values = [](auto&& rng) {
    using R = std::remove_cvref_t<decltype(rng)>;
    return values_view<R>(std::forward<decltype(rng)>(rng));
};

template<typename Range, typename Adapter>
auto operator|(Range&& rng, Adapter adapter) {
    return adapter(std::forward<Range>(rng));
}

} // namespace ra

