/** @file
  A non-functional instance of the Timer Library.

  Copyright (c) 2007 - 2010, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <PiPei.h>
#include <Library/TimerLib.h>
#include <Library/DebugLib.h>
#include <Library/EmuThunkLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>

#include <Protocol/Timer.h>



/**
  Stalls the CPU for at least the given number of microseconds.

  Stalls the CPU for the number of microseconds specified by MicroSeconds.

  @param  MicroSeconds  The minimum number of microseconds to delay.

  @return The value of MicroSeconds inputted.

**/
UINTN
EFIAPI
MicroSecondDelay (
  IN      UINTN                     MicroSeconds
  )
{
  return NanoSecondDelay (MicroSeconds * 1000);
}


/**
  Stalls the CPU for at least the given number of nanoseconds.

  Stalls the CPU for the number of nanoseconds specified by NanoSeconds.

  @param  NanoSeconds The minimum number of nanoseconds to delay.

  @return The value of NanoSeconds inputted.

**/
UINTN
EFIAPI
NanoSecondDelay (
  IN      UINTN                     NanoSeconds
  )
{
  gEmuThunk->Sleep (NanoSeconds);
  return NanoSeconds;
}


/**
  Retrieves the current value of a 64-bit free running performance counter.

  The counter can either count up by 1 or count down by 1. If the physical
  performance counter counts by a larger increment, then the counter values
  must be translated. The properties of the counter can be retrieved from
  GetPerformanceCounterProperties().

  @return The current value of the free running performance counter.

**/
UINT64
EFIAPI
GetPerformanceCounter (
  VOID
  )
{
  return gEmuThunk->QueryPerformanceCounter ();
}

/**
  Retrieves the 64-bit frequency in Hz and the range of performance counter
  values.

  If StartValue is not NULL, then the value that the performance counter starts
  with immediately after is it rolls over is returned in StartValue. If
  EndValue is not NULL, then the value that the performance counter end with
  immediately before it rolls over is returned in EndValue. The 64-bit
  frequency of the performance counter in Hz is always returned. If StartValue
  is less than EndValue, then the performance counter counts up. If StartValue
  is greater than EndValue, then the performance counter counts down. For
  example, a 64-bit free running counter that counts up would have a StartValue
  of 0 and an EndValue of 0xFFFFFFFFFFFFFFFF. A 24-bit free running counter
  that counts down would have a StartValue of 0xFFFFFF and an EndValue of 0.

  @param  StartValue  The value the performance counter starts with when it
                      rolls over.
  @param  EndValue    The value that the performance counter ends with before
                      it rolls over.

  @return The frequency in Hz.

**/
UINT64
EFIAPI
GetPerformanceCounterProperties (
  OUT      UINT64                    *StartValue,  OPTIONAL
  OUT      UINT64                    *EndValue     OPTIONAL
  )
{

  if (StartValue != NULL) {
    *StartValue = 0ULL;
  }
  if (EndValue != NULL) {
    *EndValue = (UINT64)-1LL;
  }

  return gEmuThunk->QueryPerformanceFrequency ();
}


