#include "bloom_filter.h"
#include "murmurhash3/MurmurHash3.h"
#include <functional>
#include <iterator>

BloomFilter::BloomFilter(uint64_t size, uint8_t numHashes) : m_bits(size), n_numHashes(numHashes) {}

std::array<uint64_t, 2> hash(const uint8_t *data, std::size_t len) {
	std::array<uint64_t, 2> hashValue;
	MurmurHash3_x64_128(data,len,0,hashValue.data());
	return hashValue;
}

void BloomFilter::add(const uint8_t *data, std::size_t len) {
	auto hashValues = hash(data,len);

	for (int n=0; n<n_numHashes; n++) {
		m_bits[nthHash(n,hashValues[0],hashValues[1],m_bits.size())] = true;
	}
}

bool BloomFilter::possiblyContains(const uint8_t *data, std::size_t len) const {
	auto hashValues = hash(data,len);

	for (int n = 0; n < n_numHashes; n++) {
		if (!m_bits[nthHash(n,hashValues[0],hashValues[1],m_bits.size())]) {
			return false;
		}

	}
	return true;
}



