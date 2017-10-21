#include <vector>
#include <cstdint>
#include <iterator>
#include <iostream>
#include <vector>


inline uint64_t nthHash (uint8_t n, uint64_t hashA, uint64_t hashB, uint64_t filterSize) {
	return (hashA + n * hashB) % filterSize;
}

//TODO pending to improve
//template <class Key, class Hash = std::hash<Key> >
struct BloomFilter {
	BloomFilter(uint64_t size, uint8_t numHashes);
	void add(const uint8_t *data, std::size_t len);
	bool possiblyContains(const uint8_t *data, std::size_t len) const;

	private:
		uint8_t n_numHashes;
		std::vector<bool> m_bits;

};
