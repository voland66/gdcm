/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef GDCMAASSOCIATERJPDU_H
#define GDCMAASSOCIATERJPDU_H

#include "gdcmTypes.h"
#include "gdcmBasePDU.h"

namespace gdcm
{

namespace network
{

/**
 * \brief AAssociateRJPDU
 * Table 9-21
 * ASSOCIATE-RJ PDU FIELDS
 */
class AAssociateRJPDU : public BasePDU
{
public:
  AAssociateRJPDU();
  std::istream &Read(std::istream &is);
  const std::ostream &Write(std::ostream &os) const;
  void Print(std::ostream &os) const;
  size_t Size() const;
  bool IsLastFragment() const { return true; }
private:
  static const uint8_t ItemType; // PDUType ?
  static const uint8_t Reserved2;
  uint32_t ItemLength; // PDU Length ?
  static const uint8_t Reserved8;
  uint8_t Result;
  uint8_t Source;
  uint8_t Reason; // diag ?
};

} // end namespace network

} // end namespace gdcm

#endif //GDCMAASSOCIATERJPDU_H
