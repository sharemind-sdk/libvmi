/*
 * Copyright (C) 2015 Cybernetica
 *
 * Research/Commercial License Usage
 * Licensees holding a valid Research License or Commercial License
 * for the Software may use this file according to the written
 * agreement between you and Cybernetica.
 *
 * GNU General Public License Usage
 * Alternatively, this file may be used under the terms of the GNU
 * General Public License version 3.0 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU General Public License version 3.0 requirements will be
 * met: http://www.gnu.org/copyleft/gpl-3.0.html.
 *
 * For further information, please contact us at sharemind@cyber.ee.
 */

#include "instr.h"

#include <algorithm>
#include <cassert>
#include <sharemind/DebugOnly.h>
#include <type_traits>


namespace sharemind {

namespace {

VmInstructionInfo const instructions[] = {
    #define SHAREMIND_HANDLE_VMI_INSTRUCTION(iFull, iCode, iNumArgs) \
        {iFull, sizeof(iFull) - 1u, iCode, iNumArgs},
    #include <sharemind/m4/instruction_index.h>
    #undef SHAREMIND_HANDLE_VMI_INSTRUCTION
};

SimpleUnorderedStringMap<VmInstructionInfo const &> createFullnameMap() {
    SimpleUnorderedStringMap<VmInstructionInfo const &> r(sizeof(instructions));
    for (auto const & info : instructions) {
        assert(info.fullName);
        assert(info.fullNameSize > 0u);
        assert(*info.fullName);
        r.emplace(info.fullName, info);
    }
    return r;
}

SimpleUnorderedStringMap<VmInstructionInfo const &> createNameMap() {
    /* Count number of keys. Note that overflow does not matter while counting,
       because it is used for reserving the number of buckets only. On overflow
       we allocate less buckets and will probably just run out of memory when
       inserting elements. */
    std::size_t size = 0u;
    for (auto const & info : instructions) {
        assert(info.fullName);
        assert(info.fullNameSize > 0u);
        assert(*info.fullName);
        auto const numNamespaces =
                std::count(info.fullName,
                           info.fullName + info.fullNameSize,
                           '.');
        assert(numNamespaces >= 0u);
        using U = std::make_unsigned<decltype(numNamespaces)>::type;
        size += static_cast<U>(numNamespaces);
        ++size; // We count all components, not just namespaces
    }
    SimpleUnorderedStringMap<VmInstructionInfo const &> r(size);
    for (auto const & info : instructions) {
        r.emplace(info.fullName, info);
        auto const end = info.fullName + info.fullNameSize;
        for (auto const * key = info.fullName + 1u; key != end; ++key) {
            assert(*key);
            if (*key == '.') {
                ++key;
                assert(*key);
                r.emplace(key, info);
            }
        }
    }
    assert(r.size() == size);
    return r;
}

UnorderedMap<std::uint64_t, VmInstructionInfo const &> createCodeMap() {
    UnorderedMap<std::uint64_t, VmInstructionInfo const &> r;
    for (auto const & info : instructions)
        r.emplace(info.code, info);
    return r;
}

} // anonymous namespace

SimpleUnorderedStringMap<VmInstructionInfo const &> const &
instructionFullnameMap()
{
    static auto const r(createFullnameMap());
    return r;
}

SimpleUnorderedStringMap<VmInstructionInfo const &> const &
instructionNameMap()
{
    static auto const r(createNameMap());
    return r;
}

UnorderedMap<std::uint64_t, VmInstructionInfo const &> const &
instructionCodeMap()
{
    static auto const r(createCodeMap());
    return r;
}

} // namespace sharemind {
