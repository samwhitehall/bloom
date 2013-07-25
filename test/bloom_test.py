import bloom
import unittest, random, string
from bloom import CryptHashBloomFilter

class AddElementsToBloomFilter(unittest.TestCase):
    def setUp(self):
        self.bf = CryptHashBloomFilter(10000, 5)        
        self.added = set()

    def testRecall(self):
        for i in xrange(1000):
            random_string = "".join(random.choice(string.ascii_letters) 
                for n in xrange(30))
            self.added.add(random_string)
            self.bf.add(random_string)
            self.assertIn(random_string, self.bf) 

if __name__ == '__main__':
    unittest.main()
