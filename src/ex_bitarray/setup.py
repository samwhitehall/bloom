from distutils.core import setup, Extension

setup(
    name="bitarray",
    version="0.9",
    description="Optimised binary array datatype using C",
    author="Sam Whitehall",
    author_email="me@samwhitehall.com",
    url="http://www.samwhitehall.com",
    ext_modules = [
        Extension("bitarray", sources=["pybitarray.c", "bitarray_compressed.c"]),
        ],
    )
