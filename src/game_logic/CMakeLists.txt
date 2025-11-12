cmake_minimum_required(VERSION 3.23)

# Collect game logic files
file(GLOB_RECURSE GAME_LOGIC_SRC
	CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

# Create GameLogic static library
add_library(GameLogic STATIC ${GAME_LOGIC_SRC})

# Include directory for GameLogic headers
target_include_directories(GameLogic
	PUBLIC
		"${CMAKE_SOURCE_DIR}/include"
)