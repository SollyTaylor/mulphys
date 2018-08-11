INCLUDEPATH += $$(PANAX_ROOT)/panax/kernel
win32:CONFIG(release, debug|release): LIBS += -L$$(PANAX_ROOT)/lib/Release/ -lpanax_kernel_win_x64
else:win32:CONFIG(debug, debug|release): LIBS += -L$$(PANAX_ROOT)/lib/Debug/ -lpanax_kernel_win_x64
