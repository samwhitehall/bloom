from distutils.core import setup

setup(
    name="swbloom",
    version="0.9",
    description="Basic Bloom Filter implementation",
    author="Sam Whitehall",
    author_email="me@samwhitehall.com",
    url="http://www.samwhitehall.com",
    packages=["bloom", "bloom.hashfunc"],
    package_dir={"bloom" : "src/bloom", 
                 "bloom.hashfunc" : "src/bloom/hashfunc"},
)
