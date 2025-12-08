cmake_minimum_required(VERSION 3.23)

# Collect chess app files
file(GLOB_RECURSE CHESS_APP_SRC
	CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

# Create ChessApp static library
add_library(ChessApp STATIC ${CHESS_APP_SRC})

# Include directory for ChessApp headers
target_include_directories(ChessApp
	PUBLIC
		"${CMAKE_SOURCE_DIR}/include"
		"${boost_SOURCE_DIR}/libs/process/include"
		"${boost_SOURCE_DIR}/libs/asio/include"
		"${boost_SOURCE_DIR}/libs/system/include"
		"${boost_SOURCE_DIR}/libs/config/include"
		"${boost_SOURCE_DIR}/libs/core/include"
		"${boost_SOURCE_DIR}/libs/filesystem/include"
		"${boost_SOURCE_DIR}/libs/algorithm/include"
)

target_link_libraries(ChessApp PUBLIC
    Boost::process
    Boost::asio
    Boost::system
)