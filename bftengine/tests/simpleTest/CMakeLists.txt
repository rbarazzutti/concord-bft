set(simpleTest_client_source_files
        client.cpp
        ${CONFIG_FOLDER_PATH_VALUE}/test_comm_config.cpp
        ${CONFIG_FOLDER_PATH_VALUE}/config_file_parser.cpp
        ${concord_bft_tools_SOURCE_DIR}/KeyfileIOUtils.cpp
        simple_test_client.hpp
        )

set(simpleTest_replica_source_files
        replica.cpp
        ${CONFIG_FOLDER_PATH_VALUE}/test_comm_config.cpp
        ${CONFIG_FOLDER_PATH_VALUE}/config_file_parser.cpp
        ${concord_bft_tools_SOURCE_DIR}/KeyfileIOUtils.cpp
        simple_test_replica.hpp
        simple_test_replica_behavior.hpp
        )

# This target should be moved to UT infrastructure code when created.
set(config_source_files
    ${CONFIG_FOLDER_PATH_VALUE}/config_file_parser.cpp
    ${CONFIG_FOLDER_PATH_VALUE}/config_file_parser_test.cpp
)

add_executable(simpleTest_client $<TARGET_OBJECTS:logging_dev>
    ${simpleTest_client_source_files}
)

add_executable(simpleTest_server $<TARGET_OBJECTS:logging_dev>
    ${simpleTest_replica_source_files}
)

add_executable(configTest
    ${config_source_files}
    $<TARGET_OBJECTS:logging_dev>
)

add_executable(persistency_test
        persistency_test.cpp
        ${concord_bft_tools_SOURCE_DIR}/KeyfileIOUtils.cpp)

target_include_directories(persistency_test PUBLIC
        ${bftengine_SOURCE_DIR}/tests/simpleStorage
        ${CONFIG_FOLDER_PATH_VALUE}
        ${bftengine_SOURCE_DIR}/include/communication
        ${concord_bft_tools_SOURCE_DIR}
        ${SIMPLE_STORAGE_DIR})

target_link_libraries(persistency_test PUBLIC
        corebft
        gtest
        gtest_main
        test_config_lib
        $<TARGET_OBJECTS:logging_dev>
        simple_file_storage_lib)

add_test( persistency_test persistency_test )
add_custom_target(copy_simple_test_config ALL
        COMMENT "Copying config files of
        simpleTest")
add_custom_command(TARGET copy_simple_test_config
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/test_config
        $<TARGET_FILE_DIR:simpleTest_client>/)


if(${USE_COMM_PLAIN_TCP})
    target_compile_definitions(simpleTest_client PUBLIC USE_COMM_PLAIN_TCP)
    target_compile_definitions(simpleTest_server PUBLIC USE_COMM_PLAIN_TCP)
endif()

if(${USE_COMM_TLS_TCP})
    target_compile_definitions(simpleTest_client PUBLIC USE_COMM_TLS_TCP)
    target_compile_definitions(simpleTest_server PUBLIC USE_COMM_TLS_TCP)
endif()

set_target_properties(simpleTest_client PROPERTIES OUTPUT_NAME client)
set_target_properties(simpleTest_server PROPERTIES OUTPUT_NAME server)
set_target_properties(configTest PROPERTIES OUTPUT_NAME config)

target_link_libraries(simpleTest_client PUBLIC corebft)
target_link_libraries(simpleTest_server PUBLIC corebft simple_file_storage_lib)
target_link_libraries(configTest PUBLIC corebft)

target_include_directories(simpleTest_client
                           PRIVATE
                           ${concord_bft_tools_SOURCE_DIR}
                           ${bftengine_SOURCE_DIR}/include
                           ${CONFIG_FOLDER_PATH_VALUE})

target_include_directories(simpleTest_server
                           PRIVATE
                           ${bftengine_SOURCE_DIR}/tests/simpleStorage
                           ${concord_bft_tools_SOURCE_DIR}
                           ${bftengine_SOURCE_DIR}/src/bftengine
                           ${bftengine_SOURCE_DIR}/include
                           ${CONFIG_FOLDER_PATH_VALUE})

target_include_directories(configTest
                           PRIVATE
                           ${concord_bft_tools_SOURCE_DIR}
                           ${bftengine_SOURCE_DIR}/include
                           ${CONFIG_FOLDER_PATH_VALUE})

add_custom_target(copy_simple_test_scripts ALL COMMENT "Copying scripts of simpleTest")
add_custom_command(TARGET copy_simple_test_scripts
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:simpleTest_client>/scripts
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/scripts $<TARGET_FILE_DIR:simpleTest_client>/scripts)

# Fill in CMAKE variables in the test script
configure_file (
    "${CMAKE_CURRENT_SOURCE_DIR}/scripts/testReplicasAndClient.sh.in"
    "${CMAKE_CURRENT_BINARY_DIR}/scripts/testReplicasAndClient.sh"
)

# Fill in CMAKE variables in the python wrapper
configure_file (
    "${CMAKE_CURRENT_SOURCE_DIR}/scripts/simpleTest.py.in"
    "${CMAKE_CURRENT_BINARY_DIR}/scripts/simpleTest.py"
)

# Fill in CMAKE variables in the python histogram for perf test
configure_file (
        "${CMAKE_CURRENT_SOURCE_DIR}/scripts/histogram.py.in"
        "${CMAKE_CURRENT_BINARY_DIR}/scripts/histogram.py"
)

add_custom_target(copy_tls_script ALL COMMENT "Copying TLS script")
add_custom_command(TARGET copy_tls_script
        COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_SOURCE_DIR}/scripts/linux/create_tls_certs.sh
     $<TARGET_FILE_DIR:simpleTest_client>/scripts/create_tls_certs.sh)
