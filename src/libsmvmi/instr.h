/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#ifndef LIBSMVMI_INSTR_H
#define LIBSMVMI_INSTR_H

#include <stddef.h>
#include <stdint.h>
#include "../preprocessor.h"


#ifdef __cplusplus
extern "C" {
#endif

#define SMVMI_MAKE_INSTR(a,b,c,d,e,f,g,h) SM_MAKE_UINT64_BE(a,b,c,d,e,f,g,h)

struct SMVMI_Instruction {
    const char * fullname;
    uint64_t code;
    size_t numargs;
};

const struct SMVMI_Instruction * SMVMI_Instruction_from_code(uint64_t code);
const struct SMVMI_Instruction * SMVMI_Instruction_from_name(const char * name);
const char * SMVMI_Instruction_fullname_to_name(const char * fullname);

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* LIBSMVMI_INSTR_H */
