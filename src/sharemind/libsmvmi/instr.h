/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#ifndef SHAREMIND_LIBSMVMI_INSTR_H
#define SHAREMIND_LIBSMVMI_INSTR_H

#include <sharemind/preprocessor.h>
#include <stddef.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

#define SMVMI_MAKE_INSTR(a,b,c,d,e,f,g,h) SM_MAKE_UINT64_BE(a,b,c,d,e,f,g,h)

typedef struct {
    const char * fullName;
    uint64_t code;
    size_t numArgs;
} SMVMI_Instruction;

const SMVMI_Instruction * SMVMI_Instruction_from_code(uint64_t code) __attribute__ ((warn_unused_result));
const SMVMI_Instruction * SMVMI_Instruction_from_name(const char * name) __attribute__ ((nonnull(1),warn_unused_result));
const char * SMVMI_Instruction_fullname_to_name(const char * fullName) __attribute__ ((nonnull(1),warn_unused_result));

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* SHAREMIND_LIBSMVMI_INSTR_H */
