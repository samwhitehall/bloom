An implementation of a Bloom filter in Python with a C-backend binary array.
Developed for my own amusement and education, but feel free to use it/fix bugs.

# Theory

The Bloom filter is an interesting data structure, used for very time- and
space-efficient set membership tests, if you don't mind a small number of false
positives. This is achieved by finding _k_ hash values for the element (from
_k_ different hash functions) and setting the values indexed by these values in
a large binary array to "1". Membership is tested by checking the array at the
indexes from the element's hash values: they will all be "1" if (but not only
if) the element is in the set.

They're often used in big-data-y things to reduce the number of disk lookups
for non-existent rows in a database. 


# Installation

`python setup.py install` should work. Verify installation worked 
by executing `test/bloom_test.py`.

# Usage 

`bloom` contains two bloom filter classes. `BloomFilter` can be used by
supplying the size of the bit-array, _m_. A larger _m_ means fewer false
positives, but obviously uses more memory. The tradeoff can be determined
experimentally, or calculated for an [average false positive
rate](http://en.wikipedia.org/wiki/Bloom_filter#Probability_of_false_positives).

A collection of _k_ hash functions (some iterable containing function objects
that return some hash of a single argument) also needs to be provided.
`CryptHashBloomFilter` generates these automatically by skimming bits from 
Python's cryptographic hash functions. I have no idea if these are optimal (I
haven't done large testing or anything), so assume it's not. There's probably
a limit that I'm not checking, too.
