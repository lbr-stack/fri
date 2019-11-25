BASE_DIR	= ../..
include $(BASE_DIR)/build/GNUMake/paths.mak
include $(BASE_DIR)/build/GNUMake/$(TOOLS_MAK)

SOURCES 		= LBRJointSineOverlayApp.cpp \
			 	  LBRJointSineOverlayClient.cpp

TARGET 		= LBRJointSineOverlay

CXXFLAGS 	+= 
LDFLAGS 		+= $(LIB_DIR)/libFRIClient.a

include $(BASE_DIR)/build/GNUMake/rules_examples.mak
