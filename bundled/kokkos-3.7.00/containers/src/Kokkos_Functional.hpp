//@HEADER
// ************************************************************************
//
//                        Kokkos v. 3.0
//       Copyright (2020) National Technology & Engineering
//               Solutions of Sandia, LLC (NTESS).
//
// Under the terms of Contract DE-NA0003525 with NTESS,
// the U.S. Government retains certain rights in this software.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY NTESS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL NTESS OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact Christian R. Trott (crtrott@sandia.gov)
//
// ************************************************************************
//@HEADER

#ifndef KOKKOS_FUNCTIONAL_HPP
#define KOKKOS_FUNCTIONAL_HPP
#ifndef KOKKOS_IMPL_PUBLIC_INCLUDE
#define KOKKOS_IMPL_PUBLIC_INCLUDE
#define KOKKOS_IMPL_PUBLIC_INCLUDE_NOTDEFINED_FUNCTIONAL
#endif

#include <Kokkos_Macros.hpp>
#include <impl/Kokkos_Functional_impl.hpp>

namespace Kokkos {

// These should work for most types

template <typename T>
struct pod_hash {
#if defined KOKKOS_ENABLE_DEPRECATED_CODE_3
  using argument_type KOKKOS_DEPRECATED        = T;
  using first_argument_type KOKKOS_DEPRECATED  = T;
  using second_argument_type KOKKOS_DEPRECATED = uint32_t;
  using result_type KOKKOS_DEPRECATED          = uint32_t;
#endif

  KOKKOS_FORCEINLINE_FUNCTION
  uint32_t operator()(T const& t) const {
    return Impl::MurmurHash3_x86_32(&t, sizeof(T), 0);
  }

  KOKKOS_FORCEINLINE_FUNCTION
  uint32_t operator()(T const& t, uint32_t seed) const {
    return Impl::MurmurHash3_x86_32(&t, sizeof(T), seed);
  }
};

template <typename T>
struct pod_equal_to {
#if defined KOKKOS_ENABLE_DEPRECATED_CODE_3
  using first_argument_type KOKKOS_DEPRECATED  = T;
  using second_argument_type KOKKOS_DEPRECATED = T;
  using result_type KOKKOS_DEPRECATED          = bool;
#endif

  KOKKOS_FORCEINLINE_FUNCTION
  bool operator()(T const& a, T const& b) const {
    return Impl::bitwise_equal(&a, &b);
  }
};

template <typename T>
struct pod_not_equal_to {
#if defined KOKKOS_ENABLE_DEPRECATED_CODE_3
  using first_argument_type KOKKOS_DEPRECATED  = T;
  using second_argument_type KOKKOS_DEPRECATED = T;
  using result_type KOKKOS_DEPRECATED          = bool;
#endif

  KOKKOS_FORCEINLINE_FUNCTION
  bool operator()(T const& a, T const& b) const {
    return !Impl::bitwise_equal(&a, &b);
  }
};

template <typename T>
struct equal_to {
#if defined KOKKOS_ENABLE_DEPRECATED_CODE_3
  using first_argument_type KOKKOS_DEPRECATED  = T;
  using second_argument_type KOKKOS_DEPRECATED = T;
  using result_type KOKKOS_DEPRECATED          = bool;
#endif

  KOKKOS_FORCEINLINE_FUNCTION
  bool operator()(T const& a, T const& b) const { return a == b; }
};

template <typename T>
struct not_equal_to {
#if defined KOKKOS_ENABLE_DEPRECATED_CODE_3
  using first_argument_type KOKKOS_DEPRECATED  = T;
  using second_argument_type KOKKOS_DEPRECATED = T;
  using result_type KOKKOS_DEPRECATED          = bool;
#endif

  KOKKOS_FORCEINLINE_FUNCTION
  bool operator()(T const& a, T const& b) const { return a != b; }
};

template <typename T>
struct greater {
#if defined KOKKOS_ENABLE_DEPRECATED_CODE_3
  using first_argument_type KOKKOS_DEPRECATED  = T;
  using second_argument_type KOKKOS_DEPRECATED = T;
  using result_type KOKKOS_DEPRECATED          = bool;
#endif

  KOKKOS_FORCEINLINE_FUNCTION
  bool operator()(T const& a, T const& b) const { return a > b; }
};

template <typename T>
struct less {
#if defined KOKKOS_ENABLE_DEPRECATED_CODE_3
  using first_argument_type KOKKOS_DEPRECATED  = T;
  using second_argument_type KOKKOS_DEPRECATED = T;
  using result_type KOKKOS_DEPRECATED          = bool;
#endif

  KOKKOS_FORCEINLINE_FUNCTION
  bool operator()(T const& a, T const& b) const { return a < b; }
};

template <typename T>
struct greater_equal {
#if defined KOKKOS_ENABLE_DEPRECATED_CODE_3
  using first_argument_type KOKKOS_DEPRECATED  = T;
  using second_argument_type KOKKOS_DEPRECATED = T;
  using result_type KOKKOS_DEPRECATED          = bool;
#endif

  KOKKOS_FORCEINLINE_FUNCTION
  bool operator()(T const& a, T const& b) const { return a >= b; }
};

template <typename T>
struct less_equal {
#if defined KOKKOS_ENABLE_DEPRECATED_CODE_3
  using first_argument_type KOKKOS_DEPRECATED  = T;
  using second_argument_type KOKKOS_DEPRECATED = T;
  using result_type KOKKOS_DEPRECATED          = bool;
#endif

  KOKKOS_FORCEINLINE_FUNCTION
  bool operator()(T const& a, T const& b) const { return a <= b; }
};

}  // namespace Kokkos

#ifdef KOKKOS_IMPL_PUBLIC_INCLUDE_NOTDEFINED_FUNCTIONAL
#undef KOKKOS_IMPL_PUBLIC_INCLUDE
#undef KOKKOS_IMPL_PUBLIC_INCLUDE_NOTDEFINED_FUNCTIONAL
#endif
#endif  // KOKKOS_FUNCTIONAL_HPP
