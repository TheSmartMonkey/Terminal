/*++
Copyright (c) Microsoft Corporation

Module Name:
- _output.h

Abstract:
- These methods provide processing of the text buffer into the final screen rendering state
- For all languages (CJK and Western)
- Most GDI work is processed in these classes

Author(s):
- KazuM Jun.11.1997

Revision History:
- Remove FE/Non-FE separation in preparation for refactoring. (MiNiksa, 2014)
--*/

#pragma once

#include "screenInfo.hpp"
#include "OutputCell.hpp"

void StreamWriteToScreenBuffer(_Inout_updates_(cchBuffer) PWCHAR pwchBuffer,
                               _In_ SHORT cchBuffer,
                               SCREEN_INFORMATION& screenInfo,
                               _Inout_updates_(cchBuffer) DbcsAttribute* const pDbcsAttributes,
                               const bool fWasLineWrapped);

[[nodiscard]]
NTSTATUS WriteRectToScreenBuffer(_In_reads_(coordSrcDimensions.X * coordSrcDimensions.Y * sizeof(CHAR_INFO)) PBYTE const prgbSrc,
                             const COORD coordSrcDimensions,
                             const SMALL_RECT * const psrSrc,
                             SCREEN_INFORMATION& screenInfo,
                             const COORD coordDest,
                             _In_reads_opt_(coordSrcDimensions.X * coordSrcDimensions.Y) TextAttribute* const pTextAttributes);

void WriteRectToScreenBuffer(SCREEN_INFORMATION& screenInfo,
                             const std::vector<std::vector<OutputCell>>& cells,
                             const COORD coordDest);

void WriteRegionToScreen(SCREEN_INFORMATION& screenInfo, _In_ PSMALL_RECT psrRegion);

void WriteToScreen(SCREEN_INFORMATION& screenInfo, const SMALL_RECT srRegion);

[[nodiscard]]
NTSTATUS WriteOutputString(SCREEN_INFORMATION& screenInfo,
                           _In_reads_(*pcRecords) const VOID * pvBuffer,
                           const COORD coordWrite,
                           const ULONG ulStringType,
                           _Inout_ PULONG pcRecords,    // this value is valid even for error cases
                           _Out_opt_ PULONG pcColumns);

[[nodiscard]]
NTSTATUS FillOutput(SCREEN_INFORMATION& screenInfo,
                    _In_ WORD wElement,
                    const COORD coordWrite,
                    const ULONG ulElementType,
                    _Inout_ PULONG pcElements); // this value is valid even for error cases

void FillRectangle(const CHAR_INFO * const pciFill, SCREEN_INFORMATION& screenInfo, const SMALL_RECT * const psrTarget);
