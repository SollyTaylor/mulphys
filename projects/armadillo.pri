win32: {
INCLUDEPATH += \
        $$(MULPHYS_ROOT)/3rd/armadillo-9.200.7/include
}

unix: !macx: {
#    DEFINES += ARMA_64BIT_WORD
INCLUDEPATH += \
        $$(MULPHYS_ROOT)/3rd/armadillo-9.200.7/include
}

macx: {
#    DEFINES += ARMA_64BIT_WORD
INCLUDEPATH += \
        $$(MULPHYS_ROOT)/3rd/armadillo-9.200.7/include
}
