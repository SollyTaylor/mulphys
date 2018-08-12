INCLUDEPATH += $$(MULPHYS_ROOT)/mulphys/kernel
win32:CONFIG(release, debug|release): LIBS += -L$$(MULPHYS_ROOT)/lib/Release/ -lmulphys_kernel_win_x64
else:win32:CONFIG(debug, debug|release): LIBS += -L$$(MULPHYS_ROOT)/lib/Debug/ -lmulphys_kernel_win_x64
