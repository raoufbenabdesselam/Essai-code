/*
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
 */

#ifndef KOKKOSP_PROFILE_SECTION_HPP
#define KOKKOSP_PROFILE_SECTION_HPP
#ifndef KOKKOS_IMPL_PUBLIC_INCLUDE
#define KOKKOS_IMPL_PUBLIC_INCLUDE
#define KOKKOS_IMPL_PUBLIC_INCLUDE_PROFILING_PROFILESECTION
#endif

#include <Kokkos_Macros.hpp>
#include <impl/Kokkos_Profiling_Interface.hpp>
#include <impl/Kokkos_Profiling.hpp>

#include <string>

namespace Kokkos {
namespace Profiling {

class ProfilingSection {
 public:
  ProfilingSection(ProfilingSection const&) = delete;
  ProfilingSection& operator=(ProfilingSection const&) = delete;

  ProfilingSection(const std::string& sectionName)
#ifdef KOKKOS_ENABLE_DEPRECATED_CODE_3
      : secName(sectionName)
#endif
  {
    if (Kokkos::Profiling::profileLibraryLoaded()) {
      Kokkos::Profiling::createProfileSection(sectionName, &secID);
    }
  }

  void start() {
    if (Kokkos::Profiling::profileLibraryLoaded()) {
      Kokkos::Profiling::startSection(secID);
    }
  }

  void stop() {
    if (Kokkos::Profiling::profileLibraryLoaded()) {
      Kokkos::Profiling::stopSection(secID);
    }
  }

  ~ProfilingSection() {
    if (Kokkos::Profiling::profileLibraryLoaded()) {
      Kokkos::Profiling::destroyProfileSection(secID);
    }
  }

#ifdef KOKKOS_ENABLE_DEPRECATED_CODE_3
  KOKKOS_DEPRECATED std::string getName() { return secName; }

  KOKKOS_DEPRECATED uint32_t getSectionID() { return secID; }
#endif

 protected:
#ifdef KOKKOS_ENABLE_DEPRECATED_CODE_3
  const std::string secName;
#endif
  uint32_t secID;
};

}  // namespace Profiling
}  // namespace Kokkos

#ifdef KOKKOS_IMPL_PUBLIC_INCLUDE_NOTDEFINED_CORE
#undef KOKKOS_IMPL_PUBLIC_INCLUDE
#undef KOKKOS_IMPL_PUBLIC_INCLUDE_NOTDEFINED_PROFILING_PROFILESECTION
#endif
#endif
