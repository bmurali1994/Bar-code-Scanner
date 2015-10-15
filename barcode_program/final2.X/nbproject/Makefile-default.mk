#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/final2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/final2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Demonstration.o ${OBJECTDIR}/ELB_I2C.o ${OBJECTDIR}/_ext/1964663391/ELB_ISR.o ${OBJECTDIR}/ELB_LCD.o ${OBJECTDIR}/ELB_OSC.o ${OBJECTDIR}/ELB_PWM.o ${OBJECTDIR}/ELB_Timer.o ${OBJECTDIR}/ELB_UART.o ${OBJECTDIR}/ELBv21_HardwareConfig.o ${OBJECTDIR}/FSIO.o ${OBJECTDIR}/SD-SPI.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Demonstration.o.d ${OBJECTDIR}/ELB_I2C.o.d ${OBJECTDIR}/_ext/1964663391/ELB_ISR.o.d ${OBJECTDIR}/ELB_LCD.o.d ${OBJECTDIR}/ELB_OSC.o.d ${OBJECTDIR}/ELB_PWM.o.d ${OBJECTDIR}/ELB_Timer.o.d ${OBJECTDIR}/ELB_UART.o.d ${OBJECTDIR}/ELBv21_HardwareConfig.o.d ${OBJECTDIR}/FSIO.o.d ${OBJECTDIR}/SD-SPI.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Demonstration.o ${OBJECTDIR}/ELB_I2C.o ${OBJECTDIR}/_ext/1964663391/ELB_ISR.o ${OBJECTDIR}/ELB_LCD.o ${OBJECTDIR}/ELB_OSC.o ${OBJECTDIR}/ELB_PWM.o ${OBJECTDIR}/ELB_Timer.o ${OBJECTDIR}/ELB_UART.o ${OBJECTDIR}/ELBv21_HardwareConfig.o ${OBJECTDIR}/FSIO.o ${OBJECTDIR}/SD-SPI.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/final2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ256GB206
MP_LINKER_FILE_OPTION=,-Tp24FJ256GB206.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/Demonstration.o: Demonstration.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Demonstration.o.d 
	@${RM} ${OBJECTDIR}/Demonstration.o.ok ${OBJECTDIR}/Demonstration.o.err 
	@${FIXDEPS} "${OBJECTDIR}/Demonstration.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Demonstration.o.d" -o ${OBJECTDIR}/Demonstration.o Demonstration.c    
	
${OBJECTDIR}/ELB_I2C.o: ELB_I2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/ELB_I2C.o.d 
	@${RM} ${OBJECTDIR}/ELB_I2C.o.ok ${OBJECTDIR}/ELB_I2C.o.err 
	@${FIXDEPS} "${OBJECTDIR}/ELB_I2C.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ELB_I2C.o.d" -o ${OBJECTDIR}/ELB_I2C.o ELB_I2C.c    
	
${OBJECTDIR}/_ext/1964663391/ELB_ISR.o: ../../Desktop/Brigosha\ Embeded\ Learning\ kit\ Application\ &\ Manual/Brigosha\ Embeded\ Learning\ kit\ Manual/ELB_SampleProjLibrary_v0.1/ELBproj_Hardware.X/ELB_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1964663391 
	@${RM} ${OBJECTDIR}/_ext/1964663391/ELB_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/1964663391/ELB_ISR.o.ok ${OBJECTDIR}/_ext/1964663391/ELB_ISR.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1964663391/ELB_ISR.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1964663391/ELB_ISR.o.d" -o ${OBJECTDIR}/_ext/1964663391/ELB_ISR.o "../../Desktop/Brigosha Embeded Learning kit Application & Manual/Brigosha Embeded Learning kit Manual/ELB_SampleProjLibrary_v0.1/ELBproj_Hardware.X/ELB_ISR.c"    
	
${OBJECTDIR}/ELB_LCD.o: ELB_LCD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/ELB_LCD.o.d 
	@${RM} ${OBJECTDIR}/ELB_LCD.o.ok ${OBJECTDIR}/ELB_LCD.o.err 
	@${FIXDEPS} "${OBJECTDIR}/ELB_LCD.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ELB_LCD.o.d" -o ${OBJECTDIR}/ELB_LCD.o ELB_LCD.c    
	
${OBJECTDIR}/ELB_OSC.o: ELB_OSC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/ELB_OSC.o.d 
	@${RM} ${OBJECTDIR}/ELB_OSC.o.ok ${OBJECTDIR}/ELB_OSC.o.err 
	@${FIXDEPS} "${OBJECTDIR}/ELB_OSC.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ELB_OSC.o.d" -o ${OBJECTDIR}/ELB_OSC.o ELB_OSC.c    
	
${OBJECTDIR}/ELB_PWM.o: ELB_PWM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/ELB_PWM.o.d 
	@${RM} ${OBJECTDIR}/ELB_PWM.o.ok ${OBJECTDIR}/ELB_PWM.o.err 
	@${FIXDEPS} "${OBJECTDIR}/ELB_PWM.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ELB_PWM.o.d" -o ${OBJECTDIR}/ELB_PWM.o ELB_PWM.c    
	
${OBJECTDIR}/ELB_Timer.o: ELB_Timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/ELB_Timer.o.d 
	@${RM} ${OBJECTDIR}/ELB_Timer.o.ok ${OBJECTDIR}/ELB_Timer.o.err 
	@${FIXDEPS} "${OBJECTDIR}/ELB_Timer.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ELB_Timer.o.d" -o ${OBJECTDIR}/ELB_Timer.o ELB_Timer.c    
	
${OBJECTDIR}/ELB_UART.o: ELB_UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/ELB_UART.o.d 
	@${RM} ${OBJECTDIR}/ELB_UART.o.ok ${OBJECTDIR}/ELB_UART.o.err 
	@${FIXDEPS} "${OBJECTDIR}/ELB_UART.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ELB_UART.o.d" -o ${OBJECTDIR}/ELB_UART.o ELB_UART.c    
	
${OBJECTDIR}/ELBv21_HardwareConfig.o: ELBv21_HardwareConfig.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/ELBv21_HardwareConfig.o.d 
	@${RM} ${OBJECTDIR}/ELBv21_HardwareConfig.o.ok ${OBJECTDIR}/ELBv21_HardwareConfig.o.err 
	@${FIXDEPS} "${OBJECTDIR}/ELBv21_HardwareConfig.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ELBv21_HardwareConfig.o.d" -o ${OBJECTDIR}/ELBv21_HardwareConfig.o ELBv21_HardwareConfig.c    
	
${OBJECTDIR}/FSIO.o: FSIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/FSIO.o.d 
	@${RM} ${OBJECTDIR}/FSIO.o.ok ${OBJECTDIR}/FSIO.o.err 
	@${FIXDEPS} "${OBJECTDIR}/FSIO.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/FSIO.o.d" -o ${OBJECTDIR}/FSIO.o FSIO.c    
	
${OBJECTDIR}/SD-SPI.o: SD-SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/SD-SPI.o.d 
	@${RM} ${OBJECTDIR}/SD-SPI.o.ok ${OBJECTDIR}/SD-SPI.o.err 
	@${FIXDEPS} "${OBJECTDIR}/SD-SPI.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/SD-SPI.o.d" -o ${OBJECTDIR}/SD-SPI.o SD-SPI.c    
	
else
${OBJECTDIR}/Demonstration.o: Demonstration.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Demonstration.o.d 
	@${RM} ${OBJECTDIR}/Demonstration.o.ok ${OBJECTDIR}/Demonstration.o.err 
	@${FIXDEPS} "${OBJECTDIR}/Demonstration.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Demonstration.o.d" -o ${OBJECTDIR}/Demonstration.o Demonstration.c    
	
${OBJECTDIR}/ELB_I2C.o: ELB_I2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/ELB_I2C.o.d 
	@${RM} ${OBJECTDIR}/ELB_I2C.o.ok ${OBJECTDIR}/ELB_I2C.o.err 
	@${FIXDEPS} "${OBJECTDIR}/ELB_I2C.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ELB_I2C.o.d" -o ${OBJECTDIR}/ELB_I2C.o ELB_I2C.c    
	
${OBJECTDIR}/_ext/1964663391/ELB_ISR.o: ../../Desktop/Brigosha\ Embeded\ Learning\ kit\ Application\ &\ Manual/Brigosha\ Embeded\ Learning\ kit\ Manual/ELB_SampleProjLibrary_v0.1/ELBproj_Hardware.X/ELB_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1964663391 
	@${RM} ${OBJECTDIR}/_ext/1964663391/ELB_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/1964663391/ELB_ISR.o.ok ${OBJECTDIR}/_ext/1964663391/ELB_ISR.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1964663391/ELB_ISR.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1964663391/ELB_ISR.o.d" -o ${OBJECTDIR}/_ext/1964663391/ELB_ISR.o "../../Desktop/Brigosha Embeded Learning kit Application & Manual/Brigosha Embeded Learning kit Manual/ELB_SampleProjLibrary_v0.1/ELBproj_Hardware.X/ELB_ISR.c"    
	
${OBJECTDIR}/ELB_LCD.o: ELB_LCD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/ELB_LCD.o.d 
	@${RM} ${OBJECTDIR}/ELB_LCD.o.ok ${OBJECTDIR}/ELB_LCD.o.err 
	@${FIXDEPS} "${OBJECTDIR}/ELB_LCD.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ELB_LCD.o.d" -o ${OBJECTDIR}/ELB_LCD.o ELB_LCD.c    
	
${OBJECTDIR}/ELB_OSC.o: ELB_OSC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/ELB_OSC.o.d 
	@${RM} ${OBJECTDIR}/ELB_OSC.o.ok ${OBJECTDIR}/ELB_OSC.o.err 
	@${FIXDEPS} "${OBJECTDIR}/ELB_OSC.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ELB_OSC.o.d" -o ${OBJECTDIR}/ELB_OSC.o ELB_OSC.c    
	
${OBJECTDIR}/ELB_PWM.o: ELB_PWM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/ELB_PWM.o.d 
	@${RM} ${OBJECTDIR}/ELB_PWM.o.ok ${OBJECTDIR}/ELB_PWM.o.err 
	@${FIXDEPS} "${OBJECTDIR}/ELB_PWM.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ELB_PWM.o.d" -o ${OBJECTDIR}/ELB_PWM.o ELB_PWM.c    
	
${OBJECTDIR}/ELB_Timer.o: ELB_Timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/ELB_Timer.o.d 
	@${RM} ${OBJECTDIR}/ELB_Timer.o.ok ${OBJECTDIR}/ELB_Timer.o.err 
	@${FIXDEPS} "${OBJECTDIR}/ELB_Timer.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ELB_Timer.o.d" -o ${OBJECTDIR}/ELB_Timer.o ELB_Timer.c    
	
${OBJECTDIR}/ELB_UART.o: ELB_UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/ELB_UART.o.d 
	@${RM} ${OBJECTDIR}/ELB_UART.o.ok ${OBJECTDIR}/ELB_UART.o.err 
	@${FIXDEPS} "${OBJECTDIR}/ELB_UART.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ELB_UART.o.d" -o ${OBJECTDIR}/ELB_UART.o ELB_UART.c    
	
${OBJECTDIR}/ELBv21_HardwareConfig.o: ELBv21_HardwareConfig.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/ELBv21_HardwareConfig.o.d 
	@${RM} ${OBJECTDIR}/ELBv21_HardwareConfig.o.ok ${OBJECTDIR}/ELBv21_HardwareConfig.o.err 
	@${FIXDEPS} "${OBJECTDIR}/ELBv21_HardwareConfig.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ELBv21_HardwareConfig.o.d" -o ${OBJECTDIR}/ELBv21_HardwareConfig.o ELBv21_HardwareConfig.c    
	
${OBJECTDIR}/FSIO.o: FSIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/FSIO.o.d 
	@${RM} ${OBJECTDIR}/FSIO.o.ok ${OBJECTDIR}/FSIO.o.err 
	@${FIXDEPS} "${OBJECTDIR}/FSIO.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/FSIO.o.d" -o ${OBJECTDIR}/FSIO.o FSIO.c    
	
${OBJECTDIR}/SD-SPI.o: SD-SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/SD-SPI.o.d 
	@${RM} ${OBJECTDIR}/SD-SPI.o.ok ${OBJECTDIR}/SD-SPI.o.err 
	@${FIXDEPS} "${OBJECTDIR}/SD-SPI.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/SD-SPI.o.d" -o ${OBJECTDIR}/SD-SPI.o SD-SPI.c    
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/final2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -o dist/${CND_CONF}/${IMAGE_TYPE}/final2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1
else
dist/${CND_CONF}/${IMAGE_TYPE}/final2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/final2.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}\\pic30-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/final2.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -omf=elf
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
