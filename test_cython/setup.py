from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext

ext_modules = [Extension("test",
                     ["Test.pyx"],
                     language='c++',
                     inclide_dirs=['/home/ubuntu/survision\ soft/CDK_x64/1.0.3.0/include'],
                     extra_objects=["libcdk64.so"],
                     )]

setup(
  name = 'test',
  cmdclass = {'build_ext': build_ext},
  ext_modules = ext_modules
)
