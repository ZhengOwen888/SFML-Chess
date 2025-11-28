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
)