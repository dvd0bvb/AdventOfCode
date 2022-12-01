#pragma once

#include <ranges>
#include <vector>
#include <algorithm>

template <std::ranges::view V, class Comp = std::ranges::less>
class sorted_view : public std::ranges::view_interface<sorted_view<V, Comp>>
{
    using view_iterator_t = std::ranges::iterator_t<V>;
    using cache_t = std::vector<view_iterator_t>;
    using cache_iterator_t = std::ranges::iterator_t<cache_type>;

public:
    sorted_view(V view, Comp comp) :
        _view(view),
        _comp(comp)
    {
        _items.reserve(std::ranges::size(_view));
        for (auto iter = std::ranges::begin(_view), end = std::ranges::end(_view); iter != end; ++iter)
        {
            _items.push_back(iter);
        }
    }

    class _Iterator
    {
    public:
        friend class sorted_view;

        _Iterator(sorted_view& owner, cache_iterator_t underlying_iter) :
            _owner(owner),
            _underlying_iter(underlying_iter)
        {

        }

    private:
        auto Increment()
        {
            _owner.FindNext(*this);
        }

        sorted_view& _owner;
        cache_iterator_t _underlying_iter;
    };

    class _Sentinel
    {

    };

    auto begin()
    {

    }

    auto end()
    {
        //return _end;?
    }

private:
    auto FindNext()
    {
        return _Iterator(*this, std::min_element(_items.begin(), _end, [](auto lh, auto rh) {
            return _comp(lh, rh);
            });
    }

    auto FindNext(_Iterator& last_iter)
    {
        //remove 
        //invalidates _items
        auto result = std::ranges::remove(_items.begin(), _end, [](auto item) {
            
            }, last_iter._underlying_iter);

        //update the new end
        _end = std::ranges::end(result);

        //find the next max_element
        auto next = std::min_element(_items.begin(), _end, [](auto lh, auto rh) {
            return _comp(lh, rh);
            });

        last_iter._underlying_iter = next;
    }

    V _view;
    Comp _comp;
    //state cache
    cache_t _items;
    cache_iterator_t _end;
};