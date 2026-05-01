from setuptools import setup

package_name = 'startup'

setup(
    name=package_name,
    version='0.0.1',
    packages=[],
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        ('share/' + package_name + '/launch', ['launch/all_nodes.py']),
    ],
    zip_safe=True,
    maintainer='Arthur Alves',
    maintainer_email='arthurarg1@gmail.com',
    description='This package launch all nodes',
    license='MIT',
    entry_points={
        'console_scripts': [],
    },
)
