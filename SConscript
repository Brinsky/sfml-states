# SConscript file
# Effectively the contents of a normal Sconstruct file -- allows the use of VarientDir for changing the build output directory

execName = 'sfml-states'
libName = 'sfml-state-man'

libSrc = Glob('src/StateManager/*.cpp')
mainSrc = Glob('src/*.cpp')

includeDirs = ['./include', './include/StateManager', '/usr/include']

env = Environment(CPPPATH = includeDirs,
                  LIBPATH = '/usr/lib',
                  LIBS = ['sfml-window', 'sfml-system', 'sfml-graphics'],
                  CXXFLAGS = "-std=c++11")

env.Program(target = '../' + execName , source = [mainSrc, libSrc])
env.StaticLibrary(target = '../' + libName, source = libSrc)

