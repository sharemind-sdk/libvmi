/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#ifndef SHAREMIND_LIBVMI_INSTR_H
#define SHAREMIND_LIBVMI_INSTR_H

#include <sharemind/preprocessor.h>
#include <stddef.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

#define SHAREMIND_VMI_MAKE_INSTR(a,b,c,d,e,f,g,h) SHAREMIND_MAKE_UINT64_BE(a,b,c,d,e,f,g,h)

typedef struct {
    const char * fullName;
    uint64_t code;
    size_t numArgs;
} SharemindVmInstruction;

const SharemindVmInstruction * sharemind_vm_instruction_from_code(uint64_t code) __attribute__ ((warn_unused_result));
const SharemindVmInstruction * sharemind_vm_instruction_from_name(const char * name) __attribute__ ((nonnull(1),warn_unused_result));
const char * sharemind_vm_instruction_fullname_to_name(const char * fullName) __attribute__ ((nonnull(1),warn_unused_result));

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* SHAREMIND_LIBVMI_INSTR_H */
