obj-$(CONFIG_DEBUG_VA_USER) += user.o

##
## Individual Compile with different architecture
INDIC_FLAGS :=

ifdef CONFIG_DEBUG_VA_USER_I386
INDIC_FLAGS += gcc -m32 -DCONFIG_DEBUG_VA_USER_I386
endif

ifdef CONFIG_DEBUG_VA_USER_IA64
INDIC_FLAGS += gcc -DCONFIG_DEBUG_VA_USER_IA64
endif

ifdef CONFIG_DEBUG_VA_USER_DATA_GNINIT
INDIC_FLAGS += -DCONFIG_DEBUG_VA_USER_DATA_GNINIT
endif

ifdef CONFIG_DEBUG_VA_USER_DATA_GINITZERO
INDIC_FLAGS += -DCONFIG_DEBUG_VA_USER_DATA_GINITZERO
endif

ifdef CONFIG_DEBUG_VA_USER_DATA_GINITNZERO
INDIC_FLAGS += -DCONFIG_DEBUG_VA_USER_DATA_GINITNZERO
endif

ifdef CONFIG_DEBUG_VA_USER_DATA_SNINIT
INDIC_FLAGS += -DCONFIG_DEBUG_VA_USER_DATA_SNINIT
endif

ifdef CONFIG_DEBUG_VA_USER_DATA_SINITZERO
INDIC_FLAGS += -DCONFIG_DEBUG_VA_USER_DATA_SINITZERO
endif

ifdef CONFIG_DEBUG_VA_USER_DATA_SINITNZERO
INDIC_FLAGS += -DCONFIG_DEBUG_VA_USER_DATA_SINITNZERO
endif

ifdef CONFIG_DEBUG_VA_USER_DATA_LSNINIT
INDIC_FLAGS += -DCONFIG_DEBUG_VA_USER_DATA_LSNINIT
endif

ifdef CONFIG_DEBUG_VA_USER_DATA_LSINITZERO
INDIC_FLAGS += -DCONFIG_DEBUG_VA_USER_DATA_LSINITZERO
endif

ifdef CONFIG_DEBUG_VA_USER_DATA_LSINITNZERO
INDIC_FLAGS += -DCONFIG_DEBUG_VA_USER_DATA_LSINITNZERO
endif

ifdef CONFIG_DEBUG_VA_USER_DATA_LNINIT
INDIC_FLAGS += -DCONFIG_DEBUG_VA_USER_DATA_LNINIT
endif

ifdef CONFIG_DEBUG_VA_USER_DATA_LINITZERO
INDIC_FLAGS += -DCONFIG_DEBUG_VA_USER_DATA_LINITZERO
endif

ifdef CONFIG_DEBUG_VA_USER_DATA_LINITNZERO
INDIC_FLAGS += -DCONFIG_DEBUG_VA_USER_DATA_LINITNZERO
endif

ifdef CONFIG_DEBUG_VA_USER_DATA_HEAP
INDIC_FLAGS += -DCONFIG_DEBUG_VA_USER_DATA_HEAP
endif

ifdef CONFIG_DEBUG_VA_USER_DATA_MMAP
INDIC_FLAGS += -DCONFIG_DEBUG_VA_USER_DATA_MMAP
endif

ifdef CONFIG_DEBUG_VA_USER_DATA_CONST
INDIC_FLAGS += -DCONFIG_DEBUG_VA_USER_DATA_CONST
endif

## BBS not on COMMON 
INDIC_FLAGS += -fno-common

DO_HERE     :=$(shell $(obj)/do.sh $(INDIC_FLAGS))
$(info " SH      tools/demo/mmu/addressing/virtual_address/data/user$(DO_HERE)")
