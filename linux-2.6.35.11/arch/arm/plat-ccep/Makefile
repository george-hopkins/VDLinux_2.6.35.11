obj-y				:= sdp_hwmem.o sdp_mem.o #sdp_hba.o
ifeq ($(CONFIG_ARM_GIC),y)
else
ifeq ($(CONFIG_SDP_INTC64),y)
obj-y				+= sdp_irq64.o
else
obj-y				+= sdp_irq.o
endif
endif
obj-$(CONFIG_SDP_TICK_TIMER)	+= sdp_timer.o
obj-$(CONFIG_SDP_HR_TIMER)	+= sdp_hrtimer.o
obj-$(CONFIG_SDP_TICK_TIMER64)	+= sdp_timer64.o
obj-$(CONFIG_SDP_HR_TIMER64)	+= sdp_hrtimer64.o
obj-$(CONFIG_SDP_GPIO)		+= sdp_gpio.o

ifneq ($(CONFIG_ARCH_SDP1004),y)
ifneq ($(CONFIG_ARCH_SDP1002),y)
ifneq ($(CONFIG_ARCH_SDP1001),y)
obj-$(CONFIG_SDP_I2C)		+= sdp_i2c.o
else # SDP1001
obj-$(CONFIG_SDP_I2C)		+= sdp_i2c_m.o
endif
else # SDP1002
obj-$(CONFIG_SDP_I2C)		+= sdp_i2c_m.o
endif
else # SDP1004
obj-$(CONFIG_SDP_I2C)		+= sdp_i2c_f.o
endif

#UART
#obj-$(CONFIG_SERIAL_SDP) 	+= serial_sdp.o 
obj-$(CONFIG_SERIAL_SDP) 	+= sdp_uart.o 

#Ethernet
obj-$(CONFIG_SDP_MAC)		+= sdp_mac.o

#PCI
obj-$(CONFIG_SDP_PCI)		+= pci.o sdp_pci.o 
obj-$(CONFIG_SDP_PCIE)		+= pcie.o sdp_pcie.o 
obj-$(CONFIG_SDP_PCIE_EP)	+= sdp_pcie_ep.o 

#SATA
#obj-$(CONFIG_SDP_SATA)		+= sdpSata/

#MMC
obj-$(CONFIG_SDP_MMC)		+= sdp_mmc.o

#SMC
obj-$(CONFIG_SDP_SMC)		+= sdp_smc.o
