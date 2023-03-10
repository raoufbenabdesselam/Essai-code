// ---------------------------------------------------------------------
//
// Copyright (C) 2017 - 2018 by the deal.II authors
//
// This file is part of the deal.II library.
//
// The deal.II library is free software; you can use it, redistribute
// it, and/or modify it under the terms of the GNU Lesser General
// Public License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// The full text of the license can be found in the file LICENSE.md at
// the top level directory of deal.II.
//
// ---------------------------------------------------------------------

// Verify that we can correctly copy a PETSc vector to a parallel (non-PETSc)
// SUNDIALS vector.

#include <deal.II/base/mpi.h>

#include <deal.II/lac/petsc_vector.h>

#include <deal.II/sundials/copy.h>

#include <iostream>
#include <vector>

#include "../tests.h"

int
main(int argc, char **argv)
{
  Utilities::MPI::MPI_InitFinalize mpi_initialization(argc, argv, 1);
  MPILogInitAll                    log_all;

  MPI_Comm communicator = MPI_COMM_WORLD;

  const unsigned int current_process =
    Utilities::MPI::this_mpi_process(communicator);
  const unsigned int n_processes =
    Utilities::MPI::n_mpi_processes(communicator);

  // give the zeroth process 1 dof, the first 2, etc
  const types::global_dof_index n_local_dofs = 1 + current_process;
  const types::global_dof_index begin_dof =
    (current_process * (current_process + 1)) / 2;
  const types::global_dof_index end_dof = begin_dof + n_local_dofs;

  const types::global_dof_index n_global_dofs =
    ((n_processes - 1) * (n_processes)) / 2 + n_processes;
  IndexSet local_dofs(n_global_dofs);
  local_dofs.add_range(begin_dof, end_dof);
  local_dofs.compress();
  AssertDimension(local_dofs.n_elements(), n_local_dofs);


  PETScWrappers::MPI::Vector vec(local_dofs, communicator);
  for (const types::global_dof_index local_dof : local_dofs)
    {
      vec[local_dof] = 2 * local_dof - current_process;
    }
  vec.compress(VectorOperation::insert);
  const std::size_t n_dofs = vec.size();

#if DEAL_II_SUNDIALS_VERSION_GTE(6, 0, 0)
  SUNContext context;
  int        status = SUNContext_Create(&communicator, &context);
  AssertThrow(status == 0, ExcInternalError());
#endif

  N_Vector sundials_vector = N_VNew_Parallel(communicator,
                                             n_local_dofs,
                                             n_dofs
#if DEAL_II_SUNDIALS_VERSION_GTE(6, 0, 0)
                                             ,
                                             context
#endif
  );
  SUNDIALS::internal::copy(sundials_vector, vec);

  PETScWrappers::MPI::Vector vec2(local_dofs, communicator);
  SUNDIALS::internal::copy(vec2, sundials_vector);

  AssertThrow(vec2 == vec,
              ExcMessage(
                "The two PETSc vectors should be equal since they are "
                "copies (by means of an intermediate SUNDIALs vector)"));

  deallog << "n_local_dofs: " << n_local_dofs << std::endl;
  deallog << "OK" << std::endl;

  N_VDestroy_Parallel(sundials_vector);
#if DEAL_II_SUNDIALS_VERSION_GTE(6, 0, 0)
  status = SUNContext_Free(&context);
  AssertThrow(status == 0, ExcInternalError());
#endif
}
