# Begin_DVE_Session_Save_Info
# DVE full session
# Saved on Fri Sep 19 19:37:08 2014
# Designs open: 1
#   V1: /home/ss3912/eecs4340/examples/examples/adder32/vcdplus.vpd
# Toplevel windows open: 1
# 	TopLevel.1
#   Group count = 0
# End_DVE_Session_Save_Info

# DVE version: F-2011.12_Full64
# DVE build date: Nov 22 2011 20:55:00


#<Session mode="Full" path="/home/ss3912/eecs4340/examples/examples/adder32/DVEfiles/session.tcl" type="Debug">

gui_set_loading_session_type Post
gui_continuetime_set

# Close design
if { [gui_sim_state -check active] } {
    gui_sim_terminate
}
gui_close_db -all
gui_expr_clear_all

# Close all windows
gui_close_window -type Console
gui_close_window -type Wave
gui_close_window -type Source
gui_close_window -type Schematic
gui_close_window -type Data
gui_close_window -type DriverLoad
gui_close_window -type List
gui_close_window -type Memory
gui_close_window -type HSPane
gui_close_window -type DLPane
gui_close_window -type Assertion
gui_close_window -type CovHier
gui_close_window -type CoverageTable
gui_close_window -type CoverageMap
gui_close_window -type CovDetail
gui_close_window -type Local
gui_close_window -type Stack
gui_close_window -type Watch
gui_close_window -type Group
gui_close_window -type Transaction



# Application preferences
gui_set_pref_value -key app_default_font -value {Helvetica,10,-1,5,50,0,0,0,0,0}
gui_src_preferences -tabstop 8 -maxbits 24 -windownumber 1
#<WindowLayout>

# DVE Topleve session: 


# Create and position top-level windows :TopLevel.1

if {![gui_exist_window -window TopLevel.1]} {
    set TopLevel.1 [ gui_create_window -type TopLevel \
       -icon $::env(DVE)/auxx/gui/images/toolbars/dvewin.xpm] 
} else { 
    set TopLevel.1 TopLevel.1
}
gui_show_window -window ${TopLevel.1} -show_state normal -rect {{66 52} {784 760}}

# ToolBar settings

# End ToolBar settings

# Docked window settings
gui_sync_global -id ${TopLevel.1} -option true

gui_set_env TOPLEVELS::TARGET_FRAME(Source) 
gui_set_env TOPLEVELS::TARGET_FRAME(Schematic) 
gui_set_env TOPLEVELS::TARGET_FRAME(PathSchematic) 
gui_set_env TOPLEVELS::TARGET_FRAME(Wave) 
gui_set_env TOPLEVELS::TARGET_FRAME(List) 
gui_set_env TOPLEVELS::TARGET_FRAME(Memory) 
gui_set_env TOPLEVELS::TARGET_FRAME(DriverLoad) 
gui_update_statusbar_target_frame ${TopLevel.1}

#</WindowLayout>

#<Database>

# DVE Open design session: 

if { ![gui_is_db_opened -db {/home/ss3912/eecs4340/examples/examples/adder32/vcdplus.vpd}] } {
	gui_open_db -design V1 -file /home/ss3912/eecs4340/examples/examples/adder32/vcdplus.vpd -nosource
}
gui_set_precision 1s
gui_set_time_units 1s
#</Database>

# DVE Global setting session: 


# Global: Bus

# Global: Expressions

# Global: Signal Time Shift

# Global: Signal Compare

# Global: Signal Groups


# Global: Highlighting

# Post database loading setting...

# Restore C1 time
gui_set_time -C1_only 0



# Save global setting...

# Wave/List view global setting
gui_cov_show_value -switch false

# Close all empty TopLevel windows
foreach __top [gui_ekki_get_window_ids -type TopLevel] {
    if { [llength [gui_ekki_get_window_ids -parent $__top]] == 0} {
        gui_close_window -window $__top
    }
}
gui_set_loading_session_type noSession
# DVE View/pane content session: 

# Restore toplevel window zorder
# The toplevel window could be closed if it has no view/pane
if {[gui_exist_window -window ${TopLevel.1}]} {
	gui_set_active_window -window ${TopLevel.1}
}
#</Session>

