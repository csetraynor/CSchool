##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=UOCMoney
ConfigurationName      :=Release
WorkspacePath          := "C:\Users\Xavier\Desktop\Programacio\PR2\UOCMoney"
ProjectPath            := "C:\Users\Xavier\Desktop\Programacio\PR2\UOCMoney\UOCMoney"
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Xavier
Date                   :=02/11/2015
CodeLitePath           :="C:\Program Files\CodeLite"
LinkerName             :=C:/TDM-GCC-64/bin/g++.exe
SharedObjectLinkerName :=C:/TDM-GCC-64/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=../bin/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)NDEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="UOCMoney.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=C:/TDM-GCC-64/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/TDM-GCC-64/bin/ar.exe rcu
CXX      := C:/TDM-GCC-64/bin/g++.exe
CC       := C:/TDM-GCC-64/bin/gcc.exe
CXXFLAGS :=  -O2 -Wall $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/TDM-GCC-64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/src_main.c$(ObjectSuffix) $(IntermediateDirectory)/src_uocmoney.c$(ObjectSuffix) $(IntermediateDirectory)/src_movements.c$(ObjectSuffix) $(IntermediateDirectory)/src_test.c$(ObjectSuffix) $(IntermediateDirectory)/src_menu.c$(ObjectSuffix) $(IntermediateDirectory)/src_concepts.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Release"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Release"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_main.c$(ObjectSuffix): src/main.c $(IntermediateDirectory)/src_main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/Xavier/Desktop/Programacio/PR2/UOCMoney/UOCMoney/src/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_main.c$(DependSuffix): src/main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_main.c$(DependSuffix) -MM "src/main.c"

$(IntermediateDirectory)/src_main.c$(PreprocessSuffix): src/main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_main.c$(PreprocessSuffix) "src/main.c"

$(IntermediateDirectory)/src_uocmoney.c$(ObjectSuffix): src/uocmoney.c $(IntermediateDirectory)/src_uocmoney.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/Xavier/Desktop/Programacio/PR2/UOCMoney/UOCMoney/src/uocmoney.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_uocmoney.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_uocmoney.c$(DependSuffix): src/uocmoney.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_uocmoney.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_uocmoney.c$(DependSuffix) -MM "src/uocmoney.c"

$(IntermediateDirectory)/src_uocmoney.c$(PreprocessSuffix): src/uocmoney.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_uocmoney.c$(PreprocessSuffix) "src/uocmoney.c"

$(IntermediateDirectory)/src_movements.c$(ObjectSuffix): src/movements.c $(IntermediateDirectory)/src_movements.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/Xavier/Desktop/Programacio/PR2/UOCMoney/UOCMoney/src/movements.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_movements.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_movements.c$(DependSuffix): src/movements.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_movements.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_movements.c$(DependSuffix) -MM "src/movements.c"

$(IntermediateDirectory)/src_movements.c$(PreprocessSuffix): src/movements.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_movements.c$(PreprocessSuffix) "src/movements.c"

$(IntermediateDirectory)/src_test.c$(ObjectSuffix): src/test.c $(IntermediateDirectory)/src_test.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/Xavier/Desktop/Programacio/PR2/UOCMoney/UOCMoney/src/test.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_test.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_test.c$(DependSuffix): src/test.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_test.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_test.c$(DependSuffix) -MM "src/test.c"

$(IntermediateDirectory)/src_test.c$(PreprocessSuffix): src/test.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_test.c$(PreprocessSuffix) "src/test.c"

$(IntermediateDirectory)/src_menu.c$(ObjectSuffix): src/menu.c $(IntermediateDirectory)/src_menu.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/Xavier/Desktop/Programacio/PR2/UOCMoney/UOCMoney/src/menu.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_menu.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_menu.c$(DependSuffix): src/menu.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_menu.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_menu.c$(DependSuffix) -MM "src/menu.c"

$(IntermediateDirectory)/src_menu.c$(PreprocessSuffix): src/menu.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_menu.c$(PreprocessSuffix) "src/menu.c"

$(IntermediateDirectory)/src_concepts.c$(ObjectSuffix): src/concepts.c $(IntermediateDirectory)/src_concepts.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/Xavier/Desktop/Programacio/PR2/UOCMoney/UOCMoney/src/concepts.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_concepts.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_concepts.c$(DependSuffix): src/concepts.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_concepts.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_concepts.c$(DependSuffix) -MM "src/concepts.c"

$(IntermediateDirectory)/src_concepts.c$(PreprocessSuffix): src/concepts.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_concepts.c$(PreprocessSuffix) "src/concepts.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/


