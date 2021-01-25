project(svgeezer_lib)

add_library(svgeezer_lib svgeezy.h svgeezy.cpp)

target_link_libraries(svgeezer_lib PUBLIC
	CONAN_PKG::opencv
	)

add_executable(tinker tinker.cpp)
target_link_libraries(tinker PUBLIC
		CONAN_PKG::opencv
		)

# target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/lib")
# install (TARGETS svgeezer DESTINATION ${INSTALL_PREFIX}/bin)




