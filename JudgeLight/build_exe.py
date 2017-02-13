#coding=utf-8
from cx_Freeze import setup, Executable
import sys
import os
os.chdir(os.path.split(sys.argv[0])[0])
if len(sys.argv)==1:
    sys.argv.append('build')

options = {
  'build_exe' : {
    'includes' : ['html5lib'],
    'packages' : ['bs4'],
  }
}

setup(name='JudgeLight',
    version='1.0',
    description='Judgelight by @xmcp',
    options=options,
    executables=[Executable("judgelight.pyw",base='Win32GUI')])
