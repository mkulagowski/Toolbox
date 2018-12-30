#pragma once

#include <type_traits>

// for checking templates with type args
template <template <typename...> class Base, typename Derived>
struct _is_base_of_template_type
{
	using U = typename std::remove_cv<Derived>::type;

	template <typename... Args>
	static std::true_type test(Base<Args...>*);

	static std::false_type test(void*);

	using type = decltype(test(std::declval<U*>()));
};

template <template <typename...> class Base, typename Derived>
using is_base_of_template = typename _is_base_of_template_type<Base, Derived>::type;

template <template <typename...> class Base, typename Derived>
inline constexpr bool is_base_of_template_v = is_base_of_template<Base, Derived>::value;


// for checking templates with value args, the type of the values needs to be given
template <typename ArgT, template <ArgT...> class Base, typename Derived>
struct _is_base_of_template_val
{
	using U = typename std::remove_cv<Derived>::type;

	template <ArgT... Args>
	static std::true_type test(Base<Args...>*);

	static std::false_type test(void*);

	using type = decltype(test(std::declval<U*>()));
};

template <typename ArgT, template <ArgT...> class Base, typename Derived>
using is_base_of_val_template = typename _is_base_of_template_val<ArgT, Base, Derived>::type;

template <typename ArgT, template <ArgT...> class Base, typename Derived>
inline constexpr bool is_base_of_val_template_v = is_base_of_val_template<ArgT, Base, Derived>::value;

template<intmax_t N, intmax_t F>
class nieratio {

};