add_library(jami-cpp
	jami-cpp.cpp
	Account.cpp
	proxy/JamiConfigurationManagerController.cpp)
target_compile_features(jami-cpp PRIVATE cxx_std_17)
target_link_libraries(jami-cpp PUBLIC sdbus-c++)
