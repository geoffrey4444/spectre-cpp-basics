/*!
@file
@copyright Nils Deppe 2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/

#include <cstddef>
#include <functional>
#include <ostream>
#include <type_traits>
#include <utility>

namespace tuples {

#if __cplusplus >= 201402L
#define TUPLES_LIB_CONSTEXPR_CXX_14 constexpr
#else
#define TUPLES_LIB_CONSTEXPR_CXX_14
#endif

namespace tuples_detail {

template <class T>
inline constexpr T&& forward(
    typename std::remove_reference<T>::type& t) noexcept {
  return static_cast<T&&>(t);
}

template <class T>
inline constexpr T&& forward(
    typename std::remove_reference<T>::type&& t) noexcept {
  static_assert(!std::is_lvalue_reference<T>::value,
                "cannot forward an rvalue as an lvalue");
  return static_cast<T&&>(t);
}

template <class T, T...>
struct value_list {};

template <class...>
struct typelist {};

template <typename... Ts>
struct make_void {
  typedef void type;
};
template <typename... Ts>
using void_t = typename make_void<Ts...>::type;

template <bool... Bs>
using all = typename std::is_same<
    value_list<bool, Bs...>,
    value_list<bool, (static_cast<void>(Bs), true)...>>::type;

struct no_such_type {
  no_such_type() = delete;
  no_such_type(no_such_type const& /*unused*/) = delete;
  no_such_type(no_such_type&& /*unused*/) = delete;
  ~no_such_type() = delete;
  no_such_type& operator=(no_such_type const& /*unused*/) = delete;
  no_such_type operator=(no_such_type&& /*unused*/) = delete;
};

namespace detail {
using std::swap;

template <class T, class S,
          bool = not std::is_void<T>::value and not std::is_void<S>::value>
struct is_swappable_with {
  template <class L, class R>
  static auto test_swap(int)
      -> decltype(swap(std::declval<L&>(), std::declval<R&>()));
  template <class L, class R>
  static tuples::tuples_detail::no_such_type test_swap(...);

  static const bool value =
      not std::is_same<decltype(test_swap<T, S>(0)),
                       tuples::tuples_detail::no_such_type>::value and
      not std::is_same<decltype(test_swap<S, T>(0)),
                       tuples::tuples_detail::no_such_type>::value;
};

template <class T, class S>
struct is_swappable_with<T, S, false> : std::false_type {};
}  // namespace detail

template <class T, class S>
using is_swappable_with = detail::is_swappable_with<T, S>;

template <class T, class S, bool = is_swappable_with<T, S>::value>
struct is_nothrow_swappable_with {
 private:
  static constexpr bool check() {
    using std::swap;
    return noexcept(swap(std::declval<T&>(), std::declval<S&>())) and
           noexcept(swap(std::declval<S&>(), std::declval<T&>()));
  }

 public:
  static const bool value = check();
};

template <class T, class S>
struct is_nothrow_swappable_with<T, S, false> : std::false_type {};

template <typename... Ts>
constexpr char swallow(Ts&&...) noexcept {
  return '0';
}
}  // namespace tuples_detail

namespace tuples_detail {
template <class Tag,
          bool Ebo = std::is_empty<typename Tag::type>::value &&
                     !__is_final(typename Tag::type)>
class tagged_tuple_leaf;

template <class T, bool B>
void swap(tagged_tuple_leaf<T, B>& lhs, tagged_tuple_leaf<T, B>& rhs) noexcept(
    is_nothrow_swappable_with<typename T::type, typename T::type>::value) {
  using std::swap;
  swap(lhs.get(), rhs.get());
}

template <class Tag>
class tagged_tuple_leaf<Tag, false> {
  using value_type = typename Tag::type;
  value_type value_;

  template <class T>
  static constexpr bool can_bind_reference() noexcept {
    using rem_ref_value_type = typename std::remove_reference<value_type>::type;
    using rem_ref_T = typename std::remove_reference<T>::type;
    using is_lvalue_type = std::integral_constant<
        bool,
        std::is_lvalue_reference<T>::value or
            std::is_same<std::reference_wrapper<rem_ref_value_type>,
                         rem_ref_T>::value or
            std::is_same<std::reference_wrapper<typename std::remove_const<
                             rem_ref_value_type>::type>,
                         rem_ref_T>::value>;
    return not std::is_reference<value_type>::value or
           (std::is_lvalue_reference<value_type>::value and
            is_lvalue_type::value) or
           (std::is_rvalue_reference<value_type>::value and
            not std::is_lvalue_reference<T>::value);
  }

 public:
  // Tested in constexpr context in Unit.tagged_tuple.Ebo
  constexpr tagged_tuple_leaf() noexcept(
      std::is_nothrow_default_constructible<value_type>::value)
      : value_() {
    static_assert(
        !std::is_reference<value_type>::value,
        "Cannot default construct a reference element in a tagged_tuple");
  }

  template <class T,
            typename std::enable_if<
                !std::is_same<typename std::decay<T>::type,
                              tagged_tuple_leaf>::value &&
                std::is_constructible<value_type, T&&>::value>::type* = nullptr>
  constexpr explicit tagged_tuple_leaf(T&& t) noexcept(
      std::is_nothrow_constructible<value_type, T&&>::value)
      : value_(tuples_detail::forward<T>(t)) {
    static_assert(can_bind_reference<T>(),
                  "Cannot construct an lvalue reference with an rvalue");
  }

  constexpr tagged_tuple_leaf(tagged_tuple_leaf const& /*rhs*/) = default;
  constexpr tagged_tuple_leaf(tagged_tuple_leaf&& /*rhs*/) = default;

#if __cplusplus < 201402L
  value_type& get() noexcept { return value_; }
#else
  constexpr value_type& get() noexcept { return value_; }
#endif
  constexpr const value_type& get() const noexcept { return value_; }

  bool swap(tagged_tuple_leaf& t) noexcept(
      is_nothrow_swappable_with<tagged_tuple_leaf, tagged_tuple_leaf>::value) {
    using std::swap;
    swap(*this, t);
    return false;
  }
};

template <class Tag>
class tagged_tuple_leaf<Tag, true> : private Tag::type {
  using value_type = typename Tag::type;

 public:
  constexpr tagged_tuple_leaf() noexcept(
      std::is_nothrow_default_constructible<value_type>::value)
      : value_type{} {}

  template <class T,
            typename std::enable_if<
                !std::is_same<typename std::decay<T>::type,
                              tagged_tuple_leaf>::value &&
                std::is_constructible<value_type, T&&>::value>::type* = nullptr>
  constexpr explicit tagged_tuple_leaf(T&& t) noexcept(
      std::is_nothrow_constructible<value_type, T&&>::value)
      : value_type(tuples_detail::forward<T>(t)) {}

  constexpr tagged_tuple_leaf(tagged_tuple_leaf const& /*rhs*/) = default;
  constexpr tagged_tuple_leaf(tagged_tuple_leaf&& /*rhs*/) = default;

#if __cplusplus < 201402L
  value_type& get() noexcept { return static_cast<value_type&>(*this); }
#else
  constexpr value_type& get() noexcept {
    return static_cast<value_type&>(*this);
  }
#endif

  constexpr const value_type& get() const noexcept {
    return static_cast<const value_type&>(*this);
  }

  bool swap(tagged_tuple_leaf& t) noexcept(
      is_nothrow_swappable_with<tagged_tuple_leaf, tagged_tuple_leaf>::value) {
    using std::swap;
    swap(*this, t);
    return false;
  }
};

struct disable_constructors {
  static constexpr bool enable_default() noexcept { return false; }
  static constexpr bool enable_explicit() noexcept { return false; }
  static constexpr bool enable_implicit() noexcept { return false; }
};
}  // namespace tuples_detail

/*!
 * \brief A compile time associative container between structs and data
 *
 * The template parameters to `tagged_tuple` are `struct`s with a member type
 * alias, `type` denoting the type of the data to be associated with the tag.
 * An example tag is:
 * \snippet runtime_tests.cpp example_tag_simple
 * A tagged_tuple is created by, for example
 * \snippet runtime_tests.cpp example_simple_create
 * Elements are retrieved using the `get` functions as follows:
 * \snippet runtime_tests.cpp example_get_function
 */
template <class... Tags>
class tagged_tuple;

template <class Tag, class... Tags>
constexpr const typename Tag::type& get(
    const tagged_tuple<Tags...>& t) noexcept;
template <class Tag, class... Tags>
constexpr typename Tag::type& get(tagged_tuple<Tags...>& t) noexcept;
template <class Tag, class... Tags>
constexpr const typename Tag::type&& get(
    const tagged_tuple<Tags...>&& t) noexcept;
template <class Tag, class... Tags>
constexpr typename Tag::type&& get(tagged_tuple<Tags...>&& t) noexcept;

/*!
 * \brief Metafunction that returns the type of the Tag
 */
template <class Tag>
using tag_type = typename Tag::type;

template <class... Tags>
class tagged_tuple : private tuples_detail::tagged_tuple_leaf<Tags>... {
  template <class... Args>
  struct pack_is_tagged_tuple : std::false_type {};
  template <class Arg>
  struct pack_is_tagged_tuple<Arg>
      : std::is_same<typename std::decay<Arg>::type, tagged_tuple> {};

  template <bool EnableConstructor, class Dummy = void>
  struct args_constructor : tuples_detail::disable_constructors {};

  template <class Dummy>
  struct args_constructor<true, Dummy> {
    static constexpr bool enable_default() {
      return tuples_detail::all<
          std::is_default_constructible<tag_type<Tags>>::value...>::value;
    }

    template <class... Ts>
    static constexpr bool enable_explicit() noexcept {
      return tuples_detail::all<
                 std::is_constructible<tuples_detail::tagged_tuple_leaf<Tags>,
                                       Ts>::value...>::value and
             not tuples_detail::all<
                 std::is_convertible<Ts, tag_type<Tags>>::value...>::value;
    }
    template <class... Ts>
    static constexpr bool enable_implicit() noexcept {
      return sizeof...(Ts) == sizeof...(Tags) and
             tuples_detail::all<
                 std::is_constructible<tuples_detail::tagged_tuple_leaf<Tags>,
                                       Ts>::value...>::value and
             tuples_detail::all<
                 std::is_convertible<Ts, tag_type<Tags>>::value...>::value;
    }
  };

  template <bool EnableConstructor, bool = sizeof...(Tags) == 1,
            class Dummy = void>
  struct tuple_like_constructor : tuples_detail::disable_constructors {};

  template <class Dummy>
  struct tuple_like_constructor<true, false, Dummy> {
    template <class Tuple, class... Ts>
    static constexpr bool enable_explicit() noexcept {
      return not tuples_detail::all<
          std::is_convertible<Ts, tag_type<Tags>>::value...>::value;
    }

    template <class Tuple, class... Ts>
    static constexpr bool enable_implicit() noexcept {
      return tuples_detail::all<
          std::is_convertible<Ts, tag_type<Tags>>::value...>::value;
    }
  };

  template <class Dummy>
  struct tuple_like_constructor<true, true, Dummy> {
    template <class Tuple, class... Ts>
    static constexpr bool enable_explicit() noexcept {
      return not tuples_detail::all<
                 std::is_convertible<Ts, tag_type<Tags>>::value...>::value and
             (not tuples_detail::all<std::is_convertible<
                  Tuple, tag_type<Tags>>::value...>::value and
              not tuples_detail::all<std::is_constructible<
                  tag_type<Tags>, Tuple>::value...>::value and
              not tuples_detail::all<
                  std::is_same<tag_type<Tags>, Ts>::value...>::value);
    }

    template <class Tuple, class... Ts>
    static constexpr bool enable_implicit() noexcept {
      return tuples_detail::all<
                 std::is_convertible<Ts, tag_type<Tags>>::value...>::value and
             (not tuples_detail::all<std::is_convertible<
                  Tuple, tag_type<Tags>>::value...>::value and
              not tuples_detail::all<std::is_constructible<
                  tag_type<Tags>, Tuple>::value...>::value and
              not tuples_detail::all<
                  std::is_same<tag_type<Tags>, Ts>::value...>::value);
    }
  };

  // C++17 Draft 23.5.3.2 Assignment - helper aliases
  using is_copy_assignable =
      tuples_detail::all<std::is_copy_assignable<tag_type<Tags>>::value...>;
  using is_nothrow_copy_assignable = tuples_detail::all<
      std::is_nothrow_copy_assignable<tag_type<Tags>>::value...>;
  using is_move_assignable =
      tuples_detail::all<std::is_move_assignable<tag_type<Tags>>::value...>;
  using is_nothrow_move_assignable = tuples_detail::all<
      std::is_nothrow_move_assignable<tag_type<Tags>>::value...>;

  template <class Tag, class... LTags>
  friend constexpr const typename Tag::type& get(
      const tagged_tuple<LTags...>& t) noexcept;
  template <class Tag, class... LTags>
  friend constexpr typename Tag::type& get(tagged_tuple<LTags...>& t) noexcept;
  template <class Tag, class... LTags>
  friend constexpr const typename Tag::type&& get(
      const tagged_tuple<LTags...>&& t) noexcept;
  template <class Tag, class... LTags>
  friend constexpr typename Tag::type&& get(
      tagged_tuple<LTags...>&& t) noexcept;

 public:
  // C++17 Draft 23.5.3.1 Construction
  template <bool Dummy = true,
            typename std::enable_if<
                args_constructor<Dummy>::enable_default()>::type* = nullptr>
  constexpr tagged_tuple() noexcept(
      tuples_detail::all<std::is_nothrow_default_constructible<
          tag_type<Tags>>::value...>::value) {}

  constexpr tagged_tuple(tagged_tuple const& /*rhs*/) = default;
  constexpr tagged_tuple(tagged_tuple&& /*rhs*/) = default;

  template <
      bool Dummy = true,
      typename std::enable_if<args_constructor<Dummy>::template enable_explicit<
          tag_type<Tags> const&...>()>::type* = nullptr>
  constexpr explicit tagged_tuple(tag_type<Tags> const&... ts) noexcept(
      tuples_detail::all<std::is_nothrow_copy_constructible<
          tuples_detail::tagged_tuple_leaf<Tags>>::value...>::value)
      : tuples_detail::tagged_tuple_leaf<Tags>(ts)... {}

  template <
      bool Dummy = true,
      typename std::enable_if<args_constructor<Dummy>::template enable_implicit<
          tag_type<Tags> const&...>()>::type* = nullptr>
  constexpr tagged_tuple(tag_type<Tags> const&... ts) noexcept(
      tuples_detail::all<std::is_nothrow_copy_constructible<
          tuples_detail::tagged_tuple_leaf<Tags>>::value...>::value)
      : tuples_detail::tagged_tuple_leaf<Tags>(ts)... {}

  template <class... Us,
            typename std::enable_if<
                args_constructor<not pack_is_tagged_tuple<Us...>::value and
                                 sizeof...(Us) == sizeof...(Tags)>::
                    template enable_explicit<Us&&...>()>::type* = nullptr>
  constexpr explicit tagged_tuple(Us&&... us) noexcept(
      tuples_detail::all<std::is_nothrow_constructible<
          tuples_detail::tagged_tuple_leaf<Tags>, Us&&>::value...>::value)
      : tuples_detail::tagged_tuple_leaf<Tags>(
            tuples_detail::forward<Us>(us))... {}

  template <class... Us,
            typename std::enable_if<
                args_constructor<not pack_is_tagged_tuple<Us...>::value and
                                 sizeof...(Us) == sizeof...(Tags)>::
                    template enable_implicit<Us&&...>()>::type* = nullptr>
  constexpr tagged_tuple(Us&&... us) noexcept(
      tuples_detail::all<std::is_nothrow_constructible<
          tuples_detail::tagged_tuple_leaf<Tags>, Us&&>::value...>::value)
      : tuples_detail::tagged_tuple_leaf<Tags>(
            tuples_detail::forward<Us>(us))... {}

  template <
      class... UTags,
      typename std::enable_if<
          tuple_like_constructor<
              sizeof...(Tags) == sizeof...(UTags) and
              tuples_detail::all<std::is_constructible<
                  tag_type<Tags>, tag_type<UTags> const&>::value...>::value>::
              template enable_explicit<tagged_tuple<UTags...> const&,
                                       tag_type<UTags>...>()>::type* = nullptr>
  constexpr explicit tagged_tuple(tagged_tuple<UTags...> const& t) noexcept(
      tuples_detail::all<std::is_nothrow_constructible<
          tag_type<Tags>, tag_type<UTags> const&>::value...>::value)
      : tuples_detail::tagged_tuple_leaf<Tags>(get<UTags>(t))... {}

  template <
      class... UTags,
      typename std::enable_if<
          tuple_like_constructor<
              sizeof...(Tags) == sizeof...(UTags) and
              tuples_detail::all<std::is_constructible<
                  tag_type<Tags>, tag_type<UTags> const&>::value...>::value>::
              template enable_implicit<tagged_tuple<UTags...> const&,
                                       tag_type<UTags>...>()>::type* = nullptr>
  constexpr tagged_tuple(tagged_tuple<UTags...> const& t) noexcept(
      tuples_detail::all<std::is_nothrow_constructible<
          tag_type<Tags>, tag_type<UTags> const&>::value...>::value)
      : tuples_detail::tagged_tuple_leaf<Tags>(get<UTags>(t))... {}

  template <
      class... UTags,
      typename std::enable_if<
          tuple_like_constructor<
              sizeof...(Tags) == sizeof...(UTags) and
              tuples_detail::all<std::is_constructible<
                  tag_type<Tags>, tag_type<UTags>&&>::value...>::value>::
              template enable_explicit<tagged_tuple<UTags...>&&,
                                       tag_type<UTags>...>()>::type* = nullptr>
  constexpr explicit tagged_tuple(tagged_tuple<UTags...>&& t) noexcept(
      tuples_detail::all<std::is_nothrow_constructible<
          tag_type<Tags>, tag_type<UTags>&&>::value...>::value)
      : tuples_detail::tagged_tuple_leaf<Tags>(
            tuples_detail::forward<tag_type<UTags>>(get<UTags>(t)))... {}

  template <
      class... UTags,
      typename std::enable_if<
          tuple_like_constructor<
              sizeof...(Tags) == sizeof...(UTags) and
              tuples_detail::all<std::is_constructible<
                  tag_type<Tags>, tag_type<UTags>&&>::value...>::value>::
              template enable_implicit<tagged_tuple<UTags...>&&,
                                       tag_type<UTags>...>()>::type* = nullptr>
  constexpr tagged_tuple(tagged_tuple<UTags...>&& t) noexcept(
      tuples_detail::all<std::is_nothrow_constructible<
          tag_type<Tags>, tag_type<UTags>&&>::value...>::value)
      : tuples_detail::tagged_tuple_leaf<Tags>(
            tuples_detail::forward<tag_type<UTags>>(get<UTags>(t)))... {}

  // C++17 Draft 23.5.3.2 Assignment
  tagged_tuple& operator=(
      typename std::conditional<is_copy_assignable::value, tagged_tuple,
                                tuples_detail::no_such_type>::type const&
          t) noexcept(is_nothrow_copy_assignable::value) {
    static_cast<void>(
        tuples_detail::swallow((get<Tags>(*this) = get<Tags>(t))...));
    return *this;
  }

  tagged_tuple& operator=(
      typename std::conditional<is_move_assignable::value, tagged_tuple,
                                tuples_detail::no_such_type>::type&&
          t) noexcept(is_nothrow_move_assignable::value) {
    static_cast<void>(tuples_detail::swallow(
        (get<Tags>(*this) =
             tuples_detail::forward<tag_type<Tags>>(get<Tags>(t)))...));
    return *this;
  }

  template <class... UTags,
            typename std::enable_if<
                sizeof...(Tags) == sizeof...(UTags) and
                tuples_detail::all<std::is_assignable<
                    tag_type<Tags>&,
                    tag_type<UTags> const&>::value...>::value>::type* = nullptr>
  tagged_tuple& operator=(tagged_tuple<UTags...> const& t) noexcept(
      tuples_detail::all<std::is_nothrow_assignable<
          tag_type<Tags>&, tag_type<UTags> const&>::value...>::value) {
    static_cast<void>(
        tuples_detail::swallow((get<Tags>(*this) = get<UTags>(t))...));
    return *this;
  }

  template <
      class... UTags,
      typename std::enable_if<
          sizeof...(Tags) == sizeof...(UTags) and
          tuples_detail::all<std::is_assignable<
              tag_type<Tags>&, tag_type<UTags>&&>::value...>::value>::type* =
          nullptr>
  tagged_tuple& operator=(tagged_tuple<UTags...>&& t) noexcept(
      tuples_detail::all<std::is_nothrow_assignable<
          tag_type<Tags>&, tag_type<UTags>&&>::value...>::value) {
    static_cast<void>(tuples_detail::swallow(
        (get<Tags>(*this) =
             tuples_detail::forward<tag_type<UTags>>(get<UTags>(t)))...));
    return *this;
  }

  // C++17 Draft 23.5.3.3 swap
  void swap(tagged_tuple& t) noexcept(
      tuples_detail::all<tuples_detail::is_nothrow_swappable_with<
          tuples_detail::tagged_tuple_leaf<Tags>,
          tuples_detail::tagged_tuple_leaf<Tags>>::value...>::value) {
    tuples_detail::swallow(tuples_detail::tagged_tuple_leaf<Tags>::swap(
        static_cast<tuples_detail::tagged_tuple_leaf<Tags>&>(t))...);
  }
};

/// \cond
template <>
class tagged_tuple<> {
 public:
  tagged_tuple() noexcept {}
  void swap(tagged_tuple& /*unused*/) noexcept {}
};
/// \endcond

// C++17 Draft 23.5.3.6 Tuple helper classes
/*!
 * \brief Has a member variable `value` equal to the number of elements in a
 * tagged_tuple
 */
template <class T>
struct tuple_size;

/// \cond
template <class... Tags>
struct tuple_size<tagged_tuple<Tags...>>
    : std::integral_constant<size_t, sizeof...(Tags)> {};
template <class... Tags>
struct tuple_size<const tagged_tuple<Tags...>>
    : tuple_size<tagged_tuple<Tags...>> {};
template <class... Tags>
struct tuple_size<volatile tagged_tuple<Tags...>>
    : tuple_size<tagged_tuple<Tags...>> {};
template <class... Tags>
struct tuple_size<const volatile tagged_tuple<Tags...>>
    : tuple_size<tagged_tuple<Tags...>> {};
/// \endcond

// C++17 Draft 23.5.3.7 Element access
// @{
/*!
 * \brief Retrieve the element with tag `Tag` from the tagged_tuple `t`
 */
template <class Tag, class... Tags>
inline constexpr const typename Tag::type& get(
    const tagged_tuple<Tags...>& t) noexcept {
  return static_cast<const tuples_detail::tagged_tuple_leaf<Tag>&>(t).get();
}
template <class Tag, class... Tags>
inline constexpr typename Tag::type& get(tagged_tuple<Tags...>& t) noexcept {
  return static_cast<tuples_detail::tagged_tuple_leaf<Tag>&>(t).get();
}
template <class Tag, class... Tags>
inline constexpr const typename Tag::type&& get(
    const tagged_tuple<Tags...>&& t) noexcept {
  return static_cast<const typename Tag::type&&>(
      static_cast<const tuples_detail::tagged_tuple_leaf<Tag>&&>(t).get());
}
template <class Tag, class... Tags>
inline constexpr typename Tag::type&& get(tagged_tuple<Tags...>&& t) noexcept {
  return static_cast<typename Tag::type&&>(
      static_cast<tuples_detail::tagged_tuple_leaf<Tag>&&>(t).get());
}
// @}

// C++17 Draft 23.5.3.8 Relational operators
namespace tuples_detail {
struct equal {
  template <class T, class U>
  static TUPLES_LIB_CONSTEXPR_CXX_14 void apply(
      T const& lhs, U const& rhs, bool& result) noexcept(noexcept(lhs == rhs)) {
    result = result and lhs == rhs;
  }
};

template <class... LTags, class... RTags>
TUPLES_LIB_CONSTEXPR_CXX_14 bool tuple_equal_impl(
    tagged_tuple<LTags...> const& lhs,
    tagged_tuple<RTags...> const&
        rhs) noexcept(noexcept(std::initializer_list<bool>{
    (get<LTags>(lhs) == get<RTags>(rhs))...})) {
  bool equal = true;
  // This short circuits in the sense that the operator== is only evaluated if
  // the result thus far is true
  static_cast<void>(std::initializer_list<char>{
      (equal::apply(get<LTags>(lhs), get<RTags>(rhs), equal), '0')...});
  return equal;
}
}  // namespace tuples_detail

template <class... LTags, class... RTags,
          typename std::enable_if<sizeof...(LTags) == sizeof...(RTags)>::type* =
              nullptr>
TUPLES_LIB_CONSTEXPR_CXX_14 bool operator==(
    tagged_tuple<LTags...> const& lhs,
    tagged_tuple<RTags...> const&
        rhs) noexcept(noexcept(tuples_detail::tuple_equal_impl(lhs, rhs))) {
  return tuples_detail::tuple_equal_impl(lhs, rhs);
}

template <class... LTags, class... RTags,
          typename std::enable_if<sizeof...(LTags) == sizeof...(RTags)>::type* =
              nullptr>
TUPLES_LIB_CONSTEXPR_CXX_14 bool operator!=(
    tagged_tuple<LTags...> const& lhs,
    tagged_tuple<RTags...> const& rhs) noexcept(noexcept(lhs == rhs)) {
  return not(lhs == rhs);
}

namespace tuples_detail {
struct less {
  template <class T, class U>
  static TUPLES_LIB_CONSTEXPR_CXX_14 void apply(
      T const& lhs, U const& rhs, bool& last_rhs_less_lhs,
      bool& result) noexcept(noexcept(lhs < rhs) and noexcept(rhs < lhs)) {
    if (result or last_rhs_less_lhs) {
      return;
    }
    result = lhs < rhs;
    if (result) {
      return;
    }
    last_rhs_less_lhs = rhs < lhs;
  }
};

template <class... LTags, class... RTags>
TUPLES_LIB_CONSTEXPR_CXX_14 bool tuple_less_impl(
    tagged_tuple<LTags...> const& lhs,
    tagged_tuple<RTags...> const&
        rhs) noexcept(noexcept(std::initializer_list<bool>{
    (get<LTags>(lhs) < get<RTags>(rhs))...})) {
  bool result = false;
  bool last_rhs_less_lhs = false;
  static_cast<void>(std::initializer_list<char>{
      (less::apply(get<LTags>(lhs), get<RTags>(rhs), last_rhs_less_lhs, result),
       '0')...});
  return result;
}
}  // namespace tuples_detail

template <class... LTags, class... RTags,
          typename std::enable_if<sizeof...(LTags) == sizeof...(RTags)>::type* =
              nullptr>
TUPLES_LIB_CONSTEXPR_CXX_14 bool operator<(
    tagged_tuple<LTags...> const& lhs,
    tagged_tuple<RTags...> const&
        rhs) noexcept(noexcept(tuples_detail::tuple_less_impl(lhs, rhs))) {
  return tuples_detail::tuple_less_impl(lhs, rhs);
}

template <class... LTags, class... RTags,
          typename std::enable_if<sizeof...(LTags) == sizeof...(RTags)>::type* =
              nullptr>
TUPLES_LIB_CONSTEXPR_CXX_14 bool operator>(
    tagged_tuple<LTags...> const& lhs,
    tagged_tuple<RTags...> const& rhs) noexcept(noexcept(rhs < lhs)) {
  return rhs < lhs;
}

template <class... LTags, class... RTags,
          typename std::enable_if<sizeof...(LTags) == sizeof...(RTags)>::type* =
              nullptr>
TUPLES_LIB_CONSTEXPR_CXX_14 bool operator<=(
    tagged_tuple<LTags...> const& lhs,
    tagged_tuple<RTags...> const& rhs) noexcept(noexcept(rhs < lhs)) {
  return not(rhs < lhs);
}

template <class... LTags, class... RTags,
          typename std::enable_if<sizeof...(LTags) == sizeof...(RTags)>::type* =
              nullptr>
TUPLES_LIB_CONSTEXPR_CXX_14 bool operator>=(
    tagged_tuple<LTags...> const& lhs,
    tagged_tuple<RTags...> const& rhs) noexcept(noexcept(lhs < rhs)) {
  return not(lhs < rhs);
}

// C++17 Draft 23.5.3.3 swap
template <
    class... Tags,
    typename std::enable_if<tuples_detail::all<tuples_detail::is_swappable_with<
        tuples_detail::tagged_tuple_leaf<Tags>,
        tuples_detail::tagged_tuple_leaf<Tags>>::value...>::value>::type* =
        nullptr>
void swap(tagged_tuple<Tags...>& lhs, tagged_tuple<Tags...>& rhs) noexcept(
    tuples_detail::all<tuples_detail::is_nothrow_swappable_with<
        tuples_detail::tagged_tuple_leaf<Tags>,
        tuples_detail::tagged_tuple_leaf<Tags>>::value...>::value) {
  lhs.swap(rhs);
}

namespace tuples_detail {
template <class S, class T, class = void_t<>>
struct is_streamable : std::false_type {};
template <class S, class T>
struct is_streamable<
    S, T,
    void_t<decltype(std::declval<typename std::add_lvalue_reference<S>::type>()
                    << std::declval<T>()),
           typename std::enable_if<not std::is_same<S, T>::value>::type>>
    : std::true_type {};

template <class S, class T>
using is_streamable_t = typename is_streamable<S, T>::type;

struct stream_helper {
  template <class T>
  void operator()(std::ostream& os, const T& element, size_t& current_value,
                  const size_t num_tags, const std::true_type /*meta*/) {
    os << element;
    current_value++;
    if (current_value < num_tags) {
      os << std::string(", ");
    }
  }

  template <class T>
  void operator()(std::ostream& os, const T& /*element*/, size_t& current_value,
                  const size_t num_tags, const std::false_type /*meta*/) {
    os << std::string("NOT STREAMABLE");
    current_value++;
    if (current_value < num_tags) {
      os << std::string(", ");
    }
  }
};
}  // namespace tuples_detail

template <class... Tags>
std::ostream& operator<<(std::ostream& os, const tagged_tuple<Tags...>& t) {
  os << std::string("(");
  size_t current_value = 0;
  tuples_detail::stream_helper helper;
  // With empty tagged_tuple's helper is unused
  static_cast<void>(helper);
  static_cast<void>(std::initializer_list<char>{
      (helper(os, get<Tags>(t), current_value, sizeof...(Tags),
              tuples_detail::is_streamable_t<std::ostream, tag_type<Tags>>{}),
       '0')...});
  return os << std::string(")");
}

}  // namespace tuples
