import bitarray
from hashfunc import crypthash

class BloomFilter:
    """
    A Bloom Filter data structure. This is a very efficient way of testing set
    membership, provided you don't mind occasional false positives. The
    data structure is a binary array of size m, with some number of hash functions;
    h_1 ... h_n. For an element x, we consider all the indexes h_1(x) ... h_n(x).
    """
    def __init__(self, m, hash_functions):
        self.m = m
        self.bit_array = bitarray.BitArray(m)
        self.hash_functions = hash_functions

    def add(self, element):
        """Add 'element' to the filter."""
        array_positions = [hash_function(element) 
                            for hash_function in self.hash_functions]

        for i in array_positions:
            self.bit_array.set(i)

    def __contains__(self, element):
        """Determine whether 'element' is in the filter'. Overrides the
        'in' keyword"""
        array_positions = [hash_function(element) 
                            for hash_function in self.hash_functions]

        return all(self.bit_array.get(i) for i in array_positions)


class CryptHashBloomFilter(BloomFilter):
    """
    Bloom Filter of size m using k hash functions based on standard 
    cryptographic (SHA) hash functions. These will have minimal false 
    positives, but the overhead in calculating the hashes may be too high.
    """
    def __init__(self, m, k):
        hf = [crypthash.hash_function(i,m) for i in range(k)] 
        BloomFilter.__init__(self, m, hf)
