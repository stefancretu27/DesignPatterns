#pragma once

template<class T>
struct check_type
{
    static constexpr bool is_ref(){return false;};
    static constexpr bool is_ptr(){return false;};
    static constexpr bool is_uptr(){return false;};
};

template<class T>
struct check_type<T&>
{
    static  constexpr bool is_ref(){return true;};
    static constexpr  bool is_ptr(){return false;};
    static  constexpr bool is_uptr(){return false;};
};

template<class T>
struct check_type<T*>
{
    static constexpr bool is_ref(){return false;};
    static constexpr bool is_ptr(){return true;};
    static constexpr bool is_uptr(){return false;};
};

template<class T>
struct check_type<const unique_ptr<T>&>
{
    static  constexpr bool is_ref(){return false;};
    static constexpr  bool is_ptr(){return false;};
    static  constexpr bool is_uptr(){return true;};
};