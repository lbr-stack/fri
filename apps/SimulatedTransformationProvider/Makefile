BASE_DIR	= ../..
include $(BASE_DIR)/build/GNUMake/paths.mak
include $(BASE_DIR)/build/GNUMake/$(TOOLS_MAK)

SOURCES 		= SimulatedTransformationProviderApp.cpp \
			 	  SimulatedTransformationProviderClient.cpp

TARGET 		= SimulatedTransformationProvider

CXXFLAGS 	+= 
LDFLAGS 		+= $(LIB_DIR)/libFRIClient.a

include $(BASE_DIR)/build/GNUMake/rules_examples.mak
