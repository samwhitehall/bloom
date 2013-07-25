import hashlib

def hash_function(k, m):
    """
    Return a ''clipped hash'' function, which will return a hash value
    between 0 and m (the size of the bit array), with a random salt value
    (to allow arbitrarily many quasi-independent hash functions).
    """
    def hash_of(element):
        hash_hex = hashlib.sha1(element+str(k)).hexdigest()
        return int(hash_hex,base=16) % m
    return hash_of # bound with k and m in args
