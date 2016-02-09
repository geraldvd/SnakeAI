if(WITH_QT)
    # Add subdirectories
    # E.g: 
    #    add_subdirectory(widgets)
    #    INCLUDE_DIRECTORIES(widgets)


    # Specify source files
    set(gui_SRCS
	# E.g.:
        #    mainwindow.cpp
    )

    # For Ubuntu/gcc - automoc is not working
    qt5_wrap_ui(gui_ui_moc
        # E.g.:
        #    mainwindow.ui
    )

    add_library(${PROJECT_NAME}_gui ${gui_SRCS} ${gui_hdr_moc} ${gui_ui_moc})
    target_link_libraries(${PROJECT_NAME}_gui ${QT_LIBS})
endif(WITH_QT)
