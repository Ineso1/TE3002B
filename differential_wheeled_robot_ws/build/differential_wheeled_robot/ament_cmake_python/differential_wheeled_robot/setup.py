from setuptools import find_packages
from setuptools import setup

setup(
    name='differential_wheeled_robot',
    version='0.0.0',
    packages=find_packages(
        include=('differential_wheeled_robot', 'differential_wheeled_robot.*')),
)
