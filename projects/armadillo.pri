win32: {
INCLUDEPATH += \
        $$(MULPHYS_ROOT)/3rd/armadillo-9.100-RC2/include
}

unix: !macx: {
#    DEFINES += ARMA_64BIT_WORD
INCLUDEPATH += \
        $$(MULPHYS_ROOT)/3rd/armadillo-9.100-RC2/include
}

macx: {
#    DEFINES += ARMA_64BIT_WORD
INCLUDEPATH += \
        $$(MULPHYS_ROOT)/3rd/armadillo-9.100-RC2/include
}
