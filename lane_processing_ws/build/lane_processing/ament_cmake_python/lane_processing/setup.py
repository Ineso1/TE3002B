from setuptools import find_packages
from setuptools import setup

setup(
    name='lane_processing',
    version='0.0.0',
    packages=find_packages(
        include=('lane_processing', 'lane_processing.*')),
)
