from setuptools import setup, find_packages

setup(
    name='tokenicer',
    version='0.1.0',
    description='A Python package that wraps a C tokenizer library using ctypes',
    packages=['tokenicer'],
    package_dir={'tokenicer': 'src/tokenicer'},
    package_data={
        # Include all .so files in the tokenicer package
        'tokenicer': ['*.so'],
    },
    include_package_data=True,
)
