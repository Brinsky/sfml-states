# SConscript file
# Effectively the contents of a normal Sconstruct file -- allows the use of VarientDir for changing the build output directory

# Basic SConstruct file for use with SFML and a simple project/folder structure

execName = 'sfml-states'

libList = [ 'sfml-window','sfml-system','sfml-graphics' ]

env = Environment( CPPPATH = [ './include', '/usr/include' ] )

# The "'../' + " before the target name is used to keep the executable in the top level of the project folder
# Remove it in order to keep the executable in the variant_dir
env.Program( target = '../' + execName , source = Glob( 'src/*.cpp' ), LIBS = libList, LIBPATH = '/usr/lib', CXXFLAGS = "-std=c++11" )
