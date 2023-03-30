 #pragma once
#include "basicTypes.h"
#include "ClassMacros.h"
#include "ItemAddress.h"
#include "RawArray.h"
#include "showMessage.h"
#include "StandardIntegralTypes.h"
namespace tecplot { namespace ___3933 { class CszConnectivity { UNCOPYABLE_CLASS(CszConnectivity) public: typedef uint16_t EntryIndex_t; CszConnectivity() : m_ptr(NULL) {} ~CszConnectivity() { ___937(); } static size_t bytesRequired(uint32_t ___2795, uint32_t numRefNszs); bool empty() const { return m_ptr == NULL; } bool alloc(uint32_t ___2795, uint32_t numRefNszs); size_t numBytesAllocated(void) const; void ___937(); uint32_t getNumEntries() const; uint32_t getNumRefNszs() const; uint8_t* getItemOffsetArray(); uint8_t const* getItemOffsetArray() const; uint16_t* getRszOffsetArray(); uint16_t const * getRszOffsetArray() const; ___2090::SubzoneAddress* getRefNszArray(); ___2090::SubzoneAddress const* getRefNszArray() const; bool getRszAddresses(___3269<___2090::SubzoneAddress>& rszAddresses) const; ___2090::SubzoneAddress getRszAddress(RefSubzoneOffset_t rszOffset) const; RefSubzoneOffset_t getRszOffset(EntryIndex_t entry) const; uint8_t getNodeOffset(EntryIndex_t entry) const; ___2090 getNodeAddress(EntryIndex_t entry) const; private: uint8_t* m_ptr; static uint16_t const MAX_NUM_ENTRIES = 2048; static size_t const POS_NUMENTRIES = 0; static size_t const POS_NUMREFNSZS = POS_NUMENTRIES + sizeof(uint32_t); static size_t const POS_OFFSETARRAY = POS_NUMREFNSZS + sizeof(uint32_t); static size_t const POS_RSZINDEXARRAY = POS_OFFSETARRAY + MAX_NUM_ENTRIES*sizeof(uint8_t); static size_t const POS_REFNSZARRAY = POS_RSZINDEXARRAY + MAX_NUM_ENTRIES*sizeof(uint16_t); }; inline size_t CszConnectivity::bytesRequired( uint32_t ___2795, uint32_t numRefNszs) { ___4278(___2795); size_t const bytes = POS_REFNSZARRAY + numRefNszs*sizeof(uint64_t); return bytes; } inline bool CszConnectivity::alloc( uint32_t ___2795, uint32_t numRefNszs) { REQUIRE(empty()); REQUIRE(___2795 > 0 && ___2795 <= MAX_NUM_ENTRIES); REQUIRE(numRefNszs > 0 && numRefNszs <= ___2795); size_t const bytes = bytesRequired(___2795, numRefNszs); m_ptr = (uint8_t*)malloc(bytes); if (m_ptr) { *((uint32_t*)(m_ptr + POS_NUMENTRIES)) = ___2795; *((uint32_t*)(m_ptr + POS_NUMREFNSZS)) = numRefNszs; } return m_ptr != NULL; } inline size_t CszConnectivity::numBytesAllocated(void) const { if (empty()) return 0; else { uint32_t const ___2795 = getNumEntries(); uint32_t const numRefNszs = getNumRefNszs(); size_t const bytes = bytesRequired(___2795, numRefNszs); return bytes; } } inline void CszConnectivity::___937() { if (!empty()) { free(m_ptr); m_ptr = 0; } ENSURE(empty()); } inline uint32_t CszConnectivity::getNumEntries() const { REQUIRE(!empty()); uint32_t const ___2795 = *((uint32_t*)(m_ptr + POS_NUMENTRIES)); ENSURE(___2795 > 0 && ___2795 <= MAX_NUM_ENTRIES); return ___2795; } inline uint32_t CszConnectivity::getNumRefNszs() const { REQUIRE(!empty()); uint32_t const numRefNszs = *((uint32_t*)(m_ptr + POS_NUMREFNSZS)); ENSURE(numRefNszs > 0 && numRefNszs <= getNumEntries()); return numRefNszs; } inline uint8_t* CszConnectivity::getItemOffsetArray() { REQUIRE(!empty()); return ((uint8_t*)(m_ptr + POS_OFFSETARRAY)); } inline uint8_t const* CszConnectivity::getItemOffsetArray() const { REQUIRE(!empty()); return ((uint8_t*)(m_ptr + POS_OFFSETARRAY)); } inline uint16_t* CszConnectivity::getRszOffsetArray() { REQUIRE(!empty()); return ((uint16_t*)(m_ptr + POS_RSZINDEXARRAY)); } inline uint16_t const* CszConnectivity::getRszOffsetArray() const { REQUIRE(!empty()); return ((uint16_t*)(m_ptr + POS_RSZINDEXARRAY)); } inline ___2090::SubzoneAddress* CszConnectivity::getRefNszArray() { REQUIRE(!empty()); INVARIANT(sizeof(___2090::SubzoneAddress) == sizeof(uint64_t)); return ((___2090::SubzoneAddress*)(m_ptr + POS_REFNSZARRAY)); } inline ___2090::SubzoneAddress const* CszConnectivity::getRefNszArray() const { REQUIRE(!empty()); INVARIANT(sizeof(___2090::SubzoneAddress) == sizeof(uint64_t)); return ((___2090::SubzoneAddress*)(m_ptr + POS_REFNSZARRAY)); } inline bool CszConnectivity::getRszAddresses(___3269<___2090::SubzoneAddress>& rszAddresses) const { REQUIRE(!empty()); REQUIRE(rszAddresses.empty()); bool ___2039 = ___4226; try { uint32_t const numRefNszs = getNumRefNszs(); ___478(numRefNszs > 0); rszAddresses.reserve(numRefNszs); rszAddresses.___3503(numRefNszs); ___2090::SubzoneAddress const* refNszArray = getRefNszArray(); memcpy(&rszAddresses[0], refNszArray, numRefNszs*sizeof(___2090::SubzoneAddress)); } catch (std::bad_alloc const&) { ___2039 = ___1186("Out of memory getRszAddresses"); } return ___2039; } inline ___2090::SubzoneAddress CszConnectivity::getRszAddress(RefSubzoneOffset_t rszOffset) const { REQUIRE(!empty()); REQUIRE(rszOffset < getNumRefNszs()); ___2090::SubzoneAddress const* refNszArray = getRefNszArray(); ___2090::SubzoneAddress const ___2757 = refNszArray[rszOffset]; return ___2757; } inline RefSubzoneOffset_t CszConnectivity::getRszOffset(EntryIndex_t entry) const { REQUIRE(!empty()); REQUIRE(entry < getNumEntries()); uint16_t const* rszOffsetArray = getRszOffsetArray();
uint16_t const  rszOffset = rszOffsetArray[entry]; ENSURE(rszOffset < getNumRefNszs()); return rszOffset; } inline uint8_t CszConnectivity::getNodeOffset(EntryIndex_t entry) const { REQUIRE(!empty()); REQUIRE(entry < getNumEntries()); uint8_t const* itemOffsetArray = getItemOffsetArray(); uint8_t const  itemOffset = itemOffsetArray[entry]; return itemOffset; } inline ___2090 CszConnectivity::getNodeAddress(EntryIndex_t entry) const { REQUIRE(!empty()); REQUIRE(entry < getNumEntries()); uint8_t const itemOffset = getNodeOffset(entry); uint16_t const rszOffset = getRszOffset(entry); ___2090::SubzoneAddress const nszAddress = getRszAddress(rszOffset); return ___2090(nszAddress, itemOffset); } }}