/*****************************************************************************
 * \file type_traits.hpp
 *
 * \brief This header provides definitions from the C++ header <type_traits>
 *****************************************************************************/

/*
  The MIT License (MIT)

  Copyright (c) 2020 Matthew Rodusek All rights reserved.

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/
#ifndef BPSTD_TYPE_TRAITS_HPP
#define BPSTD_TYPE_TRAITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "config.hpp"
#include "detail/invoke.hpp" // detail::INVOKE

#include <type_traits>
#include <cstddef> // std::size_t

namespace bpstd {

  //============================================================================
  // Type constants
  //============================================================================

  template <typename T, T V>
  using integral_constant = std::integral_constant<T, V>;

  template <bool B>
  using bool_constant = integral_constant<bool,B>;

  using std::true_type;
  using std::false_type;

  template <typename T>
  struct type_identity {
    using type = T;
  };

  namespace detail {
    template <typename T>
    struct make_void : type_identity<void>{};
  } // namespace detail

  template <typename T>
  using void_t = typename detail::make_void<T>::type;

  //============================================================================
  // Metafunctions
  //============================================================================

  template <bool B, typename T = void>
  using enable_if = std::enable_if<B, T>;

  template <bool B, typename T = void>
  using enable_if_t = typename enable_if<B, T>::type;

  //----------------------------------------------------------------------------

  template <bool B, typename True, typename False>
  using conditional = std::conditional<B, True, False>;

  template <bool B, typename True, typename False>
  using conditional_t = typename conditional<B, True, False>::type;

  /// \brief Type trait to determine the bool_constant from a logical
  ///        AND operation of other bool_constants
  ///
  /// The result is aliased as \c ::value
  template<typename...>
  struct conjunction;

  template<typename B1>
  struct conjunction<B1> : B1{};

  template<typename B1, typename... Bn>
  struct conjunction<B1, Bn...>
    : conditional_t<B1::value, conjunction<Bn...>, B1>{};

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template<typename...Bs>
  BPSTD_CPP17_INLINE constexpr auto disconjunction_v = conjunction<Bs...>::value;
#endif

  //----------------------------------------------------------------------------

  /// \brief Type trait to determine the \c bool_constant from a logical
  ///        OR operations of other bool_constant
  ///
  /// The result is aliased as \c ::value
  template<typename...>
  struct disjunction : false_type { };

  template<typename B1>
  struct disjunction<B1> : B1{};

  template<typename B1, typename... Bn>
  struct disjunction<B1, Bn...>
    : conditional_t<B1::value != false, B1, disjunction<Bn...>>{};

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template<typename...Bs>
  BPSTD_CPP17_INLINE constexpr auto disjunction_v = disjunction<Bs...>::value;
#endif

  //----------------------------------------------------------------------------

  /// \brief Utility metafunction for negating a bool_constant
  ///
  /// The result is aliased as \c ::value
  ///
  /// \tparam B the constant
  template<typename B>
  struct negation : bool_constant<!static_cast<bool>(B::value)>{};

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template<typename B>
  BPSTD_CPP17_INLINE constexpr auto negation_v = negation<Bs>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename Fn, typename...Args>
  using is_invocable = detail::is_invocable<Fn, Args...>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template<typename Fn, typename...Args>
  BPSTD_CPP17_INLINE constexpr auto is_invocable_v = is_invocable<Fn, Args...>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename Fn, typename...Args>
  using is_nothrow_invocable = detail::is_nothrow_invocable<Fn, Args...>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template<typename Fn, typename...Args>
  BPSTD_CPP17_INLINE constexpr auto is_nothrow_invocable_v = is_nothrow_invocable<Fn, Args...>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename Fn, typename...Args>
  using invoke_result = detail::invoke_result<Fn,Args...>;

  template <typename Fn, typename...Args>
  using invoke_result_t = typename invoke_result<Fn,Args...>::type;

  //============================================================================
  // Type categories
  //============================================================================

  template <typename T>
  using is_void = std::is_void<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_void_v = is_void<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_null_pointer = std::is_null_pointer<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_null_pointer_v = is_null_pointer<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_array = std::is_array<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_array_v = is_array<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_pointer = std::is_pointer<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_pointer_v = is_pointer<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_enum = std::is_enum<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_enum_v = is_enum<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_union = std::is_union<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_union_v = is_union<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_class = std::is_class<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_class_v = is_class<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_function = std::is_function<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_function_v = is_function<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_object = std::is_object<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_object_v = is_object<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_scalar = std::is_scalar<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_scalar_v = is_scalar<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_compound = std::is_compound<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_compound_v = is_compound<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_integral = std::is_integral<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_integral_v = is_integral<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_floating_point = std::is_floating_point<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_floating_point_v = is_floating_point<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_fundamental = std::is_fundamental<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_fundamental_v = is_fundamental<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_arithmetic = std::is_arithmetic<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_arithmetic_v = is_arithmetic<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_reference = std::is_reference<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_reference_v = is_reference<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_lvalue_reference = std::is_lvalue_reference<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_lvalue_reference_v = is_lvalue_reference<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_rvalue_reference = std::is_rvalue_reference<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_rvalue_reference_v = is_rvalue_reference<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_member_pointer = std::is_member_pointer<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_member_pointer_v = is_member_pointer<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_member_object_pointer = std::is_member_object_pointer<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_member_object_pointer_v = is_member_object_pointer<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_member_function_pointer = std::is_member_function_pointer<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_member_function_pointer_v = is_member_function_pointer<T>::value;
#endif

  //============================================================================
  // Type properties
  //============================================================================

  template <typename T>
  using is_const = std::is_const<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_const_v = is_const<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_volatile = std::is_volatile<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_volatile_v = is_volatile<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_empty = std::is_empty<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_empty_v = is_empty<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_polymorphic = std::is_polymorphic<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_polymorphic_v = is_polymorphic<T>::value;
#endif

  //----------------------------------------------------------------------------

  // is_final is only defined in C++14
#if __cplusplus >= 201402L
  template <typename T>
  using is_final = std::is_final<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_final_v = is_final<T>::value;
#endif
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_abstract = std::is_abstract<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_abstract_v = is_abstract<T>::value;
#endif

  //----------------------------------------------------------------------------

  // is_aggregate is only defined in C++17
#if __cplusplus >= 201703L

  template <typename T>
  using is_aggregate = std::is_aggregate<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_aggregate_v = is_aggregate<T>::value;
#endif
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_trivial = std::is_trivial<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_trivial_v = is_trivial<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_trivially_copyable = std::is_trivially_copyable<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_trivially_copyable_v = is_trivially_copyable<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_standard_layout = std::is_standard_layout<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_standard_layout_v = is_standard_layout<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_literal_type = std::is_literal_type<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_literal_type_v = is_literal_type<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_pod = std::is_pod<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_pod_v = is_pod<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_signed = std::is_signed<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_signed_v = is_signed<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_unsigned = std::is_unsigned<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_unsigned_v = is_unsigned<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  struct is_bounded_array : false_type{};

  template <typename T, std::size_t N>
  struct is_bounded_array<T[N]> : true_type{};

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_bounded_array_v = is_bounded_array<T>::value;
#endif

  //----------------------------------------------------------------------------


  template <typename T>
  struct is_unbounded_array : false_type{};

  template <typename T>
  struct is_unbounded_array<T[]> : true_type{};

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_unbounded_array_v = is_unbounded_array<T>::value;
#endif

  //----------------------------------------------------------------------------

  // has_unique_object_representation only defined in C++17
#if __cplusplus >= 201703L
  template <typename T>
  using has_unique_object_representations = std::has_unique_object_representations<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto has_unique_object_representations_v = has_unique_object_representations<T>::value;
#endif
#endif

  //============================================================================
  // Type Modification
  //============================================================================

  template <typename T>
  using remove_cv = std::remove_cv<T>;

  template <typename T>
  using remove_cv_t = typename remove_cv<T>::type;

  //----------------------------------------------------------------------------

  template <typename T>
  using remove_const = std::remove_const<T>;

  template <typename T>
  using remove_const_t = typename remove_const<T>::type;

  //----------------------------------------------------------------------------

  template <typename T>
  using remove_volatile = std::remove_volatile<T>;

  template <typename T>
  using remove_volatile_t = typename remove_volatile<T>::type;

  //----------------------------------------------------------------------------

  template <typename T>
  using add_cv = std::add_cv<T>;

  template <typename T>
  using add_cv_t = typename add_cv<T>::type;

  //----------------------------------------------------------------------------

  template <typename T>
  using add_const = std::add_const<T>;

  template <typename T>
  using add_const_t = typename add_const<T>::type;

  //----------------------------------------------------------------------------

  template <typename T>
  using add_volatile = std::add_volatile<T>;

  template <typename T>
  using add_volatile_t = typename add_volatile<T>::type;

  //----------------------------------------------------------------------------

  template <typename T>
  using make_signed = std::make_signed<T>;

  template <typename T>
  using make_signed_t = typename make_signed<T>::type;

  //----------------------------------------------------------------------------

  template <typename T>
  using make_unsigned = std::make_unsigned<T>;

  template <typename T>
  using make_unsigned_t = typename make_unsigned<T>::type;

  //----------------------------------------------------------------------------

  template <typename T>
  using remove_reference = std::remove_reference<T>;

  template <typename T>
  using remove_reference_t = typename remove_reference<T>::type;

  //----------------------------------------------------------------------------

  template <typename T>
  using add_lvalue_reference = std::add_lvalue_reference<T>;

  template <typename T>
  using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;

  //----------------------------------------------------------------------------

  template <typename T>
  using add_rvalue_reference = std::add_rvalue_reference<T>;

  template <typename T>
  using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

  //----------------------------------------------------------------------------

  template <typename T>
  using remove_pointer = std::remove_pointer<T>;

  template <typename T>
  using remove_pointer_t = typename remove_pointer<T>::type;

  //----------------------------------------------------------------------------

  template <typename T>
  using add_pointer = std::add_pointer<T>;

  template <typename T>
  using add_pointer_t = typename add_pointer<T>::type;

  //----------------------------------------------------------------------------

  template <typename T>
  using remove_extent = std::remove_extent<T>;

  template <typename T>
  using remove_extent_t = typename remove_extent<T>::type;

  //----------------------------------------------------------------------------

  template <typename T>
  using remove_all_extents = std::remove_all_extents<T>;

  template <typename T>
  using remove_all_extents_t = typename remove_all_extents<T>::type;

  //----------------------------------------------------------------------------

  template <typename T>
  using remove_cvref = remove_cv<remove_reference_t<T>>;

  template <typename T>
  using remove_cvref_t = typename remove_cvref<T>::type;

  //============================================================================
  // Type Transformation
  //============================================================================

  template <std::size_t Size, std::size_t Align>
  using aligned_storage = std::aligned_storage<Size, Align>;

  template <std::size_t Size, std::size_t Align>
  using aligned_storage_t = typename aligned_storage<Size, Align>::type;

  //----------------------------------------------------------------------------

  template <std::size_t Len, typename...Ts>
  using aligned_union = std::aligned_union<Len, Ts...>;

  template <std::size_t Len, typename...Ts>
  using aligned_union_t = typename aligned_union<Len, Ts...>::type;

  //----------------------------------------------------------------------------

  template <typename T>
  using decay = std::decay<T>;

  template <typename T>
  using decay_t = typename decay<T>::type;

  //----------------------------------------------------------------------------

  template <typename...Ts>
  using common_type = std::common_type<Ts...>;

  template <typename...Ts>
  using common_type_t = typename common_type<Ts...>::type;

  //----------------------------------------------------------------------------

  template <typename T>
  using underlying_type = std::underlying_type<T>;

  template <typename T>
  using underlying_type_t = typename underlying_type<T>::type;

  //----------------------------------------------------------------------------

  template <typename T>
  using result_of = std::result_of<T>;

  template <typename T>
  using result_of_t = typename result_of<T>::type;

  //============================================================================
  // Supported Operations
  //============================================================================

  template <typename T, typename...Args>
  using is_constructible = std::is_constructible<T, Args...>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T, typename...Args>
  BPSTD_CPP17_INLINE constexpr auto is_constructible_v = is_constructible<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T, typename...Args>
  using is_trivially_constructible = std::is_trivially_constructible<T, Args...>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T, typename...Args>
  BPSTD_CPP17_INLINE constexpr auto is_trivially_constructible_v = is_trivially_constructible<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T, typename...Args>
  using is_nothrow_constructible = std::is_nothrow_constructible<T, Args...>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T, typename...Args>
  BPSTD_CPP17_INLINE constexpr auto is_nothrow_constructible_v = is_nothrow_constructible<T, Args...>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_default_constructible = std::is_default_constructible<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_default_constructible_v = is_default_constructible<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_trivially_default_constructible = std::is_trivially_default_constructible<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_trivially_default_constructible_v = is_trivially_default_constructible<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_nothrow_default_constructible = std::is_nothrow_default_constructible<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_nothrow_default_constructible_v = is_nothrow_default_constructible<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_copy_constructible = std::is_copy_constructible<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_copy_constructible_v = is_copy_constructible<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_trivially_copy_constructible = std::is_trivially_copy_constructible<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_trivially_copy_constructible_v = is_trivially_copy_constructible<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_nothrow_copy_constructible = std::is_nothrow_copy_constructible<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_nothrow_copy_constructible_v = is_nothrow_copy_constructible<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_move_constructible = std::is_move_constructible<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_move_constructible_v = is_move_constructible<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_trivially_move_constructible = std::is_trivially_move_constructible<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_trivially_move_constructible_v = is_trivially_move_constructible<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_nothrow_move_constructible = std::is_nothrow_move_constructible<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_nothrow_move_constructible_v = is_nothrow_move_constructible<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T, typename U>
  using is_assignable = std::is_assignable<T, U>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T, typename U>
  BPSTD_CPP17_INLINE constexpr auto is_assignable_v = is_assignable<T, U>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T, typename U>
  using is_trivially_assignable = std::is_trivially_assignable<T, U>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T, typename U>
  BPSTD_CPP17_INLINE constexpr auto is_trivially_assignable_v = is_trivially_assignable<T, U>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T, typename U>
  using is_nothrow_assignable = std::is_nothrow_assignable<T, U>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T, typename U>
  BPSTD_CPP17_INLINE constexpr auto is_nothrow_assignable_v = is_nothrow_assignable<T, U>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_copy_assignable = std::is_copy_assignable<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_copy_assignable_v = is_copy_assignable<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_trivially_copy_assignable = std::is_trivially_copy_assignable<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_trivially_copy_assignable_v = is_trivially_copy_assignable<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_nothrow_copy_assignable = std::is_nothrow_copy_assignable<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_nothrow_copy_assignable_v = is_nothrow_copy_assignable<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_move_assignable = std::is_move_assignable<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_move_assignable_v = is_move_assignable<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_trivially_move_assignable = std::is_trivially_move_assignable<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_trivially_move_assignable_v = is_trivially_move_assignable<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_nothrow_move_assignable = std::is_nothrow_move_assignable<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_nothrow_move_assignable_v = is_nothrow_move_assignable<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_destructible = std::is_destructible<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_destructible_v = is_destructible<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_trivially_destructible = std::is_trivially_destructible<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_trivially_destructible_v = is_trivially_destructible<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using is_nothrow_destructible = std::is_nothrow_destructible<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto is_nothrow_destructible_v = is_nothrow_destructible<T>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename T>
  using has_virtual_destructor = std::has_virtual_destructor<T>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T>
  BPSTD_CPP17_INLINE constexpr auto has_virtual_destructor_v = has_virtual_destructor<T>::value;
#endif

  //============================================================================
  // Relationship
  //============================================================================

  template <typename T, typename U>
  using is_same = std::is_same<T, U>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename T, typename U>
  BPSTD_CPP17_INLINE constexpr auto is_same_v = is_same<T, U>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename Base, typename Derived>
  using is_base_of = std::is_base_of<Base,Derived>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename Base, typename Derived>
  BPSTD_CPP17_INLINE constexpr auto is_base_of_v = is_base_of<Base,Derived>::value;
#endif

  //----------------------------------------------------------------------------

  template <typename From, typename To>
  using is_convertible = std::is_convertible<From, To>;

#if BPSTD_HAS_TEMPLATE_VARIABLES
  template <typename From, typename To>
  BPSTD_CPP17_INLINE constexpr auto is_convertible_v = is_convertible<From, To>::value;
#endif

  //----------------------------------------------------------------------------

  // TODO(bitwizeshift): is_nothrow_convertible
} // namespace bpstd

#endif /* BPSTD_TYPE_TRAITS_HPP */