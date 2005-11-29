#include "gdcmType.h"
#include "gdcmByteSwap.txx"

int myfunc()
{
  char vl_str[5];
  vl_str[4] = '\0';
  const char raw[] = "\000\000\000\004";
  memcpy(vl_str, raw, 4); // strncpy gets confused because of the \0
  uint32_t vl;
  gdcm::ByteSwap<uint32_t>::SwapRangeFromSwapCodeIntoSystem((uint32_t*)(&vl_str), gdcm::SC::BigEndian, 1);
  memcpy(&vl, vl_str, 4);
  std::cout << std::hex << "vl: " << vl << std::endl;
  if( vl != 0x00000004 )
    return 1;

  gdcm::ByteSwap<uint32_t>::SwapFromSwapCodeIntoSystem(vl, gdcm::SC::LittleEndian);
  std::cout << std::hex << "vl: " << vl << std::endl;
  if( vl != 0x00000004 )
    return 1;

  gdcm::ByteSwap<uint32_t>::SwapFromSwapCodeIntoSystem(vl, gdcm::SC::BigEndian);
  std::cout << std::hex << "vl: " << vl << std::endl;
  if( vl != 0x4000000 )
    return 1;

  return 0;
}

int TestSwap(int , char *[])
{
  gdcm::SC::SwapCodeType sc = gdcm::SC::Unknown;
  if ( gdcm::ByteSwap<uint16_t>::SystemIsBigEndian() )
    {
    sc = gdcm::SC::BigEndian;
    }
  else if ( gdcm::ByteSwap<uint16_t>::SystemIsLittleEndian() )
    {
    sc = gdcm::SC::LittleEndian;
    }
  if( sc == gdcm::SC::Unknown )
    {
    return 1;
    }

  std::cout << "sc: " << sc << std::endl;

  uint16_t t = 0x1234;
  gdcm::ByteSwap<uint16_t>::SwapFromSwapCodeIntoSystem(t, sc);
  std::cout << std::hex << "t: " << t << std::endl;
  if( sc == gdcm::SC::BigEndian )
    {
    if( t != 0x3412 )
      return 1;
    }
  else if ( sc == gdcm::SC::LittleEndian )
    {
    if( t != 0x1234 )
      return 1;
    }

  char n[2];
  memcpy(n, &t, 2 );
  gdcm::ByteSwap<uint16_t>::SwapRangeFromSwapCodeIntoSystem((uint16_t*)n, sc, 1);
  uint16_t tn = *((uint16_t*)n);
  //std::cout << std::hex << "tn: " << tn << std::endl;
  if( sc == gdcm::SC::BigEndian )
    {
    if( tn != 0x3412 )
      return 1;
    }
  else if ( sc == gdcm::SC::LittleEndian )
    {
    if( tn != 0x1234 )
      return 1;
    }
  gdcm::ByteSwap<uint16_t>::SwapRangeFromSwapCodeIntoSystem((uint16_t*)n, gdcm::SC::BigEndian, 1);
  tn = *((uint16_t*)n);
  //std::cout << std::hex << "tn: " << tn << std::endl;
  if( sc == gdcm::SC::LittleEndian )
    {
    if( tn != 0x3412 )
      return 1;
    }
  else if ( sc == gdcm::SC::BigEndian )
    {
    if( tn != 0x1234 )
      return 1;
    }

  if( myfunc() )
    return 1;

  return 0;
}
