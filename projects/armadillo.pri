win32: {
INCLUDEPATH += \
        $$(MULPHYS_ROOT)/3rd/armadillo-8.600.0/include
}

unix: !macx: {
#    DEFINES += ARMA_64BIT_WORD
INCLUDEPATH += \
        $$(MULPHYS_ROOT)/3rd/armadillo-8.600.0/include
}

macx: {
#    DEFINES += ARMA_64BIT_WORD
INCLUDEPATH += \
        $$(MULPHYS_ROOT)/3rd/armadillo-8.600.0/include
}
