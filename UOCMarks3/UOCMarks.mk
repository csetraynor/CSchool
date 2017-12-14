##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=UOCMarks
ConfigurationName      :=Debug
WorkspacePath          :=/home/carlos/C-Factory/UOCMarks3
ProjectPath            :=/home/carlos/C-Factory/UOCMarks3
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=carl carlson
Date                   :=18/12/16
CodeLitePath           :=/home/carlos/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
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
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="UOCMarks.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
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
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall -Wno-unused-result -Wpedantic $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/src_main.c$(ObjectSuffix) $(IntermediateDirectory)/src_menu.c$(ObjectSuffix) $(IntermediateDirectory)/src_test.c$(ObjectSuffix) $(IntermediateDirectory)/src_queue.c$(ObjectSuffix) $(IntermediateDirectory)/src_students.c$(ObjectSuffix) $(IntermediateDirectory)/src_subjects.c$(ObjectSuffix) $(IntermediateDirectory)/src_marks.c$(ObjectSuffix) $(IntermediateDirectory)/src_record.c$(ObjectSuffix) $(IntermediateDirectory)/src_api.c$(ObjectSuffix) 



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
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_main.c$(ObjectSuffix): src/main.c $(IntermediateDirectory)/src_main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/carlos/C-Factory/UOCMarks3/src/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_main.c$(DependSuffix): src/main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_main.c$(DependSuffix) -MM src/main.c

$(IntermediateDirectory)/src_main.c$(PreprocessSuffix): src/main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_main.c$(PreprocessSuffix)src/main.c

$(IntermediateDirectory)/src_menu.c$(ObjectSuffix): src/menu.c $(IntermediateDirectory)/src_menu.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/carlos/C-Factory/UOCMarks3/src/menu.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_menu.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_menu.c$(DependSuffix): src/menu.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_menu.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_menu.c$(DependSuffix) -MM src/menu.c

$(IntermediateDirectory)/src_menu.c$(PreprocessSuffix): src/menu.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_menu.c$(PreprocessSuffix)src/menu.c

$(IntermediateDirectory)/src_test.c$(ObjectSuffix): src/test.c $(IntermediateDirectory)/src_test.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/carlos/C-Factory/UOCMarks3/src/test.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_test.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_test.c$(DependSuffix): src/test.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_test.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_test.c$(DependSuffix) -MM src/test.c

$(IntermediateDirectory)/src_test.c$(PreprocessSuffix): src/test.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_test.c$(PreprocessSuffix)src/test.c

$(IntermediateDirectory)/src_queue.c$(ObjectSuffix): src/queue.c $(IntermediateDirectory)/src_queue.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/carlos/C-Factory/UOCMarks3/src/queue.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_queue.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_queue.c$(DependSuffix): src/queue.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_queue.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_queue.c$(DependSuffix) -MM src/queue.c

$(IntermediateDirectory)/src_queue.c$(PreprocessSuffix): src/queue.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_queue.c$(PreprocessSuffix)src/queue.c

$(IntermediateDirectory)/src_students.c$(ObjectSuffix): src/students.c $(IntermediateDirectory)/src_students.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/carlos/C-Factory/UOCMarks3/src/students.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_students.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_students.c$(DependSuffix): src/students.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_students.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_students.c$(DependSuffix) -MM src/students.c

$(IntermediateDirectory)/src_students.c$(PreprocessSuffix): src/students.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_students.c$(PreprocessSuffix)src/students.c

$(IntermediateDirectory)/src_subjects.c$(ObjectSuffix): src/subjects.c $(IntermediateDirectory)/src_subjects.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/carlos/C-Factory/UOCMarks3/src/subjects.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_subjects.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_subjects.c$(DependSuffix): src/subjects.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_subjects.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_subjects.c$(DependSuffix) -MM src/subjects.c

$(IntermediateDirectory)/src_subjects.c$(PreprocessSuffix): src/subjects.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_subjects.c$(PreprocessSuffix)src/subjects.c

$(IntermediateDirectory)/src_marks.c$(ObjectSuffix): src/marks.c $(IntermediateDirectory)/src_marks.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/carlos/C-Factory/UOCMarks3/src/marks.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_marks.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_marks.c$(DependSuffix): src/marks.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_marks.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_marks.c$(DependSuffix) -MM src/marks.c

$(IntermediateDirectory)/src_marks.c$(PreprocessSuffix): src/marks.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_marks.c$(PreprocessSuffix)src/marks.c

$(IntermediateDirectory)/src_record.c$(ObjectSuffix): src/record.c $(IntermediateDirectory)/src_record.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/carlos/C-Factory/UOCMarks3/src/record.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_record.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_record.c$(DependSuffix): src/record.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_record.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_record.c$(DependSuffix) -MM src/record.c

$(IntermediateDirectory)/src_record.c$(PreprocessSuffix): src/record.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_record.c$(PreprocessSuffix)src/record.c

$(IntermediateDirectory)/src_api.c$(ObjectSuffix): src/api.c $(IntermediateDirectory)/src_api.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/carlos/C-Factory/UOCMarks3/src/api.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_api.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_api.c$(DependSuffix): src/api.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_api.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_api.c$(DependSuffix) -MM src/api.c

$(IntermediateDirectory)/src_api.c$(PreprocessSuffix): src/api.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_api.c$(PreprocessSuffix)src/api.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


