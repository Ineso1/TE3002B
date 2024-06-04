from setuptools import find_packages
from setuptools import setup

setup(
    name='puzzle_pkg',
    version='0.0.0',
    packages=find_packages(
        include=('puzzle_pkg', 'puzzle_pkg.*')),
)
