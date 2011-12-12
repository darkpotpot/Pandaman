pyInc= '/usr/include/python2.6'
pandaInc= '/usr/include/panda3d'
pandaLib= '/usr/lib/panda3d'

Program(['main.cpp',
         'simu.cpp', 
         'entity.cpp', 
         'grid.cpp', 
         'cell.cpp', 
         'grid_display.cpp', 
         'tinyxml/tinyxml.cpp', 
         'tinyxml/tinystr.cpp', 
         'tinyxml/tinyxmlparser.cpp', 
         'tinyxml/tinyxmlerror.cpp'
         ],
	CCFLAGS=['-fPIC', '-O2'],
	CPPPATH=[pyInc, pandaInc],
	LIBPATH=pandaLib,
	LIBS=[	'libp3framework',
		'libpanda',
		'libpandafx',
		'libpandaexpress',
		'libp3dtoolconfig',
		'libp3dtool',
		'libp3pystub',
		'libp3direct'])
