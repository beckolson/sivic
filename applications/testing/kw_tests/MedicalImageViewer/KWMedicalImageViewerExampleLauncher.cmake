set(ENV{PATH} "/netopt/lib/vtk-5.2:/netopt/lib/vtk-5.2:/netopt/lib/KWWidgets:/netopt/lib/KWWidgets:/usr/bin:/usr/bin:$ENV{PATH}")
set(ENV{LD_LIBRARY_PATH} "/netopt/lib/vtk-5.2:/netopt/lib/KWWidgets:$ENV{LD_LIBRARY_PATH}")
set(ENV{TCLLIBPATH} " {/netopt/lib/vtk-5.2} {/netopt/lib/KWWidgets/tcl} $ENV{TCLLIBPATH}")
set(ENV{PYTHONPATH} "/netopt/lib/vtk-5.2/../python2.4/site-packages:/netopt/lib/vtk-5.2:/netopt/lib/KWWidgets/../python2.4/site-packages:/netopt/lib/KWWidgets/../python2.4/site-packages:/netopt/lib/KWWidgets:$ENV{PYTHONPATH}")
if("0" STREQUAL "1")
  set(ENV{ITCL_LIBRARY} "")
  set(ENV{ITK_LIBRARY} "")
endif("0" STREQUAL "1")
