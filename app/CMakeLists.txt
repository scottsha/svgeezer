project(svgeezer)

add_executable(svgeezer svgeezer_main.cpp )
target_link_libraries(svgeezer PUBLIC
	CONAN_PKG::boost
	CONAN_PKG::opencv
	)

# target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/lib")
# install (TARGETS svgeezer DESTINATION ${INSTALL_PREFIX}/bin)




