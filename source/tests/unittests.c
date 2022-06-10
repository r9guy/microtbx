/************************************************************************************//**
* \file         unittests.c
* \brief        Unit tests source file.
* \internal
*----------------------------------------------------------------------------------------
*                          C O P Y R I G H T
*----------------------------------------------------------------------------------------
*   Copyright (c) 2022 by Feaser     www.feaser.com     All rights reserved
*
*----------------------------------------------------------------------------------------
*                            L I C E N S E
*----------------------------------------------------------------------------------------
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* \endinternal
****************************************************************************************/

/****************************************************************************************
* Include files
****************************************************************************************/
#include "microtbx.h"                            /* MicroTBX global header             */
#include "unity.h"                               /* Unity unit test framework          */
#include "unittests.h"                           /* Unit tests header                  */
#include <sys/time.h>                            /* Time definitions                   */


/****************************************************************************************
* Local data declarations
****************************************************************************************/
/** \brief Keeps track of how often an assertion got triggered. */
uint32_t assertionCnt = 0;


/************************************************************************************//**
** \brief     Handles the run-time assertions. 
** \param     file The filename of the source file where the assertion occurred in.
** \param     line The line number inside the file where the assertion occurred.
**
****************************************************************************************/
void handleTbxAssertion(const char * const file, uint32_t line)
{
  /* Increment the assertion counter. */
  assertionCnt++;
} /*** end of handleTbxAssertion ***/


/************************************************************************************//**
** \brief     Handler function that gets called by the random number generator. This
**            module requires a seed, which this function should obtain. 
** \details   This example implementation set the seed based on the value of system time.
** \return    The 32-bit value that the random number generator module uses as a seed to
**            initialize itself.
**
****************************************************************************************/
uint32_t seedInitHandler(void)
{
  uint32_t result = 0;
  struct timeval tv;

  if (gettimeofday(&tv, NULL) == 0)
  {
    result = (((uint32_t)tv.tv_sec * 1000U) + ((uint32_t)tv.tv_usec / 1000U));
  }
  /* Give the result back to the caller. */
  return result;
} /*** end of seedInitHandler ***/


/************************************************************************************//**
** \brief     Tests that verifies that the version macros are present.
**
****************************************************************************************/
void test_TbxGeneric_VersionMacrosShouldBePresent(void)
{
  /* Check presence of the main version macro. */
  #ifndef TBX_VERSION_MAIN
  TEST_FAIL();
  #endif
  /* Check presence of the minor version macro. */
  #ifndef TBX_VERSION_MINOR
  TEST_FAIL();
  #endif
  /* Check presence of the patch version macro. */
  #ifndef TBX_VERSION_PATCH
  TEST_FAIL();
  #endif
} /*** end of test_TbxGeneric_VersionMacrosShouldBePresent ***/


/************************************************************************************//**
** \brief     Tests that verifies the presence and correct values of the boolean type
**            macros.
**
****************************************************************************************/
void test_TbxGeneric_BooleanMacrosShouldBePresent(void)
{
  /* Check TBX_TRUE macro. */
  #ifndef TBX_TRUE
  TEST_FAIL();
  #else
  TEST_ASSERT_EQUAL(1, TBX_TRUE);
  #endif
  /* Check TBX_FALSE macro. */
  #ifndef TBX_FALSE
  TEST_FAIL();
  #else
  TEST_ASSERT_EQUAL(0, TBX_FALSE);
  #endif
  /* Check TBX_OK macro. */
  #ifndef TBX_OK
  TEST_FAIL();
  #else
  TEST_ASSERT_EQUAL(1, TBX_OK);
  #endif
  /* Check TBX_ERROR macro. */
  #ifndef TBX_ERROR
  TEST_FAIL();
  #else
  TEST_ASSERT_EQUAL(0, TBX_ERROR);
  #endif
} /*** end of test_TbxGeneric_BooleanMacrosShouldBePresent ***/


/************************************************************************************//**
** \brief     Tests that verifies that the unused argument macro is present.
**
****************************************************************************************/
void test_TbxGeneric_UnusedArgMacroShouldBePresent(void)
{
  /* Check presence of the unused argument macro. */
  #ifndef TBX_UNUSED_ARG
  TEST_FAIL();
  #endif
} /*** end of test_TbxGeneric_UnusedArgMacroShouldBePresent ***/


/************************************************************************************//**
** \brief     Tests that an assertion triggers if you specify NULL when configuring a
**            custom assertion handler.
**
****************************************************************************************/
void test_TbxAssertSetHandler_ShouldTriggerAssertionIfParamNull(void)
{
  /* Attempt to configure an invalid custom assertion handler. */
  TbxAssertSetHandler(NULL);
  /* Make sure an assertion was triggered. Note that this also verifies that the 
   * initially configured assertion handler still works.
   */
  TEST_ASSERT_GREATER_THAN_UINT32(0, assertionCnt);
} /*** end of test_TbxAssertSetHandler_ShouldTriggerAssertionIfParamNull ***/


/************************************************************************************//**
** \brief     Tests that the triggering of assertions work.
**
****************************************************************************************/
void test_TbxAssertTrigger_ShouldTriggerAssertion(void)
{
  /* Perform an assertion that shouldn't trigger. */
  TBX_ASSERT(TBX_TRUE);
  /* Make sure no assertion was triggered. */
  TEST_ASSERT_EQUAL_UINT32(0, assertionCnt);
  /* Perform an assertion that shouldn trigger. */
  TBX_ASSERT(TBX_FALSE);
  /* Make sure an assertion was triggered. */
  TEST_ASSERT_GREATER_THAN_UINT32(0, assertionCnt);
} /*** end of test_TbxAssertTrigger_ShouldTriggerAssertion ***/


/************************************************************************************//**
** \brief     Tests that an assertion triggerss if you attempt to exit a critical section
**            before first entering one.
**
****************************************************************************************/
void test_TbxCriticalSectionExit_ShouldTriggerAssertionIfNotInCritSect(void)
{
  /* Exit a critical section, which hasn't actually been entered yet. */
  TbxCriticalSectionExit();
  /* Make sure an assertion was triggered. */
  TEST_ASSERT_GREATER_THAN_UINT32(0, assertionCnt);
} /*** end of test_TbxCriticalSectionExit_ShouldTriggerAssertionIfNotInCritSect ***/


/************************************************************************************//**
** \brief     Tests that an assertion triggerss if you attempt to exit a critical section
**            before first entering one.
**
****************************************************************************************/
void test_TbxCriticalSectionEnter_ShouldNotAssertUponCritSectExit(void)
{
  /* Enter and exit a critical section. */
  TbxCriticalSectionEnter();
  TbxCriticalSectionExit();
  /* Make sure no assertion was triggered. */
  TEST_ASSERT_EQUAL_UINT32(0, assertionCnt);
} /*** end of test_TbxCriticalSectionEnter_ShouldNotAssertUponCritSectExit ***/


/************************************************************************************//**
** \brief     Tests that free heap size reporting works.
** \attention Should run before any other tests that might allocated from the heap.
**
****************************************************************************************/
void test_TbxHeapGetFree_ShouldReturnActualFreeSize(void)
{
  size_t initialFreeHeap;
  size_t currentFreeHeap;
  void * mem;
  const size_t allocSize = 2;

  /* Get the initial free heap size. */
  initialFreeHeap = TbxHeapGetFree();
  /* Heap should not be zero. */
  TEST_ASSERT_GREATER_THAN(0, initialFreeHeap);
  /* First time that anything gets allocated means that the full heap should be free. */
  TEST_ASSERT_EQUAL(TBX_CONF_HEAP_SIZE, initialFreeHeap);
  /* Allocate some memory from the heap. */
  mem = TbxHeapAllocate(allocSize);
  /* Get the current free heap size. */
  currentFreeHeap = TbxHeapGetFree();
  /* Free size after allocation should be less then before. */
  TEST_ASSERT_LESS_THAN(initialFreeHeap, currentFreeHeap);
  /* Make sure no assertion was triggered. */
  TEST_ASSERT_EQUAL_UINT32(0, assertionCnt);
} /*** end of test_TbxHeapGetFree_ShouldReturnActualFreeSize ***/


/************************************************************************************//**
** \brief     Tests that basic memory allocation from the heap works.
**
****************************************************************************************/
void test_TbxHeapAllocate_ShouldReturnNotNull(void)
{
  void * mem;
  const size_t allocSize = 2;

  /* Allocate some memory from the heap. */
  mem = TbxHeapAllocate(allocSize);
  /* Make sure the allocation worked. */
  TEST_ASSERT_NOT_NULL(mem);  
  /* Make sure no assertion was triggered. */
  TEST_ASSERT_EQUAL_UINT32(0, assertionCnt);
} /*** end of test_TbxHeapAllocate_ShouldReturnNotNull ***/


/************************************************************************************//**
** \brief     Tests that a zero size memory allocation does not work.
**
****************************************************************************************/
void test_TbxHeapAllocate_ShouldReturnNullIfZeroSizeAllocated(void)
{
  size_t initialFreeHeap;
  size_t currentFreeHeap;
  void * mem;
  const size_t allocSize = 0;

  /* Get the initial free heap size. */
  initialFreeHeap = TbxHeapGetFree();
  /* Allocate zero memory from the heap. */
  mem = TbxHeapAllocate(allocSize);
  /* Make sure the allocation failed. */
  TEST_ASSERT_NULL(mem);  
  /* Get current free heap size. */
  currentFreeHeap = TbxHeapGetFree();
  /* Should still be the same as before, because nothing should have been allocated. */
  TEST_ASSERT_EQUAL(initialFreeHeap, currentFreeHeap);
  /* Make sure an assertion was triggered. */
  TEST_ASSERT_GREATER_THAN_UINT32(0, assertionCnt);
} /*** end of test_TbxHeapAllocate_ShouldReturnNullIfZeroSizeAllocated ***/


/************************************************************************************//**
** \brief     Tests that too much memory allocation does not work.
**
****************************************************************************************/
void test_TbxHeapAllocate_ShouldReturnNullIfTooMuchAllocated(void)
{
  size_t initialFreeHeap;
  size_t currentFreeHeap;
  size_t allocSize;
  void * mem;

  /* Get the initial free heap size. */
  initialFreeHeap = TbxHeapGetFree();
  /* Allocate more memory from the heap than what is currently available. */
  allocSize = initialFreeHeap + 1;
  mem = TbxHeapAllocate(allocSize);
  /* Make sure the allocation failed. */
  TEST_ASSERT_NULL(mem);  
  /* Get current free heap size. */
  currentFreeHeap = TbxHeapGetFree();
  /* Should still be the same as before, because nothing should have been allocated. */
  TEST_ASSERT_EQUAL(initialFreeHeap, currentFreeHeap);
  /* Make sure no assertion was triggered. */
  TEST_ASSERT_EQUAL_UINT32(0, assertionCnt);
} /*** end of test_TbxHeapAllocate_ShouldReturnNullIfTooMuchAllocated ***/


/************************************************************************************//**
** \brief     Tests that the allocated size automatically aligns to the pointer size
**            of the architecture. So for 32-bit memory addresses, the allocated size
**            should always be aligned to 4 bytes.
**
****************************************************************************************/
void test_TbxHeapAllocate_ShouldAlignToAddressSize(void)
{
  size_t initialFreeHeap;
  size_t currentFreeHeap;
  size_t delta;
  size_t addressSize;
  const size_t allocSize = 1;
  void * mem;

  /* Get the initial free heap size. */
  initialFreeHeap = TbxHeapGetFree();
  /* Allocate a single byte. */
  mem = TbxHeapAllocate(allocSize);
  /* Make sure the allocation worked. */
  TEST_ASSERT_NOT_NULL(mem);  
  /* Get current free heap size. */
  currentFreeHeap = TbxHeapGetFree();
  /* Calculate the delta. */
  delta = initialFreeHeap - currentFreeHeap;
  /* Determine architectures address size by looking at the width of a pointer. */
  addressSize = sizeof(void *);
  /* Make sure the allocated size was aligned to the address size automatically. */
  /* Should still be the same as before, because nothing should have been allocated. */
  TEST_ASSERT_EQUAL(addressSize, delta);
  /* Make sure no assertion was triggered. */
  TEST_ASSERT_EQUAL_UINT32(0, assertionCnt);
} /*** end of test_TbxHeapAllocate_ShouldAlignToAddressSize ***/


/************************************************************************************//**
** \brief     Tests that an assertion is triggered if you try to set an invalid seed
**            initialization handler.
**
****************************************************************************************/
void test_TbxRandomSetSeedInitHandler_ShouldTriggerAssertionIfParamNull(void)
{
  /* Attempt to configure an invalid custom seed initialization handler. */
  TbxRandomSetSeedInitHandler(NULL);
  /* Make sure an assertion was triggered. */
  TEST_ASSERT_GREATER_THAN_UINT32(0, assertionCnt);
} /*** end of test_TbxRandomSetSeedInitHandler_ShouldTriggerAssertionIfParamNull ***/


/************************************************************************************//**
** \brief     Tests that the setting of a seed initialization handler works.
**
****************************************************************************************/
void test_TbxRandomSetSeedInitHandler_ShouldWork(void)
{
  /* Attempt to configure an valid custom seed initialization handler. */
  TbxRandomSetSeedInitHandler(seedInitHandler);
  /* Make sure no assertion was triggered. */
  TEST_ASSERT_EQUAL_UINT32(0, assertionCnt);
} /*** end of test_TbxRandomSetSeedInitHandler_ShouldWork ***/


/************************************************************************************//**
** \brief     Tests that the randon numbers are actually created.
**
****************************************************************************************/
void test_TbxRandomNumberGet_ShouldReturnRandomNumbers(void)
{
  uint32_t randomNumber1;
  uint32_t randomNumber2;

  /* Attempt to obtain two random numbers. */
  randomNumber1 = TbxRandomNumberGet();
  randomNumber2 = TbxRandomNumberGet();
  /* Make sure the numbers are not equal. */
  TEST_ASSERT_NOT_EQUAL_UINT32(randomNumber1, randomNumber2);
  /* Make sure no assertion was triggered. */
  TEST_ASSERT_EQUAL_UINT32(0, assertionCnt);
} /*** end of test_TbxRandomNumberGet_ShouldReturnRandomNumbers ***/


/************************************************************************************//**
** \brief     Tests that invalid parameters trigger and assertion and returns zero.
**
****************************************************************************************/
void test_TbxChecksumCrc16Calculate_ShouldAssertOnInvalidParams(void)
{
  uint16_t checksum; 
  const uint8_t sourceData[] = 
  {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,    
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 
    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F    
  };
  const size_t sourceLen = sizeof(sourceData)/sizeof(sourceData[0]);

  /* Pass a NULL pointer for the data byte array. */
  checksum = TbxChecksumCrc16Calculate(NULL, sourceLen);
  /* Make sure an assertion was triggered. */
  TEST_ASSERT_GREATER_THAN_UINT32(0, assertionCnt);
  /* Verify that it did not continue with the actual checksum calculation. */
  TEST_ASSERT_EQUAL_UINT16(0, checksum);
  /* Reset the assertion counter. */
  assertionCnt = 0;
  /* Pass an invalid size. */
  checksum = TbxChecksumCrc16Calculate(sourceData, 0);
  /* Make sure an assertion was triggered. */
  TEST_ASSERT_GREATER_THAN_UINT32(0, assertionCnt);
  /* Verify that it did not continue with the actual checksum calculation. */
  TEST_ASSERT_EQUAL_UINT16(0, checksum);
} /*** end of test_TbxChecksumCrc16Calculate_ShouldAssertOnInvalidParams ***/


/************************************************************************************//**
** \brief     Tests that the calculated checksum is correct.
**
****************************************************************************************/
void test_TbxChecksumCrc16Calculate_ShouldReturnValidCrc16(void)
{
  uint16_t checksum; 
  const uint8_t sourceData[] = 
  {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,    
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 
    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F    
  };
  const size_t sourceLen = sizeof(sourceData)/sizeof(sourceData[0]);
  /* Obtained using an online CRC calculator using the CRC16_CCITT_FALSE algorithm:
   * http://www.sunshine2k.de/coding/javascript/crc/crc_js.html
   */
  const uint16_t correctChecksum = 0x23B3;

  /* Calculate the checksum. */
  checksum = TbxChecksumCrc16Calculate(sourceData, sourceLen);
  /* Verify the correctness of the checksum calculation. */
  TEST_ASSERT_EQUAL_UINT16(correctChecksum, checksum);
  /* Make sure no assertion was triggered. */
  TEST_ASSERT_EQUAL_UINT32(0, assertionCnt);
} /*** end of test_TbxChecksumCrc16Calculate_ShouldReturnValidCrc16 ***/


/************************************************************************************//**
** \brief     Tests that invalid parameters trigger and assertion and returns zero.
**
****************************************************************************************/
void test_TbxChecksumCrc32Calculate_ShouldAssertOnInvalidParams(void)
{
  uint32_t checksum; 
  const uint8_t sourceData[] = 
  {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,    
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 
    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F    
  };
  const size_t sourceLen = sizeof(sourceData)/sizeof(sourceData[0]);

  /* Pass a NULL pointer for the data byte array. */
  checksum = TbxChecksumCrc32Calculate(NULL, sourceLen);
  /* Make sure an assertion was triggered. */
  TEST_ASSERT_GREATER_THAN_UINT32(0, assertionCnt);
  /* Verify that it did not continue with the actual checksum calculation. */
  TEST_ASSERT_EQUAL_UINT32(0, checksum);
  /* Reset the assertion counter. */
  assertionCnt = 0;
  /* Pass an invalid size. */
  checksum = TbxChecksumCrc32Calculate(sourceData, 0);
  /* Make sure an assertion was triggered. */
  TEST_ASSERT_GREATER_THAN_UINT32(0, assertionCnt);
  /* Verify that it did not continue with the actual checksum calculation. */
  TEST_ASSERT_EQUAL_UINT32(0, checksum);
} /*** end of test_TbxChecksumCrc32Calculate_ShouldAssertOnInvalidParams ***/


/************************************************************************************//**
** \brief     Tests that the calculated checksum is correct.
**
****************************************************************************************/
void test_TbxChecksumCrc32Calculate_ShouldReturnValidCrc32(void)
{
  uint32_t checksum; 
  const uint8_t sourceData[] = 
  {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,    
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 
    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F    
  };
  const size_t sourceLen = sizeof(sourceData)/sizeof(sourceData[0]);
  /* Obtained using an online CRC calculator using the CRC16_BUYPASS algorithm:
   * http://www.sunshine2k.de/coding/javascript/crc/crc_js.html
   */
  const uint32_t correctChecksum = 0x8F819950UL;

  /* Calculate the checksum. */
  checksum = TbxChecksumCrc32Calculate(sourceData, sourceLen);
  /* Verify the correctness of the checksum calculation. */
  TEST_ASSERT_EQUAL_UINT32(correctChecksum, checksum);
  /* Make sure no assertion was triggered. */
  TEST_ASSERT_EQUAL_UINT32(0, assertionCnt);
} /*** end of test_TbxChecksumCrc32Calculate_ShouldReturnValidCrc32 ***/


/************************************************************************************//**
** \brief     Tests that invalid parameters trigger an assertion and do not perform the
**            actual encryption.
**
****************************************************************************************/
void test_TbxCryptoAes256Encrypt_ShouldAssertOnInvalidParams(void)
{
  const uint8_t cryptoKey[] =
  {
    0x32, 0x72, 0x35, 0x75, 0x38, 0x78, 0x21, 0x41,
    0x25, 0x44, 0x2A, 0x47, 0x2D, 0x4B, 0x61, 0x50,
    0x64, 0x53, 0x67, 0x56, 0x6B, 0x59, 0x70, 0x33,
    0x73, 0x36, 0x76, 0x39, 0x79, 0x24, 0x42, 0x3F
  };
  uint8_t sourceData[] = 
  {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F
  };
  uint8_t tmpBuffer[sizeof(sourceData)/sizeof(sourceData[0])];
  const size_t sourceLen = sizeof(sourceData)/sizeof(sourceData[0]);
  uint8_t idx;
  uint8_t dataChanged;

  /* Pass a NULL pointer for the data byte array. */
  TbxCryptoAes256Encrypt(NULL, sourceLen, cryptoKey);
  /* Make sure an assertion was triggered. */
  TEST_ASSERT_GREATER_THAN_UINT32(0, assertionCnt);

  /* Reset the assertion counter. */
  assertionCnt = 0;
  /* Copy the source data to the temp buffer. */
  for (idx = 0; idx < sourceLen; idx++)
  {
    tmpBuffer[idx] = sourceData[idx];
  }
  /* Pass a size of zero. */
  TbxCryptoAes256Encrypt(tmpBuffer, 0, cryptoKey);
  /* Make sure an assertion was triggered. */
  TEST_ASSERT_GREATER_THAN_UINT32(0, assertionCnt);
  /* Verify that no encryption was attempted. */
  dataChanged = TBX_FALSE;
  for (idx = 0; idx < sourceLen; idx++)
  {
    if (tmpBuffer[idx] != sourceData[idx])
    {
      dataChanged = TBX_TRUE;
      break;
    }
  }
  TEST_ASSERT_EQUAL(TBX_FALSE, dataChanged);

  /* Reset the assertion counter. */
  assertionCnt = 0;
  /* Copy the source data to the temp buffer. */
  for (idx = 0; idx < sourceLen; idx++)
  {
    tmpBuffer[idx] = sourceData[idx];
  }
  /* Pass a size that is not aligned to the AES256 block size. */
  TbxCryptoAes256Encrypt(tmpBuffer, 15, cryptoKey);
  /* Make sure an assertion was triggered. */
  TEST_ASSERT_GREATER_THAN_UINT32(0, assertionCnt);
  /* Verify that no encryption was attempted. */
  dataChanged = TBX_FALSE;
  for (idx = 0; idx < sourceLen; idx++)
  {
    if (tmpBuffer[idx] != sourceData[idx])
    {
      dataChanged = TBX_TRUE;
      break;
    }
  }
  TEST_ASSERT_EQUAL(TBX_FALSE, dataChanged);

  /* Reset the assertion counter. */
  assertionCnt = 0;
  /* Copy the source data to the temp buffer. */
  for (idx = 0; idx < sourceLen; idx++)
  {
    tmpBuffer[idx] = sourceData[idx];
  }
  /* Pass a NULL pointer for the key. */
  TbxCryptoAes256Encrypt(tmpBuffer, sourceLen, NULL);
  /* Make sure an assertion was triggered. */
  TEST_ASSERT_GREATER_THAN_UINT32(0, assertionCnt);
  /* Verify that no encryption was attempted. */
  dataChanged = TBX_FALSE;
  for (idx = 0; idx < sourceLen; idx++)
  {
    if (tmpBuffer[idx] != sourceData[idx])
    {
      dataChanged = TBX_TRUE;
      break;
    }
  }
  TEST_ASSERT_EQUAL(TBX_FALSE, dataChanged);
} /*** end of test_TbxCryptoAes256Encrypt_ShouldAssertOnInvalidParams ***/


/************************************************************************************//**
** \brief     Tests that data is properly encrypted.
**
****************************************************************************************/
void test_TbxCryptoAes256Encrypt_ShouldEncrypt(void)
{
  const uint8_t cryptoKey[] =
  {
    0x32, 0x72, 0x35, 0x75, 0x38, 0x78, 0x21, 0x41,
    0x25, 0x44, 0x2A, 0x47, 0x2D, 0x4B, 0x61, 0x50,
    0x64, 0x53, 0x67, 0x56, 0x6B, 0x59, 0x70, 0x33,
    0x73, 0x36, 0x76, 0x39, 0x79, 0x24, 0x42, 0x3F
  };
  uint8_t sourceData[] = 
  {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F
  };
  /* Obtained using an online AES calculator using a 256 bit key and ECB:
   * http://aes.online-domain-tools.com/
   */
  const uint8_t expectedData[] = 
  {
    0xC1, 0x2A, 0x81, 0xC0, 0x6C, 0xC3, 0xDB, 0x9F,
    0x70, 0x54, 0x74, 0xB4, 0xB9, 0x3E, 0xA3, 0x1B,
    0xF7, 0xA2, 0xEC, 0xAF, 0x39, 0x0F, 0x9D, 0x43,
    0x00, 0x0F, 0x82, 0xF8, 0xBC, 0xFE, 0x23, 0x1A
  };
  uint8_t tmpBuffer[sizeof(sourceData)/sizeof(sourceData[0])];
  const size_t sourceLen = sizeof(sourceData)/sizeof(sourceData[0]);
  uint8_t idx;
  uint8_t dataOkay = TBX_TRUE;

  /* Copy the source data to the temp buffer. */
  for (idx = 0; idx < sourceLen; idx++)
  {
    tmpBuffer[idx] = sourceData[idx];
  }
  /* Perform the encryption. */
  TbxCryptoAes256Encrypt(tmpBuffer, sourceLen, cryptoKey);
  /* Make sure no assertion was triggered. */
  TEST_ASSERT_EQUAL_UINT32(0, assertionCnt);
  /* Verify that the encrypted data is as expected. */
  for (idx = 0; idx < sourceLen; idx++)
  {
    if (tmpBuffer[idx] != expectedData[idx])
    {
      dataOkay = TBX_FALSE;
    }
  }
  TEST_ASSERT_EQUAL(TBX_TRUE, dataOkay);
} /*** end of test_TbxCryptoAes256Encrypt_ShouldEncrypt ***/


/************************************************************************************//**
** \brief     Tests that invalid parameters trigger an assertion and do not perform the
**            actual decryption.
**
****************************************************************************************/
void test_TbxCryptoAes256Decrypt_ShouldAssertOnInvalidParams(void)
{
  const uint8_t cryptoKey[] =
  {
    0x32, 0x72, 0x35, 0x75, 0x38, 0x78, 0x21, 0x41,
    0x25, 0x44, 0x2A, 0x47, 0x2D, 0x4B, 0x61, 0x50,
    0x64, 0x53, 0x67, 0x56, 0x6B, 0x59, 0x70, 0x33,
    0x73, 0x36, 0x76, 0x39, 0x79, 0x24, 0x42, 0x3F
  };
  uint8_t sourceData[] = 
  {
    0xC1, 0x2A, 0x81, 0xC0, 0x6C, 0xC3, 0xDB, 0x9F,
    0x70, 0x54, 0x74, 0xB4, 0xB9, 0x3E, 0xA3, 0x1B,
    0xF7, 0xA2, 0xEC, 0xAF, 0x39, 0x0F, 0x9D, 0x43,
    0x00, 0x0F, 0x82, 0xF8, 0xBC, 0xFE, 0x23, 0x1A
  };
  uint8_t tmpBuffer[sizeof(sourceData)/sizeof(sourceData[0])];
  const size_t sourceLen = sizeof(sourceData)/sizeof(sourceData[0]);
  uint8_t idx;
  uint8_t dataChanged;

  /* Pass a NULL pointer for the data byte array. */
  TbxCryptoAes256Decrypt(NULL, sourceLen, cryptoKey);
  /* Make sure an assertion was triggered. */
  TEST_ASSERT_GREATER_THAN_UINT32(0, assertionCnt);

  /* Reset the assertion counter. */
  assertionCnt = 0;
  /* Copy the source data to the temp buffer. */
  for (idx = 0; idx < sourceLen; idx++)
  {
    tmpBuffer[idx] = sourceData[idx];
  }
  /* Pass a size of zero. */
  TbxCryptoAes256Decrypt(tmpBuffer, 0, cryptoKey);
  /* Make sure an assertion was triggered. */
  TEST_ASSERT_GREATER_THAN_UINT32(0, assertionCnt);
  /* Verify that no decryption was attempted. */
  dataChanged = TBX_FALSE;
  for (idx = 0; idx < sourceLen; idx++)
  {
    if (tmpBuffer[idx] != sourceData[idx])
    {
      dataChanged = TBX_TRUE;
      break;
    }
  }
  TEST_ASSERT_EQUAL(TBX_FALSE, dataChanged);

  /* Reset the assertion counter. */
  assertionCnt = 0;
  /* Copy the source data to the temp buffer. */
  for (idx = 0; idx < sourceLen; idx++)
  {
    tmpBuffer[idx] = sourceData[idx];
  }
  /* Pass a size that is not aligned to the AES256 block size. */
  TbxCryptoAes256Decrypt(tmpBuffer, 15, cryptoKey);
  /* Make sure an assertion was triggered. */
  TEST_ASSERT_GREATER_THAN_UINT32(0, assertionCnt);
  /* Verify that no decryption was attempted. */
  dataChanged = TBX_FALSE;
  for (idx = 0; idx < sourceLen; idx++)
  {
    if (tmpBuffer[idx] != sourceData[idx])
    {
      dataChanged = TBX_TRUE;
      break;
    }
  }
  TEST_ASSERT_EQUAL(TBX_FALSE, dataChanged);

  /* Reset the assertion counter. */
  assertionCnt = 0;
  /* Copy the source data to the temp buffer. */
  for (idx = 0; idx < sourceLen; idx++)
  {
    tmpBuffer[idx] = sourceData[idx];
  }
  /* Pass a NULL pointer for the key. */
  TbxCryptoAes256Decrypt(tmpBuffer, sourceLen, NULL);
  /* Make sure an assertion was triggered. */
  TEST_ASSERT_GREATER_THAN_UINT32(0, assertionCnt);
  /* Verify that no decryption was attempted. */
  dataChanged = TBX_FALSE;
  for (idx = 0; idx < sourceLen; idx++)
  {
    if (tmpBuffer[idx] != sourceData[idx])
    {
      dataChanged = TBX_TRUE;
      break;
    }
  }
  TEST_ASSERT_EQUAL(TBX_FALSE, dataChanged);
} /*** end of test_TbxCryptoAes256Decrypt_ShouldAssertOnInvalidParams ***/


/************************************************************************************//**
** \brief     Tests that data is properly decrypted.
**
****************************************************************************************/
void test_TbxCryptoAes256Decrypt_ShouldDecrypt(void)
{
  const uint8_t cryptoKey[] =
  {
    0x32, 0x72, 0x35, 0x75, 0x38, 0x78, 0x21, 0x41,
    0x25, 0x44, 0x2A, 0x47, 0x2D, 0x4B, 0x61, 0x50,
    0x64, 0x53, 0x67, 0x56, 0x6B, 0x59, 0x70, 0x33,
    0x73, 0x36, 0x76, 0x39, 0x79, 0x24, 0x42, 0x3F
  };
  uint8_t sourceData[] = 
  {
    0xC1, 0x2A, 0x81, 0xC0, 0x6C, 0xC3, 0xDB, 0x9F,
    0x70, 0x54, 0x74, 0xB4, 0xB9, 0x3E, 0xA3, 0x1B,
    0xF7, 0xA2, 0xEC, 0xAF, 0x39, 0x0F, 0x9D, 0x43,
    0x00, 0x0F, 0x82, 0xF8, 0xBC, 0xFE, 0x23, 0x1A
  };
  const uint8_t expectedData[] = 
  {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F
  };
  uint8_t tmpBuffer[sizeof(sourceData)/sizeof(sourceData[0])];
  const size_t sourceLen = sizeof(sourceData)/sizeof(sourceData[0]);
  uint8_t idx;
  uint8_t dataOkay = TBX_TRUE;

  /* Copy the source data to the temp buffer. */
  for (idx = 0; idx < sourceLen; idx++)
  {
    tmpBuffer[idx] = sourceData[idx];
  }
  /* Perform the decryption. */
  TbxCryptoAes256Decrypt(tmpBuffer, sourceLen, cryptoKey);
  /* Make sure no assertion was triggered. */
  TEST_ASSERT_EQUAL_UINT32(0, assertionCnt);
  /* Verify that the decrypted data is as expected. */
  for (idx = 0; idx < sourceLen; idx++)
  {
    if (tmpBuffer[idx] != expectedData[idx])
    {
      dataOkay = TBX_FALSE;
    }
  }
  TEST_ASSERT_EQUAL(TBX_TRUE, dataOkay);
} /*** end of test_TbxCryptoAes256Decrypt_ShouldDecrypt ***/


/****************************************************************************************
* Local data declarations
****************************************************************************************/
const size_t memPoolNumBlocks = 2;
const size_t memPoolBlockSize = 16;
void * memPoolAllocatedBlocks[3];


/************************************************************************************//**
** \brief     Tests that invalid parameters trigger an assertion and returns TBX_ERROR.
**
****************************************************************************************/
void test_TbxMemPoolCreate_ShouldAssertOnInvalidParams(void)
{
  uint8_t result;
  size_t  heapFreeBefore;
  size_t  heapFreeAfter;

  /* It should not be possible to create a memory pool with zero blocks. */
  heapFreeBefore = TbxHeapGetFree();
  result = TbxMemPoolCreate(0, 16);
  heapFreeAfter = TbxHeapGetFree();
  /* Make sure an assertion was triggered. */
  TEST_ASSERT_GREATER_THAN_UINT32(0, assertionCnt);
  /* Make sure an error was returned. */
  TEST_ASSERT_EQUAL(TBX_ERROR, result);
  /* Make sure no heap memory was allocated. */
  TEST_ASSERT_EQUAL(heapFreeBefore, heapFreeAfter);

  /* Reset the assertion counter. */
  assertionCnt = 0;
  /* It should not be possible to create a memory pool of zero sized blocks. */
  heapFreeBefore = TbxHeapGetFree();
  result = TbxMemPoolCreate(1, 0);
  heapFreeAfter = TbxHeapGetFree();
  /* Make sure an assertion was triggered. */
  TEST_ASSERT_GREATER_THAN_UINT32(0, assertionCnt);
  /* Make sure an error was returned. */
  TEST_ASSERT_EQUAL(TBX_ERROR, result);
  /* Make sure no heap memory was allocated. */
  TEST_ASSERT_EQUAL(heapFreeBefore, heapFreeAfter);
} /*** end of test_TbxMemPoolCreate_ShouldAssertOnInvalidParams ***/


/************************************************************************************//**
** \brief     Tests that it cannot create memory pools that require more memory than
**            currently available on the heap. It should also returns TBX_ERROR.
**
****************************************************************************************/
void test_TbxMemPoolCreate_CannotAllocateMoreThanFreeHeap(void)
{
  uint8_t result;
  size_t  heapFree;

  /* Try to create a memory pool with just one block, but a block size larger than what
   * is free on the heap at this point.
   */
  heapFree = TbxHeapGetFree();
  result = TbxMemPoolCreate(1, heapFree + 1);
  /* Make sure an error was returned. */
  TEST_ASSERT_EQUAL(TBX_ERROR, result);
} /*** end of test_TbxMemPoolCreate_CannotAllocateMoreThanFreeHeap ***/


/************************************************************************************//**
** \brief     Tests that a memory pool can be created.
**
****************************************************************************************/
void test_TbxMemPoolCreate_CanCreatePool(void)
{
  uint8_t result;
  size_t heapFreeBefore;
  size_t heapFreeAfter;

  /* Try to create a memory pool with 2 blocks of 16 bytes. */
  heapFreeBefore = TbxHeapGetFree();
  result = TbxMemPoolCreate(memPoolNumBlocks, memPoolBlockSize);
  heapFreeAfter = TbxHeapGetFree();

  /* Make sure no error was returned. */
  TEST_ASSERT_EQUAL(TBX_OK, result);
  /* Make sure at least the data for the blocks was allocated from the heap. */
  TEST_ASSERT_GREATER_OR_EQUAL(memPoolNumBlocks * memPoolBlockSize, 
                               heapFreeBefore - heapFreeAfter);
  /* Make sure no assertion was triggered. */
  TEST_ASSERT_EQUAL_UINT32(0, assertionCnt);
} /*** end of test_TbxMemPoolCreate_CanCreatePool ***/


/************************************************************************************//**
** \brief     Tests that invalid parameters trigger and assertion and returns NULL.
**
****************************************************************************************/
void test_TbxMemPoolAllocate_ShouldAssertOnInvalidParams(void)
{
  void * result;

  /* Attempt to allocate zero bytes, which is not a valid size. */
  result = TbxMemPoolAllocate(0);

  /* Make sure an assertion was triggered. */
  TEST_ASSERT_GREATER_THAN_UINT32(0, assertionCnt);
  /* Make sure a NULL pointer was returned. */
  TEST_ASSERT_NULL(result);
} /*** end of test_TbxMemPoolAllocate_ShouldAssertOnInvalidParams ***/


/************************************************************************************//**
** \brief     Tests that a block can be allocated from the previously created memory
**            pool. Use a block size exactly the same for which the memory pool was
**            created.
**
****************************************************************************************/
void test_TbxMemPoolAllocate_CanAllocateSameSize(void)
{
  /* Attempt to allocate a block inside the previously created memory pool. */
  memPoolAllocatedBlocks[0] = TbxMemPoolAllocate(memPoolBlockSize);
  /* Make sure a valid pointer was returned. */
  TEST_ASSERT_NOT_NULL(memPoolAllocatedBlocks[0]);
  /* Make sure no assertion was triggered. */
  TEST_ASSERT_EQUAL_UINT32(0, assertionCnt);
} /*** end of test_TbxMemPoolAllocate_CanAllocateSameSize ***/


/************************************************************************************//**
** \brief     Tests that a block cannot be allocated from the previously created memory
**            pool, when using a block size that is larger than for which the memory pool
**            was created. It should automatically match it to the memory pool of the
**            next size. This design decision was made, because you can then implement
**            logic that automatically increases the size of a memory pool in this case.
**
****************************************************************************************/
void test_TbxMemPoolAllocate_CannotAllocateLargerSize(void)
{
  void * result;

  /* Attempt to allocate another block inside the previously created memory pool. This
   * time with a block size slightly larger to test that it does not match it.
   */
  result = TbxMemPoolAllocate(memPoolBlockSize + 1);
  /* Make sure a NULL pointer was returned. */
  TEST_ASSERT_NULL(result);
  /* Make sure no assertion was triggered. */
  TEST_ASSERT_EQUAL_UINT32(0, assertionCnt);
} /*** end of test_TbxMemPoolAllocate_CannotAllocateLargerSize ***/


/************************************************************************************//**
** \brief     Tests that a block can be allocated from the previously created memory
**            pool. Use a block size that is a bit smaller than for which the memory pool
**            was created. It should automatically match it to the memory pool of the
**            next size.
**
****************************************************************************************/
void test_TbxMemPoolAllocate_CanAllocateSmallerSize(void)
{
  /* Attempt to allocate another block inside the previously created memory pool. This
   * time with a block size slightly smaller to test that it matched it to the memory
   * pool of the next size.
   */
  memPoolAllocatedBlocks[1] = TbxMemPoolAllocate(memPoolBlockSize - 1);
  /* Make sure a valid pointer was returned. */
  TEST_ASSERT_NOT_NULL(memPoolAllocatedBlocks[1]);
  /* Make sure no assertion was triggered. */
  TEST_ASSERT_EQUAL_UINT32(0, assertionCnt);
} /*** end of test_TbxMemPoolAllocate_CanAllocateSmallerSize ***/


/************************************************************************************//**
** \brief     Tests that a block cannot be allocated from the previously created memory
**            pool, when all available blocks are already allocated.
**
****************************************************************************************/
void test_TbxMemPoolAllocate_CannotAllocateWhenFull(void)
{
  void * result;

  /* Attempt to allocate another block inside the previously created memory pool. Use
   * a valid block size for the memory pool.
   */
  result = TbxMemPoolAllocate(memPoolBlockSize);
  /* Make sure a NULL pointer was returned, because the previous tests already allocated
   * all blocks from this memory pool.
   */
  TEST_ASSERT_NULL(result);
  /* Make sure no assertion was triggered. */
  TEST_ASSERT_EQUAL_UINT32(0, assertionCnt);
} /*** end of test_TbxMemPoolAllocate_CannotAllocateWhenFull ***/


/************************************************************************************//**
** \brief     Tests that a memory pool can be dynamically increased.
**
****************************************************************************************/
void test_TbxMemPoolCreate_CanIncreasePoolSize(void)
{
  uint8_t increaseResult;
  void * result;

  /* First double-check that the memory pool no longer has free blocks. The previous 
   * test should have caused this.
   */
  result = TbxMemPoolAllocate(memPoolBlockSize);
  /* Make sure a NULL pointer was returned, because the previous tests already allocated
   * all blocks from this memory pool.
   */
  TEST_ASSERT_NULL(result);
  
  /* Now increase the memory pool by one. This is done by create a memory pool with the
   * same size. Because a memory pool with the same size already exists, the existing
   * one will simply be increased in size.
   */
  increaseResult = TbxMemPoolCreate(1, memPoolBlockSize);
  /* Make sure no error was returned. */
  TEST_ASSERT_EQUAL(TBX_OK, increaseResult);

  /* Now one more free block should be available. Verify this by allocating it. */
  memPoolAllocatedBlocks[2] = TbxMemPoolAllocate(memPoolBlockSize);
  /* Make sure a valid pointer was returned. */
  TEST_ASSERT_NOT_NULL(memPoolAllocatedBlocks[2]);

  /* Make sure no assertion was triggered. */
  TEST_ASSERT_EQUAL_UINT32(0, assertionCnt);
} /*** end of test_TbxMemPoolCreate_CanIncreasePoolSize ***/


/************************************************************************************//**
** \brief     Tests that invalid parameters trigger and assertion.
**
****************************************************************************************/
void test_TbxMemPoolRelease_ShouldAssertOnInvalidParams(void)
{
  /* Pass on a NULL pointer, which should not work. */
  TbxMemPoolRelease(NULL);
  /* Make sure an assertion was triggered. */
  TEST_ASSERT_GREATER_THAN_UINT32(0, assertionCnt);

  /* Reset the assertion counter. */
  assertionCnt = 0;

  /* Next, pass a valid pointer but not one that belongs to a previously allocated
   * block from any memory pool. Basically use the first allocated pointer and deduct
   * a bunch of bytes to make sure it is outside of the memory pool range.
   */
  TbxMemPoolRelease(memPoolAllocatedBlocks[0] - 0x1000);
  /* Make sure an assertion was triggered. */
  TEST_ASSERT_GREATER_THAN_UINT32(0, assertionCnt);
} /*** end of test_TbxMemPoolRelease_ShouldAssertOnInvalidParams ***/


/************************************************************************************//**
** \brief     Tests that all previously allocated blocks can be released back to the
**            memory pool.
**
****************************************************************************************/
void test_TbxMemPoolRelease_CanReleaseBlocks(void)
{
  /* Release all previously allocated blocks. */
  TbxMemPoolRelease(memPoolAllocatedBlocks[0]);
  TbxMemPoolRelease(memPoolAllocatedBlocks[1]);
  TbxMemPoolRelease(memPoolAllocatedBlocks[2]);
  /* Make sure no assertion was triggered. */
  TEST_ASSERT_EQUAL_UINT32(0, assertionCnt);
} /*** end of test_TbxMemPoolRelease_CanReleaseBlocks ***/


/************************************************************************************//**
** \brief     Tests that all previously released blocks can be reallocated.
**
****************************************************************************************/
void test_TbxMemPoolAllocate_CanReallocate(void)
{
  void * result;
  size_t heapFreeBefore;
  size_t heapFreeAfter;

  /* Get the current free heap size. */
  heapFreeBefore = TbxHeapGetFree();

  /* Attempt to allocate the first block. */
  memPoolAllocatedBlocks[0] = TbxMemPoolAllocate(memPoolBlockSize);
  /* Make sure a valid pointer was returned. */
  TEST_ASSERT_NOT_NULL(memPoolAllocatedBlocks[0]);
  /* Make sure no assertion was triggered. */
  TEST_ASSERT_EQUAL_UINT32(0, assertionCnt);

  /* Reset the assertion counter. */
  assertionCnt = 0;
  /* Attempt to allocate the second block. */
  memPoolAllocatedBlocks[1] = TbxMemPoolAllocate(memPoolBlockSize);
  /* Make sure a valid pointer was returned. */
  TEST_ASSERT_NOT_NULL(memPoolAllocatedBlocks[1]);
  /* Make sure no assertion was triggered. */
  TEST_ASSERT_EQUAL_UINT32(0, assertionCnt);

  /* Reset the assertion counter. */
  assertionCnt = 0;
  /* Attempt to allocate the third block. */
  memPoolAllocatedBlocks[2] = TbxMemPoolAllocate(memPoolBlockSize);
  /* Make sure a valid pointer was returned. */
  TEST_ASSERT_NOT_NULL(memPoolAllocatedBlocks[2]);
  /* Make sure no assertion was triggered. */
  TEST_ASSERT_EQUAL_UINT32(0, assertionCnt);

  /* Reset the assertion counter. */
  assertionCnt = 0;
  /* Attempt to allocate one more block. It should fail because the memory pool is
   * exhausted by now.
   */
  result = TbxMemPoolAllocate(memPoolBlockSize);
  /* Make sure a NULL pointer was returned, because the previous tests already allocated
   * all blocks from this memory pool.
   */
  TEST_ASSERT_NULL(result);
  /* Make sure no assertion was triggered. */
  TEST_ASSERT_EQUAL_UINT32(0, assertionCnt);

  /* Get the current free heap size. */
  heapFreeAfter = TbxHeapGetFree();
  /* Verify that no new memory from the heap was needed. This proves that the memory
   * pool was fully reused.
   */
  TEST_ASSERT_EQUAL(heapFreeBefore, heapFreeAfter);
} /*** end of test_TbxMemPoolAllocate_CanReallocate ***/


/****************************************************************************************
* Type definitions
****************************************************************************************/
typedef struct
{
  uint32_t id;
  uint8_t  len;
  uint8_t  data[8];
} tListTestMsg;


/****************************************************************************************
* Local data declarations
****************************************************************************************/
static tTbxList * listTestList;
static tListTestMsg listTestMsgA = 
{
  .id = 123,
  .len = 8,
  .data = { 0, 1, 2, 3, 4, 5, 7 }
};
static tListTestMsg listTestMsgB = 
{
  .id = 456,
  .len = 4,
  .data = { 8, 9, 10, 11 }
};
static tListTestMsg listTestMsgC = 
{
  .id = 789,
  .len = 2,
  .data = { 12, 13 }
};


/************************************************************************************//**
** \brief     Tests that a new list can be created.
**
****************************************************************************************/
void test_TbxListCreate_ReturnsValidListPointer(void)
{
  /* Attempt to create a new linked list. */
  listTestList = TbxListCreate();
  /* Make sure a valid pointer was returned. */
  TEST_ASSERT_NOT_NULL(listTestList);
  /* Make sure no assertion was triggered. */
  TEST_ASSERT_EQUAL_UINT32(0, assertionCnt);
} /*** end of test_TbxListCreate_ReturnsValidListPointer ***/


/************************************************************************************//**
** \brief     Tests that invalid parameters trigger and assertion.
**
****************************************************************************************/
void test_TbxListDelete_ShouldAssertOnInvalidParams(void)
{
  /* Pass on a NULL pointer, which should not work. */
  TbxListDelete(NULL);
  /* Make sure an assertion was triggered. */
  TEST_ASSERT_GREATER_THAN_UINT32(0, assertionCnt);
} /*** end of test_TbxListDelete_ShouldAssertOnInvalidParams ***/


/************************************************************************************//**
** \brief     Tests that an existing list can be deleted.
**
****************************************************************************************/
void test_TbxListDelete_CanDelete(void)
{
  /* Delete the previously created linked list. */
  TbxListDelete(listTestList);  
  /* Make sure no assertion was triggered. */
  TEST_ASSERT_EQUAL_UINT32(0, assertionCnt);
} /*** end of test_TbxListDelete_CanDelete ***/


/************************************************************************************//**
** \brief     Tests that invalid parameters trigger and assertion and returns 0.
**
****************************************************************************************/
void test_TbxListClear_ShouldAssertOnInvalidParams(void)
{
  /* Pass on a NULL pointer, which should not work. */
  TbxListClear(NULL);
  /* Make sure an assertion was triggered. */
  TEST_ASSERT_GREATER_THAN_UINT32(0, assertionCnt);
} /*** end of test_TbxListClear_ShouldAssertOnInvalidParams ***/


/************************************************************************************//**
** \brief     Tests that entries from a list can be cleared.
**
****************************************************************************************/
void test_TbxListClear_CanEmptyList(void)
{
  tTbxList * myList;
  size_t listSize;

  /* Create a new linked list. */
  myList = TbxListCreate();
  /* Add two items. */
  (void)TbxListInsertItemBack(myList, &listTestMsgA);
  (void)TbxListInsertItemBack(myList, &listTestMsgB);
  /* Make sure its size is now two. */
  listSize = TbxListGetSize(myList);
  TEST_ASSERT_EQUAL(2, listSize);
  /* Clear the list. */
  TbxListClear(myList);
  /* Make sure its size is now zero. */
  listSize = TbxListGetSize(myList);
  TEST_ASSERT_EQUAL(0, listSize);
  /* Add two items again. */
  (void)TbxListInsertItemBack(myList, &listTestMsgA);
  (void)TbxListInsertItemBack(myList, &listTestMsgB);
  /* Make sure its size is now two. */
  listSize = TbxListGetSize(myList);
  TEST_ASSERT_EQUAL(2, listSize);
  /* Delete the list as cleanup. */
  TbxListDelete(myList);
  /* Make sure no assertion was triggered. */
  TEST_ASSERT_EQUAL_UINT32(0, assertionCnt);
} /*** end of test_TbxListClear_CanEmptyList ***/


/************************************************************************************//**
** \brief     Tests that invalid parameters trigger and assertion and returns 0.
**
****************************************************************************************/
void test_TbxListGetSize_ShouldAssertOnInvalidParams(void)
{
  size_t result;

  /* Pass on a NULL pointer, which should not work. */
  result = TbxListGetSize(NULL);
  /* Make sure it returns zero. */
  TEST_ASSERT_EQUAL(0, result);
  /* Make sure an assertion was triggered. */
  TEST_ASSERT_GREATER_THAN_UINT32(0, assertionCnt);
} /*** end of test_TbxListGetSize_ShouldAssertOnInvalidParams ***/


/************************************************************************************//**
** \brief     Tests that the number of entries in a list can be properly obtained.
**
****************************************************************************************/
void test_TbxListGetSize_ReturnsActualSize(void)
{
  tTbxList * myList;
  size_t listSize;

  /* Create a new linked list. */
  myList = TbxListCreate();
  /* Make sure its size is zero. */
  listSize = TbxListGetSize(myList);
  TEST_ASSERT_EQUAL(0, listSize);
  /* Add two items. */
  (void)TbxListInsertItemBack(myList, &listTestMsgA);
  (void)TbxListInsertItemBack(myList, &listTestMsgB);
  /* Make sure its size is now two. */
  listSize = TbxListGetSize(myList);
  TEST_ASSERT_EQUAL(2, listSize);
  /* Delete the list as cleanup. */
  TbxListDelete(myList);
  /* Make sure no assertion was triggered. */
  TEST_ASSERT_EQUAL_UINT32(0, assertionCnt);
} /*** end of test_TbxListGetSize_ReturnsActualSize ***/


/************************************************************************************//**
** \brief     Tests that invalid parameters trigger and assertion and returns TBX_ERROR.
**
****************************************************************************************/
void test_TbxListInsertItemFront_ShouldAssertOnInvalidParams(void)
{
  uint8_t result;
  tTbxList * myList;

  /* Create a new linked list. */
  myList = TbxListCreate();
  /* Pass on a NULL pointer for the list, which should not work. */
  result = TbxListInsertItemFront(NULL, &listTestMsgA);
  /* Make sure it returns an error. */
  TEST_ASSERT_EQUAL_UINT8(TBX_ERROR, result);
  /* Make sure an assertion was triggered. */
  TEST_ASSERT_GREATER_THAN_UINT32(0, assertionCnt);
  /* Reset the assertion counter. */
  assertionCnt = 0;
  /* Pass on a NULL pointer for the time, which should not work. */
  result = TbxListInsertItemFront(myList, NULL);
  /* Make sure it returns an error. */
  TEST_ASSERT_EQUAL_UINT8(TBX_ERROR, result);
  /* Make sure an assertion was triggered. */
  TEST_ASSERT_GREATER_THAN_UINT32(0, assertionCnt);
  /* Delete the list as cleanup. */
  TbxListDelete(myList);
} /*** end of test_TbxListInsertItemFront_ShouldAssertOnInvalidParams ***/


/************************************************************************************//**
** \brief     Tests that an item is inserted at the front of the linked list.
**
****************************************************************************************/
void test_TbxListInsertItemFront_InsertsAtCorrectLocation(void)
{
  tTbxList * myList;
  tListTestMsg * myMsg;
  uint8_t sameMsg;

  /* Create a new linked list. */
  myList = TbxListCreate();
  /* Add an item. */
  (void)TbxListInsertItemFront(myList, &listTestMsgA);
  /* Make sure listTestMsgA is in the front of the list. */
  myMsg = TbxListGetFirstItem(myList);
  sameMsg = TBX_FALSE;
  if ((myMsg->id == listTestMsgA.id) && (myMsg == &listTestMsgA))
  {
    sameMsg = TBX_TRUE;
  }
  /* Add another item. */
  (void)TbxListInsertItemFront(myList, &listTestMsgB);
  /* Make sure listTestMsgB is in the front of the list. */
  myMsg = TbxListGetFirstItem(myList);
  sameMsg = TBX_FALSE;
  if ((myMsg->id == listTestMsgB.id) && (myMsg == &listTestMsgB))
  {
    sameMsg = TBX_TRUE;
  }
  /* Delete the list as cleanup. */
  TbxListDelete(myList);
  /* Make sure no assertion was triggered. */
  TEST_ASSERT_EQUAL_UINT32(0, assertionCnt);
} /*** end of test_TbxListInsertItemFront_InsertsAtCorrectLocation ***/


/************************************************************************************//**
** \brief     Tests that invalid parameters trigger and assertion and returns TBX_ERROR.
**
****************************************************************************************/
void test_TbxListInsertItemBack_ShouldAssertOnInvalidParams(void)
{
  uint8_t result;
  tTbxList * myList;

  /* Create a new linked list. */
  myList = TbxListCreate();
  /* Pass on a NULL pointer for the list, which should not work. */
  result = TbxListInsertItemBack(NULL, &listTestMsgA);
  /* Make sure it returns an error. */
  TEST_ASSERT_EQUAL_UINT8(TBX_ERROR, result);
  /* Make sure an assertion was triggered. */
  TEST_ASSERT_GREATER_THAN_UINT32(0, assertionCnt);
  /* Reset the assertion counter. */
  assertionCnt = 0;
  /* Pass on a NULL pointer for the time, which should not work. */
  result = TbxListInsertItemBack(myList, NULL);
  /* Make sure it returns an error. */
  TEST_ASSERT_EQUAL_UINT8(TBX_ERROR, result);
  /* Make sure an assertion was triggered. */
  TEST_ASSERT_GREATER_THAN_UINT32(0, assertionCnt);
  /* Delete the list as cleanup. */
  TbxListDelete(myList);
} /*** end of test_TbxListInsertItemBack_ShouldAssertOnInvalidParams ***/


/************************************************************************************//**
** \brief     Tests that an item is inserted at the back of the linked list.
**
****************************************************************************************/
void test_TbxListInsertItemBack_InsertsAtCorrectLocation(void)
{
  tTbxList * myList;
  tListTestMsg * myMsg;
  uint8_t sameMsg;

  /* Create a new linked list. */
  myList = TbxListCreate();
  /* Add an item. */
  (void)TbxListInsertItemBack(myList, &listTestMsgA);
  /* Make sure listTestMsgA is in the back of the list. */
  myMsg = TbxListGetLastItem(myList);
  sameMsg = TBX_FALSE;
  if ((myMsg->id == listTestMsgA.id) && (myMsg == &listTestMsgA))
  {
    sameMsg = TBX_TRUE;
  }
  /* Add another item. */
  (void)TbxListInsertItemBack(myList, &listTestMsgB);
  /* Make sure listTestMsgB is in the front of the list. */
  myMsg = TbxListGetLastItem(myList);
  sameMsg = TBX_FALSE;
  if ((myMsg->id == listTestMsgB.id) && (myMsg == &listTestMsgB))
  {
    sameMsg = TBX_TRUE;
  }
  /* Delete the list as cleanup. */
  TbxListDelete(myList);
  /* Make sure no assertion was triggered. */
  TEST_ASSERT_EQUAL_UINT32(0, assertionCnt);
} /*** end of test_TbxListInsertItemBack_InsertsAtCorrectLocation ***/


/* TODO Continue with TbxListInsertItemBefore. */


/************************************************************************************//**
** \brief     Handles the running of the unit tests.
** \return    Test results.
**
****************************************************************************************/
int runTests(void)
{
  /* Inform the framework that unit testing is about to start. */
  UNITY_BEGIN();
  /* Tests that are generic and not module specific. */
  RUN_TEST(test_TbxGeneric_VersionMacrosShouldBePresent);
  RUN_TEST(test_TbxGeneric_BooleanMacrosShouldBePresent);
  RUN_TEST(test_TbxGeneric_UnusedArgMacroShouldBePresent);
  /* Tests for the assertion module. */
  RUN_TEST(test_TbxAssertSetHandler_ShouldTriggerAssertionIfParamNull);
  RUN_TEST(test_TbxAssertTrigger_ShouldTriggerAssertion);
  /* Tests for the critical section module. */
  RUN_TEST(test_TbxCriticalSectionExit_ShouldTriggerAssertionIfNotInCritSect);
  RUN_TEST(test_TbxCriticalSectionEnter_ShouldNotAssertUponCritSectExit);
  /* Tests for the heap module. */
  RUN_TEST(test_TbxHeapGetFree_ShouldReturnActualFreeSize);
  RUN_TEST(test_TbxHeapAllocate_ShouldReturnNotNull);
  RUN_TEST(test_TbxHeapAllocate_ShouldReturnNullIfZeroSizeAllocated);
  RUN_TEST(test_TbxHeapAllocate_ShouldReturnNullIfTooMuchAllocated);
  RUN_TEST(test_TbxHeapAllocate_ShouldAlignToAddressSize);
  /* Tests for the random number module. */
  RUN_TEST(test_TbxRandomSetSeedInitHandler_ShouldTriggerAssertionIfParamNull);
  RUN_TEST(test_TbxRandomSetSeedInitHandler_ShouldWork);
  RUN_TEST(test_TbxRandomNumberGet_ShouldReturnRandomNumbers);
  /* Tests for the checksum module. */
  RUN_TEST(test_TbxChecksumCrc16Calculate_ShouldAssertOnInvalidParams);
  RUN_TEST(test_TbxChecksumCrc16Calculate_ShouldReturnValidCrc16);
  RUN_TEST(test_TbxChecksumCrc32Calculate_ShouldAssertOnInvalidParams);
  RUN_TEST(test_TbxChecksumCrc32Calculate_ShouldReturnValidCrc32);
  /* Tests for the cryptography module. */
  RUN_TEST(test_TbxCryptoAes256Encrypt_ShouldAssertOnInvalidParams);
  RUN_TEST(test_TbxCryptoAes256Encrypt_ShouldEncrypt);
  RUN_TEST(test_TbxCryptoAes256Decrypt_ShouldAssertOnInvalidParams);
  RUN_TEST(test_TbxCryptoAes256Decrypt_ShouldDecrypt);
  /* Tests for the memory pool module. */
  RUN_TEST(test_TbxMemPoolCreate_ShouldAssertOnInvalidParams);
  RUN_TEST(test_TbxMemPoolCreate_CannotAllocateMoreThanFreeHeap);
  RUN_TEST(test_TbxMemPoolCreate_CanCreatePool);
  RUN_TEST(test_TbxMemPoolAllocate_ShouldAssertOnInvalidParams);
  RUN_TEST(test_TbxMemPoolAllocate_CanAllocateSameSize);
  RUN_TEST(test_TbxMemPoolAllocate_CannotAllocateLargerSize);
  RUN_TEST(test_TbxMemPoolAllocate_CanAllocateSmallerSize);
  RUN_TEST(test_TbxMemPoolAllocate_CannotAllocateWhenFull);
  RUN_TEST(test_TbxMemPoolCreate_CanIncreasePoolSize);
  RUN_TEST(test_TbxMemPoolRelease_ShouldAssertOnInvalidParams);
  RUN_TEST(test_TbxMemPoolRelease_CanReleaseBlocks);
  RUN_TEST(test_TbxMemPoolAllocate_CanReallocate);
  /* Tests for the linked list module. */
  RUN_TEST(test_TbxListCreate_ReturnsValidListPointer);
  RUN_TEST(test_TbxListDelete_ShouldAssertOnInvalidParams);
  RUN_TEST(test_TbxListDelete_CanDelete);
  RUN_TEST(test_TbxListClear_ShouldAssertOnInvalidParams);
  RUN_TEST(test_TbxListClear_CanEmptyList);
  RUN_TEST(test_TbxListGetSize_ShouldAssertOnInvalidParams);
  RUN_TEST(test_TbxListGetSize_ReturnsActualSize);
  RUN_TEST(test_TbxListInsertItemFront_ShouldAssertOnInvalidParams);
  RUN_TEST(test_TbxListInsertItemFront_InsertsAtCorrectLocation);
  RUN_TEST(test_TbxListInsertItemBack_ShouldAssertOnInvalidParams);
  RUN_TEST(test_TbxListInsertItemBack_InsertsAtCorrectLocation);
  /* Inform the framework that unit testing is done and return the result. */
  return UNITY_END();
} /*** end of runUnittests ***/


/************************************************************************************//**
** \brief     Initialization before running the unit tests.
**
****************************************************************************************/
void initializeTests(void)
{
/* Register the application specific assertion handler. */
  TbxAssertSetHandler(handleTbxAssertion);
} /*** end of initializeTests ***/


/************************************************************************************//**
** \brief     Code to run before each test.
**
****************************************************************************************/
void setUp(void)
{
  /* Reset the assertion counter. */
  assertionCnt = 0;
} /*** end of setUp ***/


/************************************************************************************//**
** \brief     Code to run after each test.
**
****************************************************************************************/
void tearDown(void)
{
} /*** end of tearDown ***/


/*********************************** end of unittests.c ********************************/
